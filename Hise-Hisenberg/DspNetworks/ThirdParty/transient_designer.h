#pragma once
#include <JuceHeader.h>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV>
struct transient_designer : public data::base
{
    SNEX_NODE(transient_designer);
    struct MetadataClass { SN_NODE_ID("transient_designer"); };
    
    transient_designer()
    {
        snarePunch = 0.0f;    // -100 to +100 (bipolar control)
        attackTime = 5.0f;    // 5ms default
        releaseTime = 50.0f;  // 50ms default
        
        sampleRate = 44100.0;
        
        for (int ch = 0; ch < 2; ++ch)
        {
            fastEnv[ch] = 0.0f;
            slowEnv[ch] = 0.0f;
            smoothedGain[ch] = 1.0f;
            attackCutSmooth[ch] = 1.0f;
        }
        
        updateCoefficients();
    }
    
    static constexpr bool isModNode() { return false; }
    static constexpr bool isPolyphonic() { return NV > 1; }
    static constexpr bool hasTail() { return false; }
    static constexpr bool isSuspendedOnSilence() { return false; }
    static constexpr int getFixChannelAmount() { return 2; }
    static constexpr int NumTables = 0;
    static constexpr int NumSliderPacks = 0;
    static constexpr int NumAudioFiles = 0;
    static constexpr int NumFilters = 0;
    static constexpr int NumDisplayBuffers = 0;
    
    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;
        updateCoefficients();
    }
    
    void reset()
    {
        for (int ch = 0; ch < 2; ++ch)
        {
            fastEnv[ch] = 0.0f;
            slowEnv[ch] = 0.0f;
            smoothedGain[ch] = 1.0f;
            attackCutSmooth[ch] = 1.0f;
        }
    }
    
    void handleHiseEvent(HiseEvent& e) {}
    
    template <typename T> void process(T& data)
    {
        static constexpr int NumChannels = getFixChannelAmount();
        auto& fixData = data.template as<ProcessData<NumChannels>>();
        auto fd = fixData.toFrameData();
        
        while(fd.next())
        {
            processFrame(fd.toSpan());
        }
    }
    
    template <typename T> void processFrame(T& data)
    {
        data[0] = processChannel(data[0], 0);
        data[1] = processChannel(data[1], 1);
    }
    
    float processChannel(float input, int channel)
    {
        // Skip processing if knob is at center
        if (std::abs(snarePunch) < 0.1f) return input;
        
        const float absInput = std::abs(input);
        
        // References to per-channel state
        float& fast = fastEnv[channel];
        float& slow = slowEnv[channel];
        float& smoothed = smoothedGain[channel];
        
        // Two envelope followers - classic SPL method
        // Fast envelope: tracks rapid changes (attacks)
        if (absInput > fast)
            fast += fastAttack * (absInput - fast);
        else
            fast += fastRelease * (absInput - fast);
        
        // Slow envelope: tracks average level (sustain)
        if (absInput > slow)
            slow += slowAttack * (absInput - slow);
        else
            slow += slowRelease * (absInput - slow);
        
        // CRITICAL: SPL-style transient detection
        // The key is the DIFFERENCE between fast and slow envelopes
        float envDiff = fast - slow;
        
        // Normalize the difference - this is our "transient detector"
        // When envDiff is high = we're in attack phase
        // When envDiff is low/negative = we're in sustain phase
        float transientAmount = jlimit(-1.0f, 1.0f, envDiff * 8.0f); // Aggressive scaling
        
        // Calculate gain based on knob position and transient detection
        float gain = 1.0f;
        float knobNorm = snarePunch / 100.0f; // -1 to +1
        
        if (knobNorm < 0.0f) // Negative values: BOOST ATTACKS, CUT SUSTAIN
        {
            // When transientAmount is HIGH (attack): boost
            // When transientAmount is LOW (sustain): cut
            float attackBoost = jmax(0.0f, transientAmount) * (-knobNorm) * 18.0f; // Up to +18dB
            float sustainCut = jmax(0.0f, -transientAmount) * (-knobNorm) * -60.0f; // Down to -60dB
            
            float totalDB = attackBoost + sustainCut;
            gain = std::pow(10.0f, totalDB / 20.0f);
        }
        else // Positive values: CUT ATTACKS, BOOST SUSTAIN
        {
            // When transientAmount is HIGH (attack): cut
            // When transientAmount is LOW (sustain): boost
            float attackCut = jmax(0.0f, transientAmount) * knobNorm * -60.0f; // Down to -60dB
            float sustainBoost = jmax(0.0f, -transientAmount) * knobNorm * 12.0f; // Up to +12dB
            
            // Apply variable smoothing to attack cuts based on knob position
            // Smoothing strength increases with knob value (0 = no smoothing, 100 = full smoothing)
            float& attackSmooth = attackCutSmooth[channel];
            float attackCutGain = std::pow(10.0f, attackCut / 20.0f);
            
            // Variable smoothing coefficient based on knob position
            float variableSmoothCoeff = attackCutSmoothCoeff * knobNorm; // Scales from 0 to full smoothing
            attackSmooth += variableSmoothCoeff * (attackCutGain - attackSmooth);
            
            // Apply sustain boost directly (keep it sharp)
            float sustainGain = std::pow(10.0f, sustainBoost / 20.0f);
            
            gain = attackSmooth * sustainGain;
        }
        
        // Aggressive gain limiting for drum processing
        gain = jlimit(0.001f, 8.0f, gain); // -60dB to +18dB
        
        // Light smoothing to prevent extreme clicks but preserve transient character
        smoothed += smoothCoeff * (gain - smoothed);
        
        return input * smoothed;
    }
    
    int handleModulation(double& value) { return 0; }
    void setExternalData(const ExternalData& data, int index) {}
    
    template <int P>
    void setParameter(double v)
    {
        if (P == 0)
        {
            snarePunch = (float)v;
        }
        else if (P == 1)
        {
            attackTime = (float)v;
            updateCoefficients();
        }
        else if (P == 2)
        {
            releaseTime = (float)v;
            updateCoefficients();
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("Snare Punch", { -100.0, 100.0, 0.1 });
            registerCallback<0>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Attack Time", { 0.1, 20.0, 0.1 });
            registerCallback<1>(p);
            p.setDefaultValue(5.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Release Time", { 30.0, 200.0, 1.0 });
            registerCallback<2>(p);
            p.setDefaultValue(50.0);
            data.add(std::move(p));
        }
    }
    
private:
    // Parameters
    float snarePunch;     // -100 to +100: negative = more attack, positive = more sustain
    float attackTime;     // Fast envelope attack time (1-20ms)
    float releaseTime;    // Fast envelope release time (10-200ms)
    double sampleRate;
    
    // Envelope coefficients
    float fastAttack, fastRelease;
    float slowAttack, slowRelease;
    float smoothCoeff;
    float attackCutSmoothCoeff;
    
    // Per-channel states
    float fastEnv[2];        // Fast envelope follower (tracks attacks)
    float slowEnv[2];        // Slow envelope follower (tracks sustain)
    float smoothedGain[2];   // Smoothed gain output
    float attackCutSmooth[2]; // Separate smoothing for attack cuts to prevent pops
    
    void updateCoefficients()
    {
        // Fast envelope: user-controlled timing for attack detection
        fastAttack = 1.0f - std::exp(-1.0f / (attackTime * 0.001f * (float)sampleRate));
        fastRelease = 1.0f - std::exp(-1.0f / (releaseTime * 0.001f * (float)sampleRate));
        
        // Slow envelope: much slower for sustain tracking
        // Using 8x multiplier for dramatic difference (not just 4x)
        slowAttack = 1.0f - std::exp(-1.0f / (attackTime * 8.0f * 0.001f * (float)sampleRate));
        slowRelease = 1.0f - std::exp(-1.0f / (releaseTime * 8.0f * 0.001f * (float)sampleRate));
        
        // Minimal gain smoothing - we want to preserve transient character
        smoothCoeff = 1.0f - std::exp(-1.0f / (0.5f * 0.001f * (float)sampleRate)); // 0.5ms smoothing
        
        // Attack cut smoothing - prevents pops when cutting attacks in sustain mode
        // 10ms smoothing that scales with knob position (0 at knob=0, full at knob=100)
        attackCutSmoothCoeff = 1.0f - std::exp(-1.0f / (10.0f * 0.001f * (float)sampleRate));
    }
};
}

// ==================================| VHS Peak Limiter - Vintage-Optimized Limiter |==================================

#pragma once
#include <JuceHeader.h>
#include <algorithm>
#include <cmath>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV> struct vhs_peakLimiter: public data::base
{
    // Metadata Definitions ------------------------------------------------------------------------
    
    SNEX_NODE(vhs_peakLimiter);
    
    struct MetadataClass
    {
        SN_NODE_ID("vhs_peakLimiter");
    };
    
    static constexpr bool isModNode() { return false; };
    static constexpr bool isPolyphonic() { return NV > 1; };
    static constexpr bool hasTail() { return false; };
    static constexpr bool isSuspendedOnSilence() { return false; };
    static constexpr int getFixChannelAmount() { return 2; };
    
    static constexpr int NumTables = 0;
    static constexpr int NumSliderPacks = 0;
    static constexpr int NumAudioFiles = 0;
    static constexpr int NumFilters = 0;
    static constexpr int NumDisplayBuffers = 0;
    
    // Constructor
    vhs_peakLimiter()
    {
        sampleRate = 44100.0;
        ceiling = -0.1; // -0.1dB ceiling (very conservative)
        release = 10.0; // 10ms release
        character = 0.3; // 30% character blend
        
        // Initialize processing state
        currentGain_L = currentGain_R = 1.0;
        envelope_L = envelope_R = 0.0;
        rmsSmooth_L = rmsSmooth_R = 0.0;
        
        updateCoefficients();
    }
    
    // Scriptnode Callbacks ------------------------------------------------------------------------
    
    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;
        updateCoefficients();
        reset();
    }
    
    void reset()
    {
        currentGain_L = currentGain_R = 1.0;
        envelope_L = envelope_R = 0.0;
        rmsSmooth_L = rmsSmooth_R = 0.0;
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
        // Process each channel independently for better stereo imaging
        data[0] = processChannel(data[0], 0);
        data[1] = processChannel(data[1], 1);
    }
    
    int handleModulation(double& value) { return 0; }
    void setExternalData(const ExternalData& data, int index) {}
    
    // Parameter Functions -------------------------------------------------------------------------
    
    template <int P> void setParameter(double v)
    {
        if (P == 0)
        {
            // Ceiling: -3.0dB to -0.1dB
            ceiling = jlimit(-3.0, -0.1, v);
            ceilingLinear = std::pow(10.0, ceiling / 20.0);
        }
        else if (P == 1)
        {
            // Release: 1ms to 100ms
            release = jlimit(1.0, 100.0, v);
            updateCoefficients();
        }
        else if (P == 2)
        {
            // Character: 0.0 = transparent, 1.0 = vintage warmth
            character = jlimit(0.0, 1.0, v);
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("Ceiling", { -3.0, -0.1 });
            registerCallback<0>(p);
            p.setDefaultValue(-0.1); // Very conservative ceiling
            data.add(std::move(p));
        }
        {
            parameter::data p("Release", { 1.0, 100.0 });
            registerCallback<1>(p);
            p.setDefaultValue(10.0); // Fast recovery for vintage feel
            data.add(std::move(p));
        }
        {
            parameter::data p("Character", { 0.0, 1.0 });
            registerCallback<2>(p);
            p.setDefaultValue(0.3); // Subtle vintage character
            data.add(std::move(p));
        }
    }
    
private:
    double sampleRate;
    double ceiling;        // Ceiling in dB
    double release;        // Release time in ms
    double character;      // Character amount (0-1)
    
    // Derived parameters
    double ceilingLinear;
    double attackCoeff;
    double releaseCoeff;
    double rmsCoeff;
    
    // Per-channel processing state
    double currentGain_L, currentGain_R;
    double envelope_L, envelope_R;
    double rmsSmooth_L, rmsSmooth_R;
    
    // Update filter coefficients
    void updateCoefficients()
    {
        // Ultra-fast attack (0.05ms) for peak catching
        double attackTime = 0.00005; // 0.05ms
        attackCoeff = std::exp(-1.0 / (attackTime * sampleRate));
        
        // User-controllable release
        double releaseTime = release / 1000.0; // Convert ms to seconds
        releaseCoeff = std::exp(-1.0 / (releaseTime * sampleRate));
        
        // RMS smoothing for character detection (5ms)
        rmsCoeff = std::exp(-1.0 / (0.005 * sampleRate));
        
        // Update ceiling
        ceilingLinear = std::pow(10.0, ceiling / 20.0);
        
        // Clamp coefficients
        attackCoeff = jlimit(0.0, 0.99, attackCoeff);
        releaseCoeff = jlimit(0.0, 0.99, releaseCoeff);
        rmsCoeff = jlimit(0.0, 0.99, rmsCoeff);
    }
    
    // Process individual channel
    inline float processChannel(float input, int channel)
    {
        // Get channel-specific state
        double& currentGain = (channel == 0) ? currentGain_L : currentGain_R;
        double& envelope = (channel == 0) ? envelope_L : envelope_R;
        double& rmsSmooth = (channel == 0) ? rmsSmooth_L : rmsSmooth_R;
        
        // === 1. Multi-Stage Detection ===
        
        // Peak detection for hard limiting
        double peak = std::abs(input);
        
        // RMS detection for character
        rmsSmooth = rmsSmooth * rmsCoeff + (input * input) * (1.0 - rmsCoeff);
        double rms = std::sqrt(rmsSmooth);
        
        // Envelope follower for smooth limiting
        envelope = (peak > envelope) ?
        envelope * attackCoeff + peak * (1.0 - attackCoeff) :
        envelope * releaseCoeff + peak * (1.0 - releaseCoeff);
        
        // === 2. Intelligent Gain Calculation ===
        
        double targetGain = 1.0;
        
        // Primary peak limiting (always active)
        if (peak > ceilingLinear)
        {
            targetGain = ceilingLinear / peak;
        }
        
        // Secondary envelope-based limiting for smoother response
        if (envelope > ceilingLinear * 0.9) // Start limiting at 90% of ceiling
        {
            double envGain = (ceilingLinear * 0.9) / envelope;
            targetGain = std::min(targetGain, envGain);
        }
        
        // === 3. Character-Aware Gain Smoothing ===
        
        double smoothingCoeff;
        if (targetGain < currentGain)
        {
            // Attack phase - always fast for peak protection
            smoothingCoeff = attackCoeff;
        }
        else
        {
            // Release phase - adaptive based on character and signal content
            smoothingCoeff = releaseCoeff;
            
            // Character adjustment: more character = slower release for vintage pumping
            if (character > 0.0)
            {
                double characterFactor = 1.0 + character * 2.0; // 1.0 to 3.0 multiplier
                smoothingCoeff = std::pow(smoothingCoeff, characterFactor);
            }
            
            // Content-aware release: slower release during sustained passages
            if (rms > 0.1) // Sustained content detected
            {
                smoothingCoeff = std::pow(smoothingCoeff, 1.5); // 50% slower release
            }
        }
        
        // Apply smoothing
        currentGain = currentGain * smoothingCoeff + targetGain * (1.0 - smoothingCoeff);
        
        // === 4. Character Processing ===
        
        float output = input * (float)currentGain;
        
        if (character > 0.0 && currentGain < 0.98) // Only when limiting is active
        {
            // Add subtle vintage character through harmonic enhancement
            float characterAmount = (float)character * 0.1f; // Scale down for subtlety
            
            // Gentle even harmonic distortion (tape-like)
            float harmonics = output * output;
            if (output < 0.0f) harmonics = -harmonics; // Preserve sign
            
            // Compress the harmonics to prevent overs
            harmonics = std::tanh(harmonics * 2.0f) * 0.5f;
            
            // Blend in character based on gain reduction amount
            float reductionAmount = (float)(1.0 - currentGain); // How much we're limiting
            float characterGain = reductionAmount * characterAmount;
            
            output += harmonics * characterGain;
        }
        
        // === 5. Final Safety Limiting ===
        
        // Hard clip at ceiling + 0.1dB as final safety (should never engage)
        float safetyThreshold = (float)ceilingLinear * 1.012f; // +0.1dB
        if (std::abs(output) > safetyThreshold)
        {
            output = (output > 0.0f) ? safetyThreshold : -safetyThreshold;
        }
        
        return output;
    }
};
}

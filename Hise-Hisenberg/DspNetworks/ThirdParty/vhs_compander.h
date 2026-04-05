// ==================================| 80s VHS Dolby Compander |==================================
// Simulates the characteristic "bright, compressed" sound of VHS tapes played without proper Dolby decoding

#pragma once
#include <JuceHeader.h>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV> struct vhs_compander: public data::base
{
    // Metadata Definitions ------------------------------------------------------------------------
    
    SNEX_NODE(vhs_compander);
    
    struct MetadataClass
    {
        SN_NODE_ID("vhs_compander");
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
    vhs_compander()
    {
        sampleRate = 44100.0;
        dolbyIntensity = 0.5; // 50% of the effect
        eightyMode = 1.0;     // 1.0 = Dolby B, 0.0 = Dolby C
        
        // Initialize filter states per channel
        for (int ch = 0; ch < 2; ++ch)
        {
            // 3-band processing states (simplified from Dolby's 4-band for VHS character)
            lowBand[ch] = midBand[ch] = highBand[ch] = 0.0f;
            
            // Envelope followers per band
            lowEnv[ch] = midEnv[ch] = highEnv[ch] = 0.0f;
            
            // Gain controllers per band
            lowGain[ch] = midGain[ch] = highGain[ch] = 1.0f;
            
            // Spectral tilt states (your excellent implementation)
            tiltLow[ch] = tiltHigh[ch] = 0.0f;
        }
        
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
        for (int ch = 0; ch < 2; ++ch)
        {
            lowBand[ch] = midBand[ch] = highBand[ch] = 0.0f;
            lowEnv[ch] = midEnv[ch] = highEnv[ch] = 0.0f;
            lowGain[ch] = midGain[ch] = highGain[ch] = 1.0f;
            tiltLow[ch] = tiltHigh[ch] = 0.0f;
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
        if (dolbyIntensity <= 0.0f) return; // Bypass if no effect
        
        // Process each channel
        for (int ch = 0; ch < 2; ++ch)
        {
            float sample = data[ch];
            float drySample = sample;
            
            // Apply VHS compander with proper band splitting
            sample = processVHSCompander(sample, ch);
            
            // Blend with dry signal based on intensity
            data[ch] = drySample + (sample - drySample) * dolbyIntensity;
        }
    }
    
    int handleModulation(double& value) { return 0; }
    void setExternalData(const ExternalData& data, int index) {}
    
    // Parameter Functions -------------------------------------------------------------------------
    
    template <int P> void setParameter(double v)
    {
        if (P == 0)
        {
            // Dolby Intensity: 0.0 = off, 1.0 = full effect
            dolbyIntensity = jlimit(0.0f, 1.0f, (float)v);
        }
        else if (P == 1)
        {
            // 80s Mode: 0.0 = Dolby C (late 80s), 1.0 = Dolby B (early-mid 80s)
            eightyMode = jlimit(0.0f, 1.0f, (float)v);
            updateCoefficients();
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("Dolby Intensity", { 0.0, 1.0 });
            registerCallback<0>(p);
            p.setDefaultValue(0.5); // 50% effect
            data.add(std::move(p));
        }
        {
            parameter::data p("80s Mode", { 0.0, 1.0 });
            registerCallback<1>(p);
            p.setDefaultValue(1.0); // Dolby B (more common in early-mid 80s)
            data.add(std::move(p));
        }
    }
    
private:
    double sampleRate;
    float dolbyIntensity; // 0.0 to 1.0
    float eightyMode;     // 0.0 = Dolby C, 1.0 = Dolby B
    
    // Band-splitting coefficients (3-band system for VHS character)
    float lowCoeff, midCoeff, highCoeff;
    
    // Exaggerated time constants for VHS character
    float attackCoeff, releaseCoeff;
    
    // Your excellent spectral tilt coefficients
    float tiltLowCoeff, tiltHighCoeff;
    
    // Per-channel processing states
    float lowBand[2], midBand[2], highBand[2];           // Band filters
    float lowEnv[2], midEnv[2], highEnv[2];              // Envelope followers
    float lowGain[2], midGain[2], highGain[2];           // Gain controllers
    float tiltLow[2], tiltHigh[2];                       // Your spectral tilt
    
    // Update filter coefficients based on Dolby type
    void updateCoefficients()
    {
        // 3-band crossover frequencies (simplified from Dolby for VHS character)
        float lowFreq = 800.0f;  // Low-mid crossover
        float highFreq = eightyMode * 3000.0f + (1.0f - eightyMode) * 2000.0f; // Mid-high crossover
        
        // Calculate band-splitting coefficients
        lowCoeff = calculateLowPassCoeff(lowFreq);
        midCoeff = calculateBandPassCoeff(lowFreq, highFreq);
        highCoeff = calculateHighPassCoeff(highFreq);
        
        // Exaggerated time constants for VHS character (slower than real Dolby)
        float attackTime = eightyMode * 0.005f + (1.0f - eightyMode) * 0.003f;  // Slower: B: 5ms, C: 3ms
        float releaseTime = eightyMode * 0.150f + (1.0f - eightyMode) * 0.100f; // Slower: B: 150ms, C: 100ms
        
        attackCoeff = std::exp(-1.0f / ((float)sampleRate * attackTime));
        releaseCoeff = std::exp(-1.0f / ((float)sampleRate * releaseTime));
        
        // Your excellent spectral tilt coefficients (keeping these!)
        tiltLowCoeff = calculateLowPassCoeff(800.0f);   // Low shelf
        tiltHighCoeff = calculateHighPassCoeff(3000.0f); // High shelf
        
        // Clamp all coefficients
        lowCoeff = jlimit(0.01f, 0.99f, lowCoeff);
        midCoeff = jlimit(0.01f, 0.99f, midCoeff);
        highCoeff = jlimit(0.01f, 0.99f, highCoeff);
        attackCoeff = jlimit(0.01f, 0.99f, attackCoeff);
        releaseCoeff = jlimit(0.01f, 0.99f, releaseCoeff);
        tiltLowCoeff = jlimit(0.01f, 0.99f, tiltLowCoeff);
        tiltHighCoeff = jlimit(0.01f, 0.99f, tiltHighCoeff);
    }
    
    // Helper functions for filter coefficient calculation
    inline float calculateHighPassCoeff(float freq)
    {
        float omega = 2.0f * float(M_PI) * freq / (float)sampleRate;
        return std::exp(-omega);
    }
    
    inline float calculateLowPassCoeff(float freq)
    {
        float omega = 2.0f * float(M_PI) * freq / (float)sampleRate;
        return 1.0f - std::exp(-omega);
    }
    
    inline float calculateBandPassCoeff(float lowFreq, float highFreq)
    {
        // Simple bandpass approximation
        return (calculateLowPassCoeff(highFreq) + calculateHighPassCoeff(lowFreq)) * 0.5f;
    }
    
    // Main VHS compander processing with proper band splitting
    inline float processVHSCompander(float input, int channel)
    {
        float sample = input;
        
        // === 1. Band Splitting (3-band system optimized for VHS character) ===
        
        // Low band: up to ~800Hz
        lowBand[channel] += lowCoeff * (sample - lowBand[channel]);
        float lowSignal = lowBand[channel];
        
        // Mid band: ~800Hz to ~3kHz (the vocal range - key for VHS)
        float midInput = sample - lowSignal; // Remove lows
        midBand[channel] += midCoeff * (midInput - midBand[channel]);
        float midSignal = midBand[channel];
        
        // High band: above ~3kHz (the hiss and brightness region)
        highBand[channel] = highBand[channel] * highCoeff + sample * (1.0f - highCoeff);
        float highSignal = sample - highBand[channel];
        
        // === 2. Per-Band Compression with Exaggerated Characteristics ===
        
        // Low band: minimal processing (VHS doesn't compress lows much)
        float lowLevel = std::abs(lowSignal);
        lowEnv[channel] = updateEnvelope(lowEnv[channel], lowLevel);
        lowGain[channel] = calculateVHSGain(lowEnv[channel], 0.3f); // Gentle processing
        float processedLow = lowSignal * lowGain[channel];
        
        // Mid band: moderate compression (vocal presence)
        float midLevel = std::abs(midSignal);
        midEnv[channel] = updateEnvelope(midEnv[channel], midLevel);
        midGain[channel] = calculateVHSGain(midEnv[channel], 0.8f); // Stronger processing
        float processedMid = midSignal * midGain[channel];
        
        // High band: aggressive compression (the key to VHS brightness)
        float highLevel = std::abs(highSignal);
        highEnv[channel] = updateEnvelope(highEnv[channel], highLevel);
        highGain[channel] = calculateVHSGain(highEnv[channel], 1.2f); // Exaggerated processing
        float processedHigh = highSignal * highGain[channel];
        
        // === 3. Recombine Bands ===
        sample = processedLow + processedMid + processedHigh;
        
        // === 4. Your Excellent Spectral Tilt (keeping this exactly as you had it!) ===
        // VHS + undecoded Dolby creates a characteristic spectral tilt
        
        // Low frequency rolloff
        tiltLow[channel] += tiltLowCoeff * (sample - tiltLow[channel]);
        
        // High frequency emphasis
        tiltHigh[channel] = tiltHigh[channel] * tiltHighCoeff + sample * (1.0f - tiltHighCoeff);
        float tiltedHigh = sample - tiltHigh[channel];
        
        // Combine for characteristic tilt (your magic numbers!)
        sample = tiltLow[channel] * 0.9f + tiltedHigh * 0.4f + sample * 0.7f;
        
        // === 5. Subtle Saturation (VHS electronics + Dolby circuits) ===
        // Very gentle saturation to simulate the electronic stages
        if (std::abs(sample) > 0.7f)
        {
            sample = std::tanh(sample * 0.9f) * 1.1f;
        }
        
        return sample;
    }
    
    inline float updateEnvelope(float currentEnv, float inputLevel)
    {
        // Envelope follower with exaggerated time constants for VHS character
        if (inputLevel > currentEnv)
            return currentEnv * attackCoeff + inputLevel * (1.0f - attackCoeff);
        else
            return currentEnv * releaseCoeff + inputLevel * (1.0f - releaseCoeff);
    }
    
    inline float calculateVHSGain(float envelope, float intensity)
    {
        // VHS-style gain calculation: exaggerated compared to real Dolby
        // Lower threshold and higher ratios for more character
        
        const float threshold = 0.05f;  // Higher threshold than Dolby (-26dB vs -40dB)
        const float maxGain = 4.0f;     // 12dB maximum boost (higher than Dolby's 10dB)
        
        if (envelope < threshold)
        {
            // Below threshold: strong boost for quiet signals (VHS pumping character)
            float gainReduction = envelope / threshold;
            float targetGain = 1.0f + (maxGain - 1.0f) * (1.0f - gainReduction) * intensity;
            return jlimit(1.0f, maxGain, targetGain);
        }
        else
        {
            // Above threshold: exaggerated compression ratios
            float compressionRatio = eightyMode * 3.0f + (1.0f - eightyMode) * 4.0f; // Higher ratios than real Dolby
            float overThreshold = envelope / threshold;
            float compressedGain = 1.0f + (overThreshold - 1.0f) / compressionRatio;
            return jlimit(0.5f, 2.0f, compressedGain * intensity); // Allow more extreme ranges
        }
    }
};

} // namespace project

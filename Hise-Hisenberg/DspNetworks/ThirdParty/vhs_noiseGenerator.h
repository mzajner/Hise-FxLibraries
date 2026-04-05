// ==================================| Multi-Format Vintage Noise Generator |==================================

#pragma once
#include <JuceHeader.h>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV> struct vhs_noiseGenerator: public data::base
{
    // Metadata Definitions ------------------------------------------------------------------------
    
    SNEX_NODE(vhs_noiseGenerator);
    
    struct MetadataClass
    {
        SN_NODE_ID("vhs_noiseGenerator");
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
    
    // Noise Format Types
    enum NoiseFormat {
        TAPE = 0,      // Professional reel-to-reel tape
        CASSETTE = 1,  // Compact cassette
        VHS = 2,       // VHS linear audio
        RADIO = 3      // AM/FM radio static
    };
    
    // Constructor
    vhs_noiseGenerator()
    {
        sampleRate = 44100.0;
        noiseFormat = CASSETTE; // Default to cassette
        noiseLevel = 0.0;
        slewAmount = 0.0;
        
        // Initialize RMS detection (Chowdhury's level-dependent noise)
        rmsSmooth_L = rmsSmooth_R = 0.0f;
        
        // Initialize noise generation states
        pinkState1 = pinkState2 = pinkState3 = pinkState4 = 0.0f;
        whiteState = 0.0f;
        
        // Initialize filter states
        filter_L1 = filter_L2 = 0.0f;
        filter_R1 = filter_R2 = 0.0f;
        
        // Initialize format-specific generators
        humPhase = 0.0;
        staticPhase = 0.0;
        crackleClock = 0;
        
        // Initialize slew noise detection
        lastSample_L = lastSample_R = 0.0f;
        slewFilter_L = slewFilter_R = 0.0f;
        rmsSmooth_L = rmsSmooth_R = 0.0f;
        
        randomSeed = 1;
    }
    
    // Scriptnode Callbacks ------------------------------------------------------------------------
    
    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;
        updateFormatSettings();
        reset();
    }
    
    void reset()
    {
        pinkState1 = pinkState2 = pinkState3 = pinkState4 = 0.0f;
        whiteState = 0.0f;
        filter_L1 = filter_L2 = 0.0f;
        filter_R1 = filter_R2 = 0.0f;
        humPhase = staticPhase = 0.0;
        crackleClock = 0;
        lastSample_L = lastSample_R = 0.0f;
        slewFilter_L = slewFilter_R = 0.0f;
        randomSeed = 1;
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
        if (noiseLevel <= 0.0f) return; // Bypass if no noise
        
        float inputL = data[0];
        float inputR = data[1];
        
        float noiseL = 0.0f;
        float noiseR = 0.0f;
        
        // Generate noise based on selected format
        switch (noiseFormat)
        {
            case TAPE:
                generateTapeNoise(noiseL, noiseR);
                break;
            case CASSETTE:
                generateCassetteNoise(noiseL, noiseR, inputL, inputR);
                break;
            case VHS:
                generateVHSNoise(noiseL, noiseR, inputL, inputR);
                break;
            case RADIO:
                generateRadioNoise(noiseL, noiseR);
                break;
        }
        
        // Scale by noise level and add to signal
        data[0] = inputL + noiseL * noiseLevel;
        data[1] = inputR + noiseR * noiseLevel;
    }
    
    int handleModulation(double& value) { return 0; }
    void setExternalData(const ExternalData& data, int index) {}
    
    // Parameter Functions -------------------------------------------------------------------------
    
    template <int P> void setParameter(double v)
    {
        if (P == 0)
        {
            // Noise Format (0=Tape, 1=Cassette, 2=VHS, 3=Radio)
            int format = (int)(v * 3.99f); // Map 0-1 to 0-3
            noiseFormat = (NoiseFormat)jlimit(0, 3, format);
            updateFormatSettings();
        }
        else if (P == 1)
        {
            // Noise Level
            noiseLevel = jlimit(0.0f, 1.0f, (float)v);
        }
        else if (P == 2)
        {
            // Slew Noise Amount (for dynamic tape dust effect)
            slewAmount = jlimit(0.0f, 1.0f, (float)v);
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("Format", { 0.0, 1.0 });
            registerCallback<0>(p);
            p.setDefaultValue(0.25); // Cassette (1/4 = 0.25)
            data.add(std::move(p));
        }
        {
            parameter::data p("Noise Level", { 0.0, 1.0 });
            registerCallback<1>(p);
            p.setDefaultValue(0.3); // 30% noise level
            data.add(std::move(p));
        }
        {
            parameter::data p("Slew Amount", { 0.0, 1.0 });
            registerCallback<2>(p);
            p.setDefaultValue(0.2); // 20% slew noise
            data.add(std::move(p));
        }
    }
    
private:
    double sampleRate;
    NoiseFormat noiseFormat;
    float noiseLevel;
    float slewAmount; // Control for slew noise intensity
    
    // Chowdhury-style level detection
    float rmsSmooth_L, rmsSmooth_R;
    float rmsCoeff;
    
    // Noise generation states
    float pinkState1, pinkState2, pinkState3, pinkState4;
    float whiteState;
    
    // Filtering states
    float filter_L1, filter_L2, filter_R1, filter_R2;
    float filterCoeff1, filterCoeff2;
    
    // Format-specific generators
    double humPhase, humPhaseIncrement;
    double staticPhase, staticPhaseIncrement;
    int crackleClock;
    
    // Slew noise detection
    float lastSample_L, lastSample_R;
    float slewFilter_L, slewFilter_R;
    float slewFilterCoeff;
    
    uint32_t randomSeed;
    
    // === Format Settings Update ===
    void updateFormatSettings()
    {
        switch (noiseFormat)
        {
            case TAPE:
                // Professional tape: 15 IPS, excellent freq response up to 20kHz
                filterCoeff1 = 1.0f - std::exp(-2.0f * float(M_PI) * 18000.0f / (float)sampleRate);
                filterCoeff2 = 1.0f - std::exp(-2.0f * float(M_PI) * 20000.0f / (float)sampleRate);
                break;
                
            case CASSETTE:
                // Compact cassette: good response up to 15kHz, some bias noise
                filterCoeff1 = 1.0f - std::exp(-2.0f * float(M_PI) * 12000.0f / (float)sampleRate);
                filterCoeff2 = 1.0f - std::exp(-2.0f * float(M_PI) * 15000.0f / (float)sampleRate);
                break;
                
            case VHS:
                // VHS linear: limited to ~10kHz, poor SNR
                filterCoeff1 = 1.0f - std::exp(-2.0f * float(M_PI) * 8000.0f / (float)sampleRate);
                filterCoeff2 = 1.0f - std::exp(-2.0f * float(M_PI) * 10000.0f / (float)sampleRate);
                humPhaseIncrement = 2.0 * M_PI * 60.0 / sampleRate; // 60Hz hum
                break;
                
            case RADIO:
                // Radio: wide range but with static and interference
                filterCoeff1 = 1.0f - std::exp(-2.0f * float(M_PI) * 6000.0f / (float)sampleRate);
                filterCoeff2 = 1.0f - std::exp(-2.0f * float(M_PI) * 16000.0f / (float)sampleRate);
                staticPhaseIncrement = 2.0 * M_PI * 2500.0 / sampleRate; // 2.5kHz carrier bleed
                break;
        }
        
        // Slew detection for dynamic noise
        slewFilterCoeff = std::exp(-2.0f * float(M_PI) * 1000.0f / (float)sampleRate);
        
        // RMS detection for level-dependent noise (Chowdhury's insight)
        rmsCoeff = 1.0 - std::exp(-1.0 / (0.02 * sampleRate)); // 20ms smoothing
        
        // Clamp coefficients
        filterCoeff1 = jlimit(0.01f, 0.99f, filterCoeff1);
        filterCoeff2 = jlimit(0.01f, 0.99f, filterCoeff2);
        slewFilterCoeff = jlimit(0.01f, 0.99f, slewFilterCoeff);
        rmsCoeff = jlimit(0.01f, 0.99f, rmsCoeff);
    }
    
    // === Random Number Generator ===
    inline float generateRandom()
    {
        randomSeed = randomSeed * 1664525 + 1013904223;
        return ((float)(randomSeed >> 16) / 32768.0f) - 1.0f;
    }
    
    // === Noise Generators ===
    inline float generatePinkNoise()
    {
        float white = generateRandom();
        pinkState1 = 0.99886f * pinkState1 + white * 0.0555179f;
        pinkState2 = 0.99332f * pinkState2 + white * 0.0750759f;
        pinkState3 = 0.96900f * pinkState3 + white * 0.1538520f;
        pinkState4 = 0.86650f * pinkState4 + white * 0.3104856f;
        float pink = pinkState1 + pinkState2 + pinkState3 + pinkState4 + white * 0.5362f;
        return pink * 0.11f;
    }
    
    inline float generateWhiteNoise()
    {
        return generateRandom();
    }
    
    inline float applyFiltering(float input, int channel)
    {
        if (channel == 0) // Left
        {
            filter_L1 += filterCoeff1 * (input - filter_L1);
            filter_L2 += filterCoeff2 * (filter_L1 - filter_L2);
            return filter_L2;
        }
        else // Right
        {
            filter_R1 += filterCoeff1 * (input - filter_R1);
            filter_R2 += filterCoeff2 * (filter_R1 - filter_R2);
            return filter_R2;
        }
    }
    
    // === Format-Specific Noise Generators ===
    
    // Professional Tape: Clean pink noise, minimal artifacts
    void generateTapeNoise(float& outL, float& outR)
    {
        float pink = generatePinkNoise();
        outL = applyFiltering(pink, 0) * 0.02f; // Very low noise floor
        outR = applyFiltering(pink, 1) * 0.02f;
    }
    
    // Cassette: Pink noise + bias whistle + slight modulation
    void generateCassetteNoise(float& outL, float& outR, float inputL, float inputR)
    {
        float pink = generatePinkNoise() * 0.5f;
        
        // Add subtle bias tone (around 100kHz folded down)
        float biasNoise = std::sin(crackleClock * 0.01f) * 0.003f;
        crackleClock++;
        
        // Level-dependent noise (quieter during loud signals)
        float inputLevel = std::sqrt((inputL * inputL + inputR * inputR) * 0.5f);
        float levelFactor = 1.0f / (inputLevel + 0.1f);
        
        float noise = (pink + biasNoise) * levelFactor;
        outL = applyFiltering(noise, 0) * 0.025f;
        outR = applyFiltering(noise, 1) * 0.025f;
    }
    
    // VHS: Heavy hiss + 60Hz hum + slew noise
    void generateVHSNoise(float& outL, float& outR, float inputL, float inputR)
    {
        // Heavy pink noise hiss
        float hiss = generatePinkNoise() * 0.06f;
        
        // 60Hz AC hum with harmonics
        float hum = std::sin(humPhase) * 0.02f;
        hum += std::sin(humPhase * 2.0) * 0.008f; // 2nd harmonic
        humPhase += humPhaseIncrement;
        if (humPhase >= 2.0 * M_PI) humPhase -= 2.0 * M_PI;
        
        // Slew-dependent noise (TapeDust style)
        float slewL = generateSlewNoise(inputL, 0);
        float slewR = generateSlewNoise(inputR, 1);
        
        outL = applyFiltering(hiss + hum + slewL, 0);
        outR = applyFiltering(hiss + hum * 0.8f + slewR, 1); // Slightly different hum levels
    }
    
    // Radio: Filtered pink noise + subtle carrier bleed + random pops
    void generateRadioNoise(float& outL, float& outR)
    {
        // Use pink noise instead of white for less harsh highs
        float staticNoise = generatePinkNoise() * 0.025f; // Reduced level
        
        // Much quieter carrier frequency bleed-through
        float carrier = std::sin(staticPhase) * 0.0003f; // Reduced from 0.008f
        staticPhase += staticPhaseIncrement;
        if (staticPhase >= 2.0 * M_PI) staticPhase -= 2.0 * M_PI;
        
        // Random pops and clicks
        float pop = 0.0f;
        if ((crackleClock % 2000) == 0) // Random timing
        {
            pop = generateRandom() * 0.015f;
        }
        crackleClock++;
        
        float totalNoise = staticNoise + carrier + pop;
        outL = applyFiltering(totalNoise, 0);
        outR = applyFiltering(totalNoise, 1);
    }
    
    // === Slew Noise (for VHS) ===
    inline float generateSlewNoise(float input, int channel)
    {
        float* lastSample = (channel == 0) ? &lastSample_L : &lastSample_R;
        float* slewFilter = (channel == 0) ? &slewFilter_L : &slewFilter_R;
        
        float slewRate = std::abs(input - *lastSample);
        *lastSample = input;
        
        *slewFilter = *slewFilter * slewFilterCoeff + slewRate * (1.0f - slewFilterCoeff);
        float filteredSlew = slewRate - *slewFilter;
        
        float noise = generateRandom() * 0.3f;
        float slewNoise = noise * std::abs(filteredSlew) * 15.0f;
        
        return jlimit(-0.05f, 0.05f, slewNoise);
    }
};
}

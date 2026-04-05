// ==================================| Simple Tape Dropout Engine |==================================

#pragma once
#include <JuceHeader.h>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV> struct vhs_dropout: public data::base
{
    // Metadata Definitions ------------------------------------------------------------------------
    
    SNEX_NODE(vhs_dropout);
    
    struct MetadataClass
    {
        SN_NODE_ID("vhs_dropout");
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
    
    // Constructor - Keep it simple like your other nodes
    vhs_dropout()
    {
        sampleRate = 44100.0;
        dropoutIntensity = 0.0;
        dropoutType = 2; // Default to VHS (0=Silence, 1=Tape, 2=VHS, 3=Radio)
        dropoutLength = 0.5; // Default to medium length
        
        // Simple state variables
        dropoutCounter = 0;
        isInDropout = false;
        fadeCounter = 0;
        totalDropoutLength = 0; // Track total length for proper fade timing
        randomSeed = 12345;
        
        // Simple timing
        checkInterval = 4410; // Check every 100ms at 44.1kHz
        sampleCount = 0;
        
        // Simple noise generation state
        pinkState1 = pinkState2 = pinkState3 = pinkState4 = 0.0f;
    }
    
    // Scriptnode Callbacks - Following your working pattern ------------------------
    
    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;
        checkInterval = int(sampleRate * 0.1); // 100ms check interval
        fadeLength = int(sampleRate * 0.003); // 3ms fade (shorter for less clicks)
        reset();
    }
    
    void reset()
    {
        dropoutCounter = 0;
        isInDropout = false;
        fadeCounter = 0;
        totalDropoutLength = 0;
        sampleCount = 0;
        randomSeed = 12345;
        
        // Reset noise states
        pinkState1 = pinkState2 = pinkState3 = pinkState4 = 0.0f;
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
        if (dropoutIntensity <= 0.0f) return; // Bypass like your other nodes
        
        sampleCount++;
        
        // Check for new dropouts periodically
        if (sampleCount >= checkInterval)
        {
            sampleCount = 0;
            checkForDropout();
        }
        
        // Process current state
        if (isInDropout)
        {
            processDropout(data);
        }
    }
    
    int handleModulation(double& value) { return 0; }
    void setExternalData(const ExternalData& data, int index) {}
    
    // Parameter Functions - Following your pattern ------------------------------------------------
    
    template <int P> void setParameter(double v)
    {
        if (P == 0)
        {
            dropoutIntensity = jlimit(0.0f, 1.0f, (float)v);
        }
        else if (P == 1)
        {
            // Dropout Type (0=Silence, 1=Tape, 2=VHS, 3=Radio)
            int type = (int)(v * 3.99f); // Map 0-1 to 0-3
            dropoutType = jlimit(0, 3, type);
        }
        else if (P == 2)
        {
            // Dropout Length (0=short, 1=long)
            dropoutLength = jlimit(0.0f, 1.0f, (float)v);
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("Dropout Intensity", { 0.0, 1.0 });
            registerCallback<0>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Dropout Type", { 0.0, 1.0 });
            registerCallback<1>(p);
            p.setDefaultValue(0.5); // VHS (2/4 = 0.5)
            data.add(std::move(p));
        }
        {
            parameter::data p("Dropout Length", { 0.0, 1.0 });
            registerCallback<2>(p);
            p.setDefaultValue(0.5); // Medium length
            data.add(std::move(p));
        }
    }
    
private:
    double sampleRate;
    float dropoutIntensity;
    int dropoutType; // 0=Silence, 1=Tape, 2=VHS, 3=Radio
    float dropoutLength; // 0=short, 1=long
    
    // Simple state variables
    int dropoutCounter;
    bool isInDropout;
    int fadeCounter;
    int totalDropoutLength; // Track total length for fade calculations
    int fadeLength;
    int checkInterval;
    int sampleCount;
    uint32_t randomSeed;
    
    // Simple pink noise states
    float pinkState1, pinkState2, pinkState3, pinkState4;
    
    // Simple random generator - like your noise generator
    inline float getRandom()
    {
        randomSeed = randomSeed * 1664525 + 1013904223;
        return ((float)(randomSeed >> 16) / 32768.0f) - 1.0f;
    }
    
    inline uint32_t getRandomInt()
    {
        randomSeed = randomSeed * 1664525 + 1013904223;
        return randomSeed;
    }
    
    // Simple pink noise generator
    inline float generatePinkNoise()
    {
        float white = getRandom();
        pinkState1 = 0.99886f * pinkState1 + white * 0.0555179f;
        pinkState2 = 0.99332f * pinkState2 + white * 0.0750759f;
        pinkState3 = 0.96900f * pinkState3 + white * 0.1538520f;
        pinkState4 = 0.86650f * pinkState4 + white * 0.3104856f;
        float pink = pinkState1 + pinkState2 + pinkState3 + pinkState4 + white * 0.5362f;
        return pink * 0.11f;
    }
    
    // Simple dropout check
    void checkForDropout()
    {
        if (isInDropout) return; // Already dropping out
        
        // Simple probability check
        float chance = dropoutIntensity * 0.1f; // 10% of intensity per check
        float random = (float)getRandomInt() / (float)UINT32_MAX;
        
        if (random < chance)
        {
            startDropout();
        }
    }
    
    // Start a dropout event
    void startDropout()
    {
        isInDropout = true;
        fadeCounter = 0;
        
        // Calculate dropout length based on parameter
        // Short: 5ms-50ms, Medium: 10ms-200ms, Long: 50ms-500ms
        float minTime, maxTime;
        
        if (dropoutLength < 0.33f) // Short
        {
            minTime = 0.005f; // 5ms
            maxTime = 0.05f;  // 50ms
        }
        else if (dropoutLength < 0.66f) // Medium
        {
            minTime = 0.01f;  // 10ms
            maxTime = 0.2f;   // 200ms
        }
        else // Long
        {
            minTime = 0.05f;  // 50ms
            maxTime = 0.5f;   // 500ms
        }
        
        // Random duration within range
        float randomTime = minTime + (maxTime - minTime) * ((float)getRandomInt() / (float)UINT32_MAX);
        int duration = int(randomTime * sampleRate);
        
        dropoutCounter = duration;
        totalDropoutLength = duration; // Store for fade calculations
        
        // Ensure fade length doesn't exceed dropout length
        fadeLength = jmin(fadeLength, duration / 4); // Max 25% of dropout for fades
    }
    
    // Generate dropout noise based on type - BALANCED LEVELS
    float generateDropoutNoise()
    {
        switch (dropoutType)
        {
            case 0: // Silence
                return 0.0f;
                
            case 1: // Tape - quiet but audible hiss
                return generatePinkNoise() * 0.015f; // Increased from 0.003f
                
            case 2: // VHS - hiss + occasional glitches
            {
                float hiss = generatePinkNoise() * 0.015f; // Same base level as tape
                float glitch = 0.0f;
                if ((getRandomInt() % 1000) < 3) // 0.3% chance per sample
                {
                    glitch = getRandom() * 0.03f; // Reduced glitch level
                }
                return hiss + glitch;
            }
                
            case 3: // Radio - static + pops
            {
                float staticNoise = generatePinkNoise() * 0.015f; // Same base level
                float pop = 0.0f;
                if ((getRandomInt() % 2000) < 2) // 0.1% chance per sample
                {
                    pop = getRandom() * 0.02f; // Reduced pop level
                }
                return staticNoise + pop;
            }
                
            default:
                return 0.0f;
        }
    }
    
    // Process dropout frame with FIXED fades
    template <typename T>
    void processDropout(T& data)
    {
        dropoutCounter--;
        
        if (dropoutCounter <= 0)
        {
            isInDropout = false;
            return;
        }
        
        // Calculate how far we are into the dropout
        int samplesFromStart = totalDropoutLength - dropoutCounter;
        
        // Generate replacement noise first
        float noiseL = generateDropoutNoise();
        float noiseR = generateDropoutNoise() * 0.85f; // Slightly different for stereo
        
        // Apply fades - FIXED LOGIC
        if (samplesFromStart < fadeLength)
        {
            // Fade OUT (start of dropout) - crossfade from signal to noise
            float fadeOut = (float)samplesFromStart / (float)fadeLength;
            fadeOut = 0.5f * (1.0f - std::cos(fadeOut * float(M_PI))); // Smooth S-curve
            
            data[0] = data[0] * (1.0f - fadeOut) + noiseL * fadeOut;
            data[1] = data[1] * (1.0f - fadeOut) + noiseR * fadeOut;
        }
        else if (dropoutCounter < fadeLength)
        {
            // Fade IN (end of dropout) - crossfade from noise to signal
            float fadeIn = (float)dropoutCounter / (float)fadeLength;
            fadeIn = 0.5f * (1.0f - std::cos(fadeIn * float(M_PI))); // Smooth S-curve
            
            data[0] = data[0] * (1.0f - fadeIn) + noiseL * fadeIn;
            data[1] = data[1] * (1.0f - fadeIn) + noiseR * fadeIn;
        }
        else
        {
            // Full dropout - pure replacement
            data[0] = noiseL;
            data[1] = noiseR;
        }
    }
};
}

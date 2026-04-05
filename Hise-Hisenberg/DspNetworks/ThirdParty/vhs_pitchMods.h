// ==================================| Simplified VHS Pitch Instabilities |==================================

#pragma once
#include <JuceHeader.h>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV> struct vhs_pitchMods: public data::base
{
    // Metadata Definitions ------------------------------------------------------------------------
    
    SNEX_NODE(vhs_pitchMods);
    
    struct MetadataClass
    {
        SN_NODE_ID("vhs_pitchMods");
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
    vhs_pitchMods()
    {
        sampleRate = 44100.0;
        
        // Simple phase accumulators for VHS pitch effects
        speedHuntPhase = 0.0;
        speedHuntPhase2 = 0.0;
        stretchPhase = 0.0;
        driftPhase = 0.0;
        
        // Anti-aliasing filter states
        for (int ch = 0; ch < 2; ++ch)
        {
            writeIndex[ch] = 0;
            smoothedDelay[ch] = 8.0;
            
            modFilter1[ch] = 0.0;
            modFilter2[ch] = 0.0;
            
            for (int i = 0; i < delaySize; ++i)
            {
                delayBuffer[ch][i] = 0.0f;
            }
        }
        
        // Initialize parameters
        speedHuntDepth = 0.0;
        speedHuntRate = 1.5;
        stretchDepth = 0.0;
        stretchRate = 0.08;
        driftDepth = 0.0;
        driftRate = 0.02;
        
        srScale = 1.0;
    }
    
    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;
        srScale = sampleRate / 44100.0;
        
        // Reset phases
        speedHuntPhase = 0.0;
        speedHuntPhase2 = 0.0;
        stretchPhase = 0.0;
        driftPhase = 0.0;
        
        // Anti-aliasing filter
        double cutoffFreq = sampleRate * 0.125;
        modFilterCoeff = exp(-2.0 * 3.14159 * cutoffFreq / sampleRate);
        
        // Clear buffers
        for (int ch = 0; ch < 2; ++ch)
        {
            writeIndex[ch] = 0;
            smoothedDelay[ch] = 8.0 * srScale;
            modFilter1[ch] = 0.0;
            modFilter2[ch] = 0.0;
            
            for (int i = 0; i < delaySize; ++i)
            {
                delayBuffer[ch][i] = 0.0f;
            }
        }
    }
    
    void reset()
    {
        // Gentle reset
        speedHuntPhase *= 0.1;
        speedHuntPhase2 *= 0.1;
        stretchPhase *= 0.1;
        driftPhase *= 0.1;
        
        for (int ch = 0; ch < 2; ++ch)
        {
            writeIndex[ch] = 0;
            smoothedDelay[ch] = 8.0 * srScale;
            modFilter1[ch] *= 0.5;
            modFilter2[ch] *= 0.5;
            
            for (int i = 0; i < delaySize; ++i)
            {
                delayBuffer[ch][i] = 0.0f;
            }
        }
    }
    
    void handleHiseEvent(HiseEvent& e)
    {
        // No MIDI handling needed
    }
    
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
        double twoPi = 6.28318530717958647692;
        double sampleRateInv = 1.0 / sampleRate;
        
        // === Simple VHS-style pitch modulations ===
        
        // 1. Speed Hunt - VHS motor instabilities (like wow but more irregular)
        double speedHuntIncrement = speedHuntRate * twoPi * sampleRateInv;
        double speedHuntIncrement2 = speedHuntRate * 1.618 * twoPi * sampleRateInv; // Golden ratio detuning
        
        speedHuntPhase += speedHuntIncrement;
        if (speedHuntPhase >= twoPi) speedHuntPhase -= twoPi;
        
        speedHuntPhase2 += speedHuntIncrement2;
        if (speedHuntPhase2 >= twoPi) speedHuntPhase2 -= twoPi;
        
        double speedHuntMod = (sin(speedHuntPhase) + 0.4 * sin(speedHuntPhase2)) * speedHuntDepth;
        
        // 2. Tape Stretching - Occasional pitch drops (very slow)
        double stretchIncrement = stretchRate * twoPi * sampleRateInv;
        stretchPhase += stretchIncrement;
        if (stretchPhase >= twoPi) stretchPhase -= twoPi;
        
        // Create occasional pitch drops using a squared sine wave
        double stretchBase = sin(stretchPhase);
        double stretchMod = 0.0;
        if (stretchBase > 0.5 && stretchDepth > 0.0)  // Only on positive peaks
        {
            stretchMod = -stretchBase * stretchBase * stretchDepth * 0.5;  // Negative for pitch drop
        }
        
        // 3. Long-term Drift - Very slow pitch wandering
        double driftIncrement = driftRate * twoPi * sampleRateInv;
        driftPhase += driftIncrement;
        if (driftPhase >= twoPi) driftPhase -= twoPi;
        
        double driftMod = sin(driftPhase) * driftDepth * 0.3;
        
        // Combine all modulations
        double totalMod = speedHuntMod + stretchMod + driftMod;
        
        // VHS-style soft limiting
        if (totalMod > 0.5) totalMod = 0.5 + (totalMod - 0.5) * 0.6;
        if (totalMod < -0.5) totalMod = -0.5 + (totalMod + 0.5) * 0.6;
        
        // Convert to delay samples
        double delayModSamples = totalMod * 8.0 * srScale;  // Conservative scaling
        
        // Base delay
        double baseDelay = 8.0 * srScale;
        double targetDelay = baseDelay + delayModSamples;
        
        // Clamp to safe range
        targetDelay = jlimit(2.0, double(delaySize - 10), targetDelay);
        
        // Process both channels
        for (int ch = 0; ch < 2; ++ch)
        {
            // Smooth delay changes
            smoothedDelay[ch] += (targetDelay - smoothedDelay[ch]) * 0.01;
            
            // Slight stereo width - right channel gets offset
            double channelDelay = smoothedDelay[ch];
            if (ch == 1)
            {
                channelDelay += sin(speedHuntPhase * 0.8) * 0.3;
            }
            
            // Anti-aliasing filter
            modFilter1[ch] += (channelDelay - modFilter1[ch]) * (1.0 - modFilterCoeff);
            modFilter2[ch] += (modFilter1[ch] - modFilter2[ch]) * (1.0 - modFilterCoeff);
            double filteredDelay = modFilter2[ch];
            
            // Store input sample
            float inputSample = data[ch];
            delayBuffer[ch][writeIndex[ch]] = inputSample;
            
            // Calculate read position
            double readPos = double(writeIndex[ch]) - filteredDelay;
            while (readPos < 0.0) readPos += delaySize;
            while (readPos >= delaySize) readPos -= delaySize;
            
            // Cubic interpolation
            int idx = int(readPos);
            double frac = readPos - double(idx);
            
            int idx0 = (idx - 1 + delaySize) % delaySize;
            int idx1 = idx % delaySize;
            int idx2 = (idx + 1) % delaySize;
            int idx3 = (idx + 2) % delaySize;
            
            float y0 = delayBuffer[ch][idx0];
            float y1 = delayBuffer[ch][idx1];
            float y2 = delayBuffer[ch][idx2];
            float y3 = delayBuffer[ch][idx3];
            
            // Catmull-Rom cubic interpolation
            float a = -0.5f * y0 + 1.5f * y1 - 1.5f * y2 + 0.5f * y3;
            float b = y0 - 2.5f * y1 + 2.0f * y2 - 0.5f * y3;
            float c = -0.5f * y0 + 0.5f * y2;
            float d = y1;
            
            float delayedSample = a * frac * frac * frac + b * frac * frac + c * frac + d;
            
            // Output sample
            data[ch] = delayedSample;
            
            // Advance write pointer
            writeIndex[ch] = (writeIndex[ch] + 1) % delaySize;
        }
    }
    
    int handleModulation(double& value)
    {
        return 0;
    }
    
    void setExternalData(const ExternalData& data, int index)
    {
        // No external data needed
    }
    
    // Parameter Functions -------------------------------------------------------------------------
    
    template <int P> void setParameter(double v)
    {
        if (P == 0)      // Speed Hunt Depth
        {
            speedHuntDepth = v;
        }
        else if (P == 1) // Speed Hunt Rate
        {
            speedHuntRate = 0.5 + v * 4.5;  // 0.5 to 5.0 Hz
        }
        else if (P == 2) // Stretch Depth
        {
            stretchDepth = v;
        }
        else if (P == 3) // Stretch Rate
        {
            stretchRate = 0.02 + v * 0.48;  // 0.02 to 0.5 Hz (very slow)
        }
        else if (P == 4) // Drift Depth
        {
            driftDepth = v;
        }
        else if (P == 5) // Drift Rate
        {
            driftRate = 0.005 + v * 0.095;  // 0.005 to 0.1 Hz (very slow)
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("Speed Hunt Depth", { 0.0, 1.0 });
            registerCallback<0>(p);
            p.setDefaultValue(0.15);  // Moderate VHS speed hunting
            data.add(std::move(p));
        }
        {
            parameter::data p("Speed Hunt Rate", { 0.0, 1.0 });
            registerCallback<1>(p);
            p.setDefaultValue(0.3);   // Maps to ~2 Hz
            data.add(std::move(p));
        }
        {
            parameter::data p("Stretch Depth", { 0.0, 1.0 });
            registerCallback<2>(p);
            p.setDefaultValue(0.1);   // Subtle tape stretching
            data.add(std::move(p));
        }
        {
            parameter::data p("Stretch Rate", { 0.0, 1.0 });
            registerCallback<3>(p);
            p.setDefaultValue(0.2);   // Maps to ~0.12 Hz
            data.add(std::move(p));
        }
        {
            parameter::data p("Drift Depth", { 0.0, 1.0 });
            registerCallback<4>(p);
            p.setDefaultValue(0.08);  // Subtle long-term drift
            data.add(std::move(p));
        }
        {
            parameter::data p("Drift Rate", { 0.0, 1.0 });
            registerCallback<5>(p);
            p.setDefaultValue(0.2);   // Maps to ~0.024 Hz (very slow)
            data.add(std::move(p));
        }
    }
    
private:
    static constexpr int delaySize = 512;
    
    double sampleRate;
    double srScale;
    
    // Simple phase accumulators
    double speedHuntPhase;
    double speedHuntPhase2;
    double stretchPhase;
    double driftPhase;
    
    // Delay buffers and indices
    float delayBuffer[2][delaySize];
    int writeIndex[2];
    
    // Anti-aliasing and smoothing
    double smoothedDelay[2];
    double modFilter1[2];
    double modFilter2[2];
    double modFilterCoeff;
    
    // Parameters
    double speedHuntDepth;
    double speedHuntRate;
    double stretchDepth;
    double stretchRate;
    double driftDepth;
    double driftRate;
};
}

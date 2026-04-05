// ==================================| Tape Modulation - Enhanced for Stronger Effect |==================================

#pragma once
#include <JuceHeader.h>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV> struct vhs_modulation: public data::base
{
    // Metadata Definitions ------------------------------------------------------------------------
    
    SNEX_NODE(vhs_modulation);
    
    struct MetadataClass
    {
        SN_NODE_ID("vhs_modulation");
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
    
    // Constructor with anti-aliasing improvements
    vhs_modulation()
    {
        sampleRate = 44100.0;
        
        // High precision phase accumulators
        wowPhase = 0.0;
        wowPhase2 = 0.0;
        flutterPhase = 0.0;
        flutterPhase2 = 0.0;
        driftPhase = 0.0;
        variancePhase = 0.0;
        
        // Anti-aliasing filter states and delay smoothing
        for (int ch = 0; ch < 2; ++ch)
        {
            writeIndex[ch] = 0;
            smoothedDelay[ch] = 8.0;  // Initialize to base delay
            
            // 2-pole anti-aliasing filter for modulation
            modFilter1[ch] = 0.0;
            modFilter2[ch] = 0.0;
            
            for (int i = 0; i < delaySize; ++i)
            {
                delayBuffer[ch][i] = 0.0f;
            }
        }
        
        // Initialize parameters with tape-appropriate values
        wowDepth = 0.0;
        wowRate = 1.0;
        flutterDepth = 0.0;
        flutterRate = 8.0;
        variance = 0.0;
        drift = 0.0;
        
        // Sample rate scaling factor
        srScale = 1.0;
    }
    
    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;
        srScale = sampleRate / 44100.0;
        
        // Reset all phases
        wowPhase = 0.0;
        wowPhase2 = 0.0;
        flutterPhase = 0.0;
        flutterPhase2 = 0.0;
        driftPhase = 0.0;
        variancePhase = 0.0;
        
        // Calculate anti-aliasing filter coefficient
        // Cutoff at 1/4 of Nyquist to prevent modulation aliasing
        double cutoffFreq = sampleRate * 0.125;
        modFilterCoeff = exp(-2.0 * 3.14159 * cutoffFreq / sampleRate);
        
        // Clear delay buffers and filters
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
        // Gentle reset to avoid clicks
        wowPhase *= 0.1;
        wowPhase2 *= 0.1;
        flutterPhase *= 0.1;
        flutterPhase2 *= 0.1;
        driftPhase *= 0.1;
        variancePhase *= 0.1;
        
        for (int ch = 0; ch < 2; ++ch)
        {
            writeIndex[ch] = 0;
            smoothedDelay[ch] = 8.0 * srScale;
            // Gentle filter reset
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
        // High precision constants
        double twoPi = 6.28318530717958647692;
        double sampleRateInv = 1.0 / sampleRate;
        
        // Calculate phase increments - Classic tape wow/flutter characteristics
        double wowIncrement = wowRate * twoPi * sampleRateInv;
        double wowIncrement2 = wowRate * 1.618 * twoPi * sampleRateInv; // Golden ratio detuning
        double flutterIncrement = flutterRate * twoPi * sampleRateInv;
        double flutterIncrement2 = flutterRate * 1.3 * twoPi * sampleRateInv; // Slight detuning
        
        // Chowdhury's variance and drift frequencies for tape character
        double driftIncrement = 0.02 * twoPi * sampleRateInv; // Very slow drift (~0.02 Hz)
        double varianceIncrement = (20.0 + variance * 30.0) * twoPi * sampleRateInv; // 20-50 Hz range
        
        // Update phases with proper wraparound
        wowPhase += wowIncrement;
        if (wowPhase >= twoPi) wowPhase -= twoPi;
        
        wowPhase2 += wowIncrement2;
        if (wowPhase2 >= twoPi) wowPhase2 -= twoPi;
        
        flutterPhase += flutterIncrement;
        if (flutterPhase >= twoPi) flutterPhase -= twoPi;
        
        flutterPhase2 += flutterIncrement2;
        if (flutterPhase2 >= twoPi) flutterPhase2 -= twoPi;
        
        driftPhase += driftIncrement;
        if (driftPhase >= twoPi) driftPhase -= twoPi;
        
        variancePhase += varianceIncrement;
        if (variancePhase >= twoPi) variancePhase -= twoPi;
        
        // Generate Chowdhury-style modulations with tape character
        double wowMod = (sin(wowPhase) + 0.4 * sin(wowPhase2)) * wowDepth;
        double flutterMod = (sin(flutterPhase) + 0.6 * sin(flutterPhase2)) * flutterDepth;
        
        // Add Chowdhury's variance and drift for tape realism
        double driftMod = sin(driftPhase) * drift * 0.5; // Long-term drift
        double varianceMod = sin(variancePhase) * variance * 0.2; // Random-like irregularities
        
        // **VHS-SPECIFIC ADDITION**: Occasional pitch drops (from your VHS script)
        double vhsStretchMod = 0.0;
        if (variance > 0.3) // Only when variance is high enough to enable VHS mode
        {
            double stretchBase = sin(variancePhase * 0.1); // Very slow stretch cycles
            if (stretchBase > 0.7) // Only on high peaks (less frequent than your original 0.5)
            {
                vhsStretchMod = -stretchBase * stretchBase * variance * 0.3; // Pitch drops
            }
        }
        
        // Combine all modulations
        double totalMod = wowMod + flutterMod + driftMod + varianceMod + vhsStretchMod;
        
        // **CRITICAL FIX 1**: Remove the compression that was killing your effect!
        // Your original code was compressing extreme values, making everything weak
        // if (totalMod > 0.5) totalMod = 0.5 + (totalMod - 0.5) * 0.7; // REMOVED
        // if (totalMod < -0.5) totalMod = -0.5 + (totalMod + 0.5) * 0.7; // REMOVED
        
        // **CRITICAL FIX 2**: Much stronger delay modulation scaling
        // Your original: totalMod * 10.0 * srScale was too weak
        double delayModSamples = totalMod * 35.0 * srScale;  // INCREASED from 10.0 to 35.0
        
        // Base delay with sample rate scaling
        double baseDelay = 8.0 * srScale;
        double targetDelay = baseDelay + delayModSamples;
        
        // Clamp to safe range
        targetDelay = jlimit(2.0, double(delaySize - 10), targetDelay);
        
        // Process both channels with enhanced stereo character
        for (int ch = 0; ch < 2; ++ch)
        {
            // **CRITICAL FIX 3**: Much faster delay smoothing for audible modulation
            // Your original: 0.015 was too slow, making modulation inaudible
            smoothedDelay[ch] += (targetDelay - smoothedDelay[ch]) * 0.06;  // INCREASED from 0.015 to 0.06
            
            // **SIMPLE FIX**: Much smaller, safer stereo offset
            double channelDelay = smoothedDelay[ch];
            if (ch == 1)
            {
                // Right channel gets subtle offset - reduced from 1.5 to 0.3 for stability
                channelDelay += (sin(wowPhase * 0.7) + sin(variancePhase * 0.3)) * 0.3;
            }
            
            // Apply anti-aliasing filter to modulation
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
            
            // **SIMPLE LINEAR INTERPOLATION**: Skip complex sinc for stability
            int idx = int(readPos);
            double frac = readPos - double(idx);
            
            int idx1 = idx % delaySize;
            int idx2 = (idx + 1) % delaySize;
            
            double y1 = double(delayBuffer[ch][idx1]);
            double y2 = double(delayBuffer[ch][idx2]);
            
            double delayedSample = y1 + frac * (y2 - y1);
            
            // Output sample with proper float casting
            data[ch] = float(delayedSample);
            
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
        if (P == 0)      // Wow Depth
        {
            // **CRITICAL FIX 5**: Scale depth parameters to be more effective
            wowDepth = v * 2.0; // INCREASED from v to v * 2.0 for stronger effect
        }
        else if (P == 1) // Wow Rate - direct Hz input
        {
            wowRate = v; // Direct Hz value (0.1 to 10.0 Hz)
        }
        else if (P == 2) // Flutter Depth
        {
            // **CRITICAL FIX 6**: Scale flutter depth for more effect
            flutterDepth = v * 1.5; // INCREASED from v to v * 1.5 for stronger effect
        }
        else if (P == 3) // Flutter Rate - direct Hz input
        {
            flutterRate = v; // Direct Hz value (1.0 to 40.0 Hz)
        }
        else if (P == 4) // Variance
        {
            variance = v;
        }
        else if (P == 5) // Drift
        {
            drift = v;
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("Wow Depth", { 0.0, 1.0 });
            registerCallback<0>(p);
            p.setDefaultValue(0.3); // INCREASED from 0.2 - more audible starting point
            data.add(std::move(p));
        }
        {
            parameter::data p("Wow Rate", { 0.1, 10.0 }); // Display actual Hz values
            registerCallback<1>(p);
            p.setDefaultValue(1.2); // Slightly lower for more obvious wow
            data.add(std::move(p));
        }
        {
            parameter::data p("Flutter Depth", { 0.0, 1.0 });
            registerCallback<2>(p);
            p.setDefaultValue(0.25); // INCREASED from 0.15 - more audible flutter
            data.add(std::move(p));
        }
        {
            parameter::data p("Flutter Rate", { 1.0, 40.0 }); // Display actual Hz values
            registerCallback<3>(p);
            p.setDefaultValue(6.5); // Lowered to more audible range
            data.add(std::move(p));
        }
        {
            parameter::data p("Variance", { 0.0, 1.0 });
            registerCallback<4>(p);
            p.setDefaultValue(0.15); // INCREASED from 0.1 - more irregularities
            data.add(std::move(p));
        }
        {
            parameter::data p("Drift", { 0.0, 1.0 });
            registerCallback<5>(p);
            p.setDefaultValue(0.08); // INCREASED from 0.05 - more noticeable drift
            data.add(std::move(p));
        }
    }
    
private:
    static constexpr int delaySize = 512;
    
    double sampleRate;
    double srScale;  // Sample rate scaling factor
    
    // High precision phase accumulators
    double wowPhase;
    double wowPhase2;     // Second wow oscillator for organic movement
    double flutterPhase;
    double flutterPhase2; // Second flutter oscillator for character
    double driftPhase;    // Chowdhury-style long-term drift
    double variancePhase; // Chowdhury-style random irregularities
    
    // Delay buffers and indices
    float delayBuffer[2][delaySize];
    int writeIndex[2];
    
    // Anti-aliasing and smoothing
    double smoothedDelay[2];      // Smoothed delay values per channel
    double modFilter1[2];         // First pole of anti-aliasing filter
    double modFilter2[2];         // Second pole of anti-aliasing filter
    double modFilterCoeff;        // Filter coefficient
    
    // Parameters
    double wowDepth;
    double wowRate;
    double flutterDepth;
    double flutterRate;
    double variance;      // Chowdhury's variance parameter
    double drift;         // Chowdhury's drift parameter
};
}

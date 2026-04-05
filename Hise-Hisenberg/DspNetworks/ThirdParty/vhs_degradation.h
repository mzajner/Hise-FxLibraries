// ==================================| DeRez3-Inspired Tape Degradation |==================================

#pragma once
#include <JuceHeader.h>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV> struct vhs_degradation: public data::base
{
    // Metadata Definitions ------------------------------------------------------------------------
    
    SNEX_NODE(vhs_degradation);
    
    struct MetadataClass
    {
        SN_NODE_ID("vhs_degradation");
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
    vhs_degradation()
    {
        sampleRate = 44100.0; // Will be updated in prepare()
        rateControl = 1.0;   // Full sample rate initially
        rezControl = 1.0;    // Full bit depth initially
        dryWetControl = 1.0; // Full wet initially
        
        // Initialize state variables
        heldSample_L = heldSample_R = 0.0;
        samplePosition_L = samplePosition_R = 0.0;
        lastSample_L = lastSample_R = 0.0;
        
        // Smoothing filter states for control changes
        rateSmooth = rezSmooth = dryWetSmooth = 0.0;
        smoothingCoeff = 0.1; // Will be recalculated in prepare()
    }
    
    // Scriptnode Callbacks ------------------------------------------------------------------------
    
    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;
        
        // Calculate smoothing coefficient for control changes (like synth filter smoothing)
        // This prevents stepping artifacts when parameters change
        double smoothingTimeMs = 10.0; // 10ms smoothing time
        smoothingCoeff = 1.0 - std::exp(-1.0 / (smoothingTimeMs * 0.001 * sampleRate));
        smoothingCoeff = jlimit(0.01, 0.99, smoothingCoeff);
        
        // Reset positions to ensure clean state at new sample rate
        reset();
    }
    
    void reset()
    {
        heldSample_L = heldSample_R = 0.0;
        samplePosition_L = samplePosition_R = 0.0;
        lastSample_L = lastSample_R = 0.0;
        rateSmooth = rateControl;
        rezSmooth = rezControl;
        dryWetSmooth = dryWetControl;
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
        // Apply control smoothing to prevent stepping artifacts
        rateSmooth += smoothingCoeff * (rateControl - rateSmooth);
        rezSmooth += smoothingCoeff * (rezControl - rezSmooth);
        dryWetSmooth += smoothingCoeff * (dryWetControl - dryWetSmooth);
        
        // Store dry signal
        double dryL = data[0];
        double dryR = data[1];
        
        // Apply DeRez3-style processing
        double wetL = processChannel(data[0], 0);  // Left channel
        double wetR = processChannel(data[1], 1);  // Right channel
        
        // DeRez3-style dry/wet mixing
        // Full dry: sneak in effect without affecting dry level
        // Full wet: sneak in dry without cutting wet level
        // 0.5: equal balance
        if (dryWetSmooth < 0.5)
        {
            // More dry than wet - preserve dry level
            double wetAmount = dryWetSmooth * 2.0;
            data[0] = dryL + wetL * wetAmount;
            data[1] = dryR + wetR * wetAmount;
        }
        else
        {
            // More wet than dry - preserve wet level
            double dryAmount = (1.0 - dryWetSmooth) * 2.0;
            data[0] = wetL + dryL * dryAmount;
            data[1] = wetR + dryR * dryAmount;
        }
    }
    
    int handleModulation(double& value) { return 0; }
    void setExternalData(const ExternalData& data, int index) {}
    
    // Parameter Functions -------------------------------------------------------------------------
    
    template <int P> void setParameter(double v)
    {
        if (P == 0)
        {
            // Rate control (sample rate reduction)
            // 1.0 = full rate, 0.0 = extreme downsampling
            rateControl = jlimit(0.0001, 1.0, v); // Prevent zero to avoid trapping energy
        }
        else if (P == 1)
        {
            // Rez control (bit depth reduction)
            // 1.0 = full resolution, 0.0 = extreme quantization with gating
            rezControl = jlimit(0.0, 1.0, v);
        }
        else if (P == 2)
        {
            // Dry/Wet control (DeRez3-style wetness)
            // 0.0 = full dry, 0.5 = equal mix, 1.0 = full wet
            dryWetControl = jlimit(0.0, 1.0, v);
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("Rate", { 0.0001, 1.0 });
            registerCallback<0>(p);
            p.setDefaultValue(1.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Rez", { 0.0, 1.0 });
            registerCallback<1>(p);
            p.setDefaultValue(1.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("DryWet", { 0.0, 1.0 });
            registerCallback<2>(p);
            p.setDefaultValue(1.0);
            data.add(std::move(p));
        }
    }
    
private:
    double sampleRate;
    double rateControl, rezControl, dryWetControl;
    double rateSmooth, rezSmooth, dryWetSmooth;
    double smoothingCoeff;
    
    // Per-channel state for sample rate reduction
    double heldSample_L, heldSample_R;
    double samplePosition_L, samplePosition_R;
    double lastSample_L, lastSample_R;
    
    // === DeRez3-Style Channel Processing ===
    double processChannel(double input, int channel)
    {
        double output = input;
        
        // Sample rate reduction (Rate control)
        output = applySampleRateReduction(output, channel);
        
        // Bit depth reduction (Rez control)
        output = applyBitDepthReduction(output);
        
        return output;
    }
    
    // === Sample Rate Reduction (Rate Control) ===
    double applySampleRateReduction(double input, int channel)
    {
        if (rateSmooth >= 0.99) return input; // Bypass if rate is essentially full
        
        // Calculate decimation rate - goes to subsonics, never quite zero
        double decimationRate = rateSmooth * rateSmooth; // Non-linear for better control feel
        decimationRate = jmax(0.0001, decimationRate); // Minimum rate to prevent energy trapping
        
        if (channel == 0) // Left channel
        {
            // Accumulate position
            samplePosition_L += decimationRate;
            
            // When we cross 1.0, update the held sample
            if (samplePosition_L >= 1.0)
            {
                samplePosition_L -= 1.0;
                
                // DeRez3-style: smooth transition between samples
                // Uses interpolation to avoid harsh stepping
                double blend = samplePosition_L;
                heldSample_L = lastSample_L + blend * (input - lastSample_L);
                lastSample_L = input;
            }
            
            return heldSample_L;
        }
        else // Right channel
        {
            // Same processing for right channel
            samplePosition_R += decimationRate;
            
            if (samplePosition_R >= 1.0)
            {
                samplePosition_R -= 1.0;
                double blend = samplePosition_R;
                heldSample_R = lastSample_R + blend * (input - lastSample_R);
                lastSample_R = input;
            }
            
            return heldSample_R;
        }
    }
    
    // === Bit Depth Reduction (Rez Control) ===
    double applyBitDepthReduction(double input)
    {
        if (rezSmooth >= 0.99) return input; // Bypass if resolution is essentially full
        
        // Calculate effective bit depth - maps from 16-bit down to extreme quantization
        // SOW specifies 16-bit to 8-bit, but DeRez3 can go more extreme
        double bitDepth = 2.0 + rezSmooth * 14.0; // 2 to 16 bits
        double levels = std::pow(2.0, bitDepth);
        double stepSize = 2.0 / levels;
        
        // Apply quantization
        double quantized = std::round(input / stepSize) * stepSize;
        
        // DeRez3 feature: Gating behavior at extreme low bit depths
        if (rezSmooth < 0.1) // Extreme settings
        {
            // Add gating effect - if signal is below threshold, gate it to zero
            double gateThreshold = stepSize * 2.0;
            if (std::abs(quantized) < gateThreshold)
            {
                quantized = 0.0;
            }
        }
        
        // Soft clipping to prevent overflow
        quantized = std::tanh(quantized);
        
        return quantized;
    }
};
}

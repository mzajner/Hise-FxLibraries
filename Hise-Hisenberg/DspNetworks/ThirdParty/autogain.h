// ==================================| Zero-Latency Autogain Module |==================================
//
// Purpose: True zero-latency output level control (no analysis, no delay)
// Features:
//   - Static gain compensation (exactly like soft_clip.h pattern)
//   - Absolutely zero latency - no sample delay whatsoever
//   - Optional auto-compensation toggle
//   - Minimal CPU usage
//
// Usage: Place at end of chain for output level management
// This is NOT adaptive - it's just clean gain staging with optional compensation
//
// ==================================================================================================

#pragma once
#include <JuceHeader.h>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV> struct autogain : public data::base
{
    SNEX_NODE(autogain);
    
    struct MetadataClass
    {
        SN_NODE_ID("autogain");
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
    
    autogain()
    : leftEffect(0.0f, 0.0f, true),
    rightEffect(0.0f, 0.0f, true)
    {
    }
    
    void prepare(PrepareSpecs specs)
    {
        leftEffect.prepare(specs.sampleRate);
        rightEffect.prepare(specs.sampleRate);
    }
    
    void reset()
    {
    }
    
    void handleHiseEvent(HiseEvent& e)
    {
    }
    
    template <typename T> void process(T& data)
    {
        static constexpr int NumChannels = getFixChannelAmount();
        auto& fixData = data.template as<ProcessData<NumChannels>>();
        
        // Convert to AudioBlock (HISE API)
        auto audioBlock = fixData.toAudioBlock();
        int numSamples = data.getNumSamples();
        
        // Process left and right channels separately
        leftEffect.processBlock(audioBlock.getChannelPointer(0), numSamples);
        rightEffect.processBlock(audioBlock.getChannelPointer(1), numSamples);
    }
    
    template <typename T> void processFrame(T& data)
    {
    }
    
    int handleModulation(double& value)
    {
        return 0;
    }
    
    void setExternalData(const ExternalData& data, int index)
    {
    }
    
    template <int P> void setParameter(double v)
    {
        if (P == 0)
        {
            // Input Gain (dB)
            leftEffect.setInputGain(static_cast<float>(v));
            rightEffect.setInputGain(static_cast<float>(v));
        }
        else if (P == 1)
        {
            // Auto Compensation toggle
            bool enabled = (v >= 0.5);
            leftEffect.setAutoCompensation(enabled);
            rightEffect.setAutoCompensation(enabled);
        }
        else if (P == 2)
        {
            // Output Trim (dB)
            leftEffect.setOutputGain(static_cast<float>(v));
            rightEffect.setOutputGain(static_cast<float>(v));
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            // Parameter 0: Input Gain
            // This simulates the gain change from previous processing
            parameter::data p("Input Gain (dB)", { -24.0, 24.0 });
            registerCallback<0>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        {
            // Parameter 1: Auto Compensation
            // When ON: inverts input gain, then applies trim
            // When OFF: just applies trim
            parameter::data p("Auto Compensation", { 0.0, 1.0, 1.0 });
            registerCallback<1>(p);
            p.setDefaultValue(1.0);
            data.add(std::move(p));
        }
        {
            // Parameter 2: Output Trim
            // Fine-tune output level
            parameter::data p("Output Trim (dB)", { -20.0, 20.0 });
            registerCallback<2>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
    }
    
private:
    // AudioEffect class - exactly like soft_clip.h pattern
    class AudioEffect
    {
    public:
        AudioEffect(float inputGain_dB_, float outputGain_dB_, bool autoComp_)
        : inputGain_dB(inputGain_dB_),
        outputGain_dB(outputGain_dB_),
        autoCompensation(autoComp_),
        m_sampleRate(48000.0)
        {
            updateParams();
        }
        
        void prepare(double sr)
        {
            m_sampleRate = sr;
        }
        
        inline void processBlock(float* samples, int numSamples)
        {
            // Apply input gain
            FloatVectorOperations::multiply(samples, samples, m_inGain, numSamples);
            
            // Apply output gain (with compensation if enabled)
            FloatVectorOperations::multiply(samples, samples, m_outGain, numSamples);
        }
        
        inline void setInputGain(float v)
        {
            inputGain_dB = v;
            updateParams();
        }
        
        inline void setOutputGain(float v)
        {
            outputGain_dB = v;
            updateParams();
        }
        
        inline void setAutoCompensation(bool en)
        {
            autoCompensation = en;
            updateParams();
        }
        
    private:
        float inputGain_dB, outputGain_dB;
        bool autoCompensation;
        float m_inGain, m_outGain;
        double m_sampleRate;
        
        inline void updateParams()
        {
            // Convert input gain from dB to linear
            m_inGain = std::pow(10.0f, inputGain_dB / 20.0f);
            
            // Calculate output gain
            // If auto-compensation ON: invert input gain, then apply trim
            // If auto-compensation OFF: just apply trim
            m_outGain = autoCompensation
            ? std::pow(10.0f, -inputGain_dB / 20.0f) * std::pow(10.0f, outputGain_dB / 20.0f)
            : std::pow(10.0f, outputGain_dB / 20.0f);
        }
    };
    
    AudioEffect leftEffect, rightEffect;
};

} // namespace project

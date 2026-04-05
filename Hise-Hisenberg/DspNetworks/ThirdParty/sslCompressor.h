#pragma once
#include <JuceHeader.h>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV> struct sslCompressor: public data::base
{
    SNEX_NODE(sslCompressor);
    
    struct MetadataClass
    {
        SN_NODE_ID("sslCompressor");
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
    
    // SSL Compressor Variables
    float threshold = 0.0f;
    float ratio = 4.0f;
    float attack = 1.0f;
    float release = 2.0f;
    float makeup = 0.0f;
    float intensity = 0.0f;
    
    float sampleRate = 44100.0f;
    float envelope = 0.0f;
    float attack_coeff = 0.99f;
    float release_coeff = 0.999f;
    float vca_envelope = 0.0f;
    
    void prepare(PrepareSpecs specs)
    {
        sampleRate = static_cast<float>(specs.sampleRate);
        updateSSLTiming();
        envelope = 0.0f;
        vca_envelope = 0.0f;
    }
    
    void updateSSLTiming()
    {
        float attack_time = (attack < 0.5f) ? 0.0003f : 0.003f;
        float release_time;
        if (release < 0.33f) {
            release_time = 0.1f;
        } else if (release < 0.66f) {
            release_time = 0.3f;
        } else {
            release_time = 0.2f;
        }
        
        attack_coeff = std::exp(-1.0f / (attack_time * sampleRate));
        release_coeff = std::exp(-1.0f / (release_time * sampleRate));
    }
    
    float processVCASaturation(float input, float gainReduction)
    {
        float intensityScale = 1.0f + (intensity * 2.0f);  // Scale harmonics with intensity
        
        float drive = 1.0f + (gainReduction * 0.15f * intensityScale);
        float driven = input * drive;
        
        float saturated = std::tanh(driven * 1.2f);
        float harmonic2nd = driven * driven * (0.08f * intensityScale);
        float harmonic3rd = driven * driven * driven * (0.02f * intensityScale);
        float blend = gainReduction * (0.4f * intensityScale);
        
        return input * (1.0f - blend) + (saturated + harmonic2nd + harmonic3rd) * blend;
    }
    
    void reset()
    {
        envelope = 0.0f;
        vca_envelope = 0.0f;
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
        updateSSLTiming();
        
        float left = data[0];
        float right = data[1];
        
        // Input gain staging based on intensity
        float inputGain = 1.0f + (intensity * 2.0f);  // Up to 3x input gain at max intensity
        left *= inputGain;
        right *= inputGain;
        
        float peak = std::max(std::abs(left), std::abs(right));
        
        float target = peak;
        float coeff = (target > envelope) ? attack_coeff : release_coeff;
        envelope = envelope * coeff + target * (1.0f - coeff);
        
        float envelope_db = 20.0f * std::log10(std::max(envelope, 1e-10f));
        float over_threshold = std::max(0.0f, envelope_db - threshold);
        float gain_reduction_db = over_threshold * (1.0f - (1.0f / ratio));
        
        float auto_makeup = threshold * -0.3f;
        float total_gain_db = -gain_reduction_db + makeup + auto_makeup;
        float gain = juce::Decibels::decibelsToGain(total_gain_db);
        
        float compressed_left = left * gain;
        float compressed_right = right * gain;
        
        float normalized_gr = gain_reduction_db / 20.0f;
        compressed_left = processVCASaturation(compressed_left, normalized_gr);
        compressed_right = processVCASaturation(compressed_right, normalized_gr);
        
        data[0] = compressed_left;
        data[1] = compressed_right;
    }
    
    int handleModulation(double& value) { return 0; }
    void setExternalData(const ExternalData& data, int index) {}
    
    template <int P> void setParameter(double v)
    {
        if (P == 0) threshold = static_cast<float>(v);
        else if (P == 1) ratio = static_cast<float>(v);
        else if (P == 2) attack = static_cast<float>(v);
        else if (P == 3) release = static_cast<float>(v);
        else if (P == 4) makeup = static_cast<float>(v);
        else if (P == 5) intensity = static_cast<float>(v);  // New intensity parameter
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("Threshold", { -15.0, 15.0 });
            registerCallback<0>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Ratio", { 2.0, 10.0 });
            registerCallback<1>(p);
            p.setDefaultValue(4.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Attack", { 0.0, 1.0 });
            registerCallback<2>(p);
            p.setDefaultValue(1.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Release", { 0.0, 2.0 });
            registerCallback<3>(p);
            p.setDefaultValue(2.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Makeup", { 0.0, 20.0 });
            registerCallback<4>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Intensity", { 0.0, 1.0 });
            registerCallback<5>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
    }
};
}

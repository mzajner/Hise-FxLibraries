// ==================================| Butterworth 2nd Order HPF |==================================

#pragma once
#include <JuceHeader.h>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV> struct Butterworth2ndHpf: public data::base
{
    SNEX_NODE(Butterworth2ndHpf);
    
    struct MetadataClass
    {
        SN_NODE_ID("Butterworth2ndHpf");
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
    
    Butterworth2ndHpf()
    {
        cutoff = 60.0f;
        sampleRate = 44100.0;
        reset();
        updateCoefficients();
    }
    
    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;
        updateCoefficients();
    }
    
    void reset()
    {
        for (int ch = 0; ch < 2; ++ch)
        {
            x1[ch] = x2[ch] = y1[ch] = y2[ch] = 0.0f;
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
        // Process both channels
        data[0] = processChannel(data[0], 0);
        data[1] = processChannel(data[1], 1);
    }
    
    float processChannel(float input, int channel)
    {
        // Butterworth 12dB/oct HPF (2-pole, Q=0.707)
        float output = b0 * input + b1 * x1[channel] + b2 * x2[channel]
        - a1 * y1[channel] - a2 * y2[channel];
        
        x2[channel] = x1[channel];
        x1[channel] = input;
        y2[channel] = y1[channel];
        y1[channel] = output;
        
        return output;
    }
    
    int handleModulation(double& value) { return 0; }
    
    void setExternalData(const ExternalData& data, int index) {}
    
    template <int P> void setParameter(double v)
    {
        if (P == 0)
        {
            cutoff = (float)v;
            updateCoefficients();
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("Frequency", { 20.0, 500.0, 1.0 });
            registerCallback<0>(p);
            p.setDefaultValue(60.0);
            data.add(std::move(p));
        }
    }
    
private:
    void updateCoefficients()
    {
        float omega = 2.0f * M_PI * cutoff / sampleRate;
        float cosw = std::cos(omega);
        float sinw = std::sin(omega);
        float alpha = sinw / (2.0f * 0.707f); // Q = 0.707 for Butterworth
        
        float a0 = 1.0f + alpha;
        b0 = ((1.0f + cosw) / 2.0f) / a0;
        b1 = (-(1.0f + cosw)) / a0;
        b2 = ((1.0f + cosw) / 2.0f) / a0;
        a1 = (-2.0f * cosw) / a0;
        a2 = (1.0f - alpha) / a0;
    }
    
    float cutoff;
    double sampleRate;
    
    // Biquad coefficients
    float b0, b1, b2, a1, a2;
    
    // Per-channel state
    float x1[2], x2[2];  // Input history
    float y1[2], y2[2];  // Output history
};
}

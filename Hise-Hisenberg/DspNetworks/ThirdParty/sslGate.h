#pragma once
#include <JuceHeader.h>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV>
struct sslGate : public data::base
{
    SNEX_NODE(sslGate);
    struct MetadataClass { SN_NODE_ID("sslGate"); };
    
    sslGate()
    {
        threshold = -40.0f;
        range = 60.0f;
        attack = 0.3f;
        hold = 5.0f;
        release = 100.0f;
        sidechain_hpf_freq = 80.0f;
        sidechain_lpf_freq = 8000.0f;
        frequency_dependent = false;
        
        sampleRate = 44100.0;
        
        for (int ch = 0; ch < 2; ++ch)
        {
            envelope[ch] = 0.0f;
            holdCounter[ch] = 0;
            smoothGain[ch] = 1.0f;
            gateOpen[ch] = true;
            hpf_x1[ch] = hpf_x2[ch] = hpf_y1[ch] = hpf_y2[ch] = 0.0f;
            lpf_x1[ch] = lpf_x2[ch] = lpf_y1[ch] = lpf_y2[ch] = 0.0f;
        }
        
        updateCoefficients();
    }
    
    static constexpr bool isModNode() { return false; }
    static constexpr bool isPolyphonic() { return NV > 1; }
    static constexpr bool hasTail() { return false; }
    static constexpr bool isSuspendedOnSilence() { return false; }
    static constexpr int getFixChannelAmount() { return 2; }
    static constexpr int NumTables = 0;
    static constexpr int NumSliderPacks = 0;
    static constexpr int NumAudioFiles = 0;
    static constexpr int NumFilters = 0;
    static constexpr int NumDisplayBuffers = 0;
    
    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;
        updateCoefficients();
    }
    
    void reset()
    {
        for (int ch = 0; ch < 2; ++ch)
        {
            envelope[ch] = 0.0f;
            holdCounter[ch] = 0;
            smoothGain[ch] = 1.0f;
            gateOpen[ch] = true;
            hpf_x1[ch] = hpf_x2[ch] = hpf_y1[ch] = hpf_y2[ch] = 0.0f;
            lpf_x1[ch] = lpf_x2[ch] = lpf_y1[ch] = lpf_y2[ch] = 0.0f;
        }
    }
    
    void handleHiseEvent(HiseEvent& e) {}
    
    template <typename T> void process(T& data)
    {
        static constexpr int NumChannels = getFixChannelAmount();
        auto& fixData = data.template as<ProcessData<NumChannels>>();
        auto audioBlock = fixData.toAudioBlock();
        int numSamples = data.getNumSamples();
        
        float* leftChannel = audioBlock.getChannelPointer(0);
        float* rightChannel = audioBlock.getChannelPointer(1);
        
        for (int i = 0; i < numSamples; ++i)
        {
            leftChannel[i] = processChannel(leftChannel[i], 0);
            rightChannel[i] = processChannel(rightChannel[i], 1);
        }
    }
    
    template <typename T> void processFrame(T& data) {}
    
    float processChannel(float input, int channel)
    {
        if (threshold < -70.0f) return input;
        
        float sidechain = input;
        if (frequency_dependent)
        {
            sidechain = processBiquadHPF(sidechain, channel);
            sidechain = processBiquadLPF(sidechain, channel);
        }
        
        float absLevel = std::abs(sidechain);
        float& env = envelope[channel];
        int& holdCount = holdCounter[channel];
        
        if (absLevel > env)
        {
            env += attack_coeff * (absLevel - env);
            holdCount = hold_samples;
        }
        else if (holdCount > 0)
        {
            holdCount--;
        }
        else
        {
            env += release_coeff * (absLevel - env);
        }
        
        float env_db = 20.0f * std::log10(std::max(env, 1e-10f));
        
        bool& isOpen = gateOpen[channel];
        float hysteresis_db = 3.0f;
        float openThreshold = threshold;
        float closeThreshold = threshold - hysteresis_db;
        
        if (env_db > openThreshold)
            isOpen = true;
        else if (env_db < closeThreshold)
            isOpen = false;
        
        float targetGain = isOpen ? 1.0f : juce::Decibels::decibelsToGain(-range);
        
        float& smooth = smoothGain[channel];
        float smoothCoeff = isOpen ? attack_smooth_coeff : release_smooth_coeff;
        smooth += smoothCoeff * (targetGain - smooth);
        
        return input * smooth;
    }
    
    float processBiquadHPF(float input, int channel)
    {
        float output = hpf_b0 * input + hpf_b1 * hpf_x1[channel] + hpf_b2 * hpf_x2[channel]
        - hpf_a1 * hpf_y1[channel] - hpf_a2 * hpf_y2[channel];
        
        hpf_x2[channel] = hpf_x1[channel];
        hpf_x1[channel] = input;
        hpf_y2[channel] = hpf_y1[channel];
        hpf_y1[channel] = output;
        
        return output;
    }
    
    float processBiquadLPF(float input, int channel)
    {
        float output = lpf_b0 * input + lpf_b1 * lpf_x1[channel] + lpf_b2 * lpf_x2[channel]
        - lpf_a1 * lpf_y1[channel] - lpf_a2 * lpf_y2[channel];
        
        lpf_x2[channel] = lpf_x1[channel];
        lpf_x1[channel] = input;
        lpf_y2[channel] = lpf_y1[channel];
        lpf_y1[channel] = output;
        
        return output;
    }
    
    int handleModulation(double& value) { return 0; }
    void setExternalData(const ExternalData& data, int index) {}
    
    template <int P>
    void setParameter(double v)
    {
        if (P == 0)
        {
            threshold = (float)v;
        }
        else if (P == 1)
        {
            range = (float)v;
        }
        else if (P == 2)
        {
            attack = (float)v;
            updateCoefficients();
        }
        else if (P == 3)
        {
            hold = (float)v;
            updateCoefficients();
        }
        else if (P == 4)
        {
            release = (float)v;
            updateCoefficients();
        }
        else if (P == 5)
        {
            sidechain_hpf_freq = (float)v;
            updateFilterCoefficients();
        }
        else if (P == 6)
        {
            sidechain_lpf_freq = (float)v;
            updateFilterCoefficients();
        }
        else if (P == 7)
        {
            frequency_dependent = v >= 0.5;
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("Threshold", { -80.0, 0.0, 0.1 });
            registerCallback<0>(p);
            p.setDefaultValue(-40.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Range", { 0.0, 80.0, 0.1 });
            registerCallback<1>(p);
            p.setDefaultValue(60.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Attack", { 0.1, 10.0, 0.1 });
            registerCallback<2>(p);
            p.setDefaultValue(0.3);
            data.add(std::move(p));
        }
        {
            parameter::data p("Hold", { 0.0, 100.0, 1.0 });
            registerCallback<3>(p);
            p.setDefaultValue(5.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Release", { 10.0, 1000.0, 1.0 });
            registerCallback<4>(p);
            p.setDefaultValue(100.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("SC HPF Freq", { 20.0, 500.0, 1.0 });
            registerCallback<5>(p);
            p.setDefaultValue(80.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("SC LPF Freq", { 1000.0, 20000.0, 1.0 });
            registerCallback<6>(p);
            p.setDefaultValue(8000.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Freq Dependent", { 0.0, 1.0, 1.0 });
            registerCallback<7>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
    }
    
private:
    float threshold, range, attack, hold, release;
    float sidechain_hpf_freq, sidechain_lpf_freq;
    bool frequency_dependent;
    double sampleRate;
    
    float attack_coeff, release_coeff;
    float attack_smooth_coeff, release_smooth_coeff;
    int hold_samples;
    
    float envelope[2];
    int holdCounter[2];
    float smoothGain[2];
    bool gateOpen[2];
    
    float hpf_b0, hpf_b1, hpf_b2, hpf_a1, hpf_a2;
    float lpf_b0, lpf_b1, lpf_b2, lpf_a1, lpf_a2;
    float hpf_x1[2], hpf_x2[2], hpf_y1[2], hpf_y2[2];
    float lpf_x1[2], lpf_x2[2], lpf_y1[2], lpf_y2[2];
    
    void updateCoefficients()
    {
        attack_coeff = 1.0f - std::exp(-1.0f / (attack * 0.001f * sampleRate));
        release_coeff = 1.0f - std::exp(-1.0f / (release * 0.001f * sampleRate));
        hold_samples = static_cast<int>(hold * 0.001f * sampleRate);
        
        float attack_smooth_time = std::max(attack * 2.0f, 3.0f);
        float release_smooth_time = std::max(release * 0.5f, 10.0f);
        
        attack_smooth_coeff = 1.0f - std::exp(-1.0f / (attack_smooth_time * 0.001f * sampleRate));
        release_smooth_coeff = 1.0f - std::exp(-1.0f / (release_smooth_time * 0.001f * sampleRate));
        
        updateFilterCoefficients();
    }
    
    void updateFilterCoefficients()
    {
        float omega_hpf = 2.0f * M_PI * sidechain_hpf_freq / sampleRate;
        float cosw_hpf = std::cos(omega_hpf);
        float sinw_hpf = std::sin(omega_hpf);
        float alpha_hpf = sinw_hpf / (2.0f * 0.707f);
        
        float b0_temp = (1.0f + cosw_hpf) / 2.0f;
        float b1_temp = -(1.0f + cosw_hpf);
        float b2_temp = (1.0f + cosw_hpf) / 2.0f;
        float a0_temp = 1.0f + alpha_hpf;
        float a1_temp = -2.0f * cosw_hpf;
        float a2_temp = 1.0f - alpha_hpf;
        
        hpf_b0 = b0_temp / a0_temp;
        hpf_b1 = b1_temp / a0_temp;
        hpf_b2 = b2_temp / a0_temp;
        hpf_a1 = a1_temp / a0_temp;
        hpf_a2 = a2_temp / a0_temp;
        
        float omega_lpf = 2.0f * M_PI * sidechain_lpf_freq / sampleRate;
        float cosw_lpf = std::cos(omega_lpf);
        float sinw_lpf = std::sin(omega_lpf);
        float alpha_lpf = sinw_lpf / (2.0f * 0.707f);
        
        b0_temp = (1.0f - cosw_lpf) / 2.0f;
        b1_temp = 1.0f - cosw_lpf;
        b2_temp = (1.0f - cosw_lpf) / 2.0f;
        a0_temp = 1.0f + alpha_lpf;
        a1_temp = -2.0f * cosw_lpf;
        a2_temp = 1.0f - alpha_lpf;
        
        lpf_b0 = b0_temp / a0_temp;
        lpf_b1 = b1_temp / a0_temp;
        lpf_b2 = b2_temp / a0_temp;
        lpf_a1 = a1_temp / a0_temp;
        lpf_a2 = a2_temp / a0_temp;
    }
};
}

#pragma once

#include <JuceHeader.h>
#include "src/Aspik/aspik.h"

/*
 ==========================| ASPIK Allpass Filter HISE Node |==========================
 
 Allpass filters provide phase shifting without amplitude change.
 - APF1: 1st-order allpass - simple phase delay with smooth response
 - APF2: 2nd-order allpass - more complex phase relationships for effects
 - Essential for reverb, phasing effects, and delay line applications
 
 Based on Will Pirkle's "Designing Audio Effect Plugins in C++" APF1 and APF2 algorithms.
 */

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;
using namespace aspik;

template <int NV> struct AspikFilterAllpass : public data::base
{
    SNEX_NODE(AspikFilterAllpass);
    
    struct MetadataClass
    {
        SN_NODE_ID("AspikFilterAllpass");
    };
    
    static constexpr bool isModNode() { return false; };
    static constexpr bool isPolyphonic() { return NV > 1; };
    static constexpr bool hasTail() { return false; };
    static constexpr bool isSuspendedOnSilence() { return true; };
    static constexpr int getFixChannelAmount() { return 2; };
    
    static constexpr int NumTables = 0;
    static constexpr int NumSliderPacks = 0;
    static constexpr int NumAudioFiles = 0;
    static constexpr int NumFilters = 0;
    static constexpr int NumDisplayBuffers = 0;
    
    aspik::AudioFilter leftFilter;
    aspik::AudioFilter rightFilter;
    
    double sampleRate = 44100.0;
    double frequency = 1000.0;
    int filterType = 0;
    
    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;
        leftFilter.reset(specs.sampleRate);
        rightFilter.reset(specs.sampleRate);
        updateFilterParameters();
    }
    
    void reset()
    {
        leftFilter.reset(sampleRate);
        rightFilter.reset(sampleRate);
    }
    
    void handleHiseEvent(HiseEvent& e) {}
    
    template <typename T> void process(T& data)
    {
        static constexpr int NumChannels = getFixChannelAmount();
        auto& fixData = data.template as<ProcessData<NumChannels>>();
        auto fd = fixData.toFrameData();
        
        while (fd.next())
        {
            processFrame(fd.toSpan());
        }
    }
    
    template <typename T> void processFrame(T& data)
    {
        data[0] = static_cast<float>(leftFilter.processAudioSample(static_cast<double>(data[0])));
        
        if (getFixChannelAmount() > 1)
        {
            data[1] = static_cast<float>(rightFilter.processAudioSample(static_cast<double>(data[1])));
        }
    }
    
    int handleModulation(double& value)
    {
        return 0;
    }
    
    template <int P> void setParameter(double v)
    {
        if (P == 0)
        {
            double newFreq = jlimit(20.0, 20000.0, v);
            if (frequency != newFreq)
            {
                frequency = newFreq;
                updateFilterParameters();
            }
        }
        else if (P == 1)
        {
            int newType = jlimit(0, 1, (int)v);
            if (filterType != newType)
            {
                filterType = newType;
                updateFilterParameters();
            }
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("Frequency", { 20.0, 20000.0 });
            registerCallback<0>(p);
            p.setDefaultValue(1000.0);
            p.setSkewForCentre(1000.0);
            data.add(std::move(p));
        }
        
        {
            parameter::data p("FilterType", { 0.0, 1.0, 1.0 });
            registerCallback<1>(p);
            p.setDefaultValue(0.0);
            
            StringArray filterNames;
            filterNames.add("1 Pole");
            filterNames.add("2 Pole");
            
            p.setParameterValueNames(filterNames);
            data.add(std::move(p));
        }
    }
    
private:
    
    void updateFilterParameters()
    {
        aspik::AudioFilterParameters params;
        params.fc = frequency;
        params.Q = 0.707;
        params.boostCut_dB = 0.0;
        params.algorithm = (filterType == 0) ? aspik::filterAlgorithm::kAPF1 : aspik::filterAlgorithm::kAPF2;
        
        leftFilter.setParameters(params);
        rightFilter.setParameters(params);
    }
};

} // namespace project

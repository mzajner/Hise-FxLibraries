#pragma once

#include <JuceHeader.h>
#include "src/Aspik/aspik.h"

/*
 ==========================| ASPIK Filter Template |==========================
 
 Template for creating ASPIK-based filter nodes in HISE.
 Copy this file and modify the sections marked with TODO.
 
 Based on Will Pirkle's "Designing Audio Effect Plugins in C++"
 Uses proven AudioFilter implementations with HISE integration.
 
 NAMING CONVENTION:
 - File: AspikFilter[Category].h (e.g., AspikFilterShelf.h)
 - Struct: AspikFilter[Category] (e.g., AspikFilterShelf)
 - All filters use unified aspik namespace via #include "src/Aspik/aspik.h"
 
 PARAMETER GUIDELINES:
 - Always include Frequency (20-20000 Hz, log scale)
 - Include Q for resonant filters (0.1-10.0, linear scale)
 - Include Gain for EQ/shelf filters (-24 to +24 dB, linear scale)
 - Include Type selector for multi-algorithm filters
 
 WORKFLOW:
 1. Copy this template file
 2. Rename file and struct (search/replace AspikFilterTemplate)
 3. Define your parameters
 4. Set the appropriate aspik::filterAlgorithm in updateFilterParameters()
 */

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;
using namespace aspik;

template <int NV> struct AspikFilterTemplate : public data::base
{
    SNEX_NODE(AspikFilterTemplate);
    
    struct MetadataClass
    {
        SN_NODE_ID("AspikFilterTemplate");
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
    double q = 0.707;
    double gain = 0.0;
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
            double newQ = jlimit(0.1, 10.0, v);
            if (q != newQ)
            {
                q = newQ;
                updateFilterParameters();
            }
        }
        else if (P == 2)
        {
            double newGain = jlimit(-24.0, 24.0, v);
            if (gain != newGain)
            {
                gain = newGain;
                updateFilterParameters();
            }
        }
        else if (P == 3)
        {
            int newType = jlimit(0, 3, (int)v);
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
            parameter::data p("Q", { 0.1, 10.0 });
            registerCallback<1>(p);
            p.setDefaultValue(0.707);
            p.setSkewForCentre(1.0);
            data.add(std::move(p));
        }
        
        {
            parameter::data p("Gain", { -24.0, 24.0 });
            registerCallback<2>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        
        {
            parameter::data p("FilterType", { 0.0, 3.0, 1.0 });
            registerCallback<3>(p);
            p.setDefaultValue(0.0);
            
            StringArray filterNames;
            filterNames.add("Type A");
            filterNames.add("Type B");
            filterNames.add("Type C");
            filterNames.add("Type D");
            
            p.setParameterValueNames(filterNames);
            data.add(std::move(p));
        }
    }
    
private:
    
    void updateFilterParameters()
    {
        aspik::AudioFilterParameters params;
        params.fc = frequency;
        params.Q = q;
        params.boostCut_dB = gain;
        
        switch (filterType)
        {
            case 0: params.algorithm = aspik::filterAlgorithm::kLPF2; break;
            case 1: params.algorithm = aspik::filterAlgorithm::kHPF2; break;
            case 2: params.algorithm = aspik::filterAlgorithm::kBPF2; break;
            case 3: params.algorithm = aspik::filterAlgorithm::kBSF2; break;
            default: params.algorithm = aspik::filterAlgorithm::kLPF2; break;
        }
        
        leftFilter.setParameters(params);
        rightFilter.setParameters(params);
    }
};

} // namespace project

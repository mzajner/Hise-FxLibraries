#pragma once

#include <JuceHeader.h>
#include "src/Aspik/aspik.h"

/*
 ==========================| ASPIK Analog FIR Filter |==========================
 
 FIR filter with analog magnitude responses using frequency sampling method.
 - Uses ASPiK AnalogFIRFilter object directly
 - Creates FIR filters that match analog filter magnitude responses
 - Six filter types: LPF1, HPF1, LPF2, HPF2, BPF2, BSF2
 - Linear phase response (unlike analog counterparts)
 - CPU intensive - parameters updated once per buffer cycle
 
 Based on Will Pirkle's "Designing Audio Effect Plugins in C++" Chapter 16.11.
 */

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;
using namespace aspik;

template <int NV>
struct AspikFilterAnalogFIR : public data::base
{
    SNEX_NODE(AspikFilterAnalogFIR);
    
    struct MetadataClass
    {
        SN_NODE_ID("AspikFilterAnalogFIR");
    };
    
    static constexpr bool isModNode() { return false; }
    static constexpr bool isPolyphonic() { return NV > 1; }
    static constexpr bool hasTail() { return true; }
    static constexpr bool isSuspendedOnSilence() { return false; }
    static constexpr int getFixChannelAmount() { return 1; }
    
    static constexpr int NumTables = 0;
    static constexpr int NumSliderPacks = 0;
    static constexpr int NumAudioFiles = 0;
    static constexpr int NumFilters = 0;
    static constexpr int NumDisplayBuffers = 0;
    
    aspik::AnalogFIRFilter analogFIRFilter;
    
    int filterType = 0;
    double fc_Hz = 1000.0;
    double Q = 0.707;
    
    int bufferCounter = 0;
    static constexpr int UPDATE_RATE = 64;
    bool needsParameterUpdate = true;
    
    AspikFilterAnalogFIR()
    {
        updateFilterParameters();
    }
    
    void prepare(PrepareSpecs specs)
    {
        analogFIRFilter.reset(specs.sampleRate);
        bufferCounter = 0;
        needsParameterUpdate = true;
        updateFilterParameters();
    }
    
    void reset()
    {
        analogFIRFilter.reset(44100.0);
        bufferCounter = 0;
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
        if (needsParameterUpdate && bufferCounter++ >= UPDATE_RATE)
        {
            updateFilterParameters();
            needsParameterUpdate = false;
            bufferCounter = 0;
        }
        
        data[0] = static_cast<float>(analogFIRFilter.processAudioSample(static_cast<double>(data[0])));
    }
    
    int handleModulation(double& value)
    {
        return 0;
    }
    
    template <int P> void setParameter(double v)
    {
        if (P == 0)
        {
            int newFilterType = jlimit(0, 5, (int)v);
            if (filterType != newFilterType)
            {
                filterType = newFilterType;
                needsParameterUpdate = true;
            }
        }
        else if (P == 1)
        {
            double newFc = jlimit(20.0, 20480.0, v);
            if (abs(fc_Hz - newFc) > 1.0)
            {
                fc_Hz = newFc;
                needsParameterUpdate = true;
            }
        }
        else if (P == 2)
        {
            double newQ = jlimit(0.1, 20.0, v);
            if (abs(Q - newQ) > 0.01)
            {
                Q = newQ;
                needsParameterUpdate = true;
            }
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("FilterType", { 0.0, 5.0, 1.0 });
            registerCallback<0>(p);
            p.setDefaultValue(0.0);
            
            StringArray filterTypes;
            filterTypes.add("LPF1");
            filterTypes.add("HPF1");
            filterTypes.add("LPF2");
            filterTypes.add("HPF2");
            filterTypes.add("BPF2");
            filterTypes.add("BSF2");
            
            p.setParameterValueNames(filterTypes);
            data.add(std::move(p));
        }
        
        {
            parameter::data p("Frequency", { 20.0, 20480.0 });
            registerCallback<1>(p);
            p.setDefaultValue(1000.0);
            p.setSkewForCentre(1000.0);
            data.add(std::move(p));
        }
        
        {
            parameter::data p("Q", { 0.1, 20.0 });
            registerCallback<2>(p);
            p.setDefaultValue(0.707);
            data.add(std::move(p));
        }
    }
    
private:
    
    void updateFilterParameters()
    {
        aspik::AnalogFIRFilterParameters params;
        
        switch (filterType)
        {
            case 0: params.filterType = aspik::analogFilter::kLPF1; break;
            case 1: params.filterType = aspik::analogFilter::kHPF1; break;
            case 2: params.filterType = aspik::analogFilter::kLPF2; break;
            case 3: params.filterType = aspik::analogFilter::kHPF2; break;
            case 4: params.filterType = aspik::analogFilter::kBPF2; break;
            case 5: params.filterType = aspik::analogFilter::kBSF2; break;
            default: params.filterType = aspik::analogFilter::kLPF1; break;
        }
        
        params.fc = fc_Hz;
        params.Q = Q;
        
        analogFIRFilter.setParameters(params);
    }
};

} // namespace project

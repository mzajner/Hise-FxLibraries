#pragma once

#include <JuceHeader.h>
#include "src/Aspik/aspik.h"

/*
 ==========================| ASPIK Resonance Filter HISE Node |==========================
 
 Resonance filters provide high-Q resonant peaks for special effects and synthesis.
 - kResonA: Resonance algorithm A - bandwidth-controlled resonant design
 - kResonB: Resonance algorithm B - alternative resonance calculation method
 - Designed for musical resonance effects with high Q capabilities
 - Perfect for creating ringing, bell-like sounds and resonant sweeps
 
 Based on Will Pirkle's "Designing Audio Effect Plugins in C++" Resonance algorithms.
 Uses bandwidth and frequency controls for precise resonant peak shaping.
 */

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;
using namespace aspik;

template <int NV> struct AspikFilterResonance : public data::base
{
    SNEX_NODE(AspikFilterResonance);
    
    struct MetadataClass
    {
        SN_NODE_ID("AspikFilterResonance");
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
    double q = 5.0;
    int resonanceType = 0;
    
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
            double newQ = jlimit(0.1, 50.0, v);
            if (q != newQ)
            {
                q = newQ;
                updateFilterParameters();
            }
        }
        else if (P == 2)
        {
            int newType = jlimit(0, 1, (int)v);
            if (resonanceType != newType)
            {
                resonanceType = newType;
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
            parameter::data p("Q", { 0.1, 50.0 });
            registerCallback<1>(p);
            p.setDefaultValue(5.0);
            p.setSkewForCentre(5.0);
            data.add(std::move(p));
        }
        
        {
            parameter::data p("ResonanceType", { 0.0, 1.0, 1.0 });
            registerCallback<2>(p);
            p.setDefaultValue(0.0);
            
            StringArray resonanceNames;
            resonanceNames.add("Resonance A");
            resonanceNames.add("Resonance B");
            
            p.setParameterValueNames(resonanceNames);
            data.add(std::move(p));
        }
    }
    
private:
    
    void updateFilterParameters()
    {
        aspik::AudioFilterParameters params;
        params.fc = frequency;
        params.Q = q;
        params.boostCut_dB = 0.0;
        params.algorithm = (resonanceType == 0) ? aspik::filterAlgorithm::kResonA : aspik::filterAlgorithm::kResonB;
        
        leftFilter.setParameters(params);
        rightFilter.setParameters(params);
    }
};

} // namespace project

#pragma once

#include <JuceHeader.h>
#include "src/Aspik/aspik.h"

/*
 ==========================| ASPIK Biquad Filter HISE Node |==========================
 
 Pure biquad implementation from section 10.23 with calculation topology selection.
 - Uses raw aspik::Biquad object with direct coefficient control
 - Four calculation topologies: Direct, Canonical, Transpose Direct, Transpose Canonical
 - Simple frequency/Q controls that calculate basic lowpass coefficients
 - Educational tool for understanding biquad mathematics and topology differences
 
 Based on Will Pirkle's "Designing Audio Effect Plugins in C++" Section 10.23 Biquad object.
 This is the raw mathematical biquad engine, not the high-level AudioFilter algorithms.
 */

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;
using namespace aspik;

template <int NV> struct AspikFilterBiquad : public data::base
{
    SNEX_NODE(AspikFilterBiquad);
    
    struct MetadataClass
    {
        SN_NODE_ID("AspikFilterBiquad");
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
    
    aspik::Biquad leftBiquad;
    aspik::Biquad rightBiquad;
    
    double sampleRate = 44100.0;
    double frequency = 1000.0;
    double q = 0.707;
    int calcType = 3;
    
    double currentCoeffs[7] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    
    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;
        leftBiquad.reset(specs.sampleRate);
        rightBiquad.reset(specs.sampleRate);
        updateBiquadParameters();
    }
    
    void reset()
    {
        leftBiquad.reset(sampleRate);
        rightBiquad.reset(sampleRate);
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
        data[0] = static_cast<float>(leftBiquad.processAudioSample(static_cast<double>(data[0])));
        
        if (getFixChannelAmount() > 1)
        {
            data[1] = static_cast<float>(rightBiquad.processAudioSample(static_cast<double>(data[1])));
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
                updateBiquadParameters();
            }
        }
        else if (P == 1)
        {
            double newQ = jlimit(0.1, 50.0, v);
            if (q != newQ)
            {
                q = newQ;
                updateBiquadParameters();
            }
        }
        else if (P == 2)
        {
            int newCalcType = jlimit(0, 3, (int)v);
            if (calcType != newCalcType)
            {
                calcType = newCalcType;
                updateBiquadParameters();
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
            p.setDefaultValue(0.707);
            p.setSkewForCentre(3.0);
            data.add(std::move(p));
        }
        
        {
            parameter::data p("CalcType", { 0.0, 3.0, 1.0 });
            registerCallback<2>(p);
            p.setDefaultValue(3.0);
            
            StringArray calcNames;
            calcNames.add("Direct");
            calcNames.add("Canonical");
            calcNames.add("Transpose Direct");
            calcNames.add("Transpose Canon");
            
            p.setParameterValueNames(calcNames);
            data.add(std::move(p));
        }
    }
    
private:
    
    void updateBiquadParameters()
    {
        calculateBasicLowpassCoefficients();
        
        leftBiquad.setCoefficients(currentCoeffs);
        rightBiquad.setCoefficients(currentCoeffs);
        
        aspik::BiquadParameters bqParams;
        switch (calcType)
        {
            case 0: bqParams.biquadCalcType = aspik::biquadAlgorithm::kDirect; break;
            case 1: bqParams.biquadCalcType = aspik::biquadAlgorithm::kCanonical; break;
            case 2: bqParams.biquadCalcType = aspik::biquadAlgorithm::kTransposeDirect; break;
            case 3: bqParams.biquadCalcType = aspik::biquadAlgorithm::kTransposeCanonical; break;
            default: bqParams.biquadCalcType = aspik::biquadAlgorithm::kTransposeCanonical; break;
        }
        
        leftBiquad.setParameters(bqParams);
        rightBiquad.setParameters(bqParams);
    }
    
    void calculateBasicLowpassCoefficients()
    {
        double theta_c = 2.0 * juce::MathConstants<double>::pi * frequency / sampleRate;
        double d = 1.0 / q;
        
        double betaNumerator = 1.0 - ((d / 2.0) * sin(theta_c));
        double betaDenominator = 1.0 + ((d / 2.0) * sin(theta_c));
        double beta = 0.5 * (betaNumerator / betaDenominator);
        double gamma = (0.5 + beta) * cos(theta_c);
        double alpha = (0.5 + beta - gamma) / 2.0;
        
        currentCoeffs[0] = alpha;
        currentCoeffs[1] = 2.0 * alpha;
        currentCoeffs[2] = alpha;
        currentCoeffs[3] = -2.0 * gamma;
        currentCoeffs[4] = 2.0 * beta;
        currentCoeffs[5] = 0.0;
        currentCoeffs[6] = 0.0;
    }
};

} // namespace project

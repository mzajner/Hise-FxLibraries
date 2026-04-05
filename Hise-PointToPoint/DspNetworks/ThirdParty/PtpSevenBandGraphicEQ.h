#pragma once
#include <JuceHeader.h>
#include "src/PointToPoint/EQCircuits.h"

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV>
struct PtpSevenBandGraphicEQ : public data::base
{
    SNEX_NODE(PtpSevenBandGraphicEQ);

    struct MetadataClass { SN_NODE_ID("PtpSevenBandGraphicEQ"); };

    static constexpr bool isModNode()            { return false; }
    static constexpr bool isPolyphonic()         { return NV > 1; }
    static constexpr bool hasTail()              { return false; }
    static constexpr bool isSuspendedOnSilence() { return true; }
    static constexpr int  getFixChannelAmount()  { return 2; }

    static constexpr int NumTables         = 0;
    static constexpr int NumSliderPacks    = 0;
    static constexpr int NumAudioFiles     = 0;
    static constexpr int NumFilters        = 0;
    static constexpr int NumDisplayBuffers = 0;

    PointToPoint::SevenBandGraphicEQ effect;

    double sampleRate = 44100.0;
    int    blockSize  = 512;

    std::vector<double> params { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };

    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;
        blockSize  = specs.blockSize;
        effect.prepare(sampleRate, blockSize);
        effect.setParameterUpdateIntervalInSamples(64);
        effect.setSmoothResponseTimeMilliseconds(5.0f);
    }

    void reset()
    {
        effect.prepare(sampleRate, blockSize);
    }

    template <typename ProcessDataType>
    void process(ProcessDataType& data)
    {
        effect.setParametersWithSmoothing(params);

        auto& fix = data.template as<ProcessData<2>>();
        auto  blk = fix.toAudioBlock();

        float* L = blk.getChannelPointer(0);
        float* R = blk.getChannelPointer(1);
        int    n = data.getNumSamples();

        effect.processInPlace(L, 0, n);
        effect.processInPlace(R, 1, n);
    }

    SN_EMPTY_PROCESS_FRAME;
    SN_EMPTY_HANDLE_EVENT;

    template <int P> void setParameter(double v)
    {
        if      (P == 0) params[0] = v;
        else if (P == 1) params[1] = v;
        else if (P == 2) params[2] = v;
        else if (P == 3) params[3] = v;
        else if (P == 4) params[4] = v;
        else if (P == 5) params[5] = v;
        else if (P == 6) params[6] = v;
    }

    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("63 Hz", { 0.0, 1.0 });
            registerCallback<0>(p);
            p.setDefaultValue(0.5);
            data.add(std::move(p));
        }
        {
            parameter::data p("160 Hz", { 0.0, 1.0 });
            registerCallback<1>(p);
            p.setDefaultValue(0.5);
            data.add(std::move(p));
        }
        {
            parameter::data p("410 Hz", { 0.0, 1.0 });
            registerCallback<2>(p);
            p.setDefaultValue(0.5);
            data.add(std::move(p));
        }
        {
            parameter::data p("1 Khz", { 0.0, 1.0 });
            registerCallback<3>(p);
            p.setDefaultValue(0.5);
            data.add(std::move(p));
        }
        {
            parameter::data p("2 5 Khz", { 0.0, 1.0 });
            registerCallback<4>(p);
            p.setDefaultValue(0.5);
            data.add(std::move(p));
        }
        {
            parameter::data p("7 7 Khz", { 0.0, 1.0 });
            registerCallback<5>(p);
            p.setDefaultValue(0.5);
            data.add(std::move(p));
        }
        {
            parameter::data p("16 Khz", { 0.0, 1.0 });
            registerCallback<6>(p);
            p.setDefaultValue(0.5);
            data.add(std::move(p));
        }
    }

    void setExternalData(const ExternalData&, int) {}
    int  handleModulation(double&) { return 0; }
};

} // namespace project

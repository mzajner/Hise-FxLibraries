#pragma once
#include <JuceHeader.h>
#include "src/PointToPoint/Lite.h"

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV>
struct PtpFourOpAmpStateVariableBPF2kHzA : public data::base
{
    SNEX_NODE(PtpFourOpAmpStateVariableBPF2kHzA);

    struct MetadataClass { SN_NODE_ID("PtpFourOpAmpStateVariableBPF2kHzA"); };

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

    PointToPoint::FourOpAmpStateVariableBPF_2kHz_A effect;

    double sampleRate = 44100.0;
    int    blockSize  = 512;

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

    void createParameters(ParameterDataList&) {}

    void setExternalData(const ExternalData&, int) {}
    int  handleModulation(double&) { return 0; }
};

} // namespace project

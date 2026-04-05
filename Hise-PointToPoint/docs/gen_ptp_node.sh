#!/usr/bin/env bash
set -euo pipefail

FORCE=0
if [[ "${1:-}" == "--force" ]]; then
  FORCE=1
  shift
fi

CIRCUIT_CLASS="${1:?}"
PTP_HEADER="${2:?}"
NODE_NAME="${3:?}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
THIRDPARTY_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

PTP_INCLUDE="src/PointToPoint/${PTP_HEADER}"
PTP_HEADER_PATH="${THIRDPARTY_DIR}/${PTP_INCLUDE}"
OUT_FILE="${THIRDPARTY_DIR}/${NODE_NAME}.h"

[[ -f "${PTP_HEADER_PATH}" ]] || exit 1
if [[ -f "${OUT_FILE}" && "${FORCE}" -ne 1 ]]; then
  exit 1
fi

cat > "${OUT_FILE}" <<EOF
#pragma once
#include <JuceHeader.h>
#include "${PTP_INCLUDE}"

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV>
struct ${NODE_NAME} : public data::base
{
    SNEX_NODE(${NODE_NAME});

    struct MetadataClass { SN_NODE_ID("${NODE_NAME}"); };

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

    PointToPoint::${CIRCUIT_CLASS} effect;

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
EOF

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::biquadonehalf_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/BiquadOneHalf/BiquadOneHalf.h"
#include "src/airwindows/BiquadOneHalf/BiquadOneHalf.cpp.inc"
#include "src/airwindows/BiquadOneHalf/BiquadOneHalfProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::biquadonehalf_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(BiquadOneHalf, biquadonehalf_ns);

}  // namespace project

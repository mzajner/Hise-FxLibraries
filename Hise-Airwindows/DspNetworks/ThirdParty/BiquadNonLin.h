#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::biquadnonlin_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/BiquadNonLin/BiquadNonLin.h"
#include "src/airwindows/BiquadNonLin/BiquadNonLin.cpp.inc"
#include "src/airwindows/BiquadNonLin/BiquadNonLinProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::biquadnonlin_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(BiquadNonLin, biquadnonlin_ns);

}  // namespace project

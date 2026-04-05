#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::biquadplus_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/BiquadPlus/BiquadPlus.h"
#include "src/airwindows/BiquadPlus/BiquadPlus.cpp.inc"
#include "src/airwindows/BiquadPlus/BiquadPlusProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::biquadplus_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(BiquadPlus, biquadplus_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::biquaddouble_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/BiquadDouble/BiquadDouble.h"
#include "src/airwindows/BiquadDouble/BiquadDouble.cpp.inc"
#include "src/airwindows/BiquadDouble/BiquadDoubleProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::biquaddouble_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(BiquadDouble, biquaddouble_ns);

}  // namespace project

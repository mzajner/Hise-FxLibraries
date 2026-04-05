#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::ditherfloat_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/DitherFloat/DitherFloat.h"
#include "src/airwindows/DitherFloat/DitherFloat.cpp.inc"
#include "src/airwindows/DitherFloat/DitherFloatProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ditherfloat_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(DitherFloat, ditherfloat_ns);

}  // namespace project

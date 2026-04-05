#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::anglefilter_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/AngleFilter/AngleFilter.h"
#include "src/airwindows/AngleFilter/AngleFilter.cpp.inc"
#include "src/airwindows/AngleFilter/AngleFilterProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::anglefilter_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(AngleFilter, anglefilter_ns);

}  // namespace project

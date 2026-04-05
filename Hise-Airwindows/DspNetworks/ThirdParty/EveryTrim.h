#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::everytrim_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/EveryTrim/EveryTrim.h"
#include "src/airwindows/EveryTrim/EveryTrim.cpp.inc"
#include "src/airwindows/EveryTrim/EveryTrimProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::everytrim_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(EveryTrim, everytrim_ns);

}  // namespace project

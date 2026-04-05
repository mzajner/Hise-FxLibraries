#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::platinumslew_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PlatinumSlew/PlatinumSlew.h"
#include "src/airwindows/PlatinumSlew/PlatinumSlew.cpp.inc"
#include "src/airwindows/PlatinumSlew/PlatinumSlewProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::platinumslew_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PlatinumSlew, platinumslew_ns);

}  // namespace project

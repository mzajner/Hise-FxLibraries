#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::console7crunch_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Console7Crunch/Console7Crunch.h"
#include "src/airwindows/Console7Crunch/Console7Crunch.cpp.inc"
#include "src/airwindows/Console7Crunch/Console7CrunchProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::console7crunch_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Console7Crunch, console7crunch_ns);

}  // namespace project

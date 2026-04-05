#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::console7cascade_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Console7Cascade/Console7Cascade.h"
#include "src/airwindows/Console7Cascade/Console7Cascade.cpp.inc"
#include "src/airwindows/Console7Cascade/Console7CascadeProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::console7cascade_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Console7Cascade, console7cascade_ns);

}  // namespace project

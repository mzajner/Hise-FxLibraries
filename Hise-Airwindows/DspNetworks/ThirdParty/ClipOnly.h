#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::cliponly_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ClipOnly/ClipOnly.h"
#include "src/airwindows/ClipOnly/ClipOnly.cpp.inc"
#include "src/airwindows/ClipOnly/ClipOnlyProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::cliponly_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ClipOnly, cliponly_ns);

}  // namespace project

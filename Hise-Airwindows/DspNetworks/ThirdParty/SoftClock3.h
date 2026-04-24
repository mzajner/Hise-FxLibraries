#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::softclock3_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/SoftClock3/SoftClock3.h"
#include "src/airwindows/SoftClock3/SoftClock3.cpp.inc"
#include "src/airwindows/SoftClock3/SoftClock3Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::softclock3_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(SoftClock3, softclock3_ns);

}  // namespace project

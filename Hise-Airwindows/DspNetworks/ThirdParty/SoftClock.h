#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::softclock_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/SoftClock/SoftClock.h"
#include "src/airwindows/SoftClock/SoftClock.cpp.inc"
#include "src/airwindows/SoftClock/SoftClockProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::softclock_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(SoftClock, softclock_ns);

}  // namespace project

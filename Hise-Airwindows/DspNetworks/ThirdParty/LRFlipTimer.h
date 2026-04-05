#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::lrfliptimer_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/LRFlipTimer/LRFlipTimer.h"
#include "src/airwindows/LRFlipTimer/LRFlipTimer.cpp.inc"
#include "src/airwindows/LRFlipTimer/LRFlipTimerProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::lrfliptimer_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(LRFlipTimer, lrfliptimer_ns);

}  // namespace project

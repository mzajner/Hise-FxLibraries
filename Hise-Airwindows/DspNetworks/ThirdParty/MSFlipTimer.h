#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::msfliptimer_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/MSFlipTimer/MSFlipTimer.h"
#include "src/airwindows/MSFlipTimer/MSFlipTimer.cpp.inc"
#include "src/airwindows/MSFlipTimer/MSFlipTimerProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::msfliptimer_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(MSFlipTimer, msfliptimer_ns);

}  // namespace project

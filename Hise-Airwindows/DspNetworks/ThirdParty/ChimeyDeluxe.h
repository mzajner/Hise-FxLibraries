#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::chimeydeluxe_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ChimeyDeluxe/ChimeyDeluxe.h"
#include "src/airwindows/ChimeyDeluxe/ChimeyDeluxe.cpp.inc"
#include "src/airwindows/ChimeyDeluxe/ChimeyDeluxeProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::chimeydeluxe_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ChimeyDeluxe, chimeydeluxe_ns);

}  // namespace project

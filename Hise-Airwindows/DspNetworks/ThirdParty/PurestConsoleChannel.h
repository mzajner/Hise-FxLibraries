#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::purestconsolechannel_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PurestConsoleChannel/PurestConsoleChannel.h"
#include "src/airwindows/PurestConsoleChannel/PurestConsoleChannel.cpp.inc"
#include "src/airwindows/PurestConsoleChannel/PurestConsoleChannelProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::purestconsolechannel_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PurestConsoleChannel, purestconsolechannel_ns);

}  // namespace project

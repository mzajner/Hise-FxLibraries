#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::purestconsole3channel_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PurestConsole3Channel/PurestConsole3Channel.h"
#include "src/airwindows/PurestConsole3Channel/PurestConsole3Channel.cpp.inc"
#include "src/airwindows/PurestConsole3Channel/PurestConsole3ChannelProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::purestconsole3channel_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PurestConsole3Channel, purestconsole3channel_ns);

}  // namespace project

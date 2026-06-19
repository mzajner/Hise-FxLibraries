#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::purestconsole2channel_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PurestConsole2Channel/PurestConsole2Channel.h"
#include "src/airwindows/PurestConsole2Channel/PurestConsole2Channel.cpp"
#include "src/airwindows/PurestConsole2Channel/PurestConsole2ChannelProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::purestconsole2channel_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PurestConsole2Channel, purestconsole2channel_ns);

}  // namespace project

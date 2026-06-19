#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::consolexchannel_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ConsoleXChannel/ConsoleXChannel.h"
#include "src/airwindows/ConsoleXChannel/ConsoleXChannel.cpp"
#include "src/airwindows/ConsoleXChannel/ConsoleXChannelProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::consolexchannel_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ConsoleXChannel, consolexchannel_ns);

}  // namespace project

#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::consolemcchannel_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ConsoleMCChannel/ConsoleMCChannel.h"
#include "src/airwindows/ConsoleMCChannel/ConsoleMCChannel.cpp"
#include "src/airwindows/ConsoleMCChannel/ConsoleMCChannelProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::consolemcchannel_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ConsoleMCChannel, consolemcchannel_ns);

}  // namespace project

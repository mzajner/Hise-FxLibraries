#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::consolemcchannel_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ConsoleMCChannel/ConsoleMCChannel.h"
#include "src/airwindows/ConsoleMCChannel/ConsoleMCChannel.cpp.inc"
#include "src/airwindows/ConsoleMCChannel/ConsoleMCChannelProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::consolemcchannel_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ConsoleMCChannel, consolemcchannel_ns);

}  // namespace project

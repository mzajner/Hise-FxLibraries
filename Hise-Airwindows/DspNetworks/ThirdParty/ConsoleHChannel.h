#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::consolehchannel_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ConsoleHChannel/ConsoleHChannel.h"
#include "src/airwindows/ConsoleHChannel/ConsoleHChannel.cpp.inc"
#include "src/airwindows/ConsoleHChannel/ConsoleHChannelProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::consolehchannel_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ConsoleHChannel, consolehchannel_ns);

}  // namespace project

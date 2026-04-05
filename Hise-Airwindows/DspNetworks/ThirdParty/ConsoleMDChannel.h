#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::consolemdchannel_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ConsoleMDChannel/ConsoleMDChannel.h"
#include "src/airwindows/ConsoleMDChannel/ConsoleMDChannel.cpp.inc"
#include "src/airwindows/ConsoleMDChannel/ConsoleMDChannelProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::consolemdchannel_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ConsoleMDChannel, consolemdchannel_ns);

}  // namespace project

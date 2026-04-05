#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::consolex2channel_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ConsoleX2Channel/ConsoleX2Channel.h"
#include "src/airwindows/ConsoleX2Channel/ConsoleX2Channel.cpp.inc"
#include "src/airwindows/ConsoleX2Channel/ConsoleX2ChannelProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::consolex2channel_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ConsoleX2Channel, consolex2channel_ns);

}  // namespace project

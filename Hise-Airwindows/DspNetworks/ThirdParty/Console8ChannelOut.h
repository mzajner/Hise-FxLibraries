#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::console8channelout_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Console8ChannelOut/Console8ChannelOut.h"
#include "src/airwindows/Console8ChannelOut/Console8ChannelOut.cpp.inc"
#include "src/airwindows/Console8ChannelOut/Console8ChannelOutProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::console8channelout_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Console8ChannelOut, console8channelout_ns);

}  // namespace project

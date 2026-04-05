#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::console8litechannel_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Console8LiteChannel/Console8LiteChannel.h"
#include "src/airwindows/Console8LiteChannel/Console8LiteChannel.cpp.inc"
#include "src/airwindows/Console8LiteChannel/Console8LiteChannelProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::console8litechannel_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Console8LiteChannel, console8litechannel_ns);

}  // namespace project

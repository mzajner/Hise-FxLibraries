#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::console6channel_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Console6Channel/Console6Channel.h"
#include "src/airwindows/Console6Channel/Console6Channel.cpp.inc"
#include "src/airwindows/Console6Channel/Console6ChannelProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::console6channel_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Console6Channel, console6channel_ns);

}  // namespace project

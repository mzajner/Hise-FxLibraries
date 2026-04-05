#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::console8channelin_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Console8ChannelIn/Console8ChannelIn.h"
#include "src/airwindows/Console8ChannelIn/Console8ChannelIn.cpp.inc"
#include "src/airwindows/Console8ChannelIn/Console8ChannelInProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::console8channelin_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Console8ChannelIn, console8channelin_ns);

}  // namespace project

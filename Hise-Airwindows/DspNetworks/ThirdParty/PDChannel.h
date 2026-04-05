#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::pdchannel_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PDChannel/PDChannel.h"
#include "src/airwindows/PDChannel/PDChannel.cpp.inc"
#include "src/airwindows/PDChannel/PDChannelProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::pdchannel_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PDChannel, pdchannel_ns);

}  // namespace project

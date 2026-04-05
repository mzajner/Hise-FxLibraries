#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::atmospherechannel_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/AtmosphereChannel/AtmosphereChannel.h"
#include "src/airwindows/AtmosphereChannel/AtmosphereChannel.cpp.inc"
#include "src/airwindows/AtmosphereChannel/AtmosphereChannelProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::atmospherechannel_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(AtmosphereChannel, atmospherechannel_ns);

}  // namespace project

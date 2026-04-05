#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::console8channelhype_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Console8ChannelHype/Console8ChannelHype.h"
#include "src/airwindows/Console8ChannelHype/Console8ChannelHype.cpp.inc"
#include "src/airwindows/Console8ChannelHype/Console8ChannelHypeProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::console8channelhype_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Console8ChannelHype, console8channelhype_ns);

}  // namespace project

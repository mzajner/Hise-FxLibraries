#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::c5rawchannel_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/C5RawChannel/C5RawChannel.h"
#include "src/airwindows/C5RawChannel/C5RawChannel.cpp"
#include "src/airwindows/C5RawChannel/C5RawChannelProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::c5rawchannel_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(C5RawChannel, c5rawchannel_ns);

}  // namespace project

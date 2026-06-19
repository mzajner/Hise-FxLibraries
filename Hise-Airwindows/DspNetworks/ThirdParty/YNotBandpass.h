#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::ynotbandpass_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/YNotBandpass/YNotBandpass.h"
#include "src/airwindows/YNotBandpass/YNotBandpass.cpp"
#include "src/airwindows/YNotBandpass/YNotBandpassProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ynotbandpass_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(YNotBandpass, ynotbandpass_ns);

}  // namespace project

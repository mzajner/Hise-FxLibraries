#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::xbandpass_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/XBandpass/XBandpass.h"
#include "src/airwindows/XBandpass/XBandpass.cpp.inc"
#include "src/airwindows/XBandpass/XBandpassProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::xbandpass_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(XBandpass, xbandpass_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::ybandpass_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/YBandpass/YBandpass.h"
#include "src/airwindows/YBandpass/YBandpass.cpp.inc"
#include "src/airwindows/YBandpass/YBandpassProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ybandpass_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(YBandpass, ybandpass_ns);

}  // namespace project

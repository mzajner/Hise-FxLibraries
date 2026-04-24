#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::ynotlowpass_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/YNotLowpass/YNotLowpass.h"
#include "src/airwindows/YNotLowpass/YNotLowpass.cpp.inc"
#include "src/airwindows/YNotLowpass/YNotLowpassProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ynotlowpass_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(YNotLowpass, ynotlowpass_ns);

}  // namespace project

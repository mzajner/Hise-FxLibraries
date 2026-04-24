#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::ynotnotch_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/YNotNotch/YNotNotch.h"
#include "src/airwindows/YNotNotch/YNotNotch.cpp.inc"
#include "src/airwindows/YNotNotch/YNotNotchProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ynotnotch_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(YNotNotch, ynotnotch_ns);

}  // namespace project

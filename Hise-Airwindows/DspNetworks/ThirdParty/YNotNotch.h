#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::ynotnotch_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/YNotNotch/YNotNotch.h"
#include "src/airwindows/YNotNotch/YNotNotch.cpp"
#include "src/airwindows/YNotNotch/YNotNotchProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ynotnotch_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(YNotNotch, ynotnotch_ns);

}  // namespace project

#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::hipcrush_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/HipCrush/HipCrush.h"
#include "src/airwindows/HipCrush/HipCrush.cpp"
#include "src/airwindows/HipCrush/HipCrushProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::hipcrush_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(HipCrush, hipcrush_ns);

}  // namespace project

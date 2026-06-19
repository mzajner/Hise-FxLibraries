#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::powersag2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PowerSag2/PowerSag2.h"
#include "src/airwindows/PowerSag2/PowerSag2.cpp"
#include "src/airwindows/PowerSag2/PowerSag2Proc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::powersag2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PowerSag2, powersag2_ns);

}  // namespace project

#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::dynamics2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Dynamics2/Dynamics2.h"
#include "src/airwindows/Dynamics2/Dynamics2.cpp"
#include "src/airwindows/Dynamics2/Dynamics2Proc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::dynamics2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Dynamics2, dynamics2_ns);

}  // namespace project

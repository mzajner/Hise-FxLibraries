#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::acceleration2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Acceleration2/Acceleration2.h"
#include "src/airwindows/Acceleration2/Acceleration2.cpp.inc"
#include "src/airwindows/Acceleration2/Acceleration2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::acceleration2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Acceleration2, acceleration2_ns);

}  // namespace project

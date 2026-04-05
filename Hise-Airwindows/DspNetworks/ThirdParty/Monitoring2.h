#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::monitoring2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Monitoring2/Monitoring2.h"
#include "src/airwindows/Monitoring2/Monitoring2.cpp.inc"
#include "src/airwindows/Monitoring2/Monitoring2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::monitoring2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Monitoring2, monitoring2_ns);

}  // namespace project

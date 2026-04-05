#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::monitoring3_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Monitoring3/Monitoring3.h"
#include "src/airwindows/Monitoring3/Monitoring3.cpp.inc"
#include "src/airwindows/Monitoring3/Monitoring3Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::monitoring3_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Monitoring3, monitoring3_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::buttercomp2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ButterComp2/ButterComp2.h"
#include "src/airwindows/ButterComp2/ButterComp2.cpp.inc"
#include "src/airwindows/ButterComp2/ButterComp2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::buttercomp2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ButterComp2, buttercomp2_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::lowpass2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Lowpass2/Lowpass2.h"
#include "src/airwindows/Lowpass2/Lowpass2.cpp.inc"
#include "src/airwindows/Lowpass2/Lowpass2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::lowpass2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Lowpass2, lowpass2_ns);

}  // namespace project

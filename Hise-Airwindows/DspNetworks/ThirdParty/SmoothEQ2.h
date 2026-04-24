#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::smootheq2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/SmoothEQ2/SmoothEQ2.h"
#include "src/airwindows/SmoothEQ2/SmoothEQ2.cpp.inc"
#include "src/airwindows/SmoothEQ2/SmoothEQ2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::smootheq2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(SmoothEQ2, smootheq2_ns);

}  // namespace project

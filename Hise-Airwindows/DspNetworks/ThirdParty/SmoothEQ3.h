#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::smootheq3_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/SmoothEQ3/SmoothEQ3.h"
#include "src/airwindows/SmoothEQ3/SmoothEQ3.cpp.inc"
#include "src/airwindows/SmoothEQ3/SmoothEQ3Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::smootheq3_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(SmoothEQ3, smootheq3_ns);

}  // namespace project

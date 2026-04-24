#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::smootheq_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/SmoothEQ/SmoothEQ.h"
#include "src/airwindows/SmoothEQ/SmoothEQ.cpp.inc"
#include "src/airwindows/SmoothEQ/SmoothEQProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::smootheq_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(SmoothEQ, smootheq_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::lrconvolve2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/LRConvolve2/LRConvolve2.h"
#include "src/airwindows/LRConvolve2/LRConvolve2.cpp.inc"
#include "src/airwindows/LRConvolve2/LRConvolve2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::lrconvolve2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(LRConvolve2, lrconvolve2_ns);

}  // namespace project

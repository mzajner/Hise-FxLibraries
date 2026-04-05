#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::lrconvolve3_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/LRConvolve3/LRConvolve3.h"
#include "src/airwindows/LRConvolve3/LRConvolve3.cpp.inc"
#include "src/airwindows/LRConvolve3/LRConvolve3Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::lrconvolve3_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(LRConvolve3, lrconvolve3_ns);

}  // namespace project

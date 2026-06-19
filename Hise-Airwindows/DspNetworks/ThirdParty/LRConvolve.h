#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::lrconvolve_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/LRConvolve/LRConvolve.h"
#include "src/airwindows/LRConvolve/LRConvolve.cpp"
#include "src/airwindows/LRConvolve/LRConvolveProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::lrconvolve_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(LRConvolve, lrconvolve_ns);

}  // namespace project

#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::xregion_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/XRegion/XRegion.h"
#include "src/airwindows/XRegion/XRegion.cpp"
#include "src/airwindows/XRegion/XRegionProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::xregion_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(XRegion, xregion_ns);

}  // namespace project

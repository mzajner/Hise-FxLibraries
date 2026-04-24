#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::zregion2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ZRegion2/ZRegion2.h"
#include "src/airwindows/ZRegion2/ZRegion2.cpp.inc"
#include "src/airwindows/ZRegion2/ZRegion2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::zregion2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ZRegion2, zregion2_ns);

}  // namespace project

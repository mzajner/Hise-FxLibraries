#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::dubplate2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/DubPlate2/DubPlate2.h"
#include "src/airwindows/DubPlate2/DubPlate2.cpp.inc"
#include "src/airwindows/DubPlate2/DubPlate2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::dubplate2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(DubPlate2, dubplate2_ns);

}  // namespace project

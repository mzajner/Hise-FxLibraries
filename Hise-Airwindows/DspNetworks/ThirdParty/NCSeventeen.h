#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::ncseventeen_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/NCSeventeen/NCSeventeen.h"
#include "src/airwindows/NCSeventeen/NCSeventeen.cpp.inc"
#include "src/airwindows/NCSeventeen/NCSeventeenProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ncseventeen_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(NCSeventeen, ncseventeen_ns);

}  // namespace project

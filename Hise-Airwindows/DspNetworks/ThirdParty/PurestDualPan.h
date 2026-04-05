#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::purestdualpan_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PurestDualPan/PurestDualPan.h"
#include "src/airwindows/PurestDualPan/PurestDualPan.cpp.inc"
#include "src/airwindows/PurestDualPan/PurestDualPanProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::purestdualpan_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PurestDualPan, purestdualpan_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::surgetide_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/SurgeTide/SurgeTide.h"
#include "src/airwindows/SurgeTide/SurgeTide.cpp.inc"
#include "src/airwindows/SurgeTide/SurgeTideProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::surgetide_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(SurgeTide, surgetide_ns);

}  // namespace project

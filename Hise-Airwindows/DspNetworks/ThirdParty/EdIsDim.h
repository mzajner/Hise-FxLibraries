#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::edisdim_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/EdIsDim/EdIsDim.h"
#include "src/airwindows/EdIsDim/EdIsDim.cpp.inc"
#include "src/airwindows/EdIsDim/EdIsDimProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::edisdim_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(EdIsDim, edisdim_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::console8subin_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Console8SubIn/Console8SubIn.h"
#include "src/airwindows/Console8SubIn/Console8SubIn.cpp.inc"
#include "src/airwindows/Console8SubIn/Console8SubInProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::console8subin_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Console8SubIn, console8subin_ns);

}  // namespace project

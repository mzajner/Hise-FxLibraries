#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::console8bussin_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Console8BussIn/Console8BussIn.h"
#include "src/airwindows/Console8BussIn/Console8BussIn.cpp.inc"
#include "src/airwindows/Console8BussIn/Console8BussInProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::console8bussin_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Console8BussIn, console8bussin_ns);

}  // namespace project

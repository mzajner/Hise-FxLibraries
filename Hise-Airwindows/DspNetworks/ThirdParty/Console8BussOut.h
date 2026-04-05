#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::console8bussout_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Console8BussOut/Console8BussOut.h"
#include "src/airwindows/Console8BussOut/Console8BussOut.cpp.inc"
#include "src/airwindows/Console8BussOut/Console8BussOutProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::console8bussout_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Console8BussOut, console8bussout_ns);

}  // namespace project

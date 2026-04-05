#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::console8subout_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Console8SubOut/Console8SubOut.h"
#include "src/airwindows/Console8SubOut/Console8SubOut.cpp.inc"
#include "src/airwindows/Console8SubOut/Console8SubOutProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::console8subout_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Console8SubOut, console8subout_ns);

}  // namespace project

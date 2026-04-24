#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::tapedelay2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/TapeDelay2/TapeDelay2.h"
#include "src/airwindows/TapeDelay2/TapeDelay2.cpp.inc"
#include "src/airwindows/TapeDelay2/TapeDelay2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::tapedelay2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(TapeDelay2, tapedelay2_ns);

}  // namespace project

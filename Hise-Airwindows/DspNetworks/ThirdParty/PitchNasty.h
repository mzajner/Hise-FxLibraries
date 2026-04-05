#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::pitchnasty_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PitchNasty/PitchNasty.h"
#include "src/airwindows/PitchNasty/PitchNasty.cpp.inc"
#include "src/airwindows/PitchNasty/PitchNastyProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::pitchnasty_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PitchNasty, pitchnasty_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::pitchdelay_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PitchDelay/PitchDelay.h"
#include "src/airwindows/PitchDelay/PitchDelay.cpp.inc"
#include "src/airwindows/PitchDelay/PitchDelayProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::pitchdelay_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PitchDelay, pitchdelay_ns);

}  // namespace project

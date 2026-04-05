#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::phasenudge_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PhaseNudge/PhaseNudge.h"
#include "src/airwindows/PhaseNudge/PhaseNudge.cpp.inc"
#include "src/airwindows/PhaseNudge/PhaseNudgeProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::phasenudge_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PhaseNudge, phasenudge_ns);

}  // namespace project

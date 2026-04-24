#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::tubedesk_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/TubeDesk/TubeDesk.h"
#include "src/airwindows/TubeDesk/TubeDesk.cpp.inc"
#include "src/airwindows/TubeDesk/TubeDeskProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::tubedesk_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(TubeDesk, tubedesk_ns);

}  // namespace project

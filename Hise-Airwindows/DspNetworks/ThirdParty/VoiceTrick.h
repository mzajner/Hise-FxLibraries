#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::voicetrick_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/VoiceTrick/VoiceTrick.h"
#include "src/airwindows/VoiceTrick/VoiceTrick.cpp.inc"
#include "src/airwindows/VoiceTrick/VoiceTrickProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::voicetrick_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(VoiceTrick, voicetrick_ns);

}  // namespace project

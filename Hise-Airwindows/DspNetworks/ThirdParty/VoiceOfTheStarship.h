#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::voiceofthestarship_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/VoiceOfTheStarship/VoiceOfTheStarship.h"
#include "src/airwindows/VoiceOfTheStarship/VoiceOfTheStarship.cpp.inc"
#include "src/airwindows/VoiceOfTheStarship/VoiceOfTheStarshipProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::voiceofthestarship_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(VoiceOfTheStarship, voiceofthestarship_ns);

}  // namespace project

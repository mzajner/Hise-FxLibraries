#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::galacticvibe_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/GalacticVibe/GalacticVibe.h"
#include "src/airwindows/GalacticVibe/GalacticVibe.cpp.inc"
#include "src/airwindows/GalacticVibe/GalacticVibeProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::galacticvibe_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(GalacticVibe, galacticvibe_ns);

}  // namespace project

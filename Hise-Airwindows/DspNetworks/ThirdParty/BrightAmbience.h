#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::brightambience_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/BrightAmbience/BrightAmbience.h"
#include "src/airwindows/BrightAmbience/BrightAmbience.cpp.inc"
#include "src/airwindows/BrightAmbience/BrightAmbienceProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::brightambience_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(BrightAmbience, brightambience_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::darknoise_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/DarkNoise/DarkNoise.h"
#include "src/airwindows/DarkNoise/DarkNoise.cpp.inc"
#include "src/airwindows/DarkNoise/DarkNoiseProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::darknoise_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(DarkNoise, darknoise_ns);

}  // namespace project

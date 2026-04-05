#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::dithermediskers_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/DitherMeDiskers/DitherMeDiskers.h"
#include "src/airwindows/DitherMeDiskers/DitherMeDiskers.cpp.inc"
#include "src/airwindows/DitherMeDiskers/DitherMeDiskersProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::dithermediskers_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(DitherMeDiskers, dithermediskers_ns);

}  // namespace project

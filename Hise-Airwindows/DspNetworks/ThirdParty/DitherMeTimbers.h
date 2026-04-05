#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::dithermetimbers_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/DitherMeTimbers/DitherMeTimbers.h"
#include "src/airwindows/DitherMeTimbers/DitherMeTimbers.cpp.inc"
#include "src/airwindows/DitherMeTimbers/DitherMeTimbersProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::dithermetimbers_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(DitherMeTimbers, dithermetimbers_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::tapehack2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/TapeHack2/TapeHack2.h"
#include "src/airwindows/TapeHack2/TapeHack2.cpp.inc"
#include "src/airwindows/TapeHack2/TapeHack2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::tapehack2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(TapeHack2, tapehack2_ns);

}  // namespace project

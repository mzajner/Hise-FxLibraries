#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::ultrasonicmed_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/UltrasonicMed/UltrasonicMed.h"
#include "src/airwindows/UltrasonicMed/UltrasonicMed.cpp.inc"
#include "src/airwindows/UltrasonicMed/UltrasonicMedProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ultrasonicmed_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(UltrasonicMed, ultrasonicmed_ns);

}  // namespace project

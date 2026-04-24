#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::ultrasonic_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Ultrasonic/Ultrasonic.h"
#include "src/airwindows/Ultrasonic/Ultrasonic.cpp.inc"
#include "src/airwindows/Ultrasonic/UltrasonicProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ultrasonic_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Ultrasonic, ultrasonic_ns);

}  // namespace project

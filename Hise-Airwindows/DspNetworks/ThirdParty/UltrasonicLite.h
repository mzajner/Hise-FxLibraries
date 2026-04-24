#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::ultrasoniclite_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/UltrasonicLite/UltrasonicLite.h"
#include "src/airwindows/UltrasonicLite/UltrasonicLite.cpp.inc"
#include "src/airwindows/UltrasonicLite/UltrasonicLiteProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ultrasoniclite_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(UltrasonicLite, ultrasoniclite_ns);

}  // namespace project

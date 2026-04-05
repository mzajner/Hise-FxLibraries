#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::infrasonic_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Infrasonic/Infrasonic.h"
#include "src/airwindows/Infrasonic/Infrasonic.cpp.inc"
#include "src/airwindows/Infrasonic/InfrasonicProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::infrasonic_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Infrasonic, infrasonic_ns);

}  // namespace project

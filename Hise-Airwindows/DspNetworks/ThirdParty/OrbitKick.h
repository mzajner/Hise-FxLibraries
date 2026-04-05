#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::orbitkick_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/OrbitKick/OrbitKick.h"
#include "src/airwindows/OrbitKick/OrbitKick.cpp.inc"
#include "src/airwindows/OrbitKick/OrbitKickProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::orbitkick_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(OrbitKick, orbitkick_ns);

}  // namespace project

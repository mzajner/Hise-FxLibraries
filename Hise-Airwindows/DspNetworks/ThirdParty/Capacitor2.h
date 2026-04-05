#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::capacitor2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Capacitor2/Capacitor2.h"
#include "src/airwindows/Capacitor2/Capacitor2.cpp.inc"
#include "src/airwindows/Capacitor2/Capacitor2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::capacitor2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Capacitor2, capacitor2_ns);

}  // namespace project

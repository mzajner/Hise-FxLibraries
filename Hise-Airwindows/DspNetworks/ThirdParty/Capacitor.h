#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::capacitor_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Capacitor/Capacitor.h"
#include "src/airwindows/Capacitor/Capacitor.cpp"
#include "src/airwindows/Capacitor/CapacitorProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::capacitor_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Capacitor, capacitor_ns);

}  // namespace project

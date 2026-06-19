#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::dcvoltage_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/DCVoltage/DCVoltage.h"
#include "src/airwindows/DCVoltage/DCVoltage.cpp"
#include "src/airwindows/DCVoltage/DCVoltageProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::dcvoltage_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(DCVoltage, dcvoltage_ns);

}  // namespace project

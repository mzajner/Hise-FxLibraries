#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::ringmodulator_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/RingModulator/RingModulator.h"
#include "src/airwindows/RingModulator/RingModulator.cpp.inc"
#include "src/airwindows/RingModulator/RingModulatorProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ringmodulator_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(RingModulator, ringmodulator_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::hardvacuum_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/HardVacuum/HardVacuum.h"
#include "src/airwindows/HardVacuum/HardVacuum.cpp.inc"
#include "src/airwindows/HardVacuum/HardVacuumProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::hardvacuum_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(HardVacuum, hardvacuum_ns);

}  // namespace project

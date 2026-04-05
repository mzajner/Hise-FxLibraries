#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::purestsaturation_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PurestSaturation/PurestSaturation.h"
#include "src/airwindows/PurestSaturation/PurestSaturation.cpp.inc"
#include "src/airwindows/PurestSaturation/PurestSaturationProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::purestsaturation_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PurestSaturation, purestsaturation_ns);

}  // namespace project

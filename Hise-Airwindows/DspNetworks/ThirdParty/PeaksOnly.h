#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::peaksonly_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PeaksOnly/PeaksOnly.h"
#include "src/airwindows/PeaksOnly/PeaksOnly.cpp.inc"
#include "src/airwindows/PeaksOnly/PeaksOnlyProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::peaksonly_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PeaksOnly, peaksonly_ns);

}  // namespace project

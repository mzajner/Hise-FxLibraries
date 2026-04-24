#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::subsonly_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/SubsOnly/SubsOnly.h"
#include "src/airwindows/SubsOnly/SubsOnly.cpp.inc"
#include "src/airwindows/SubsOnly/SubsOnlyProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::subsonly_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(SubsOnly, subsonly_ns);

}  // namespace project

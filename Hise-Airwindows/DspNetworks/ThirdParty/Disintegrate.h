#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::disintegrate_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Disintegrate/Disintegrate.h"
#include "src/airwindows/Disintegrate/Disintegrate.cpp.inc"
#include "src/airwindows/Disintegrate/DisintegrateProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::disintegrate_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Disintegrate, disintegrate_ns);

}  // namespace project

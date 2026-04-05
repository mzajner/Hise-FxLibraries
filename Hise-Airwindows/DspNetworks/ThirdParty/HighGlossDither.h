#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::highglossdither_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/HighGlossDither/HighGlossDither.h"
#include "src/airwindows/HighGlossDither/HighGlossDither.cpp.inc"
#include "src/airwindows/HighGlossDither/HighGlossDitherProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::highglossdither_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(HighGlossDither, highglossdither_ns);

}  // namespace project

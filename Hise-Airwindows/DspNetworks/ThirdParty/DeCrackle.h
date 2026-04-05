#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::decrackle_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/DeCrackle/DeCrackle.h"
#include "src/airwindows/DeCrackle/DeCrackle.cpp.inc"
#include "src/airwindows/DeCrackle/DeCrackleProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::decrackle_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(DeCrackle, decrackle_ns);

}  // namespace project

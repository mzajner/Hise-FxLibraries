#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::infinity_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Infinity/Infinity.h"
#include "src/airwindows/Infinity/Infinity.cpp"
#include "src/airwindows/Infinity/InfinityProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::infinity_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Infinity, infinity_ns);

}  // namespace project

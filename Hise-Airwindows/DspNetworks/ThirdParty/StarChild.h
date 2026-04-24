#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::starchild_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/StarChild/StarChild.h"
#include "src/airwindows/StarChild/StarChild.cpp.inc"
#include "src/airwindows/StarChild/StarChildProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::starchild_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(StarChild, starchild_ns);

}  // namespace project

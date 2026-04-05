#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::consolex2pre_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ConsoleX2Pre/ConsoleX2Pre.h"
#include "src/airwindows/ConsoleX2Pre/ConsoleX2Pre.cpp.inc"
#include "src/airwindows/ConsoleX2Pre/ConsoleX2PreProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::consolex2pre_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ConsoleX2Pre, consolex2pre_ns);

}  // namespace project

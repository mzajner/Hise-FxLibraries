#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::consolexpre_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ConsoleXPre/ConsoleXPre.h"
#include "src/airwindows/ConsoleXPre/ConsoleXPre.cpp.inc"
#include "src/airwindows/ConsoleXPre/ConsoleXPreProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::consolexpre_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ConsoleXPre, consolexpre_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::everyconsole_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/EveryConsole/EveryConsole.h"
#include "src/airwindows/EveryConsole/EveryConsole.cpp.inc"
#include "src/airwindows/EveryConsole/EveryConsoleProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::everyconsole_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(EveryConsole, everyconsole_ns);

}  // namespace project

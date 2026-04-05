#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::consolexbuss_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ConsoleXBuss/ConsoleXBuss.h"
#include "src/airwindows/ConsoleXBuss/ConsoleXBuss.cpp.inc"
#include "src/airwindows/ConsoleXBuss/ConsoleXBussProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::consolexbuss_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ConsoleXBuss, consolexbuss_ns);

}  // namespace project

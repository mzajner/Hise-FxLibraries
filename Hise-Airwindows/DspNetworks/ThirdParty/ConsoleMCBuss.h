#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::consolemcbuss_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ConsoleMCBuss/ConsoleMCBuss.h"
#include "src/airwindows/ConsoleMCBuss/ConsoleMCBuss.cpp.inc"
#include "src/airwindows/ConsoleMCBuss/ConsoleMCBussProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::consolemcbuss_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ConsoleMCBuss, consolemcbuss_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::consolex2buss_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ConsoleX2Buss/ConsoleX2Buss.h"
#include "src/airwindows/ConsoleX2Buss/ConsoleX2Buss.cpp.inc"
#include "src/airwindows/ConsoleX2Buss/ConsoleX2BussProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::consolex2buss_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ConsoleX2Buss, consolex2buss_ns);

}  // namespace project

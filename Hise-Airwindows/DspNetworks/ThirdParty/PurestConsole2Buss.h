#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::purestconsole2buss_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PurestConsole2Buss/PurestConsole2Buss.h"
#include "src/airwindows/PurestConsole2Buss/PurestConsole2Buss.cpp.inc"
#include "src/airwindows/PurestConsole2Buss/PurestConsole2BussProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::purestconsole2buss_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PurestConsole2Buss, purestconsole2buss_ns);

}  // namespace project

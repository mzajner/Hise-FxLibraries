#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::purestconsole3buss_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PurestConsole3Buss/PurestConsole3Buss.h"
#include "src/airwindows/PurestConsole3Buss/PurestConsole3Buss.cpp"
#include "src/airwindows/PurestConsole3Buss/PurestConsole3BussProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::purestconsole3buss_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PurestConsole3Buss, purestconsole3buss_ns);

}  // namespace project

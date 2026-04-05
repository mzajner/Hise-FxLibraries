#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::purestconsolebuss_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PurestConsoleBuss/PurestConsoleBuss.h"
#include "src/airwindows/PurestConsoleBuss/PurestConsoleBuss.cpp.inc"
#include "src/airwindows/PurestConsoleBuss/PurestConsoleBussProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::purestconsolebuss_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PurestConsoleBuss, purestconsolebuss_ns);

}  // namespace project

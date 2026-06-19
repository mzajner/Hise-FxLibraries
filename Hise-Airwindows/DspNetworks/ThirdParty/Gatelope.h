#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::gatelope_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Gatelope/Gatelope.h"
#include "src/airwindows/Gatelope/Gatelope.cpp"
#include "src/airwindows/Gatelope/GatelopeProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::gatelope_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Gatelope, gatelope_ns);

}  // namespace project

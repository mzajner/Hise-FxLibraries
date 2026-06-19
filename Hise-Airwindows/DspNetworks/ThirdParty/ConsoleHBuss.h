#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::consolehbuss_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ConsoleHBuss/ConsoleHBuss.h"
#include "src/airwindows/ConsoleHBuss/ConsoleHBuss.cpp"
#include "src/airwindows/ConsoleHBuss/ConsoleHBussProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::consolehbuss_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ConsoleHBuss, consolehbuss_ns);

}  // namespace project

#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::consolemdbuss_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ConsoleMDBuss/ConsoleMDBuss.h"
#include "src/airwindows/ConsoleMDBuss/ConsoleMDBuss.cpp"
#include "src/airwindows/ConsoleMDBuss/ConsoleMDBussProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::consolemdbuss_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ConsoleMDBuss, consolemdbuss_ns);

}  // namespace project

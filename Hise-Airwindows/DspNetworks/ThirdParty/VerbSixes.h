#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::verbsixes_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/VerbSixes/VerbSixes.h"
#include "src/airwindows/VerbSixes/VerbSixes.cpp"
#include "src/airwindows/VerbSixes/VerbSixesProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::verbsixes_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(VerbSixes, verbsixes_ns);

}  // namespace project

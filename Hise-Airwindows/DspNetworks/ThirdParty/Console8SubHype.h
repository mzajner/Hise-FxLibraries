#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::console8subhype_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Console8SubHype/Console8SubHype.h"
#include "src/airwindows/Console8SubHype/Console8SubHype.cpp"
#include "src/airwindows/Console8SubHype/Console8SubHypeProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::console8subhype_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Console8SubHype, console8subhype_ns);

}  // namespace project

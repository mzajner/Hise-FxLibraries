#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::console8busshype_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Console8BussHype/Console8BussHype.h"
#include "src/airwindows/Console8BussHype/Console8BussHype.cpp.inc"
#include "src/airwindows/Console8BussHype/Console8BussHypeProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::console8busshype_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Console8BussHype, console8busshype_ns);

}  // namespace project

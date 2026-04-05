#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::goldenslew_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/GoldenSlew/GoldenSlew.h"
#include "src/airwindows/GoldenSlew/GoldenSlew.cpp.inc"
#include "src/airwindows/GoldenSlew/GoldenSlewProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::goldenslew_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(GoldenSlew, goldenslew_ns);

}  // namespace project

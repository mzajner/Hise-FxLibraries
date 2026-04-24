#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::ultrasonx_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/UltrasonX/UltrasonX.h"
#include "src/airwindows/UltrasonX/UltrasonX.cpp.inc"
#include "src/airwindows/UltrasonX/UltrasonXProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ultrasonx_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(UltrasonX, ultrasonx_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::cliponly2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ClipOnly2/ClipOnly2.h"
#include "src/airwindows/ClipOnly2/ClipOnly2.cpp.inc"
#include "src/airwindows/ClipOnly2/ClipOnly2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::cliponly2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ClipOnly2, cliponly2_ns);

}  // namespace project

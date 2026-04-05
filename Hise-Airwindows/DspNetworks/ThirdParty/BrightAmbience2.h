#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::brightambience2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/BrightAmbience2/BrightAmbience2.h"
#include "src/airwindows/BrightAmbience2/BrightAmbience2.cpp.inc"
#include "src/airwindows/BrightAmbience2/BrightAmbience2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::brightambience2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(BrightAmbience2, brightambience2_ns);

}  // namespace project

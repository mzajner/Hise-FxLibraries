#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::groovewear_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/GrooveWear/GrooveWear.h"
#include "src/airwindows/GrooveWear/GrooveWear.cpp"
#include "src/airwindows/GrooveWear/GrooveWearProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::groovewear_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(GrooveWear, groovewear_ns);

}  // namespace project

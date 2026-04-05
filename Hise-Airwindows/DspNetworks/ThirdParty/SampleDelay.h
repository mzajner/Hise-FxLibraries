#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::sampledelay_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/SampleDelay/SampleDelay.h"
#include "src/airwindows/SampleDelay/SampleDelay.cpp.inc"
#include "src/airwindows/SampleDelay/SampleDelayProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::sampledelay_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(SampleDelay, sampledelay_ns);

}  // namespace project

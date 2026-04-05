#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::clipsoftly_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ClipSoftly/ClipSoftly.h"
#include "src/airwindows/ClipSoftly/ClipSoftly.cpp.inc"
#include "src/airwindows/ClipSoftly/ClipSoftlyProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::clipsoftly_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ClipSoftly, clipsoftly_ns);

}  // namespace project

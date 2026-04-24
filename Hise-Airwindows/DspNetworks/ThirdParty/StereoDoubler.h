#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::stereodoubler_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/StereoDoubler/StereoDoubler.h"
#include "src/airwindows/StereoDoubler/StereoDoubler.cpp.inc"
#include "src/airwindows/StereoDoubler/StereoDoublerProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::stereodoubler_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(StereoDoubler, stereodoubler_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::drumslam_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/DrumSlam/DrumSlam.h"
#include "src/airwindows/DrumSlam/DrumSlam.cpp.inc"
#include "src/airwindows/DrumSlam/DrumSlamProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::drumslam_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(DrumSlam, drumslam_ns);

}  // namespace project

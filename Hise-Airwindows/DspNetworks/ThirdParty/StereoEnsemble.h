#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::stereoensemble_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/StereoEnsemble/StereoEnsemble.h"
#include "src/airwindows/StereoEnsemble/StereoEnsemble.cpp.inc"
#include "src/airwindows/StereoEnsemble/StereoEnsembleProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::stereoensemble_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(StereoEnsemble, stereoensemble_ns);

}  // namespace project

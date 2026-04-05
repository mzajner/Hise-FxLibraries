#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::multibanddistortion_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/MultiBandDistortion/MultiBandDistortion.h"
#include "src/airwindows/MultiBandDistortion/MultiBandDistortion.cpp.inc"
#include "src/airwindows/MultiBandDistortion/MultiBandDistortionProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::multibanddistortion_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(MultiBandDistortion, multibanddistortion_ns);

}  // namespace project

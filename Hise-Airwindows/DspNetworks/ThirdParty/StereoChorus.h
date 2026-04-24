#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::stereochorus_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/StereoChorus/StereoChorus.h"
#include "src/airwindows/StereoChorus/StereoChorus.cpp.inc"
#include "src/airwindows/StereoChorus/StereoChorusProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::stereochorus_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(StereoChorus, stereochorus_ns);

}  // namespace project

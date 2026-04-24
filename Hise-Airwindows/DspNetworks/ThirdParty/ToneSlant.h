#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::toneslant_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ToneSlant/ToneSlant.h"
#include "src/airwindows/ToneSlant/ToneSlant.cpp.inc"
#include "src/airwindows/ToneSlant/ToneSlantProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::toneslant_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ToneSlant, toneslant_ns);

}  // namespace project

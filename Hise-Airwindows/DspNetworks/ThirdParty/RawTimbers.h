#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::rawtimbers_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/RawTimbers/RawTimbers.h"
#include "src/airwindows/RawTimbers/RawTimbers.cpp.inc"
#include "src/airwindows/RawTimbers/RawTimbersProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::rawtimbers_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(RawTimbers, rawtimbers_ns);

}  // namespace project

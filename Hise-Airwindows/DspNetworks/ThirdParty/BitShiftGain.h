#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::bitshiftgain_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/BitShiftGain/BitShiftGain.h"
#include "src/airwindows/BitShiftGain/BitShiftGain.cpp.inc"
#include "src/airwindows/BitShiftGain/BitShiftGainProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::bitshiftgain_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(BitShiftGain, bitshiftgain_ns);

}  // namespace project

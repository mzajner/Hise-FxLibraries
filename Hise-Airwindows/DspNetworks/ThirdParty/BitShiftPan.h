#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::bitshiftpan_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/BitShiftPan/BitShiftPan.h"
#include "src/airwindows/BitShiftPan/BitShiftPan.cpp"
#include "src/airwindows/BitShiftPan/BitShiftPanProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::bitshiftpan_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(BitShiftPan, bitshiftpan_ns);

}  // namespace project

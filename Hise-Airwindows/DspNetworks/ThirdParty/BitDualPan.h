#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::bitdualpan_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/BitDualPan/BitDualPan.h"
#include "src/airwindows/BitDualPan/BitDualPan.cpp"
#include "src/airwindows/BitDualPan/BitDualPanProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::bitdualpan_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(BitDualPan, bitdualpan_ns);

}  // namespace project

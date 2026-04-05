#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::digitalblack_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/DigitalBlack/DigitalBlack.h"
#include "src/airwindows/DigitalBlack/DigitalBlack.cpp.inc"
#include "src/airwindows/DigitalBlack/DigitalBlackProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::digitalblack_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(DigitalBlack, digitalblack_ns);

}  // namespace project

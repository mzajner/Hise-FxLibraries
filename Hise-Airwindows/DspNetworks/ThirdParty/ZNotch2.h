#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::znotch2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ZNotch2/ZNotch2.h"
#include "src/airwindows/ZNotch2/ZNotch2.cpp.inc"
#include "src/airwindows/ZNotch2/ZNotch2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::znotch2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ZNotch2, znotch2_ns);

}  // namespace project

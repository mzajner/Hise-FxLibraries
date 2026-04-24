#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::tovinyl4_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ToVinyl4/ToVinyl4.h"
#include "src/airwindows/ToVinyl4/ToVinyl4.cpp.inc"
#include "src/airwindows/ToVinyl4/ToVinyl4Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::tovinyl4_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ToVinyl4, tovinyl4_ns);

}  // namespace project

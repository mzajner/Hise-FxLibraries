#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::ironoxideclassic2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/IronOxideClassic2/IronOxideClassic2.h"
#include "src/airwindows/IronOxideClassic2/IronOxideClassic2.cpp.inc"
#include "src/airwindows/IronOxideClassic2/IronOxideClassic2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ironoxideclassic2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(IronOxideClassic2, ironoxideclassic2_ns);

}  // namespace project

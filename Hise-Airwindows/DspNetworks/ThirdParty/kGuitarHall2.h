#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::kguitarhall2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/kGuitarHall2/kGuitarHall2.h"
#include "src/airwindows/kGuitarHall2/kGuitarHall2.cpp.inc"
#include "src/airwindows/kGuitarHall2/kGuitarHall2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::kguitarhall2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(kGuitarHall2, kguitarhall2_ns);

}  // namespace project

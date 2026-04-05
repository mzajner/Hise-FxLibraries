#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::pafnuty2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Pafnuty2/Pafnuty2.h"
#include "src/airwindows/Pafnuty2/Pafnuty2.cpp.inc"
#include "src/airwindows/Pafnuty2/Pafnuty2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::pafnuty2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Pafnuty2, pafnuty2_ns);

}  // namespace project

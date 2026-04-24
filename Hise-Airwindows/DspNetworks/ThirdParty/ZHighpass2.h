#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::zhighpass2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ZHighpass2/ZHighpass2.h"
#include "src/airwindows/ZHighpass2/ZHighpass2.cpp.inc"
#include "src/airwindows/ZHighpass2/ZHighpass2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::zhighpass2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ZHighpass2, zhighpass2_ns);

}  // namespace project

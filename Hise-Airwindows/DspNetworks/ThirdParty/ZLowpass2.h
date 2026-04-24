#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::zlowpass2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ZLowpass2/ZLowpass2.h"
#include "src/airwindows/ZLowpass2/ZLowpass2.cpp.inc"
#include "src/airwindows/ZLowpass2/ZLowpass2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::zlowpass2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ZLowpass2, zlowpass2_ns);

}  // namespace project

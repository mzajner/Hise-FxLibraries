#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::zlowpass_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ZLowpass/ZLowpass.h"
#include "src/airwindows/ZLowpass/ZLowpass.cpp.inc"
#include "src/airwindows/ZLowpass/ZLowpassProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::zlowpass_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ZLowpass, zlowpass_ns);

}  // namespace project

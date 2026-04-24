#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::ynothighpass_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/YNotHighpass/YNotHighpass.h"
#include "src/airwindows/YNotHighpass/YNotHighpass.cpp.inc"
#include "src/airwindows/YNotHighpass/YNotHighpassProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ynothighpass_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(YNotHighpass, ynothighpass_ns);

}  // namespace project

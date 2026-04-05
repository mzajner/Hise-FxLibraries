#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::chromeoxide_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ChromeOxide/ChromeOxide.h"
#include "src/airwindows/ChromeOxide/ChromeOxide.cpp.inc"
#include "src/airwindows/ChromeOxide/ChromeOxideProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::chromeoxide_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ChromeOxide, chromeoxide_ns);

}  // namespace project

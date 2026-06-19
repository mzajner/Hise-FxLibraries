#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::kchamberar_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/kChamberAR/kChamberAR.h"
#include "src/airwindows/kChamberAR/kChamberAR.cpp"
#include "src/airwindows/kChamberAR/kChamberARProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::kchamberar_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(kChamberAR, kchamberar_ns);

}  // namespace project

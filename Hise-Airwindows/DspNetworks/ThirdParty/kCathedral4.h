#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::kcathedral4_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/kCathedral4/kCathedral4.h"
#include "src/airwindows/kCathedral4/kCathedral4.cpp.inc"
#include "src/airwindows/kCathedral4/kCathedral4Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::kcathedral4_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(kCathedral4, kcathedral4_ns);

}  // namespace project

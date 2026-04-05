#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::kcathedral3_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/kCathedral3/kCathedral3.h"
#include "src/airwindows/kCathedral3/kCathedral3.cpp.inc"
#include "src/airwindows/kCathedral3/kCathedral3Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::kcathedral3_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(kCathedral3, kcathedral3_ns);

}  // namespace project

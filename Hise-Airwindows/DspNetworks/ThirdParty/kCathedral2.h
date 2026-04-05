#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::kcathedral2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/kCathedral2/kCathedral2.h"
#include "src/airwindows/kCathedral2/kCathedral2.cpp.inc"
#include "src/airwindows/kCathedral2/kCathedral2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::kcathedral2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(kCathedral2, kcathedral2_ns);

}  // namespace project

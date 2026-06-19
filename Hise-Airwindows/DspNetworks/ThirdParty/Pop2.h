#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::pop2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Pop2/Pop2.h"
#include "src/airwindows/Pop2/Pop2.cpp"
#include "src/airwindows/Pop2/Pop2Proc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::pop2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Pop2, pop2_ns);

}  // namespace project

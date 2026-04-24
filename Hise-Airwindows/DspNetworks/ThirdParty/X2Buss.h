#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::x2buss_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/X2Buss/X2Buss.h"
#include "src/airwindows/X2Buss/X2Buss.cpp.inc"
#include "src/airwindows/X2Buss/X2BussProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::x2buss_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(X2Buss, x2buss_ns);

}  // namespace project

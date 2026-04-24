#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::shortbuss_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ShortBuss/ShortBuss.h"
#include "src/airwindows/ShortBuss/ShortBuss.cpp.inc"
#include "src/airwindows/ShortBuss/ShortBussProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::shortbuss_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ShortBuss, shortbuss_ns);

}  // namespace project

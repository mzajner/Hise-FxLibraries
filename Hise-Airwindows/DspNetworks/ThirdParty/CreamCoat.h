#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::creamcoat_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/CreamCoat/CreamCoat.h"
#include "src/airwindows/CreamCoat/CreamCoat.cpp.inc"
#include "src/airwindows/CreamCoat/CreamCoatProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::creamcoat_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(CreamCoat, creamcoat_ns);

}  // namespace project

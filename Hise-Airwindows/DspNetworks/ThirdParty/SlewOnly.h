#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::slewonly_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/SlewOnly/SlewOnly.h"
#include "src/airwindows/SlewOnly/SlewOnly.cpp.inc"
#include "src/airwindows/SlewOnly/SlewOnlyProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::slewonly_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(SlewOnly, slewonly_ns);

}  // namespace project

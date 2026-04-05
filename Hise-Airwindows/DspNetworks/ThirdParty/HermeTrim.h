#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::hermetrim_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/HermeTrim/HermeTrim.h"
#include "src/airwindows/HermeTrim/HermeTrim.cpp.inc"
#include "src/airwindows/HermeTrim/HermeTrimProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::hermetrim_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(HermeTrim, hermetrim_ns);

}  // namespace project

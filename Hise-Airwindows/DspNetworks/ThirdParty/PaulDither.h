#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::pauldither_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PaulDither/PaulDither.h"
#include "src/airwindows/PaulDither/PaulDither.cpp.inc"
#include "src/airwindows/PaulDither/PaulDitherProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::pauldither_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PaulDither, pauldither_ns);

}  // namespace project

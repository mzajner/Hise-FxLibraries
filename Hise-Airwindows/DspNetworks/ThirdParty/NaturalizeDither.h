#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::naturalizedither_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/NaturalizeDither/NaturalizeDither.h"
#include "src/airwindows/NaturalizeDither/NaturalizeDither.cpp.inc"
#include "src/airwindows/NaturalizeDither/NaturalizeDitherProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::naturalizedither_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(NaturalizeDither, naturalizedither_ns);

}  // namespace project

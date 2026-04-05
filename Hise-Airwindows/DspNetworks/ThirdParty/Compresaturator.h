#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::compresaturator_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Compresaturator/Compresaturator.h"
#include "src/airwindows/Compresaturator/Compresaturator.cpp.inc"
#include "src/airwindows/Compresaturator/CompresaturatorProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::compresaturator_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Compresaturator, compresaturator_ns);

}  // namespace project

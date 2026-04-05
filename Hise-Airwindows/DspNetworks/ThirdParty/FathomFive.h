#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::fathomfive_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/FathomFive/FathomFive.h"
#include "src/airwindows/FathomFive/FathomFive.cpp.inc"
#include "src/airwindows/FathomFive/FathomFiveProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::fathomfive_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(FathomFive, fathomfive_ns);

}  // namespace project

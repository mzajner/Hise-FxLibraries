#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::discontinuity_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Discontinuity/Discontinuity.h"
#include "src/airwindows/Discontinuity/Discontinuity.cpp.inc"
#include "src/airwindows/Discontinuity/DiscontinuityProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::discontinuity_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Discontinuity, discontinuity_ns);

}  // namespace project

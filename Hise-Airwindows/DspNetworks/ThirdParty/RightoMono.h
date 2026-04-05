#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::rightomono_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/RightoMono/RightoMono.h"
#include "src/airwindows/RightoMono/RightoMono.cpp.inc"
#include "src/airwindows/RightoMono/RightoMonoProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::rightomono_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(RightoMono, rightomono_ns);

}  // namespace project

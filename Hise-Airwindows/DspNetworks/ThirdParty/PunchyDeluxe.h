#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::punchydeluxe_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PunchyDeluxe/PunchyDeluxe.h"
#include "src/airwindows/PunchyDeluxe/PunchyDeluxe.cpp.inc"
#include "src/airwindows/PunchyDeluxe/PunchyDeluxeProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::punchydeluxe_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PunchyDeluxe, punchydeluxe_ns);

}  // namespace project

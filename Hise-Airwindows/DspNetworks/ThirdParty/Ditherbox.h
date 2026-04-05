#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::ditherbox_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Ditherbox/Ditherbox.h"
#include "src/airwindows/Ditherbox/Ditherbox.cpp.inc"
#include "src/airwindows/Ditherbox/DitherboxProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ditherbox_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Ditherbox, ditherbox_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::pointydeluxe_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PointyDeluxe/PointyDeluxe.h"
#include "src/airwindows/PointyDeluxe/PointyDeluxe.cpp.inc"
#include "src/airwindows/PointyDeluxe/PointyDeluxeProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::pointydeluxe_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PointyDeluxe, pointydeluxe_ns);

}  // namespace project

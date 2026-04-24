#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::singleendedtriode_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/SingleEndedTriode/SingleEndedTriode.h"
#include "src/airwindows/SingleEndedTriode/SingleEndedTriode.cpp.inc"
#include "src/airwindows/SingleEndedTriode/SingleEndedTriodeProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::singleendedtriode_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(SingleEndedTriode, singleendedtriode_ns);

}  // namespace project

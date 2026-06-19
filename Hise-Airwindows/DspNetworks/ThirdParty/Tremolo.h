#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::tremolo_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Tremolo/Tremolo.h"
#include "src/airwindows/Tremolo/Tremolo.cpp"
#include "src/airwindows/Tremolo/TremoloProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::tremolo_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Tremolo, tremolo_ns);

}  // namespace project

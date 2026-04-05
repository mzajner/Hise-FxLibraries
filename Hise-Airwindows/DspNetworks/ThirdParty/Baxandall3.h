#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::baxandall3_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Baxandall3/Baxandall3.h"
#include "src/airwindows/Baxandall3/Baxandall3.cpp.inc"
#include "src/airwindows/Baxandall3/Baxandall3Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::baxandall3_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Baxandall3, baxandall3_ns);

}  // namespace project

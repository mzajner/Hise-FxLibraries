#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::baxandall2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Baxandall2/Baxandall2.h"
#include "src/airwindows/Baxandall2/Baxandall2.cpp.inc"
#include "src/airwindows/Baxandall2/Baxandall2Proc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::baxandall2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Baxandall2, baxandall2_ns);

}  // namespace project

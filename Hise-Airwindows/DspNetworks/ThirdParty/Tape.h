#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::tape_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Tape/Tape.h"
#include "src/airwindows/Tape/Tape.cpp.inc"
#include "src/airwindows/Tape/TapeProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::tape_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Tape, tape_ns);

}  // namespace project

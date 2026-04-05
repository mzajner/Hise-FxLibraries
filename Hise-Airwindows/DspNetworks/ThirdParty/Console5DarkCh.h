#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::console5darkch_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Console5DarkCh/Console5DarkCh.h"
#include "src/airwindows/Console5DarkCh/Console5DarkCh.cpp.inc"
#include "src/airwindows/Console5DarkCh/Console5DarkChProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::console5darkch_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Console5DarkCh, console5darkch_ns);

}  // namespace project

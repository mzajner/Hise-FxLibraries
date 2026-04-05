#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::consolehpre_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ConsoleHPre/ConsoleHPre.h"
#include "src/airwindows/ConsoleHPre/ConsoleHPre.cpp.inc"
#include "src/airwindows/ConsoleHPre/ConsoleHPreProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::consolehpre_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ConsoleHPre, consolehpre_ns);

}  // namespace project

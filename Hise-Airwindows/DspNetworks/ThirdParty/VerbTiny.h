#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::verbtiny_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/VerbTiny/VerbTiny.h"
#include "src/airwindows/VerbTiny/VerbTiny.cpp.inc"
#include "src/airwindows/VerbTiny/VerbTinyProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::verbtiny_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(VerbTiny, verbtiny_ns);

}  // namespace project

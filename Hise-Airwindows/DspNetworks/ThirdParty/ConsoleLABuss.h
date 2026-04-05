#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::consolelabuss_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ConsoleLABuss/ConsoleLABuss.h"
#include "src/airwindows/ConsoleLABuss/ConsoleLABuss.cpp.inc"
#include "src/airwindows/ConsoleLABuss/ConsoleLABussProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::consolelabuss_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ConsoleLABuss, consolelabuss_ns);

}  // namespace project

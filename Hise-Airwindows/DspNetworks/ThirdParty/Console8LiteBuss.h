#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::console8litebuss_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Console8LiteBuss/Console8LiteBuss.h"
#include "src/airwindows/Console8LiteBuss/Console8LiteBuss.cpp.inc"
#include "src/airwindows/Console8LiteBuss/Console8LiteBussProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::console8litebuss_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Console8LiteBuss, console8litebuss_ns);

}  // namespace project

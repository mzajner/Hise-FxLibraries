#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::triplespread_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/TripleSpread/TripleSpread.h"
#include "src/airwindows/TripleSpread/TripleSpread.cpp.inc"
#include "src/airwindows/TripleSpread/TripleSpreadProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::triplespread_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(TripleSpread, triplespread_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::tremosquare_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/TremoSquare/TremoSquare.h"
#include "src/airwindows/TremoSquare/TremoSquare.cpp.inc"
#include "src/airwindows/TremoSquare/TremoSquareProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::tremosquare_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(TremoSquare, tremosquare_ns);

}  // namespace project

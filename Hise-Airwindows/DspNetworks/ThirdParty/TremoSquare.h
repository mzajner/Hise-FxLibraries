#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::tremosquare_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/TremoSquare/TremoSquare.h"
#include "src/airwindows/TremoSquare/TremoSquare.cpp"
#include "src/airwindows/TremoSquare/TremoSquareProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::tremosquare_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(TremoSquare, tremosquare_ns);

}  // namespace project

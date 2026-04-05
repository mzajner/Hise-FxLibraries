#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::apicolypse_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Apicolypse/Apicolypse.h"
#include "src/airwindows/Apicolypse/Apicolypse.cpp.inc"
#include "src/airwindows/Apicolypse/ApicolypseProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::apicolypse_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Apicolypse, apicolypse_ns);

}  // namespace project

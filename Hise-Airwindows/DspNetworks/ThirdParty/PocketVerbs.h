#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::pocketverbs_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PocketVerbs/PocketVerbs.h"
#include "src/airwindows/PocketVerbs/PocketVerbs.cpp.inc"
#include "src/airwindows/PocketVerbs/PocketVerbsProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::pocketverbs_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PocketVerbs, pocketverbs_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::deess_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/DeEss/DeEss.h"
#include "src/airwindows/DeEss/DeEss.cpp"
#include "src/airwindows/DeEss/DeEssProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::deess_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(DeEss, deess_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::bigamp_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/BigAmp/BigAmp.h"
#include "src/airwindows/BigAmp/BigAmp.cpp"
#include "src/airwindows/BigAmp/BigAmpProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::bigamp_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(BigAmp, bigamp_ns);

}  // namespace project

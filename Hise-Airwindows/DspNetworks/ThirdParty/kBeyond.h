#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::kbeyond_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/kBeyond/kBeyond.h"
#include "src/airwindows/kBeyond/kBeyond.cpp.inc"
#include "src/airwindows/kBeyond/kBeyondProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::kbeyond_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(kBeyond, kbeyond_ns);

}  // namespace project

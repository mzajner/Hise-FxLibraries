#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::c5rawbuss_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/C5RawBuss/C5RawBuss.h"
#include "src/airwindows/C5RawBuss/C5RawBuss.cpp.inc"
#include "src/airwindows/C5RawBuss/C5RawBussProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::c5rawbuss_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(C5RawBuss, c5rawbuss_ns);

}  // namespace project

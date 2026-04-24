#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::ulawencode_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/uLawEncode/uLawEncode.h"
#include "src/airwindows/uLawEncode/uLawEncode.cpp.inc"
#include "src/airwindows/uLawEncode/uLawEncodeProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ulawencode_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(uLawEncode, ulawencode_ns);

}  // namespace project

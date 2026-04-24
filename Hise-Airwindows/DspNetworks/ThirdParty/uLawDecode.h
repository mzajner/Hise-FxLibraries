#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::ulawdecode_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/uLawDecode/uLawDecode.h"
#include "src/airwindows/uLawDecode/uLawDecode.cpp.inc"
#include "src/airwindows/uLawDecode/uLawDecodeProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ulawdecode_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(uLawDecode, ulawdecode_ns);

}  // namespace project

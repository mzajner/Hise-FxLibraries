#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::discontapeity_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Discontapeity/Discontapeity.h"
#include "src/airwindows/Discontapeity/Discontapeity.cpp.inc"
#include "src/airwindows/Discontapeity/DiscontapeityProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::discontapeity_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Discontapeity, discontapeity_ns);

}  // namespace project

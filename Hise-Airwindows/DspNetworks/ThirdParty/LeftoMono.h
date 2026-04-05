#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::leftomono_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/LeftoMono/LeftoMono.h"
#include "src/airwindows/LeftoMono/LeftoMono.cpp.inc"
#include "src/airwindows/LeftoMono/LeftoMonoProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::leftomono_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(LeftoMono, leftomono_ns);

}  // namespace project

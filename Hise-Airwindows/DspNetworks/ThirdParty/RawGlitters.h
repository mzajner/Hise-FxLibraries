#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::rawglitters_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/RawGlitters/RawGlitters.h"
#include "src/airwindows/RawGlitters/RawGlitters.cpp"
#include "src/airwindows/RawGlitters/RawGlittersProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::rawglitters_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(RawGlitters, rawglitters_ns);

}  // namespace project

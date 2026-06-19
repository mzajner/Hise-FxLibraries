#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::punchyguitar_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PunchyGuitar/PunchyGuitar.h"
#include "src/airwindows/PunchyGuitar/PunchyGuitar.cpp"
#include "src/airwindows/PunchyGuitar/PunchyGuitarProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::punchyguitar_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PunchyGuitar, punchyguitar_ns);

}  // namespace project

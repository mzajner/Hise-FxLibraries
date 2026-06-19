#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::slewsonic_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/SlewSonic/SlewSonic.h"
#include "src/airwindows/SlewSonic/SlewSonic.cpp"
#include "src/airwindows/SlewSonic/SlewSonicProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::slewsonic_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(SlewSonic, slewsonic_ns);

}  // namespace project

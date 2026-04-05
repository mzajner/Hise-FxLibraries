#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::kalienspaceship_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/kAlienSpaceship/kAlienSpaceship.h"
#include "src/airwindows/kAlienSpaceship/kAlienSpaceship.cpp.inc"
#include "src/airwindows/kAlienSpaceship/kAlienSpaceshipProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::kalienspaceship_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(kAlienSpaceship, kalienspaceship_ns);

}  // namespace project

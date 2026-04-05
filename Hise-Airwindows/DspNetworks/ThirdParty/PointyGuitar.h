#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::pointyguitar_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PointyGuitar/PointyGuitar.h"
#include "src/airwindows/PointyGuitar/PointyGuitar.cpp.inc"
#include "src/airwindows/PointyGuitar/PointyGuitarProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::pointyguitar_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PointyGuitar, pointyguitar_ns);

}  // namespace project

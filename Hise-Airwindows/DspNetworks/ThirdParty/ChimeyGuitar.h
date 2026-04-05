#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::chimeyguitar_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ChimeyGuitar/ChimeyGuitar.h"
#include "src/airwindows/ChimeyGuitar/ChimeyGuitar.cpp.inc"
#include "src/airwindows/ChimeyGuitar/ChimeyGuitarProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::chimeyguitar_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ChimeyGuitar, chimeyguitar_ns);

}  // namespace project

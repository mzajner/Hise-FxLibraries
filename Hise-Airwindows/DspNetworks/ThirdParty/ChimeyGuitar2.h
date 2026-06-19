#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::chimeyguitar2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ChimeyGuitar2/ChimeyGuitar2.h"
#include "src/airwindows/ChimeyGuitar2/ChimeyGuitar2.cpp"
#include "src/airwindows/ChimeyGuitar2/ChimeyGuitar2Proc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::chimeyguitar2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ChimeyGuitar2, chimeyguitar2_ns);

}  // namespace project

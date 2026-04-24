#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::trianglizer_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Trianglizer/Trianglizer.h"
#include "src/airwindows/Trianglizer/Trianglizer.cpp.inc"
#include "src/airwindows/Trianglizer/TrianglizerProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::trianglizer_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Trianglizer, trianglizer_ns);

}  // namespace project

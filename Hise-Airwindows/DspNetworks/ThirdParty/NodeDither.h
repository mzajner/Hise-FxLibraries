#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::nodedither_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/NodeDither/NodeDither.h"
#include "src/airwindows/NodeDither/NodeDither.cpp.inc"
#include "src/airwindows/NodeDither/NodeDitherProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::nodedither_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(NodeDither, nodedither_ns);

}  // namespace project

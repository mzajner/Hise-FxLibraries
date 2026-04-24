#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::spatializedither_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/SpatializeDither/SpatializeDither.h"
#include "src/airwindows/SpatializeDither/SpatializeDither.cpp.inc"
#include "src/airwindows/SpatializeDither/SpatializeDitherProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::spatializedither_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(SpatializeDither, spatializedither_ns);

}  // namespace project

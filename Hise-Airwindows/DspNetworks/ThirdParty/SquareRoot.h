#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::squareroot_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/SquareRoot/SquareRoot.h"
#include "src/airwindows/SquareRoot/SquareRoot.cpp.inc"
#include "src/airwindows/SquareRoot/SquareRootProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::squareroot_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(SquareRoot, squareroot_ns);

}  // namespace project

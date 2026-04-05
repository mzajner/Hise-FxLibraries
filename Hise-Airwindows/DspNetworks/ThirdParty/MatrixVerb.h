#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::matrixverb_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/MatrixVerb/MatrixVerb.h"
#include "src/airwindows/MatrixVerb/MatrixVerb.cpp.inc"
#include "src/airwindows/MatrixVerb/MatrixVerbProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::matrixverb_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(MatrixVerb, matrixverb_ns);

}  // namespace project

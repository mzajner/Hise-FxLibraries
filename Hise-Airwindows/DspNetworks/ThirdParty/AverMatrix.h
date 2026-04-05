#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::avermatrix_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/AverMatrix/AverMatrix.h"
#include "src/airwindows/AverMatrix/AverMatrix.cpp.inc"
#include "src/airwindows/AverMatrix/AverMatrixProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::avermatrix_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(AverMatrix, avermatrix_ns);

}  // namespace project

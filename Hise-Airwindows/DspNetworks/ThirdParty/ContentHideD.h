#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::contenthided_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ContentHideD/ContentHideD.h"
#include "src/airwindows/ContentHideD/ContentHideD.cpp.inc"
#include "src/airwindows/ContentHideD/ContentHideDProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::contenthided_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ContentHideD, contenthided_ns);

}  // namespace project

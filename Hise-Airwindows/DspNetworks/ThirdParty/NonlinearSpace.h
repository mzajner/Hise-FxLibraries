#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::nonlinearspace_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/NonlinearSpace/NonlinearSpace.h"
#include "src/airwindows/NonlinearSpace/NonlinearSpace.cpp.inc"
#include "src/airwindows/NonlinearSpace/NonlinearSpaceProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::nonlinearspace_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(NonlinearSpace, nonlinearspace_ns);

}  // namespace project

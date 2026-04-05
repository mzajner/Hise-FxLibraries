#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::notjustanothercd_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/NotJustAnotherCD/NotJustAnotherCD.h"
#include "src/airwindows/NotJustAnotherCD/NotJustAnotherCD.cpp.inc"
#include "src/airwindows/NotJustAnotherCD/NotJustAnotherCDProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::notjustanothercd_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(NotJustAnotherCD, notjustanothercd_ns);

}  // namespace project

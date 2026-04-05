#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::primefir_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PrimeFIR/PrimeFIR.h"
#include "src/airwindows/PrimeFIR/PrimeFIR.cpp.inc"
#include "src/airwindows/PrimeFIR/PrimeFIRProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::primefir_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PrimeFIR, primefir_ns);

}  // namespace project

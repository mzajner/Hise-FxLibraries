#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::buildatpdf_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/BuildATPDF/BuildATPDF.h"
#include "src/airwindows/BuildATPDF/BuildATPDF.cpp.inc"
#include "src/airwindows/BuildATPDF/BuildATPDFProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::buildatpdf_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(BuildATPDF, buildatpdf_ns);

}  // namespace project

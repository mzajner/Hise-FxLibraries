#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::tpdfwide_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/TPDFWide/TPDFWide.h"
#include "src/airwindows/TPDFWide/TPDFWide.cpp"
#include "src/airwindows/TPDFWide/TPDFWideProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::tpdfwide_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(TPDFWide, tpdfwide_ns);

}  // namespace project

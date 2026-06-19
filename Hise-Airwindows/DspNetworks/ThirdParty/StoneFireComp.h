#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::stonefirecomp_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/StoneFireComp/StoneFireComp.h"
#include "src/airwindows/StoneFireComp/StoneFireComp.cpp"
#include "src/airwindows/StoneFireComp/StoneFireCompProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::stonefirecomp_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(StoneFireComp, stonefirecomp_ns);

}  // namespace project

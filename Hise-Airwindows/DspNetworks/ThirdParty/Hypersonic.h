#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::hypersonic_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Hypersonic/Hypersonic.h"
#include "src/airwindows/Hypersonic/Hypersonic.cpp.inc"
#include "src/airwindows/Hypersonic/HypersonicProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::hypersonic_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Hypersonic, hypersonic_ns);

}  // namespace project

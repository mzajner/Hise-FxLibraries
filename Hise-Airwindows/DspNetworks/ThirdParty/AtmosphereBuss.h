#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::atmospherebuss_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/AtmosphereBuss/AtmosphereBuss.h"
#include "src/airwindows/AtmosphereBuss/AtmosphereBuss.cpp.inc"
#include "src/airwindows/AtmosphereBuss/AtmosphereBussProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::atmospherebuss_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(AtmosphereBuss, atmospherebuss_ns);

}  // namespace project

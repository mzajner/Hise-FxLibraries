#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::clearcoat_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ClearCoat/ClearCoat.h"
#include "src/airwindows/ClearCoat/ClearCoat.cpp"
#include "src/airwindows/ClearCoat/ClearCoatProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::clearcoat_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ClearCoat, clearcoat_ns);

}  // namespace project

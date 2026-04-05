#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::cloudcoat_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/CloudCoat/CloudCoat.h"
#include "src/airwindows/CloudCoat/CloudCoat.cpp.inc"
#include "src/airwindows/CloudCoat/CloudCoatProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::cloudcoat_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(CloudCoat, cloudcoat_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::texturizems_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/TexturizeMS/TexturizeMS.h"
#include "src/airwindows/TexturizeMS/TexturizeMS.cpp.inc"
#include "src/airwindows/TexturizeMS/TexturizeMSProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::texturizems_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(TexturizeMS, texturizems_ns);

}  // namespace project

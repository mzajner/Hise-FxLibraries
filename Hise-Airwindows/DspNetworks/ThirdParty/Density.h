#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::density_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Density/Density.h"
#include "src/airwindows/Density/Density.cpp"
#include "src/airwindows/Density/DensityProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::density_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Density, density_ns);

}  // namespace project

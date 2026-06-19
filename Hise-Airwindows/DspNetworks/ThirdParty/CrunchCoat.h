#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::crunchcoat_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/CrunchCoat/CrunchCoat.h"
#include "src/airwindows/CrunchCoat/CrunchCoat.cpp"
#include "src/airwindows/CrunchCoat/CrunchCoatProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::crunchcoat_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(CrunchCoat, crunchcoat_ns);

}  // namespace project

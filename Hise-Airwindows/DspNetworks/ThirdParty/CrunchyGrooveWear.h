#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::crunchygroovewear_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/CrunchyGrooveWear/CrunchyGrooveWear.h"
#include "src/airwindows/CrunchyGrooveWear/CrunchyGrooveWear.cpp.inc"
#include "src/airwindows/CrunchyGrooveWear/CrunchyGrooveWearProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::crunchygroovewear_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(CrunchyGrooveWear, crunchygroovewear_ns);

}  // namespace project

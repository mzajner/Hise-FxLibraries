#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::doublepaul_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/DoublePaul/DoublePaul.h"
#include "src/airwindows/DoublePaul/DoublePaul.cpp.inc"
#include "src/airwindows/DoublePaul/DoublePaulProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::doublepaul_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(DoublePaul, doublepaul_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::wolfbot_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Wolfbot/Wolfbot.h"
#include "src/airwindows/Wolfbot/Wolfbot.cpp.inc"
#include "src/airwindows/Wolfbot/WolfbotProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::wolfbot_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Wolfbot, wolfbot_ns);

}  // namespace project

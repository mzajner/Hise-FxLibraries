#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::kwoodroom_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/kWoodRoom/kWoodRoom.h"
#include "src/airwindows/kWoodRoom/kWoodRoom.cpp"
#include "src/airwindows/kWoodRoom/kWoodRoomProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::kwoodroom_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(kWoodRoom, kwoodroom_ns);

}  // namespace project

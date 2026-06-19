#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::blockparty_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/BlockParty/BlockParty.h"
#include "src/airwindows/BlockParty/BlockParty.cpp"
#include "src/airwindows/BlockParty/BlockPartyProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::blockparty_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(BlockParty, blockparty_ns);

}  // namespace project

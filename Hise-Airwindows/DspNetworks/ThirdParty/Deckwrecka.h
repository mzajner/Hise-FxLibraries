#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::deckwrecka_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Deckwrecka/Deckwrecka.h"
#include "src/airwindows/Deckwrecka/Deckwrecka.cpp.inc"
#include "src/airwindows/Deckwrecka/DeckwreckaProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::deckwrecka_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Deckwrecka, deckwrecka_ns);

}  // namespace project

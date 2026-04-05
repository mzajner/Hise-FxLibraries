#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::pyewacket_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Pyewacket/Pyewacket.h"
#include "src/airwindows/Pyewacket/Pyewacket.cpp.inc"
#include "src/airwindows/Pyewacket/PyewacketProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::pyewacket_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Pyewacket, pyewacket_ns);

}  // namespace project

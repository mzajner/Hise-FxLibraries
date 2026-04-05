#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::notjustanotherdither_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/NotJustAnotherDither/NotJustAnotherDither.h"
#include "src/airwindows/NotJustAnotherDither/NotJustAnotherDither.cpp.inc"
#include "src/airwindows/NotJustAnotherDither/NotJustAnotherDitherProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::notjustanotherdither_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(NotJustAnotherDither, notjustanotherdither_ns);

}  // namespace project

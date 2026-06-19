#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::biquadtriple_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/BiquadTriple/BiquadTriple.h"
#include "src/airwindows/BiquadTriple/BiquadTriple.cpp"
#include "src/airwindows/BiquadTriple/BiquadTripleProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::biquadtriple_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(BiquadTriple, biquadtriple_ns);

}  // namespace project

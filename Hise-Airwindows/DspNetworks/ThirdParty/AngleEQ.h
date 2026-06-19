#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::angleeq_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/AngleEQ/AngleEQ.h"
#include "src/airwindows/AngleEQ/AngleEQ.cpp"
#include "src/airwindows/AngleEQ/AngleEQProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::angleeq_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(AngleEQ, angleeq_ns);

}  // namespace project

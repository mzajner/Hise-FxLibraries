#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::mackeq_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/MackEQ/MackEQ.h"
#include "src/airwindows/MackEQ/MackEQ.cpp"
#include "src/airwindows/MackEQ/MackEQProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::mackeq_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(MackEQ, mackeq_ns);

}  // namespace project

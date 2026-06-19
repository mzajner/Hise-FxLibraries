#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::chorusensemble_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ChorusEnsemble/ChorusEnsemble.h"
#include "src/airwindows/ChorusEnsemble/ChorusEnsemble.cpp"
#include "src/airwindows/ChorusEnsemble/ChorusEnsembleProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::chorusensemble_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ChorusEnsemble, chorusensemble_ns);

}  // namespace project

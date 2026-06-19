#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::ensemble_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/Ensemble/Ensemble.h"
#include "src/airwindows/Ensemble/Ensemble.cpp"
#include "src/airwindows/Ensemble/EnsembleProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ensemble_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Ensemble, ensemble_ns);

}  // namespace project

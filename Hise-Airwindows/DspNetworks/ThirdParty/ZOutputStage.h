#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::zoutputstage_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/ZOutputStage/ZOutputStage.h"
#include "src/airwindows/ZOutputStage/ZOutputStage.cpp"
#include "src/airwindows/ZOutputStage/ZOutputStageProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::zoutputstage_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ZOutputStage, zoutputstage_ns);

}  // namespace project

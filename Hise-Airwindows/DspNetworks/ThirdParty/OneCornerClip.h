#pragma once

#include <JuceHeader.h>
#include "src/airwindows/AirWindows.h"

namespace airwindows::onecornerclip_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/OneCornerClip/OneCornerClip.h"
#include "src/airwindows/OneCornerClip/OneCornerClip.cpp"
#include "src/airwindows/OneCornerClip/OneCornerClipProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::onecornerclip_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(OneCornerClip, onecornerclip_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::aquickvoiceclip_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/AQuickVoiceClip/AQuickVoiceClip.h"
#include "src/airwindows/AQuickVoiceClip/AQuickVoiceClip.cpp.inc"
#include "src/airwindows/AQuickVoiceClip/AQuickVoiceClipProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::aquickvoiceclip_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(AQuickVoiceClip, aquickvoiceclip_ns);

}  // namespace project

#pragma once

#include "../Binaries/JuceLibraryCode/JuceHeader.h"
#include "src/airwindows/AirWindows.h"

namespace airwindows::podcastdeluxe_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "src/airwindows/PodcastDeluxe/PodcastDeluxe.h"
#include "src/airwindows/PodcastDeluxe/PodcastDeluxe.cpp.inc"
#include "src/airwindows/PodcastDeluxe/PodcastDeluxeProc.cpp.inc"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::podcastdeluxe_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PodcastDeluxe, podcastdeluxe_ns);

}  // namespace project

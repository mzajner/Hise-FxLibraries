/*
 ==========================| ASPIK Unified Namespace Header |==========================
 
 This header provides a unified namespace for all ASPIK-based effects in HISE.
 Include this once in your project to access all ASPIK functionality.
 
 Based on Will Pirkle's "Designing Audio Effect Plugins in C++"
 Location: DspNetworks/ThirdParty/Aspik/aspik.h
 
 Usage in other effects:
 - Include this header: #include "../Aspik/aspik.h"
 - Add using statement: using namespace aspik;
 - Use objects directly: AudioFilter, AudioFilterParameters, filterAlgorithm::kLPF1, etc.
 */

#pragma once

#include <JuceHeader.h>

// Aspik Namespace
namespace aspik {

#include "fxobjects.h"

#ifndef FXOBJECTS_CPP_INCLUDED
#include "fxobjects.cpp"
#define FXOBJECTS_CPP_INCLUDED
#endif

} // namespace aspik

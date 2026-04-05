//
//  ExampleChains.h
//
//  Basic examples for creating circuit chains
//
//
#include "PedalCircuits.h"
#include "EQCircuits.h"
#include "FilterCircuits.h"
#include "Lite.h"
#include "ClippingCircuits.h"

#pragma once
namespace PointToPoint {

// ---------------- THESE ARE EXAMPLES, ADD YOUR OWN CHAINS BELOW THESE

//------ LPFClipper

class LPFClipper : public CircuitChain
{
//  Input --->[ LPF ]--->[ Diode Soft Clipper (Silicon) ]---> Output
public:
    
    LPFClipper(){
    
        circuitChain.emplace_back(new ButterworthSallenKeyLPF_2kHz);
        circuitChain.emplace_back(new DiodeSoftSI);
        
    }
};


//------ LPFClipper2

class LPFClipper2 : public CircuitChain
{
//          [LPFClipper:CircuitChain]->[Circuit]
//  Input --->[ LPF ]--->[ Clipper ]--->[ LPF ]---> Output
public:
    
    LPFClipper2(){
        
        circuitChain.emplace_back(new LPFClipper);
        circuitChain.emplace_back(new ButterworthSallenKeyLPF_8kHz);
    }
};


class HPF_LPF_Notch : public CircuitChain

{
    // The class demonstrates how to handle multiple parameters
    // with circuit chains. For this chain, the first circuit
    // is a HPF and LPF. Parameter 1 controls the frequency
    // of the HPF. Parameter 2 conterols the frequency of the
    // LPF. The second circuit is a notch filter. It has one
    // parameter for the frequency of the notch.
    // When setting the parameters for the entire circuit chain,
    // an array with size 3 should be passed into the
    // function "setParametersWithSmoothing." This function
    // will use the parameters in order for the potentiometers
    // in the first circuit. Any parameters which weren't used
    // in the first circuit will be passed into the second circuit
    // to be used. In general, the parameters are used in the order
    // of the circuits in the chain.
public:
    HPF_LPF_Notch() {
        circuitChain.emplace_back(new HPFLPFCombo);
        circuitChain.emplace_back(new BridgedTNotchFilter);
        
    }
    
    
    
};

class BigMuffTone_ThreeFilters : public CircuitChain

{
    // The class demonstrates how to handle multiple parameters
    // with circuit chains. For this chain, the tone section from the Big Muff
    // pedal is used first. It has one parameter for the tone control. Then a
    // separate circuit chain is used with a HPF, LPF, and Notch filter.
    // The circuit chain has a total of three parameters (see HPF_LPF_Notch for more).
    // Therefore, this entire circuit chain has four parameters. When updating the
    // parameters for the entire circuit chain, you should create an array of values
    // in order based on the individual circuits making up the chain.
public:
    BigMuffTone_ThreeFilters() {
        circuitChain.emplace_back(new BigMuffToneStage);
        circuitChain.emplace_back(new HPF_LPF_Notch);
    }
    
    
    
};

// End of namespace
}




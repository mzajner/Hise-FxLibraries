//
//  AmpTonestacks.h
//
//  Collection of tonestack circuits from guitar amps (e.g. Fender Bassman, Vox, etc)
//
//
#include "Circuit.h"
#include "CircuitModel.h"
#include "CircuitElement.h"

#pragma once
namespace PointToPoint {

// -------------------- Acoustic117ToneStack --------------------
class Acoustic117ToneStack : public Circuit
{
public:
    Acoustic117ToneStack() {
        layout.numNodes = 6;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {39e3, 1, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Capacitor C1 {560e-12, 1, 2};
        CircuitElement::Capacitor C2 {0.15e-6, 3, 5};
        CircuitElement::Capacitor C3 {0.15e-6, 3, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        // Bass Pot
        CircuitElement::VariableResistor VrB {100e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 6, 1};
        
        // Mid Pot
        CircuitElement::VariableResistor VrM {4e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 0, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrM};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {100e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 4, 5, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- Acoustic118ToneStack --------------------
class Acoustic118ToneStack : public Circuit
{
public:
    Acoustic118ToneStack() {
        layout.numNodes = 6;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {39e3, 1, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Capacitor C1 {560e-12, 1, 2};
        CircuitElement::Capacitor C2 {0.12e-6, 3, 5};
        CircuitElement::Capacitor C3 {0.12e-6, 3, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        // Bass Pot
        CircuitElement::VariableResistor VrB {100e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 6, 1};
        
        // Mid Pot
        CircuitElement::VariableResistor VrM {4e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 0, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrM};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {100e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 4, 5, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- Acoustic165ToneStack --------------------
class Acoustic165ToneStack : public Circuit
{
public:
    Acoustic165ToneStack() {
        layout.numNodes = 8;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {8, 0};
        
        CircuitElement::Resistor R1 {100e3, 1, 4};
        CircuitElement::Resistor R2 {100e3, 3, 7};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {250e-12, 1, 2};
        CircuitElement::Capacitor C2 {0.1e-6, 4, 5};
        CircuitElement::Capacitor C3 {0.047e-6, 4, 6};
        CircuitElement::Capacitor C4 {150e-12, 7, 8};
        CircuitElement::Capacitor C5 {27e-12, 8, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5};

        // Bass Pot
        CircuitElement::VariableResistor VrB {250e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 6, 1};
        
        // Mid Pot
        CircuitElement::VariableResistor VrM {10e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 0, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrM};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {250e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 5, 0.55};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 4,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        7, 8, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT, PtV};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- AmpegB15PortaflexToneStack --------------------
class AmpegB15PortaflexToneStack : public Circuit
{
public:
    AmpegB15PortaflexToneStack() {
        layout.numNodes = 8;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {8, 0};
        
        CircuitElement::Resistor R1 {220e3, 1, 2};
        CircuitElement::Resistor R2 {120e3, 3, 7};
        CircuitElement::Resistor R3 {270e3, 3, 0};
        CircuitElement::Resistor R4 {22e3, 4, 0};
        CircuitElement::Resistor R5 {270e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {0.001e-6, 2, 3};
        CircuitElement::Capacitor C2 {0.01e-6, 3, 4};
        CircuitElement::Capacitor C3 {47e-12, 1, 6};
        CircuitElement::Capacitor C4 {470e-12, 0, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4};
        
        // Bass Pot
        CircuitElement::Potentiometer PtB {1e6, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 4, 1};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {1e6, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 7, 5, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtT};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- AmpegBA115AToneStack --------------------
class AmpegBA115AToneStack : public Circuit
{
public:
    AmpegBA115AToneStack() {
        layout.numNodes = 13;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {13, 0};
        
        CircuitElement::Resistor R1 {4.7e3, 3, 4};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {2.2e3, 2, 5};
        CircuitElement::Resistor R4 {2.2e3, 7, 8};
        CircuitElement::Resistor R5 {4.7e3, 8, 0};
        CircuitElement::Resistor R6 {47e3, 9, 11};
        CircuitElement::Resistor R7 {100e3, 10, 0};
        CircuitElement::Resistor R8 {22e3, 11, 12};
        CircuitElement::Resistor R9 {22e3, 13, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8, R9};
        
        CircuitElement::Capacitor C1 {1e-6, 4, 7};
        CircuitElement::Capacitor C2 {100e-12, 2, 3};
        CircuitElement::Capacitor C3 {2.2e-6, 5, 6};
        CircuitElement::Capacitor C4 {0.033e-6, 8, 9};
        CircuitElement::Capacitor C5 {0.033e-6, 9, 10};
        CircuitElement::Capacitor C6 {0.22e-6, 12, 13};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5, C6};
        
        CircuitElement::OPAmp OP1 {1, 2, 3};
        CircuitElement::OPAmp OP2 {10, 11, 11};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {50e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 0, 7, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- AmpegBA115BToneStack --------------------
class AmpegBA115BToneStack : public Circuit
{
public:
    AmpegBA115BToneStack() {
        layout.numNodes = 10;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {10, 0};
        
        CircuitElement::Resistor R1 {4.7e3, 3, 4};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {2.2e3, 2, 5};
        CircuitElement::Resistor R4 {47e3, 7, 9};
        CircuitElement::Resistor R5 {22e3, 7, 8};
        CircuitElement::Resistor R6 {22e3, 10, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6};
        
        CircuitElement::Capacitor C1 {1e-6, 4, 7};
        CircuitElement::Capacitor C2 {100e-12, 2, 3};
        CircuitElement::Capacitor C3 {2.2e-6, 5, 6};
        CircuitElement::Capacitor C4 {0.015e-6, 8, 9};
        CircuitElement::Capacitor C5 {0.22e-6, 9, 10};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5};
        
        CircuitElement::OPAmp OP1 {1, 2, 3};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {50e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 0, 7, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- AmpegBA115CToneStack --------------------
class AmpegBA115CToneStack : public Circuit
{
public:
    AmpegBA115CToneStack() {
        layout.numNodes = 9;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {9, 0};
        
        CircuitElement::Resistor R1 {4.7e3, 3, 4};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {2.2e3, 2, 5};
        CircuitElement::Resistor R4 {47e3, 7, 8};
        CircuitElement::Resistor R5 {22e3, 9, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {1e-6, 4, 7};
        CircuitElement::Capacitor C2 {100e-12, 2, 3};
        CircuitElement::Capacitor C3 {2.2e-6, 5, 6};
        CircuitElement::Capacitor C4 {0.22e-6, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4};
        
        CircuitElement::OPAmp OP1 {1, 2, 3};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {50e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 0, 7, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};
        
        circuit = CircuitModel(layout);
    }
};



// -------------------- AmpegBA115DToneStack --------------------
class AmpegBA115DToneStack : public Circuit
{
public:
    AmpegBA115DToneStack() {
        layout.numNodes = 11;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {11, 0};
        
        CircuitElement::Resistor R1 {4.7e3, 3, 4};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {2.2e3, 2, 5};
        CircuitElement::Resistor R4 {22e3, 7, 8};
        CircuitElement::Resistor R5 {22e3, 8, 9};
        CircuitElement::Resistor R6 {22e3, 9, 10};
        CircuitElement::Resistor R7 {47e3, 11, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7};
        
        CircuitElement::Capacitor C1 {1e-6, 4, 7};
        CircuitElement::Capacitor C2 {100e-12, 2, 3};
        CircuitElement::Capacitor C3 {2.2e-6, 5, 6};
        CircuitElement::Capacitor C4 {0.0047e-6, 7, 9};
        CircuitElement::Capacitor C5 {0.047e-6, 8, 0};
        CircuitElement::Capacitor C6 {0.22e-6, 10, 11};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5, C6};
        
        CircuitElement::OPAmp OP1 {1, 2, 3};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {50e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 0, 7, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};

        circuit = CircuitModel(layout);
    }
};


// -------------------- AmpegBA115EToneStack --------------------
class AmpegBA115EToneStack : public Circuit
{
public:
    AmpegBA115EToneStack() {
        layout.numNodes = 11;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {11, 0};
        
        CircuitElement::Resistor R1 {4.7e3, 3, 4};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {2.2e3, 2, 5};
        CircuitElement::Resistor R4 {47e3, 7, 8};
        CircuitElement::Resistor R5 {47e3, 8, 9};
        CircuitElement::Resistor R6 {22e3, 9, 10};
        CircuitElement::Resistor R7 {47e3, 11, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7};
        
        CircuitElement::Capacitor C1 {1e-6, 4, 7};
        CircuitElement::Capacitor C2 {100e-12, 2, 3};
        CircuitElement::Capacitor C3 {2.2e-6, 5, 6};
        CircuitElement::Capacitor C4 {0.001e-6, 7, 9};
        CircuitElement::Capacitor C5 {0.047e-6, 8, 0};
        CircuitElement::Capacitor C6 {0.22e-6, 10, 11};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5, C6};
        
        CircuitElement::OPAmp OP1 {1, 2, 3};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {50e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 0, 7, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- AriaToneStack --------------------
class AriaToneStack : public Circuit
{
public:
    AriaToneStack() {
        layout.numNodes = 8;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {8, 0};
        
        CircuitElement::Resistor R1 {1e3, 1, 2};
        CircuitElement::Resistor R2 {33e3, 2, 3};
        CircuitElement::Resistor R3 {220e3, 7, 8};
        CircuitElement::Resistor R4 {100e3, 4, 8};
        CircuitElement::Resistor R5 {1e6, 5, 8};
        CircuitElement::Resistor R6 {1e6, 8, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6};
        
        CircuitElement::Capacitor C1 {1e-9, 2, 6};
        CircuitElement::Capacitor C2 {220e-9, 3, 0};
        CircuitElement::Capacitor C3 {1e-9, 7, 8};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
        
        // Bass Pot
        CircuitElement::Potentiometer PtB {100e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 4, 0, 1};
        
        // Mid Pot
        CircuitElement::Potentiometer PtM {100e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 5, 0, 1};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {100e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 7, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtM, PtT};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- BadCatHotcat30ToneStack --------------------
class BadCatHotcat30ToneStack : public Circuit
{
public:
    BadCatHotcat30ToneStack() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};
        
        CircuitElement::Resistor R1 {100e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 4, 0};
        CircuitElement::Resistor R3 {1e3, 6, 7};
        CircuitElement::Resistor R4 {56e3, 1, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};
        
        CircuitElement::Capacitor C1 {50e-12, 1, 3};
        CircuitElement::Capacitor C2 {22e-9, 2, 4};
        CircuitElement::Capacitor C3 {22e-9, 2, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
        
        // Volume Pot
        CircuitElement::VariableResistor VrV {1e6, 3,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        7, 0, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrV};
        
        // Bass Pot
        CircuitElement::Potentiometer PtB {1.5e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LOG,
                        5, 4, 0, 1};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {1e6, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 6, 5, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtT};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- BlackstarHT5ToneStack --------------------
class BlackstarHT5ToneStack : public Circuit
{
public:
    BlackstarHT5ToneStack() {
        layout.numNodes = 12;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {12, 0};
        
        CircuitElement::Resistor R1 {47e3, 2, 0};
        CircuitElement::Resistor R2 {4.7e3, 5, 6};
        CircuitElement::Resistor R3 {6.8e3, 4, 7};
        CircuitElement::Resistor R4 {22e3, 3, 8};
        CircuitElement::Resistor R5 {1e3, 9, 10};
        CircuitElement::Resistor R6 {470e3, 12, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6};
        
        CircuitElement::Capacitor C1 {22e-6, 1, 2};
        CircuitElement::Capacitor C2 {220e-9, 6, 0};
        CircuitElement::Capacitor C3 {470e-9, 2, 4};
        CircuitElement::Capacitor C4 {4.7e-9, 2, 3};
        CircuitElement::Capacitor C5 {220e-9, 7, 9};
        CircuitElement::Capacitor C6 {100e-9, 11, 12};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5, C6};
        
        // Bass Pot
        CircuitElement::VariableResistor VrB {100e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        10, 0, 1};
        
        // Mid Pot
        CircuitElement::VariableResistor VrM {2.2e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        7, 6, 1};
        
        // ISF Pot
        CircuitElement::VariableResistor VrI {10e3, 4,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        8, 9, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrM, VrI};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {47e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 11, 9, 1};
        
        // ISF Pot
        CircuitElement::Potentiometer PtI {10e3, 4,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 4, 5, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT, PtI};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- BognerEcstasyToneStack --------------------
class BognerEcstasyToneStack : public Circuit
{
public:
    BognerEcstasyToneStack() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {33e3, 1, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Capacitor C1 {470e-12, 1, 2};
        CircuitElement::Capacitor C2 {0.022e-6, 3, 5};
        CircuitElement::Capacitor C3 {0.022e-6, 3, 7};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
        
        // Bass Pot
        CircuitElement::VariableResistor VrB {1e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 6, 0};
    
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB};
        
        // Mid Pot
        CircuitElement::Potentiometer PtM {25e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 7, 0, 1};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {250e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 4, 5, 0};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtM, PtT};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- BoneRayToneStack --------------------
class BoneRayToneStack : public Circuit
{
public:
    BoneRayToneStack() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {38e3, 1, 2};
        CircuitElement::Resistor R2 {470e3, 3, 0};
        CircuitElement::Resistor R3 {470e3, 2, 6};
        CircuitElement::Resistor R4 {1e6, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};
        
        CircuitElement::Capacitor C1 {220e-12, 2, 3};
        CircuitElement::Capacitor C2 {1e-9, 6, 7};
        CircuitElement::Capacitor C3 {4.7e-9, 7, 0};
        CircuitElement::Capacitor C4 {4.7e-9, 4, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4};
        
        // Mid Pot
        CircuitElement::Potentiometer PtM {1e6, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 6, 7, 0.5};
        
        // Tilt Pot
        CircuitElement::Potentiometer PtTi {1e6, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 4, 6, 0.6};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtM, PtTi};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- CrateToneStack --------------------
class CrateToneStack : public Circuit
{
public:
    CrateToneStack() {
        layout.numNodes = 9;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};
        
        CircuitElement::Resistor R1 {1e3, 1, 2};
        CircuitElement::Resistor R2 {68e3, 2, 5};
        CircuitElement::Resistor R3 {47e3, 9, 0};
        CircuitElement::Resistor R4 {22e3, 3, 4};
        CircuitElement::Resistor R5 {10e3, 8, 0};
        CircuitElement::Resistor R6 {1e6, 7, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6};
        
        CircuitElement::Capacitor C1 {220e-12, 2, 3};
        CircuitElement::Capacitor C2 {47e-9, 5, 6};
        CircuitElement::Capacitor C3 {220e-9, 5, 9};
        CircuitElement::Capacitor C4 {4.7e-9, 9, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4};
        
        // Bass Pot
        CircuitElement::VariableResistor VrB {250e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 8, 1};
        
        // Mid Pot
        CircuitElement::VariableResistor VrM {50e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        9, 0, 1};
    
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrM};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {250e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 7, 6, 0.35};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- DrZToneStack --------------------
class DrZToneStack : public Circuit
{
public:
    DrZToneStack() {
        layout.numNodes = 5;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {38e3, 1, 2};
        CircuitElement::Resistor R2 {330e3, 3, 5};
        CircuitElement::Resistor R3 {330e3, 4, 5};
        CircuitElement::Resistor R4 {1e6, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};
        
        CircuitElement::Capacitor C1 {10e-9, 2, 3};
        CircuitElement::Capacitor C2 {120e-12, 3, 4};
        CircuitElement::Capacitor C3 {4700e-12, 5, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
        
        // Tone Pot
        CircuitElement::Potentiometer PtTo {1e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 5, 0, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtTo};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- DumbleJazzToneStack --------------------

class DumbleJazzToneStack : public Circuit
{
public:
    DumbleJazzToneStack() {
        layout.numNodes = 12;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {10, 0};

        CircuitElement::Resistor R1 {40e3, 1, 2};
        CircuitElement::Resistor R2 {150e3, 2, 4};
        CircuitElement::Resistor R3 {10e3, 8, 0};
        CircuitElement::Resistor R4 {4.7e6, 3, 0};
        CircuitElement::Resistor R5 {100e3, 7, 9};
        CircuitElement::Resistor R6 {1e6, 10, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6};

        CircuitElement::Capacitor C1 {2e-9, 2, 3};
        CircuitElement::Capacitor C2 {100e-9, 4, 6};
        CircuitElement::Capacitor C3 {10e-9, 4, 5};
        CircuitElement::Capacitor C4 {4.7e-9, 11, 0};
        CircuitElement::Capacitor C5 {390e-12, 3, 12};
        CircuitElement::Capacitor C6 {220e-12, 9, 10};
        CircuitElement::Capacitor C7 {1e-9, 6, 8};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5, C6, C7};

        // Mid Pot
        CircuitElement::VariableResistor VrM {250e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 0, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrM};

        // Bass Pot
        CircuitElement::Potentiometer PtB {312e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 7, 8, 1};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {270e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        12, 9, 11, 0.85};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 4,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        9, 10, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtT, PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- DumbleRockToneStack --------------------

class DumbleRockToneStack : public Circuit
{
public:
    DumbleRockToneStack() {
        layout.numNodes = 10;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {10, 0};

        CircuitElement::Resistor R1 {40e3, 1, 2};
        CircuitElement::Resistor R2 {150e3, 2, 4};
        CircuitElement::Resistor R3 {10e3, 7, 0};
        CircuitElement::Resistor R4 {4.7e6, 3, 0};
        CircuitElement::Resistor R5 {1e6, 10, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};

        CircuitElement::Capacitor C1 {2e-9, 2, 3};
        CircuitElement::Capacitor C2 {100e-9, 4, 6};
        CircuitElement::Capacitor C3 {10e-9, 4, 5};
        CircuitElement::Capacitor C4 {1e-9, 6, 7};
        CircuitElement::Capacitor C5 {390e-12, 3, 9};
        CircuitElement::Capacitor C6 {220e-12, 8, 10};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5, C6};

        // Bass Pot
        CircuitElement::VariableResistor VrB {312e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 7, 0.8};
        
        // Mid Pot
        CircuitElement::VariableResistor VrM {250e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 0, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrM};

        // Treble Pot
        CircuitElement::Potentiometer PtT {270e3, 3,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 8, 9, 0.5};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 4,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        8, 10, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT, PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- EpiphoneEA32RVTToneStack --------------------

class EpiphoneEA32RVTToneStack : public Circuit
{
public:
    EpiphoneEA32RVTToneStack() {
        layout.numNodes = 6;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};

        CircuitElement::Resistor R1 {470e3, 1, 0};
        CircuitElement::Resistor R2 {220e3, 2, 3};
        CircuitElement::Resistor R3 {220e3, 3, 4};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::Capacitor C1 {0.001e-6, 1, 2};
        CircuitElement::Capacitor C2 {500e-12, 2, 4};
        CircuitElement::Capacitor C3 {0.003e-6, 3, 0};
        CircuitElement::Capacitor C4 {0.0047e-6, 6, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4};

        // Bass Pot
        CircuitElement::VariableResistor VrB {2e6, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        1, 2, 1};
        
        // Treble Pot
        CircuitElement::VariableResistor VrT {2e6, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LOG,
                        4, 6, 0.75};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrT};

        // Volume Pot
        CircuitElement::Potentiometer PtV {500e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 5, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- FenderBassmanToneStack --------------------

class FenderBassmanToneStack : public Circuit
{
public:
    FenderBassmanToneStack() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};

        CircuitElement::Resistor R1 {1300, 1, 2};
        CircuitElement::Resistor R2 {56e3, 2, 4};
        CircuitElement::Resistor R3 {1e6, 7, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::Capacitor C1 {250e-12, 2, 3};
        CircuitElement::Capacitor C2 {20e-9, 4, 5};
        CircuitElement::Capacitor C3 {20e-9, 4, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        // Bass Pot
        CircuitElement::VariableResistor VrB {1e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 6, 1};
        
        // Mid Pot
        CircuitElement::VariableResistor VrM {25e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 0, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrM};

        // Treble Pot
        CircuitElement::Potentiometer PtT {250e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 7, 5, 0.75};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT};

        circuit = CircuitModel(layout);
    }
};

// -------------------- FenderBlondeTwinToneStack --------------------

class FenderBlondeTwinToneStack : public Circuit
{
public:
    FenderBlondeTwinToneStack() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};

        CircuitElement::Resistor R1 {180e3, 1, 3};
        CircuitElement::Resistor R2 {10e3, 5, 0};
        CircuitElement::Resistor R3 {70e3, 4, 6};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::Capacitor C1 {0.25e-9, 1, 2};
        CircuitElement::Capacitor C2 {1e-9, 3, 4};
        CircuitElement::Capacitor C3 {10e-9, 4, 5};
        CircuitElement::Capacitor C4 {50e-9, 7, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4};

        // Bass Pot
        CircuitElement::Potentiometer PtB {1e6, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 4, 5, 1};
        
        // Treble Pot
        CircuitElement::Potentiometer PtV {350e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 6, 7, 0.8};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- FenderBrownFaceToneStack --------------------

class FenderBrownFaceToneStack : public Circuit
{
public:
    FenderBrownFaceToneStack() {
        layout.numNodes = 8;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};

        CircuitElement::Resistor R1 {38e3, 1, 2};
        CircuitElement::Resistor R2 {100e3, 2, 4};
        CircuitElement::Resistor R3 {6.8e3, 6, 0};
        CircuitElement::Resistor R4 {1e6, 5, 0};
        CircuitElement::Resistor R5 {70e3, 8, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};

        CircuitElement::Capacitor C1 {250e-12, 2, 3};
        CircuitElement::Capacitor C2 {100e-9, 4, 8};
        CircuitElement::Capacitor C3 {100e-9, 4, 6};
        CircuitElement::Capacitor C4 {5e-9, 7, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4};

        // Bass Pot
        CircuitElement::VariableResistor VrB {250e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        8, 6, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {350e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 5, 7, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT};

        circuit = CircuitModel(layout);
    }
};

// -------------------- FenderESeriesToneStack --------------------

class FenderESeriesToneStack : public Circuit
{
public:
    FenderESeriesToneStack() {
        layout.numNodes = 8;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};

        CircuitElement::Resistor R1 {1300, 1, 2};
        CircuitElement::Resistor R2 {220e3, 3, 0};
        CircuitElement::Resistor R3 {100e3, 3, 4};
        CircuitElement::Resistor R4 {220e3, 4, 6};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};

        CircuitElement::Capacitor C1 {10e-9, 8, 0};
        CircuitElement::Capacitor C2 {250e-12, 2, 7};
        CircuitElement::Capacitor C3 {100e-9, 2, 3};
        CircuitElement::Capacitor C4 {5e-9, 5, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4};

        // Bass Pot
        CircuitElement::Potentiometer PtB {1e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        0, 4, 5, 1};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {1e6, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        7, 6, 8, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtT};

        circuit = CircuitModel(layout);
    }
};

// -------------------- FenderPrinceton5E2ToneStack --------------------

class FenderPrinceton5E2ToneStack : public Circuit
{
public:
    FenderPrinceton5E2ToneStack() {
        layout.numNodes = 7;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};

        CircuitElement::Resistor R1 {38e3, 1, 2};
        CircuitElement::Resistor R2 {100e3, 5, 4};
        CircuitElement::Resistor R3 {1e6, 7, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::Capacitor C1 {500e-12, 2, 3};
        CircuitElement::Capacitor C2 {5e-9, 6, 0};
        CircuitElement::Capacitor C3 {20e-9, 2, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        // Tone Pot
        CircuitElement::Potentiometer PtTo {250e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 4, 6, 0.65};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 7, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtTo, PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- FenderPrinceton5F2AToneStack --------------------

class FenderPrinceton5F2AToneStack : public Circuit
{
public:
    FenderPrinceton5F2AToneStack() {
        layout.numNodes = 6;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};

        CircuitElement::Resistor R1 {38e3, 1, 2};
        CircuitElement::Resistor R2 {1e6, 5, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};

        CircuitElement::Capacitor C1 {22e-9, 2, 3};
        CircuitElement::Capacitor C2 {4.7e-9, 4, 0};
        CircuitElement::Capacitor C3 {500e-12, 6, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        // Tone Pot
        CircuitElement::Potentiometer PtTo {1e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 3, 6, 0.5};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 5, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtTo, PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- FenderTMBToneStack --------------------

class FenderTMBToneStack : public Circuit
{
public:
    FenderTMBToneStack() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};

        CircuitElement::Resistor R1 {39e3, 1, 2};
        CircuitElement::Resistor R2 {100e3, 2, 4};
        CircuitElement::Resistor R3 {1e6, 7, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::Capacitor C1 {250e-12, 2, 3};
        CircuitElement::Capacitor C2 {100e-9, 4, 5};
        CircuitElement::Capacitor C3 {47e-9, 4, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
        
        // Bass Pot
        CircuitElement::VariableResistor VrB {250e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 6, 1};
        
        // Mid Pot
        CircuitElement::VariableResistor VrM {10e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 0, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrM};

        // Treble Pot
        CircuitElement::Potentiometer PtT {250e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 7, 5, 0.75};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT};

        circuit = CircuitModel(layout);
    }
};

// -------------------- FramusToneStack --------------------

class FramusToneStack : public Circuit
{
public:
    FramusToneStack() {
        layout.numNodes = 5;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};

        CircuitElement::Resistor R1 {1e3, 1, 2};
        CircuitElement::Resistor R2 {100e3, 3, 0};
        CircuitElement::Resistor R3 {1e6, 5, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::Capacitor C1 {1e-9, 2, 3};
        CircuitElement::Capacitor C2 {1e-9, 3, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        // Mid Pot
        CircuitElement::Potentiometer PtM {1e6, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 5, 4, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtM};

        circuit = CircuitModel(layout);
    }
};

// -------------------- GibsonGA5TToneStack --------------------

class GibsonGA5TToneStack : public Circuit
{
public:
    GibsonGA5TToneStack() {
        layout.numNodes = 5;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};

        CircuitElement::Resistor R1 {220e3, 1, 2};
        CircuitElement::Resistor R2 {220e3, 2, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};

        CircuitElement::Capacitor C1 {500e-12, 1, 3};
        CircuitElement::Capacitor C2 {0.01e-6, 1, 4};
        CircuitElement::Capacitor C3 {0.0047e-6, 2, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
        
        // Tone Pot
        CircuitElement::VariableResistor VrTo {1e6, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 0, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrTo};

        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 5, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- GibsonGA16TToneStack --------------------

class GibsonGA16TToneStack : public Circuit
{
public:
    GibsonGA16TToneStack() {
        layout.numNodes = 4;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};

        CircuitElement::Capacitor C1 {0.005e-6, 2, 0};
        CircuitElement::Capacitor C2 {500e-12, 3, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        // Tone Pot
        CircuitElement::Potentiometer PtTo {1e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LOG,
                        2, 1, 3, 1};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LOG,
                        1, 4, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtTo, PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- GibsonGA20RVTToneStack --------------------

class GibsonGA20RVTToneStack : public Circuit
{
public:
    GibsonGA20RVTToneStack() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};

        CircuitElement::Resistor R1 {60e3, 7, 2};
        CircuitElement::Resistor R2 {220e3, 4, 5};
        CircuitElement::Resistor R3 {220e3, 5, 6};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {0.0022e-6, 2, 0};
        CircuitElement::Capacitor C2 {0.01e-6, 3, 0};
        CircuitElement::Capacitor C3 {330e-12, 4, 6};
        CircuitElement::Capacitor C4 {0.0047e-6, 5, 0};
        CircuitElement::Capacitor C5 {0.0047e-6, 1, 7};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5};
        
        // Bass Pot
        CircuitElement::VariableResistor VrB {2e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LOG,
                        2, 0, 1};
        
        // Treble Pot
        CircuitElement::VariableResistor VrT {2e6, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LOG,
                        7, 3, 0};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrT};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {250e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        7, 4, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- GibsonGA45RVTToneStack --------------------

class GibsonGA45RVTToneStack : public Circuit
{
public:
    GibsonGA45RVTToneStack() {
        layout.numNodes = 11;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {9, 0};

        CircuitElement::Resistor R1 {100e3, 2, 4};
        CircuitElement::Resistor R2 {22e3, 3, 0};
        CircuitElement::Resistor R3 {82e3, 5, 7};
        CircuitElement::Resistor R4 {82e3, 7, 9};
        CircuitElement::Resistor R5 {4.7e3, 8, 0};
        CircuitElement::Resistor R6 {39e3, 6, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6};
        
        CircuitElement::Capacitor C1 {0.0022e-6, 11, 2};
        CircuitElement::Capacitor C2 {0.0015e-6, 2, 3};
        CircuitElement::Capacitor C3 {0.001e-6, 11, 10};
        CircuitElement::Capacitor C4 {0.01e-6, 5, 0};
        CircuitElement::Capacitor C5 {0.0047e-6, 5, 6};
        CircuitElement::Capacitor C6 {0.0047e-6, 6, 9};
        CircuitElement::Capacitor C7 {0.01e-6, 7, 8};
        CircuitElement::Capacitor C8 {0.01e-6, 1, 11};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5, C6, C7, C8};
        
        // Bass Pot
        CircuitElement::Potentiometer PtB {1e6, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        11, 2, 3, 1};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {1e6, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LOG,
                        10, 4, 5, 1};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 5, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtT, PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- GibsonGA75ToneStack --------------------

class GibsonGA75ToneStack : public Circuit
{
public:
    GibsonGA75ToneStack() {
        layout.numNodes = 8;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};

        CircuitElement::Resistor R1 {47e3, 2, 3};
        CircuitElement::Resistor R2 {10e3, 5, 0};
        CircuitElement::Resistor R3 {100e3, 4, 7};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {0.0022e-6, 3, 4};
        CircuitElement::Capacitor C2 {0.022e-6, 4, 5};
        CircuitElement::Capacitor C3 {250e-12, 2, 6};
        CircuitElement::Capacitor C4 {0.022e-6, 8, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4};
        
        // Bass Pot
        CircuitElement::Potentiometer PtB {1e6, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 4, 5, 1};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {1e6, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 7, 8, 1};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {500e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        1, 2, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtT, PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- HiWattCP103ToneStack --------------------

class HiWattCP103ToneStack : public Circuit
{
public:
    HiWattCP103ToneStack() {
        layout.numNodes = 5;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};

        CircuitElement::Resistor R1 {100e3, 1, 4};
        CircuitElement::Resistor R2 {10e3, 4, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {220e-12, 1, 2};
        CircuitElement::Capacitor C2 {0.047e-6, 5, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        // Bass Pot
        CircuitElement::Potentiometer PtB {1e6, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 5, 0, 0.5};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {250e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 4, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtT};

        circuit = CircuitModel(layout);
    }
};

// -------------------- HiWattToneStack --------------------

class HiWattToneStack : public Circuit
{
public:
    HiWattToneStack() {
        layout.numNodes = 10;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {10, 0};

        CircuitElement::Resistor R1 {48e3, 1, 2};
        CircuitElement::Resistor R2 {100e3, 2, 5};
        CircuitElement::Resistor R3 {220e3, 3, 8};
        CircuitElement::Resistor R4 {22e3, 8, 7};
        CircuitElement::Resistor R5 {22e3, 9, 10};
        CircuitElement::Resistor R6 {220e3, 10, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6};
        
        CircuitElement::Capacitor C1 {47e-9, 5, 0};
        CircuitElement::Capacitor C2 {1e-9, 2, 3};
        CircuitElement::Capacitor C3 {47e-9, 5, 6};
        CircuitElement::Capacitor C4 {220e-12, 3, 4};
        CircuitElement::Capacitor C5 {1e-9, 7, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5};
        
        // Bass Pot
        CircuitElement::VariableResistor VrB {470e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 0, 1};
        
        // Mid Pot
        CircuitElement::VariableResistor VrM {100e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        7, 6, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrM};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {220e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 9, 8, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT};

        circuit = CircuitModel(layout);
    }
};

// -------------------- LaneyLC15ToneStack --------------------

class LaneyLC15ToneStack : public Circuit
{
public:
    LaneyLC15ToneStack() {
        layout.numNodes = 8;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};

        CircuitElement::Resistor R1 {33e3, 1, 2};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Capacitor C1 {470e-12, 1, 3};
        CircuitElement::Capacitor C2 {22e-9, 2, 4};
        CircuitElement::Capacitor C3 {22e-9, 2, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
        
        // Bass Pot
        CircuitElement::VariableResistor VrB {1e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 8, 0.05};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB};
        
        // Mid Pot
        CircuitElement::Potentiometer PtM {22e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        8, 5, 0, 1};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {220e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        7, 3, 4, 0.05};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {220e3, 4,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 6, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtM, PtT, PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- MarshallBluesbreakerToneStack --------------------

class MarshallBluesbreakerToneStack : public Circuit
{
public:
    MarshallBluesbreakerToneStack() {
        layout.numNodes = 8;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};

        CircuitElement::Resistor R1 {1.2e3, 1, 2};
        CircuitElement::Resistor R2 {56e3, 2, 7};
        CircuitElement::Resistor R3 {500e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {220e-12, 2, 3};
        CircuitElement::Capacitor C2 {22e-9, 7, 5};
        CircuitElement::Capacitor C3 {22e-9, 7, 8};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
        
        // Bass Pot
        CircuitElement::VariableResistor VrB {1e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 6, 0};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB};
        
        // Mid Pot
        CircuitElement::Potentiometer PtM {22e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 8, 0, 1};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {220e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 4, 5, 0};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtM, PtT};

        circuit = CircuitModel(layout);
    }
};

// -------------------- MarshallJCM800_2203ToneStack --------------------

class MarshallJCM800_2203ToneStack : public Circuit
{
public:
    MarshallJCM800_2203ToneStack() {
        layout.numNodes = 8;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};

        CircuitElement::Resistor R1 {1.2e3, 1, 2};
        CircuitElement::Resistor R2 {33e3, 2, 7};
        CircuitElement::Resistor R3 {500e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {470e-12, 2, 3};
        CircuitElement::Capacitor C2 {22e-9, 7, 5};
        CircuitElement::Capacitor C3 {22e-9, 7, 8};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
        
        // Bass Pot
        CircuitElement::VariableResistor VrB {1e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 6, 0};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB};
        
        // Mid Pot
        CircuitElement::Potentiometer PtM {22e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 8, 0, 1};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {22e4, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 4, 5, 0};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtM, PtT};

        circuit = CircuitModel(layout);
    }
};

// -------------------- MarshallJCM800_2210BoostToneStack --------------------

class MarshallJCM800_2210BoostToneStack : public Circuit
{
public:
    MarshallJCM800_2210BoostToneStack() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};

        CircuitElement::Resistor R1 {56e3, 1, 4};
        CircuitElement::Resistor R2 {4.7e3, 5, 6};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {470e-12, 1, 2};
        CircuitElement::Capacitor C2 {22e-9, 4, 5};
        CircuitElement::Capacitor C3 {22e-9, 4, 7};
        CircuitElement::Capacitor C4 {2e-9, 5, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4};
        
        // Bass Pot
        CircuitElement::VariableResistor VrB {1e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 0, 0.75};
        
        // Mid Pot
        CircuitElement::VariableResistor VrM {100e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        7, 0, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrM};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {220e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 5, 0.75};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT};

        circuit = CircuitModel(layout);
    }
};

// -------------------- MarshallJCM900_2210SLXToneStack --------------------

class MarshallJCM900_2210SLXToneStack : public Circuit
{
public:
    MarshallJCM900_2210SLXToneStack() {
        layout.numNodes = 8;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};

        CircuitElement::Resistor R1 {1.2e3, 1, 2};
        CircuitElement::Resistor R2 {33e3, 2, 6};
        CircuitElement::Resistor R3 {500e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {470e-12, 2, 3};
        CircuitElement::Capacitor C2 {22e-9, 6, 5};
        CircuitElement::Capacitor C3 {22e-9, 6, 8};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
                
        // Bass Pot
        CircuitElement::VariableResistor VrB {220e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 7, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB};
        
        // Mid Pot
        CircuitElement::Potentiometer PtM {22e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        7, 8, 0, 1};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {220e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 4, 5, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtM, PtT};

        circuit = CircuitModel(layout);
    }
};

// -------------------- MarshallJCM900_4100ToneStack --------------------

class MarshallJCM900_4100ToneStack : public Circuit
{
public:
    MarshallJCM900_4100ToneStack() {
        layout.numNodes = 8;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};

        CircuitElement::Resistor R1 {4.7e3, 1, 2};
        CircuitElement::Resistor R2 {4.7e3, 3, 5};
        CircuitElement::Resistor R3 {100e3, 7, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {0.22e-6, 2, 3};
        CircuitElement::Capacitor C2 {4.7e-9, 3, 4};
        CircuitElement::Capacitor C3 {0.22e-6, 5, 6};
        CircuitElement::Capacitor C4 {0.22e-6, 5, 8};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4};
                
        // Bass Pot
        CircuitElement::VariableResistor VrB {100e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 8, 1};
        
        // Mid Pot
        CircuitElement::VariableResistor VrM {10e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        8, 0, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrM};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {20e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 7, 6, 0};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT};

        circuit = CircuitModel(layout);
    }
};

// -------------------- MarshallPlexiToneStack --------------------

class MarshallPlexiToneStack : public Circuit
{
public:
    MarshallPlexiToneStack() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};

        CircuitElement::Resistor R1 {33e3, 1, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Capacitor C1 {500e-12, 1, 2};
        CircuitElement::Capacitor C2 {0.022e-6, 5, 4};
        CircuitElement::Capacitor C3 {0.022e-6, 5, 7};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
                
        // Bass Pot
        CircuitElement::VariableResistor VrB {1e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 6, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB};
        
        // Mid Pot
        CircuitElement::Potentiometer PtM {25e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 7, 0, 1};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {250e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 4, 0.9};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtM, PtT};

        circuit = CircuitModel(layout);
    }
};

// -------------------- MarshallToneStack --------------------

class MarshallToneStack : public Circuit
{
public:
    MarshallToneStack() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};

        CircuitElement::Resistor R1 {1.3e3, 1, 2};
        CircuitElement::Resistor R2 {33e3, 2, 4};
        CircuitElement::Resistor R3 {517e3, 7, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {470e-12, 2, 3};
        CircuitElement::Capacitor C2 {22e-9, 4, 5};
        CircuitElement::Capacitor C3 {22e-9, 4, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
                
        // Bass Pot
        CircuitElement::VariableResistor VrB {1e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 6, 1};
        
        // Mid Pot
        CircuitElement::VariableResistor VrM {25e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 0, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrM};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {220e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 7, 5, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT};

        circuit = CircuitModel(layout);
    }
};

// -------------------- MoonlightToneStack --------------------

class MoonlightToneStack : public Circuit
{
public:
    MoonlightToneStack() {
        layout.numNodes = 5;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};

        CircuitElement::Resistor R1 {220e3, 1, 4};
        CircuitElement::Resistor R2 {470e3, 1, 2};
        CircuitElement::Resistor R3 {270e3, 2, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {560e-12, 5, 2};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
                        
        // Tone Pot
        CircuitElement::Potentiometer PtTo {500e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 5, 0, 0.5};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtTo, PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- OrangeAD15ToneStack --------------------

class OrangeAD15ToneStack : public Circuit
{
public:
    OrangeAD15ToneStack() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};

        CircuitElement::Resistor R1 {68e3, 1, 4};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Capacitor C1 {150e-12, 1, 2};
        CircuitElement::Capacitor C2 {0.022e-6, 4, 5};
        CircuitElement::Capacitor C3 {0.022e-6, 4, 7};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
        
        // Bass Pot
        CircuitElement::VariableResistor VrB {250e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 6, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB};

        // Mid Pot
        CircuitElement::Potentiometer PtM {25e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 7, 0, 1};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {250e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 5, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtM, PtT};

        circuit = CircuitModel(layout);
    }
};

// -------------------- RolandCube60BrightToneStack --------------------

class RolandCube60BrightToneStack : public Circuit
{
public:
    RolandCube60BrightToneStack() {
        layout.numNodes = 10;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {10, 0};

        CircuitElement::Resistor R1 {49e3, 1, 4};
        CircuitElement::Resistor R2 {10e3, 6, 0};
        CircuitElement::Resistor R3 {1e3, 9, 10};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {240e-12, 1, 2};
        CircuitElement::Capacitor C2 {0.033e-6, 4, 5};
        CircuitElement::Capacitor C3 {0.082e-6, 4, 7};
        CircuitElement::Capacitor C4 {0.01-6, 7, 0};
        CircuitElement::Capacitor C5 {0.015e-6, 8, 9};
        CircuitElement::Capacitor C6 {240e-12, 3, 8};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5, C6};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
            CircuitElement::Diode::Configuration::MATCHEDPAIR,
            8, 0};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};
        
        // Bass Pot
        CircuitElement::VariableResistor VrB {250e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 6, 0.25};
        // Mid Pot
        CircuitElement::VariableResistor VrM {10e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        7, 0, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrM};

        // Treble Pot
        CircuitElement::Potentiometer PtT {250e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 5, 1};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 4,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 8, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT, PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- RolandCube60NormalToneStack --------------------

class RolandCube60NormalToneStack : public Circuit
{
public:
    RolandCube60NormalToneStack() {
        layout.numNodes = 10;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {10, 0};

        CircuitElement::Resistor R1 {49e3, 1, 4};
        CircuitElement::Resistor R2 {10e3, 6, 0};
        CircuitElement::Resistor R3 {1e3, 9, 10};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {240e-12, 1, 2};
        CircuitElement::Capacitor C2 {0.033e-6, 4, 5};
        CircuitElement::Capacitor C3 {0.082e-6, 4, 7};
        CircuitElement::Capacitor C4 {0.01-6, 7, 0};
        CircuitElement::Capacitor C5 {0.015e-6, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
            CircuitElement::Diode::Configuration::MATCHEDPAIR,
            8, 0};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};
        
        // Bass Pot
        CircuitElement::VariableResistor VrB {250e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 6, 0.25};
        
        // Mid Pot
        CircuitElement::VariableResistor VrM {10e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        7, 0, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrM};

        // Treble Pot
        CircuitElement::Potentiometer PtT {250e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 5, 1};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 4,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 8, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT, PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- RolandJazzChorusToneStack --------------------

class RolandJazzChorusToneStack : public Circuit
{
public:
    RolandJazzChorusToneStack() {
        layout.numNodes = 11;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {11, 0};

        CircuitElement::Resistor R1 {100e3, 1, 3};
        CircuitElement::Resistor R2 {1e3, 5, 6};
        CircuitElement::Resistor R3 {100e3, 7, 9};
        CircuitElement::Resistor R4 {1e6, 11, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};
        
        CircuitElement::Capacitor C1 {150e-12, 1, 2};
        CircuitElement::Capacitor C2 {0.082e-6, 3, 4};
        CircuitElement::Capacitor C3 {0.047e-6, 3, 6};
        CircuitElement::Capacitor C4 {470e-12, 7, 8};
        CircuitElement::Capacitor C5 {0.082e-6, 10, 11};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5};
                
        // Bass Pot
        CircuitElement::VariableResistor VrB {250e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 5, 1};
        
        // Mid Pot
        CircuitElement::VariableResistor VrM {10e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 0, 1};
        
        // High Pot
        CircuitElement::VariableResistor VrH {1e6, 4,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        8, 10, 0};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrM, VrH};

        // Treble Pot
        CircuitElement::Potentiometer PtT {250e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 7, 4, 0.45};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 5,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        9, 10, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT, PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- SoldanoSuperLead60ToneStack --------------------

class SoldanoSuperLead60ToneStack : public Circuit
{
public:
    SoldanoSuperLead60ToneStack() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};

        CircuitElement::Resistor R1 {100e3, 1, 0};
        CircuitElement::Resistor R2 {47e3, 1, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {470e-12, 1, 2};
        CircuitElement::Capacitor C2 {22e-9, 5, 6};
        CircuitElement::Capacitor C3 {22e-9, 5, 7};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
                
        // Bass Pot
        CircuitElement::VariableResistor VrB {1e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 7, 1};
        
        // Mid Pot
        CircuitElement::VariableResistor VrM {30e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        7, 0, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrM};

        // Treble Pot
        CircuitElement::Potentiometer PtT {220e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 6, 0.65};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 4,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 4, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT, PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- SoldanoSuperLead100ToneStack --------------------

class SoldanoSuperLead100ToneStack : public Circuit
{
public:
    SoldanoSuperLead100ToneStack() {
        layout.numNodes = 8;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};

        CircuitElement::Resistor R1 {100e3, 1, 0};
        CircuitElement::Resistor R2 {47e3, 1, 2};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {470e-12, 1, 3};
        CircuitElement::Capacitor C2 {0.02e-6, 2, 6};
        CircuitElement::Capacitor C3 {0.02e-6, 2, 8};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
                
        // Bass Pot
        CircuitElement::VariableResistor VrB {1e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 7, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB};

        // Mid Pot
        CircuitElement::Potentiometer PtM {25e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        7, 8, 0, 1};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {250e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 4, 6, 0.65};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 4,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 5, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtM, PtT, PtV};

        circuit = CircuitModel(layout);
    }
};


// -------------------- VoxACToneStack --------------------

class VoxACToneStack : public Circuit
{
public:
    VoxACToneStack() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};

        CircuitElement::Resistor R1 {717, 1, 2};
        CircuitElement::Resistor R2 {100e3, 2, 5};
        CircuitElement::Resistor R3 {10e3, 7, 0};
        CircuitElement::Resistor R4 {600e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};
        
        CircuitElement::Capacitor C1 {47e-12, 2, 3};
        CircuitElement::Capacitor C2 {22e-9, 5, 6};
        CircuitElement::Capacitor C3 {22e-9, 5, 7};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
                
        // Bass Pot
        CircuitElement::Potentiometer PtB {1e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 7, 0, 0.5};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {1e6, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 4, 6, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtT};

        circuit = CircuitModel(layout);
    }
};

// -------------------- WardsAirlineGDR_8502AToneStack --------------------

class WardsAirlineGDR_8502AToneStack : public Circuit
{
public:
    WardsAirlineGDR_8502AToneStack() {
        layout.numNodes = 5;
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};

        CircuitElement::Resistor R1 {68e3, 1, 2};
        CircuitElement::Resistor R2 {15e6, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {0.01e-6, 2, 5};
        CircuitElement::Capacitor C2 {0.02e-6, 3, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
                
        // Tone Pot
        CircuitElement::VariableResistor VrTo {1e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LOG,
                        5, 0, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrTo};

        // Volume Pot
        CircuitElement::Potentiometer PtV {350e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- WardsAirlineGDR_8516AToneStack --------------------

class WardsAirlineGDR_8516AToneStack : public Circuit
{
public:
    WardsAirlineGDR_8516AToneStack() {
        layout.numNodes = 6;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};

        CircuitElement::Resistor R1 {100e3, 1, 0};
        CircuitElement::Resistor R2 {220e3, 3, 0};
        CircuitElement::Resistor R3 {60e3, 3, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {0.02e-6, 1, 2};
        CircuitElement::Capacitor C2 {0.00068e-6, 2, 3};
        CircuitElement::Capacitor C3 {0.003e-6, 3, 4};
        CircuitElement::Capacitor C4 {0.003e-6, 4, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4};
                
        // Bass Pot
        CircuitElement::VariableResistor VrB {1e6, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 1};
        
        // Treble Pot
        CircuitElement::VariableResistor VrT {1e6, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LOG,
                        4, 0, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrT};

        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 6, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- WardsAirlineGIM_9151AToneStack --------------------

class WardsAirlineGIM_9151AToneStack : public Circuit
{
public:
    WardsAirlineGIM_9151AToneStack() {
        layout.numNodes = 10;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {10, 0};

        CircuitElement::Resistor R1 {270e3, 1, 3};
        CircuitElement::Resistor R2 {100e3, 3, 0};
        CircuitElement::Resistor R3 {150e3, 5, 6};
        CircuitElement::Resistor R4 {680e3, 6, 7};
        CircuitElement::Resistor R5 {680e3, 10, 7};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {0.02e-6, 1, 2};
        CircuitElement::Capacitor C2 {0.1e-6, 3, 0};
        CircuitElement::Capacitor C3 {0.001e-6, 4, 8};
        CircuitElement::Capacitor C4 {500e-12, 8, 10};
        CircuitElement::Capacitor C5 {0.005e-6, 9, 0};
        CircuitElement::Capacitor C6 {0.003e-6, 6, 0};
        CircuitElement::Capacitor C7 {0.001e-6, 7, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5, C6, C7};
                
        // Treble Pot
        CircuitElement::VariableResistor VrT {500e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        8, 9, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrT};

        // Bass Pot
        CircuitElement::Potentiometer PtB {500e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 5, 0, 1};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {500e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 4, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- WardsAirlineGVC_9002AToneStack --------------------

class WardsAirlineGVC_9002AToneStack : public Circuit
{
public:
    WardsAirlineGVC_9002AToneStack() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};

        CircuitElement::Resistor R1 {15e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 1, 3};
        CircuitElement::Resistor R3 {10e3, 3, 4};
        CircuitElement::Resistor R4 {33e3, 2, 5};
        CircuitElement::Resistor R5 {33e3, 5, 6};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {0.01e-6, 2, 0};
        CircuitElement::Capacitor C2 {0.0033e-6, 3, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
                
        // Tone Pot
        CircuitElement::VariableResistor VrTo {100e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 0, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrTo};

        // Volume Pot
        CircuitElement::Potentiometer PtV {100e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 7, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- WardsAirlineGVC_9056AToneStack --------------------

class WardsAirlineGVC_9056AToneStack : public Circuit
{
public:
    WardsAirlineGVC_9056AToneStack() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};

        CircuitElement::Resistor R1 {22e3, 2, 3};
        CircuitElement::Resistor R2 {100e3, 5, 6};
        CircuitElement::Resistor R3 {6.8e3, 7, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {0.0033e-6, 2, 4};
        CircuitElement::Capacitor C2 {0.1e-6, 3, 6};
        CircuitElement::Capacitor C3 {0.05e-6, 3, 7};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
                
        // Bass Pot
        CircuitElement::VariableResistor VrB {500e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 7, 1};
        
        // Treble Pot
        CircuitElement::VariableResistor VrT {500e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 5, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrB, VrT};

        // Volume Pot
        CircuitElement::Potentiometer PtV {500e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        1, 2, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};

        circuit = CircuitModel(layout);
    }
};

// -------------------- WardsAirlineGVC_9062AToneStack --------------------

class WardsAirlineGVC_9062AToneStack : public Circuit
{
public:
    WardsAirlineGVC_9062AToneStack() {
        layout.numNodes = 9;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};

        CircuitElement::Resistor R1 {150e3, 7, 8};
        CircuitElement::Resistor R2 {680e3, 8, 9};
        CircuitElement::Resistor R3 {680e3, 9, 4};
        CircuitElement::Resistor R4 {100e3, 4, 5};
        CircuitElement::Resistor R5 {270e3, 3, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {0.001e-6, 2, 3};
        CircuitElement::Capacitor C2 {500e-12, 3, 4};
        CircuitElement::Capacitor C3 {0.0033e-6, 6, 0};
        CircuitElement::Capacitor C4 {0.0033e-6, 8, 0};
        CircuitElement::Capacitor C5 {0.001e-6, 9, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5};
                
        // Bass Pot
        CircuitElement::Potentiometer PtB {500e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 7, 0, 1};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {500e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LOG,
                        3, 6, 0, 1};
    
        // Volume Pot
        CircuitElement::Potentiometer PtV {500e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        1, 2, 0, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtT, PtV};

        circuit = CircuitModel(layout);
    }
};

// End of namespace
}

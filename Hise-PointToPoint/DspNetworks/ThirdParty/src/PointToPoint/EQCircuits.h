//
//  EQCircuits.h
//
//  Collection of basic EQ-style filters (3/4/5 band EQs, shelves, graphic EQs, etc)
//
//
#include "Circuit.h"
#include "CircuitModel.h"
#include "CircuitElement.h"

#pragma once
namespace PointToPoint {

// -------------------- Baxandall1 --------------------

class Baxandall1 : public Circuit
{
public:
    Baxandall1() {
        layout.numNodes = 8;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {8, 0};
        
        CircuitElement::Resistor R1 {1.8e3, 1, 2};
        CircuitElement::Resistor R2 {1.8e3, 4, 8};
        CircuitElement::Resistor R3 {22e3, 3, 5};
        CircuitElement::Resistor R4 {9.1e3, 5, 6};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};
        
        CircuitElement::Capacitor C1 {100e-9, 2, 4};
        CircuitElement::Capacitor C2 {4.7e-9, 6, 7};
        CircuitElement::Capacitor C3 {22e-12, 5, 8};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        CircuitElement::OPAmp OP1 {0, 5, 8};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};

        // Bass Pot
        CircuitElement::Potentiometer PtB {10e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            2, 3, 4, 0.5};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {10e3, 2,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            1, 7, 8, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtT};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- Baxandall2 --------------------

class Baxandall2 : public Circuit
{
public:
    Baxandall2() {
        layout.numNodes = 9;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {1.8e3, 1, 2};
        CircuitElement::Resistor R2 {1.8e3, 4, 5};
        CircuitElement::Resistor R3 {12e3, 3, 8};
        CircuitElement::Resistor R4 {1.2e3, 6, 5};
        CircuitElement::Resistor R5 {1.2e3, 1, 9};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {100e-9, 4, 3};
        CircuitElement::Capacitor C2 {100e-9, 2, 3};
        CircuitElement::Capacitor C3 {12e-9, 8, 7};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        CircuitElement::OPAmp OP1 {0, 8, 5};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};

        // Bass Pot
        CircuitElement::Potentiometer PtB {10e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            2, 3, 4, 0.5};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {10e3, 2,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            9, 7, 6, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtT};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- Baxandall3 --------------------

class Baxandall3 : public Circuit
{
public:
    Baxandall3() {
        layout.numNodes = 11;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {1.8e3, 1, 2};
        CircuitElement::Resistor R2 {1.8e3, 4, 5};
        CircuitElement::Resistor R3 {12e3, 3, 8};
        CircuitElement::Resistor R4 {1e3, 8, 7};
        CircuitElement::Resistor R5 {1e3, 5, 6};
        CircuitElement::Resistor R6 {1e3, 1, 10};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6};
        
        CircuitElement::Capacitor C1 {100e-9, 2, 4};
        CircuitElement::Capacitor C2 {15e-9, 6, 11};
        CircuitElement::Capacitor C3 {15e-9, 9, 10};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        CircuitElement::OPAmp OP1 {0, 8, 5};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};

        // Bass Pot
        CircuitElement::Potentiometer PtB {10e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            2, 3, 4, 0.5};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {10e3, 2,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            9, 7, 11, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtT};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- Baxandall5 --------------------

class Baxandall5 : public Circuit
{
public:
    Baxandall5() {
        layout.numNodes = 11;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};
        
        CircuitElement::Resistor R1 {2.2e3, 11, 2};
        CircuitElement::Resistor R2 {2.2e3, 4, 5};
        CircuitElement::Resistor R3 {6.8e3, 3, 8};
        CircuitElement::Resistor R4 {2.2e3, 8, 9};
        CircuitElement::Resistor R5 {1.8e3, 5, 6};
        CircuitElement::Resistor R6 {1e3, 6, 7};
        CircuitElement::Resistor R7 {2.2e3, 5, 7};
        CircuitElement::Resistor R8 {1.3e3, 1, 11};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {100e-9, 4, 3};
        CircuitElement::Capacitor C2 {100e-9, 2, 3};
        CircuitElement::Capacitor C3 {15e-9, 9, 10};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        CircuitElement::OPAmp OP1 {0, 8, 6};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};

        // Bass Pot
        CircuitElement::Potentiometer PtB {10e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            2, 3, 4, 0.5};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {10e3, 2,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            11, 10, 5, 0.5};
        
        // Balance Pot
        CircuitElement::Potentiometer PtBa {10e3, 3,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            0, 7, 6, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtT, PtBa};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- Baxandall63Band --------------------

class Baxandall63Band : public Circuit
{
public:
    Baxandall63Band() {
        layout.numNodes = 12;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {6.8e3, 1, 2};
        CircuitElement::Resistor R2 {6.8e3, 4, 5};
        CircuitElement::Resistor R3 {2.2e3, 7, 5};
        CircuitElement::Resistor R4 {2.2e3, 1, 9};
        CircuitElement::Resistor R5 {68e3, 3, 6};
        CircuitElement::Resistor R6 {15e3, 8, 10};
        CircuitElement::Resistor R7 {10e3, 10, 11};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7};
        
        CircuitElement::Capacitor C1 {47e-9, 2, 4};
        CircuitElement::Capacitor C2 {10e-9, 9, 7};
        CircuitElement::Capacitor C3 {2.2e-9, 11, 12};
        CircuitElement::Capacitor C4 {10e-9, 10, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4};

        CircuitElement::OPAmp OP1 {0, 6, 5};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};

        // Bass Pot
        CircuitElement::Potentiometer PtB {20e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            2, 3, 4, 0.5};
        
        // Treble Pot
        CircuitElement::Potentiometer PtM {20e3, 2,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            9, 8, 7, 0.5};
        
        // Balance Pot
        CircuitElement::Potentiometer PtT {20e3, 3,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            1, 12, 5, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtM, PtT};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- Baxandall74Band --------------------

class Baxandall74Band : public Circuit
{
public:
    Baxandall74Band() {
        layout.numNodes = 18;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {18, 0};
        
        CircuitElement::Resistor R1 {1.6e3, 4, 5};
        CircuitElement::Resistor R2 {1.6e3, 1, 2};
        CircuitElement::Resistor R3 {22e3, 6, 7};
        CircuitElement::Resistor R4 {4.7e3, 7, 8};
        CircuitElement::Resistor R5 {180e3, 7, 5};
        CircuitElement::Resistor R6 {180e3, 1, 7};
        CircuitElement::Resistor R7 {3.3e3, 12, 18};
        CircuitElement::Resistor R8 {3.3e3, 5, 10};
        CircuitElement::Resistor R9 {22e3, 11, 13};
        CircuitElement::Resistor R10 {4.7e3, 13, 14};
        CircuitElement::Resistor R11 {1.6e3, 17, 18};
        CircuitElement::Resistor R12 {1.6e3, 5, 16};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12};
        
        CircuitElement::Capacitor C1 {22e-9, 2, 4};
        CircuitElement::Capacitor C2 {33e-9, 3, 6};
        CircuitElement::Capacitor C3 {2.2e-9, 8, 9};
        CircuitElement::Capacitor C4 {100e-9, 10, 12};
        CircuitElement::Capacitor C5 {2.2e-9, 14, 15};
        CircuitElement::Capacitor C6 {4.7e-9, 16, 17};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5, C6};

        CircuitElement::OPAmp OP1 {0, 7, 5};
        CircuitElement::OPAmp OP2 {0, 13, 18};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};

        // Low Pot
        CircuitElement::Potentiometer PtL {20e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            10, 11, 12, 0.5};
        
        // Low Mid Pot
        CircuitElement::Potentiometer PtLM {20e3, 2,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            2, 3, 4, 0.5};
        
        // High Mid Pot
        CircuitElement::Potentiometer PtHM {20e3, 3,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            16, 15, 17, 0.5};
        
        // High Pot
        CircuitElement::Potentiometer PtH {20e3, 4,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            1, 9, 5, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtL, PtLM, PtHM, PtH};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- FourBandEQ --------------------

class FourBandEQ : public Circuit
{
public:
    FourBandEQ() {
        layout.numNodes = 22;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {8, 0};
        
        CircuitElement::Resistor R1 {2.7e3, 1, 2};
        CircuitElement::Resistor R2 {2.7e3, 7, 22};
        CircuitElement::Resistor R3 {100, 22, 8};
        CircuitElement::Resistor R4 {470, 9, 0};
        CircuitElement::Resistor R5 {470, 10, 13};
        CircuitElement::Resistor R6 {47e3, 11, 12};
        CircuitElement::Resistor R7 {470, 14, 17};
        CircuitElement::Resistor R8 {47e3, 15, 16};
        CircuitElement::Resistor R9 {470, 18, 21};
        CircuitElement::Resistor R10 {47e3, 19, 20};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8, R9, R10};
        
        CircuitElement::Capacitor C1 {12e-9, 6, 9};
        CircuitElement::Capacitor C2 {22e-9, 5, 10};
        CircuitElement::Capacitor C3 {10e-9, 10, 11};
        CircuitElement::Capacitor C4 {150e-9, 4, 18};
        CircuitElement::Capacitor C5 {22e-9, 18, 19};
        CircuitElement::Capacitor C6 {1e-6, 3, 14};
        CircuitElement::Capacitor C7 {47e-9, 14, 15};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5, C6, C7};

        CircuitElement::OPAmp OP1 {2, 7, 22};
        CircuitElement::OPAmp OP2 {15, 17, 17};
        CircuitElement::OPAmp OP3 {19, 21, 21};
        CircuitElement::OPAmp OP4 {11, 13, 13};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};

        // Bass Frequency Pot
        CircuitElement::VariableResistor VrBF {1e6, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            16, 0, 0.5};
        
        // Low Mid Frequency Pot
        CircuitElement::VariableResistor VrLMF {1e6, 3,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            20, 0, 0.5};
        
        // High Mid Frequency Pot
        CircuitElement::VariableResistor VrHMF {1e6, 5,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            12, 0, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrBF, VrLMF, VrHMF};
        
        // Bass Gain Pot
        CircuitElement::Potentiometer PtBG {10e3, 2,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            2, 3, 7, 0.5};
        
        // Low Mid Gain Pot
        CircuitElement::Potentiometer PtLMG {10e3, 4,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            2, 4, 7, 0.5};
        
        // High Mid Gain Pot
        CircuitElement::Potentiometer PtHMG {10e3, 6,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            2, 5, 7, 0.5};
        
        // Treble Gain Pot
        CircuitElement::Potentiometer PtTG {10e3, 7,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            2, 6, 7, 0.5};
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtBG, PtLMG, PtHMG, PtTG};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- HPFLPFCombo --------------------

class HPFLPFCombo : public Circuit
{
public:
    HPFLPFCombo() {
        layout.numNodes = 4;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {15e3, 2, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Capacitor C1 {47e-9, 1, 2};
        CircuitElement::Capacitor C2 {1e-9, 4, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        // HPF Cutoff
        CircuitElement::VariableResistor VrHPF {100e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            3, 0, 0};
        
        // LPF Cutoff
        CircuitElement::VariableResistor VrLPF {100e3, 2,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            2, 4, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrHPF, VrLPF};

        circuit = CircuitModel(layout);
    }
};

// -------------------- LowPlusHighPeaking --------------------

class LowPlusHighPeaking : public Circuit
{
public:
    LowPlusHighPeaking() {
        layout.numNodes = 13;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {2.7e3, 1, 2};
        CircuitElement::Resistor R2 {2.7e3, 4, 5};
        CircuitElement::Resistor R3 {470, 10, 13};
        CircuitElement::Resistor R4 {47e3, 11, 12};
        CircuitElement::Resistor R5 {1e3, 6, 7};
        CircuitElement::Resistor R6 {470, 6, 9};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6};
        
        CircuitElement::Capacitor C1 {1e-6, 3, 10};
        CircuitElement::Capacitor C2 {47e-9, 10, 11};
        CircuitElement::Capacitor C3 {10e-9, 8, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        CircuitElement::OPAmp OP1 {2, 4, 5};
        CircuitElement::OPAmp OP2 {11, 13, 13};
        CircuitElement::OPAmp OP3 {8, 9, 9};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3};

        // Bass Frequency Pot
        CircuitElement::VariableResistor VrBF {1e6, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            12, 0, 0.5};
        
        // Treble Frequency Pot
        CircuitElement::VariableResistor VrTF {10e3, 3,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            7, 8, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrBF, VrTF};
        
        // Bass Gain Pot
        CircuitElement::Potentiometer PtBG {10e3, 2,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            2, 3, 4, 0.5};
        
        // Treble Gain Pot
        CircuitElement::Potentiometer PtTG {10e3, 4,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            2, 6, 4, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtBG, PtTG};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- LowPlusHighShelves --------------------

class LowPlusHighShelves : public Circuit
{
public:
    LowPlusHighShelves() {
        layout.numNodes = 13;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {9, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {3.3e3, 3, 4};
        CircuitElement::Resistor R4 {3.3e3, 12, 13};
        CircuitElement::Resistor R5 {3.3e3, 6, 7};
        CircuitElement::Resistor R6 {3.3e3, 10, 11};
        CircuitElement::Resistor R7 {10e3, 3, 8};
        CircuitElement::Resistor R8 {10e3, 8, 9};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {220e-9, 5, 0};
        CircuitElement::Capacitor C2 {10e-9, 3, 12};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {0, 2, 3};
        CircuitElement::OPAmp OP2 {5, 6, 6};
        CircuitElement::OPAmp OP3 {12, 11, 11};
        CircuitElement::OPAmp OP4 {0, 8, 9};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};

        // Bass Frequency Pot
        CircuitElement::VariableResistor VrBF {10e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            4, 5, 0.5};
        
        // Treble Frequency Pot
        CircuitElement::VariableResistor VrTF {10e3, 3,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            13, 0, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrBF, VrTF};
        
        // Bass Gain Pot
        CircuitElement::Potentiometer PtBG {10e3, 2,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            2, 7, 8, 0.5};
        
        // Treble Gain Pot
        CircuitElement::Potentiometer PtTG {10e3, 4,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            2, 10, 8, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtBG, PtTG};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- Seven Band Graphic EQ --------------------

class SevenBandGraphicEQ : public Circuit
{
public:
    SevenBandGraphicEQ() {
        layout.numNodes = 32;
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};

        CircuitElement::Resistor R1 {2.7e3, 1, 2};
        CircuitElement::Resistor R2 {2.7e3, 3, 4};
        CircuitElement::Resistor RA1 {1.8e3, 6, 8};
        CircuitElement::Resistor RA2 {130e3, 7, 0};
        CircuitElement::Resistor RB1 {1.8e3, 10, 12};
        CircuitElement::Resistor RB2 {110e3, 11, 0};
        CircuitElement::Resistor RC1 {1.8e3, 14, 16};
        CircuitElement::Resistor RC2 {91e3, 15, 0};
        CircuitElement::Resistor RD1 {1.8e3, 18, 20};
        CircuitElement::Resistor RD2 {82e3, 19, 0};
        CircuitElement::Resistor RE1 {1.8e3, 22, 24};
        CircuitElement::Resistor RE2 {68e3, 23, 0};
        CircuitElement::Resistor RF1 {1.8e3, 26, 28};
        CircuitElement::Resistor RF2 {62e3, 27, 0};
        CircuitElement::Resistor RG1 {1.8e3, 30, 32};
        CircuitElement::Resistor RG2 {51e3, 31, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, RA1, RA2, RB1, RB2, RC1, RC2, RD1, RD2, RE1, RE2, RF1, RF2, RG1, RG2};

        CircuitElement::Capacitor CA1 {1270e-9, 5, 6};
        CircuitElement::Capacitor CA2 {22e-9, 6, 7};
        CircuitElement::Capacitor CB1 {503e-9, 9, 10};
        CircuitElement::Capacitor CB2 {10e-9, 10, 11};
        CircuitElement::Capacitor CC1 {200e-9, 13, 14};
        CircuitElement::Capacitor CC2 {4.7e-9, 14, 15};
        CircuitElement::Capacitor CD1 {80e-9, 17, 18};
        CircuitElement::Capacitor CD2 {2.2e-9, 18, 19};
        CircuitElement::Capacitor CE1 {33e-9, 21, 22};
        CircuitElement::Capacitor CE2 {1e-9, 22, 23};
        CircuitElement::Capacitor CF1 {12.2e-9, 25, 26};
        CircuitElement::Capacitor CF2 {470e-12, 26, 27};
        CircuitElement::Capacitor CG1 {4.7e-9, 29, 30};
        CircuitElement::Capacitor CG2 {220e-12, 30, 31};
        layout.Cs = std::vector<CircuitElement::Capacitor> {CA1, CA2, CB1, CB2, CC1, CC2, CD1, CD2, CE1, CE2, CF1, CF2, CG1, CG2};

        CircuitElement::OPAmp OP1 {2, 3, 4};
        CircuitElement::OPAmp OPA {7, 8, 8};
        CircuitElement::OPAmp OPB {11, 12, 12};
        CircuitElement::OPAmp OPC {15, 16, 16};
        CircuitElement::OPAmp OPD {19, 20, 20};
        CircuitElement::OPAmp OPE {23, 24, 24};
        CircuitElement::OPAmp OPF {27, 28, 28};
        CircuitElement::OPAmp OPG {31, 32, 32};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OPA, OPB, OPC, OPD, OPE, OPF, OPG};

        // 63 Hz Pot
        CircuitElement::Potentiometer PtA {10e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 5, 3, 0.5};
        
        // 160 Hz Pot
        CircuitElement::Potentiometer PtB {10e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 9, 3, 0.5};
        
        // 410 Hz Pot
        CircuitElement::Potentiometer PtC {10e3, 3,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 13, 3, 0.5};
        
        // 1 kHz Pot
        CircuitElement::Potentiometer PtD {10e3, 4,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 17, 3, 0.5};
        
        // 2.5 kHz Pot
        CircuitElement::Potentiometer PtE {10e3, 5,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 21, 3, 0.5};
        
        // 7.7 kHz Pot
        CircuitElement::Potentiometer PtF {10e3, 6,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 25, 3, 0.5};
        
        // 16 kHz Pot
        CircuitElement::Potentiometer PtG {10e3, 7,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 29, 3, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtA, PtB, PtC, PtD, PtE, PtF, PtG};

        circuit = CircuitModel(layout);
    }
};

// End of namespace
}

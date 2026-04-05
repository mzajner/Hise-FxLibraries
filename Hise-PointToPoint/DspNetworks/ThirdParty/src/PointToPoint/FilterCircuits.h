//
//  FilterCircuits.h
//
//  Collection of common linear filter circuits
//
//
#include "Circuit.h"
#include "CircuitModel.h"
#include "CircuitElement.h"

#pragma once
namespace PointToPoint {

// -------------------- AllPassFilter --------------------

class AllPassFilter : public Circuit
{
public:
    AllPassFilter() {
        layout.numNodes = 5;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};

        CircuitElement::Resistor R1 {1e3, 1, 5};
        CircuitElement::Resistor R2 {10e3, 1, 3};
        CircuitElement::Resistor R3 {10e3, 3, 4};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {10e-9, 2, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};

        CircuitElement::OPAmp OP1 {2, 3, 4};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        // Phase Pot
        CircuitElement::VariableResistor VrP {50e3, 1,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            5, 2, 0};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrP};

        layout.hasDCBlocker = true;
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- AmblerTiltEQ --------------------

class AmblerTiltEQ : public Circuit
{
public:
    AmblerTiltEQ() {
        layout.numNodes = 7;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};

        CircuitElement::Resistor R1 {6.8e3, 1, 3};
        CircuitElement::Resistor R2 {6.8e3, 5, 7};
        CircuitElement::Resistor R3 {2.2e3, 1, 2};
        CircuitElement::Resistor R4 {2.2e3, 6, 7};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};
        
        CircuitElement::Capacitor C1 {33e-9, 3, 6};
        CircuitElement::Capacitor C2 {33e-9, 2, 5};
        CircuitElement::Capacitor C3 {22e-12, 4, 7};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        CircuitElement::OPAmp OP1 {0, 4, 7};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        // Tilt Pot
        CircuitElement::Potentiometer PtTi {10e3, 1,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            3, 4, 5, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtTi};

        circuit = CircuitModel(layout);
    }
};

// -------------------- BiquadBPF --------------------

class BiquadBPF : public Circuit
{
public:
    BiquadBPF() {
        layout.numNodes = 7;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};

        CircuitElement::Resistor R1 {5e3, 1, 2};
        CircuitElement::Resistor R2 {5e3, 2, 3};
        CircuitElement::Resistor R3 {5e3, 2, 7};
        CircuitElement::Resistor R4 {5e3, 5, 6};
        CircuitElement::Resistor R5 {5e3, 6, 7};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {20e-9, 2, 3};
        CircuitElement::Capacitor C2 {20e-9, 4, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {0, 2, 3};
        CircuitElement::OPAmp OP2 {0, 4, 5};
        CircuitElement::OPAmp OP3 {0, 6, 7};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3};
        
        // Frequency/Q Pot
        CircuitElement::VariableResistor VrQ {200e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            3, 4, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrQ};

        circuit = CircuitModel(layout);
    }
};

// -------------------- BiquadLPF --------------------

class BiquadLPF : public Circuit
{
public:
    BiquadLPF() {
        layout.numNodes = 7;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};

        CircuitElement::Resistor R1 {5e3, 1, 2};
        CircuitElement::Resistor R2 {5e3, 2, 3};
        CircuitElement::Resistor R3 {5e3, 2, 7};
        CircuitElement::Resistor R4 {5e3, 5, 6};
        CircuitElement::Resistor R5 {5e3, 6, 7};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {20e-9, 2, 3};
        CircuitElement::Capacitor C2 {20e-9, 4, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {0, 2, 3};
        CircuitElement::OPAmp OP2 {0, 4, 5};
        CircuitElement::OPAmp OP3 {0, 6, 7};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3};
        
        // Frequency/Q Pot
        // Q increases alongside frequency in a biquad
        CircuitElement::VariableResistor VrQ {200e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            3, 4, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrQ};

        circuit = CircuitModel(layout);
    }
};

// -------------------- BridgedTNotchFilter --------------------

class BridgedTNotchFilter : public Circuit
{
public:
    BridgedTNotchFilter() {
        layout.numNodes = 4;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        CircuitElement::Capacitor C2 {100e-9, 3, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {2, 4, 4};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        // Frequency Pot
        CircuitElement::VariableResistor VrF1 {200e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            1, 3, 1};
        
        // Frequency Pot
        CircuitElement::VariableResistor VrF2 {200e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            3, 2, 1}; 
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF1, VrF2};

        circuit = CircuitModel(layout);
    }
};

// -------------------- ButterworthSallenKeyHPF --------------------

class ButterworthSallenKeyHPF : public Circuit
{
public:
    ButterworthSallenKeyHPF() {
        layout.numNodes = 4;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        CircuitElement::Capacitor C2 {10e-9, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {3, 4, 4};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF1 {705e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            3, 0, 0};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF2 {353.5e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            2, 4, 0};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF1, VrF2};

        circuit = CircuitModel(layout);
    }
};

// -------------------- ButterworthSallenKeyLPF --------------------

class ButterworthSallenKeyLPF : public Circuit
{
public:
    ButterworthSallenKeyLPF() {
        layout.numNodes = 4;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Capacitor C1 {7.07e-9, 3, 0};
        CircuitElement::Capacitor C2 {14.1e-9, 2, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {3, 4, 4};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF1 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            1, 2, 1};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF2 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            2, 3, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF1, VrF2};

        circuit = CircuitModel(layout);
    }
};

// -------------------- FirstOrderStateVariableHPF --------------------

class FirstOrderStateVariableHPF : public Circuit
{
public:
    FirstOrderStateVariableHPF() {
        layout.numNodes = 7;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 3, 0};
        CircuitElement::Resistor R3 {10e3, 3, 4};
        CircuitElement::Resistor R4 {10e3, 2, 7};
        CircuitElement::Resistor R5 {100, 4, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {100e-9, 6, 7};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};

        CircuitElement::OPAmp OP1 {2, 3, 4};
        CircuitElement::OPAmp OP2 {0, 6, 7};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF {20e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            5, 6, 0};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF};

        circuit = CircuitModel(layout);
    }
};

// -------------------- FirstOrderStateVariableLPF --------------------

class FirstOrderStateVariableLPF : public Circuit
{
public:
    FirstOrderStateVariableLPF() {
        layout.numNodes = 7;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 3, 0};
        CircuitElement::Resistor R3 {10e3, 3, 4};
        CircuitElement::Resistor R4 {10e3, 2, 7};
        CircuitElement::Resistor R5 {100, 4, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {100e-9, 6, 7};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};

        CircuitElement::OPAmp OP1 {2, 3, 4};
        CircuitElement::OPAmp OP2 {0, 6, 7};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF {20e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            5, 6, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF};

        circuit = CircuitModel(layout);
    }
};

// -------------------- FliegeLPF --------------------

class FliegeLPF : public Circuit
{
public:
    FliegeLPF() {
        layout.numNodes = 9;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {500, 1, 8};
        CircuitElement::Resistor R2 {500, 3, 9};
        CircuitElement::Resistor R3 {500, 2, 7};
        CircuitElement::Resistor R4 {10e3, 5, 6};
        CircuitElement::Resistor R5 {10e3, 6, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {50e-9, 2, 3};
        CircuitElement::Capacitor C2 {50e-9, 4, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {2, 4, 5};
        CircuitElement::OPAmp OP2 {6, 4, 3};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF1 {10e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            8, 2, 1};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF2 {10e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            9, 4, 1};
        
        // Q Pot
        CircuitElement::VariableResistor VrQ {4e3, 2,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            7, 3, 0};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF1, VrF2, VrQ};

        circuit = CircuitModel(layout);
    }
};

// -------------------- FourOpAmpStateVariableBPF --------------------

class FourOpAmpStateVariableBPF : public Circuit
{
public:
    FourOpAmpStateVariableBPF() {
        layout.numNodes = 12;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {9, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 9};
        CircuitElement::Resistor R4 {5e3, 4, 5};
        CircuitElement::Resistor R5 {10e3, 5, 6};
        CircuitElement::Resistor R6 {10e3, 5, 12};
        CircuitElement::Resistor R7 {5e3, 7, 8};
        CircuitElement::Resistor R8 {5e3, 10, 11};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 8, 9};
        CircuitElement::Capacitor C2 {5e-9, 11, 12};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {0, 2, 3};
        CircuitElement::OPAmp OP2 {0, 5, 6};
        CircuitElement::OPAmp OP3 {0, 8, 9};
        CircuitElement::OPAmp OP4 {0, 11, 12};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF1 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            6, 7, 0.5};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF2 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            9, 10, 0.5};
        
        // Q Pot
        CircuitElement::VariableResistor VrQ {100e3, 2,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            3, 4, 0};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF1, VrF2, VrQ};

        circuit = CircuitModel(layout);
    }
};

// -------------------- FourOpAmpStateVariableHPF --------------------

class FourOpAmpStateVariableHPF : public Circuit
{
public:
    FourOpAmpStateVariableHPF() {
        layout.numNodes = 12;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 9};
        CircuitElement::Resistor R4 {7.07e3, 4, 5};
        CircuitElement::Resistor R5 {10e3, 5, 6};
        CircuitElement::Resistor R6 {10e3, 5, 12};
        CircuitElement::Resistor R7 {5e3, 7, 8};
        CircuitElement::Resistor R8 {5e3, 10, 11};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 8, 9};
        CircuitElement::Capacitor C2 {5e-9, 11, 12};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {0, 2, 3};
        CircuitElement::OPAmp OP2 {0, 5, 6};
        CircuitElement::OPAmp OP3 {0, 8, 9};
        CircuitElement::OPAmp OP4 {0, 11, 12};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF1 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            6, 7, 0};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF2 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            9, 10, 0};
        
        // Q Pot
        CircuitElement::VariableResistor VrQ {14.1e3, 2,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            3, 4, 0};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF1, VrF2, VrQ};

        circuit = CircuitModel(layout);
    }
};

// -------------------- FourOpAmpStateVariableLPF --------------------

class FourOpAmpStateVariableLPF : public Circuit
{
public:
    FourOpAmpStateVariableLPF() {
        layout.numNodes = 12;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {12, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 9};
        CircuitElement::Resistor R4 {7.07e3, 4, 5};
        CircuitElement::Resistor R5 {10e3, 5, 6};
        CircuitElement::Resistor R6 {10e3, 5, 12};
        CircuitElement::Resistor R7 {5e3, 7, 8};
        CircuitElement::Resistor R8 {5e3, 10, 11};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 8, 9};
        CircuitElement::Capacitor C2 {5e-9, 11, 12};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {0, 2, 3};
        CircuitElement::OPAmp OP2 {0, 5, 6};
        CircuitElement::OPAmp OP3 {0, 8, 9};
        CircuitElement::OPAmp OP4 {0, 11, 12};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};

        // Cutoff Pot
        CircuitElement::VariableResistor VrF1 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            6, 7, 1};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF2 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            9, 10, 1};
        
        // Q Pot
        CircuitElement::VariableResistor VrQ {14.1e3, 2,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            3, 4, 0};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF1, VrF2, VrQ};

        circuit = CircuitModel(layout);
    }
};

// -------------------- FourOpAmpStateVariableNotch --------------------

class FourOpAmpStateVariableNotch : public Circuit
{
public:
    FourOpAmpStateVariableNotch() {
        layout.numNodes = 12;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 9};
        CircuitElement::Resistor R4 {5e3, 4, 5};
        CircuitElement::Resistor R5 {10e3, 5, 6};
        CircuitElement::Resistor R6 {10e3, 5, 12};
        CircuitElement::Resistor R7 {5e3, 7, 8};
        CircuitElement::Resistor R8 {5e3, 10, 11};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 8, 9};
        CircuitElement::Capacitor C2 {5e-9, 11, 12};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {0, 2, 3};
        CircuitElement::OPAmp OP2 {0, 5, 6};
        CircuitElement::OPAmp OP3 {0, 8, 9};
        CircuitElement::OPAmp OP4 {0, 11, 12};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF1 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            6, 7, 0.5};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF2 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            9, 10, 0.5};
        
        // Q Pot
        CircuitElement::VariableResistor VrQ {100e3, 2,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            3, 4, 0};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF1, VrF2, VrQ};

        circuit = CircuitModel(layout);
    }
};

// -------------------- MFBBandpass --------------------

class MFBBandpass : public Circuit
{
public:
    MFBBandpass() {
        layout.numNodes = 4;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {65e3, 2, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Capacitor C1 {10e-9, 2, 3};
        CircuitElement::Capacitor C2 {10e-9, 2, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {0, 3, 4};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF1 {2e6, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            1, 2, 0.25};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF2 {4e6, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            4, 3, 0.25};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF1, VrF2};

        circuit = CircuitModel(layout);
    }
};

// -------------------- SallenKeyFeedbackHPF --------------------

class SallenKeyFeedbackHPF : public Circuit
{
public:
    SallenKeyFeedbackHPF() {
        layout.numNodes = 5;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {500e3, 5, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        CircuitElement::Capacitor C2 {10e-9, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {3, 5, 4};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF1 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            3, 0, 0};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF2 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            2, 4, 0};
        
        // Q Pot
        CircuitElement::VariableResistor VrQ {857e3, 2,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            4, 5, 0.35};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF1, VrF2, VrQ};

        circuit = CircuitModel(layout);
    }
};

// -------------------- SallenKeyFeedbackLPF --------------------

class SallenKeyFeedbackLPF : public Circuit
{
public:
    SallenKeyFeedbackLPF() {
        layout.numNodes = 5;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {500e3, 5, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Capacitor C1 {10e-9, 3, 0};
        CircuitElement::Capacitor C2 {10e-9, 2, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {3, 5, 4};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF1 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            1, 2, 1};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF2 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            2, 3, 1};
        
        // Q Pot
        CircuitElement::VariableResistor VrQ {857e3, 2,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            4, 5, 0.35};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF1, VrF2, VrQ};

        circuit = CircuitModel(layout);
    }
};

// -------------------- SubBesselSallenKeyHPF --------------------

class SubBesselSallenKeyHPF : public Circuit
{
public:
    SubBesselSallenKeyHPF() {
        layout.numNodes = 4;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        CircuitElement::Capacitor C2 {10e-9, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {3, 4, 4};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF1 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            3, 0, 0};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF2 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            2, 4, 0};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF1, VrF2};

        circuit = CircuitModel(layout);
    }
};

// -------------------- SubBesselSallenKeyLPF --------------------

class SubBesselSallenKeyLPF : public Circuit
{
public:
    SubBesselSallenKeyLPF() {
        layout.numNodes = 4;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Capacitor C1 {10e-9, 3, 0};
        CircuitElement::Capacitor C2 {10e-9, 2, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {3, 4, 4};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF1 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            1, 2, 1};
        
        // Cutoff Pot
        CircuitElement::VariableResistor VrF2 {500e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            2, 3, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF1, VrF2};

        circuit = CircuitModel(layout);
    }
};

// -------------------- ThreeBandBaxandallEQ --------------------

class ThreeBandBaxandallEQ : public Circuit
{
public:
    ThreeBandBaxandallEQ() {
        layout.numNodes = 12;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {12, 0};
        
        CircuitElement::Resistor R1 {6.8e3, 1, 2};
        CircuitElement::Resistor R2 {6.8e3, 4, 12};
        CircuitElement::Resistor R3 {2.2e3, 7, 12};
        CircuitElement::Resistor R4 {2.2e3, 1, 5};
        CircuitElement::Resistor R5 {68e3, 3, 9};
        CircuitElement::Resistor R6 {15e3, 6, 8};
        CircuitElement::Resistor R7 {10e3, 8, 10};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7};
        
        CircuitElement::Capacitor C1 {47e-9, 2, 4};
        CircuitElement::Capacitor C2 {10e-9, 5, 7};
        CircuitElement::Capacitor C3 {2.2e-9, 10, 11};
        CircuitElement::Capacitor C4 {10e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4};

        CircuitElement::OPAmp OP1 {0, 9, 12};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        // Bass Pot
        CircuitElement::Potentiometer PtB {20e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            2, 3, 4, 0.5};
        
        // Mid Pot
        CircuitElement::Potentiometer PtM {20e3, 2,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            5, 6, 7, 0.5};
        
        // Treble Pot
        CircuitElement::Potentiometer PtT {20e3, 3,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            1, 11, 12, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtM, PtT};

        circuit = CircuitModel(layout);
    }
};

// -------------------- TwoLFBaxandallToneControl --------------------

class TwoLFBaxandallToneControl : public Circuit
{
public:
    TwoLFBaxandallToneControl() {
        layout.numNodes = 9;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {9, 0};
        
        CircuitElement::Resistor R1 {1.8e3, 1, 2};
        CircuitElement::Resistor R2 {1.8e3, 4, 9};
        CircuitElement::Resistor R3 {12e3, 3, 5};
        CircuitElement::Resistor R4 {1.2e3, 6, 9};
        CircuitElement::Resistor R5 {1.2e3, 1, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {100e-9, 4, 3};
        CircuitElement::Capacitor C2 {100e-9, 3, 2};
        CircuitElement::Capacitor C3 {12e-9, 5, 7};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        CircuitElement::OPAmp OP1 {0, 5, 9};
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
            8, 7, 6, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtT};

        circuit = CircuitModel(layout);
    }
};

// -------------------- VariableFrequencyHFEQ --------------------

class VariableFrequencyHFEQ : public Circuit
{
public:
    VariableFrequencyHFEQ() {
        layout.numNodes = 8;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {8, 0};
        
        CircuitElement::Resistor R1 {22e3, 1, 7};
        CircuitElement::Resistor R2 {22e3, 7, 8};
        CircuitElement::Resistor R3 {7.5e3, 2, 3};
        CircuitElement::Resistor R4 {5.6e3, 3, 0};
        CircuitElement::Resistor R5 {6.8e3, 5, 6};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {2.2e-9, 4, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};

        CircuitElement::OPAmp OP1 {3, 4, 4};
        CircuitElement::OPAmp OP2 {5, 7, 8};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        // Gain pot
        CircuitElement::Potentiometer PtG {10e3, 1,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            1, 2, 8, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtG};
        
        // Frequency Pot
        CircuitElement::VariableResistor VrF {100e3, 2,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            6, 0, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF};

        circuit = CircuitModel(layout);
    }
};

// -------------------- VariableFrequencyLFEQ --------------------

class VariableFrequencyLFEQ : public Circuit
{
public:
    VariableFrequencyLFEQ() {
        layout.numNodes = 8;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {8, 0};
        
        CircuitElement::Resistor R1 {22e3, 1, 7};
        CircuitElement::Resistor R2 {22e3, 7, 8};
        CircuitElement::Resistor R3 {7.5e3, 2, 3};
        CircuitElement::Resistor R4 {5.6e3, 3, 0};
        CircuitElement::Resistor R5 {6.8e3, 5, 6};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {10e-9, 6, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};

        CircuitElement::OPAmp OP1 {3, 4, 4};
        CircuitElement::OPAmp OP2 {6, 7, 8};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        // Gain pot
        CircuitElement::Potentiometer PtG {10e3, 1,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            1, 2, 8, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtG};
        
        // Frequency pot
        CircuitElement::VariableResistor VrF {100e3, 2,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            4, 5, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF};

        circuit = CircuitModel(layout);
    }
};

// -------------------- VariableFrequencyVariableQMidEQ --------------------

class VariableFrequencyVariableQMidEQ : public Circuit
{
public:
    VariableFrequencyVariableQMidEQ() {
        layout.numNodes = 16;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {4.7e3, 1, 3};
        CircuitElement::Resistor R2 {4.7e3, 3, 5};
        CircuitElement::Resistor R3 {6.8e3, 11, 12};
        CircuitElement::Resistor R4 {2.2e3, 2, 8};
        CircuitElement::Resistor R5 {4.7e3, 8, 13};
        CircuitElement::Resistor R6 {2.2e3, 4, 0};
        CircuitElement::Resistor R7 {2.2e3, 4, 13};
        CircuitElement::Resistor R8 {12e3, 9, 10};
        CircuitElement::Resistor R9 {12e3, 9, 16};
        CircuitElement::Resistor R10 {470, 7, 8};
        CircuitElement::Resistor R11 {4.7e3, 6, 9};
        CircuitElement::Resistor R12 {6.8e3, 14, 15};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12};
        
        CircuitElement::Capacitor C1 {10e-9, 12, 13};
        CircuitElement::Capacitor C2 {47e-9, 15, 16};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {4, 3, 5};
        CircuitElement::OPAmp OP2 {8, 9, 10};
        CircuitElement::OPAmp OP3 {0, 12, 13};
        CircuitElement::OPAmp OP4 {0, 15, 16};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        // Frequency pot
        CircuitElement::VariableResistor VrF1 {100e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            10, 11, 0.5};
        
        // Frequency pot
        CircuitElement::VariableResistor VrF2 {100e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            13, 14, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF1, VrF2};

        // Gain pot
        CircuitElement::Potentiometer PtG {10e3, 2,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            1, 2, 5, 0.5};
        
        // Q pot
        CircuitElement::Potentiometer PtQ {100e3, 3,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LOG,
            6, 0, 7, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtG, PtQ};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- WienVariableFrequencyMidEQ --------------------

class WienVariableFrequencyMidEQ : public Circuit
{
public:
    WienVariableFrequencyMidEQ() {
        layout.numNodes = 8;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {8, 0};
        
        CircuitElement::Resistor R1 {6.8e3, 3, 4};
        CircuitElement::Resistor R2 {6.8e3, 6, 0};
        CircuitElement::Resistor R3 {22e3, 1, 7};
        CircuitElement::Resistor R4 {22e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};
        
        CircuitElement::Capacitor C1 {15e-9, 2, 3};
        CircuitElement::Capacitor C2 {6.8e-9, 5, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {5, 7, 8};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};

        // Mid pot
        CircuitElement::Potentiometer PtM {10e3, 1,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            1, 2, 8, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtM};
        
        // Frequency pot
        CircuitElement::VariableResistor VrF1 {100e3, 2,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            4, 5, 0.5};
        
        // Frequency pot
        CircuitElement::VariableResistor VrF2 {100e3, 2,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            5, 6, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrF1, VrF2};
        
        circuit = CircuitModel(layout);
    }
};

// End of namespace
}

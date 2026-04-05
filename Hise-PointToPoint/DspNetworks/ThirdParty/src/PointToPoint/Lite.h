//
//  Lite.h
//
//  Static (predefined cutoff) versions of various filter circuits
//
//
#include "Circuit.h"
#include "CircuitModel.h"
#include "CircuitElement.h"

#pragma once
namespace PointToPoint {

// -------------------- ButterworthSallenKeyHPF_30Hz --------------------
class ButterworthSallenKeyHPF_30Hz : public Circuit
{
public:
    ButterworthSallenKeyHPF_30Hz() {
        layout.numNodes = 4;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {747.30e3, 3, 0};
        CircuitElement::Resistor R2 {374.71e3, 2, 4};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        CircuitElement::Capacitor C2 {10e-9, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (3, 4, 4);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- ButterworthSallenKeyHPF_60Hz --------------------
class ButterworthSallenKeyHPF_60Hz : public Circuit
{
public:
    ButterworthSallenKeyHPF_60Hz() {
        layout.numNodes = 4;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {373.65e3, 3, 0};
        CircuitElement::Resistor R2 {187.36e3, 2, 4};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        CircuitElement::Capacitor C2 {10e-9, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (3, 4, 4);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- ButterworthSallenKeyHPF_90Hz --------------------
class ButterworthSallenKeyHPF_90Hz : public Circuit
{
public:
    ButterworthSallenKeyHPF_90Hz() {
        layout.numNodes = 4;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {249.92e3, 3, 0};
        CircuitElement::Resistor R2 {125.32e3, 2, 4};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        CircuitElement::Capacitor C2 {10e-9, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (3, 4, 4);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- ButterworthSallenKeyHPF_120Hz --------------------
class ButterworthSallenKeyHPF_120Hz : public Circuit
{
public:
    ButterworthSallenKeyHPF_120Hz() {
        layout.numNodes = 4;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {187.25e3, 3, 0};
        CircuitElement::Resistor R2 {93.89e3, 2, 4};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        CircuitElement::Capacitor C2 {10e-9, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (3, 4, 4);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- ButterworthSallenKeyLPF_2kHz --------------------
class ButterworthSallenKeyLPF_2kHz : public Circuit
{
public:
    ButterworthSallenKeyLPF_2kHz() {
        layout.numNodes = 4;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {7.95e3, 1, 2};
        CircuitElement::Resistor R2 {7.95e3, 2, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {7.07e-9, 3, 0};
        CircuitElement::Capacitor C2 {14.1e-9, 2, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (3, 4, 4);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- ButterworthSallenKeyLPF_4kHz --------------------
class ButterworthSallenKeyLPF_4kHz : public Circuit
{
public:
    ButterworthSallenKeyLPF_4kHz() {
        layout.numNodes = 4;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {3.99e3, 1, 2};
        CircuitElement::Resistor R2 {3.99e3, 2, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {7.07e-9, 3, 0};
        CircuitElement::Capacitor C2 {14.1e-9, 2, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (3, 4, 4);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- ButterworthSallenKeyLPF_8kHz --------------------
class ButterworthSallenKeyLPF_8kHz : public Circuit
{
public:
    ButterworthSallenKeyLPF_8kHz() {
        layout.numNodes = 4;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {1.99e3, 1, 2};
        CircuitElement::Resistor R2 {1.99e3, 2, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {7.07e-9, 3, 0};
        CircuitElement::Capacitor C2 {14.1e-9, 2, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (3, 4, 4);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- ButterworthSallenKeyLPF_16kHz --------------------
class ButterworthSallenKeyLPF_16kHz : public Circuit
{
public:
    ButterworthSallenKeyLPF_16kHz() {
        layout.numNodes = 4;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {1e3, 1, 2};
        CircuitElement::Resistor R2 {1e3, 2, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {7.07e-9, 3, 0};
        CircuitElement::Capacitor C2 {14.1e-9, 2, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (3, 4, 4);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FirstOrderStateVariableHPF_60Hz --------------------
class FirstOrderStateVariableHPF_60Hz : public Circuit
{
public:
    FirstOrderStateVariableHPF_60Hz() {
        layout.numNodes = 6;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 3, 0};
        CircuitElement::Resistor R3 {10e3, 3, 4};
        CircuitElement::Resistor R4 {10e3, 2, 6};
        CircuitElement::Resistor R5 {26.5e3, 4, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {100e-9, 5, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
        
        CircuitElement::OPAmp OP1 (2, 3, 4);
        CircuitElement::OPAmp OP2 (0, 5, 6);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FirstOrderStateVariableHPF_120Hz --------------------
class FirstOrderStateVariableHPF_120Hz : public Circuit
{
public:
    FirstOrderStateVariableHPF_120Hz() {
        layout.numNodes = 6;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 3, 0};
        CircuitElement::Resistor R3 {10e3, 3, 4};
        CircuitElement::Resistor R4 {10e3, 2, 6};
        CircuitElement::Resistor R5 {13.26e3, 4, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {100e-9, 5, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
        
        CircuitElement::OPAmp OP1 (2, 3, 4);
        CircuitElement::OPAmp OP2 (0, 5, 6);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FirstOrderStateVariableHPF_250Hz --------------------
class FirstOrderStateVariableHPF_250Hz : public Circuit
{
public:
    FirstOrderStateVariableHPF_250Hz() {
        layout.numNodes = 6;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 3, 0};
        CircuitElement::Resistor R3 {10e3, 3, 4};
        CircuitElement::Resistor R4 {10e3, 2, 6};
        CircuitElement::Resistor R5 {6.37e3, 4, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {100e-9, 5, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
        
        CircuitElement::OPAmp OP1 (2, 3, 4);
        CircuitElement::OPAmp OP2 (0, 5, 6);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FirstOrderStateVariableHPF_500Hz --------------------
class FirstOrderStateVariableHPF_500Hz : public Circuit
{
public:
    FirstOrderStateVariableHPF_500Hz() {
        layout.numNodes = 6;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 3, 0};
        CircuitElement::Resistor R3 {10e3, 3, 4};
        CircuitElement::Resistor R4 {10e3, 2, 6};
        CircuitElement::Resistor R5 {3.18e3, 4, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {100e-9, 5, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
        
        CircuitElement::OPAmp OP1 (2, 3, 4);
        CircuitElement::OPAmp OP2 (0, 5, 6);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FirstOrderStateVariableLPF_1kHz --------------------
class FirstOrderStateVariableLPF_1kHz : public Circuit
{
public:
    FirstOrderStateVariableLPF_1kHz() {
        layout.numNodes = 6;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 3, 0};
        CircuitElement::Resistor R3 {10e3, 3, 4};
        CircuitElement::Resistor R4 {10e3, 2, 6};
        CircuitElement::Resistor R5 {1.59e3, 4, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {100e-9, 5, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
        
        CircuitElement::OPAmp OP1 (2, 3, 4);
        CircuitElement::OPAmp OP2 (0, 5, 6);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FirstOrderStateVariableLPF_2kHz --------------------
class FirstOrderStateVariableLPF_2kHz : public Circuit
{
public:
    FirstOrderStateVariableLPF_2kHz() {
        layout.numNodes = 6;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 3, 0};
        CircuitElement::Resistor R3 {10e3, 3, 4};
        CircuitElement::Resistor R4 {10e3, 2, 6};
        CircuitElement::Resistor R5 {795, 4, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {100e-9, 5, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
        
        CircuitElement::OPAmp OP1 (2, 3, 4);
        CircuitElement::OPAmp OP2 (0, 5, 6);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FirstOrderStateVariableLPF_4kHz --------------------
class FirstOrderStateVariableLPF_4kHz : public Circuit
{
public:
    FirstOrderStateVariableLPF_4kHz() {
        layout.numNodes = 6;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 3, 0};
        CircuitElement::Resistor R3 {10e3, 3, 4};
        CircuitElement::Resistor R4 {10e3, 2, 6};
        CircuitElement::Resistor R5 {397.5, 4, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {100e-9, 5, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
        
        CircuitElement::OPAmp OP1 (2, 3, 4);
        CircuitElement::OPAmp OP2 (0, 5, 6);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FirstOrderStateVariableLPF_8kHz --------------------
class FirstOrderStateVariableLPF_8kHz : public Circuit
{
public:
    FirstOrderStateVariableLPF_8kHz() {
        layout.numNodes = 6;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 3, 0};
        CircuitElement::Resistor R3 {10e3, 3, 4};
        CircuitElement::Resistor R4 {10e3, 2, 6};
        CircuitElement::Resistor R5 {198.8, 4, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {100e-9, 5, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
        
        CircuitElement::OPAmp OP1 (2, 3, 4);
        CircuitElement::OPAmp OP2 (0, 5, 6);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FliegeHPF_30Hz --------------------
class FliegeHPF_30Hz : public Circuit
{
public:
    FliegeHPF_30Hz() {
        layout.numNodes = 6;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {530e3, 2, 3};
        CircuitElement::Resistor R2 {530e3, 4, 5};
        CircuitElement::Resistor R3 {374.71e3, 2, 0};
        CircuitElement::Resistor R4 {10e3, 5, 6};
        CircuitElement::Resistor R5 {10e3, 6, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        CircuitElement::Capacitor C2 {10e-9, 3, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (2, 4, 5);
        CircuitElement::OPAmp OP2 (6, 4, 3);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FliegeHPF_60Hz --------------------
class FliegeHPF_60Hz : public Circuit
{
public:
    FliegeHPF_60Hz() {
        layout.numNodes = 6;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {265e3, 2, 3};
        CircuitElement::Resistor R2 {265e3, 4, 5};
        CircuitElement::Resistor R3 {187.36e3, 2, 0};
        CircuitElement::Resistor R4 {10e3, 5, 6};
        CircuitElement::Resistor R5 {10e3, 6, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        CircuitElement::Capacitor C2 {10e-9, 3, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (2, 4, 5);
        CircuitElement::OPAmp OP2 (6, 4, 3);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FliegeHPF_90Hz --------------------
class FliegeHPF_90Hz : public Circuit
{
public:
    FliegeHPF_90Hz() {
        layout.numNodes = 6;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {176.67e3, 2, 3};
        CircuitElement::Resistor R2 {176.67e3, 4, 5};
        CircuitElement::Resistor R3 {124.91e3, 2, 0};
        CircuitElement::Resistor R4 {10e3, 5, 6};
        CircuitElement::Resistor R5 {10e3, 6, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        CircuitElement::Capacitor C2 {10e-9, 3, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (2, 4, 5);
        CircuitElement::OPAmp OP2 (6, 4, 3);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FliegeHPF_120Hz --------------------
class FliegeHPF_120Hz : public Circuit
{
public:
    FliegeHPF_120Hz() {
        layout.numNodes = 6;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {132.5e3, 2, 3};
        CircuitElement::Resistor R2 {132.5e3, 4, 5};
        CircuitElement::Resistor R3 {93.69e3, 2, 0};
        CircuitElement::Resistor R4 {10e3, 5, 6};
        CircuitElement::Resistor R5 {10e3, 6, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        CircuitElement::Capacitor C2 {10e-9, 3, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (2, 4, 5);
        CircuitElement::OPAmp OP2 (6, 4, 3);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FliegeLPF_2kHz --------------------
class FliegeLPF_2kHz : public Circuit
{
public:
    FliegeLPF_2kHz() {
        layout.numNodes = 6;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {7.95e3, 1, 2};
        CircuitElement::Resistor R2 {7.95e3, 3, 4};
        CircuitElement::Resistor R3 {5.62e3, 2, 3};
        CircuitElement::Resistor R4 {10e3, 5, 6};
        CircuitElement::Resistor R5 {10e3, 6, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {10e-9, 2, 3};
        CircuitElement::Capacitor C2 {10e-9, 4, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (2, 4, 5);
        CircuitElement::OPAmp OP2 (6, 4, 3);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FliegeLPF_4kHz --------------------
class FliegeLPF_4kHz : public Circuit
{
public:
    FliegeLPF_4kHz() {
        layout.numNodes = 6;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {3.99e3, 1, 2};
        CircuitElement::Resistor R2 {3.99e3, 3, 4};
        CircuitElement::Resistor R3 {2.82e3, 2, 3};
        CircuitElement::Resistor R4 {10e3, 5, 6};
        CircuitElement::Resistor R5 {10e3, 6, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {10e-9, 2, 3};
        CircuitElement::Capacitor C2 {10e-9, 4, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (2, 4, 5);
        CircuitElement::OPAmp OP2 (6, 4, 3);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FliegeLPF_8kHz --------------------
class FliegeLPF_8kHz : public Circuit
{
public:
    FliegeLPF_8kHz() {
        layout.numNodes = 6;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {1.99e3, 1, 2};
        CircuitElement::Resistor R2 {1.99e3, 3, 4};
        CircuitElement::Resistor R3 {1.41e3, 2, 3};
        CircuitElement::Resistor R4 {10e3, 5, 6};
        CircuitElement::Resistor R5 {10e3, 6, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {10e-9, 2, 3};
        CircuitElement::Capacitor C2 {10e-9, 4, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (2, 4, 5);
        CircuitElement::OPAmp OP2 (6, 4, 3);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FliegeLPF_16kHz --------------------
class FliegeLPF_16kHz : public Circuit
{
public:
    FliegeLPF_16kHz() {
        layout.numNodes = 6;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {1e3, 1, 2};
        CircuitElement::Resistor R2 {1e3, 3, 4};
        CircuitElement::Resistor R3 {707, 2, 3};
        CircuitElement::Resistor R4 {10e3, 5, 6};
        CircuitElement::Resistor R5 {10e3, 6, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {10e-9, 2, 3};
        CircuitElement::Capacitor C2 {10e-9, 4, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (2, 4, 5);
        CircuitElement::OPAmp OP2 (6, 4, 3);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableBPF_2kHz_A --------------------
class FourOpAmpStateVariableBPF_2kHz_A : public Circuit
{
public:
    FourOpAmpStateVariableBPF_2kHz_A() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {5e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {15.9e3, 5, 6};
        CircuitElement::Resistor R8 {15.9e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableBPF_2kHz_B --------------------
class FourOpAmpStateVariableBPF_2kHz_B : public Circuit
{
public:
    FourOpAmpStateVariableBPF_2kHz_B() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {12e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {15.9e3, 5, 6};
        CircuitElement::Resistor R8 {15.9e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableBPF_4kHz_A --------------------
class FourOpAmpStateVariableBPF_4kHz_A : public Circuit
{
public:
    FourOpAmpStateVariableBPF_4kHz_A() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {5e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {7.95e3, 5, 6};
        CircuitElement::Resistor R8 {7.95e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableBPF_4kHz_B --------------------
class FourOpAmpStateVariableBPF_4kHz_B : public Circuit
{
public:
    FourOpAmpStateVariableBPF_4kHz_B() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {12e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {7.95e3, 5, 6};
        CircuitElement::Resistor R8 {7.95e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableBPF_60Hz_A --------------------
class FourOpAmpStateVariableBPF_60Hz_A : public Circuit
{
public:
    FourOpAmpStateVariableBPF_60Hz_A() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {5e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {530e3, 5, 6};
        CircuitElement::Resistor R8 {530e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableBPF_60Hz_B --------------------
class FourOpAmpStateVariableBPF_60Hz_B : public Circuit
{
public:
    FourOpAmpStateVariableBPF_60Hz_B() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {12e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {530e3, 5, 6};
        CircuitElement::Resistor R8 {530e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableBPF_120Hz_A --------------------
class FourOpAmpStateVariableBPF_120Hz_A : public Circuit
{
public:
    FourOpAmpStateVariableBPF_120Hz_A() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {5e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {265e3, 5, 6};
        CircuitElement::Resistor R8 {265e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableBPF_120Hz_B --------------------
class FourOpAmpStateVariableBPF_120Hz_B : public Circuit
{
public:
    FourOpAmpStateVariableBPF_120Hz_B() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {12e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {265e3, 5, 6};
        CircuitElement::Resistor R8 {265e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableHPF_120Hz_A --------------------
class FourOpAmpStateVariableHPF_120Hz_A : public Circuit
{
public:
    FourOpAmpStateVariableHPF_120Hz_A() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {5e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {265e3, 5, 6};
        CircuitElement::Resistor R8 {265e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableHPF_120Hz_B --------------------
class FourOpAmpStateVariableHPF_120Hz_B : public Circuit
{
public:
    FourOpAmpStateVariableHPF_120Hz_B() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {12e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {265e3, 5, 6};
        CircuitElement::Resistor R8 {265e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableHPF_500Hz_A --------------------
class FourOpAmpStateVariableHPF_500Hz_A : public Circuit
{
public:
    FourOpAmpStateVariableHPF_500Hz_A() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {5e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {63.6e3, 5, 6};
        CircuitElement::Resistor R8 {63.6e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableHPF_500Hz_B --------------------
class FourOpAmpStateVariableHPF_500Hz_B : public Circuit
{
public:
    FourOpAmpStateVariableHPF_500Hz_B() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {12e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {63.6e3, 5, 6};
        CircuitElement::Resistor R8 {63.6e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableLPF_2kHz_A --------------------
class FourOpAmpStateVariableLPF_2kHz_A : public Circuit
{
public:
    FourOpAmpStateVariableLPF_2kHz_A() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {9, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {5e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {15.9e3, 5, 6};
        CircuitElement::Resistor R8 {15.9e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableLPF_2kHz_B --------------------
class FourOpAmpStateVariableLPF_2kHz_B : public Circuit
{
public:
    FourOpAmpStateVariableLPF_2kHz_B() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {9, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {12e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {15.9e3, 5, 6};
        CircuitElement::Resistor R8 {15.9e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableLPF_8kHz_A --------------------
class FourOpAmpStateVariableLPF_8kHz_A : public Circuit
{
public:
    FourOpAmpStateVariableLPF_8kHz_A() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {9, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {5e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {3.99e3, 5, 6};
        CircuitElement::Resistor R8 {3.99e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableLPF_8kHz_B --------------------
class FourOpAmpStateVariableLPF_8kHz_B : public Circuit
{
public:
    FourOpAmpStateVariableLPF_8kHz_B() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {9, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {12e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {3.99e3, 5, 6};
        CircuitElement::Resistor R8 {3.99e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableNotch_4kHz_A --------------------
class FourOpAmpStateVariableNotch_4kHz_A : public Circuit
{
public:
    FourOpAmpStateVariableNotch_4kHz_A() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {5e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {7.95e3, 5, 6};
        CircuitElement::Resistor R8 {7.95e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableNotch_4kHz_B --------------------
class FourOpAmpStateVariableNotch_4kHz_B : public Circuit
{
public:
    FourOpAmpStateVariableNotch_4kHz_B() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {12e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {7.95e3, 5, 6};
        CircuitElement::Resistor R8 {7.95e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableNotch_8kHz_A --------------------
class FourOpAmpStateVariableNotch_8kHz_A : public Circuit
{
public:
    FourOpAmpStateVariableNotch_8kHz_A() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {5e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {3.99e3, 5, 6};
        CircuitElement::Resistor R8 {3.99e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FourOpAmpStateVariableNotch_8kHz_B --------------------
class FourOpAmpStateVariableNotch_8kHz_B : public Circuit
{
public:
    FourOpAmpStateVariableNotch_8kHz_B() {
        layout.numNodes = 9;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 3};
        CircuitElement::Resistor R3 {10e3, 2, 7};
        CircuitElement::Resistor R4 {12e3, 3, 4}; // Q
        CircuitElement::Resistor R5 {10e3, 4, 5};
        CircuitElement::Resistor R6 {10e3, 4, 9};
        CircuitElement::Resistor R7 {3.99e3, 5, 6};
        CircuitElement::Resistor R8 {3.99e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};
        
        CircuitElement::Capacitor C1 {5e-9, 6, 7};
        CircuitElement::Capacitor C2 {5e-9, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (0, 2, 3);
        CircuitElement::OPAmp OP2 (0, 4, 5);
        CircuitElement::OPAmp OP3 (0, 6, 7);
        CircuitElement::OPAmp OP4 (0, 8, 9);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2, OP3, OP4};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- SubBesselSallenKeyHPF_30Hz --------------------
class SubBesselSallenKeyHPF_30Hz : public Circuit
{
public:
    SubBesselSallenKeyHPF_30Hz() {
        layout.numNodes = 4;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {530e3, 3, 0};
        CircuitElement::Resistor R2 {530e3, 2, 4};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        CircuitElement::Capacitor C2 {10e-9, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (3, 4, 4);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- SubBesselSallenKeyHPF_60Hz --------------------
class SubBesselSallenKeyHPF_60Hz : public Circuit
{
public:
    SubBesselSallenKeyHPF_60Hz() {
        layout.numNodes = 4;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {265e3, 3, 0};
        CircuitElement::Resistor R2 {265e3, 2, 4};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        CircuitElement::Capacitor C2 {10e-9, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (3, 4, 4);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- SubBesselSallenKeyHPF_90Hz --------------------
class SubBesselSallenKeyHPF_90Hz : public Circuit
{
public:
    SubBesselSallenKeyHPF_90Hz() {
        layout.numNodes = 4;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {176.67e3, 3, 0};
        CircuitElement::Resistor R2 {176.67e3, 2, 4};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        CircuitElement::Capacitor C2 {10e-9, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (3, 4, 4);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- SubBesselSallenKeyHPF_120Hz --------------------
class SubBesselSallenKeyHPF_120Hz : public Circuit
{
public:
    SubBesselSallenKeyHPF_120Hz() {
        layout.numNodes = 4;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {132.5e3, 3, 0};
        CircuitElement::Resistor R2 {132.5e3, 2, 4};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        CircuitElement::Capacitor C2 {10e-9, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (3, 4, 4);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- SubBesselSallenKeyLPF_2kHz --------------------
class SubBesselSallenKeyLPF_2kHz : public Circuit
{
public:
    SubBesselSallenKeyLPF_2kHz() {
        layout.numNodes = 4;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {7.95e3, 1, 2};
        CircuitElement::Resistor R2 {7.95e3, 2, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {10e-9, 3, 0};
        CircuitElement::Capacitor C2 {10e-9, 2, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (3, 4, 4);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- SubBesselSallenKeyLPF_4kHz --------------------
class SubBesselSallenKeyLPF_4kHz : public Circuit
{
public:
    SubBesselSallenKeyLPF_4kHz() {
        layout.numNodes = 4;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {3.99e3, 1, 2};
        CircuitElement::Resistor R2 {3.99e3, 2, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {10e-9, 3, 0};
        CircuitElement::Capacitor C2 {10e-9, 2, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (3, 4, 4);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- SubBesselSallenKeyLPF_8kHz --------------------
class SubBesselSallenKeyLPF_8kHz : public Circuit
{
public:
    SubBesselSallenKeyLPF_8kHz() {
        layout.numNodes = 4;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {1.99e3, 1, 2};
        CircuitElement::Resistor R2 {1.99e3, 2, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {10e-9, 3, 0};
        CircuitElement::Capacitor C2 {10e-9, 2, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (3, 4, 4);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- SubBesselSallenKeyLPF_16kHz --------------------
class SubBesselSallenKeyLPF_16kHz : public Circuit
{
public:
    SubBesselSallenKeyLPF_16kHz() {
        layout.numNodes = 4;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::Resistor R1 {1e3, 1, 2};
        CircuitElement::Resistor R2 {1e3, 2, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {10e-9, 3, 0};
        CircuitElement::Capacitor C2 {10e-9, 2, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::OPAmp OP1 (3, 4, 4);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- TwinTNotchFilter_4kHz --------------------
class TwinTNotchFilter_4kHz : public Circuit
{
public:
    TwinTNotchFilter_4kHz() {
        layout.numNodes = 7;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};
        
        CircuitElement::Resistor R1 {3.8e3, 1, 2};
        CircuitElement::Resistor R2 {3.8e3, 2, 4};
        CircuitElement::Resistor R3 {1.9e3, 3, 5};
        CircuitElement::Resistor R4 {1e3, 6, 7};
        CircuitElement::Resistor R5 {10e3, 7, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 3};
        CircuitElement::Capacitor C2 {10e-9, 3, 4};
        CircuitElement::Capacitor C3 {20e-9, 2, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
        
        CircuitElement::OPAmp OP1 (4, 6, 6);
        CircuitElement::OPAmp OP2 (7, 5, 5);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- TwinTNotchFilter_6kHz --------------------
class TwinTNotchFilter_6kHz : public Circuit
{
public:
    TwinTNotchFilter_6kHz() {
        layout.numNodes = 7;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};
        
        CircuitElement::Resistor R1 {2.53e3, 1, 2};
        CircuitElement::Resistor R2 {2.53e3, 2, 4};
        CircuitElement::Resistor R3 {1.26e3, 3, 5};
        CircuitElement::Resistor R4 {1e3, 6, 7};
        CircuitElement::Resistor R5 {10e3, 7, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 3};
        CircuitElement::Capacitor C2 {10e-9, 3, 4};
        CircuitElement::Capacitor C3 {20e-9, 2, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
        
        CircuitElement::OPAmp OP1 (4, 6, 6);
        CircuitElement::OPAmp OP2 (7, 5, 5);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- TwinTNotchFilter_8kHz --------------------
class TwinTNotchFilter_8kHz : public Circuit
{
public:
    TwinTNotchFilter_8kHz() {
        layout.numNodes = 7;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};
        
        CircuitElement::Resistor R1 {1.8e3, 1, 2};
        CircuitElement::Resistor R2 {1.8e3, 2, 4};
        CircuitElement::Resistor R3 {900, 3, 5};
        CircuitElement::Resistor R4 {1e3, 6, 7};
        CircuitElement::Resistor R5 {10e3, 7, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 3};
        CircuitElement::Capacitor C2 {10e-9, 3, 4};
        CircuitElement::Capacitor C3 {20e-9, 2, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
        
        CircuitElement::OPAmp OP1 (4, 6, 6);
        CircuitElement::OPAmp OP2 (7, 5, 5);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- TwinTNotchFilter_10kHz --------------------
class TwinTNotchFilter_10kHz : public Circuit
{
public:
    TwinTNotchFilter_10kHz() {
        layout.numNodes = 7;
            
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};
        
        CircuitElement::Resistor R1 {1.35e3, 1, 2};
        CircuitElement::Resistor R2 {1.35e3, 2, 4};
        CircuitElement::Resistor R3 {675, 3, 5};
        CircuitElement::Resistor R4 {1e3, 6, 7};
        CircuitElement::Resistor R5 {10e3, 7, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 3};
        CircuitElement::Capacitor C2 {10e-9, 3, 4};
        CircuitElement::Capacitor C3 {20e-9, 2, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
        
        CircuitElement::OPAmp OP1 (4, 6, 6);
        CircuitElement::OPAmp OP2 (7, 5, 5);
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};
        
        circuit = CircuitModel(layout);
    }
};

// End of namespace
}

//
//  AmpClippers.h
//
//  Collection of nonlinear clipping circuits based on guitar amplifiers
//
//
#include "Circuit.h"
#include "CircuitModel.h"
#include "CircuitElement.h"

#pragma once
namespace PointToPoint {

// -------------------- AmpegB15Portaflex1A --------------------
class AmpegB15Portaflex1A : public Circuit
{
public:
    AmpegB15Portaflex1A() {
        layout.numNodes = 5;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::VoltageSource Vs1 {500, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {47e3, 1, 2};
        CircuitElement::Resistor R2 {5.6e6, 2, 0};
        CircuitElement::Resistor R3 {5.6e6, 3, 0};
        CircuitElement::Resistor R4 {470e3, 4, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};

        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 2, 4, 3};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};

        layout.hasDCBlocker = true;

        circuit = CircuitModel(layout);
    }
};


// -------------------- AmpegB15Portaflex1B --------------------
class AmpegB15Portaflex1B : public Circuit
{
public:
    AmpegB15Portaflex1B() {
        layout.numNodes = 5;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::VoltageSource Vs1 {500, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {100e3, 1, 2};
        CircuitElement::Resistor R2 {5.6e6, 2, 0};
        CircuitElement::Resistor R3 {5.6e6, 3, 0};
        CircuitElement::Resistor R4 {470e3, 4, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};
        
        CircuitElement::Capacitor C1 {0.005e-6, 1, 2};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};

        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 2, 4, 3};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};

        layout.hasDCBlocker = true;

        circuit = CircuitModel(layout);
    }
};


// -------------------- AmpegB15Portaflex2A --------------------
class AmpegB15Portaflex2A : public Circuit
{
public:
    AmpegB15Portaflex2A() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::VoltageSource Vs1 {500, 6};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {39e3, 2, 0};
        CircuitElement::Resistor R2 {2.2e3, 7, 0};
        CircuitElement::Resistor R3 {220e3, 5, 6};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {0.02e-6, 1, 2};
        CircuitElement::Capacitor C2 {0.01e-6, 1, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 4, 5, 7};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            3, 4, 0, 0.05};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};

        layout.hasDCBlocker = true;

        circuit = CircuitModel(layout);
    }
};


// -------------------- AmpegB15Portaflex2B --------------------
class AmpegB15Portaflex2B : public Circuit
{
public:
    AmpegB15Portaflex2B() {
        layout.numNodes = 8;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::VoltageSource Vs1 {500, 6};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {39e3, 2, 8};
        CircuitElement::Resistor R2 {2.2e3, 7, 0};
        CircuitElement::Resistor R3 {220e3, 5, 6};
        CircuitElement::Resistor R4 {1e6, 8, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};
        
        CircuitElement::Capacitor C1 {0.02e-6, 1, 2};
        CircuitElement::Capacitor C2 {0.01e-6, 1, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 4, 5, 7};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            3, 4, 0, 0.05};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};

        layout.hasDCBlocker = true;

        circuit = CircuitModel(layout);
    }
};



// -------------------- AmpegB15Portaflex2C --------------------
class AmpegB15Portaflex2C : public Circuit
{
public:
    AmpegB15Portaflex2C() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::VoltageSource Vs1 {500, 6};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {39e3, 2, 0};
        CircuitElement::Resistor R2 {2.2e3, 7, 0};
        CircuitElement::Resistor R3 {220e3, 5, 6};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {0.02e-6, 1, 2};
        CircuitElement::Capacitor C2 {0.01e-6, 1, 3};
        CircuitElement::Capacitor C3 {500e-12, 3, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 4, 5, 7};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            3, 4, 0, 0.05};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};

        layout.hasDCBlocker = true;

        circuit = CircuitModel(layout);
    }
};


// -------------------- AmpegB15Portaflex2D --------------------
class AmpegB15Portaflex2D : public Circuit
{
public:
    AmpegB15Portaflex2D() {
        layout.numNodes = 8;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::VoltageSource Vs1 {500, 6};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {39e3, 2, 8};
        CircuitElement::Resistor R2 {2.2e3, 7, 0};
        CircuitElement::Resistor R3 {220e3, 5, 6};
        CircuitElement::Resistor R4 {1e6, 8, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};
        
        CircuitElement::Capacitor C1 {0.02e-6, 1, 2};
        CircuitElement::Capacitor C2 {0.01e-6, 1, 3};
        CircuitElement::Capacitor C3 {500e-12, 3, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 4, 5, 7};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {1e6, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            3, 4, 0, 0.05};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};

        layout.hasDCBlocker = true;

        circuit = CircuitModel(layout);
    }
};


// -------------------- BognerEcstasy1 --------------------
class BognerEcstasy1 : public Circuit
{
public:
    BognerEcstasy1() {
        
        layout.numNodes = 5;
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::VoltageSource Vs1 {240, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};
        
        CircuitElement::Resistor R1 {68e3, 1, 2};
        CircuitElement::Resistor R2 {820, 3, 0};
        CircuitElement::Resistor R3 {100e3, 4, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {0.68e-6, 3, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 2, 4, 3};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
                        
        layout.hasDCBlocker = true;
        
        layout.Output = 0.64;
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- BognerEcstasy2A --------------------
class BognerEcstasy2A : public Circuit
{
public:
    BognerEcstasy2A() {
        layout.numNodes = 5;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::VoltageSource Vs1 {256, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};
        
        CircuitElement::Resistor R1 {470e3, 1, 2};
        CircuitElement::Resistor R2 {500e3, 2, 0};
        CircuitElement::Resistor R3 {4.75e3, 3, 0};
        CircuitElement::Resistor R4 {100e3, 4, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};
        
        CircuitElement::Capacitor C1 {470e-12, 1, 2};
        CircuitElement::Capacitor C2 {0.001e-6, 4, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 2, 4, 3};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        layout.hasDCBlocker = true;
        
        layout.Output = 0.8;
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- BognerEcstasy2B --------------------
class BognerEcstasy2B : public Circuit
{
public:
    BognerEcstasy2B() {
        layout.numNodes = 5;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::VoltageSource Vs1 {256, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};
        
        CircuitElement::Resistor R1 {470e3, 1, 2};
        CircuitElement::Resistor R2 {500e3, 2, 0};
        CircuitElement::Resistor R3 {4.75e3, 3, 0};
        CircuitElement::Resistor R4 {100e3, 4, 5};
        CircuitElement::Resistor R5 {100e3, 2, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {470e-12, 1, 2};
        CircuitElement::Capacitor C2 {0.001e-6, 4, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 2, 4, 3};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        layout.hasDCBlocker = true;
        
        layout.Output = 0.88;
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- BognerEcstasy3 --------------------
class BognerEcstasy3 : public Circuit
{
public:
    BognerEcstasy3() {
        
        layout.numNodes = 6;
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::VoltageSource Vs1 {256, 6};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};
        
        CircuitElement::Resistor R1 {500e3, 1, 2};
        CircuitElement::Resistor R2 {500e3, 2, 0};
        CircuitElement::Resistor R3 {500e3, 2, 3};
        CircuitElement::Resistor R4 {10e3, 4, 0};
        CircuitElement::Resistor R5 {100e3, 5, 6};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};
        
        CircuitElement::Capacitor C1 {470e-12, 2, 3};
        CircuitElement::Capacitor C2 {470e-12, 5, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 3, 5, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        layout.hasDCBlocker = true;
        
        layout.Output = 0.87;
        
        circuit = CircuitModel(layout);
    }
};



// -------------------- FenderBassman100_1 --------------------
class FenderBassman100_1 : public Circuit
{
public:
    FenderBassman100_1() {
        layout.numNodes = 5;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::VoltageSource Vs1 {375, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};
        
        CircuitElement::Resistor R1 {68e3, 1, 2};
        CircuitElement::Resistor R2 {1.068e6, 2, 0};
        CircuitElement::Resistor R3 {100e3, 4, 5};
        CircuitElement::Resistor R4 {1500, 3, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};
        
        CircuitElement::Capacitor C1 {25e-9, 3, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 2, 4, 3};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        layout.hasDCBlocker = true;
        
        layout.Output = 0.69;
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- FenderBassman100_2A --------------------
class FenderBassman100_2A : public Circuit
{
public:
    FenderBassman100_2A() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};
        
        CircuitElement::VoltageSource Vs1 {375, 6};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};
        
        CircuitElement::Resistor R1 {920, 4, 0};
        CircuitElement::Resistor R2 {100e3, 5, 6};
        CircuitElement::Resistor R3 {220e3, 5, 7};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {0.047e-6, 1, 2};
        CircuitElement::Capacitor C2 {5e-9, 4, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 3, 5, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        // Gain Pot
        CircuitElement::Potentiometer PtG {1e6, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            2, 3, 0, 1};
                
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtG};
        
        layout.hasDCBlocker = true;
        
        layout.Output = 0.67;
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- FenderBassman100_2B --------------------
class FenderBassman100_2B : public Circuit
{
public:
    FenderBassman100_2B() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};
        
        CircuitElement::VoltageSource Vs1 {375, 6};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};
        
        CircuitElement::Resistor R1 {920, 4, 0};
        CircuitElement::Resistor R2 {100e3, 5, 6};
        CircuitElement::Resistor R3 {220e3, 5, 7};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {0.047e-6, 1, 2};
        CircuitElement::Capacitor C2 {5e-9, 4, 0};
        CircuitElement::Capacitor C3 {120e-12, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 3, 5, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        // Gain Pot
        CircuitElement::Potentiometer PtG {1e6, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            2, 3, 0, 1};
                
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtG};
        
        layout.hasDCBlocker = true;
        
        layout.Output = 0.67;
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- MarshallJCM800_2203_1A --------------------
class MarshallJCM800_2203_1A : public Circuit
{
public:
    MarshallJCM800_2203_1A() {
        layout.numNodes = 6;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};

        CircuitElement::VoltageSource Vs1 {500, 6};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {470e3, 1, 2};
        CircuitElement::Resistor R2 {100e3, 6, 5};
        CircuitElement::Resistor R3 {10e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::Capacitor C1 {470e-12, 1, 2};
        CircuitElement::Capacitor C2 {1e-9, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 3, 5, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};

        CircuitElement::Potentiometer PtV {1e6, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 0, 0.05};
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};

        layout.hasDCBlocker = true;
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- RolandJazzChorus1 --------------------
class RolandJazzChorus1 : public Circuit
{
public:
    RolandJazzChorus1() {
        layout.numNodes = 5;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};

        CircuitElement::Resistor R1 {1e3, 1, 2};
        CircuitElement::Resistor R2 {1e6, 2, 0};
        CircuitElement::Resistor R3 {39e3, 3, 0};
        CircuitElement::Resistor R4 {100e3, 3, 4};
        CircuitElement::Resistor R5 {1e6, 5, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};

        CircuitElement::Capacitor C1 {100e-12, 2, 0};
        CircuitElement::Capacitor C2 {47e-12, 3, 4};
        CircuitElement::Capacitor C3 {0.082e-6, 4, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        CircuitElement::OPAmp OP1 {2, 3, 4};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        layout.Output = 0.88;
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- RolandJazzChorus2A --------------------
class RolandJazzChorus2A : public Circuit
{
public:
    RolandJazzChorus2A() {
        layout.numNodes = 12;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {10, 0};

        CircuitElement::Resistor R1 {1e3, 1, 2};
        CircuitElement::Resistor R2 {47e3, 3, 4};
        CircuitElement::Resistor R3 {270e3, 5, 0};
        CircuitElement::Resistor R4 {3.9e3, 5, 6};
        CircuitElement::Resistor R5 {3.9e3, 6, 10};
        CircuitElement::Resistor R6 {1.5e6, 9, 0};
        CircuitElement::Resistor R7 {1e3, 3, 11};
        CircuitElement::Resistor R8 {50e3, 12, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};

        CircuitElement::Capacitor C1 {100e-12, 3, 4};
        CircuitElement::Capacitor C2 {0.082e-6, 4, 5};
        CircuitElement::Capacitor C3 {0.082e-6, 7, 9};
        CircuitElement::Capacitor C4 {1e-9, 8, 9};
        CircuitElement::Capacitor C5 {0.01e-6, 10, 9};
        CircuitElement::Capacitor C6 {10e-9, 11, 12};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5, C6};

        CircuitElement::OPAmp OP1 {2, 3, 4};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
                            CircuitElement::Diode::Configuration::MATCHEDPAIR,
                            6, 7};
        CircuitElement::Diode D2 {CircuitElement::Diode::Semiconductor::SILICON,
                            CircuitElement::Diode::Configuration::MATCHEDPAIR,
                            10, 8};
        
        layout.Ds = std::vector<CircuitElement::Diode> {D1, D2};
        
        layout.Output = 0.94;
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- RolandJazzChorus2B --------------------
class RolandJazzChorus2B : public Circuit
{
public:
    RolandJazzChorus2B() {
        layout.numNodes = 13;
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {10, 0};

        CircuitElement::Resistor R1 {1e3, 1, 2};
        CircuitElement::Resistor R2 {47e3, 3, 4};
        CircuitElement::Resistor R3 {270e3, 5, 0};
        CircuitElement::Resistor R4 {3.9e3, 5, 6};
        CircuitElement::Resistor R5 {3.9e3, 6, 10};
        CircuitElement::Resistor R6 {1.5e6, 9, 0};
        CircuitElement::Resistor R7 {1e3, 3, 11};
        CircuitElement::Resistor R8 {50e3, 13, 9};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7, R8};

        CircuitElement::Capacitor C1 {100e-12, 3, 4};
        CircuitElement::Capacitor C2 {0.082e-6, 4, 5};
        CircuitElement::Capacitor C3 {0.082e-6, 7, 9};
        CircuitElement::Capacitor C4 {1e-9, 8, 9};
        CircuitElement::Capacitor C5 {0.01e-6, 10, 9};
        CircuitElement::Capacitor C6 {0.01e-6, 11, 12};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5, C6};

        CircuitElement::OPAmp OP1 {2, 3, 4};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};

        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
                        CircuitElement::Diode::Configuration::MATCHEDPAIR,
                        6, 7};
        CircuitElement::Diode D2 {CircuitElement::Diode::Semiconductor::SILICON,
                        CircuitElement::Diode::Configuration::MATCHEDPAIR,
                        10, 8};
        CircuitElement::Diode D3{CircuitElement::Diode::Semiconductor::SILICON,
                        CircuitElement::Diode::Configuration::MATCHEDPAIR,
                        9, 0};
        layout.Ds = std::vector<CircuitElement::Diode> {D1, D2, D3};

        // Distortion Pot
        CircuitElement::VariableResistor VrD {50e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        12, 13, 0.5};

        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrD};

        layout.Output = 0.96;

        circuit = CircuitModel(layout);
    }
};


// -------------------- SoldanoSuperLead100_1 --------------------
class SoldanoSuperLead100_1 : public Circuit
{
public:
    SoldanoSuperLead100_1() {
        layout.numNodes = 5;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::VoltageSource Vs1 {359, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {1e6, 1, 0};
        CircuitElement::Resistor R2 {68e3, 1, 2};
        CircuitElement::Resistor R3 {1.8e3, 3, 0};
        CircuitElement::Resistor R4 {220e3, 4, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};

        CircuitElement::Capacitor C1 {1e-6, 3, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};

        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 2, 4, 3};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};

        layout.hasDCBlocker = true;

        layout.Output = 0.62;

        circuit = CircuitModel(layout);
    }
};


// -------------------- SoldanoSuperLead100_2A --------------------
class SoldanoSuperLead100_2A : public Circuit
{
public:
    SoldanoSuperLead100_2A() {
        layout.numNodes = 6;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::VoltageSource Vs1 {359, 6};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {2.2e3, 4, 0};
        CircuitElement::Resistor R2 {100e3, 5, 6};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};

        CircuitElement::Capacitor C1 {470e-12, 1, 2};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};

        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 3, 5, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        CircuitElement::Potentiometer PtG {500e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 0, 0.05};
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtG};

        layout.hasDCBlocker = true;
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- SoldanoSuperLead100_2B --------------------
class SoldanoSuperLead100_2B : public Circuit
{
public:
    SoldanoSuperLead100_2B() {
        layout.numNodes = 6;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::VoltageSource Vs1 {359, 6};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {2.2e3, 4, 0};
        CircuitElement::Resistor R2 {100e3, 5, 6};
        CircuitElement::Resistor R3 {470e3, 1, 2};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 3, 5, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        // Gain Pot
        CircuitElement::Potentiometer PtG {500e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 0, 0.05};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtG};

        layout.hasDCBlocker = true;
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- VoxAC10 --------------------
class VoxAC10 : public Circuit
{
public:
    VoxAC10() {
        layout.numNodes = 5;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::VoltageSource Vs1 {255, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {220e3, 1, 2};
        CircuitElement::Resistor R2 {1e6, 2, 0};
        CircuitElement::Resistor R3 {820, 4, 0};
        CircuitElement::Resistor R4 {220e3, 3, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};
        
        CircuitElement::Capacitor C1 {25e-9, 4, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};

        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::Model12AX7::EXH, 2, 3, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
                
        layout.hasDCBlocker = true;
        
        layout.Output = 0.64;
        
        circuit = CircuitModel(layout);
    }
};

// End of namespace
}

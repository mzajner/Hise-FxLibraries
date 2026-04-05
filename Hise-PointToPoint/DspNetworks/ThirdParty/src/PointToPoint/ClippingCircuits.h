//
//  ClippingCircuits.h
//
//  Collection of basic clipping circuits
//
//
#include "Circuit.h"
#include "CircuitModel.h"
#include "CircuitElement.h"

#pragma once
namespace PointToPoint {

// -------------------- BiasDiodeGE_A --------------------

class BiasDiodeGE_A : public Circuit
{
public:
    BiasDiodeGE_A() {
        layout.numNodes = 3;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {2, 0};
        
        CircuitElement::VoltageSource Vs1 {0.5, 3};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {1e6, 2, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::GERMANIUM,
            CircuitElement::Diode::Configuration::MATCHEDPAIR,
            3, 2};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};

        // Bias Pot
        CircuitElement::VariableResistor VrBI {1e6, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            1, 2, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrBI};

        layout.hasDCBlocker = true;
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- BiasDiodeGE_B --------------------

class BiasDiodeGE_B : public Circuit
{
public:
    BiasDiodeGE_B() {
        layout.numNodes = 3;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {2, 0};
        
        CircuitElement::VoltageSource Vs1 {0.5, 3};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {1e6, 2, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::GERMANIUM,
            CircuitElement::Diode::Configuration::SINGLE,
            3, 2};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};

        // Bias Pot
        CircuitElement::VariableResistor VrBI {1e6, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            1, 2, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrBI};

        layout.hasDCBlocker = true;
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- BiasDiodeSI_A --------------------

class BiasDiodeSI_A : public Circuit
{
public:
    BiasDiodeSI_A() {
        layout.numNodes = 3;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {2, 0};
        
        CircuitElement::VoltageSource Vs1 {0.5, 3};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {1e6, 2, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
            CircuitElement::Diode::Configuration::MATCHEDPAIR,
            3, 2};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};

        // Bias Pot
        CircuitElement::VariableResistor VrBI {1e6, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            1, 2, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrBI};

        layout.hasDCBlocker = true;
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- BiasDiodeSI_B --------------------

class BiasDiodeSI_B : public Circuit
{
public:
    BiasDiodeSI_B() {
        layout.numNodes = 3;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {2, 0};
        
        CircuitElement::VoltageSource Vs1 {0.5, 3};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {1e6, 2, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
            CircuitElement::Diode::Configuration::SINGLE,
            3, 2};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};

        // Bias Pot
        CircuitElement::VariableResistor VrBI {1e6, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            1, 2, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrBI};

        layout.hasDCBlocker = true;
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- BJT_NPN_GE --------------------

class BJT_NPN_GE : public Circuit
{
public:
    BJT_NPN_GE() {
        layout.numNodes = 6;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::VoltageSource Vs1 {9, 6};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {1e3, 1, 2};
        CircuitElement::Resistor R2 {150e3, 4, 0};
        CircuitElement::Resistor R3 {1e3, 3, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::BJT BJT1 {CircuitElement::BJT::Doping::NPN,
                        CircuitElement::BJT::Semiconductor::GERMANIUM,
                        2, 3, 4};
        layout.BJTs = std::vector<CircuitElement::BJT> {BJT1};
        
        // Bias Pot
        CircuitElement::VariableResistor VrBI {199e3, 1,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            5, 6, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrBI};

        layout.hasDCBlocker = true;
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- BJT_NPN_SI --------------------

class BJT_NPN_SI : public Circuit
{
public:
    BJT_NPN_SI() {
        layout.numNodes = 6;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::VoltageSource Vs1 {9, 6};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {1e3, 1, 2};
        CircuitElement::Resistor R2 {100e3, 4, 0};
        CircuitElement::Resistor R3 {1e3, 3, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::BJT BJT1 {CircuitElement::BJT::Doping::NPN,
                        CircuitElement::BJT::Semiconductor::SILICON,
                        2, 3, 4};
        layout.BJTs = std::vector<CircuitElement::BJT> {BJT1};
        
        // Bias Pot
        CircuitElement::VariableResistor VrBI {199e3, 1,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            5, 6, 1};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrBI};

        layout.hasDCBlocker = true;
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- DiodeHardGE --------------------

class DiodeHardGE : public Circuit
{
public:
    DiodeHardGE() {
        layout.numNodes = 3;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {2, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::GERMANIUM,
            CircuitElement::Diode::Configuration::MATCHEDPAIR,
            2, 3};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};

        // Distortion Pot
        CircuitElement::VariableResistor VrD {100e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            3, 0, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrD};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- DiodeHardSI --------------------

class DiodeHardSI : public Circuit
{
public:
    DiodeHardSI() {
        layout.numNodes = 3;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {2, 0};
        
        CircuitElement::Resistor R1 {10e3, 1, 2};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
            CircuitElement::Diode::Configuration::MATCHEDPAIR,
            2, 3};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};

        // Distortion Pot
        CircuitElement::VariableResistor VrD {100e3, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            3, 0, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrD};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- DiodeHPF_GE --------------------

class DiodeHPF_GE : public Circuit
{
public:
    DiodeHPF_GE() {
        layout.numNodes = 3;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {2, 0};
        
        CircuitElement::Resistor R1 {1e3, 3, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};

        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::GERMANIUM,
            CircuitElement::Diode::Configuration::MATCHEDPAIR,
            2, 0};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};

        // Distortion Pot
        CircuitElement::VariableResistor VrD {2e6, 1,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LOG,
            2, 3, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrD};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- DiodeHPF_SI --------------------

class DiodeHPF_SI : public Circuit
{
public:
    DiodeHPF_SI() {
        layout.numNodes = 3;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {2, 0};
        
        CircuitElement::Resistor R1 {1e3, 3, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Capacitor C1 {10e-9, 1, 2};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
            CircuitElement::Diode::Configuration::MATCHEDPAIR,
            2, 0};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};

        // Distortion Pot
        CircuitElement::VariableResistor VrD {2e6, 1,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LOG,
            2, 3, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrD};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- DiodeLPF_GE --------------------

class DiodeLPF_GE : public Circuit
{
public:
    DiodeLPF_GE() {
        layout.numNodes = 3;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::Resistor R1 {1e3, 1, 2};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Capacitor C1 {1e-9, 3, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::GERMANIUM,
            CircuitElement::Diode::Configuration::MATCHEDPAIR,
            3, 0};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};
        
        // Distortion Pot
        CircuitElement::VariableResistor VrD {2e6, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            2, 3, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrD};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- DiodeLPF_SI --------------------

class DiodeLPF_SI : public Circuit
{
public:
    DiodeLPF_SI() {
        layout.numNodes = 3;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::Resistor R1 {1e3, 1, 2};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Capacitor C1 {1e-9, 3, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
            CircuitElement::Diode::Configuration::MATCHEDPAIR,
            3, 0};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};
        
        // Distortion Pot
        CircuitElement::VariableResistor VrD {2e6, 1,
            CircuitElement::ParamDirection::INVPROPORTIONAL,
            CircuitElement::Skew::LOG,
            2, 3, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrD};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- DiodeSoftGE --------------------

class DiodeSoftGE : public Circuit
{
public:
    DiodeSoftGE() {
        layout.numNodes = 3;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::Resistor R1 {10e3, 2, 0};
        CircuitElement::Resistor R2 {100e3, 2, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {1e-9, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
        
        CircuitElement::OPAmp OP1 {1, 2, 3};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::GERMANIUM,
            CircuitElement::Diode::Configuration::MATCHEDPAIR,
            2, 3};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};
        
        layout.Output = 1;
                
        circuit = CircuitModel(layout);
    }
};

// -------------------- DiodeSoftSI --------------------

class DiodeSoftSI : public Circuit
{
public:
    DiodeSoftSI() {
        layout.numNodes = 3;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::Resistor R1 {10e3, 2, 0};
        CircuitElement::Resistor R2 {100e3, 2, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};
        
        CircuitElement::Capacitor C1 {1e-9, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
        
        CircuitElement::OPAmp OP1 {1, 2, 3};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
            CircuitElement::Diode::Configuration::MATCHEDPAIR,
            2, 3};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};

        layout.Output = 1;
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- FullwaveRectifierSI --------------------

class FullwaveRectifierSI : public Circuit
{
public:
    FullwaveRectifierSI() {
        layout.numNodes = 3;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {2, 3};
        
        CircuitElement::Resistor R1 {100e9, 2, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
            CircuitElement::Diode::Configuration::SINGLE,
            3, 1};
        CircuitElement::Diode D2 {CircuitElement::Diode::Semiconductor::SILICON,
            CircuitElement::Diode::Configuration::SINGLE,
            3, 0};
        CircuitElement::Diode D3 {CircuitElement::Diode::Semiconductor::SILICON,
            CircuitElement::Diode::Configuration::SINGLE,
            1, 2};
        CircuitElement::Diode D4 {CircuitElement::Diode::Semiconductor::SILICON,
            CircuitElement::Diode::Configuration::SINGLE,
            0, 2};
        layout.Ds = std::vector<CircuitElement::Diode> {D1, D2, D3, D4};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- HalfwaveRectifierSI --------------------

class HalfwaveRectifierSI : public Circuit
{
public:
    HalfwaveRectifierSI() {
        layout.numNodes = 2;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {2, 0};
        
        CircuitElement::Resistor R1 {100e9, 2, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
            CircuitElement::Diode::Configuration::SINGLE,
            1, 2};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- StaticBJT_NPN_GE --------------------

class StaticBJT_NPN_GE : public Circuit
{
public:
    StaticBJT_NPN_GE() {
        layout.numNodes = 5;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::VoltageSource Vs1 {9, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {1e3, 1, 2};
        CircuitElement::Resistor R2 {150e3, 4, 0};
        CircuitElement::Resistor R3 {200e3, 3, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::BJT BJT1 {CircuitElement::BJT::Doping::NPN,
                        CircuitElement::BJT::Semiconductor::GERMANIUM,
                        2, 3, 4};
        layout.BJTs = std::vector<CircuitElement::BJT> {BJT1};
        
        layout.hasDCBlocker = true;
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- StaticBJT_NPN_SI --------------------

class StaticBJT_NPN_SI : public Circuit
{
public:
    StaticBJT_NPN_SI() {
        layout.numNodes = 5;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::VoltageSource Vs1 {9, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {1e3, 1, 2};
        CircuitElement::Resistor R2 {100e3, 4, 0};
        CircuitElement::Resistor R3 {200e3, 3, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::BJT BJT1 {CircuitElement::BJT::Doping::NPN,
                        CircuitElement::BJT::Semiconductor::SILICON,
                        2, 3, 4};
        layout.BJTs = std::vector<CircuitElement::BJT> {BJT1};
        
        layout.hasDCBlocker = true;
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- StaticBJT_PNP_GE --------------------

class StaticBJT_PNP_GE : public Circuit
{
public:
    StaticBJT_PNP_GE() {
        layout.numNodes = 5;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::VoltageSource Vs1 {9, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {1e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 4, 0};
        CircuitElement::Resistor R3 {100e3, 3, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::BJT BJT1 {CircuitElement::BJT::Doping::PNP,
                        CircuitElement::BJT::Semiconductor::GERMANIUM,
                        2, 4, 3};
        layout.BJTs = std::vector<CircuitElement::BJT> {BJT1};
        
        layout.hasDCBlocker = true;
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- StaticBJT_PNP_SI --------------------

class StaticBJT_PNP_SI : public Circuit
{
public:
    StaticBJT_PNP_SI() {
        layout.numNodes = 5;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};
        
        CircuitElement::VoltageSource Vs1 {9, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {1e3, 1, 2};
        CircuitElement::Resistor R2 {15e3, 4, 0};
        CircuitElement::Resistor R3 {100e3, 3, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::BJT BJT1 {CircuitElement::BJT::Doping::PNP,
                        CircuitElement::BJT::Semiconductor::SILICON,
                        2, 4, 3};
        layout.BJTs = std::vector<CircuitElement::BJT> {BJT1};
        
        layout.hasDCBlocker = true;
        
        circuit = CircuitModel(layout);
    }
};

// -------------------- StaticDiodeHardGE --------------------

class StaticDiodeHardGE : public Circuit
{
public:
    StaticDiodeHardGE() {
        layout.numNodes = 2;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {2, 0};

        CircuitElement::Resistor R1 {10e3, 1, 2};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};

        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::GERMANIUM,
            CircuitElement::Diode::Configuration::MATCHEDPAIR,
            2, 0};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};
                
        circuit = CircuitModel(layout);
    }
};

// -------------------- StaticDiodeHardSI --------------------

class StaticDiodeHardSI : public Circuit
{
public:
    StaticDiodeHardSI() {
        layout.numNodes = 2;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {2, 0};

        CircuitElement::Resistor R1 {10e3, 1, 2};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};

        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
            CircuitElement::Diode::Configuration::MATCHEDPAIR,
            2, 0};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};
                
        circuit = CircuitModel(layout);
    }
};

// -------------------- StaticDiodeSoftGE --------------------

class StaticDiodeSoftGE : public Circuit
{
public:
    StaticDiodeSoftGE() {
        layout.numNodes = 4;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};

        CircuitElement::Resistor R1 {10e3, 2, 0};
        CircuitElement::Resistor R2 {100e3, 2, 3};
        CircuitElement::Resistor R3 {25e3, 3, 4};
        CircuitElement::Resistor R4 {100e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};
        
        CircuitElement::Capacitor C1 {1e-9, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
        
        CircuitElement::OPAmp OP1 {1, 2, 3};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::GERMANIUM,
            CircuitElement::Diode::Configuration::MATCHEDPAIR,
            2, 3};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};
                
        circuit = CircuitModel(layout);
    }
};

// -------------------- StaticDiodeSoftSI --------------------

class StaticDiodeSoftSI : public Circuit
{
public:
    StaticDiodeSoftSI() {
        layout.numNodes = 4;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {4, 0};

        CircuitElement::Resistor R1 {10e3, 2, 0};
        CircuitElement::Resistor R2 {100e3, 2, 3};
        CircuitElement::Resistor R3 {50e3, 3, 4};
        CircuitElement::Resistor R4 {100e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};
        
        CircuitElement::Capacitor C1 {1e-9, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};
        
        CircuitElement::OPAmp OP1 {1, 2, 3};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
            CircuitElement::Diode::Configuration::MATCHEDPAIR,
            2, 3};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};
                
        circuit = CircuitModel(layout);
    }
};

// -------------------- StaticTubeCleanA --------------------

class StaticTubeCleanA : public Circuit
{
public:
    StaticTubeCleanA() {
        layout.numNodes = 5;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::VoltageSource Vs1 {250, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {68e3, 1, 2};
        CircuitElement::Resistor R2 {100e3, 3, 5};
        CircuitElement::Resistor R3 {91e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::RSD1, 2, 3, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};

        layout.hasDCBlocker = true;

        circuit = CircuitModel(layout);
    }
};

// -------------------- StaticTubeCleanB --------------------

class StaticTubeCleanB : public Circuit
{
public:
    StaticTubeCleanB() {
        layout.numNodes = 5;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::VoltageSource Vs1 {250, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {68e3, 1, 2};
        CircuitElement::Resistor R2 {100e3, 3, 5};
        CircuitElement::Resistor R3 {91e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::EXH, 2, 3, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};

        layout.hasDCBlocker = true;

        circuit = CircuitModel(layout);
    }
};

// -------------------- StaticTubeDirtyA --------------------

class StaticTubeDirtyA : public Circuit
{
public:
    StaticTubeDirtyA() {
        layout.numNodes = 5;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::VoltageSource Vs1 {4.5, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {68e3, 1, 2};
        CircuitElement::Resistor R2 {8e3, 3, 5};
        CircuitElement::Resistor R3 {3e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::RSD1, 2, 3, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};

        layout.hasDCBlocker = true;

        circuit = CircuitModel(layout);
    }
};

// -------------------- StaticTubeDirtyB --------------------

class StaticTubeDirtyB : public Circuit
{
public:
    StaticTubeDirtyB() {
        layout.numNodes = 5;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::VoltageSource Vs1 {4.5, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {68e3, 1, 2};
        CircuitElement::Resistor R2 {8e3, 3, 5};
        CircuitElement::Resistor R3 {3e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::EXH, 2, 3, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};

        layout.hasDCBlocker = true;

        circuit = CircuitModel(layout);
    }
};

// -------------------- TubeCleanA --------------------

class TubeCleanA : public Circuit
{
public:
    TubeCleanA() {
        layout.numNodes = 5;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::VoltageSource Vs1 {250, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {68e3, 1, 2};
        CircuitElement::Resistor R2 {100e3, 3, 5};
        CircuitElement::Resistor R3 {91e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::RSD1, 2, 3, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};

        layout.hasDCBlocker = true;
        
        layout.Output = 1;

        circuit = CircuitModel(layout);
    }
};

// -------------------- TubeCleanB --------------------

class TubeCleanB : public Circuit
{
public:
    TubeCleanB() {
        layout.numNodes = 5;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::VoltageSource Vs1 {250, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {68e3, 1, 2};
        CircuitElement::Resistor R2 {100e3, 3, 5};
        CircuitElement::Resistor R3 {91e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::EXH, 2, 3, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};

        layout.hasDCBlocker = true;
        
        layout.Output = 1;

        circuit = CircuitModel(layout);
    }
};

// -------------------- TubeCleanBiasA --------------------

class TubeCleanBiasA : public Circuit
{
public:
    TubeCleanBiasA() {
        layout.numNodes = 6;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::VoltageSource Vs1 {250, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {68e3, 1, 2};
        CircuitElement::Resistor R2 {68e3, 6, 3};
        CircuitElement::Resistor R3 {91e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::RSD1, 2, 3, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        // Bias Pot
        CircuitElement::VariableResistor VrBI {56e3, 1,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            5, 6, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrBI};

        layout.hasDCBlocker = true;
        
        layout.Output = 1;

        circuit = CircuitModel(layout);
    }
};

// -------------------- TubeCleanBiasB --------------------

class TubeCleanBiasB : public Circuit
{
public:
    TubeCleanBiasB() {
        layout.numNodes = 6;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::VoltageSource Vs1 {250, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {68e3, 1, 2};
        CircuitElement::Resistor R2 {68e3, 6, 3};
        CircuitElement::Resistor R3 {91e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::EXH, 2, 3, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        // Bias Pot
        CircuitElement::VariableResistor VrBI {56e3, 1,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            5, 6, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrBI};

        layout.hasDCBlocker = true;
        
        layout.Output = 1;

        circuit = CircuitModel(layout);
    }
};

// -------------------- TubeDirtyA --------------------

class TubeDirtyA : public Circuit
{
public:
    TubeDirtyA() {
        layout.numNodes = 5;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::VoltageSource Vs1 {4.5, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {68e3, 1, 2};
        CircuitElement::Resistor R2 {8e3, 3, 5};
        CircuitElement::Resistor R3 {3e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::RSD1, 2, 3, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        layout.hasDCBlocker = true;
        
        layout.Output = 1;

        circuit = CircuitModel(layout);
    }
};

// -------------------- TubeDirtyB --------------------

class TubeDirtyB : public Circuit
{
public:
    TubeDirtyB() {
        layout.numNodes = 5;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::VoltageSource Vs1 {4.5, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {68e3, 1, 2};
        CircuitElement::Resistor R2 {8e3, 3, 5};
        CircuitElement::Resistor R3 {3e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::EXH, 2, 3, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        layout.hasDCBlocker = true;
        
        layout.Output = 1;

        circuit = CircuitModel(layout);
    }
};

// -------------------- TubeDirtyBiasA --------------------

class TubeDirtyBiasA : public Circuit
{
public:
    TubeDirtyBiasA() {
        layout.numNodes = 6;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::VoltageSource Vs1 {4.5, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {68e3, 1, 2};
        CircuitElement::Resistor R2 {3e3, 6, 3};
        CircuitElement::Resistor R3 {3e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::RSD1, 2, 3, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        // Bias Pot
        CircuitElement::VariableResistor VrBI {5e3, 1,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            5, 6, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrBI};
        
        layout.hasDCBlocker = true;
        
        layout.Output = 1;

        circuit = CircuitModel(layout);
    }
};

// -------------------- TubeDirtyBiasB --------------------

class TubeDirtyBiasB : public Circuit
{
public:
    TubeDirtyBiasB() {
        layout.numNodes = 6;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};
        
        CircuitElement::VoltageSource Vs1 {4.5, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {68e3, 1, 2};
        CircuitElement::Resistor R2 {3e3, 6, 3};
        CircuitElement::Resistor R3 {3e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Tube12AX7 TUBE1 {CircuitElement::Tube12AX7::EXH, 2, 3, 4};
        layout.Tube12AX7s = std::vector<CircuitElement::Tube12AX7> {TUBE1};
        
        // Bias Pot
        CircuitElement::VariableResistor VrBI {5e3, 1,
            CircuitElement::ParamDirection::PROPORTIONAL,
            CircuitElement::Skew::LINEAR,
            5, 6, 0.5};
        
        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrBI};
        
        layout.hasDCBlocker = true;
        
        layout.Output = 1;

        circuit = CircuitModel(layout);
    }
};

// End of namespace
}

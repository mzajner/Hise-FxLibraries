//
//  PedalCircuits.h
//
//  Collection of clipping, tone, and input/output sections from guitar pedals
//
//
#include "Circuit.h"
#include "CircuitModel.h"
#include "CircuitElement.h"

#pragma once
namespace PointToPoint {

// -------------------- Big Muff Output Booster --------------------
class BigMuffOutputBooster : public Circuit
{
public:
    BigMuffOutputBooster() {
        layout.numNodes = 6;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};
        
        CircuitElement::VoltageSource Vs1 {9, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {430e3, 5, 2};
        CircuitElement::Resistor R2 {100e3, 2, 0};
        CircuitElement::Resistor R3 {15e3, 5, 3};
        CircuitElement::Resistor R4 {8e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};

        CircuitElement::BJT BJT1 {CircuitElement::BJT::Doping::NPN,
                        CircuitElement::BJT::Semiconductor::SILICON,
                        2, 3, 4};
        layout.BJTs = std::vector<CircuitElement::BJT> {BJT1};

        layout.hasDCBlocker = true;
        
        layout.Output = 0.94;

        circuit = CircuitModel(layout);
    }
};


// -------------------- Big Muff Tone Stage --------------------
class BigMuffToneStage : public Circuit
{
public:
    BigMuffToneStage() {
        layout.numNodes = 4;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};

        CircuitElement::Resistor R1 {39e3, 1, 4};
        CircuitElement::Resistor R2 {22e3, 2, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2};

        CircuitElement::Capacitor C1 {4e-9, 1, 2};
        CircuitElement::Capacitor C2 {10e-9, 4, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        // Tone Pot
        CircuitElement::Potentiometer PtTo {100e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 4, 0.5 };

        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtTo};

        circuit = CircuitModel(layout);
    }
};


// -------------------- Boss BD2 Tone Clipping Stage --------------------
class BossBD2ClippingStage : public Circuit
{
public:
    BossBD2ClippingStage() {
        layout.numNodes = 7;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};

        CircuitElement::Resistor R1 {100e3, 1, 2};
        CircuitElement::Resistor R2 {330e3, 3, 5};
        CircuitElement::Resistor R3 {15e3, 4, 0};
        CircuitElement::Resistor R4 {1e6, 4, 5};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};

        CircuitElement::Capacitor C1 {220e-12, 1, 3};
        CircuitElement::Capacitor C2 {100e-9, 2, 5};
        CircuitElement::Capacitor C3 {47e-9, 2, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
                        CircuitElement::Diode::Configuration::SINGLE,
                        5, 6};
        CircuitElement::Diode D2 {CircuitElement::Diode::Semiconductor::SILICON,
                        CircuitElement::Diode::Configuration::SINGLE,
                        6, 0};
        CircuitElement::Diode D3 {CircuitElement::Diode::Semiconductor::SILICON,
                        CircuitElement::Diode::Configuration::SINGLE,
                        0, 7};
        CircuitElement::Diode D4 {CircuitElement::Diode::Semiconductor::SILICON,
                        CircuitElement::Diode::Configuration::SINGLE,
                        7, 5};
        layout.Ds = std::vector<CircuitElement::Diode> {D1, D2, D3, D4};

        circuit = CircuitModel(layout);
    }
};


// -------------------- Boss DS1 OpAmp Gain Stage --------------------
class BossDS1OpAmpGainStage : public Circuit
{
public:
    BossDS1OpAmpGainStage() {
        layout.numNodes = 9;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {8, 0};
        
        CircuitElement::VoltageSource Vs1 {4.5, 9};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};
        
        CircuitElement::Resistor R1 {100e3, 2, 3};
        CircuitElement::Resistor R2 {4.7e3, 5, 6};
        CircuitElement::Resistor R3 {220e3, 4, 7};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};
        
        CircuitElement::Capacitor C1 {100e-12, 3, 4};
        CircuitElement::Capacitor C2 {0.47e-6, 6, 0};
        CircuitElement::Capacitor C3 {0.47e-6, 7, 8};
        CircuitElement::Capacitor C4 {100e-12, 8, 9};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4};
        
        CircuitElement::OPAmp OP1 {1, 2, 4};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};
        
        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
                        CircuitElement::Diode::Configuration::MATCHEDPAIR,
                        8, 0};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};
        
        // Distortion Pot
        CircuitElement::Potentiometer PtD {100e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 3, 4, 1};

        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtD};
        
        layout.hasDCBlocker = true;
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- Boss DS1 Tone Stage --------------------
class BossDS1ToneStage : public Circuit
{
public:
    BossDS1ToneStage() {
        layout.numNodes = 7;
        
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};
        
        CircuitElement::Resistor R1 {6.8e3, 1, 2};
        CircuitElement::Resistor R2 {2.2e3, 3, 5};
        CircuitElement::Resistor R3 {6.8e3, 5, 0};
        CircuitElement::Resistor R4 {10e3, 6, 7};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};
        
        CircuitElement::Capacitor C1 {0.022e-6, 1, 3};
        CircuitElement::Capacitor C2 {0.1e-6, 2, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};
        
        // Tone Pot
        CircuitElement::Potentiometer PtT {20e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 4, 5, 0.5};
        
        // Volume Pot
        CircuitElement::Potentiometer PtV {100e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 6, 0, 1};

        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT, PtV};
        
        circuit = CircuitModel(layout);
    }
};


// -------------------- DOD FX70C Tone Stage --------------------
class DOD_FX70C_ToneStage : public Circuit
{
public:
    DOD_FX70C_ToneStage() {
        layout.numNodes = 14;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {12, 0};

        CircuitElement::Resistor R1 {100e3, 4, 0};
        CircuitElement::Resistor R2 {3.3e3, 3, 5};
        CircuitElement::Resistor R3 {2e3, 6, 7};
        CircuitElement::Resistor R4 {22e3, 8, 9};
        CircuitElement::Resistor R5 {100e3, 12, 0};
        CircuitElement::Resistor R6 {3e3, 10, 13};
        CircuitElement::Resistor R7 {1e3, 14, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6, R7};

        CircuitElement::Capacitor C1 {0.22e-6, 2, 3};
        CircuitElement::Capacitor C2 {0.05e-6, 3, 4};
        CircuitElement::Capacitor C3 {10e-9, 7, 0};
        CircuitElement::Capacitor C4 {50e-12, 8, 9};
        CircuitElement::Capacitor C5 {10e-6, 9, 10};
        CircuitElement::Capacitor C6 {0.22e-6, 11, 12};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5, C6};

        CircuitElement::OPAmp OP1 {4, 5, 5};
        CircuitElement::OPAmp OP2 {1, 8, 9};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1, OP2};

        // Bottom Pot
        CircuitElement::Potentiometer PtB {100e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        1, 2, 8, 0.5};

        // Top Pot
        CircuitElement::Potentiometer PtT {100e3, 2,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        1, 6, 14, 0.5};

        // Dissolve Pot
        CircuitElement::Potentiometer PtD {100e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        13, 11, 0, 1};

        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtT, PtD};

        circuit = CircuitModel(layout);
    }
};


// -------------------- Electra Distortion --------------------
class ElectraDistortion : public Circuit
{
public:
    ElectraDistortion() {
        layout.numNodes = 6;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};
        
        CircuitElement::VoltageSource Vs1 {9, 6};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1};

        CircuitElement::Resistor R1 {3.3e6, 2, 3};
        CircuitElement::Resistor R2 {47e3, 6, 3};
        CircuitElement::Resistor R3 {4.7e3, 4, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::Capacitor C1 {100e-9, 1, 2};
        CircuitElement::Capacitor C2 {100e-9, 3, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::BJT BJT1 {CircuitElement::BJT::Doping::NPN,
                        CircuitElement::BJT::Semiconductor::SILICON,
                        2, 3, 4};
        layout.BJTs = std::vector<CircuitElement::BJT> {BJT1};

        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::GERMANIUM,
                        CircuitElement::Diode::Configuration::MATCHEDPAIR,
                        5, 0};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};

        layout.hasDCBlocker = true;

        circuit = CircuitModel(layout);
    }
};


// -------------------- JHS Morning Glory Drive Stage A --------------------
class JHSMorningGloryDriveStage_A : public Circuit
{
public:
    JHSMorningGloryDriveStage_A() {
        layout.numNodes = 4;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};

        CircuitElement::Resistor R1 {100e3, 1, 2};
        CircuitElement::Resistor R2 {220e3, 2, 3};
        CircuitElement::Resistor R3 {6.8e3, 2, 4};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::OPAmp OP1 {0, 2, 3};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};

        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
                        CircuitElement::Diode::Configuration::MATCHEDPAIR,
                        4, 3};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};

        circuit = CircuitModel(layout);
    }
};


// -------------------- JHS Morning Glory Drive Stage B --------------------
class JHSMorningGloryDriveStage_B : public Circuit
{
public:
    JHSMorningGloryDriveStage_B() {
        layout.numNodes = 4;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};

        CircuitElement::Resistor R1 {100e3, 1, 2};
        CircuitElement::Resistor R2 {220e3, 2, 3};
        CircuitElement::Resistor R3 {6.8e3, 2, 4};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::Capacitor C1 {470e-12, 2, 3};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};

        CircuitElement::OPAmp OP1 {0, 2, 3};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};

        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
                        CircuitElement::Diode::Configuration::MATCHEDPAIR,
                        4, 3};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};

        circuit = CircuitModel(layout);
    }
};


// -------------------- JHS Morning Glory Input Stage --------------------
class JHSMorningGloryInputStage : public Circuit
{
public:
    JHSMorningGloryInputStage() {
        layout.numNodes = 7;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {5, 0};

        CircuitElement::Resistor R1 {2.2e6, 1, 0};
        CircuitElement::Resistor R2 {1e6, 2, 0};
        CircuitElement::Resistor R3 {4.7e3, 3, 7};
        CircuitElement::Resistor R4 {3.3e3, 3, 6};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};

        CircuitElement::Capacitor C1 {47e-9, 1, 2};
        CircuitElement::Capacitor C2 {47e-12, 3, 4};
        CircuitElement::Capacitor C3 {10e-9, 6, 7};
        CircuitElement::Capacitor C4 {10e-9, 7, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4};

        CircuitElement::OPAmp OP1 {2, 3, 4};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};

        // Gain Pot
        CircuitElement::Potentiometer PtG {22e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 4, 5, 0};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtG};

        circuit = CircuitModel(layout);
    }
};


// -------------------- JHS Morning Glory Tone Stage --------------------
class JHSMorningGloryToneStage : public Circuit
{
public:
    JHSMorningGloryToneStage() {
        layout.numNodes = 7;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};

        CircuitElement::Resistor R1 {1e3, 1, 2};
        CircuitElement::Resistor R2 {6.8e3, 3, 5};
        CircuitElement::Resistor R3 {100e3, 5, 0};
        CircuitElement::Resistor R4 {68e3, 6, 7};
        CircuitElement::Resistor R5 {1e6, 7, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};

        CircuitElement::Capacitor C1 {10e-9, 4, 0};
        CircuitElement::Capacitor C2 {100e-9, 5, 6};
        CircuitElement::Capacitor C3 {10e-9, 5, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        // Tone Pot
        CircuitElement::Potentiometer PtTo {25e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 4, 0.5};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtTo};

        circuit = CircuitModel(layout);
    }
};


// -------------------- Klon Centaur Tone Control --------------------
class KlonCentaurToneControl : public Circuit
{
public:
    KlonCentaurToneControl() {
        layout.numNodes = 6;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};

        CircuitElement::Resistor R1 {100e3, 1, 4};
        CircuitElement::Resistor R2 {1.8e3, 1, 2};
        CircuitElement::Resistor R3 {100e3, 4, 6};
        CircuitElement::Resistor R4 {4.7e3, 5, 6};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};

        CircuitElement::Capacitor C1 {3.9e-9, 3, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};

        CircuitElement::OPAmp OP1 {0, 4, 6};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};

        // Treble Pot
        CircuitElement::Potentiometer PtT {10e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 5, 1};
        
        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtT};
        
        layout.Output = 0.97;

        circuit = CircuitModel(layout);
    }
};


// -------------------- Marshall Guvnor Clipping Stage --------------------
class MarshallGuvnorClippingStage : public Circuit
{
public:
    MarshallGuvnorClippingStage() {
        layout.numNodes = 8;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};

        CircuitElement::Resistor R1 {10e3, 2, 3};
        CircuitElement::Resistor R2 {680e3, 4, 5};
        CircuitElement::Resistor R3 {1e3, 6, 7};
        CircuitElement::Resistor R4 {4.7e3, 8, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};

        CircuitElement::Capacitor C1 {220e-9, 1, 2};
        CircuitElement::Capacitor C2 {100e-9, 3, 4};
        CircuitElement::Capacitor C3 {220e-12, 4, 5};
        CircuitElement::Capacitor C4 {220e-9, 5, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4};

        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
                        CircuitElement::Diode::Configuration::MATCHEDPAIR,
                        7, 0};
        CircuitElement::Diode D2 {CircuitElement::Diode::Semiconductor::SILICON,
                        CircuitElement::Diode::Configuration::SINGLE,
                        8, 3};
        layout.Ds = std::vector<CircuitElement::Diode> {D1, D2};

        circuit = CircuitModel(layout);
    }
};


// -------------------- Marshall Guvnor Input Stage --------------------
class MarshallGuvnorInputStage : public Circuit
{
public:
    MarshallGuvnorInputStage() {
        layout.numNodes = 6;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};

        CircuitElement::Resistor R1 {2.2e6, 1, 0};
        CircuitElement::Resistor R2 {1e6, 2, 0};
        CircuitElement::Resistor R3 {2.2e3, 4, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::Capacitor C1 {9.6e-9, 1, 2};
        CircuitElement::Capacitor C2 {100e-9, 4, 0};
        CircuitElement::Capacitor C3 {120e-12, 3, 5};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        CircuitElement::OPAmp OP1 {2, 3, 5};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};

        // Gain Pot
        CircuitElement::Potentiometer PtG {100e3, 1,
                       CircuitElement::ParamDirection::PROPORTIONAL,
                       CircuitElement::Skew::LINEAR,
                       3, 5, 6, 0.1};

        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtG};

        circuit = CircuitModel(layout);
    }
};


// -------------------- Marshall Guvnor Output Stage --------------------
class MarshallGuvnorOutputStage : public Circuit
{
public:
    MarshallGuvnorOutputStage() {
        layout.numNodes = 3;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};

        CircuitElement::Resistor R1 {22e3, 2, 3};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1};

        CircuitElement::Capacitor C1 {470e-12, 3, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};

        // Volume Pot
        CircuitElement::Potentiometer PtV {100e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        1, 2, 0, 1};

        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};

        circuit = CircuitModel(layout);
    }
};


// -------------------- Marshall Guvnor Tone Control --------------------
class MarshallGuvnorToneControl : public Circuit
{
public:
    MarshallGuvnorToneControl() {
        layout.numNodes = 9;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {3, 0};

        CircuitElement::Resistor R1 {1.5e3, 1, 7};
        CircuitElement::Resistor R2 {100, 4, 5};
        CircuitElement::Resistor R3 {680, 7, 8};
        CircuitElement::Resistor R4 {680, 9, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};

        CircuitElement::Capacitor C1 {4.7e-9, 1, 2};
        CircuitElement::Capacitor C2 {10e-9, 2, 4};
        CircuitElement::Capacitor C3 {220e-9, 6, 7};
        CircuitElement::Capacitor C4 {100e-9, 7, 9};
        CircuitElement::Capacitor C5 {68e-9, 8, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5};

        // Bass Pot
        CircuitElement::Potentiometer PtB {10e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        8, 9, 0, 0.5};

        // Mid Pot
        CircuitElement::Potentiometer PtM {10e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 6, 0, 0.5};

        // Treble Pot
        CircuitElement::Potentiometer PtT {10e3, 3,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 3, 8, 0.1};

        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtM, PtT};

        circuit = CircuitModel(layout);
    }
};


// -------------------- Matchless Hotbox Tone Control --------------------
class MatchlessHotboxToneControl : public Circuit
{
public:
    MatchlessHotboxToneControl() {
        layout.numNodes = 8;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {8, 0};

        CircuitElement::Resistor R1 {1.5e3, 1, 0};
        CircuitElement::Resistor R2 {100e3, 1, 2};
        CircuitElement::Resistor R3 {10e3, 0, 4};
        CircuitElement::Resistor R4 {100e3, 6, 7};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};

        CircuitElement::Capacitor C1 {50e-12, 1, 5};
        CircuitElement::Capacitor C2 {0.022e-6, 2, 3};
        CircuitElement::Capacitor C3 {0.022e-6, 2, 4};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        // Bass Pot
        CircuitElement::Potentiometer PtB {1e6, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        3, 4, 0, 1};

        // Treble Pot
        CircuitElement::Potentiometer PtT {1e6, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        5, 6, 3, 1};

        // Output Pot
        CircuitElement::Potentiometer PtO {1e6, 3,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        0, 7, 8, 1};

        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtB, PtT, PtO};

        circuit = CircuitModel(layout);
    }
};


// -------------------- MXR Distortion+ --------------------
class MXRDistortionPlus : public Circuit
{
public:
    MXRDistortionPlus() {
        layout.numNodes = 7;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};

        CircuitElement::Resistor R1 {220e3, 3, 4};
        CircuitElement::Resistor R2 {1e6, 2, 5};
        CircuitElement::Resistor R3 {10e3, 6, 7};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::Capacitor C1 {47e-9, 2, 3};
        CircuitElement::Capacitor C2 {1e-6, 5, 6};
        CircuitElement::Capacitor C3 {1e-9, 7, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3};

        CircuitElement::OPAmp OP1 {1, 2, 5};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};

        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::GERMANIUM,
                        CircuitElement::Diode::Configuration::MATCHEDPAIR,
                        7, 0};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};

        // Distortion Pot
        CircuitElement::VariableResistor VrD {1e6, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        4, 0, 0.5};

        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrD};

        layout.Output = 1;

        circuit = CircuitModel(layout);
    }
};


// -------------------- Pro Co Rat --------------------
class ProCoRat : public Circuit
{
public:
    ProCoRat() {
        layout.numNodes = 8;

        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {8, 0};

        CircuitElement::Resistor R1 {47, 1, 3};
        CircuitElement::Resistor R2 {560, 1, 4};
        CircuitElement::Resistor R3 {1e3, 5, 6};
        CircuitElement::Resistor R4 {1.5e3, 7, 8};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4};

        CircuitElement::Capacitor C1 {2.2e-6, 3, 0};
        CircuitElement::Capacitor C2 {4.7e-6, 4, 0};
        CircuitElement::Capacitor C3 {100e-12, 1, 2};
        CircuitElement::Capacitor C4 {4.7e-6, 2, 5};
        CircuitElement::Capacitor C5 {3.3e-9, 8, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5};

        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::SILICON,
                                  CircuitElement::Diode::Configuration::MATCHEDPAIR,
                                  6, 0};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};

        // Distortion Pot
        CircuitElement::VariableResistor VrD {100e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        1, 2, 1};

        // Tone Pot
        CircuitElement::VariableResistor VrTo {100e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        6, 7, 1};

        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrD, VrTo};

        layout.Output = 1;

        circuit = CircuitModel(layout);
    }
};


// -------------------- Tube Screamer Input Buffer --------------------
class TubeScreamerInputBuffer : public Circuit
{
public:
    TubeScreamerInputBuffer() {
        layout.numNodes = 6;
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {6, 0};

        CircuitElement::VoltageSource Vs1 {4.5, 4};
        CircuitElement::VoltageSource Vs2 {9, 5};
        layout.Vs = std::vector<CircuitElement::VoltageSource> {Vs1, Vs2};

        CircuitElement::Resistor R1 {1e3, 2, 3};
        CircuitElement::Resistor R2 {510e3, 4, 3};
        CircuitElement::Resistor R3 {10e3, 6, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3};

        CircuitElement::Capacitor C1 {0.02e-6, 1, 2};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1};

        CircuitElement::BJT BJT1 {CircuitElement::BJT::Doping::NPN,
                        CircuitElement::BJT::Semiconductor::SILICON,
                        3, 5, 6};
        layout.BJTs = std::vector<CircuitElement::BJT> {BJT1};

        layout.hasDCBlocker = true;

        circuit = CircuitModel(layout);
    }
};


// -------------------- Tube Screamer Tone/Volume Stage --------------------
class TubeScreamerToneStage : public Circuit
{
public:
    TubeScreamerToneStage() {
        layout.numNodes = 7;
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {7, 0};

        CircuitElement::Resistor R1 {1e3, 1, 2};
        CircuitElement::Resistor R2 {10e3, 2, 0};
        CircuitElement::Resistor R3 {220, 6, 0};
        CircuitElement::Resistor R4 {1e3, 3, 4};
        CircuitElement::Resistor R5 {1e3, 4, 7};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5};

        CircuitElement::Capacitor C1 {0.22e-6, 2, 0};
        CircuitElement::Capacitor C2 {0.22e-6, 5, 6};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2};

        CircuitElement::OPAmp OP1 {2, 3, 4};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};

        // Tone Pot
        CircuitElement::Potentiometer PtTo {20e3, 1,
                        CircuitElement::ParamDirection::PROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        2, 5, 3, 1};

        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtTo};

        layout.hasDCBlocker = true;
        
        layout.Output = 1;

        circuit = CircuitModel(layout);
    }
};


// -------------------- Vox 1901 --------------------
class Vox1901 : public Circuit
{
public:
    Vox1901() {
        layout.numNodes = 11;
        layout.Vin = CircuitElement::VoltageInput {1, 0};
        layout.Vout = CircuitElement::VoltageOutput {9, 0};

        CircuitElement::Resistor R1 {10e3, 2, 3};
        CircuitElement::Resistor R2 {1e6, 3, 6};
        CircuitElement::Resistor R3 {1e6, 6, 0};
        CircuitElement::Resistor R4 {1e6, 4, 5};
        CircuitElement::Resistor R5 {12e3, 7, 8};
        CircuitElement::Resistor R6 {50e3, 11, 0};
        layout.Rs = std::vector<CircuitElement::Resistor> {R1, R2, R3, R4, R5, R6};

        CircuitElement::Capacitor C1 {0.001e-6, 1, 0};
        CircuitElement::Capacitor C2 {0.01e-6, 1, 2};
        CircuitElement::Capacitor C3 {16e-6, 6, 0};
        CircuitElement::Capacitor C4 {0.056e-6, 4, 10};
        CircuitElement::Capacitor C5 {16e-6, 5, 7};
        CircuitElement::Capacitor C6 {500e-12, 8, 0};
        layout.Cs = std::vector<CircuitElement::Capacitor> {C1, C2, C3, C4, C5, C6};

        CircuitElement::OPAmp OP1 {3, 4, 5};
        layout.OPAmps = std::vector<CircuitElement::OPAmp> {OP1};

        CircuitElement::Diode D1 {CircuitElement::Diode::Semiconductor::GERMANIUM,
                        CircuitElement::Diode::Configuration::MATCHEDPAIR,
                        8, 0};
        layout.Ds = std::vector<CircuitElement::Diode> {D1};

        // Distortion Pot
        CircuitElement::VariableResistor VrD {500e3, 1,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        10, 11, 1};

        layout.VarRs = std::vector<CircuitElement::VariableResistor> {VrD};

        // Output Pot
        CircuitElement::Potentiometer PtV {50e3, 2,
                        CircuitElement::ParamDirection::INVPROPORTIONAL,
                        CircuitElement::Skew::LINEAR,
                        8, 9, 0, 1};

        layout.Pots = std::vector<CircuitElement::Potentiometer> {PtV};

        circuit = CircuitModel(layout);
    }
};

// End of namespace
}

//
//  XMLCircuit.h
//
//  Collection of nonlinear circuits based on basic tube topologies
//
//
#include "Circuit.h"
#include "CircuitModel.h"
#include "CircuitElement.h"

#pragma once
namespace PointToPoint {

CircuitModel openXMLCircuit(const File & f);
File searchForCircuit(const String& circuitName);

class XMLCircuit : public Circuit
{
  
public:
    XMLCircuit(const File f){
        circuit = openXMLCircuit(f);
    }
    
};

class XMLCircuitChain : public CircuitChain
{
  
public:
    XMLCircuitChain(const File f){
        openXMLCircuitChain(f);
    }
    
private:
    
    void addCircuitToChain(XmlElement * xml, const File & f)
    {
        for (int m = 0; m < xml->getNumChildElements() ; ++m){
            auto c = xml->getChildElement(m);
            if (c->getTagName().equalsIgnoreCase("Circuit")){
                for (int n = 0; n < c->getNumChildElements() ; ++n){
                    auto s = c->getChildElement(n);
                    if (s->hasAttribute("text")){
                        auto val = s->getStringAttribute("text");
                        String circuitName = String(val + ".xml");
                        File newFile = searchForCircuit(circuitName);
                        auto newXml = parseXML(newFile);
                        if (newXml->hasTagName("PointToPointCircuitChain"))
                        {
                            circuitChain.emplace_back(std::make_shared<XMLCircuitChain> (newFile));
                        }
                        else if (newXml->hasTagName("PointToPointCircuit"))
                        {
                            circuitChain.emplace_back(std::make_shared<XMLCircuit> (newFile));
                        }
                    }
                }
            }
        }
    }

    void openXMLCircuitChain(const File & f)
    {
        std::unique_ptr<XmlElement> xml = parseXML (f);
        
        if (xml->hasTagName("PointToPointCircuitChain")){
            for (int m = 0; m < xml->getNumChildElements() ; ++m){
                auto s = xml->getChildElement(m);
                if (s->getTagName().equalsIgnoreCase("Chain")){
                    addCircuitToChain(s,f);
                }
            }
        }
        else if (xml->hasTagName("PointToPointCircuit")){
            circuitChain.emplace_back(std::make_shared<XMLCircuit> (f));
        }
        
    }
    
};




inline void addVoltageInputToLayout(XmlElement * xml, CircuitModel::CircuitLayout & layout)
{
    int node1 = -1;
    int node2 = -1;
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("node1")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    node1 = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("node2")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    node2 = val;
                }
            }
        }
    }
    if (node1 >= 0 && node2 >= 0){
        layout.Vin = CircuitElement::VoltageInput(node1,node2);
    }
}

inline void addVoltageOutputToLayout(XmlElement * xml, CircuitModel::CircuitLayout & layout)
{
    int node1 = -1;
    int node2 = -1;
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("node1")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    node1 = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("node2")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    node2 = val;
                }
            }
        }
    }
    if (node1 >= 0 && node2 >= 0){
        layout.Vout = CircuitElement::VoltageOutput(node1,node2);
    }
}

inline CircuitElement::VoltageSource getVoltageSource(XmlElement * xml)
{
    double voltage = -1.0;
    int node = -1;
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("voltage")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getDoubleAttribute("text");
                    voltage = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("node")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    node = val;
                }
            }
        }
    }
    if (voltage >= 0.0 && node >= 0){
        return CircuitElement::VoltageSource(voltage,node);
    }
    else
        return CircuitElement::VoltageSource(1.f,0);
}

inline void addVoltageSourcesToLayout(XmlElement * xml, CircuitModel::CircuitLayout & layout)
{
    std::vector<CircuitElement::VoltageSource> Vs;
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("VoltageSource")){
            Vs.push_back(getVoltageSource(c));
        }
    }
    if (Vs.size() >= 1){
        layout.Vs = Vs;
    }
}




inline CircuitElement::Resistor getResistor(XmlElement * xml)
{
    double value = -1.0;
    int node1 = -1;
    int node2 = -1;
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("value")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getDoubleAttribute("text");
                    value = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("node1")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    node1 = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("node2")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    node2 = val;
                }
            }
        }
    }
    if (value >= 0.0 && node1 >= 0 && node2 >= 0){
        return CircuitElement::Resistor(value,node1,node2);
    }
    else
        return CircuitElement::Resistor(value,-1,-1);
}


inline void addRsToLayout(XmlElement * xml, CircuitModel::CircuitLayout & layout)
{
    std::vector<CircuitElement::Resistor> Rs;
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("Resistor")){
            Rs.push_back(getResistor(c));
        }
    }
    if (Rs.size() >= 1){
        layout.Rs = Rs;
    }
}


inline CircuitElement::Capacitor getCapacitor(XmlElement * xml)
{
    double value = -1.0;
    int node1 = -1;
    int node2 = -1;
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("value")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getDoubleAttribute("text");
                    value = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("node1")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    node1 = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("node2")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    node2 = val;
                }
            }
        }
    }
    if (value >= 0.0 && node1 >= 0 && node2 >= 0){
        return CircuitElement::Capacitor(value,node1,node2);
    }
    else
        return CircuitElement::Capacitor(value,-1,-1);
}


inline void addCsToLayout(XmlElement * xml, CircuitModel::CircuitLayout & layout)
{
    std::vector<CircuitElement::Capacitor> Cs;
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("Capacitor")){
            Cs.push_back(getCapacitor(c));
        }
    }
    if (Cs.size() >= 1){
        layout.Cs = Cs;
    }
}




inline CircuitElement::OPAmp getOPAmp(XmlElement * xml)
{
    int nonInvertingNode = -1;
    int invertingNode = -1;
    int outputNode = -1;
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("nonInvertingNode")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    nonInvertingNode = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("invertingNode")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    invertingNode = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("outputNode")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    outputNode = val;
                }
            }
        }
    }
    if (nonInvertingNode >= 0 && invertingNode >= 0 && outputNode >= 0){
        return CircuitElement::OPAmp(nonInvertingNode,invertingNode,outputNode);
    }
    else
        return CircuitElement::OPAmp(-1,-1,-1);
}


inline void addOPAmpsToLayout(XmlElement * xml, CircuitModel::CircuitLayout & layout)
{
    std::vector<CircuitElement::OPAmp> OPAmps;
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("OPAmp")){
            OPAmps.push_back(getOPAmp(c));
        }
    }
    if (OPAmps.size() >= 1){
        layout.OPAmps = OPAmps;
    }
}




inline CircuitElement::VariableResistor getVariableResistor(XmlElement * xml)
{
    double maxValue = -1.0;
    int parameterNumber = -1;
    CircuitElement::ParamDirection direction;
    CircuitElement::Skew skew;
    int node1 = -1;
    int node2 = -1;
    double initValue = 1.0;
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("maxValue")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getDoubleAttribute("text");
                    maxValue = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("parameterNumber")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    parameterNumber = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("Direction")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getStringAttribute("text");
                    if (val.equalsIgnoreCase("PROPORTIONAL"))
                        direction = CircuitElement::ParamDirection::PROPORTIONAL;
                    else if (val.equalsIgnoreCase("INVPROPORTIONAL"))
                        direction = CircuitElement::ParamDirection::INVPROPORTIONAL;
                    
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("Skew")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getStringAttribute("text");
                    if (val.equalsIgnoreCase("LINEAR"))
                        skew = CircuitElement::Skew::LINEAR;
                    else if (val.equalsIgnoreCase("LOG"))
                        skew = CircuitElement::Skew::LOG;
                    
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("node1")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    node1 = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("node2")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    node2 = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("InitValue")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    initValue = val;
                }
            }
        }
    }
    if (maxValue >= 0.0 && parameterNumber >= 0 && node1 >= 0 && node2 >= 0){
        return CircuitElement::VariableResistor(maxValue,parameterNumber,direction,skew,node1,node2,initValue);
    }
    else
        return CircuitElement::VariableResistor(maxValue,parameterNumber,direction,skew,node1,node2);
}

inline void addVarRsToLayout(XmlElement * xml, CircuitModel::CircuitLayout & layout)
{
    std::vector<CircuitElement::VariableResistor> VarRs;
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("VariableResistor")){
            VarRs.push_back(getVariableResistor(c));
        }
    }
    if (VarRs.size() >= 1){
        layout.VarRs = VarRs;
    }
}

inline CircuitElement::Potentiometer getPotentiometer(XmlElement * xml)
{
    double maxValue = -1.0;
    int parameterNumber = -1;
    CircuitElement::ParamDirection direction;
    CircuitElement::Skew skew;
    int node1 = -1;
    int node2 = -1;
    int node3 = -1;
    double initValue = 1.0;
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("maxValue")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getDoubleAttribute("text");
                    maxValue = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("parameterNumber")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    parameterNumber = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("Direction")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getStringAttribute("text");
                    if (val.equalsIgnoreCase("PROPORTIONAL"))
                        direction = CircuitElement::ParamDirection::PROPORTIONAL;
                    else if (val.equalsIgnoreCase("INVPROPORTIONAL"))
                        direction = CircuitElement::ParamDirection::INVPROPORTIONAL;
                    
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("Skew")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getStringAttribute("text");
                    if (val.equalsIgnoreCase("LINEAR"))
                        skew = CircuitElement::Skew::LINEAR;
                    else if (val.equalsIgnoreCase("LOG"))
                        skew = CircuitElement::Skew::LOG;
                    
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("node1")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    node1 = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("node2")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    node2 = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("node3")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    node3 = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("InitValue")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    initValue = val;
                }
            }
        }
    }
    if (maxValue >= 0.0 && parameterNumber >= 0 && node1 >= 0 && node2 >= 0){
        return CircuitElement::Potentiometer(maxValue,parameterNumber,direction,skew,node1,node2,node3,initValue);
    }
    else
        return CircuitElement::Potentiometer(maxValue,parameterNumber,direction,skew,node1,node2,node3);
}

inline void addPotsToLayout(XmlElement * xml, CircuitModel::CircuitLayout & layout)
{
    std::vector<CircuitElement::Potentiometer> Pots;
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("Potentiometer")){
            Pots.push_back(getPotentiometer(c));
        }
    }
    if (Pots.size() >= 1){
        layout.Pots = Pots;
    }
}


inline CircuitElement::Diode getDiode(XmlElement * xml)
{
    double Vt = -1.0;
    double eta = -1.0;
    double Is = -1.0;
    CircuitElement::Diode::Semiconductor type = CircuitElement::Diode::Semiconductor::SILICON;
    CircuitElement::Diode::Configuration config = CircuitElement::Diode::Configuration::SINGLE;
    int node1 = -1;
    int node2 = -1;
    
    
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("ThermalVoltage")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getDoubleAttribute("text");
                    Vt = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("EmissionCoeff")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getDoubleAttribute("text");
                    eta = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("SaturationCurrent")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getDoubleAttribute("text");
                    Is = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("Semiconductor")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getStringAttribute("text");
                    if (val.equalsIgnoreCase("Germanium"))
                        type = CircuitElement::Diode::Semiconductor::GERMANIUM;
                    else if (val.equalsIgnoreCase("Silicon"))
                        type = CircuitElement::Diode::Semiconductor::SILICON;
                    
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("Configuration")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getStringAttribute("text");
                    if (val.equalsIgnoreCase("Single"))
                        config = CircuitElement::Diode::Configuration::SINGLE;
                    else if (val.equalsIgnoreCase("MatchedPair"))
                        config = CircuitElement::Diode::Configuration::MATCHEDPAIR;
                    
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("node1")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    node1 = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("node2")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    node2 = val;
                }
            }
        }
    }
    CircuitElement::Diode D {type,config,node1,node2};
    
    if (Vt >= 0.0)
        D.setThermalVoltage(Vt);
    
    if (eta >= 0.0)
        D.setEmissionCoeff(eta);
    
    if (Is >= 0.0)
        D.setSaturationCurrent(Is);
           
    return D;
}

inline void addDsToLayout(XmlElement * xml, CircuitModel::CircuitLayout & layout)
{
    std::vector<CircuitElement::Diode> Ds;
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("Diode")){
            Ds.push_back(getDiode(c));
        }
    }
    if (Ds.size() >= 1){
        layout.Ds = Ds;
    }
}




inline CircuitElement::BJT getBJT(XmlElement * xml)
{
    double Vt = -1.0;
    double eta = -1.0;
    double Is = -1.0;
    CircuitElement::BJT::Semiconductor type = CircuitElement::BJT::Semiconductor::SILICON;
    CircuitElement::BJT::Doping doping = CircuitElement::BJT::Doping::NPN;
    int nodeBase = -1;
    int nodeCollector = -1;
    int nodeEmitter = -1;
    
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("ThermalVoltage")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getDoubleAttribute("text");
                    Vt = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("EmissionCoeff")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getDoubleAttribute("text");
                    eta = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("SaturationCurrent")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getDoubleAttribute("text");
                    Is = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("Semiconductor")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getStringAttribute("text");
                    if (val.equalsIgnoreCase("Germanium"))
                        type = CircuitElement::BJT::Semiconductor::GERMANIUM;
                    else if (val.equalsIgnoreCase("Silicon"))
                        type = CircuitElement::BJT::Semiconductor::SILICON;
                    
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("Doping")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getStringAttribute("text");
                    if (val.equalsIgnoreCase("NPN"))
                        doping = CircuitElement::BJT::Doping::NPN;
                    else if (val.equalsIgnoreCase("PNP"))
                        doping = CircuitElement::BJT::Doping::PNP;
                    
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("nodeBase")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    nodeBase = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("nodeCollector")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    nodeCollector = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("nodeEmitter")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    nodeEmitter = val;
                }
            }
        }
    }
    
    CircuitElement::BJT bjt {doping,type,nodeBase,nodeCollector,nodeEmitter};
    
    if (Vt >= 0.0)
        bjt.setThermalVoltage(Vt);
    
    if (eta >= 0.0)
        bjt.setEmissionCoeff(eta);
    
    if (Is >= 0.0)
        bjt.setSaturationCurrent(Is);
           
    return bjt;
}

inline void addBJTsToLayout(XmlElement * xml, CircuitModel::CircuitLayout & layout)
{
    std::vector<CircuitElement::BJT> BJTs;
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("BJT")){
            BJTs.push_back(getBJT(c));
        }
    }
    if (BJTs.size() >= 1){
        layout.BJTs = BJTs;
    }
}




inline CircuitElement::Tube12AX7 getTube12AX7(XmlElement * xml)
{
    CircuitElement::Tube12AX7::Model12AX7 model = CircuitElement::Tube12AX7::Model12AX7::RSD1;
    int nodeGrid = -1;
    int nodeAnode = -1;
    int nodeCathode = -1;
    
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("nodeGrid")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    nodeGrid = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("nodeCathode")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    nodeCathode = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("nodeAnode")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    nodeAnode = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("Model")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getStringAttribute("text");
                    if (val.equalsIgnoreCase("RSD1"))
                        model = CircuitElement::Tube12AX7::Model12AX7::RSD1;
                    else if (val.equalsIgnoreCase("RSD2"))
                        model = CircuitElement::Tube12AX7::Model12AX7::RSD2;
                    else if (val.equalsIgnoreCase("EHX"))
                        model = CircuitElement::Tube12AX7::Model12AX7::EXH;
                    
                }
            }
        }
    }
    
    return CircuitElement::Tube12AX7 (model,nodeGrid,nodeAnode,nodeCathode);
}

inline void addTube12AX7sToLayout(XmlElement * xml, CircuitModel::CircuitLayout & layout)
{
    std::vector<CircuitElement::Tube12AX7> Tube12AX7s;
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("Tube")){
            Tube12AX7s.push_back(getTube12AX7(c));
        }
    }
    if (Tube12AX7s.size() >= 1){
        layout.Tube12AX7s = Tube12AX7s;
    }
}



inline void addParametersToLayout(XmlElement * xml, CircuitModel::CircuitLayout & layout)
{
    
}

inline void addSettingsToLayout(XmlElement * xml, CircuitModel::CircuitLayout & layout)
{
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("numNodes")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getIntAttribute("text");
                    layout.numNodes = val;
                }
            }
            
        }
        else if (c->getTagName().equalsIgnoreCase("hasDCBlocker")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getBoolAttribute("text");
                    layout.hasDCBlocker = val;
                }
            }
        }
        else if (c->getTagName().equalsIgnoreCase("Output")){
            for (int n = 0; n < c->getNumChildElements() ; ++n){
                auto s = c->getChildElement(n);
                if (s->hasAttribute("text")){
                    auto val = s->getDoubleAttribute("text");
                    layout.Output = val;
                }
            }
        }
    }
}

inline void addElementsToLayout(XmlElement * xml, CircuitModel::CircuitLayout & layout)
{
    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto c = xml->getChildElement(m);
        if (c->getTagName().equalsIgnoreCase("VoltageInput")){
            addVoltageInputToLayout(c, layout);
        }
        else if (c->getTagName().equalsIgnoreCase("VoltageOutput")){
            addVoltageOutputToLayout(c, layout);
        }
        else if (c->getTagName().equalsIgnoreCase("Vs")){
            addVoltageSourcesToLayout(c, layout);
        }
        else if (c->getTagName().equalsIgnoreCase("Rs")){
            addRsToLayout(c, layout);
        }
        else if (c->getTagName().equalsIgnoreCase("Cs")){
            addCsToLayout(c, layout);
        }
        else if (c->getTagName().equalsIgnoreCase("OPAmps")){
            addOPAmpsToLayout(c, layout);
        }
        else if (c->getTagName().equalsIgnoreCase("VarRs")){
            addVarRsToLayout(c, layout);
        }
        else if (c->getTagName().equalsIgnoreCase("Pots")){
            addPotsToLayout(c, layout);
        }
        else if (c->getTagName().equalsIgnoreCase("Ds")){
            addDsToLayout(c, layout);
        }
        else if (c->getTagName().equalsIgnoreCase("BJTs")){
            addBJTsToLayout(c, layout);
        }
        else if (c->getTagName().equalsIgnoreCase("Tube12AX7s")){
            addTube12AX7sToLayout(c, layout);
        }
    }
}

inline CircuitModel openXMLCircuit(const File & f){
    std::unique_ptr<XmlElement> xml = parseXMLIfTagMatches (f,"PointToPointCircuit");
    
    CircuitModel::CircuitLayout layout;

    for (int m = 0; m < xml->getNumChildElements() ; ++m){
        auto s = xml->getChildElement(m);
        if (s->getTagName().equalsIgnoreCase("Parameters"))
             addParametersToLayout(s,layout);
        else if (s->getTagName().equalsIgnoreCase("Settings"))
             addSettingsToLayout(s,layout);
        else if (s->getTagName().equalsIgnoreCase("Elements"))
             addElementsToLayout(s,layout);
    
    }
    
    return CircuitModel(layout);
    
}



inline File getFactoryXMLFolder()
{
    const juce::File subfolder
    {
        juce::File::getSpecialLocation (juce::File::SpecialLocationType::userApplicationDataDirectory)
        .getChildFile ("Application Support")
        .getChildFile ("Hack Audio")
        .getChildFile ("Analog Lunchbox")
        .getChildFile ("XML")
    };
    return subfolder;
}

inline File searchForCircuit(const String& circuitName)
{
    auto factoryFolder = getFactoryXMLFolder();
    
    bool searchRecursively = true;
    auto foundFiles = factoryFolder.findChildFiles(File::TypesOfFileToFind::findFilesAndDirectories,
                                                   searchRecursively,
                                                   circuitName,
                                                   File::FollowSymlinks::noCycles);
    
    File circuitFile;
    if (!foundFiles.isEmpty())
        circuitFile = foundFiles.getFirst();
        
    return circuitFile;
}




// End of namespace
}




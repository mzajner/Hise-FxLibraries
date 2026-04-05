
import("stdfaust.lib");
import("misceffects.lib");

thresh= hslider("[01]Threshold[style:knob]", -6.0, -120.0, 6, 0.01):si.smoo;
att= hslider("[01]Attack[style:knob]", 0.1, 0.00001, 0.15, 0.00001):si.smoo;
hold= hslider("[01]Hold[style:knob]", 0.5, 0.001, 1.5, 0.001):si.smoo;
release= hslider("[01]release[style:knob]", 0.5, 0.001, 3.0, 0.001):si.smoo;

process= gate_stereo(thresh,att,hold,release);



/*
el = library("effect.lib");

process = vgroup("[2]", el.gate_demo); 
*/
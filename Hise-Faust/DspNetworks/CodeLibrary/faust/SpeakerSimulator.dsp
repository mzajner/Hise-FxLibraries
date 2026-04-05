import("stdfaust.lib");
import("misceffects.lib");

f1= hslider("[01]F1[style:knob]", 130, 50, 3000, 1):si.smoo;
f2= hslider("[01]F2[style:knob]", 5000, 3500, 20000, 1):si.smoo;

process= speakerbp(f1,f2),speakerbp(f1,f2);

/*
Dirt-simple speaker simulator (overall bandpass eq with observed roll-offs above and below the passband).

Low-frequency speaker model = +12 dB/octave slope breaking to flat near f1. Implemented using two dc blockers in series.

High-frequency model = -24 dB/octave slope implemented using a fourth-order Butterworth lowpass.

Example based on measured Celestion G12 (12" speaker):
*/
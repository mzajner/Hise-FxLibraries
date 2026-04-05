
declare name        "pitchShifter";
declare version     "1.0";
declare author      "Grame";
declare license     "BSD";
declare copyright   "(c)GRAME 2006";

//--------------------------------------
// revised version of simple real time pitch shifter
// with adjustments by Brian D'Oliveira to make the algorithm smoother
//--------------------------------------

import("stdfaust.lib");

pitchshifter = vgroup("Pitch Shifter", ef.transpose(
                                    hslider("window (samples)", 1000, 50, 96000, 1) : si.smoo,
                                    hslider("xfade (samples)", 250, 100, 1000, 1): si.smoo,
                                    hslider("shift (semitones) ", 0, -48, +48, 0.001) : si.smoo
                                  )
                );

process = pitchshifter,pitchshifter;

declare name    "smoothDelay";
declare author  "Yann Orlarey";
declare copyright "Grame";
declare version "1.0";
declare license "STK-4.3";

//--------------------------process----------------------------
//
//  A stereo smooth delay with a feedback control
//  
//  This example shows how to use sdelay, a delay that doesn't
//  click and doesn't transpose when the delay time is changed
//-------------------------------------------------------------

import("stdfaust.lib");

process = par(i, 2, voice)
    with 
    { 
        voice   = (+ : de.sdelay(N, interp, dtime)) ~ *(fback);
        N       = int(240000); 
        interp  = hslider("interpolation[unit:ms][style:knob]",10,1,100,0.1)*ma.SR/1000.0 : si.smoo ; 
        dtime   = hslider("delay[unit:ms][style:knob]", 0, 0, 1000, 0.1)*ma.SR/1000.0 : si.smoo;
        fback   = hslider("feedback[style:knob]",0,0,85,0.1)/100.0; 
    };
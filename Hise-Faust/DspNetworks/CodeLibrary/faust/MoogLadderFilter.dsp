declare name "moogLadder";
declare description "Demonstration of moogLadder";
declare author "Eric Tarr";

import("stdfaust.lib");

Q = hslider("Q",1,0.7072,25,0.01):si.smoo;
normFreq = hslider("freq",0.1,0,1,0.001):si.smoo;

process = ve.moogLadder(normFreq,Q),ve.moogLadder(normFreq,Q);
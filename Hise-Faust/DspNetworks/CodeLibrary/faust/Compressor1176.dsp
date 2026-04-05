declare limiter_1176_R4_stereo author "Julius O. Smith III";
declare limiter_1176_R4_stereo copyright
        "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>";
declare limiter_1176_R4_stereo license "MIT-style STK-4.3 license";

import("stdfaust.lib");

thresh = hslider("threshold",-6,-30,0,0.01):si.smoo;
ratio = hslider("ratio",4,0,20,4):si.smoo;
att = hslider("attack",0.00002,0.00002,0.08,0.00001):si.smoo;
rel = hslider("release",0.125,0.05,1.1,0.01):si.smoo;
limiter1176 = _, _ : co.compressor_stereo(ratio,thresh, att,rel):_, _ ;

process = limiter1176;

//ratio: 4 (moderate compression), 8 (severe compression), 12 (mild limiting), or 20 to 1 (hard limiting).

//att: 20-800 MICROseconds (Note: scaled by ratio in the 1176).

//rel: 50-1100 ms (Note: scaled by ratio in the 1176).

declare limiter_1176_R4_stereo author "Julius O. Smith III";
declare limiter_1176_R4_stereo copyright
        "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>";
declare limiter_1176_R4_stereo license "MIT-style STK-4.3 license";

import("stdfaust.lib");
ratio = hslider("ratio",4,0,20,0.01);
thresh = hslider("threshold",-6,-30,0,0.01);
att = hslider("attack",0.0008,0,10,0.01);
rel = hslider("release",0.5,0,5,0.01);
limiter1176 = _, _ : co.compressor_stereo(ratio,thresh,att,rel): _, _ ;

process = limiter1176;
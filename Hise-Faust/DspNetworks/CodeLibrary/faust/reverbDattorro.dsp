declare name "dattorro";
declare version "0.1";
declare author "Jakob Zerbian";
//MIT License
declare description "Dattorro Reverb edited MNTRA";

import("stdfaust.lib");

pre_delay = hslider("predelay",0.5, 0, 1, 0.001);
bw = hslider("bw",1, 0, 1, 0.001);
i_diff1 = hslider("diffusion1",0.5, 0, 0.95, 0.001):si.smoo;
i_diff2 = hslider("diffusion2",0.5, 0, 0.95, 0.001):si.smoo;
d_diff1 = hslider("diffusiond1",0.5, 0, 0.95, 0.001):si.smoo;
d_diff2 = hslider("diffusiond2",0.5, 0, 0.95, 0.001):si.smoo;
damping = hslider("dampings",0.5, 0, 1, 0.001):si.smooth(0.99);
decay = hslider("decayrate",0.5, 0, 1, 0.001):si.smooth(0.99);

process = (re.dattorro_rev(pre_delay, bw, i_diff1, i_diff2, decay, d_diff1, d_diff2, damping):>_,_);	

/*
pre_delay: pre-delay in samples (fixed at compile time)
bw: band-width filter (pre filtering); (0 - 1)
i_diff1: input diffusion factor 1; (0 - 1)
i_diff2: input diffusion factor 2;
decay: decay rate; (0 - 1); infinite decay = 1.0
d_diff1: decay diffusion factor 1; (0 - 1)
d_diff2: decay diffusion factor 2;
damping: high-frequency damping; no damping = 0.0
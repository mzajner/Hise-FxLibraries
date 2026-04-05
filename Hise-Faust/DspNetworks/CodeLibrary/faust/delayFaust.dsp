declare id   "duckDelay";
declare name "Duck Delay";
declare category "Echo / Delay";

import("stdfaust.lib");

//Controls
p_time = hslider("time", 500, 1, 2000, 1):si.smooth(ba.tau2pole(0.1));
p_feedback = hslider("feedback", 0, 0, 1, 0.01);
p_attack_time = hslider("attack", 0.1, 0.05, 0.5, 0.01);
p_release_time = hslider("release", 0.1, 0.05, 2, 0.01);
p_amount = hslider("amount", 0.5, 0, 56.0, 0.05):ba.db2linear;
p_mix = hslider("mix", 0.5, 0, 1, 0.01);
p_hicut = hslider("highcut", 10000, 1000, 20000, 100);
p_width = hslider("width", 1, 0, 1, 0.01);

// New modulation controls
p_mod_rate = hslider("mod_rate", 0.5, 0.01, 10, 0.01);    // LFO frequency in Hz
p_mod_depth = hslider("mod_depth", 0, 0, 50, 0.1);        // Modulation depth in ms

//Consts
c_channels_sw_time = 0.1;
c_fdelay_max_len = 393216;

// Modulated delay time calculation
get_delay_length(x) = base_delay + mod_offset
with {
    base_delay = x*ma.SR*0.001;  // Convert ms to samples
    // Triangle LFO for smoother modulation
    lfo = os.triangle(p_mod_rate);
    mod_offset = lfo * (p_mod_depth*ma.SR*0.001);
};

//High cut filter for feedback path
feedback_filter = fi.lowpass(2, p_hicut);

// Single channel processing
mono_process(x) = x<:
    x,(_<:(_+_:de.fdelay(c_fdelay_max_len,get_delay_length(p_time)):feedback_filter)~_*p_feedback,        
    (an.amp_follower_ud(p_attack_time,p_release_time):_*p_amount:_>1:(1 - _):
    si.smooth(ba.tau2pole(c_channels_sw_time)))):_,_*_
    :>_*(1-p_mix) + _*p_mix;

// Stereo processing with width control
process = _,_ : mono_process, mono_process : 
    (*(1 + p_width/2), *(1 + p_width/2));
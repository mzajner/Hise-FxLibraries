import("stdfaust.lib");
amp_volume = sp.stereoize(_*amp_vol)
with {
    amp_vol = vslider("[02]Volume[style:knob]", 7.5, 0.001, 10, 0.001) / 5;
};

amp_preamp = sp.stereoize((1/atan(amp_k))*atan(amp_k*_*amp_gain))
with {
    amp_gain = pow(vslider("[01]Gain[style:knob]", 1, 0.1, 10, 0.1),2);
    amp_k = 2;
};

amp_tonestack = component("tonestacks.lib").jcm800(t,m,l), component("tonestacks.lib").jcm800(t,m,l)
with {
    t = vslider("[05]Treble[style:knob]", 6, 0, 10, 0.01) / 10;
    m = vslider("[04]Middle[style:knob]", 4.5, 0, 10, 0.01) / 10;
    l = vslider("[03]Bass[style:knob]", 5, 0, 10, 0.01) / 10;
};
amp_cabsim = sp.stereoize(ef.speakerbp(80,5000));

amp_dry_wetST(x1,x2,y1,y2) = (wet*y1 + dry*x1),(wet*y2 + dry*x2)
with {
    wet = dw;
    dry = 1.0-wet;
    dw = vslider("[06]Reverb[style:knob]", 0.25, 0.0, 1, 0.01);
};

amp_sim = amp_preamp : amp_tonestack : amp_volume <: _,_,re.dattorro_rev(128, 0.99, 0.75, 0.625, 0.5, 0.7, 0.5, 0.001) : amp_dry_wetST : amp_cabsim;

/* ROTARY EFFECT */
ms_sample = ma.SR / 1000;

//UI Elements
rot_bpc = checkbox("Bypass");
t = checkbox("Chorale/Tremolo");
slow_rate_knob = vslider("[04]Chorale[style:knob]",.5,0.1,1.0,0.01) : si.smoo;
fast_rate_knob = vslider("[04]Tremolo[style:knob]",6,4,8,0.01) : si.smoo;
ramp_speed = vslider("[04]Ramp[style:knob]",2,1,3,0.01);

low_lfo_freq = slow_rate_knob + fast_rate_knob * en.asr(ramp_speed*3,1,ramp_speed*3,t) : /(1.1);
high_lfo_freq = slow_rate_knob + fast_rate_knob * en.asr(ramp_speed,1,ramp_speed,t);

// LFOs
high_lfo = 0.5*os.oscsin(high_lfo_freq)+0.5;
low_lfo = 0.5*os.oscsin(low_lfo_freq/1.1)+0.5;

// Dynamics Parameters
rot_waveshaper(_) = sp.stereoize((1/atan(rot_k))*atan(rot_k*_*rot_gain))
with {
    rot_gain = vslider("[02]Gain[style:knob]", 1.0, 0.1, 10, 0.1);
    rot_k = 2;
};

rot_volume = sp.stereoize(_*rot_vol)
with {
    rot_vol = vslider("[03]Volume[style:knob]", 1.0, 0.001, 2, 0.01);
};

max_delay_ms = 30;
rot_trem_depth = 0.6;
rotary(_,_) = de.fdelay(delay_buf_size, high_lfo * max_delay_ms)*aml, de.fdelay(delay_buf_size, max_delay_ms - (high_lfo * max_delay_ms))*amr : fi.resonlp(fml,0.7,1), fi.resonlp(fmr,0.7,1)
with {
    delay_buf_size = max_delay_ms * ms_sample;
    aml = 1-rot_trem_depth*high_lfo;
    amr = 1-rot_trem_depth*(1-high_lfo);
    fml = 2000 + 2000 * (1-high_lfo);
    fmr = 2000 + 2000 * high_lfo;
};

rot_mixer(a,b,c) = a+c,b+c;
rot_dry_wetST(x1,x2,y1,y2) = (wet*y1 + dry*x1),(wet*y2 + dry*x2)
with {
    wet = dw;
    dry = 1.0-wet;
    dw = vslider("[05]Mix[style:knob]", 1.0, 0.0, 1, 0.01);
};

rotary_effect = ba.bypass2(rot_bpc, (_,_ <:
        _,_,(rot_waveshaper(_,_) :
        low, hi :
        rot_mixer(_,_)) :
        rot_dry_wetST :
        rot_volume
    )
)
with {
    low = fi.lowpass(1, 800) <: fi.lowpass(1,200), fi.highpass(1,200) : _+_*-low_lfo;
    hi = fi.highpass(1, 800) <: rotary(_,_) : rot_horn_eq;
    rot_horn_eq = sp.stereoize(fi.peak_eq_cq(gain,2000,.4));
    gain = vslider("[07]Horn[style:knob]", 5, 0.0, 10.0, 0.1);
};

//process = hgroup("Rotary", rotary_effect);
//process = os.oscsin(100) <: hgroup("Signal Chain", hgroup("Rotary",rotary_effect) : hgroup("British Amp", amp_sim));
process = hgroup("Signal Chain", hgroup("Rotary",rotary_effect) : hgroup("British Amp", amp_sim));
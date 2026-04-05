declare name "StereoCrossDelay";
declare description "A stereo delay with feedback and cross-mixing";
declare author "Christopher Arndt";
declare license "MIT license";

import("stdfaust.lib");

MAX_DELAY = 2.0;

time_l	= ba.sec2samp(hslider("[0]Delay Left[symbol: delay_l][unit: ms]", 250.0, 0, MAX_DELAY * 1000, 0.1) * 0.001 : si.smoo);
time_r	= ba.sec2samp(hslider("[1]Delay Right[symbol: delay_r][unit: ms]", 166.7, 0, MAX_DELAY * 1000, 0.1) * 0.001 : si.smoo);

feedback = hslider("[2]Feedback[symbol: feedback][unit: %]", 20, 0, 93, 0.1) : si.smoo;

lp_feedback	= hslider("[3]Feedback Lowpass[symbol: lp_feedback][unit: hz][scale: log]", 12000, 20, 20000, 0.1) : si.smoo;
hp_feedback	= hslider("[4]Feedback Highpass[symbol: hp_feedback][unit: hz][scale: log]", 60, 20, 20000, 0.1);
dist = hslider("[5]Distortion[symbol: dist_feedback]", 0.1, 0.1, 50, 0.1) : si.smoo;

crossfeed = hslider("[6]Crossmix[symbol: crossfeed][unit: %]", 0, 0, 100, 0.1) : si.smoo;

mixer(fb_l, fb_r, in_l, in_r) =
    in_l + (fb_l * feedback * 0.01),
    in_r + (fb_r * feedback * 0.01);

// https://www.musicdsp.org/en/latest/Effects/104-variable-hardness-clipping-function.html
icurve = 1.0 / atan(dist);
atandist(x) = icurve * atan(x * dist);

fb_filter =
    atandist :
    fi.lowpass(2, lp_feedback) :
    fi.highpass(2, hp_feedback);

delay(t) = de.sdelay(ba.sec2samp(MAX_DELAY), 512, t);

crossmix(coef, l, r) =
    l * (1 - coef) + r * coef,
    r * (1 - coef) + l * coef;

process =
    (mixer : delay(time_l), delay(time_r) : crossmix(crossfeed * 0.01)) ~
    (fb_filter, fb_filter);
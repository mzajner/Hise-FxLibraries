import("stdfaust.lib");
import("misceffects.lib");

w= hslider("[01]Width[style:knob]", 0.5, 0, 1, 0.01):si.smoo;

process= stereo_width(w);
/**
 * Your copyright notice, declarations, and imports go here
 */

import("stdfaust.lib");

process = GritAmp;

GritAmp = warmth;

grit = hslider("Gritz", 50, 0, 100, 1):si.smoo;
tone = hslider("Tone", -7.5, -15, 0, 0.1):si.smoo;
tone_frequency = hslider("Tone Frequency", 720.0, 100, 5000, 1):si.smoo; // Add tone frequency slider
depth = hslider("Depth", 1, 0, 1, 0.001); // Add depth slider
volume = hslider("Volume", 1, 0, 1, 0.001);
reset = hslider("Reset", 0, 0, 1, 1); // Add a reset control

shut = min(2.0) : max(-2.0);

pre_filter = fi.dcblocker : fi.lowpass(1, 1720.0);

distortion = *(ba.db2linear(grit / 10))
    : +(0.5) : max(0.0) : min(1.0)
    : fi.highpass(1, 120) : +(0.5)
    <: _, _ : * : -(0.4) : *(ba.db2linear(grit / 5))
    : max(-1.0) : min(1.0) : +(0.15);

filter = fi.high_shelf(tone + 7.5, tone_frequency); // Use the tone_frequency slider here

attenuation = ba.db2linear(-10 * (grit / 100)); // Attenuate by -10 dB per 100 fuzz units

// Apply the depth control to the processing chain
depth_effect = _<:*(1 + (depth - 1) * distortion) :>_;

warmth =  pre_filter : *(10.0) : depth_effect : filter
    : *(ba.db2linear(volume * 50.0) / 100.0) * attenuation  : /(20.0);

output = warmth : reset; // Apply reset control

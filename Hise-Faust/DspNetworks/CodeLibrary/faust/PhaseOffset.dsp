import("stdfaust.lib");
import("maths.lib");

// Phase Offset control
phaseOffset = hslider("Phase Offset", 180, 0, 360, 0.1):si.smoo;

// Function to apply phase offset
applyPhaseOffset(signal) = 
    cos((2 * ma.PI * phaseOffset) / 360) * signal;

process = applyPhaseOffset(_);

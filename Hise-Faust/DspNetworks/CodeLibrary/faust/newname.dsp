declare name "Reverse Delay";
declare description "Simple reverse delay effect with adjustable windowing";

import("stdfaust.lib");

//Controls
p_time = hslider("time[ms]", 500, 10, 2000, 1):si.smooth(ba.tau2pole(0.1));
p_mix = hslider("mix", 0.5, 0, 1, 0.01);
p_feedback = hslider("feedback", 0.3, 0, 0.95, 0.01);
p_window_type = hslider("window type", 0, 0, 4, 1); // 0:Hann, 1:Triangle, 2:Cosine, 3:Gauss, 4:Rectangle
p_window_width = hslider("window width", 1, 0.1, 1, 0.01); // Controls the width of the window

// Convert delay time to samples
delay_samples = p_time * ma.SR/1000;

// Create reverse phase
phase = (+(1) ~ %(int(delay_samples))) / delay_samples;

// Adjusted phase for window width
window_phase = min(1, phase / p_window_width);

// Individual window functions
hann(p) = sin(p * ma.PI) * sin(p * ma.PI);
triangle(p) = 1 - abs((p * 2) - 1);
cosine(p) = 0.5 * (1 - cos(p * 2 * ma.PI));
gauss(p) = exp(-8 * (p - 0.5) * (p - 0.5));
rectangle(p) = 1;

// Window function selector using ba.selectn
window = ba.selectn(5, int(p_window_type), 
    hann(window_phase),
    triangle(window_phase),
    cosine(window_phase),
    gauss(window_phase),
    rectangle(window_phase)
);

process = _,_ : par(i, 2, mono_reverse)
with {
    mono_reverse(x) = x <: (_, reverse_buffer) : (*(1-p_mix), *(p_mix)) :> _
    with {
        // Delay buffer with feedback
        buffer = (+ : de.delay(ma.SR*2, int(delay_samples))) ~ *(p_feedback);
        
        // Read buffer in reverse with window applied
        reverse_buffer = buffer(x) : 
            de.fdelay(ma.SR*2, delay_samples * (1-phase)) : 
            *(window);
    };
};
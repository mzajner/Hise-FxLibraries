import("stdfaust.lib");

//Cubic Shaping
amount = hslider("Amount", 0.5, 0.01, 2, 0.01):si.smoo;
depth = hslider("Depth", 1, 0, 1, 0.01):si.smoo; // Add depth control
gain = hslider("Gain", 1, 0, 1, 0.01):si.smoo;
offset = hslider("Offset", 0, -1, 1, 0.01):si.smoo;

// Define the waveshaper module with depth parameter
waveshaper(amount, depth) =_<: _ * (1.0 - amount) + amount * _ * (_ * _) * depth :>_; 

process = (waveshaper(amount, depth) + offset) * gain;

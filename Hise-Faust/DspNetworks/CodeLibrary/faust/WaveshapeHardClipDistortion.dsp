/*Hard Clipping Algoithm*/

declare name "Hard Clipping";
declare author "MNTRA.io";
declare version "1.0";

import("music.lib");
import("stdfaust.lib");

distortion	= hslider("distortion", 50, 0, 100, 0.1):si.smoo;
gain	= hslider("gain", 0, 0, 24, 0.1):si.smoo;		// (dB)

// the hard clip function
f(a, x) = x * (abs(x) + a) / (x * x + (a - 1) * abs(x) + 1);


// gain correction factor to compensate for distortion
g(a)	= 1/sqrt(a+1);

process	= vgroup("distortion", (out))
with { out(x) = db2linear(gain)*g(distortion)*f(db2linear(distortion),x); };
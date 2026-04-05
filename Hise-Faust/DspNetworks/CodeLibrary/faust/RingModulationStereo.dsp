import("filter.lib");

freq = hslider("freq",2,0.001,10000,0.001) : smooth(0.999);
gain = hslider("gain",1,0,1,0.01) : smooth(0.999);
depth = hslider("depth",1,0,1,0.01) : smooth(0.999);

pan = 1-(depth*osc(freq)/2 + 0.5);
stereoRingMod = _ <: *(pan),*(1-pan); 

process = stereoRingMod : *(gain), *(gain);

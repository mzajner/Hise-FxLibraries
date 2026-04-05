import("stdfaust.lib");


process = ringmod,ringmod;

ringmod = _<:_,*(os.oscs(freq)):drywet
		with {
            freq = hslider ( "[1]Modulation Frequency[acc:1 0 -10 0 10][scale:log]", 2,0.001,10000,0.001):si.smooth(0.999);
            drywet(x,y) = (1-c)*x + c*y;
            c = hslider("[2]Modulation intensity[style:knob][unit:%][acc:1 0 -10 0 10]", 100,0,100,0.01)*(0.01):si.smooth(0.999);
        };
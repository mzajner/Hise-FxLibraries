import("stdfaust.lib");

process = vgroup("CombFilter", environment {
    declare name "Comb Filter";

    /* =========== DESCRIPTION ==============
    
    - A feedforward comb filter creates interferences in a sound without feedback, 
      reducing the risk of excessive resonance
    - Rocking = to change the filtering frequency
    - Head = no filter
    - Bottom = maximum filtering

    */

    process = fi.ff_fcomb(maxdel, del, b0, bM) 
        with {
            maxdel = 1<<16;
            freq = 1/(hslider("Frequency[acc:0 1 -10 0 10]", 2500, 100, 20000, 0.001)):si.smooth(0.99);
            del = freq * (ma.SR) : si.smooth(0.99);
            b0 = 1; // Direct path gain
            bM = hslider("Intensity[acc:1 0 -10 0 10]", 80, 0, 95, 0.01)*(0.01):si.smooth(0.99):min(0.999):max(0);
        };
}.process);
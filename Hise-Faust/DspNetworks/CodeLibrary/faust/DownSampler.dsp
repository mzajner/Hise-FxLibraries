declare name "Simple Mid Side Ping Pong Flip Flop Tic Tac Zip Zap Delay";
declare vendor "G.A.";
declare author "Gabriele Acquafredda";
ts = library("12ts.lib");

import("stdfaust.lib");
import("filters.lib");





filters = hgroup("Filters", filterlphp, filterlphp)
with {
    flp = hslider("LPF Freq",22000,20,22000,1):si.smoo;
    qlp = hslider("LPF Q",1,1,5,0.05):si.smoo;

    fhp = hslider("HPF Freq",20,20,22000,1):si.smoo;
    qhp = hslider("HPF Q",1,1,5,0.05):si.smoo;

    filterlphp = resonlp(flp,qlp,1) : resonhp(fhp,qhp,1);
};


mod_matrix = hgroup("Modulation", modulations, modulations)
with {
    freq_down = hslider("Downsample Frequency",20000,20,22000,1):si.smoo;
    modulations = ba.downSample(freq_down);
};

process = mod_matrix : filters;

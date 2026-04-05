declare name "Korg35Filter";
declare description "FAUST Korg 35 Band-Pass Filter";
declare author "Your Name";
declare license "MIT-style STK-4.3 license";

import("stdfaust.lib");

// Define the soft clipping function outside the letrec block
dynamicQ(s) = Q - (Q * max(abs(s), abs(s1), abs(s2)) * 0.1);  // Example dynamic adjustment

korg35Filter(freq,Q) = _ <: (s1,s2,s3,yLpf) : !,!,!,_
letrec{
    // Apply soft clipping to the feedback part of the signal
's1 = _-s1:_*(alpha*2):_+s1 with { Q = dynamicQ(s1); };
    's2 = _-s1:_*alpha:_+s1:_+(s3*B3):_+(s2*B2):_*alpha0:_-s3:_*alpha:_+s3:_*K:_-s2:_*(alpha*2):_+s2;
    's3 = _-s1:_*alpha:_+s1:_+(s3*B3):_+(s2*B2):_*alpha0:_-s3:_*(alpha*2):_+s3;
    'yLpf = _-s1:_*alpha:_+s1:_+(s3*B3):_+(s2*B2) :_*alpha0:_-s3:_*alpha:_+s3;  // LPF output
    'yHpf = _<:(_-s1:_*alpha:_+s1)*-1,_:>_+(s3*B3):_+(s2*B2):_*alpha0;  // HPF output
}
with{
    K = 2.0*(Q - 0.707)/(10.0 - 0.707);
    wd = 2*ma.PI*freq;
    T = 1/ma.SR;
    wa = (2/T)*tan(wd*T/2);
    g = wa*T/2;
    G = g/(1.0 + g);
    alpha = G;
    B3 = (K - K*G)/(1 + g);
    B2 = -1/(1 + g);
    alpha0 = 1/(1 - K*G + K*G*G);
    // Feedback coefficient, adjust as needed to control resonance
    FB = K*alpha;
};

q = hslider("[1]Q[symbol: q][abbrev: q][style:knob]", 1.0, 0.5, 10.0, 0.01):si.smoo;
cutoff = hslider("[0]Cutoff frequency[symbol: cutoff][abbrev: cutoff][unit: hz][scale: log][style: knob]", 20000.0, 20.0, 20000, 0.1):si.smoo;

process = korg35Filter(cutoff, q), korg35Filter(cutoff, q);

declare moogHalfLadder author "Eric Tarr";
declare moogHalfLadder license "MIT-style STK-4.3 license";

import("stdfaust.lib");

moogHalfLadder(freq,Q) = _ <: (s1,s2,s3,y) : !,!,!,_
letrec{
  's1 = -(s3*B3*k):-(s2*B2*k):-(s1*B1*k):*(alpha0):-(s1):*(alpha*2):+(s1);
  's2 = -(s3*B3*k):-(s2*B2*k):-(s1*B1*k):*(alpha0):-(s1):*(alpha):+(s1):-(s2):*(alpha*2):+(s2);
  's3 = -(s3*B3*k):-(s2*B2*k):-(s1*B1*k):*(alpha0):-(s1):*(alpha):+(s1):-(s2):*(alpha):+(s2):-(s3):*(alpha*2):+(s3);
  'y = -(s3*B3*k):-(s2*B2*k):-(s1*B1*k):*(alpha0):-(s1):*(alpha):+(s1):-(s2):*(alpha):+(s2) <:_*-1,((-(s3):*(alpha):+(s3))*2):>_;
}
with{
  // freq = 2*(10^(3*normFreq+1));
  normFreq = (log10(freq) - log10(2)) / 3.0 - (1.0 / 3.0);
  k = 2.0*(Q - 0.707)/(25.0 - 0.707);
  wd = 2*ma.PI*freq;
  T = 1/ma.SR;
  wa = (2/T)*tan(wd*T/2);
  g = wa*T/2;
  G = g/(1.0 + g);
  alpha = G;
  GA = 2*G-1; // All-pass gain
  B1 = GA*G/(1+g);
  B2 = GA/(1+g);
  B3 = 2/(1+g);
  alpha0 = 1/(1 + k*GA*G*G);
};


q = hslider("[1]Q[symbol: q][abbrev: q][style:knob]", 1.0, 0.707, 25, 0.01):si.smoo;
cutoff = hslider("[0]Cutoff frequency[symbol: cutoff][abbrev: cutoff][unit: hz][scale: log][style: knob]", 20000.0, 20.0, 20000, 0.1):si.smoo;

process = moogHalfLadder(cutoff, q), moogHalfLadder(cutoff, q);
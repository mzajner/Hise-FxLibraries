declare name "DiodeLadder";
declare description "FAUST Diode Ladder 24 dB LPF";
declare author "Christopher Arndt";
declare license "MIT-style STK-4.3 license";

import("stdfaust.lib");

diodeLadder(freq,Q,drive) = ef.cubicnl(drive,0)*1.5 <:(s1,s2,y)  : !,!,_
letrec{
 's1 = _-(s2*B2*SG2*k) :
        _-((s2*B2*d1 + s1)*B1*SG1*k) :
        _*alpha0: _*gam1 : _+(s2)*B2 : //_+S2
        _+((s2*B2)*d1 + s1)*B1*G2 : // _ + (S2 ...
        _*a1 : _-s1 : _*alpha*2 : _+s1;

  's2 = _-(s2*B2*SG2*k) :
        _-((s2*B2*d1 + s1)*B1*SG1*k) :
        _*alpha0: _*gam1 : _+(s2)*B2 : //_+S2
        _+((s2*B2)*d1 + s1)*B1*G2 : // _ + (S2 ...
        _*a1 : _-s1 : _*alpha : _+s1 : _*gam2 :
        _*a2 : _-s2 : _*alpha*2 : _+s2;

  // Output signal
  'y = _-(s2*B2*SG2*k) :
       _-((s2*B2*d1 + s1)*B1*SG1*k) :
       _*alpha0: _*gam1 : _+(s2)*B2 : //_+S2
       _+((s2*B2)*d1 + s1)*B1*G2 : // _ + (S2 ...
       _*a1 : _-s1 : _*alpha : _+s1 : _*gam2 :
       _*a2 : _-s2 : _*alpha : _+s2;
}
with{
  // freq = 2*(10^(3*normFreq+1));
  normFreq = (log10(freq) - log10(2)) / 3.0 - (1.0 / 3.0);
  k = (17 - (normFreq^10)*9.7)*(Q - 0.707)/(25.0 - 0.707);
  wd = 2*ma.PI*freq;
  T = 1/ma.SR;
  wa = (2/T)*tan(wd*T/2);
  g = wa*T/2;
  G2 = 0.5*g/(1 + g);
  G1 = g/(1.0 + g - g*G2);
  Gamma = G1*G2;
  SG1 = G2; // feedback gain pre-calculated for 2 poles
  SG2 = 1;
  alpha = g/(1+g);
  alpha0 = 1/(1+k*Gamma);
  gam1 = 1+G1*G2;
  gam2 = 1;
  a1 = 1; // a0 for 1st LPF
  a2 = 0.5; // a0 for 2nd LPF
  B1 = 1/(1+g-g*G2); // Beta for 1st block
  B2 = 1/(1+g);
  d1 = g; // delta for 1st block
};

q = hslider("[1]Q[symbol: q][abbrev: q][style:knob]", 1.0, 0.7072, 25.0, 0.01);
cutoff = hslider("[0]Cutoff frequency[symbol: cutoff][abbrev: cutoff][unit: hz][scale: log][style: knob]", 20000.0, 20.0, 20000, 0.1):si.smoo;
drive = hslider("drive[style:knob]", 0.5, 0, 1, 0.01):si.smoo;

process = diodeLadder(cutoff, q,drive), diodeLadder(cutoff, q,drive);
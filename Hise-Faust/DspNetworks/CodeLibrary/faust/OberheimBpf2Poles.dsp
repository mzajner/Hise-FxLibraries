declare name "Oberheim";
declare description "Oberheim multi-mode, state-variable filter";
declare author "Christopher Arndt, Eric Tarr";
declare license "MIT-style STK-4.3 license";

import("stdfaust.lib");


oberheim(freq, Q) = _<:(s1,s2,ybpf) : !,!,_
letrec{
  's1 = _-s2:_-(s1*FBs1):_*alpha0:_*g<:_,(_+s1:ef.cubicnl(0.0,0)):>_;
  's2 = _-s2:_-(s1*FBs1):_*alpha0:_*g:_+s1:ef.cubicnl(0.0,0):_*g*2:_+s2;
  // Compute the BSF, BPF, HPF, LPF outputs
  //'ybsf = _-s2:_-(s1*FBs1):_*alpha0<:(_*g:_+s1:ef.cubicnl(0.0,0):_*g:_+s2),_:>_;
  'ybpf = _-s2:_-(s1*FBs1):_*alpha0:_*g:_+s1:ef.cubicnl(0.0,0);
  //'yhpf = _-s2:_-(s1*FBs1):_*alpha0;
  //'ylpf = _-s2:_-(s1*FBs1):_*alpha0:_*g :_+s1:ef.cubicnl(0.0,0):_*g:_+s2;
}
with{
  // freq = 2*(10^(3*normFreq+1));
  wd = 2*ma.PI*freq;
  T = 1/ma.SR;
  wa = (2/T)*tan(wd*T/2);
  g = wa*T/2;
  G = g/(1.0 + g);
  R = 1/(2*Q);
  FBs1 = (2*R+g);
  alpha0 = 1/(1 + 2*R*g + g*g);
};

q = hslider("[1]Q[symbol: q][abbrev: q][style:knob]", 1.0, 0.3, 10.0, 0.01):si.smoo;
cutoff = hslider("[0]Cutoff frequency[symbol: cutoff][abbrev: cutoff][unit: hz][scale: log][style: knob]", 20000.0, 20.0, 20000, 0.1):si.smoo;

process = oberheim(cutoff, q), oberheim(cutoff, q);
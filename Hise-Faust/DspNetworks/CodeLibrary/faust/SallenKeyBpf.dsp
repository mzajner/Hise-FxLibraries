declare name "SallenKeyOnePoleLPF";
declare author "Eric Tarr";
declare license "MIT-style STK-4.3 license";

import("stdfaust.lib");

declare sallenKey2ndOrder author "Eric Tarr";
declare sallenKey2ndOrder license "MIT-style STK-4.3 license";

sallenKey2ndOrder(normFreq,Q) = _<:(s1,s2,ybpf) : !,!,_
letrec{
  's1 = -(s2):-(s1*FBs1):*(alpha0):*(g*2):+(s1);
  's2 = -(s2):-(s1*FBs1):*(alpha0):*(g):+(s1):*(g*2):+(s2);
  // Compute the LPF, BPF, HPF outputs
  //'ylpf = -(s2):-(s1*FBs1):*(alpha0):*(g*2):+(s1):*(g):+(s2);
  'ybpf = -(s2):-(s1*FBs1):*(alpha0):*(g):+(s1);
  //'yhpf = -(s2):-(s1*FBs1):*(alpha0);
}
with{
  //freq = 2*(10^(3*normFreq+1));
  wd = 2*ma.PI*freq;
  T = 1/ma.SR;
  wa = (2/T)*tan(wd*T/2);
  g = wa*T/2;
  G = g/(1.0 + g);
  R = 1/(2*Q);
  FBs1 = (2*R+g);
  alpha0 = 1/(1 + 2*R*g + g*g);
};

Q = hslider("Q[Q]", 0.5, 0.3, 8.0, 0.1):si.smoo;
freq = hslider("Cutoff Frequency[cutoff]", 1000.0, 20.0, 20000.0, 0.1):si.smoo;

process = sallenKey2ndOrder(freq, Q), sallenKey2ndOrder(freq, Q);

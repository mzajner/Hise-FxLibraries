import("stdfaust.lib");
import("filter.lib");  


drive = hslider("Drive[style:knob]", 0.5, 0, 1, 0.01):si.smoo; 
pregain = pow(10, drive*2); 


nonlinearityEnv = environment {

  makeOdd(f, x) = x : optionalNegate : f : optionalNegate
  with {
    optionalNegate(y) = ba.if(x<0, -y, y);
  };

  softclipQuadratic(x) = makeOdd(f, x)
  with {
    f(x) = ba.if(x <= 1./3., 2*x, ba.if(x <= 2./3., y, 1))
    with {
      y = (3-(2-3*x)^2)/3;
    };
  };
};

softclipQuadratic = nonlinearityEnv.softclipQuadratic;

breakFreq = hslider("Break Frequency[Hz]", 35, 20, 200, 1):si.smoo; 
quadratic = _ : *(pregain) : softclipQuadratic : dcblockerat(breakFreq);

process = quadratic, quadratic;

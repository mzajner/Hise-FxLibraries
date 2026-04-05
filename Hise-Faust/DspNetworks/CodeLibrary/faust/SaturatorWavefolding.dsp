import("stdfaust.lib");
import("filter.lib");  

// Define sliders for Drive control and Wavefolding Width
drive = hslider("Drive[style:knob]", 0.5, 0, 1, 0.01) : si.smoo; 
width = hslider("Width[style:knob]", 0.5, 0, 1, 0.01) : si.smoo;
pregain = pow(10, drive * 2); // Calculate pre-gain from drive

// Environment containing non-linear processing functions
nonlinearityEnv = environment {
  makeOdd(f, x) = x : optionalNegate : f : optionalNegate
  with {
    optionalNegate(y) = ba.if(x < 0, -y, y);
  };

  // Wavefolding with Drive Control
  wavefold(width, x) = makeOdd(f, x)
  with {
    f(x) = ba.if(x > (1 - 2*a), tri, x) : *(g)
    with {
      // Adjusted width calculation
      a = width : aa.clip(0, 1) : *(.4); 
      // Peak-level normalization
      g = 1 / (1 - 2*a);
      // Triangle-like function for wavefolding effect
      tri = 1 - 2.5*a + a*abs(ma.frac((x - (1 - 2*a)) / (2*a)) - .5);
    };
  };
};

// Access the wavefold function from the environment
wavefold = nonlinearityEnv.wavefold(width);

// Define break frequency for DC blocker, if needed
breakFreq = hslider("Break Frequency[Hz]", 35, 20, 200, 1) : si.smoo; 

// Process chain for wavefolding effect
process = _ : *(pregain) : wavefold : dcblocker;

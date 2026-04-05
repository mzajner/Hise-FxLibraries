import("stdfaust.lib");

//==============================
// Two-Knob Vital Reverb
// Based on the Vital synthesizer reverb algorithm
//==============================

process = _,_ : vitalReverb : par(i, 2, _ * outputGain) : _,_
with {
    // Main reverb processing using re.vital_rev
    vitalReverb = re.vital_rev(
        prelow,     // pre-delay lowpass
        prehigh,    // pre-delay highpass  
        lowcutoff,  // low cutoff frequency
        highcutoff, // high cutoff frequency
        lowgain,    // low frequency gain
        highgain,   // high frequency gain
        chorus_amt, // chorus amount
        chorus_freq,// chorus frequency
        predelay,   // pre-delay amount
        time,       // reverb time (mapped to Size)
        size,       // reverb size (mapped to Size)
        mix         // dry/wet mix (mapped to Mix)
    );
    
    //==============================
    // Two-Knob Interface
    //==============================
    
    // Primary controls (user interface)
    sizeParam = hslider("[1]Size", 0.7, 0, 1, 0.01) : si.smoo;
    mixParam = hslider("[0]Mix", 0.5, 0, 1, 0.01) : si.smoo;
    
    //==============================
    // Internal Parameter Mapping
    // Optimized settings for musical results
    //==============================
    
    // Pre-delay EQ (subtle high-frequency emphasis for clarity)
    prelow = 0.8;     // gentle low-cut on pre-delay
    prehigh = 0.2;    // minimal high-cut on pre-delay
    
    // Main EQ (frequency-dependent decay for natural sound)
    lowcutoff = 0.1;  // very gentle low-cut
    highcutoff = 0.7; // moderate high-cut for warmth
    lowgain = 1.0;    // full low-frequency content
    highgain = 0.6;   // slightly reduced highs for smoothness
    
    // Chorus modulation (adds subtle movement and width)
    chorus_amt = 0.15; // subtle chorus for natural movement
    chorus_freq = 0.3; // slow modulation rate
    
    // Time-based parameters (mapped to Size control)
    predelay = sizeParam * 0.01; // pre-delay scales with size (0-40%)
    time = sizeParam;           // direct mapping to reverb time
    size = sizeParam;           // direct mapping to reverb size
    
    // Mix control
    mix = mixParam;             // direct mapping to mix
    
    // Output gain compensation (Vital reverb tends to be quiet)
    outputGain = 1.0;           // boost output level for audibility
};
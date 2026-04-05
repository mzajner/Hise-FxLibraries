// ==================================| Enhanced SSL Console EQ External Node |==================================

#pragma once
#include <JuceHeader.h>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

// ==========================| The node class with all required callbacks |==========================

template <int NV> struct sslEqExternal: public data::base
{
    // Metadata Definitions ------------------------------------------------------------------------
    
    SNEX_NODE(sslEqExternal);
    
    struct MetadataClass
    {
        SN_NODE_ID("sslEqExternal");
    };
    
    // set to true if you want this node to have a modulation dragger
    static constexpr bool isModNode() { return false; };
    static constexpr bool isPolyphonic() { return NV > 1; };
    // set to true if your node produces a tail
    static constexpr bool hasTail() { return false; };
    // set to true if your doesn't generate sound from silence and can be suspended when the input signal is silent
    static constexpr bool isSuspendedOnSilence() { return false; };
    // Undefine this method if you want a dynamic channel count
    static constexpr int getFixChannelAmount() { return 2; };
    
    // Define the amount and types of external data slots you want to use
    static constexpr int NumTables = 0;
    static constexpr int NumSliderPacks = 0;
    static constexpr int NumAudioFiles = 0;
    static constexpr int NumFilters = 0;
    static constexpr int NumDisplayBuffers = 0;
    
    // Constructor
    sslEqExternal()
    {
        // Initialize all filter states
        resetAllStates();
        
        // Default SSL parameters
        hpfFreq = 80.0;
        lfGain = 0.0;
        lfFreq = 100.0;
        lfBell = false; // shelf mode
        lmfGain = 0.0;
        lmfFreq = 500.0;
        lmfQ = 1.0;
        hmfGain = 0.0;
        hmfFreq = 2500.0;
        hmfQ = 1.0;
        hfGain = 0.0;
        hfFreq = 10000.0;
        hfBell = false; // shelf mode
        lpfFreq = 15000.0;
        
        // New filter parameters
        midBumpGain = 0.0;      // Default: off
        steepHpfFreq = 100.0;   // 12dB/oct HPF at 100Hz
        gentleLpfFreq = 13000.0; // 6dB/oct LPF at 13kHz
        midBumpEnable = false;   // Toggle for mid bump
        steepHpfEnable = false;  // Toggle for steep HPF
        gentleLpfEnable = false; // Toggle for gentle LPF
        
        bypass = false;
        sampleRate = 48000.0;
        updateAllCoefficients();
    }
    
    // Scriptnode Callbacks ------------------------------------------------------------------------
    
    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;
        updateAllCoefficients();
    }
    
    void reset()
    {
        resetAllStates();
    }
    
    void handleHiseEvent(HiseEvent& e)
    {
        // Not needed for this EQ
    }
    
    template <typename T> void process(T& data)
    {
        static constexpr int NumChannels = getFixChannelAmount();
        // Cast the dynamic channel data to a fixed channel amount
        auto& fixData = data.template as<ProcessData<NumChannels>>();
        
        // Create a FrameProcessor object
        auto fd = fixData.toFrameData();
        
        while(fd.next())
        {
            // Forward to frame processing
            processFrame(fd.toSpan());
        }
    }
    
    template <typename T> void processFrame(T& data)
    {
        if (bypass)
            return;
        
        // Process left channel through enhanced SSL chain
        double signal = data[0];
        signal = processEnhancedSSLChain(signal, 0); // channel 0 = left
        data[0] = signal;
        
        // Process right channel through enhanced SSL chain
        signal = data[1];
        signal = processEnhancedSSLChain(signal, 1); // channel 1 = right
        data[1] = signal;
    }
    
    int handleModulation(double& value)
    {
        return 0;
    }
    
    void setExternalData(const ExternalData& data, int index)
    {
        // Not used
    }
    
    // Parameter Functions -------------------------------------------------------------------------
    
    template <int P> void setParameter(double v)
    {
        if (P == 0) { hpfFreq = v; updateAllCoefficients(); } // Direct Hz value
        else if (P == 1) { lfGain = v; updateAllCoefficients(); } // Direct dB value
        else if (P == 2) { lfFreq = v; updateAllCoefficients(); } // Direct Hz value
        else if (P == 3) { lfBell = v >= 0.5; updateAllCoefficients(); } // shelf/bell toggle
        else if (P == 4) { lmfGain = v; updateAllCoefficients(); } // Direct dB value
        else if (P == 5) { lmfFreq = v; updateAllCoefficients(); } // Direct Hz value
        else if (P == 6) { lmfQ = v; updateAllCoefficients(); } // Direct Q value
        else if (P == 7) { hmfGain = v; updateAllCoefficients(); } // Direct dB value
        else if (P == 8) { hmfFreq = v; updateAllCoefficients(); } // Direct Hz value
        else if (P == 9) { hmfQ = v; updateAllCoefficients(); } // Direct Q value
        else if (P == 10) { hfGain = v; updateAllCoefficients(); } // Direct dB value
        else if (P == 11) { hfFreq = v; updateAllCoefficients(); } // Direct Hz value
        else if (P == 12) { hfBell = v >= 0.5; updateAllCoefficients(); } // shelf/bell toggle
        else if (P == 13) { lpfFreq = v; updateAllCoefficients(); } // Direct Hz value
        else if (P == 14) { bypass = v >= 0.5; } // bypass
        // New parameters
        else if (P == 15) { midBumpGain = v; updateAllCoefficients(); } // Mid bump gain (-15 to +15dB)
        else if (P == 16) { steepHpfFreq = v; updateAllCoefficients(); } // Steep HPF frequency
        else if (P == 17) { gentleLpfFreq = v; updateAllCoefficients(); } // Gentle LPF frequency
        else if (P == 18) { midBumpEnable = v >= 0.5; updateAllCoefficients(); } // Mid bump enable
        else if (P == 19) { steepHpfEnable = v >= 0.5; updateAllCoefficients(); } // Steep HPF enable
        else if (P == 20) { gentleLpfEnable = v >= 0.5; updateAllCoefficients(); } // Gentle LPF enable
    }
    
    void createParameters(ParameterDataList& data)
    {
        // Original SSL EQ parameters (0-14)
        {
            parameter::data p("HPF Freq", { 20.0, 500.0, 0.1 });
            registerCallback<0>(p);
            p.setDefaultValue(80.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("LF Gain", { -15.0, 15.0, 0.1 });
            registerCallback<1>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("LF Freq", { 30.0, 450.0, 1.0 });
            registerCallback<2>(p);
            p.setDefaultValue(100.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("LF Bell", { 0.0, 1.0, 1.0 });
            registerCallback<3>(p);
            p.setDefaultValue(0.0); // 0=shelf, 1=bell
            data.add(std::move(p));
        }
        {
            parameter::data p("LMF Gain", { -15.0, 15.0, 0.1 });
            registerCallback<4>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("LMF Freq", { 200.0, 2500.0, 1.0 });
            registerCallback<5>(p);
            p.setDefaultValue(500.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("LMF Q", { 0.3, 5.0, 0.1 });
            registerCallback<6>(p);
            p.setDefaultValue(1.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("HMF Gain", { -15.0, 15.0, 0.1 });
            registerCallback<7>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("HMF Freq", { 600.0, 7000.0, 1.0 });
            registerCallback<8>(p);
            p.setDefaultValue(2500.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("HMF Q", { 0.3, 5.0, 0.1 });
            registerCallback<9>(p);
            p.setDefaultValue(1.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("HF Gain", { -15.0, 15.0, 0.1 });
            registerCallback<10>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("HF Freq", { 1500.0, 16000.0, 1.0 });
            registerCallback<11>(p);
            p.setDefaultValue(10000.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("HF Bell", { 0.0, 1.0, 1.0 });
            registerCallback<12>(p);
            p.setDefaultValue(0.0); // 0=shelf, 1=bell
            data.add(std::move(p));
        }
        {
            parameter::data p("LPF Freq", { 5000.0, 20000.0, 1.0 });
            registerCallback<13>(p);
            p.setDefaultValue(15000.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Bypass", { 0.0, 1.0, 1.0 });
            registerCallback<14>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        
        // New filter parameters (15-20)
        {
            parameter::data p("Mid Bump Gain", { -15.0, 15.0, 0.1 });
            registerCallback<15>(p);
            p.setDefaultValue(1.2); // Default +1.2dB as requested
            data.add(std::move(p));
        }
        {
            parameter::data p("Steep HPF Freq", { 50.0, 300.0, 1.0 });
            registerCallback<16>(p);
            p.setDefaultValue(100.0); // 100Hz as requested
            data.add(std::move(p));
        }
        {
            parameter::data p("Gentle LPF Freq", { 8000.0, 20000.0, 1.0 });
            registerCallback<17>(p);
            p.setDefaultValue(13000.0); // 13kHz as requested
            data.add(std::move(p));
        }
        {
            parameter::data p("Mid Bump Enable", { 0.0, 1.0, 1.0 });
            registerCallback<18>(p);
            p.setDefaultValue(0.0); // Off by default
            data.add(std::move(p));
        }
        {
            parameter::data p("Steep HPF Enable", { 0.0, 1.0, 1.0 });
            registerCallback<19>(p);
            p.setDefaultValue(0.0); // Off by default
            data.add(std::move(p));
        }
        {
            parameter::data p("Gentle LPF Enable", { 0.0, 1.0, 1.0 });
            registerCallback<20>(p);
            p.setDefaultValue(0.0); // Off by default
            data.add(std::move(p));
        }
    }
    
private:
    // SSL EQ Parameters
    double sampleRate;
    double hpfFreq;
    double lfGain, lfFreq;
    bool lfBell;
    double lmfGain, lmfFreq, lmfQ;
    double hmfGain, hmfFreq, hmfQ;
    double hfGain, hfFreq;
    bool hfBell;
    double lpfFreq;
    bool bypass;
    
    // New filter parameters
    double midBumpGain;     // +1.2dB @ 750Hz Q 1.0
    double steepHpfFreq;    // 12dB/oct HPF @ 100Hz
    double gentleLpfFreq;   // 6dB/oct LPF @ 13kHz
    bool midBumpEnable;
    bool steepHpfEnable;
    bool gentleLpfEnable;
    
    // Original filter coefficients for each stage
    double hpf_b0[2], hpf_b1[2], hpf_b2[2], hpf_a1[2], hpf_a2[2];
    double lf_b0[2], lf_b1[2], lf_b2[2], lf_a1[2], lf_a2[2];
    double lmf_b0[2], lmf_b1[2], lmf_b2[2], lmf_a1[2], lmf_a2[2];
    double hmf_b0[2], hmf_b1[2], hmf_b2[2], hmf_a1[2], hmf_a2[2];
    double hf_b0[2], hf_b1[2], hf_b2[2], hf_a1[2], hf_a2[2];
    double lpf_b0[2], lpf_b1[2], lpf_b2[2], lpf_a1[2], lpf_a2[2];
    
    // New filter coefficients
    double midbump_b0[2], midbump_b1[2], midbump_b2[2], midbump_a1[2], midbump_a2[2];
    double steephpf_b0[2], steephpf_b1[2], steephpf_b2[2], steephpf_a1[2], steephpf_a2[2];
    double gentlelpf_b0[2], gentlelpf_b1[2], gentlelpf_a1[2]; // 1st order = no b2, a2
    
    // Original filter states for each stage [channel]
    double hpf_x1[2], hpf_x2[2], hpf_y1[2], hpf_y2[2];
    double lf_x1[2], lf_x2[2], lf_y1[2], lf_y2[2];
    double lmf_x1[2], lmf_x2[2], lmf_y1[2], lmf_y2[2];
    double hmf_x1[2], hmf_x2[2], hmf_y1[2], hmf_y2[2];
    double hf_x1[2], hf_x2[2], hf_y1[2], hf_y2[2];
    double lpf_x1[2], lpf_x2[2], lpf_y1[2], lpf_y2[2];
    
    // New filter states
    double midbump_x1[2], midbump_x2[2], midbump_y1[2], midbump_y2[2];
    double steephpf_x1[2], steephpf_x2[2], steephpf_y1[2], steephpf_y2[2];
    double gentlelpf_x1[2], gentlelpf_y1[2]; // 1st order = no x2, y2
    
    void resetAllStates()
    {
        for (int ch = 0; ch < 2; ++ch)
        {
            // Original states
            hpf_x1[ch] = hpf_x2[ch] = hpf_y1[ch] = hpf_y2[ch] = 0.0;
            lf_x1[ch] = lf_x2[ch] = lf_y1[ch] = lf_y2[ch] = 0.0;
            lmf_x1[ch] = lmf_x2[ch] = lmf_y1[ch] = lmf_y2[ch] = 0.0;
            hmf_x1[ch] = hmf_x2[ch] = hmf_y1[ch] = hmf_y2[ch] = 0.0;
            hf_x1[ch] = hf_x2[ch] = hf_y1[ch] = hf_y2[ch] = 0.0;
            lpf_x1[ch] = lpf_x2[ch] = lpf_y1[ch] = lpf_y2[ch] = 0.0;
            
            // New filter states
            midbump_x1[ch] = midbump_x2[ch] = midbump_y1[ch] = midbump_y2[ch] = 0.0;
            steephpf_x1[ch] = steephpf_x2[ch] = steephpf_y1[ch] = steephpf_y2[ch] = 0.0;
            gentlelpf_x1[ch] = gentlelpf_y1[ch] = 0.0;
        }
    }
    
    double processEnhancedSSLChain(double input, int channel)
    {
        double signal = input;
        
        // 1. Steep High Pass Filter (12dB/oct @ 100Hz) - if enabled
        if (steepHpfEnable)
        {
            signal = processBiquad(signal, channel,
                                   steephpf_b0[channel], steephpf_b1[channel], steephpf_b2[channel],
                                   steephpf_a1[channel], steephpf_a2[channel],
                                   steephpf_x1[channel], steephpf_x2[channel], steephpf_y1[channel], steephpf_y2[channel]);
        }
        
        // 2. Original High Pass Filter
        signal = processBiquad(signal, channel,
                               hpf_b0[channel], hpf_b1[channel], hpf_b2[channel],
                               hpf_a1[channel], hpf_a2[channel],
                               hpf_x1[channel], hpf_x2[channel], hpf_y1[channel], hpf_y2[channel]);
        
        // 3. Low Frequency (shelf or bell)
        signal = processBiquad(signal, channel,
                               lf_b0[channel], lf_b1[channel], lf_b2[channel],
                               lf_a1[channel], lf_a2[channel],
                               lf_x1[channel], lf_x2[channel], lf_y1[channel], lf_y2[channel]);
        
        // 4. Low-Mid Frequency (parametric)
        signal = processBiquad(signal, channel,
                               lmf_b0[channel], lmf_b1[channel], lmf_b2[channel],
                               lmf_a1[channel], lmf_a2[channel],
                               lmf_x1[channel], lmf_x2[channel], lmf_y1[channel], lmf_y2[channel]);
        
        // 5. Mid Bump (750Hz +1.2dB Q=1.0) - if enabled
        if (midBumpEnable)
        {
            signal = processBiquad(signal, channel,
                                   midbump_b0[channel], midbump_b1[channel], midbump_b2[channel],
                                   midbump_a1[channel], midbump_a2[channel],
                                   midbump_x1[channel], midbump_x2[channel], midbump_y1[channel], midbump_y2[channel]);
        }
        
        // 6. High-Mid Frequency (parametric)
        signal = processBiquad(signal, channel,
                               hmf_b0[channel], hmf_b1[channel], hmf_b2[channel],
                               hmf_a1[channel], hmf_a2[channel],
                               hmf_x1[channel], hmf_x2[channel], hmf_y1[channel], hmf_y2[channel]);
        
        // 7. High Frequency (shelf or bell)
        signal = processBiquad(signal, channel,
                               hf_b0[channel], hf_b1[channel], hf_b2[channel],
                               hf_a1[channel], hf_a2[channel],
                               hf_x1[channel], hf_x2[channel], hf_y1[channel], hf_y2[channel]);
        
        // 8. Original Low Pass Filter
        signal = processBiquad(signal, channel,
                               lpf_b0[channel], lpf_b1[channel], lpf_b2[channel],
                               lpf_a1[channel], lpf_a2[channel],
                               lpf_x1[channel], lpf_x2[channel], lpf_y1[channel], lpf_y2[channel]);
        
        // 9. Gentle Low Pass Filter (6dB/oct @ 13kHz) - if enabled
        if (gentleLpfEnable)
        {
            signal = processFirstOrder(signal, channel,
                                       gentlelpf_b0[channel], gentlelpf_b1[channel],
                                       gentlelpf_a1[channel],
                                       gentlelpf_x1[channel], gentlelpf_y1[channel]);
        }
        
        return signal;
    }
    
    // Standard biquad processing (2nd order)
    double processBiquad(double input, int channel,
                         double b0, double b1, double b2, double a1, double a2,
                         double& x1, double& x2, double& y1, double& y2)
    {
        double output = b0 * input + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2;
        x2 = x1; x1 = input;
        y2 = y1; y1 = output;
        return output;
    }
    
    // First order filter processing (6dB/oct)
    double processFirstOrder(double input, int channel,
                             double b0, double b1, double a1,
                             double& x1, double& y1)
    {
        double output = b0 * input + b1 * x1 - a1 * y1;
        x1 = input;
        y1 = output;
        return output;
    }
    
    void updateAllCoefficients()
    {
        for (int ch = 0; ch < 2; ++ch)
        {
            // Original SSL EQ coefficients
            calculateHighpassCoefficients(hpfFreq, hpf_b0[ch], hpf_b1[ch], hpf_b2[ch], hpf_a1[ch], hpf_a2[ch]);
            
            if (lfBell)
                calculatePeakCoefficients(lfFreq, lfGain, 0.8, lf_b0[ch], lf_b1[ch], lf_b2[ch], lf_a1[ch], lf_a2[ch]);
            else
                calculateShelfCoefficients(lfFreq, lfGain, true, lf_b0[ch], lf_b1[ch], lf_b2[ch], lf_a1[ch], lf_a2[ch]);
            
            calculatePeakCoefficients(lmfFreq, lmfGain, lmfQ, lmf_b0[ch], lmf_b1[ch], lmf_b2[ch], lmf_a1[ch], lmf_a2[ch]);
            calculatePeakCoefficients(hmfFreq, hmfGain, hmfQ, hmf_b0[ch], hmf_b1[ch], hmf_b2[ch], hmf_a1[ch], hmf_a2[ch]);
            
            if (hfBell)
                calculatePeakCoefficients(hfFreq, hfGain, 0.8, hf_b0[ch], hf_b1[ch], hf_b2[ch], hf_a1[ch], hf_a2[ch]);
            else
                calculateShelfCoefficients(hfFreq, hfGain, false, hf_b0[ch], hf_b1[ch], hf_b2[ch], hf_a1[ch], hf_a2[ch]);
            
            calculateLowpassCoefficients(lpfFreq, lpf_b0[ch], lpf_b1[ch], lpf_b2[ch], lpf_a1[ch], lpf_a2[ch]);
            
            // New filter coefficients
            // Mid bump: Fixed 750Hz, variable gain, Q=1.0
            calculatePeakCoefficients(750.0, midBumpGain, 1.0,
                                      midbump_b0[ch], midbump_b1[ch], midbump_b2[ch],
                                      midbump_a1[ch], midbump_a2[ch]);
            
            // Steep HPF: 12dB/oct (cascade two 2nd-order Butterworth for steeper roll-off)
            calculateSteepHighpassCoefficients(steepHpfFreq,
                                               steephpf_b0[ch], steephpf_b1[ch], steephpf_b2[ch],
                                               steephpf_a1[ch], steephpf_a2[ch]);
            
            // Gentle LPF: 6dB/oct (1st order)
            calculateFirstOrderLowpassCoefficients(gentleLpfFreq,
                                                   gentlelpf_b0[ch], gentlelpf_b1[ch],
                                                   gentlelpf_a1[ch]);
        }
    }
    
    // Original coefficient calculation methods (keeping them as they were)
    void calculateHighpassCoefficients(double freq, double& b0, double& b1, double& b2, double& a1, double& a2)
    {
        double omega = 2.0 * M_PI * freq / sampleRate;
        double cosw = cos(omega);
        double sinw = sin(omega);
        double alpha = sinw / sqrt(2.0); // Q = 1/sqrt(2) for Butterworth
        
        double b0_temp = (1 + cosw) / 2;
        double b1_temp = -(1 + cosw);
        double b2_temp = (1 + cosw) / 2;
        double a0_temp = 1 + alpha;
        double a1_temp = -2 * cosw;
        double a2_temp = 1 - alpha;
        
        b0 = b0_temp / a0_temp;
        b1 = b1_temp / a0_temp;
        b2 = b2_temp / a0_temp;
        a1 = a1_temp / a0_temp;
        a2 = a2_temp / a0_temp;
    }
    
    void calculateLowpassCoefficients(double freq, double& b0, double& b1, double& b2, double& a1, double& a2)
    {
        double omega = 2.0 * M_PI * freq / sampleRate;
        double cosw = cos(omega);
        double sinw = sin(omega);
        double alpha = sinw / sqrt(2.0); // Q = 1/sqrt(2) for Butterworth
        
        double b0_temp = (1 - cosw) / 2;
        double b1_temp = 1 - cosw;
        double b2_temp = (1 - cosw) / 2;
        double a0_temp = 1 + alpha;
        double a1_temp = -2 * cosw;
        double a2_temp = 1 - alpha;
        
        b0 = b0_temp / a0_temp;
        b1 = b1_temp / a0_temp;
        b2 = b2_temp / a0_temp;
        a1 = a1_temp / a0_temp;
        a2 = a2_temp / a0_temp;
    }
    
    void calculateShelfCoefficients(double freq, double gain_dB, bool isLowShelf,
                                    double& b0, double& b1, double& b2, double& a1, double& a2)
    {
        if (abs(gain_dB) < 0.01)
        {
            b0 = 1.0; b1 = 0.0; b2 = 0.0; a1 = 0.0; a2 = 0.0;
            return;
        }
        
        double omega = 2.0 * M_PI * freq / sampleRate;
        double cosw = cos(omega);
        double sinw = sin(omega);
        double A = pow(10.0, gain_dB / 40.0);
        double beta = sqrt(A) / 1.0; // Q = 1
        
        double b0_temp, b1_temp, b2_temp, a0_temp, a1_temp, a2_temp;
        
        if (isLowShelf)
        {
            b0_temp = A * ((A + 1) - (A - 1) * cosw + beta * sinw);
            b1_temp = 2 * A * ((A - 1) - (A + 1) * cosw);
            b2_temp = A * ((A + 1) - (A - 1) * cosw - beta * sinw);
            a0_temp = (A + 1) + (A - 1) * cosw + beta * sinw;
            a1_temp = -2 * ((A - 1) + (A + 1) * cosw);
            a2_temp = (A + 1) + (A - 1) * cosw - beta * sinw;
        }
        else
        {
            b0_temp = A * ((A + 1) + (A - 1) * cosw + beta * sinw);
            b1_temp = -2 * A * ((A - 1) + (A + 1) * cosw);
            b2_temp = A * ((A + 1) + (A - 1) * cosw - beta * sinw);
            a0_temp = (A + 1) - (A - 1) * cosw + beta * sinw;
            a1_temp = 2 * ((A - 1) - (A + 1) * cosw);
            a2_temp = (A + 1) - (A - 1) * cosw - beta * sinw;
        }
        
        b0 = b0_temp / a0_temp;
        b1 = b1_temp / a0_temp;
        b2 = b2_temp / a0_temp;
        a1 = a1_temp / a0_temp;
        a2 = a2_temp / a0_temp;
    }
    
    void calculatePeakCoefficients(double freq, double gain_dB, double Q,
                                   double& b0, double& b1, double& b2, double& a1, double& a2)
    {
        if (abs(gain_dB) < 0.01)
        {
            b0 = 1.0; b1 = 0.0; b2 = 0.0; a1 = 0.0; a2 = 0.0;
            return;
        }
        
        double omega = 2.0 * M_PI * freq / sampleRate;
        double cosw = cos(omega);
        double sinw = sin(omega);
        double A = pow(10.0, gain_dB / 40.0);
        double alpha = sinw / (2.0 * Q);
        
        double b0_temp = 1 + alpha * A;
        double b1_temp = -2 * cosw;
        double b2_temp = 1 - alpha * A;
        double a0_temp = 1 + alpha / A;
        double a1_temp = -2 * cosw;
        double a2_temp = 1 - alpha / A;
        
        b0 = b0_temp / a0_temp;
        b1 = b1_temp / a0_temp;
        b2 = b2_temp / a0_temp;
        a1 = a1_temp / a0_temp;
        a2 = a2_temp / a0_temp;
    }
    
    // NEW FILTER COEFFICIENT CALCULATIONS ------------------------------------------------
    
    // Steeper high-pass: 12dB/oct using higher Q for sharper cutoff
    void calculateSteepHighpassCoefficients(double freq, double& b0, double& b1, double& b2, double& a1, double& a2)
    {
        double omega = 2.0 * M_PI * freq / sampleRate;
        double cosw = cos(omega);
        double sinw = sin(omega);
        double Q = 1.414; // Higher Q for steeper roll-off (12dB/oct characteristic)
        double alpha = sinw / (2.0 * Q);
        
        double b0_temp = (1 + cosw) / 2;
        double b1_temp = -(1 + cosw);
        double b2_temp = (1 + cosw) / 2;
        double a0_temp = 1 + alpha;
        double a1_temp = -2 * cosw;
        double a2_temp = 1 - alpha;
        
        b0 = b0_temp / a0_temp;
        b1 = b1_temp / a0_temp;
        b2 = b2_temp / a0_temp;
        a1 = a1_temp / a0_temp;
        a2 = a2_temp / a0_temp;
    }
    
    // First-order low-pass: 6dB/oct gentle slope
    void calculateFirstOrderLowpassCoefficients(double freq, double& b0, double& b1, double& a1)
    {
        double omega = 2.0 * M_PI * freq / sampleRate;
        double k = tan(omega / 2.0);
        double norm = 1.0 / (1.0 + k);
        
        b0 = k * norm;
        b1 = k * norm;
        a1 = (k - 1.0) * norm;
    }
};
}

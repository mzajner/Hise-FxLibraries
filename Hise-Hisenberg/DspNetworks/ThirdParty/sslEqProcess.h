#pragma once
#include <JuceHeader.h>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV> struct sslEqProcess: public data::base
{
    SNEX_NODE(sslEqProcess);
    
    struct MetadataClass
    {
        SN_NODE_ID("sslEqProcess");
    };
    
    static constexpr bool isModNode() { return false; };
    static constexpr bool isPolyphonic() { return NV > 1; };
    static constexpr bool hasTail() { return false; };
    static constexpr bool isSuspendedOnSilence() { return false; };
    static constexpr int getFixChannelAmount() { return 2; };
    
    static constexpr int NumTables = 0;
    static constexpr int NumSliderPacks = 0;
    static constexpr int NumAudioFiles = 0;
    static constexpr int NumFilters = 0;
    static constexpr int NumDisplayBuffers = 0;
    
    sslEqProcess()
    {
        resetAllStates();
        processAmount = 0.0;
        shapeIndex = 0.0;
        
        enableMidBump = true;
        enableSteepHpf = true;
        enableGentleLpf = true;
        
        bypass = false;
        sampleRate = 48000.0;
        updateEnhancedSnareEQSettings();
    }
    
    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;
        updateEnhancedSnareEQSettings();
    }
    
    void reset()
    {
        resetAllStates();
    }
    
    void handleHiseEvent(HiseEvent& e) {}
    
    template <typename T> void process(T& data)
    {
        static constexpr int NumChannels = getFixChannelAmount();
        auto& fixData = data.template as<ProcessData<NumChannels>>();
        auto fd = fixData.toFrameData();
        
        while(fd.next())
        {
            processFrame(fd.toSpan());
        }
    }
    
    template <typename T> void processFrame(T& data)
    {
        if (bypass || processAmount <= 0.0)
            return;
        
        double signal = data[0];
        signal = processEnhancedSSLChain(signal, 0);
        data[0] = signal;
        
        signal = data[1];
        signal = processEnhancedSSLChain(signal, 1);
        data[1] = signal;
    }
    
    int handleModulation(double& value) { return 0; }
    void setExternalData(const ExternalData& data, int index) {}
    
    template <int P> void setParameter(double v)
    {
        if (P == 0)
        {
            processAmount = v;
            updateEnhancedSnareEQSettings();
        }
        else if (P == 1)
        {
            shapeIndex = v;
            updateEnhancedSnareEQSettings();
        }
        else if (P == 2)
        {
            bypass = v >= 0.5;
        }
        else if (P == 3)
        {
            enableMidBump = v >= 0.5;
            updateEnhancedSnareEQSettings();
        }
        else if (P == 4)
        {
            enableSteepHpf = v >= 0.5;
            updateEnhancedSnareEQSettings();
        }
        else if (P == 5)
        {
            enableGentleLpf = v >= 0.5;
            updateEnhancedSnareEQSettings();
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("Process", { 0.0, 100.0, 0.1 });
            registerCallback<0>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Shape", { 0.0, 3.0, 1.0 });
            registerCallback<1>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Bypass", { 0.0, 1.0, 1.0 });
            registerCallback<2>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("MidBump Enable", { 0.0, 1.0, 1.0 });
            registerCallback<3>(p);
            p.setDefaultValue(1.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("HPF Enable", { 0.0, 1.0, 1.0 });
            registerCallback<4>(p);
            p.setDefaultValue(1.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("LPF", { 0.0, 1.0, 1.0 });
            registerCallback<5>(p);
            p.setDefaultValue(1.0);
            data.add(std::move(p));
        }
    }
    
private:
    double sampleRate;
    double processAmount;
    double shapeIndex;
    bool bypass;
    bool enableMidBump, enableSteepHpf, enableGentleLpf;
    
    // Current computed values based on shape and process amount
    double currentHpfFreq, currentLfGain, currentLmfGain, currentHmfGain, currentHfGain, currentLpfFreq;
    double currentMidBumpGain, currentSteepHpfFreq, currentGentleLpfFreq;
    
    // Shape-specific curve definitions
    struct ShapeSettings
    {
        double hpfMin, hpfMax;
        double lfFreq, lfMaxGain;
        double lmfFreq, lmfMaxGain, lmfQ;
        double hmfFreq, hmfMaxGain, hmfQ;
        double hfFreq, hfMaxGain;
        double lpfMin, lpfMax;
    };
    
    ShapeSettings getShapeSettings(int shape)
    {
        ShapeSettings shapes[4] = {
            // Shape 0: Original enhanced snare curve
            { 60.0, 120.0, 200.0, 3.0, 350.0, -4.0, 1.2, 1000.0, -3.0, 0.8, 8000.0, 4.0, 18000.0, 15000.0 },
            
            // Shape 1: Guitar/Modern midrange heavy
            { 80.0, 80.0, 110.0, 2.0, 890.0, -3.0, 2.5, 3000.0, -2.0, 2.0, 8200.0, 1.5, 10000.0, 10000.0 },
            
            // Shape 2: Kick/Bass heavy
            { 20.0, 20.0, 62.0, 2.5, 315.0, -2.5, 1.5, 800.0, -2.0, 2.5, 6600.0, 2.0, 8500.0, 8500.0 },
            
            // Shape 3: Alternate snare - pronounced midrange
            { 110.0, 110.0, 180.0, 1.5, 910.0, 2.0, 1.0, 2700.0, 1.5, 1.0, 6600.0, 1.5, 15000.0, 15000.0 }
        };
        
        return shapes[shape];
    }
    
    // Enhanced SSL EQ frequencies (for mid bump and additional filters - unchanged from original)
    static constexpr double MID_BUMP_FREQ = 750.0;
    static constexpr double MID_BUMP_Q = 1.0;
    static constexpr double STEEP_HPF_FREQ = 100.0;
    static constexpr double GENTLE_LPF_FREQ = 13000.0;
    static constexpr double MAX_MID_BUMP_GAIN = 1.2;
    
    // Filter coefficients [channel]
    double hpf_b0[2], hpf_b1[2], hpf_b2[2], hpf_a1[2], hpf_a2[2];
    double lf_b0[2], lf_b1[2], lf_b2[2], lf_a1[2], lf_a2[2];
    double lmf_b0[2], lmf_b1[2], lmf_b2[2], lmf_a1[2], lmf_a2[2];
    double hmf_b0[2], hmf_b1[2], hmf_b2[2], hmf_a1[2], hmf_a2[2];
    double hf_b0[2], hf_b1[2], hf_b2[2], hf_a1[2], hf_a2[2];
    double lpf_b0[2], lpf_b1[2], lpf_b2[2], lpf_a1[2], lpf_a2[2];
    
    // New enhanced filter coefficients
    double midbump_b0[2], midbump_b1[2], midbump_b2[2], midbump_a1[2], midbump_a2[2];
    double steephpf_b0[2], steephpf_b1[2], steephpf_b2[2], steephpf_a1[2], steephpf_a2[2];
    double gentlelpf_b0[2], gentlelpf_b1[2], gentlelpf_a1[2];
    
    // Filter states [channel]
    double hpf_x1[2], hpf_x2[2], hpf_y1[2], hpf_y2[2];
    double lf_x1[2], lf_x2[2], lf_y1[2], lf_y2[2];
    double lmf_x1[2], lmf_x2[2], lmf_y1[2], lmf_y2[2];
    double hmf_x1[2], hmf_x2[2], hmf_y1[2], hmf_y2[2];
    double hf_x1[2], hf_x2[2], hf_y1[2], hf_y2[2];
    double lpf_x1[2], lpf_x2[2], lpf_y1[2], lpf_y2[2];
    
    // New enhanced filter states
    double midbump_x1[2], midbump_x2[2], midbump_y1[2], midbump_y2[2];
    double steephpf_x1[2], steephpf_x2[2], steephpf_y1[2], steephpf_y2[2];
    double gentlelpf_x1[2], gentlelpf_y1[2];
    
    void resetAllStates()
    {
        for (int ch = 0; ch < 2; ++ch)
        {
            hpf_x1[ch] = hpf_x2[ch] = hpf_y1[ch] = hpf_y2[ch] = 0.0;
            lf_x1[ch] = lf_x2[ch] = lf_y1[ch] = lf_y2[ch] = 0.0;
            lmf_x1[ch] = lmf_x2[ch] = lmf_y1[ch] = lmf_y2[ch] = 0.0;
            hmf_x1[ch] = hmf_x2[ch] = hmf_y1[ch] = hmf_y2[ch] = 0.0;
            hf_x1[ch] = hf_x2[ch] = hf_y1[ch] = hf_y2[ch] = 0.0;
            lpf_x1[ch] = lpf_x2[ch] = lpf_y1[ch] = lpf_y2[ch] = 0.0;
            
            midbump_x1[ch] = midbump_x2[ch] = midbump_y1[ch] = midbump_y2[ch] = 0.0;
            steephpf_x1[ch] = steephpf_x2[ch] = steephpf_y1[ch] = steephpf_y2[ch] = 0.0;
            gentlelpf_x1[ch] = gentlelpf_y1[ch] = 0.0;
        }
    }
    
    double processEnhancedSSLChain(double input, int channel)
    {
        double signal = input;
        
        // 1. Steep High-Pass Filter (12dB/oct @ 100Hz) - if enabled
        if (enableSteepHpf && processAmount > 0.0)
        {
            signal = processBiquad(signal, channel,
                                   steephpf_b0[channel], steephpf_b1[channel], steephpf_b2[channel],
                                   steephpf_a1[channel], steephpf_a2[channel],
                                   steephpf_x1[channel], steephpf_x2[channel],
                                   steephpf_y1[channel], steephpf_y2[channel]);
        }
        
        // 2. Original High-Pass Filter (variable frequency based on shape)
        signal = processBiquad(signal, channel,
                               hpf_b0[channel], hpf_b1[channel], hpf_b2[channel],
                               hpf_a1[channel], hpf_a2[channel],
                               hpf_x1[channel], hpf_x2[channel],
                               hpf_y1[channel], hpf_y2[channel]);
        
        // 3. Low Frequency Shelf
        signal = processBiquad(signal, channel,
                               lf_b0[channel], lf_b1[channel], lf_b2[channel],
                               lf_a1[channel], lf_a2[channel],
                               lf_x1[channel], lf_x2[channel],
                               lf_y1[channel], lf_y2[channel]);
        
        // 4. Low-Mid Frequency Cut/Boost
        signal = processBiquad(signal, channel,
                               lmf_b0[channel], lmf_b1[channel], lmf_b2[channel],
                               lmf_a1[channel], lmf_a2[channel],
                               lmf_x1[channel], lmf_x2[channel],
                               lmf_y1[channel], lmf_y2[channel]);
        
        // 5. Mid Bump @ 750Hz - if enabled
        if (enableMidBump && processAmount > 0.0)
        {
            signal = processBiquad(signal, channel,
                                   midbump_b0[channel], midbump_b1[channel], midbump_b2[channel],
                                   midbump_a1[channel], midbump_a2[channel],
                                   midbump_x1[channel], midbump_x2[channel],
                                   midbump_y1[channel], midbump_y2[channel]);
        }
        
        // 6. High-Mid Frequency Cut/Boost
        signal = processBiquad(signal, channel,
                               hmf_b0[channel], hmf_b1[channel], hmf_b2[channel],
                               hmf_a1[channel], hmf_a2[channel],
                               hmf_x1[channel], hmf_x2[channel],
                               hmf_y1[channel], hmf_y2[channel]);
        
        // 7. High Frequency Shelf
        signal = processBiquad(signal, channel,
                               hf_b0[channel], hf_b1[channel], hf_b2[channel],
                               hf_a1[channel], hf_a2[channel],
                               hf_x1[channel], hf_x2[channel],
                               hf_y1[channel], hf_y2[channel]);
        
        // 8. Original Low-Pass Filter (variable frequency based on shape)
        signal = processBiquad(signal, channel,
                               lpf_b0[channel], lpf_b1[channel], lpf_b2[channel],
                               lpf_a1[channel], lpf_a2[channel],
                               lpf_x1[channel], lpf_x2[channel],
                               lpf_y1[channel], lpf_y2[channel]);
        
        // 9. Gentle Low-Pass Filter (6dB/oct @ 13kHz) - if enabled
        if (enableGentleLpf && processAmount > 0.0)
        {
            signal = processFirstOrder(signal, channel,
                                       gentlelpf_b0[channel], gentlelpf_b1[channel],
                                       gentlelpf_a1[channel],
                                       gentlelpf_x1[channel], gentlelpf_y1[channel]);
        }
        
        return signal;
    }
    
    double processBiquad(double input, int channel,
                         double b0, double b1, double b2, double a1, double a2,
                         double& x1, double& x2, double& y1, double& y2)
    {
        double output = b0 * input + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2;
        x2 = x1; x1 = input;
        y2 = y1; y1 = output;
        return output;
    }
    
    double processFirstOrder(double input, int channel,
                             double b0, double b1, double a1,
                             double& x1, double& y1)
    {
        double output = b0 * input + b1 * x1 - a1 * y1;
        x1 = input;
        y1 = output;
        return output;
    }
    
    void updateEnhancedSnareEQSettings()
    {
        // Get current shape settings
        int currentShape = jmax(0, jmin(3, static_cast<int>(shapeIndex)));
        ShapeSettings shape = getShapeSettings(currentShape);
        
        // Apply original scaling patterns from your working code, but DOUBLED
        double normalizedProcess = processAmount / 100.0;
        double processSquared = normalizedProcess * normalizedProcess;
        double processCubed = processSquared * normalizedProcess;
        
        // Apply doubled effectiveness to original scaling patterns
        currentHpfFreq = shape.hpfMin + (shape.hpfMax - shape.hpfMin) * normalizedProcess;
        currentLpfFreq = shape.lpfMin - (shape.lpfMin - shape.lpfMax) * normalizedProcess;
        currentLfGain = shape.lfMaxGain * processSquared * 2.0;      // DOUBLED
        currentLmfGain = shape.lmfMaxGain * normalizedProcess * 2.0; // DOUBLED
        currentHmfGain = shape.hmfMaxGain * normalizedProcess * 2.0; // DOUBLED
        currentHfGain = shape.hfMaxGain * processCubed * 2.0;        // DOUBLED
        
        // New filter processing amounts (same as original)
        currentMidBumpGain = MAX_MID_BUMP_GAIN * normalizedProcess * 2.0; // DOUBLED
        currentSteepHpfFreq = STEEP_HPF_FREQ;
        currentGentleLpfFreq = GENTLE_LPF_FREQ;
        
        for (int ch = 0; ch < 2; ++ch)
        {
            // Original SSL filters with shape-specific frequencies and Q values
            calculateHighPassCoefficients(currentHpfFreq, 0.707,
                                          hpf_b0[ch], hpf_b1[ch], hpf_b2[ch], hpf_a1[ch], hpf_a2[ch]);
            
            calculateShelfCoefficients(shape.lfFreq, currentLfGain, true,
                                       lf_b0[ch], lf_b1[ch], lf_b2[ch], lf_a1[ch], lf_a2[ch]);
            
            calculatePeakCoefficients(shape.lmfFreq, currentLmfGain, shape.lmfQ,
                                      lmf_b0[ch], lmf_b1[ch], lmf_b2[ch], lmf_a1[ch], lmf_a2[ch]);
            
            calculatePeakCoefficients(shape.hmfFreq, currentHmfGain, shape.hmfQ,
                                      hmf_b0[ch], hmf_b1[ch], hmf_b2[ch], hmf_a1[ch], hmf_a2[ch]);
            
            calculateShelfCoefficients(shape.hfFreq, currentHfGain, false,
                                       hf_b0[ch], hf_b1[ch], hf_b2[ch], hf_a1[ch], hf_a2[ch]);
            
            calculateLowPassCoefficients(currentLpfFreq, 0.707,
                                         lpf_b0[ch], lpf_b1[ch], lpf_b2[ch], lpf_a1[ch], lpf_a2[ch]);
            
            // Enhanced filters (unchanged from original)
            calculatePeakCoefficients(MID_BUMP_FREQ, currentMidBumpGain, MID_BUMP_Q,
                                      midbump_b0[ch], midbump_b1[ch], midbump_b2[ch],
                                      midbump_a1[ch], midbump_a2[ch]);
            
            calculateSteepHighpassCoefficients(currentSteepHpfFreq,
                                               steephpf_b0[ch], steephpf_b1[ch], steephpf_b2[ch],
                                               steephpf_a1[ch], steephpf_a2[ch]);
            
            calculateFirstOrderLowpassCoefficients(currentGentleLpfFreq,
                                                   gentlelpf_b0[ch], gentlelpf_b1[ch], gentlelpf_a1[ch]);
        }
    }
    
    // All coefficient calculation functions (unchanged from original)
    void calculateHighPassCoefficients(double freq, double Q, double& b0, double& b1, double& b2, double& a1, double& a2)
    {
        double omega = 2.0 * M_PI * freq / sampleRate;
        double cosw = std::cos(omega);
        double sinw = std::sin(omega);
        double alpha = sinw / (2.0 * Q);
        
        double b0_temp = (1.0 + cosw) / 2.0;
        double b1_temp = -(1.0 + cosw);
        double b2_temp = (1.0 + cosw) / 2.0;
        double a0_temp = 1.0 + alpha;
        double a1_temp = -2.0 * cosw;
        double a2_temp = 1.0 - alpha;
        
        b0 = b0_temp / a0_temp;  // Fixed: was missing "b0 ="
        b1 = b1_temp / a0_temp;
        b2 = b2_temp / a0_temp;
        a1 = a1_temp / a0_temp;
        a2 = a2_temp / a0_temp;
    }
    
    void calculateLowPassCoefficients(double freq, double Q, double& b0, double& b1, double& b2, double& a1, double& a2)
    {
        double omega = 2.0 * M_PI * freq / sampleRate;
        double cosw = std::cos(omega);
        double sinw = std::sin(omega);
        double alpha = sinw / (2.0 * Q);
        
        double b0_temp = (1.0 - cosw) / 2.0;
        double b1_temp = 1.0 - cosw;
        double b2_temp = (1.0 - cosw) / 2.0;
        double a0_temp = 1.0 + alpha;
        double a1_temp = -2.0 * cosw;
        double a2_temp = 1.0 - alpha;
        
        b0 = b0_temp / a0_temp;
        b1 = b1_temp / a0_temp;
        b2 = b2_temp / a0_temp;
        a1 = a1_temp / a0_temp;
        a2 = a2_temp / a0_temp;
    }
    
    void calculateShelfCoefficients(double freq, double gain_dB, bool isLowShelf, double& b0, double& b1, double& b2, double& a1, double& a2)
    {
        double omega = 2.0 * M_PI * freq / sampleRate;
        double cosw = std::cos(omega);
        double sinw = std::sin(omega);
        double A = std::pow(10.0, gain_dB / 40.0);
        double beta = std::sqrt(A);
        
        if (isLowShelf)
        {
            double b0_temp = A * ((A + 1.0) - (A - 1.0) * cosw + beta * sinw);
            double b1_temp = 2.0 * A * ((A - 1.0) - (A + 1.0) * cosw);
            double b2_temp = A * ((A + 1.0) - (A - 1.0) * cosw - beta * sinw);
            double a0_temp = (A + 1.0) + (A - 1.0) * cosw + beta * sinw;
            double a1_temp = -2.0 * ((A - 1.0) + (A + 1.0) * cosw);
            double a2_temp = (A + 1.0) + (A - 1.0) * cosw - beta * sinw;
            
            b0 = b0_temp / a0_temp;
            b1 = b1_temp / a0_temp;
            b2 = b2_temp / a0_temp;
            a1 = a1_temp / a0_temp;
            a2 = a2_temp / a0_temp;
        }
        else
        {
            double b0_temp = A * ((A + 1.0) + (A - 1.0) * cosw + beta * sinw);
            double b1_temp = -2.0 * A * ((A - 1.0) + (A + 1.0) * cosw);
            double b2_temp = A * ((A + 1.0) + (A - 1.0) * cosw - beta * sinw);
            double a0_temp = (A + 1.0) - (A - 1.0) * cosw + beta * sinw;
            double a1_temp = 2.0 * ((A - 1.0) - (A + 1.0) * cosw);
            double a2_temp = (A + 1.0) - (A - 1.0) * cosw - beta * sinw;
            
            b0 = b0_temp / a0_temp;
            b1 = b1_temp / a0_temp;
            b2 = b2_temp / a0_temp;
            a1 = a1_temp / a0_temp;
            a2 = a2_temp / a0_temp;
        }
    }
    
    void calculatePeakCoefficients(double freq, double gain_dB, double Q, double& b0, double& b1, double& b2, double& a1, double& a2)
    {
        double omega = 2.0 * M_PI * freq / sampleRate;
        double cosw = std::cos(omega);
        double sinw = std::sin(omega);
        double A = std::pow(10.0, gain_dB / 40.0);
        double alpha = sinw / (2.0 * Q);
        
        double b0_temp = 1.0 + alpha * A;
        double b1_temp = -2.0 * cosw;
        double b2_temp = 1.0 - alpha * A;
        double a0_temp = 1.0 + alpha / A;
        double a1_temp = -2.0 * cosw;
        double a2_temp = 1.0 - alpha / A;
        
        b0 = b0_temp / a0_temp;
        b1 = b1_temp / a0_temp;
        b2 = b2_temp / a0_temp;
        a1 = a1_temp / a0_temp;
        a2 = a2_temp / a0_temp;
    }
    
    void calculateSteepHighpassCoefficients(double freq, double& b0, double& b1, double& b2, double& a1, double& a2)
    {
        double omega = 2.0 * M_PI * freq / sampleRate;
        double cosw = std::cos(omega);
        double sinw = std::sin(omega);
        double Q = 1.414;
        double alpha = sinw / (2.0 * Q);
        
        double b0_temp = (1.0 + cosw) / 2.0;
        double b1_temp = -(1.0 + cosw);
        double b2_temp = (1.0 + cosw) / 2.0;
        double a0_temp = 1.0 + alpha;
        double a1_temp = -2.0 * cosw;
        double a2_temp = 1.0 - alpha;
        
        b0 = b0_temp / a0_temp;
        b1 = b1_temp / a0_temp;
        b2 = b2_temp / a0_temp;
        a1 = a1_temp / a0_temp;
        a2 = a2_temp / a0_temp;
    }
    
    void calculateFirstOrderLowpassCoefficients(double freq, double& b0, double& b1, double& a1)
    {
        double omega = 2.0 * M_PI * freq / sampleRate;
        double k = std::tan(omega / 2.0);
        double norm = 1.0 / (1.0 + k);
        
        b0 = k * norm;
        b1 = k * norm;
        a1 = (k - 1.0) * norm;
    }
};
}

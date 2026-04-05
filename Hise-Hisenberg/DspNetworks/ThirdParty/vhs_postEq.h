// ==================================| VHS Post-EQ - Single Character Knob |==================================

#pragma once
#include <JuceHeader.h>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV> struct vhs_postEq: public data::base
{
    // Metadata Definitions ------------------------------------------------------------------------
    
    SNEX_NODE(vhs_postEq);
    
    struct MetadataClass
    {
        SN_NODE_ID("vhs_postEq");
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
    
    // Constructor
    vhs_postEq()
    {
        sampleRate = 48000.0;
        characterAmount = 0.0;
        bypass = false;
        
        resetAllStates();
        updateCharacterSettings();
    }
    
    // Scriptnode Callbacks ------------------------------------------------------------------------
    
    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;
        updateCharacterSettings();
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
        auto& fixData = data.template as<ProcessData<NumChannels>>();
        auto fd = fixData.toFrameData();
        
        while(fd.next())
        {
            processFrame(fd.toSpan());
        }
    }
    
    template <typename T> void processFrame(T& data)
    {
        if (bypass || characterAmount <= 0.0)
            return;
        
        // Process left channel through character EQ chain
        double signal = data[0];
        signal = processCharacterChain(signal, 0);
        data[0] = signal;
        
        // Process right channel through character EQ chain
        signal = data[1];
        signal = processCharacterChain(signal, 1);
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
        if (P == 0)
        {
            // Character amount: 0.0 = flat, 1.0 = full 80s VHS character
            characterAmount = jlimit(0.0, 1.0, v);
            updateCharacterSettings();
        }
        else if (P == 1)
        {
            bypass = v >= 0.5;
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("Character", { 0.0, 1.0, 0.01 });
            registerCallback<0>(p);
            p.setDefaultValue(0.5); // 50% character by default
            data.add(std::move(p));
        }
        {
            parameter::data p("Bypass", { 0.0, 1.0, 1.0 });
            registerCallback<1>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
    }
    
private:
    double sampleRate;
    double characterAmount;
    bool bypass;
    
    // Current EQ settings calculated from character amount
    double currentWarmthGain;     // 650 Hz boost for body/warmth
    double currentPresenceGain;   // 3.5 kHz boost for vocal presence
    double currentAirGain;        // 10 kHz shelf for air/sparkle
    double currentTiltGain;       // 1 kHz tilt for vintage character
    
    // EQ Frequency definitions based on research
    static constexpr double WARMTH_FREQ = 650.0;      // Body/warmth frequency
    static constexpr double PRESENCE_FREQ = 3500.0;   // Vocal presence frequency
    static constexpr double AIR_FREQ = 10000.0;       // Air/sparkle frequency
    static constexpr double TILT_FREQ = 1000.0;       // Tilt pivot frequency
    
    // Character curve parameters
    static constexpr double MAX_WARMTH_GAIN = 3.0;    // +3dB max warmth
    static constexpr double MAX_PRESENCE_GAIN = 6.0;  // +6dB max presence
    static constexpr double MAX_AIR_GAIN = 4.0;       // +4dB max air
    static constexpr double MAX_TILT_GAIN = -6.0;     // -6dB max tilt (vintage rolloff)
    
    // Filter coefficients for each band [channel]
    double warmth_b0[2], warmth_b1[2], warmth_b2[2], warmth_a1[2], warmth_a2[2];
    double presence_b0[2], presence_b1[2], presence_b2[2], presence_a1[2], presence_a2[2];
    double air_b0[2], air_b1[2], air_b2[2], air_a1[2], air_a2[2];
    double tilt_b0[2], tilt_b1[2], tilt_b2[2], tilt_a1[2], tilt_a2[2];
    
    // Filter states for each band [channel]
    double warmth_x1[2], warmth_x2[2], warmth_y1[2], warmth_y2[2];
    double presence_x1[2], presence_x2[2], presence_y1[2], presence_y2[2];
    double air_x1[2], air_x2[2], air_y1[2], air_y2[2];
    double tilt_x1[2], tilt_x2[2], tilt_y1[2], tilt_y2[2];
    
    void resetAllStates()
    {
        for (int ch = 0; ch < 2; ++ch)
        {
            warmth_x1[ch] = warmth_x2[ch] = warmth_y1[ch] = warmth_y2[ch] = 0.0;
            presence_x1[ch] = presence_x2[ch] = presence_y1[ch] = presence_y2[ch] = 0.0;
            air_x1[ch] = air_x2[ch] = air_y1[ch] = air_y2[ch] = 0.0;
            tilt_x1[ch] = tilt_x2[ch] = tilt_y1[ch] = tilt_y2[ch] = 0.0;
        }
    }
    
    double processCharacterChain(double input, int channel)
    {
        double signal = input;
        
        // 1. Warmth Band (650 Hz bell filter)
        signal = processBiquad(signal, channel,
                               warmth_b0[channel], warmth_b1[channel], warmth_b2[channel],
                               warmth_a1[channel], warmth_a2[channel],
                               warmth_x1[channel], warmth_x2[channel], warmth_y1[channel], warmth_y2[channel]);
        
        // 2. Presence Band (3.5 kHz bell filter)
        signal = processBiquad(signal, channel,
                               presence_b0[channel], presence_b1[channel], presence_b2[channel],
                               presence_a1[channel], presence_a2[channel],
                               presence_x1[channel], presence_x2[channel], presence_y1[channel], presence_y2[channel]);
        
        // 3. Air Band (10 kHz high shelf)
        signal = processBiquad(signal, channel,
                               air_b0[channel], air_b1[channel], air_b2[channel],
                               air_a1[channel], air_a2[channel],
                               air_x1[channel], air_x2[channel], air_y1[channel], air_y2[channel]);
        
        // 4. Tilt Band (1 kHz tilt for vintage character)
        signal = processBiquad(signal, channel,
                               tilt_b0[channel], tilt_b1[channel], tilt_b2[channel],
                               tilt_a1[channel], tilt_a2[channel],
                               tilt_x1[channel], tilt_x2[channel], tilt_y1[channel], tilt_y2[channel]);
        
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
    
    void updateCharacterSettings()
    {
        // Character curve mapping (0.0 to 1.0)
        double charSquared = characterAmount * characterAmount;
        double charCubed = charSquared * characterAmount;
        
        // Calculate gain values based on character amount
        // Warmth: gentle curve, starts early
        currentWarmthGain = MAX_WARMTH_GAIN * charSquared;
        
        // Presence: most important, linear to squared curve
        currentPresenceGain = MAX_PRESENCE_GAIN * (0.5 * characterAmount + 0.5 * charSquared);
        
        // Air: starts later, more dramatic
        currentAirGain = MAX_AIR_GAIN * charCubed;
        
        // Tilt: vintage character, starts at 50% and increases
        currentTiltGain = (characterAmount > 0.5) ?
        MAX_TILT_GAIN * (characterAmount - 0.5) * 2.0 : 0.0;
        
        // Update all filter coefficients
        for (int ch = 0; ch < 2; ++ch)
        {
            // Warmth band - bell filter at 650 Hz
            calculatePeakCoefficients(WARMTH_FREQ, currentWarmthGain, 1.5,
                                      warmth_b0[ch], warmth_b1[ch], warmth_b2[ch],
                                      warmth_a1[ch], warmth_a2[ch]);
            
            // Presence band - bell filter at 3.5 kHz
            calculatePeakCoefficients(PRESENCE_FREQ, currentPresenceGain, 1.0,
                                      presence_b0[ch], presence_b1[ch], presence_b2[ch],
                                      presence_a1[ch], presence_a2[ch]);
            
            // Air band - high shelf at 10 kHz
            calculateShelfCoefficients(AIR_FREQ, currentAirGain, false,
                                       air_b0[ch], air_b1[ch], air_b2[ch],
                                       air_a1[ch], air_a2[ch]);
            
            // Tilt band - tilt filter at 1 kHz for vintage character
            calculateTiltCoefficients(TILT_FREQ, currentTiltGain,
                                      tilt_b0[ch], tilt_b1[ch], tilt_b2[ch],
                                      tilt_a1[ch], tilt_a2[ch]);
        }
    }
    
    void calculatePeakCoefficients(double freq, double gain_dB, double Q,
                                   double& b0, double& b1, double& b2, double& a1, double& a2)
    {
        if (std::abs(gain_dB) < 0.01)
        {
            // Bypass filter
            b0 = 1.0; b1 = 0.0; b2 = 0.0; a1 = 0.0; a2 = 0.0;
            return;
        }
        
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
    
    void calculateShelfCoefficients(double freq, double gain_dB, bool isLowShelf,
                                    double& b0, double& b1, double& b2, double& a1, double& a2)
    {
        if (std::abs(gain_dB) < 0.01)
        {
            // Bypass filter
            b0 = 1.0; b1 = 0.0; b2 = 0.0; a1 = 0.0; a2 = 0.0;
            return;
        }
        
        double omega = 2.0 * M_PI * freq / sampleRate;
        double cosw = std::cos(omega);
        double sinw = std::sin(omega);
        double A = std::pow(10.0, gain_dB / 40.0);
        double beta = std::sqrt(A) / 1.0; // Q = 1
        
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
    
    void calculateTiltCoefficients(double freq, double gain_dB,
                                   double& b0, double& b1, double& b2, double& a1, double& a2)
    {
        if (std::abs(gain_dB) < 0.01)
        {
            // Bypass filter
            b0 = 1.0; b1 = 0.0; b2 = 0.0; a1 = 0.0; a2 = 0.0;
            return;
        }
        
        // Tilt filter implementation - combines high and low shelf
        double omega = 2.0 * M_PI * freq / sampleRate;
        double cosw = std::cos(omega);
        double sinw = std::sin(omega);
        double A = std::pow(10.0, std::abs(gain_dB) / 40.0);
        double S = 1.0; // Slope factor
        double beta = std::sqrt(A) / S;
        
        double b0_temp, b1_temp, b2_temp, a0_temp, a1_temp, a2_temp;
        
        if (gain_dB > 0) // High frequencies boosted
        {
            b0_temp = A * ((A + 1) + (A - 1) * cosw + beta * sinw);
            b1_temp = -2 * A * ((A - 1) + (A + 1) * cosw);
            b2_temp = A * ((A + 1) + (A - 1) * cosw - beta * sinw);
            a0_temp = (A + 1) - (A - 1) * cosw + beta * sinw;
            a1_temp = 2 * ((A - 1) - (A + 1) * cosw);
            a2_temp = (A + 1) - (A - 1) * cosw - beta * sinw;
        }
        else // High frequencies cut (vintage rolloff)
        {
            b0_temp = (A + 1) - (A - 1) * cosw + beta * sinw;
            b1_temp = 2 * ((A - 1) - (A + 1) * cosw);
            b2_temp = (A + 1) - (A - 1) * cosw - beta * sinw;
            a0_temp = A * ((A + 1) + (A - 1) * cosw + beta * sinw);
            a1_temp = -2 * A * ((A - 1) + (A + 1) * cosw);
            a2_temp = A * ((A + 1) + (A - 1) * cosw - beta * sinw);
        }
        
        b0 = b0_temp / a0_temp;
        b1 = b1_temp / a0_temp;
        b2 = b2_temp / a0_temp;
        a1 = a1_temp / a0_temp;
        a2 = a2_temp / a0_temp;
    }
};

} // namespace project

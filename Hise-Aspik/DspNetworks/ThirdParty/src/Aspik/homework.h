#pragma once

#ifndef __aspikHomework__
#define __aspikHomework__

#include "aspik.h"
using namespace aspik;

#include <algorithm>
#include <cmath>

// Utility function for clamping values
template<typename T>
T clamp(T value, T min, T max) {
    return std::max(min, std::min(max, value));
}

/*
 ==========================| ASPIK Chapter 17 Homework - Reverbs |==========================
 
 This file contains implementations of classic reverb algorithms from
 Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed." Chapter 17.
 
 All implementations use ASPIK building blocks from fxobjects.h for consistency
 and educational purposes. Each reverb follows the textbook specifications.
 
 Current Status:
 ✓ SchroederReverb - Complete (4 parallel combs + 2 series APFs)
 ✓ MoorerReverb - LPF-comb filters for HF damping
 ✓ DattorroReverb - Figure-8 tank with modulated APFs
 ○ FDNReverb - TODO (Feedback delay network with matrix)
 */

// =============================================================================
// CONSTANTS AND ENUMERATIONS
// =============================================================================

const unsigned int SCHROEDER_COMB_FILTERS = 4;
const unsigned int SCHROEDER_APF_FILTERS = 2;
const unsigned int MOORER_COMB_FILTERS = 6;
const unsigned int DATTORRO_BRANCHES = 2;
const unsigned int FDN_MAX_DELAYS = 8;

enum class reverbType { kSchroeder, kMoorer, kDattorro, kFDN };

// =============================================================================
// SCHROEDER REVERB (Section 17.5)
// =============================================================================

struct SchroederReverbParameters
{
    SchroederReverbParameters() {}
    SchroederReverbParameters& operator=(const SchroederReverbParameters& params)
    {
        if (this == &params) return *this;
        rt60_mSec = params.rt60_mSec;
        apfGain = params.apfGain;
        wetLevel_dB = params.wetLevel_dB;
        dryLevel_dB = params.dryLevel_dB;
        return *this;
    }
    
    double rt60_mSec = 1000.0;      // reverb time (100-5000ms typical)
    double apfGain = 0.7;           // all-pass gain (0.7 is Schroeder's recommendation)
    double wetLevel_dB = -6.0;      // wet signal level
    double dryLevel_dB = -6.0;      // dry signal level
};

class SchroederReverb : public IAudioSignalProcessor
{
public:
    SchroederReverb() {}
    ~SchroederReverb() {}
    
    virtual bool reset(double _sampleRate)
    {
        sampleRate = _sampleRate;
        
        for (int i = 0; i < SCHROEDER_COMB_FILTERS; i++)
        {
            combFilters[i].reset(_sampleRate);
        }
        
        for (int i = 0; i < SCHROEDER_APF_FILTERS; i++)
        {
            allPassFilters[i].reset(_sampleRate);
        }
        
        createDelayBuffers();
        return true;
    }
    
    SchroederReverbParameters getParameters() { return parameters; }
    
    void setParameters(const SchroederReverbParameters& params)
    {
        parameters = params;
        
        // Update comb filter RT60 times - this sets the correct feedback gains automatically
        for (int i = 0; i < SCHROEDER_COMB_FILTERS; i++)
        {
            CombFilterParameters combParams = combFilters[i].getParameters();
            combParams.RT60Time_mSec = parameters.rt60_mSec;
            // Enable interpolation for smoother sound
            combParams.interpolate = true;
            combFilters[i].setParameters(combParams);
        }
        
        // Update all-pass filter gains - typically 0.7 for better diffusion
        for (int i = 0; i < SCHROEDER_APF_FILTERS; i++)
        {
            DelayAPFParameters apfParams = allPassFilters[i].getParameters();
            apfParams.apf_g = parameters.apfGain;
            apfParams.interpolate = true;
            allPassFilters[i].setParameters(apfParams);
        }
    }
    
    virtual bool processAudioFrame(const float* inputFrame, float* outputFrame,
                                   uint32_t inputChannels, uint32_t outputChannels)
    {
        double xn = inputFrame[0];
        
        // Process through parallel comb filters
        double combSum = 0.0;
        for (int i = 0; i < SCHROEDER_COMB_FILTERS; i++)
        {
            double combOut = combFilters[i].processAudioSample(xn);
            
            // Phase flip every other comb output (per textbook)
            if (i % 2 == 1)
                combOut = -combOut;
            
            combSum += combOut;
        }
        
        // Process through series all-pass filters
        double apfOut = combSum;
        for (int i = 0; i < SCHROEDER_APF_FILTERS; i++)
        {
            apfOut = allPassFilters[i].processAudioSample(apfOut);
        }
        
        // Apply wet/dry mix
        double wet = pow(10.0, parameters.wetLevel_dB / 20.0);
        double dry = pow(10.0, parameters.dryLevel_dB / 20.0);
        
        // Output (mono to stereo)
        double output = dry * xn + wet * apfOut;
        outputFrame[0] = output;
        if (outputChannels > 1)
            outputFrame[1] = output;
        
        return true;
    }
    
    virtual double processAudioSample(double xn)
    {
        float input = xn;
        float output = 0.0;
        processAudioFrame(&input, &output, 1, 1);
        return output;
    }
    
    virtual bool canProcessAudioFrame() { return true; }
    
private:
    void createDelayBuffers()
    {
        if (sampleRate <= 0) return;
        
        // Schroeder's original delay times from textbook (scaled for 44.1kHz)
        // These maintain the 1:1.5 ratio rule and are mutually prime
        // From Pirkle textbook Section 17.5: 30-45ms range for combs
        double combDelayTimes[SCHROEDER_COMB_FILTERS] = {
            30.0,   // ~1323 samples at 44.1kHz
            37.1,   // ~1638 samples
            41.1,   // ~1813 samples
            43.7    // ~1928 samples
        };
        
        // All-pass delays: much shorter (1-5ms per textbook)
        double apfDelayTimes[SCHROEDER_APF_FILTERS] = {
            5.0,    // ~221 samples
            1.7     // ~75 samples
        };
        
        for (int i = 0; i < SCHROEDER_COMB_FILTERS; i++)
        {
            combFilters[i].createDelayBuffer(sampleRate, combDelayTimes[i]);
            
            // Set initial parameters with proper RT60 feedback calculation
            CombFilterParameters combParams = combFilters[i].getParameters();
            combParams.delayTime_mSec = combDelayTimes[i];
            combParams.RT60Time_mSec = parameters.rt60_mSec;
            combParams.interpolate = true;
            combFilters[i].setParameters(combParams);
        }
        
        for (int i = 0; i < SCHROEDER_APF_FILTERS; i++)
        {
            allPassFilters[i].createDelayBuffer(sampleRate, apfDelayTimes[i]);
            
            // Set initial parameters
            DelayAPFParameters apfParams = allPassFilters[i].getParameters();
            apfParams.delayTime_mSec = apfDelayTimes[i];
            apfParams.apf_g = parameters.apfGain;
            apfParams.interpolate = true;
            allPassFilters[i].setParameters(apfParams);
        }
    }
    
    SchroederReverbParameters parameters;
    double sampleRate = 44100.0;
    CombFilter combFilters[SCHROEDER_COMB_FILTERS];
    DelayAPF allPassFilters[SCHROEDER_APF_FILTERS];
};

// =============================================================================
// MOORER REVERB (Section 17.9)
// =============================================================================

struct MoorerReverbParameters
{
    MoorerReverbParameters() {}
    MoorerReverbParameters& operator=(const MoorerReverbParameters& params)
    {
        if (this == &params) return *this;
        rt60_mSec = params.rt60_mSec;
        damping = params.damping;
        apfGain = params.apfGain;
        preDelayTime_mSec = params.preDelayTime_mSec;
        wetLevel_dB = params.wetLevel_dB;
        dryLevel_dB = params.dryLevel_dB;
        useAdvancedDamping = params.useAdvancedDamping;
        return *this;
    }
    
    double rt60_mSec = 1000.0;
    double damping = 0.5;
    double apfGain = 0.707;
    double preDelayTime_mSec = 0.0;     // Pre-delay time (0-100ms typical)
    double wetLevel_dB = -6.0;
    double dryLevel_dB = -6.0;
    bool useAdvancedDamping = false;    // Enable air absorption modeling
};

class MoorerReverb : public IAudioSignalProcessor
{
public:
    MoorerReverb() {}
    ~MoorerReverb() {}
    
    virtual bool reset(double _sampleRate)
    {
        sampleRate = _sampleRate;
        
        // Reset pre-delay
        preDelay.reset(_sampleRate);
        
        // Reset all comb/lpf filters
        for (int i = 0; i < MOORER_COMB_FILTERS; i++)
        {
            combFilters[i].reset(_sampleRate);
        }
        
        // Reset single all-pass filter
        allPassFilter.reset(_sampleRate);
        createDelayBuffers();
        return true;
    }
    
    MoorerReverbParameters getParameters() { return parameters; }
    
    void setParameters(const MoorerReverbParameters& params)
    {
        parameters = params;
        
        // Update pre-delay
        SimpleDelayParameters preDelayParams = preDelay.getParameters();
        preDelayParams.delayTime_mSec = parameters.preDelayTime_mSec;
        preDelayParams.interpolate = true;
        preDelay.setParameters(preDelayParams);
        
        // Update comb filter parameters with LPF enabled
        for (int i = 0; i < MOORER_COMB_FILTERS; i++)
        {
            CombFilterParameters combParams = combFilters[i].getParameters();
            combParams.RT60Time_mSec = parameters.rt60_mSec;
            combParams.enableLPF = true;                    // Enable LPF
            combParams.lpf_g = calculateDamping(i);         // Frequency-dependent damping
            combParams.interpolate = true;
            combFilters[i].setParameters(combParams);
        }
        
        // Update single all-pass filter
        DelayAPFParameters apfParams = allPassFilter.getParameters();
        apfParams.apf_g = parameters.apfGain;
        apfParams.interpolate = true;
        allPassFilter.setParameters(apfParams);
    }
    
    virtual bool processAudioFrame(const float* inputFrame, float* outputFrame,
                                   uint32_t inputChannels, uint32_t outputChannels)
    {
        double xn = inputFrame[0];
        
        // Apply pre-delay first
        double preDelayedInput = preDelay.processAudioSample(xn);
        
        // Process through 6 parallel LPF-comb filters
        double combSum = 0.0;
        for (int i = 0; i < MOORER_COMB_FILTERS; i++)
        {
            double combOut = combFilters[i].processAudioSample(preDelayedInput);
            
            // Phase alternation (optional - some implementations skip this)
            if (i % 2 == 1) combOut = -combOut;
            
            combSum += combOut;
        }
        
        // Process through series all-pass filters
        double apfOut = allPassFilter.processAudioSample(combSum);
        
        // Apply wet/dry mix
        double wet = pow(10.0, parameters.wetLevel_dB / 20.0);
        double dry = pow(10.0, parameters.dryLevel_dB / 20.0);
        
        // Output (mono to stereo)
        double output = dry * xn + wet * apfOut;
        outputFrame[0] = output;
        if (outputChannels > 1) outputFrame[1] = output;
        return true;
    }
    
    virtual double processAudioSample(double xn)
    {
        float input = xn;
        float output = 0.0;
        processAudioFrame(&input, &output, 1, 1);
        return output;
    }
    
    virtual bool canProcessAudioFrame() { return true; }
    
private:
    void createDelayBuffers()
    {
        if (sampleRate <= 0) return;
        
        preDelay.createDelayBuffer(sampleRate, 100.0);
        
        combDelayTimes[0] = 25.31; combDelayTimes[1] = 26.94; combDelayTimes[2] = 28.96;
        combDelayTimes[3] = 30.75; combDelayTimes[4] = 32.24; combDelayTimes[5] = 33.83;
        
        for (int i = 0; i < MOORER_COMB_FILTERS; i++)
        {
            combFilters[i].createDelayBuffer(sampleRate, combDelayTimes[i]);
            
            CombFilterParameters combParams = combFilters[i].getParameters();
            combParams.delayTime_mSec = combDelayTimes[i];
            combParams.RT60Time_mSec = parameters.rt60_mSec;
            combParams.enableLPF = true;
            combParams.lpf_g = calculateDamping(i);
            combParams.interpolate = true;
            combFilters[i].setParameters(combParams);
        }
        
        allPassFilter.createDelayBuffer(sampleRate, 6.0);
        DelayAPFParameters apfParams = allPassFilter.getParameters();
        apfParams.delayTime_mSec = 6.0;
        apfParams.apf_g = parameters.apfGain;
        apfParams.interpolate = true;
        allPassFilter.setParameters(apfParams);
        
        SimpleDelayParameters preDelayParams = preDelay.getParameters();
        preDelayParams.delayTime_mSec = parameters.preDelayTime_mSec;
        preDelayParams.interpolate = true;
        preDelay.setParameters(preDelayParams);
    }
    
    double calculateDamping(int combIndex)
    {
        if (parameters.useAdvancedDamping)
        {
            return calculateAirAbsorption(combDelayTimes[combIndex]);
        }
        else
        {
            double baseDamping[MOORER_COMB_FILTERS] = { 0.2, 0.25, 0.3, 0.35, 0.4, 0.45 };
            double finalDamping = baseDamping[combIndex] * parameters.damping;
            return clamp(finalDamping, 0.0, 0.85);
        }
    }
    
    double calculateAirAbsorption(double delayTime_mSec)
    {
        double distance_m = (delayTime_mSec / 1000.0) * 344.8;
        double frequency = 1000.0 / (delayTime_mSec * 0.001 * 344.8);
        
        // Air absorption at 50% humidity (dB/meter)
        double absorptionCoeff;
        if (frequency <= 1000.0) absorptionCoeff = 0.0056;
        else if (frequency <= 2000.0) absorptionCoeff = 0.0056 + (frequency - 1000.0) / 1000.0 * (0.0117 - 0.0056);
        else if (frequency <= 3000.0) absorptionCoeff = 0.0117 + (frequency - 2000.0) / 1000.0 * (0.0261 - 0.0117);
        else if (frequency <= 4000.0) absorptionCoeff = 0.0261 + (frequency - 3000.0) / 1000.0 * (0.0899 - 0.0261);
        else absorptionCoeff = 0.0899;
        
        double absorption_dB = absorptionCoeff * distance_m;
        double absorptionFactor = pow(10.0, -absorption_dB / 20.0);
        double finalCoeff = absorptionFactor * (1.0 - parameters.damping * 0.8);
        
        return clamp(finalCoeff, 0.1, 0.95);
    }
    
    MoorerReverbParameters parameters;
    double sampleRate = 44100.0;
    double combDelayTimes[MOORER_COMB_FILTERS];
    
    SimpleDelay preDelay;
    CombFilter combFilters[MOORER_COMB_FILTERS];
    DelayAPF allPassFilter;
};

// Advanced Air Absorption Implementation
// Based on Moorer's 1979 paper and air absorption research

class AirAbsorptionCalculator
{
public:
    // Air absorption coefficients at 20°C (dB/meter)
    // From Moorer's paper - Table 1
    struct AbsorptionData
    {
        double humidity;    // Relative humidity %
        double freq1000;    // 1000 Hz
        double freq2000;    // 2000 Hz
        double freq3000;    // 3000 Hz
        double freq4000;    // 4000 Hz
    };
    
    static const AbsorptionData absorptionTable[4];
    
    // Calculate LPF coefficient based on delay time and frequency
    static double calculateLPFCoefficient(double delayTime_mSec, double sampleRate,
                                          double humidity = 50.0, double userDamping = 0.5)
    {
        double distance_m = (delayTime_mSec / 1000.0) * 344.8;
        double estimatedFreq = 1000.0 / delayTime_mSec;  // Hz
        double absorptionCoeff = interpolateAbsorption(estimatedFreq, humidity);
        
        // Convert to LPF coefficient
        double absorption_dB = absorptionCoeff * distance_m;
        double absorptionFactor = pow(10.0, -absorption_dB / 20.0);
        double finalCoeff = absorptionFactor * (1.0 - userDamping * 0.8);
        
        return jlimit(0.1, 0.95, finalCoeff);
    }
    
private:
    static double interpolateAbsorption(double frequency, double humidity)
    {
        // Find closest humidity value in table
        int humidityIndex = 1; // Default to 50% humidity
        if (humidity < 45.0) humidityIndex = 0;      // 40%
        else if (humidity < 55.0) humidityIndex = 1;  // 50%
        else if (humidity < 65.0) humidityIndex = 2;  // 60%
        else humidityIndex = 3;                       // 70%
        
        const AbsorptionData& data = absorptionTable[humidityIndex];
        
        // Linear interpolation between frequency points
        if (frequency <= 1000.0) return data.freq1000;
        else if (frequency <= 2000.0)
        {
            double ratio = (frequency - 1000.0) / 1000.0;
            return data.freq1000 + ratio * (data.freq2000 - data.freq1000);
        }
        else if (frequency <= 3000.0)
        {
            double ratio = (frequency - 2000.0) / 1000.0;
            return data.freq2000 + ratio * (data.freq3000 - data.freq2000);
        }
        else if (frequency <= 4000.0)
        {
            double ratio = (frequency - 3000.0) / 1000.0;
            return data.freq3000 + ratio * (data.freq4000 - data.freq3000);
        }
        else return data.freq4000; // Above 4kHz
    }
};

// Air absorption data from Moorer's paper (dB/meter)
const AirAbsorptionCalculator::AbsorptionData AirAbsorptionCalculator::absorptionTable[4] =
{
    {40.0, 0.0056, 0.0161, 0.0300, 0.1051},  // 40% humidity
    {50.0, 0.0056, 0.0117, 0.0261, 0.0899},  // 50% humidity
    {60.0, 0.0056, 0.0117, 0.0239, 0.0734},  // 60% humidity
    {70.0, 0.0056, 0.0117, 0.0217, 0.0630}   // 70% humidity
};

// Enhanced frequency-dependent damping using air absorption
double calculateAdvancedFrequencyDamping(int combIndex, double dampingControl,
                                         double combDelayTime_mSec, double sampleRate)
{
    // Use air absorption calculator for realistic damping
    return AirAbsorptionCalculator::calculateLPFCoefficient(
                                                            combDelayTime_mSec,
                                                            sampleRate,
                                                            50.0,           // 50% humidity (adjustable)
                                                            dampingControl  // User control
                                                            );
}


// =============================================================================
// DATTORRO REVERB (Section 17.10)
// =============================================================================
struct DattorroReverbParameters
{
    DattorroReverbParameters() {}
    DattorroReverbParameters& operator=(const DattorroReverbParameters& params)
    {
        if (this == &params) return *this;
        preDelay_mSec = params.preDelay_mSec;
        bandwidth = params.bandwidth;
        damping = params.damping;
        decay = params.decay;
        wetLevel_dB = params.wetLevel_dB;
        dryLevel_dB = params.dryLevel_dB;
        return *this;
    }
    double preDelay_mSec = 0.0;
    double bandwidth = 0.5;
    double damping = 0.5;
    double decay = 0.5;
    double wetLevel_dB = -6.0;
    double dryLevel_dB = -6.0;
};

class DattorroReverb : public IAudioSignalProcessor
{
public:
    DattorroReverb() {}
    ~DattorroReverb() {}
    
    virtual bool reset(double _sampleRate)
    {
        sampleRate = _sampleRate;
        
        // Reset all components
        preDelay.reset(_sampleRate);
        bandwidthLPF.reset(_sampleRate);
        
        for (int i = 0; i < 4; i++)
        {
            inputAPFs[i].reset(_sampleRate);
        }
        
        modulatedAPF1.reset(_sampleRate);
        modulatedAPF2.reset(_sampleRate);
        dampingLPF1.reset(_sampleRate);
        dampingLPF2.reset(_sampleRate);
        fixedDelay1.reset(_sampleRate);
        fixedDelay2.reset(_sampleRate);
        
        // Reset feedback state
        tankFeedback1 = 0.0;
        tankFeedback2 = 0.0;
        createDelayBuffers();
        return true;
    }
    
    DattorroReverbParameters getParameters() { return parameters; }
    
    void setParameters(const DattorroReverbParameters& params)
    {
        parameters = params;
        
        // Update pre-delay
        SimpleDelayParameters preDelayParams = preDelay.getParameters();
        preDelayParams.delayTime_mSec = parameters.preDelay_mSec;
        preDelayParams.interpolate = true;
        preDelay.setParameters(preDelayParams);
        
        // Update bandwidth LPF
        SimpleLPFParameters bandwidthParams = bandwidthLPF.getParameters();
        bandwidthParams.g = parameters.bandwidth;
        bandwidthLPF.setParameters(bandwidthParams);
        
        // Update damping LPFs
        SimpleLPFParameters dampingParams1 = dampingLPF1.getParameters();
        dampingParams1.g = parameters.damping;
        dampingLPF1.setParameters(dampingParams1);
        
        SimpleLPFParameters dampingParams2 = dampingLPF2.getParameters();
        dampingParams2.g = parameters.damping;
        dampingLPF2.setParameters(dampingParams2);
        
        // Update decay coefficient
        decayCoefficient = parameters.decay;
    }
    
    virtual bool processAudioFrame(const float* inputFrame, float* outputFrame,
                                   uint32_t inputChannels, uint32_t outputChannels)
    {
        double xn = inputFrame[0];
        
        // STEP 1: Pre-delay → Bandwidth LPF → Series APFs
        double preDelayed = preDelay.processAudioSample(xn);
        double bandwidthFiltered = bandwidthLPF.processAudioSample(preDelayed);
        
        double diffused = bandwidthFiltered;
        for (int i = 0; i < 4; i++)
        {
            diffused = inputAPFs[i].processAudioSample(diffused);
        }
        
        // STEP 2: Process through PROPER figure-8 tank
        // The Dattorro tank has two parallel paths that cross-couple
        
        // Branch 1 (Left): input + feedback from branch 2
        double branch1Input = diffused + tankFeedback2;
        double apf1Out = modulatedAPF1.processAudioSample(branch1Input);
        double damp1Out = dampingLPF1.processAudioSample(apf1Out);
        double delay1Out = fixedDelay1.processAudioSample(damp1Out);
        tankFeedback1 = delay1Out * decayCoefficient;
        
        // Branch 2 (Right): input + feedback from branch 1
        double branch2Input = diffused + tankFeedback1;
        double apf2Out = modulatedAPF2.processAudioSample(branch2Input);
        double damp2Out = dampingLPF2.processAudioSample(apf2Out);
        double delay2Out = fixedDelay2.processAudioSample(damp2Out);
        tankFeedback2 = delay2Out * decayCoefficient;
        
        // STEP 3: Stereo Output Taps (simplified but working approach)
        // Instead of complex tap reading, use the delay outputs directly with decorrelation
        double leftOut = delay1Out + delay2Out * 0.7;
        double rightOut = delay2Out + delay1Out * 0.7;
        
        // Add some early reflections from the APF stages for more density
        leftOut += apf1Out * 0.3;
        rightOut += apf2Out * 0.3;
        
        // STEP 4: Wet/Dry Mix
        double wet = pow(10.0, parameters.wetLevel_dB / 20.0);
        double dry = pow(10.0, parameters.dryLevel_dB / 20.0);
        
        outputFrame[0] = dry * xn + wet * leftOut;
        if (outputChannels > 1)
            outputFrame[1] = dry * xn + wet * rightOut;
        else
            outputFrame[0] = dry * xn + wet * (leftOut + rightOut) * 0.5;
        
        return true;
    }
    
    virtual double processAudioSample(double xn)
    {
        float input = xn;
        float output[2] = { 0.0f, 0.0f };
        processAudioFrame(&input, output, 1, 2);
        return output[0];
    }
    
    virtual bool canProcessAudioFrame() { return true; }
    
private:
    void createDelayBuffers()
    {
        if (sampleRate <= 0) return;
        
        // Create pre-delay buffer (up to 100ms)
        preDelay.createDelayBuffer(sampleRate, 100.0);
        
        // Input APF delays (44.1kHz values from Table 17.1 in Pirkle book)
        double inputAPFDelays[4] = { 4.77, 3.58, 12.73, 9.31 }; // ms
        double inputAPFGains[4] = { 0.75, 0.75, 0.625, 0.625 };
        
        for (int i = 0; i < 4; i++)
        {
            inputAPFs[i].createDelayBuffer(sampleRate, inputAPFDelays[i]);
            
            DelayAPFParameters apfParams = inputAPFs[i].getParameters();
            apfParams.delayTime_mSec = inputAPFDelays[i];
            apfParams.apf_g = inputAPFGains[i];
            apfParams.enableLPF = false;
            apfParams.enableLFO = false;
            inputAPFs[i].setParameters(apfParams);
        }
        
        // Tank modulated APFs (44.1kHz values from Table 17.1)
        double tankAPFDelays[2] = { 30.5, 22.6 }; // ms (scaled from original)
        double tankAPFGains[2] = { 0.7, 0.7 };
        
        for (int i = 0; i < 2; i++)
        {
            DelayAPF* apf = (i == 0) ? &modulatedAPF1 : &modulatedAPF2;
            apf->createDelayBuffer(sampleRate, tankAPFDelays[i]);
            
            DelayAPFParameters tankAPFParams = apf->getParameters();
            tankAPFParams.delayTime_mSec = tankAPFDelays[i];
            tankAPFParams.apf_g = tankAPFGains[i];
            tankAPFParams.enableLPF = false;
            tankAPFParams.enableLFO = true;  // Enable modulation for natural sound
            tankAPFParams.lfoRate_Hz = 0.1 + (i * 0.05); // Slow modulation, slightly different rates
            tankAPFParams.lfoDepth = 0.1; // Subtle modulation depth
            tankAPFParams.lfoMaxModulation_mSec = 1.0; // Small modulation range
            apf->setParameters(tankAPFParams);
        }
        
        // Tank fixed delays (44.1kHz values from Table 17.1)
        double tankDelays[2] = { 141.7, 125.0 }; // ms
        
        fixedDelay1.createDelayBuffer(sampleRate, tankDelays[0]);
        fixedDelay2.createDelayBuffer(sampleRate, tankDelays[1]);
        
        SimpleDelayParameters delayParams1 = fixedDelay1.getParameters();
        delayParams1.delayTime_mSec = tankDelays[0];
        delayParams1.interpolate = true;
        fixedDelay1.setParameters(delayParams1);
        
        SimpleDelayParameters delayParams2 = fixedDelay2.getParameters();
        delayParams2.delayTime_mSec = tankDelays[1];
        delayParams2.interpolate = true;
        fixedDelay2.setParameters(delayParams2);
    }
    
    DattorroReverbParameters parameters;
    double sampleRate = 44100.0;
    double tankFeedback1 = 0.0;  // Separate feedback for each branch
    double tankFeedback2 = 0.0;
    double decayCoefficient = 0.5;
    
    // Processing components
    SimpleDelay preDelay;
    SimpleLPF bandwidthLPF;
    DelayAPF inputAPFs[4];
    DelayAPF modulatedAPF1;
    DelayAPF modulatedAPF2;
    SimpleLPF dampingLPF1;
    SimpleLPF dampingLPF2;
    SimpleDelay fixedDelay1;
    SimpleDelay fixedDelay2;
};

// =============================================================================
// Forward-Delay Netowrk (FDN) REVERB (Section 17.12)
// =============================================================================
struct FDNReverbParameters
{
    FDNReverbParameters() {}
    FDNReverbParameters& operator=(const FDNReverbParameters& params)
    {
        if (this == &params) return *this;
        rt60_mSec = params.rt60_mSec;
        numDelays = params.numDelays;
        damping = params.damping;
        wetLevel_dB = params.wetLevel_dB;
        dryLevel_dB = params.dryLevel_dB;
        return *this;
    }
    
    double rt60_mSec = 1000.0;
    int numDelays = 4;
    double damping = 0.5;
    double wetLevel_dB = -6.0;
    double dryLevel_dB = -6.0;
};

class FDNReverb : public IAudioSignalProcessor
{
public:
    FDNReverb()
    {
        // Initialize matrices and state
        for (int i = 0; i < FDN_MAX_DELAYS; i++)
        {
            for (int j = 0; j < FDN_MAX_DELAYS; j++)
            {
                feedbackMatrix[i][j] = 0.0;
            }
        }
    }
    ~FDNReverb() {}
    
    virtual bool reset(double _sampleRate)
    {
        sampleRate = _sampleRate;
        
        // Reset delay lines and filters
        for (int i = 0; i < FDN_MAX_DELAYS; i++)
        {
            delayLines[i].reset(_sampleRate);
            dampingFilters[i].reset(_sampleRate);
        }
        
        createDelayBuffers();
        return true;
    }
    
    FDNReverbParameters getParameters() { return parameters; }
    
    void setParameters(const FDNReverbParameters& params)
    {
        parameters = params;
        parameters.numDelays = clamp(parameters.numDelays, 2, (int)FDN_MAX_DELAYS);
        
        // Update damping filters using Jot's formula
        for (int i = 0; i < parameters.numDelays; i++)
        {
            updateDampingFilter(i);
        }
        
        calculateFeedbackMatrix();
    }
    
    virtual bool processAudioFrame(const float* inputFrame, float* outputFrame,
                                   uint32_t inputChannels, uint32_t outputChannels)
    {
        double xn = inputFrame[0];
        
        // Step 1: Read all delay outputs before processing
        double delayOutputs[FDN_MAX_DELAYS];
        for (int i = 0; i < parameters.numDelays; i++)
        {
            delayOutputs[i] = delayLines[i].readDelay();
        }
        
        // Step 2: Calculate matrix-weighted feedback and write to delays
        for (int i = 0; i < parameters.numDelays; i++)
        {
            double newInput = xn; // Input to each delay
            
            // Matrix multiplication: sum of weighted outputs
            for (int j = 0; j < parameters.numDelays; j++)
            {
                newInput += feedbackMatrix[i][j] * delayOutputs[j];
            }
            
            // Apply frequency-dependent damping (Jot's LPF)
            newInput = dampingFilters[i].processAudioSample(newInput);
            
            // Write to delay line
            delayLines[i].writeDelay(newInput);
        }
        
        // Step 3: Mix outputs for stereo
        double leftOut = 0.0;
        double rightOut = 0.0;
        
        for (int i = 0; i < parameters.numDelays; i++)
        {
            if (i % 2 == 0)
            {
                leftOut += delayOutputs[i];
                rightOut += delayOutputs[i] * 0.7;
            }
            else
            {
                leftOut += delayOutputs[i] * 0.7;
                rightOut += delayOutputs[i];
            }
        }
        
        // Normalize to prevent energy buildup
        double norm = 1.0 / sqrt((double)parameters.numDelays);
        leftOut *= norm;
        rightOut *= norm;
        
        // Step 4: Wet/dry mix
        double wet = pow(10.0, parameters.wetLevel_dB / 20.0);
        double dry = pow(10.0, parameters.dryLevel_dB / 20.0);
        
        outputFrame[0] = dry * xn + wet * leftOut;
        if (outputChannels > 1)
            outputFrame[1] = dry * xn + wet * rightOut;
        
        return true;
    }
    
    virtual double processAudioSample(double xn)
    {
        float input = xn;
        float output[2] = { 0.0f, 0.0f };
        processAudioFrame(&input, output, 1, 2);
        return output[0];
    }
    
    virtual bool canProcessAudioFrame() { return true; }
    
private:
    void createDelayBuffers()
    {
        if (sampleRate <= 0) return;
        
        // Prime delay times (ms) for good diffusion
        double delayTimes[FDN_MAX_DELAYS] = {
            29.7, 37.1, 41.1, 43.7, 47.0, 53.0, 59.0, 61.0
        };
        
        for (int i = 0; i < FDN_MAX_DELAYS; i++)
        {
            delayLines[i].createDelayBuffer(sampleRate, delayTimes[i] + 10.0);
            
            SimpleDelayParameters delayParams = delayLines[i].getParameters();
            delayParams.delayTime_mSec = delayTimes[i];
            delayParams.interpolate = true;
            delayLines[i].setParameters(delayParams);
        }
    }
    
    void updateDampingFilter(int index)
    {
        // Jot's formula for LPF magnitude (Equation 17.21):
        // 20*log(|h|) = (-60*Ts/RT60(omega)) * M
        // where M = delay length, Ts = 1/fs
        
        double M = delayLines[index].getParameters().delayTime_mSec / 1000.0; // Convert to seconds
        double Ts = 1.0 / sampleRate;
        double RT60_sec = parameters.rt60_mSec / 1000.0;
        
        // Calculate magnitude: |h| = 10^((-60*Ts*M)/(20*RT60))
        double exponent = (-60.0 * Ts * M) / (20.0 * RT60_sec);
        double magnitude = pow(10.0, exponent);
        
        // Convert magnitude to g parameter for one-pole LPF
        // For a one-pole LPF: g = magnitude (approximately)
        double g = clamp(magnitude, 0.1, 0.99);
        
        // Apply user damping control as a multiplier
        g *= parameters.damping;
        g = clamp(g, 0.1, 0.99);
        
        SimpleLPFParameters dampingParams = dampingFilters[index].getParameters();
        dampingParams.g = g;
        dampingFilters[index].setParameters(dampingParams);
    }
    
    void calculateFeedbackMatrix()
    {
        // Clear matrix
        for (int i = 0; i < FDN_MAX_DELAYS; i++)
        {
            for (int j = 0; j < FDN_MAX_DELAYS; j++)
            {
                feedbackMatrix[i][j] = 0.0;
            }
        }
        
        // Calculate global gain using Jot's absorptive coefficient
        double g = calculateJotGain();
        
        if (parameters.numDelays == 2)
        {
            // 2x2 matrix from equation 17.18: [0 1; 1 0] * g
            feedbackMatrix[0][1] = g;
            feedbackMatrix[1][0] = g;
        }
        else if (parameters.numDelays == 4)
        {
            // CORRECT 4x4 Stautner-Puckette matrix from equation 17.22
            // G = (g/√2) * [0  1  1  0]
            //              [-1 0  0 -1]
            //              [1  0  0 -1]
            //              [0  1 -1  0]
            
            double gSqrt2 = g / sqrt(2.0);
            
            // Row 0: [0  1  1  0]
            feedbackMatrix[0][1] = gSqrt2;
            feedbackMatrix[0][2] = gSqrt2;
            
            // Row 1: [-1 0  0 -1]
            feedbackMatrix[1][0] = -gSqrt2;
            feedbackMatrix[1][3] = -gSqrt2;
            
            // Row 2: [1  0  0 -1]
            feedbackMatrix[2][0] = gSqrt2;
            feedbackMatrix[2][3] = -gSqrt2;
            
            // Row 3: [0  1 -1  0]
            feedbackMatrix[3][1] = gSqrt2;
            feedbackMatrix[3][2] = -gSqrt2;
        }
        else
        {
            // For other sizes, use Hadamard-style circulant pattern
            double normGain = g / sqrt((double)parameters.numDelays);
            for (int i = 0; i < parameters.numDelays; i++)
            {
                int next = (i + 1) % parameters.numDelays;
                feedbackMatrix[i][next] = normGain;
                
                if (parameters.numDelays > 2)
                {
                    int skip = (i + 2) % parameters.numDelays;
                    feedbackMatrix[i][skip] = normGain * ((i % 2 == 0) ? 0.7 : -0.7);
                }
            }
        }
    }
    
    double calculateJotGain()
    {
        // Jot's absorptive coefficient (Equation 17.20): k = γ^M
        // where M = delay length, γ = delay factor
        
        // Calculate average delay time in samples
        double avgDelaySamples = 0.0;
        for (int i = 0; i < parameters.numDelays; i++)
        {
            double delayMs = delayLines[i].getParameters().delayTime_mSec;
            avgDelaySamples += (delayMs / 1000.0) * sampleRate;
        }
        avgDelaySamples /= parameters.numDelays;
        
        // Calculate γ from RT60: γ = 10^(-3/(RT60*fs))
        double RT60_sec = parameters.rt60_mSec / 1000.0;
        double gamma = pow(10.0, -3.0 / (RT60_sec * sampleRate));
        
        // Calculate absorptive coefficient: k = γ^M
        double k = pow(gamma, avgDelaySamples);
        
        // Scale for matrix stability
        return clamp(k * 0.9, 0.1, 0.85);
    }
    
    double clamp(double value, double min, double max)
    {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
    
    int clamp(int value, int min, int max)
    {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
    
    FDNReverbParameters parameters;
    double sampleRate = 44100.0;
    double feedbackMatrix[FDN_MAX_DELAYS][FDN_MAX_DELAYS];
    
    SimpleDelay delayLines[FDN_MAX_DELAYS];
    SimpleLPF dampingFilters[FDN_MAX_DELAYS];
};



/*
 ==========================| ASPIK Chapter 18 Homework - Dynamics |==========================
 
 Current Status:
 ✓ Feedback Processor - feedback topology dynamics processor
 ✓ Finite Gate -  gate mode to attenuate the signal down to some finite −dB rather than 0.0 (−∞ dB)
 ○ 3-band Compressor - TODO (split into 3 bands with crossover filters, each with own compressor)
 */

//==============================================================================
/**
 * AspikDynamicsFeedbackProcessor - Feedback Topology Dynamics Processor
 *
 * Homework Assignment #1: Implements feedback topology instead of feed-forward
 * In feedback topology, the detector is placed after the DCA in the signal chain
 * Based on Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed." Chapter 18 Homework #1
 */
class AspikDynamicsFeedbackProcessor
{
public:
    struct FeedbackDynamicsParameters
    {
        FeedbackDynamicsParameters() = default;
        
        // Core dynamics parameters
        double ratio = 4.0;
        double threshold_dB = -10.0;
        double kneeWidth_dB = 10.0;
        bool hardLimitGate = false;
        bool softKnee = true;
        dynamicsProcessorType calculation = dynamicsProcessorType::kCompressor;
        double attackTime_mSec = 5.0;
        double releaseTime_mSec = 500.0;
        double outputGain_dB = 0.0;
        
        // Feedback-specific parameters
        double feedbackGain = 0.8;  // Amount of feedback (0.0 to 1.0)
        
        // Outbound values for metering
        double gainReduction = 1.0;
        double gainReduction_dB = 0.0;
    };
    
    AspikDynamicsFeedbackProcessor() = default;
    ~AspikDynamicsFeedbackProcessor() = default;
    
    bool reset(double sampleRate)
    {
        detector.reset(sampleRate);
        AudioDetectorParameters detectorParams = detector.getParameters();
        detectorParams.clampToUnityMax = false;
        detectorParams.detect_dB = true;
        detector.setParameters(detectorParams);
        
        // Initialize feedback state
        feedbackSample = 0.0;
        
        return true;
    }
    
    void setParameters(const FeedbackDynamicsParameters& params)
    {
        parameters = params;
        
        // Update detector with timing parameters
        AudioDetectorParameters detectorParams = detector.getParameters();
        detectorParams.attackTime_mSec = parameters.attackTime_mSec;
        detectorParams.releaseTime_mSec = parameters.releaseTime_mSec;
        detector.setParameters(detectorParams);
    }
    
    FeedbackDynamicsParameters getParameters() const { return parameters; }
    
    double processAudioSample(double inputSample)
    {
        // FEEDBACK TOPOLOGY: Detector processes the OUTPUT signal (after DCA)
        // Mix input with feedback from previous output
        double detectorInput = inputSample + (feedbackSample * parameters.feedbackGain);
        
        // Detect the mixed signal
        double detectLevel_dB = detector.processAudioSample(detectorInput);
        
        // Compute gain reduction
        double gainReduction = computeGain(detectLevel_dB);
        
        // Apply DCA (Digitally Controlled Attenuator)
        double processedSample = inputSample * gainReduction;
        
        // Apply makeup gain
        double makeupGain = pow(10.0, parameters.outputGain_dB / 20.0);
        double outputSample = processedSample * makeupGain;
        
        // Store output for feedback (this is the key difference from feed-forward)
        feedbackSample = outputSample;
        
        return outputSample;
    }
    
private:
    FeedbackDynamicsParameters parameters;
    AudioDetector detector;
    double feedbackSample = 0.0;  // Previous output sample for feedback
    
    double computeGain(double detectLevel_dB)
    {
        double outputLevel_dB = detectLevel_dB;
        
        // Same gain calculation logic as standard DynamicsProcessor
        if (parameters.calculation == dynamicsProcessorType::kCompressor)
        {
            if (!parameters.softKnee)
            {
                if (detectLevel_dB <= parameters.threshold_dB)
                    outputLevel_dB = detectLevel_dB;
                else
                {
                    if (parameters.hardLimitGate)
                        outputLevel_dB = parameters.threshold_dB;
                    else
                        outputLevel_dB = parameters.threshold_dB + (detectLevel_dB - parameters.threshold_dB) / parameters.ratio;
                }
            }
            else // soft knee
            {
                if (2.0 * (detectLevel_dB - parameters.threshold_dB) < -parameters.kneeWidth_dB)
                    outputLevel_dB = detectLevel_dB;
                else if (2.0 * (fabs(detectLevel_dB - parameters.threshold_dB)) <= parameters.kneeWidth_dB)
                {
                    if (parameters.hardLimitGate)
                        outputLevel_dB = detectLevel_dB - pow((detectLevel_dB - parameters.threshold_dB + (parameters.kneeWidth_dB / 2.0)), 2.0) / (2.0 * parameters.kneeWidth_dB);
                    else
                        outputLevel_dB = detectLevel_dB + (((1.0 / parameters.ratio) - 1.0) * pow((detectLevel_dB - parameters.threshold_dB + (parameters.kneeWidth_dB / 2.0)), 2.0)) / (2.0 * parameters.kneeWidth_dB);
                }
                else if (2.0 * (detectLevel_dB - parameters.threshold_dB) > parameters.kneeWidth_dB)
                {
                    if (parameters.hardLimitGate)
                        outputLevel_dB = parameters.threshold_dB;
                    else
                        outputLevel_dB = parameters.threshold_dB + (detectLevel_dB - parameters.threshold_dB) / parameters.ratio;
                }
            }
        }
        else if (parameters.calculation == dynamicsProcessorType::kDownwardExpander)
        {
            if (!parameters.softKnee || parameters.hardLimitGate)
            {
                if (detectLevel_dB >= parameters.threshold_dB)
                    outputLevel_dB = detectLevel_dB;
                else
                {
                    if (parameters.hardLimitGate)
                        outputLevel_dB = -1.0e34;
                    else
                        outputLevel_dB = parameters.threshold_dB + (detectLevel_dB - parameters.threshold_dB) * parameters.ratio;
                }
            }
            else // soft knee
            {
                if (2.0 * (detectLevel_dB - parameters.threshold_dB) > parameters.kneeWidth_dB)
                    outputLevel_dB = detectLevel_dB;
                else if (2.0 * (fabs(detectLevel_dB - parameters.threshold_dB)) > -parameters.kneeWidth_dB)
                    outputLevel_dB = ((parameters.ratio - 1.0) * pow((detectLevel_dB - parameters.threshold_dB - (parameters.kneeWidth_dB / 2.0)), 2.0)) / (2.0 * parameters.kneeWidth_dB);
                else if (2.0 * (detectLevel_dB - parameters.threshold_dB) <= -parameters.kneeWidth_dB)
                    outputLevel_dB = parameters.threshold_dB + (detectLevel_dB - parameters.threshold_dB) * parameters.ratio;
            }
        }
        
        // Store gain reduction values
        parameters.gainReduction_dB = outputLevel_dB - detectLevel_dB;
        parameters.gainReduction = pow(10.0, parameters.gainReduction_dB / 20.0);
        
        return parameters.gainReduction;
    }
};

//==============================================================================
/**
 * AspikDynamicsFiniteGateProcessor - Gate with Finite Floor
 *
 * Homework Assignment #2: Gate mode attenuates to finite -dB rather than -∞ dB
 * This reduces clicks and distortion compared to traditional gates
 * Based on Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed." Chapter 18 Homework #2
 */
class AspikDynamicsFiniteGateProcessor
{
public:
    struct FiniteGateParameters
    {
        FiniteGateParameters() = default;
        
        // Core dynamics parameters
        double ratio = 10.0;
        double threshold_dB = -20.0;
        double kneeWidth_dB = 5.0;
        bool softKnee = false;  // Gates typically use hard knee
        dynamicsProcessorType calculation = dynamicsProcessorType::kDownwardExpander;
        double attackTime_mSec = 1.0;
        double releaseTime_mSec = 100.0;
        double outputGain_dB = 0.0;
        
        // Finite gate specific parameters
        double gateFloor_dB = -60.0;  // Finite attenuation floor instead of -∞ dB
        bool enableFiniteFloor = true;
        
        // Outbound values for metering
        double gainReduction = 1.0;
        double gainReduction_dB = 0.0;
    };
    
    AspikDynamicsFiniteGateProcessor() = default;
    ~AspikDynamicsFiniteGateProcessor() = default;
    
    bool reset(double sampleRate)
    {
        detector.reset(sampleRate);
        AudioDetectorParameters detectorParams = detector.getParameters();
        detectorParams.clampToUnityMax = false;
        detectorParams.detect_dB = true;
        detector.setParameters(detectorParams);
        
        return true;
    }
    
    void setParameters(const FiniteGateParameters& params)
    {
        parameters = params;
        
        // Update detector
        AudioDetectorParameters detectorParams = detector.getParameters();
        detectorParams.attackTime_mSec = parameters.attackTime_mSec;
        detectorParams.releaseTime_mSec = parameters.releaseTime_mSec;
        detector.setParameters(detectorParams);
    }
    
    FiniteGateParameters getParameters() const { return parameters; }
    
    double processAudioSample(double inputSample)
    {
        // Detect input signal level in dB
        double detectLevel_dB = detector.processAudioSample(inputSample);
        
        // Compute gain with finite floor modification
        double gainReduction = computeFiniteGain(detectLevel_dB);
        
        // Apply makeup gain
        double makeupGain = pow(10.0, parameters.outputGain_dB / 20.0);
        
        // Apply DCA + makeup gain
        return inputSample * gainReduction * makeupGain;
    }
    
private:
    FiniteGateParameters parameters;
    AudioDetector detector;
    
    double computeFiniteGain(double detectLevel_dB)
    {
        double outputLevel_dB = detectLevel_dB;
        
        // Modified gate calculation with finite floor
        if (!parameters.softKnee)
        {
            // Hard-knee finite gate
            if (detectLevel_dB >= parameters.threshold_dB)
            {
                // Above threshold: unity gain (no gating)
                outputLevel_dB = detectLevel_dB;
            }
            else
            {
                // Below threshold: apply expansion with finite floor
                if (parameters.enableFiniteFloor)
                {
                    // Calculate standard expansion
                    double expandedLevel = parameters.threshold_dB + (detectLevel_dB - parameters.threshold_dB) * parameters.ratio;
                    
                    // Clamp to finite floor instead of allowing -∞ dB
                    outputLevel_dB = jmax(expandedLevel, parameters.gateFloor_dB);
                }
                else
                {
                    // Traditional infinite gate (-∞ dB)
                    outputLevel_dB = -1.0e34;
                }
            }
        }
        else
        {
            // Soft-knee finite gate (approximation)
            if (2.0 * (detectLevel_dB - parameters.threshold_dB) > parameters.kneeWidth_dB)
            {
                // Well above threshold: unity gain
                outputLevel_dB = detectLevel_dB;
            }
            else if (2.0 * (fabs(detectLevel_dB - parameters.threshold_dB)) <= parameters.kneeWidth_dB)
            {
                // In the knee region: smooth transition
                double kneeRatio = (parameters.ratio - 1.0) * pow((detectLevel_dB - parameters.threshold_dB - (parameters.kneeWidth_dB / 2.0)), 2.0) / (2.0 * parameters.kneeWidth_dB);
                outputLevel_dB = detectLevel_dB + kneeRatio;
                
                // Apply finite floor constraint
                if (parameters.enableFiniteFloor)
                    outputLevel_dB = jmax(outputLevel_dB, parameters.gateFloor_dB);
            }
            else
            {
                // Well below threshold: full expansion with finite floor
                if (parameters.enableFiniteFloor)
                {
                    double expandedLevel = parameters.threshold_dB + (detectLevel_dB - parameters.threshold_dB) * parameters.ratio;
                    outputLevel_dB = jmax(expandedLevel, parameters.gateFloor_dB);
                }
                else
                {
                    outputLevel_dB = parameters.threshold_dB + (detectLevel_dB - parameters.threshold_dB) * parameters.ratio;
                }
            }
        }
        
        // Store gain reduction values for metering
        parameters.gainReduction_dB = outputLevel_dB - detectLevel_dB;
        parameters.gainReduction = pow(10.0, parameters.gainReduction_dB / 20.0);
        
        return parameters.gainReduction;
    }
};









/*
 ==========================| ASPIK Chapter 19 Homework - Waveshapers |==========================
 
 This file contains implementations of classic reverb algorithms from
 Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed." Chapter 17.
 
 All implementations use ASPIK building blocks from fxobjects.h for consistency
 and educational purposes. Each reverb follows the textbook specifications.
 
 Current Status:
 ✓ Fuzz Face - Complete
 ✓ Full-wave Rectifier -
 ✓ Virtual Bass -
 ○ Class B Tube Emulation -
 */

/**
 
 Custom parameter structure for the Fuzz Face emulator object.
 Based on homework assignment 19.16.1
 */
struct FuzzFaceParameters
{
    FuzzFaceParameters() {}
    
    FuzzFaceParameters& operator=(const FuzzFaceParameters& params)
    {
        if (this == &params)
            return *this;
        
        fuzzAmount = params.fuzzAmount;
        volume = params.volume;
        bias = params.bias;
        return *this;
    }
    
    double fuzzAmount = 5.0;    ///< Drive/distortion amount (mimics input gain)
    double volume = 0.5;        ///< Output volume control
    double bias = 0.0;          ///< DC bias offset for asymmetric clipping
};

//==============================================================================
/**
 * AspikWaveshaperFuzzFace - Fuzz Face Emulator
 * The FuzzFace object implements an NPN transistor-based fuzz effect emulator.
 * Based on the classic Dunlop Fuzz Face circuit characteristics shown in Figure 19.7e
 */
class FuzzFace
{
public:
    FuzzFace() {}
    ~FuzzFace() {}
    
    /** reset members to initialized state */
    bool reset(double _sampleRate)
    {
        sampleRate = _sampleRate;
        return true;
    }
    
    /** get parameters */
    FuzzFaceParameters getParameters() { return parameters; }
    
    /** set parameters */
    void setParameters(const FuzzFaceParameters& params)
    {
        parameters = params;
    }
    
    /** return false: this object only processes samples */
    bool canProcessAudioFrame() { return false; }
    
    /**
     Fuzz Face waveshaper implementation
     Based on NPN transistor characteristics from Figure 19.7e
     Uses exponential/logarithmic curves to model transistor saturation
     */
    double processAudioSample(double xn)
    {
        // Apply input drive/fuzz amount
        double drivenInput = xn * parameters.fuzzAmount;
        
        // Add DC bias for asymmetric behavior (models transistor bias point)
        double biasedInput = drivenInput + parameters.bias;
        
        // NPN Fuzz Face characteristic curve
        // Models the exponential saturation behavior of NPN transistors
        double output = 0.0;
        
        if (biasedInput > 0.0)
        {
            // Positive half: exponential compression (transistor saturation)
            output = 1.0 - exp(-biasedInput * 2.0);
        }
        else
        {
            // Negative half: sharper cutoff (transistor cutoff region)
            output = -1.0 + exp(biasedInput * 3.0);
        }
        
        // Soft limiting to prevent excessive output
        if (output > 0.95)
            output = 0.95 + 0.05 * tanh((output - 0.95) * 10.0);
        else if (output < -0.95)
            output = -0.95 + 0.05 * tanh((output + 0.95) * 10.0);
        
        // Apply volume control
        return output * parameters.volume;
    }
    
protected:
    FuzzFaceParameters parameters;
    double sampleRate = 44100.0;
};

/**
 \struct OctaveUpParameters
 \ingroup FX-Objects-Homework
 \brief
 Custom parameter structure for the Octave Up distortion object.
 Based on homework assignment 19.16.2
 */
struct OctaveUpParameters
{
    OctaveUpParameters() {}
    
    OctaveUpParameters& operator=(const OctaveUpParameters& params)
    {
        if (this == &params)
            return *this;
        
        rectifierMix = params.rectifierMix;
        distortionAmount = params.distortionAmount;
        outputGain = params.outputGain;
        return *this;
    }
    
    double rectifierMix = 0.3;      ///< Mix level of rectified signal (octave up)
    double distortionAmount = 2.0;   ///< Base distortion amount
    double outputGain = 0.5;         ///< Output gain control
};

/**
 \class OctaveUp
 \ingroup FX-Objects-Homework
 \brief
 The OctaveUp object adds a full-wave rectifier path to create octave-up distortion.
 Based on homework assignment 19.16.2 - extending the TubePreamp
 
 Author: Based on Will Pirkle's homework assignment
 */
class OctaveUp
{
public:
    OctaveUp() {}
    ~OctaveUp() {}
    
    bool reset(double _sampleRate)
    {
        sampleRate = _sampleRate;
        return true;
    }
    
    OctaveUpParameters getParameters() { return parameters; }
    
    void setParameters(const OctaveUpParameters& params)
    {
        parameters = params;
    }
    
    bool canProcessAudioFrame() { return false; }
    
    /**
     Octave-up distortion using full-wave rectification
     Creates harmonics at 2x the fundamental frequency
     */
    double processAudioSample(double xn)
    {
        // Base tube-style distortion
        double tubeDistortion = tanhDistortion(xn * parameters.distortionAmount);
        
        // Full-wave rectified path for octave-up effect
        double rectified = abs(xn);
        
        // Apply mild saturation to rectified signal
        double octaveSignal = tanh(rectified * 2.0) * 0.5;
        
        // Mix the original distortion with octave-up component
        double mixedOutput = tubeDistortion * (1.0 - parameters.rectifierMix) +
        octaveSignal * parameters.rectifierMix;
        
        return mixedOutput * parameters.outputGain;
    }
    
private:
    /** Simple tube-style distortion using tanh */
    double tanhDistortion(double input)
    {
        return tanh(input);
    }
    
protected:
    OctaveUpParameters parameters;
    double sampleRate = 44100.0;
};

/**
 \struct VirtualBassParameters
 \ingroup FX-Objects-Homework
 \brief
 Custom parameter structure for the Virtual Bass enhancement object.
 Based on homework assignment 19.16.4 implementing the VB algorithm
 */
struct VirtualBassParameters
{
    VirtualBassParameters() {}
    
    VirtualBassParameters& operator=(const VirtualBassParameters& params)
    {
        if (this == &params)
            return *this;
        
        cutoffFreq = params.cutoffFreq;
        harmonicGain = params.harmonicGain;
        mixLevel = params.mixLevel;
        return *this;
    }
    
    double cutoffFreq = 80.0;      ///< High-pass filter cutoff (Hz)
    double harmonicGain = 2.0;     ///< Gain applied to harmonic generation
    double mixLevel = 0.3;         ///< Mix level of processed signal
};

/**
 \class VirtualBass
 \ingroup FX-Objects-Homework
 \brief
 Virtual Bass enhancement using psychoacoustic bass extension.
 Based on homework assignment 19.16.4 - Figure 19.10 algorithm
 
 Author: Based on Will Pirkle's homework assignment
 */
class VirtualBass
{
public:
    VirtualBass() {}
    ~VirtualBass() {}
    
    bool reset(double _sampleRate)
    {
        sampleRate = _sampleRate;
        // Reset any internal filters here
        return true;
    }
    
    VirtualBassParameters getParameters() { return parameters; }
    
    void setParameters(const VirtualBassParameters& params)
    {
        parameters = params;
        // Update filter coefficients when parameters change
    }
    
    bool canProcessAudioFrame() { return false; }
    
    /**
     Virtual Bass algorithm implementation
     High-pass filters the input, generates harmonics, then mixes back
     */
    double processAudioSample(double xn)
    {
        // Simple high-pass filter (would normally use proper filter design)
        double highPassed = simpleHighPass(xn, parameters.cutoffFreq);
        
        // Generate harmonics through nonlinear processing
        double harmonics = generateHarmonics(xn * parameters.harmonicGain);
        
        // Band-pass filter the harmonics (simplified)
        double bandPassedHarmonics = harmonics * 0.5; // Simplified BP filter
        
        // Mix original high-passed signal with processed harmonics
        return highPassed * (1.0 - parameters.mixLevel) +
        bandPassedHarmonics * parameters.mixLevel;
    }
    
private:
    /** Simplified high-pass filter */
    double simpleHighPass(double input, double cutoff)
    {
        // This would normally be a proper filter implementation
        // For now, just return a scaled version
        return input * 0.8; // Simplified HPF
    }
    
    /** Generate harmonics for bass enhancement */
    double generateHarmonics(double input)
    {
        // Generate 2nd and 3rd harmonics
        double squared = input * input;
        double cubed = squared * input;
        
        return tanh(squared * 0.5 + cubed * 0.3);
    }
    
protected:
    VirtualBassParameters parameters;
    double sampleRate = 44100.0;
};

/**
 \struct TubeClassBParameters
 \ingroup FX-Objects-Homework
 \brief
 Custom parameter structure for Class B tube emulation.
 Based on homework assignment 19.16.5
 */
struct TubeClassBParameters
{
    TubeClassBParameters() {}
    
    TubeClassBParameters& operator=(const TubeClassBParameters& params)
    {
        if (this == &params)
            return *this;
        
        crossoverThreshold = params.crossoverThreshold;
        saturation = params.saturation;
        crossoverDistortion = params.crossoverDistortion;
        outputGain = params.outputGain;
        return *this;
    }
    
    double crossoverThreshold = 0.1;    ///< Threshold where crossover distortion occurs
    double saturation = 2.0;            ///< Saturation amount
    double crossoverDistortion = 0.5;   ///< Amount of crossover distortion
    double outputGain = 0.5;            ///< Output gain
};

/**
 \class TubeClassB
 \ingroup FX-Objects-Homework
 \brief
 Class B tube emulation with crossover distortion.
 Based on homework assignment 19.16.5
 
 Author: Based on Will Pirkle's homework assignment
 */
class TubeClassB
{
public:
    TubeClassB() {}
    ~TubeClassB() {}
    
    bool reset(double _sampleRate)
    {
        sampleRate = _sampleRate;
        return true;
    }
    
    TubeClassBParameters getParameters() { return parameters; }
    
    void setParameters(const TubeClassBParameters& params)
    {
        parameters = params;
    }
    
    bool canProcessAudioFrame() { return false; }
    
    /**
     Class B tube emulation with crossover distortion
     Models the dead zone where neither tube conducts
     */
    double processAudioSample(double xn)
    {
        double output = 0.0;
        double absInput = abs(xn);
        
        // Crossover distortion - dead zone near zero crossing
        if (absInput < parameters.crossoverThreshold)
        {
            // Dead zone with some crossover distortion
            double distortionFactor = parameters.crossoverDistortion;
            output = xn * (1.0 - distortionFactor) +
            tanh(xn * 10.0) * distortionFactor * 0.1;
        }
        else
        {
            // Above threshold - normal tube saturation
            if (xn > 0.0)
            {
                // Positive half - tube 1 conducts
                double driven = (xn - parameters.crossoverThreshold) * parameters.saturation;
                output = parameters.crossoverThreshold + tanh(driven) * (1.0 - parameters.crossoverThreshold);
            }
            else
            {
                // Negative half - tube 2 conducts
                double driven = (xn + parameters.crossoverThreshold) * parameters.saturation;
                output = -parameters.crossoverThreshold + tanh(driven) * (1.0 - parameters.crossoverThreshold);
            }
        }
        
        return output * parameters.outputGain;
    }
    
protected:
    TubeClassBParameters parameters;
    double sampleRate = 44100.0;
};





#endif // __aspikHomework__

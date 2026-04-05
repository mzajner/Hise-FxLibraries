#pragma once
#include <JuceHeader.h>
#include <cstdint>
#include <cmath>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstring>

namespace project
{

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace juce;
using namespace hise;
using namespace scriptnode;

namespace FunctionsClasses {

//------------------------------------------------------------------------------
// DelaySmooth: A delay line with smooth crossfading between two integer delay
// lines to produce a click-free, Doppler-free delay variation.
// Fixed types: head = uint16_t and sample type = float.
class DelaySmooth {
private:
    const size_t bufferLen = 2ul << (8 * sizeof(uint16_t) - 1);
    size_t delay = 0;
    size_t interpolationTime = 1024;
    size_t lowerDelay = 0;
    size_t upperDelay = 0;
    float interpolation = 0.0f;
    float interpolationStep = 1.0f / float(interpolationTime);
    float increment = interpolationStep;
    uint16_t lowerReadPtr = 0;
    uint16_t upperReadPtr = 0;
    uint16_t writePtr = 0;
    std::vector<float> bufferLeft;
    std::vector<float> bufferRight;
public:
    void SetDelay(size_t _delay) { delay = _delay; }
    void SetInterpolationTime(size_t _interpTime) {
        interpolationTime = std::max<size_t>(1, _interpTime);
        interpolationStep = 1.0f / float(interpolationTime);
    }
    void Reset() {
        std::fill(bufferLeft.begin(), bufferLeft.end(), 0.0f);
        std::fill(bufferRight.begin(), bufferRight.end(), 0.0f);
    }
    void Process(float** xVec, float** yVec, size_t vecLen) {
        float* xLeft = xVec[0];
        float* xRight = xVec[1];
        float* yLeft = yVec[0];
        float* yRight = yVec[1];
        for (size_t n = 0; n < vecLen; n++) {
            bufferLeft[writePtr] = xLeft[n];
            bufferRight[writePtr] = xRight[n];
            bool lowerReach = (interpolation == 0.0f);
            bool upperReach = (interpolation == 1.0f);
            bool lowerDelayChanged = (delay != lowerDelay);
            bool upperDelayChanged = (delay != upperDelay);
            bool startDownwardInterp = (upperReach && upperDelayChanged);
            bool startUpwardInterp = (lowerReach && lowerDelayChanged);
            float incrementPathsUp[2] = { increment, interpolationStep };
            float incrementPathsDown[2] = { incrementPathsUp[startUpwardInterp], -interpolationStep };
            increment = incrementPathsDown[startDownwardInterp];
            size_t lowerDelayPaths[2] = { lowerDelay, delay };
            size_t upperDelayPaths[2] = { upperDelay, delay };
            lowerDelay = lowerDelayPaths[upperReach];
            upperDelay = upperDelayPaths[lowerReach];
            // Use explicit bitwise AND for modulo (bufferLen = 65536)
            lowerReadPtr = static_cast<uint16_t>(writePtr - lowerDelay) & 0xFFFF;
            upperReadPtr = static_cast<uint16_t>(writePtr - upperDelay) & 0xFFFF;
            writePtr++;
            interpolation = std::max(0.0f, std::min(1.0f, interpolation + increment));
            yLeft[n] = interpolation * (bufferLeft[upperReadPtr] - bufferLeft[lowerReadPtr]) + bufferLeft[lowerReadPtr];
            yRight[n] = interpolation * (bufferRight[upperReadPtr] - bufferRight[lowerReadPtr]) + bufferRight[lowerReadPtr];
        }
    }
    DelaySmooth() {
        bufferLeft.resize(bufferLen);
        bufferRight.resize(bufferLen);
    }
    DelaySmooth(size_t _delay, size_t _interpTime) {
        bufferLeft.resize(bufferLen);
        bufferRight.resize(bufferLen);
        delay = _delay;
        interpolationTime = std::max<size_t>(1, _interpTime);
        interpolationStep = 1.0f / float(interpolationTime);
    }
};

//------------------------------------------------------------------------------
// ExpSmootherCascade: Cascaded one-pole exponential smoothers (4 stages)
// with separate attack and release coefficients.
class ExpSmootherCascade {
private:
    static constexpr size_t stages = 4;
    const float coeffCorrection = 1.0f / std::sqrt(std::pow(2.0f, 1.0f / float(stages)) - 1.0f);
    const float epsilon = std::numeric_limits<float>::epsilon();
    float SR = 48000.0f;
    float T = 1.0f / SR;
    const float twoPiC = 2.0f * static_cast<float>(M_PI) * coeffCorrection;
    float twoPiCT = twoPiC * T;
    float attTime = 0.001f;
    float relTime = 0.01f;
    float attCoeff = std::exp(-twoPiCT / attTime);
    float relCoeff = std::exp(-twoPiCT / relTime);
    float coeff[2] = { relCoeff, attCoeff };
    float output[stages] = { 0.0f, 0.0f, 0.0f, 0.0f };
public:
    void SetSR(float _SR) {
        SR = std::max(_SR, 1.0f);
        T = 1.0f / SR;
        twoPiCT = twoPiC * T;
    }
    void SetAttTime(float _attTime) {
        attTime = std::max(epsilon, _attTime);
        attCoeff = std::exp(-twoPiCT / attTime);
        coeff[1] = attCoeff;
    }
    void SetRelTime(float _relTime) {
        relTime = std::max(epsilon, _relTime);
        relCoeff = std::exp(-twoPiCT / relTime);
        coeff[0] = relCoeff;
    }
    void Reset() { std::memset(output, 0, sizeof(output)); }
    void Process(float* xVec, float* yVec, size_t vecLen) {
        for (size_t n = 0; n < vecLen; n++) {
            float input = xVec[n];
            // Unrolled stage 0
            bool isAttackPhase = (input > output[0]);
            float coeffVal = isAttackPhase ? attCoeff : relCoeff;
            output[0] = input + coeffVal * (output[0] - input);
            input = output[0];
            // Unrolled stage 1
            isAttackPhase = (input > output[1]);
            coeffVal = isAttackPhase ? attCoeff : relCoeff;
            output[1] = input + coeffVal * (output[1] - input);
            input = output[1];
            // Unrolled stage 2
            isAttackPhase = (input > output[2]);
            coeffVal = isAttackPhase ? attCoeff : relCoeff;
            output[2] = input + coeffVal * (output[2] - input);
            input = output[2];
            // Unrolled stage 3
            isAttackPhase = (input > output[3]);
            coeffVal = isAttackPhase ? attCoeff : relCoeff;
            output[3] = input + coeffVal * (output[3] - input);
            yVec[n] = output[3];
        }
    }
    ExpSmootherCascade() {}
    ExpSmootherCascade(float _SR, float _attTime, float _relTime) {
        SR = std::max(_SR, 1.0f);
        T = 1.0f / SR;
        twoPiCT = twoPiC * T;
        attTime = std::max(epsilon, _attTime);
        relTime = std::max(epsilon, _relTime);
        attCoeff = std::exp(-twoPiCT / attTime);
        relCoeff = std::exp(-twoPiCT / relTime);
        coeff[0] = relCoeff;
        coeff[1] = attCoeff;
    }
};

//------------------------------------------------------------------------------
// PeakHoldCascade: Cascaded peak-holders (8 stages fixed) to approximate a max filter.
// The cascade splits the hold time to detect secondary peaks.
class PeakHoldCascade {
private:
    static constexpr size_t stages = 8;
    float SR = 48000.0f;
    float holdTime = 0.001f;
    const float oneOverStages = 1.0f / float(stages);
    size_t holdTimeSamples = std::rint(holdTime * oneOverStages * SR);
    size_t timer[stages];
    float output[stages];
public:
    void SetSR(float _SR) {
        SR = std::max(_SR, 1.0f);
        holdTimeSamples = std::rint(holdTime * oneOverStages * SR);
    }
    void SetHoldTime(float _holdTime) {
        holdTime = std::max(0.0f, _holdTime);
        holdTimeSamples = std::rint(holdTime * oneOverStages * SR);
    }
    void Reset() {
        std::memset(timer, 0, sizeof(timer));
        std::memset(output, 0, sizeof(output));
    }
    void Process(float* xVec, float* yVec, size_t vecLen) {
        for (size_t n = 0; n < vecLen; n++) {
            float input = std::fabs(xVec[n]);
            bool release;
            // Unrolled stage 0
            release = (input >= output[0]) || (timer[0] >= holdTimeSamples);
            timer[0] = release ? 0 : (timer[0] + 1);
            output[0] = release ? input : output[0];
            input = output[0];
            // Unrolled stage 1
            release = (input >= output[1]) || (timer[1] >= holdTimeSamples);
            timer[1] = release ? 0 : (timer[1] + 1);
            output[1] = release ? input : output[1];
            input = output[1];
            // Unrolled stage 2
            release = (input >= output[2]) || (timer[2] >= holdTimeSamples);
            timer[2] = release ? 0 : (timer[2] + 1);
            output[2] = release ? input : output[2];
            input = output[2];
            // Unrolled stage 3
            release = (input >= output[3]) || (timer[3] >= holdTimeSamples);
            timer[3] = release ? 0 : (timer[3] + 1);
            output[3] = release ? input : output[3];
            input = output[3];
            // Unrolled stage 4
            release = (input >= output[4]) || (timer[4] >= holdTimeSamples);
            timer[4] = release ? 0 : (timer[4] + 1);
            output[4] = release ? input : output[4];
            input = output[4];
            // Unrolled stage 5
            release = (input >= output[5]) || (timer[5] >= holdTimeSamples);
            timer[5] = release ? 0 : (timer[5] + 1);
            output[5] = release ? input : output[5];
            input = output[5];
            // Unrolled stage 6
            release = (input >= output[6]) || (timer[6] >= holdTimeSamples);
            timer[6] = release ? 0 : (timer[6] + 1);
            output[6] = release ? input : output[6];
            input = output[6];
            // Unrolled stage 7
            release = (input >= output[7]) || (timer[7] >= holdTimeSamples);
            timer[7] = release ? 0 : (timer[7] + 1);
            output[7] = release ? input : output[7];
            yVec[n] = output[7];
        }
    }
    PeakHoldCascade() { Reset(); }
    PeakHoldCascade(float _SR, float _holdTime) {
        SR = std::max(_SR, 1.0f);
        holdTime = _holdTime;
        holdTimeSamples = std::rint(holdTime * oneOverStages * SR);
        Reset();
    }
};

//------------------------------------------------------------------------------
// Limiter: Lookahead peak-limiter combining DelaySmooth, PeakHoldCascade, and
// ExpSmootherCascade. Computes a stereo envelope and applies a gain to keep
// signal peaks below a given threshold.
template<typename real>
class Limiter {
private:
    float SR = 48000.0f;
    float T = 1.0f / SR;
    const float twoPi = 2.0f * static_cast<float>(M_PI);
    const float epsilon = std::numeric_limits<float>::epsilon();
    const float smoothParamCutoff = 20.0f;
    float attack = 0.01f;
    float hold = 0.0f;
    float release = 0.05f;
    float dBThreshold = -6.0f;
    float linThreshold = std::pow(10.0f, dBThreshold * 0.05f);
    float dBPreGain = 0.0f;
    float linPreGain = 1.0f;
    float smoothPreGain = 0.0f;
    float smoothThreshold = 0.0f;
    float smoothParamCoeff = std::exp(-twoPi * smoothParamCutoff * T);
    size_t lookaheadDelay = 0;
    DelaySmooth delay;
    static constexpr size_t numberOfPeakHoldSections = 8;
    static constexpr size_t numberOfSmoothSections = 4;
    const float oneOverPeakSections = 1.0f / float(numberOfPeakHoldSections);
    PeakHoldCascade peakHolder;
    ExpSmootherCascade expSmoother;
public:
    void SetSR(float _SR) {
        SR = std::max(_SR, 1.0f);
        T = 1.0f / SR;
        smoothParamCoeff = std::exp(-twoPi * smoothParamCutoff * T);
        peakHolder.SetSR(SR);
        expSmoother.SetSR(SR);
    }
    void SetAttTime(float _attack) {
        attack = std::max(epsilon, _attack);
        lookaheadDelay = std::rint(attack * oneOverPeakSections * SR) * numberOfPeakHoldSections;
        delay.SetDelay(lookaheadDelay);
        delay.SetInterpolationTime(lookaheadDelay);
        expSmoother.SetAttTime(attack);
        peakHolder.SetHoldTime(attack + hold);
    }
    void SetHoldTime(float _hold) {
        hold = std::max(0.0f, _hold);
        peakHolder.SetHoldTime(attack + hold);
    }
    void SetRelTime(float _release) {
        release = std::max(epsilon, _release);
        expSmoother.SetRelTime(release);
    }
    void SetThreshold(float _threshold) {
        dBThreshold = std::max(-120.0f, _threshold);
        linThreshold = std::pow(10.0f, dBThreshold * 0.05f);
    }
    void SetPreGain(float _preGain) {
        dBPreGain = _preGain;
        linPreGain = std::pow(10.0f, dBPreGain * 0.05f);
    }
    void Reset() {
        delay.Reset();
        peakHolder.Reset();
        expSmoother.Reset();
    }
    // Process takes separate input and output stereo buffers.
    // The design uses an in-place delay so the input buffer is overwritten.
    void Process(float** xVec, float** yVec, size_t vecLen) {
        // Get channel pointers once outside loops.
        float* xLeft = xVec[0];
        float* xRight = xVec[1];
        float* yLeft = yVec[0];
        float* yRight = yVec[1];
        // Merge pre-gain smoothing and envelope computation.
        for (size_t n = 0; n < vecLen; n++) {
            smoothPreGain = linPreGain + smoothParamCoeff * (smoothPreGain - linPreGain);
            xLeft[n] *= smoothPreGain;
            xRight[n] *= smoothPreGain;
            yLeft[n] = std::max(std::fabs(xLeft[n]), std::fabs(xRight[n]));
        }
        // Process envelope with peak-hold cascade.
        peakHolder.Process(yLeft, yLeft, vecLen);
        // Smooth and clip envelope to threshold.
        for (size_t n = 0; n < vecLen; n++) {
            smoothThreshold = linThreshold + smoothParamCoeff * (smoothThreshold - linThreshold);
            yLeft[n] = std::max(yLeft[n], smoothThreshold);
            yRight[n] = smoothThreshold;
        }
        // Smooth envelope with exponential cascade.
        expSmoother.Process(yLeft, yLeft, vecLen);
        // Apply lookahead delay (in-place).
        delay.Process(xVec, xVec, vecLen);
        // Compute attenuation gain and apply to delayed signal in one loop.
        for (size_t n = 0; n < vecLen; n++) {
            float gain = yRight[n] / yLeft[n];
            yLeft[n] = gain * xLeft[n];
            yRight[n] = gain * xRight[n];
        }
    }
    Limiter() {}
    Limiter(float _SR, float _dBPreGain, float _attack, float _hold, float _release, float _dBThreshold) {
        SR = std::max(_SR, 1.0f);
        dBPreGain = _dBPreGain;
        attack = std::max(epsilon, _attack);
        hold = std::max(0.0f, _hold);
        release = std::max(epsilon, _release);
        dBThreshold = std::max(-120.0f, _dBThreshold);
    }
};

} // end namespace FunctionsClasses

//------------------------------------------------------------------------------
// SNEX Node - Stereo Limiter Node Implementation
//------------------------------------------------------------------------------
template <int NV>
struct peakLimiter : public data::base
{
    SNEX_NODE(peakLimiter);
    
    struct MetadataClass
    {
        SN_NODE_ID("peakLimiter");
    };
    
    // Node Properties
    static constexpr bool isModNode() { return false; }
    static constexpr bool isPolyphonic() { return NV > 1; }
    static constexpr bool hasTail() { return false; }
    static constexpr bool isSuspendedOnSilence() { return false; }
    static constexpr int getFixChannelAmount() { return 2; }
    
    static constexpr int NumTables = 0;
    static constexpr int NumSliderPacks = 0;
    static constexpr int NumAudioFiles = 0;
    static constexpr int NumFilters = 0;
    static constexpr int NumDisplayBuffers = 0;
    
    // Create an instance of our DSP Limiter
    FunctionsClasses::Limiter<float> limiter;
    
    // Scratch buffers to avoid per-block allocation.
private:
    std::vector<float> scratchInLeft, scratchInRight;
    std::vector<float> scratchOutLeft, scratchOutRight;
public:
    //--------------------------------------------------------------------------
    // Main Processing Functions
    //--------------------------------------------------------------------------
    void prepare(PrepareSpecs specs)
    {
        float sampleRate = specs.sampleRate;
        limiter.SetSR(sampleRate);
        limiter.Reset();
        // Preallocate scratch buffers (use maximum BlockSize if available, otherwise default to 512).
        int blockSize = (specs.blockSize > 0) ? specs.blockSize : 512;
        scratchInLeft.resize(blockSize);
        scratchInRight.resize(blockSize);
        scratchOutLeft.resize(blockSize);
        scratchOutRight.resize(blockSize);
    }
    
    void reset() {}
    
    template <typename ProcessDataType>
    inline void process(ProcessDataType& data)
    {
        auto& fixData = data.template as<ProcessData<getFixChannelAmount()>>();
        auto audioBlock = fixData.toAudioBlock();
        float* leftChannelData = audioBlock.getChannelPointer(0);
        float* rightChannelData = audioBlock.getChannelPointer(1);
        int numSamples = data.getNumSamples();
        
        juce::FloatVectorOperations::copy(scratchInLeft.data(), leftChannelData, numSamples);
        juce::FloatVectorOperations::copy(scratchInRight.data(), rightChannelData, numSamples);
        
        float* inBuffers[2] = { scratchInLeft.data(), scratchInRight.data() };
        float* outBuffers[2] = { scratchOutLeft.data(), scratchOutRight.data() };
        
        limiter.Process(inBuffers, outBuffers, numSamples);
        
        juce::FloatVectorOperations::copy(leftChannelData, scratchOutLeft.data(), numSamples);
        juce::FloatVectorOperations::copy(rightChannelData, scratchOutRight.data(), numSamples);
    }
    
    //--------------------------------------------------------------------------
    // Parameter Handling
    //--------------------------------------------------------------------------
    template <int P>
    void setParameter(double v)
    {
        if (P == 0) {
            limiter.SetPreGain(static_cast<float>(v));
        }
        else if (P == 1) {
            // Convert from ms to seconds.
            limiter.SetAttTime(static_cast<float>(v * 0.001));
        }
        else if (P == 2) {
            limiter.SetHoldTime(static_cast<float>(v * 0.001));
        }
        else if (P == 3) {
            limiter.SetRelTime(static_cast<float>(v * 0.001));
        }
        else if (P == 4) {
            limiter.SetThreshold(static_cast<float>(v));
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("PreGain (dB)", { -24.0, 24.0, 0.1 });
            registerCallback<0>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Attack (ms)", { 1.0, 500.0, 1.0 });
            registerCallback<1>(p);
            p.setDefaultValue(10.0);
            p.setSkewForCentre(80.0f);
            data.add(std::move(p));
        }
        {
            parameter::data p("Hold (ms)", { 0.0, 100.0, 1.0 });
            registerCallback<2>(p);
            p.setDefaultValue(5.0);
            p.setSkewForCentre(30.0f);
            data.add(std::move(p));
        }
        {
            parameter::data p("Release (ms)", { 1.0, 2500.0, 1.0 });
            registerCallback<3>(p);
            p.setDefaultValue(80.0);
            p.setSkewForCentre(800.0f);
            data.add(std::move(p));
        }
        {
            parameter::data p("Ceiling (dB)", { -60.0, 0.0, 0.1 });
            registerCallback<4>(p);
            p.setDefaultValue(-6.0);
            data.add(std::move(p));
        }
    }
    
    void setExternalData(const ExternalData& ed, int index)
    {
        // Not needed.
    }
    
    void handleHiseEvent(HiseEvent& e)
    {
        // Not needed.
    }
    
    template <typename FrameDataType>
    void processFrame(FrameDataType& data)
    {
        // Not needed.
    }
};

} // end namespace project

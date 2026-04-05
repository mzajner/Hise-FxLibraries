// ==================================| VHS Playhead Loss Effects with Azimuth |==================================

#pragma once
#include <JuceHeader.h>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV> struct vhs_Loss: public data::base
{
    // Metadata Definitions ------------------------------------------------------------------------
    
    SNEX_NODE(vhs_Loss);
    
    struct MetadataClass
    {
        SN_NODE_ID("vhs_Loss");
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
    vhs_Loss()
    {
        sampleRate = 44100.0;
        tapeSpeed = 0.5; // 0.0 = VHS LP (slow), 1.0 = VHS SP (fast)
        wearAmount = 0.3; // Amount of tape wear/aging
        
        // Initialize filter states
        for (int ch = 0; ch < 2; ++ch)
        {
            // Gap loss filter states (multiple stages for steep rolloff)
            gapLoss1[ch] = gapLoss2[ch] = gapLoss3[ch] = 0.0f;
            
            // Spacing loss filter states
            spacingLoss1[ch] = spacingLoss2[ch] = 0.0f;
            
            // Head bump filter states (low frequency boost)
            headBump1[ch] = headBump2[ch] = 0.0f;
            
            // Thickness loss states (notch filter)
            thicknessDelay[ch] = 0.0f;
            thicknessState[ch] = 0.0f;
        }
        
        // Initialize azimuth delay buffers
        azimuthDelayL.setSize(1, 4096); // Enough for reasonable azimuth delays
        azimuthDelayR.setSize(1, 4096);
        azimuthDelayL.clear();
        azimuthDelayR.clear();
        azimuthWritePos = 0;
        currentAzimuthDelay = 0.0f;
        targetAzimuthDelay = 0.0f;
        azimuthSmoothCoeff = 0.999f; // Will be recalculated in prepare()
        
        updateFilterCoefficients();
    }
    
    // Scriptnode Callbacks ------------------------------------------------------------------------
    
    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;
        
        // Calculate azimuth smoothing coefficient (50ms smoothing)
        azimuthSmoothCoeff = std::exp(-1.0f / (0.05f * (float)sampleRate));
        azimuthSmoothCoeff = jlimit(0.9f, 0.999f, azimuthSmoothCoeff);
        
        updateFilterCoefficients();
        reset();
    }
    
    void reset()
    {
        for (int ch = 0; ch < 2; ++ch)
        {
            gapLoss1[ch] = gapLoss2[ch] = gapLoss3[ch] = 0.0f;
            spacingLoss1[ch] = spacingLoss2[ch] = 0.0f;
            headBump1[ch] = headBump2[ch] = 0.0f;
            thicknessDelay[ch] = 0.0f;
            thicknessState[ch] = 0.0f;
        }
        
        azimuthDelayL.clear();
        azimuthDelayR.clear();
        azimuthWritePos = 0;
        currentAzimuthDelay = targetAzimuthDelay;
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
        float leftSample = data[0];
        float rightSample = data[1];
        
        // === 1. Apply Frequency Response Effects ===
        leftSample = applyHeadBump(leftSample, 0);
        leftSample = applyGapLoss(leftSample, 0);
        leftSample = applySpacingLoss(leftSample, 0);
        leftSample = applyThicknessLoss(leftSample, 0);
        
        rightSample = applyHeadBump(rightSample, 1);
        rightSample = applyGapLoss(rightSample, 1);
        rightSample = applySpacingLoss(rightSample, 1);
        rightSample = applyThicknessLoss(rightSample, 1);
        
        // === 2. Apply Azimuth Delay Effect ===
        processAzimuthDelay(leftSample, rightSample);
        
        data[0] = leftSample;
        data[1] = rightSample;
    }
    
    int handleModulation(double& value) { return 0; }
    void setExternalData(const ExternalData& data, int index) {}
    
    // Parameter Functions -------------------------------------------------------------------------
    
    template <int P> void setParameter(double v)
    {
        if (P == 0)
        {
            // Tape Speed: 0.0 = VHS LP (very slow), 1.0 = VHS SP (standard)
            tapeSpeed = jlimit(0.0f, 1.0f, (float)v);
            updateFilterCoefficients();
        }
        else if (P == 1)
        {
            // Wear Amount: 0.0 = new tape, 1.0 = heavily worn/aged tape
            wearAmount = jlimit(0.0f, 1.0f, (float)v);
            updateFilterCoefficients();
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("Tape Speed", { 0.0, 1.0 });
            registerCallback<0>(p);
            p.setDefaultValue(0.5); // Medium speed
            data.add(std::move(p));
        }
        {
            parameter::data p("Tape Wear", { 0.0, 1.0 });
            registerCallback<1>(p);
            p.setDefaultValue(0.3); // Some wear
            data.add(std::move(p));
        }
    }
    
private:
    double sampleRate;
    float tapeSpeed;  // 0.0 = LP, 1.0 = SP
    float wearAmount; // 0.0 = new, 1.0 = worn
    
    // Filter states per channel (your existing implementation)
    float gapLoss1[2], gapLoss2[2], gapLoss3[2];
    float spacingLoss1[2], spacingLoss2[2];
    float headBump1[2], headBump2[2];
    float thicknessDelay[2], thicknessState[2];
    
    // Filter coefficients (your existing implementation)
    float gapLossCoeff1, gapLossCoeff2, gapLossCoeff3;
    float spacingLossCoeff1, spacingLossCoeff2;
    float headBumpCoeff1, headBumpCoeff2;
    float thicknessCoeff, thicknessGain;
    
    // === NEW: Azimuth Processing ===
    AudioBuffer<float> azimuthDelayL, azimuthDelayR;
    int azimuthWritePos;
    float currentAzimuthDelay, targetAzimuthDelay;
    float azimuthSmoothCoeff;
    
    // VHS Constants (based on real VHS specifications)
    static constexpr float VHS_TAPE_WIDTH = 0.0127f; // VHS tape width: 12.7mm
    static constexpr float VHS_LP_SPEED = 0.0233f;   // VHS LP: 2.33 cm/s
    static constexpr float VHS_SP_SPEED = 0.0466f;   // VHS SP: 4.66 cm/s
    
    // === Filter Coefficient Calculation (your existing code) ===
    void updateFilterCoefficients()
    {
        // Your existing frequency response code...
        float speedFactor = 0.3f + tapeSpeed * 0.7f;
        float wearFactor = 1.0f - wearAmount * 0.4f;
        
        // Gap Loss
        float gapFreq1 = (6000.0f + speedFactor * 8000.0f) * wearFactor;
        float gapFreq2 = (4000.0f + speedFactor * 6000.0f) * wearFactor;
        float gapFreq3 = (2000.0f + speedFactor * 4000.0f) * wearFactor;
        
        gapLossCoeff1 = calculateLowPassCoeff(gapFreq1);
        gapLossCoeff2 = calculateLowPassCoeff(gapFreq2);
        gapLossCoeff3 = calculateLowPassCoeff(gapFreq3);
        
        // Spacing Loss
        float spacingFreq1 = (8000.0f + speedFactor * 4000.0f) * wearFactor;
        float spacingFreq2 = (12000.0f + speedFactor * 6000.0f) * wearFactor;
        
        spacingLossCoeff1 = calculateLowPassCoeff(spacingFreq1);
        spacingLossCoeff2 = calculateLowPassCoeff(spacingFreq2);
        
        // Head Bump
        float bumpFreq1 = 80.0f + speedFactor * 40.0f;
        float bumpFreq2 = 120.0f + speedFactor * 60.0f;
        
        headBumpCoeff1 = calculateHighPassCoeff(bumpFreq1);
        headBumpCoeff2 = calculateHighPassCoeff(bumpFreq2);
        
        // Thickness Loss
        float thicknessFreq = 3000.0f + speedFactor * 2000.0f;
        thicknessCoeff = std::exp(-2.0f * float(M_PI) * thicknessFreq / (float)sampleRate);
        thicknessGain = 0.1f + wearAmount * 0.2f;
        
        // === NEW: Calculate Azimuth Delay ===
        calculateAzimuthDelay();
    }
    
    void calculateAzimuthDelay()
    {
        // VHS azimuth misalignment increases with wear and varies by speed
        // Typical VHS azimuth errors: 0-30 degrees (consumer equipment)
        
        // Base azimuth error increases with wear (0-20 degrees)
        float azimuthAngleDegrees = wearAmount * 20.0f;
        
        // Speed affects the severity (LP mode has worse tracking)
        float speedEffect = 0.5f + (1.0f - tapeSpeed) * 0.5f; // LP mode = worse
        azimuthAngleDegrees *= speedEffect;
        
        // Convert to radians
        float azimuthAngleRad = azimuthAngleDegrees * float(M_PI) / 180.0f;
        
        // Calculate physical delay based on VHS geometry
        float currentTapeSpeed = VHS_LP_SPEED + tapeSpeed * (VHS_SP_SPEED - VHS_LP_SPEED);
        float delayDistance = VHS_TAPE_WIDTH * std::sin(azimuthAngleRad);
        float delayTime = delayDistance / currentTapeSpeed; // seconds
        
        targetAzimuthDelay = delayTime * (float)sampleRate; // convert to samples
        
        // Limit to reasonable range (0-10ms maximum)
        targetAzimuthDelay = jlimit(0.0f, (float)sampleRate * 0.01f, targetAzimuthDelay);
    }
    
    // === NEW: Azimuth Delay Processing ===
    void processAzimuthDelay(float& leftSample, float& rightSample)
    {
        // Smooth the delay parameter to avoid clicking
        currentAzimuthDelay = currentAzimuthDelay * azimuthSmoothCoeff +
        targetAzimuthDelay * (1.0f - azimuthSmoothCoeff);
        
        // Write samples to delay buffers
        azimuthDelayL.setSample(0, azimuthWritePos, leftSample);
        azimuthDelayR.setSample(0, azimuthWritePos, rightSample);
        
        // VHS typically has one channel delayed relative to the other
        // We'll delay the right channel (common in consumer VHS)
        
        if (currentAzimuthDelay > 0.1f) // Only apply if delay is significant
        {
            // Calculate read position for delayed channel
            float readPosFloat = (float)azimuthWritePos - currentAzimuthDelay;
            
            // Wrap around buffer
            while (readPosFloat < 0.0f)
                readPosFloat += azimuthDelayR.getNumSamples();
            
            // Linear interpolation for smooth delay
            int readPos1 = (int)readPosFloat;
            int readPos2 = (readPos1 + 1) % azimuthDelayR.getNumSamples();
            float fraction = readPosFloat - (float)readPos1;
            
            float sample1 = azimuthDelayR.getSample(0, readPos1);
            float sample2 = azimuthDelayR.getSample(0, readPos2);
            
            rightSample = sample1 + fraction * (sample2 - sample1);
        }
        // Left channel is undelayed (direct output)
        
        // Advance write position
        azimuthWritePos = (azimuthWritePos + 1) % azimuthDelayL.getNumSamples();
    }
    
    // === Helper Functions (your existing code) ===
    inline float calculateLowPassCoeff(float freq)
    {
        float omega = 2.0f * float(M_PI) * freq / (float)sampleRate;
        return 1.0f - std::exp(-omega);
    }
    
    inline float calculateHighPassCoeff(float freq)
    {
        float omega = 2.0f * float(M_PI) * freq / (float)sampleRate;
        return std::exp(-omega);
    }
    
    // === Playhead Loss Effects (your existing implementations) ===
    
    inline float applyHeadBump(float input, int channel)
    {
        headBump1[channel] = headBump1[channel] * headBumpCoeff1 + input * (1.0f - headBumpCoeff1);
        headBump2[channel] = headBump2[channel] * headBumpCoeff2 + headBump1[channel] * (1.0f - headBumpCoeff2);
        
        float boost = input - headBump2[channel];
        return input + boost * 0.15f;
    }
    
    inline float applyGapLoss(float input, int channel)
    {
        gapLoss1[channel] += gapLossCoeff1 * (input - gapLoss1[channel]);
        gapLoss2[channel] += gapLossCoeff2 * (gapLoss1[channel] - gapLoss2[channel]);
        gapLoss3[channel] += gapLossCoeff3 * (gapLoss2[channel] - gapLoss3[channel]);
        
        return gapLoss3[channel];
    }
    
    inline float applySpacingLoss(float input, int channel)
    {
        spacingLoss1[channel] += spacingLossCoeff1 * (input - spacingLoss1[channel]);
        spacingLoss2[channel] += spacingLossCoeff2 * (spacingLoss1[channel] - spacingLoss2[channel]);
        
        return spacingLoss2[channel];
    }
    
    inline float applyThicknessLoss(float input, int channel)
    {
        thicknessState[channel] = thicknessState[channel] * thicknessCoeff + thicknessDelay[channel] * (1.0f - thicknessCoeff);
        
        float output = input - thicknessState[channel] * thicknessGain;
        thicknessDelay[channel] = input;
        
        return output;
    }
};
}

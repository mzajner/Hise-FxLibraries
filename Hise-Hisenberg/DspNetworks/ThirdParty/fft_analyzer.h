// ==================================| Research-Based FFT Analyzer for HISE |==================================
// Based on parametric EQ matching research and critical-band analysis principles
// References: Nercessian et al. (DAFx-20), critical-band theory, and perceptual audio processing

#pragma once
#include <JuceHeader.h>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

enum class GlobalCables
{
    dataCable = 0,
    band1_60Hz = 1,
    band2_150Hz = 2,
    band3_400Hz = 3,
    band4_1kHz = 4,
    band5_2k5Hz = 5,
    band6_6k3Hz = 6,
    band7_12kHz = 7,
    band8_18kHz = 8
};

using cable_manager_t = routing::global_cable_cpp_manager<SN_GLOBAL_CABLE(-389806413),
SN_GLOBAL_CABLE(1470972719),
SN_GLOBAL_CABLE(-761475428),
SN_GLOBAL_CABLE(128649861),
SN_GLOBAL_CABLE(1556767916),
SN_GLOBAL_CABLE(1903572655),
SN_GLOBAL_CABLE(-1500198798),
SN_GLOBAL_CABLE(-618956993),
SN_GLOBAL_CABLE(268725434)>;

template <int NV> struct fft_analyzer: public data::base, public cable_manager_t
{
    SNEX_NODE(fft_analyzer);
    
    struct MetadataClass
    {
        SN_NODE_ID("fft_analyzer");
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
    
    // FFT Configuration
    static constexpr int fftOrder = 12;
    static constexpr int fftSize = 1 << fftOrder;
    static constexpr int numBins = fftSize / 2 + 1;
    static constexpr int overlap = 4;
    static constexpr int hopSize = fftSize / overlap;
    
    // Analysis thresholds
    static constexpr float MIN_SIGNAL_THRESHOLD = 0.001f;
    static constexpr float MIN_PEAK_PROMINENCE = 1.2f;
    static constexpr float MIN_GAIN_DIFFERENCE = 1.5f;
    
    juce::dsp::FFT fft{fftOrder};
    juce::dsp::WindowingFunction<float> window{fftSize + 1,
        juce::dsp::WindowingFunction<float>::hann, false};
    
    struct ChannelProcessor {
        std::array<float, fftSize> inputFifo;
        std::array<float, fftSize * 2> fftData;
        int count = 0;
        int pos = 0;
    };
    
    std::array<ChannelProcessor, 2> channelProcessors;
    std::array<float, numBins> currentSpectrum;
    std::array<float, numBins> smoothedSpectrum;
    std::array<float, numBins> referenceSpectrum;
    
    struct DynamicEQBand {
        float frequency;
        float gain;
        float q;
        float bandwidth;
        bool enabled;
        bool isDynamic;
        float prominence;
    };
    
    std::array<DynamicEQBand, 8> outputBands;
    
    // Control parameters
    float blendAmount = 0.25f;
    float spectralSmoothing = 0.85f;
    
    // State variables
    bool isEnabled = false;
    bool isCapturing = false;
    bool hasReferenceSpectrum = false;
    double sampleRate = 44100.0;
    
    int frameProcessCount = 0;
    int cableUpdateCount = 0;
    float signalLevel = 0.0f;
    bool significantSignalDetected = false;
    int consecutiveSignalFrames = 0;
    int captureFrames = 0;
    int maxCaptureFrames = 400;
    
    fft_analyzer()
    {
        this->registerDataCallback<GlobalCables::dataCable>([](const var& data) {});
    }
    
    // Helper Functions
    
    float binToFrequency(int bin) const
    {
        return (float)bin * sampleRate / fftSize;
    }
    
    int frequencyToBin(float frequency) const
    {
        return std::min(numBins - 1, (int)(frequency * fftSize / sampleRate));
    }
    
    void initializeOutputBands()
    {
        for (int i = 0; i < 8; ++i) {
            outputBands[i] = {0.0f, 0.0f, 1.0f, 100.0f, false, false, 0.0f};
        }
    }
    
    float calculateLocalAverage(int centerBin, int windowSize) const
    {
        float sum = 0.0f;
        int count = 0;
        
        int start = std::max(1, centerBin - windowSize);
        int end = std::min(numBins - 1, centerBin + windowSize);
        
        for (int i = start; i <= end; ++i) {
            if (i != centerBin) {
                sum += smoothedSpectrum[i];
                count++;
            }
        }
        
        return count > 0 ? sum / count : 0.001f;
    }
    
    float calculateSpectralProminence(int binIndex, int windowSize) const
    {
        if (binIndex <= 0 || binIndex >= numBins) return 0.0f;
        
        float centerValue = smoothedSpectrum[binIndex];
        float localAverage = calculateLocalAverage(binIndex, windowSize);
        
        return centerValue / std::max(localAverage, 0.001f);
    }
    
    bool isSpectralPeak(int binIndex) const
    {
        if (binIndex <= 2 || binIndex >= numBins - 2) return false;
        
        float centerValue = smoothedSpectrum[binIndex];
        
        return (centerValue > smoothedSpectrum[binIndex - 1] &&
                centerValue > smoothedSpectrum[binIndex + 1] &&
                centerValue > smoothedSpectrum[binIndex - 2] &&
                centerValue > smoothedSpectrum[binIndex + 2]);
    }
    
    float interpolatePeakFrequency(int peakBin) const
    {
        if (peakBin <= 0 || peakBin >= numBins - 1)
            return binToFrequency(peakBin);
        
        float alpha = smoothedSpectrum[peakBin - 1];
        float beta = smoothedSpectrum[peakBin];
        float gamma = smoothedSpectrum[peakBin + 1];
        
        float denominator = (alpha - 2.0f * beta + gamma);
        if (std::abs(denominator) < 0.0001f)
            return binToFrequency(peakBin);
        
        float p = 0.5f * (alpha - gamma) / denominator;
        p = std::max(-0.5f, std::min(0.5f, p));
        
        return binToFrequency(peakBin + p);
    }
    
    float calculateOptimalQ(float frequency) const
    {
        if (frequency < 100.0f) return 0.7f;
        else if (frequency < 500.0f) return 1.0f;
        else if (frequency < 2000.0f) return 1.5f;
        else if (frequency < 5000.0f) return 2.2f;
        else if (frequency < 10000.0f) return 1.8f;
        else return 1.3f;
    }
    
    float getPerceptualWeight(float frequency) const
    {
        if (frequency < 50.0f) return 0.3f;
        else if (frequency < 200.0f) return 0.6f;
        else if (frequency < 500.0f) return 0.8f;
        else if (frequency < 2000.0f) return 1.0f;
        else if (frequency < 4000.0f) return 1.4f;
        else if (frequency < 8000.0f) return 1.1f;
        else if (frequency < 12000.0f) return 0.8f;
        else return 0.5f;
    }
    
    void performSpectralAnalysis()
    {
        if (!hasReferenceSpectrum) return;
        
        // NORMALIZE CURRENT INPUT TO UNIT RMS (match reference normalization)
        float curEnergy = 0.0f;
        int validBins = 0;
        for (int bin = 5; bin < numBins - 5; ++bin) {
            float freq = binToFrequency(bin);
            if (freq >= 20.0f && freq <= 18000.0f) {
                curEnergy += smoothedSpectrum[bin] * smoothedSpectrum[bin];
                validBins++;
            }
        }
        float curRMS = std::sqrt(curEnergy / validBins);
        float normFactor = 1.0f / std::max(curRMS, 0.0001f);
        
        std::vector<std::pair<float, float>> bands = {
            {50, 100}, {100, 200}, {200, 400}, {400, 800},
            {800, 1600}, {1600, 3200}, {3200, 6400},
            {6400, 12800}, {12800, 20000}
        };
        
        std::vector<std::tuple<float, float, float, float>> spectralCandidates;
        
        for (int i = 0; i < bands.size(); ++i) {
            const auto& [lowFreq, highFreq] = bands[i];
            int startBin = frequencyToBin(lowFreq);
            int endBin = frequencyToBin(highFreq);
            
            float refAvg = 0.0f;
            float curAvg = 0.0f;
            int count = 0;
            
            for (int bin = startBin; bin <= endBin; ++bin) {
                refAvg += referenceSpectrum[bin];
                curAvg += smoothedSpectrum[bin] * normFactor; // Normalize input
                count++;
            }
            
            refAvg /= count;
            curAvg /= count;
            
            if (refAvg < 0.0001f && curAvg < 0.0001f) continue;
            
            float correctionGainDB = 20.0f * std::log10(refAvg / std::max(curAvg, 0.0001f));
            
            // Force HPF for lowest band
            if (i == 0) {
                if (curAvg > 0.01f) {
                    correctionGainDB = std::min(correctionGainDB, -3.0f);
                    spectralCandidates.emplace_back(70.0f, correctionGainDB, 1.0f, 100.0f);
                    continue;
                }
            }
            
            if (std::abs(correctionGainDB) > MIN_GAIN_DIFFERENCE) {
                float centerFreq = std::sqrt(lowFreq * highFreq);
                float quality = std::abs(correctionGainDB);
                spectralCandidates.emplace_back(centerFreq, correctionGainDB, 1.0f, quality);
            }
        }
        
        selectOptimalEQBands(spectralCandidates);
    }
    
    void selectOptimalEQBands(const std::vector<std::tuple<float, float, float, float>>& candidates)
    {
        if (candidates.empty()) {
            for (int i = 0; i < 8; ++i) {
                outputBands[i].enabled = false;
                outputBands[i].gain = 0.0f;
            }
            return;
        }
        
        auto sortedCandidates = candidates;
        std::sort(sortedCandidates.begin(), sortedCandidates.end(),
                  [this](const auto& a, const auto& b) {
            float importanceA = std::get<3>(a) * std::abs(std::get<1>(a)) * getPerceptualWeight(std::get<0>(a));
            float importanceB = std::get<3>(b) * std::abs(std::get<1>(b)) * getPerceptualWeight(std::get<0>(b));
            return importanceA > importanceB;
        });
        
        std::vector<std::tuple<float, float, float, float>> finalBands;
        
        for (const auto& [freq, gain, prominence, quality] : sortedCandidates) {
            if (finalBands.size() >= 6) break;
            
            bool tooClose = false;
            for (const auto& [existingFreq, existingGain, existingQ, existingProm] : finalBands) {
                float ratio = freq / existingFreq;
                if (ratio > 1.0f) ratio = 1.0f / ratio;
                if (ratio > 0.75f) {
                    tooClose = true;
                    break;
                }
            }
            
            if (!tooClose && std::abs(gain) > 1.0f) {
                float optimalQ = calculateOptimalQ(freq);
                float adjustedGain = std::max(-9.0f, std::min(9.0f, gain * blendAmount));
                finalBands.emplace_back(freq, adjustedGain, optimalQ, prominence);
            }
        }
        
        // Sort by frequency for HISE script ordering
        std::sort(finalBands.begin(), finalBands.end(),
                  [](const auto& a, const auto& b) {
            return std::get<0>(a) < std::get<0>(b);
        });
        
        for (int i = 0; i < 8; ++i) {
            if (i < finalBands.size()) {
                const auto& [freq, gain, q, prominence] = finalBands[i];
                outputBands[i] = {freq, gain, q, freq/q, (std::abs(gain) > 0.5f), true, prominence};
            } else {
                outputBands[i] = {0.0f, 0.0f, 1.0f, 100.0f, false, false, 0.0f};
            }
        }
    }
    
    void analyzeSpectrum(float* fftData)
    {
        auto* cdata = reinterpret_cast<std::complex<float>*>(fftData);
        
        for (int i = 1; i < numBins; ++i) {
            currentSpectrum[i] = std::abs(cdata[i]);
            
            float smoothingRate = spectralSmoothing;
            if (binToFrequency(i) < 100.0f) smoothingRate = 0.92f;
            else if (binToFrequency(i) > 8000.0f) smoothingRate = 0.78f;
            
            smoothedSpectrum[i] = smoothingRate * smoothedSpectrum[i] +
            (1.0f - smoothingRate) * currentSpectrum[i];
        }
        
        if (isCapturing && captureFrames < maxCaptureFrames) {
            captureFrames++;
            
            for (int i = 1; i < numBins; ++i) {
                float alpha = 1.0f / captureFrames;
                referenceSpectrum[i] = (1.0f - alpha) * referenceSpectrum[i] +
                alpha * smoothedSpectrum[i];
            }
            
            if (captureFrames >= maxCaptureFrames) {
                hasReferenceSpectrum = true;
                isCapturing = false;
                
                // NORMALIZE REFERENCE TO UNIT RMS (do this ONCE)
                float refEnergy = 0.0f;
                int validBins = 0;
                for (int bin = 5; bin < numBins - 5; ++bin) {
                    float freq = binToFrequency(bin);
                    if (freq >= 20.0f && freq <= 18000.0f) {
                        refEnergy += referenceSpectrum[bin] * referenceSpectrum[bin];
                        validBins++;
                    }
                }
                float refRMS = std::sqrt(refEnergy / validBins);
                
                for (int bin = 0; bin < numBins; ++bin) {
                    referenceSpectrum[bin] /= std::max(refRMS, 0.0001f);
                }
                
                DBG("Reference captured and normalized (RMS=" << refRMS << ")");
                
                performSpectralAnalysis();
                sendImmediateStatusUpdate();
            }
        }
        
        if (hasReferenceSpectrum && frameProcessCount % 256 == 0) {
            performSpectralAnalysis();
        }
        
        sendDataToGlobalCables();
    }
    
    void sendImmediateStatusUpdate()
    {
        hise::JSONObject statusData;
        statusData[String("analyzerEnabled")] = isEnabled;
        statusData[String("isCapturing")] = false;
        statusData[String("hasReference")] = true;
        statusData[String("captureProgress")] = 1.0f;
        statusData[String("signalLevel")] = signalLevel;
        statusData[String("numActiveBands")] = getNumActiveBands();
        statusData[String("updateCount")] = cableUpdateCount;
        
        this->sendDataToGlobalCable<GlobalCables::dataCable>(statusData);
    }
    
    int getNumActiveBands() const
    {
        int count = 0;
        for (const auto& band : outputBands) {
            if (band.enabled) count++;
        }
        return count;
    }
    
    void sendDataToGlobalCables()
    {
        cableUpdateCount++;
        
        for (int bandIdx = 0; bandIdx < 8; ++bandIdx) {
            const auto& band = outputBands[bandIdx];
            
            hise::JSONObject bandData;
            bandData[String("frequency")] = band.frequency;
            bandData[String("gain")] = band.gain;
            bandData[String("q")] = band.q;
            bandData[String("bandwidth")] = band.bandwidth;
            bandData[String("enabled")] = band.enabled;
            bandData[String("isDynamic")] = band.isDynamic;
            bandData[String("prominence")] = band.prominence;
            bandData[String("updateCount")] = cableUpdateCount;
            bandData[String("hasReference")] = hasReferenceSpectrum;
            bandData[String("isCapturing")] = isCapturing;
            
            switch(bandIdx) {
                case 0: this->sendDataToGlobalCable<GlobalCables::band1_60Hz>(bandData); break;
                case 1: this->sendDataToGlobalCable<GlobalCables::band2_150Hz>(bandData); break;
                case 2: this->sendDataToGlobalCable<GlobalCables::band3_400Hz>(bandData); break;
                case 3: this->sendDataToGlobalCable<GlobalCables::band4_1kHz>(bandData); break;
                case 4: this->sendDataToGlobalCable<GlobalCables::band5_2k5Hz>(bandData); break;
                case 5: this->sendDataToGlobalCable<GlobalCables::band6_6k3Hz>(bandData); break;
                case 6: this->sendDataToGlobalCable<GlobalCables::band7_12kHz>(bandData); break;
                case 7: this->sendDataToGlobalCable<GlobalCables::band8_18kHz>(bandData); break;
            }
        }
        
        if (cableUpdateCount % 10 == 0 || isCapturing) {
            hise::JSONObject statusData;
            statusData[String("analyzerEnabled")] = isEnabled;
            statusData[String("isCapturing")] = isCapturing;
            statusData[String("hasReference")] = hasReferenceSpectrum;
            statusData[String("captureProgress")] = (float)captureFrames / maxCaptureFrames;
            statusData[String("signalLevel")] = signalLevel;
            statusData[String("numActiveBands")] = getNumActiveBands();
            statusData[String("blendAmount")] = blendAmount;
            statusData[String("updateCount")] = cableUpdateCount;
            
            this->sendDataToGlobalCable<GlobalCables::dataCable>(statusData);
        }
    }
    
    // Scriptnode Interface
    
    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;
        
        for (auto& processor : channelProcessors) {
            std::fill(processor.inputFifo.begin(), processor.inputFifo.end(), 0.0f);
            std::fill(processor.fftData.begin(), processor.fftData.end(), 0.0f);
            processor.count = 0;
            processor.pos = 0;
        }
        
        std::fill(currentSpectrum.begin(), currentSpectrum.end(), 0.0f);
        std::fill(smoothedSpectrum.begin(), smoothedSpectrum.end(), 0.0f);
        std::fill(referenceSpectrum.begin(), referenceSpectrum.end(), 0.0f);
        
        initializeOutputBands();
        
        frameProcessCount = 0;
        cableUpdateCount = 0;
        signalLevel = 0.0f;
        significantSignalDetected = false;
        consecutiveSignalFrames = 0;
        captureFrames = 0;
        hasReferenceSpectrum = false;
    }
    
    void reset()
    {
        frameProcessCount = 0;
        cableUpdateCount = 0;
        signalLevel = 0.0f;
        significantSignalDetected = false;
        consecutiveSignalFrames = 0;
        captureFrames = 0;
        
        for (auto& processor : channelProcessors) {
            std::fill(processor.inputFifo.begin(), processor.inputFifo.end(), 0.0f);
            processor.count = 0;
            processor.pos = 0;
        }
        
        std::fill(smoothedSpectrum.begin(), smoothedSpectrum.end(), 0.0f);
        initializeOutputBands();
    }
    
    void handleHiseEvent(HiseEvent& e) {}
    
    template <typename T> void process(T& data)
    {
        if (!isEnabled) return;
        
        static constexpr int NumChannels = getFixChannelAmount();
        auto& fixData = data.template as<ProcessData<NumChannels>>();
        auto fd = fixData.toFrameData();
        
        while(fd.next())
        {
            processFrame(fd.toSpan());
        }
    }
    
    template <typename T> void processFrame(T& frame)
    {
        if (!isEnabled) return;
        
        frameProcessCount++;
        
        float inputSample = frame[0];
        float instantLevel = std::abs(inputSample);
        signalLevel = 0.999f * signalLevel + 0.001f * instantLevel;
        
        processFFTFrame(inputSample, 0);
        
        if (signalLevel > MIN_SIGNAL_THRESHOLD) {
            consecutiveSignalFrames++;
            if (consecutiveSignalFrames > 512) {
                significantSignalDetected = true;
            }
        } else {
            consecutiveSignalFrames = std::max(0, consecutiveSignalFrames - 32);
            if (consecutiveSignalFrames == 0) {
                significantSignalDetected = false;
            }
        }
    }
    
    void processFFTFrame(float sample, int channel)
    {
        auto& processor = channelProcessors[channel];
        
        processor.inputFifo[processor.pos] = sample;
        processor.pos = (processor.pos + 1) % fftSize;
        
        processor.count++;
        if (processor.count >= hopSize) {
            processor.count = 0;
            performFFTAnalysis(channel);
        }
    }
    
    void performFFTAnalysis(int channel)
    {
        if (!significantSignalDetected || channel != 0) return;
        
        auto& processor = channelProcessors[channel];
        
        float* fftPtr = processor.fftData.data();
        const float* inputPtr = processor.inputFifo.data();
        
        std::memcpy(fftPtr, inputPtr + processor.pos, (fftSize - processor.pos) * sizeof(float));
        if (processor.pos > 0) {
            std::memcpy(fftPtr + fftSize - processor.pos, inputPtr, processor.pos * sizeof(float));
        }
        
        window.multiplyWithWindowingTable(fftPtr, fftSize);
        fft.performRealOnlyForwardTransform(fftPtr, true);
        
        analyzeSpectrum(fftPtr);
    }
    
    int handleModulation(double& value) { return 0; }
    void setExternalData(const ExternalData& data, int index) {}
    
    // Parameters
    
    template <int P> void setParameter(double v)
    {
        if (P == 0) {
            blendAmount = (float)v * 0.5f;
            if (hasReferenceSpectrum) {
                performSpectralAnalysis();
            }
        }
        else if (P == 1) {
            isEnabled = v > 0.5;
            if (isEnabled) reset();
        }
        else if (P == 2) {
            if (v > 0.5 && !isCapturing) {
                isCapturing = true;
                captureFrames = 0;
                hasReferenceSpectrum = false;
                std::fill(referenceSpectrum.begin(), referenceSpectrum.end(), 0.0f);
                initializeOutputBands();
            }
        }
        else if (P == 3) {
            if (v > 0.5) {
                hasReferenceSpectrum = false;
                isCapturing = false;
                captureFrames = 0;
                std::fill(referenceSpectrum.begin(), referenceSpectrum.end(), 0.0f);
                initializeOutputBands();
            }
        }
        else if (P == 4) {
            spectralSmoothing = (float)v;
        }
    }
    
    void createParameters(ParameterDataList& data)
    {
        {
            parameter::data p("Blend", { 0.0, 1.0 });
            registerCallback<0>(p);
            p.setDefaultValue(0.5);
            data.add(std::move(p));
        }
        {
            parameter::data p("Enable", { 0.0, 1.0 });
            registerCallback<1>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Capture", { 0.0, 1.0 });
            registerCallback<2>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Clear", { 0.0, 1.0 });
            registerCallback<3>(p);
            p.setDefaultValue(0.0);
            data.add(std::move(p));
        }
        {
            parameter::data p("Smoothing", { 0.0, 1.0 });
            registerCallback<4>(p);
            p.setDefaultValue(0.85);
            data.add(std::move(p));
        }
    }
};

} // namespace project

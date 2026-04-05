//===========| Low Distortion Compressor with Gain Reduction Modulation Output |===========

#pragma once
#include <JuceHeader.h>
#include <algorithm>
#include <cmath>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

template <int NV>
struct comp1 : public data::base
{
    SNEX_NODE(comp1);
    struct MetadataClass { SN_NODE_ID("comp1"); };
    
    comp1()
    : comp(-6.0f, 4.0f, 0.0f, 0.0f, 0.01f, 0.1f),
    max(0.0)  // Following the working gainReduction pattern
    {
    }
    
    // Enable this node to act as a modulation source (following working example)
    static constexpr bool isModNode() { return true; }
    static constexpr bool isPolyphonic() { return NV > 1; }
    static constexpr bool hasTail() { return false; }
    static constexpr bool isSuspendedOnSilence() { return false; }
    static constexpr int  getFixChannelAmount() { return 2; }
    static constexpr int  NumTables = 0;
    static constexpr int  NumSliderPacks = 0;
    static constexpr int  NumAudioFiles = 0;
    static constexpr int  NumFilters = 0;
    static constexpr int  NumDisplayBuffers = 0;
    
    void prepare(PrepareSpecs specs)
    {
        comp.prepare(specs.sampleRate);
        max = 0.0;
    }
    
    void reset()
    {
        comp.reset();
        max = 0.0;
    }
    
    template <typename PD>
    inline void process(PD& data)
    {
        auto& fix = data.template as<ProcessData<2>>();
        auto  blk = fix.toAudioBlock();
        float* L = blk.getChannelPointer(0);
        float* R = blk.getChannelPointer(1);
        int    n = data.getNumSamples();
        
        // Reset max for this block (following working gainReduction pattern)
        max = 0.0;
        
        // Process compression and get current gain reduction
        float blockGainReduction = comp.processBlockWithMeter(L, R, n);
        
        // Convert to normalized value (0.0 = no reduction, 1.0 = max reduction)
        // Following the working example pattern
        float normalizedGR = jlimit<float>(0.0f, 1.0f, blockGainReduction / 24.0f);
        
        // Update max for this block (exactly like working gainReduction example)
        max = std::max(max, (double)normalizedGR);
    }
    
    // THIS IS THE KEY METHOD - following the EXACT signature from working example
    bool handleModulation(double& v)
    {
        // Following working gainReduction pattern exactly
        v = max;
        return true;
    }
    
    // Params - same as original compressor
    template <int P>
    inline void setParameter(double v)
    {
        if (P == 0) comp.setThreshold((float)v);
        else if (P == 1) comp.setRatio((float)v);
        else if (P == 2) comp.setKnee((float)v);
        else if (P == 3) comp.setMakeup((float)v);
        else if (P == 4) comp.setAttack((float)v * 0.001f);
        else if (P == 5) comp.setRelease((float)v * 0.001f);
    }
    
    void createParameters(ParameterDataList& d)
    {
        {
            parameter::data p("Threshold dB", { -60.0,   0.0,   0.1 });
            registerCallback<0>(p); p.setDefaultValue(-6.0);  d.add(std::move(p));
        }
        {
            parameter::data p("Ratio", { 1.0,  20.0,   0.1 });
            registerCallback<1>(p); p.setDefaultValue(4.0);  d.add(std::move(p));
        }
        {
            parameter::data p("KneeWidth dB", { 0.0,  30.0,   0.1 });
            registerCallback<2>(p); p.setDefaultValue(0.0);  d.add(std::move(p));
        }
        {
            parameter::data p("Makeup Gain dB", { -60.0,  60.0,   0.1 });
            registerCallback<3>(p); p.setDefaultValue(0.0);  d.add(std::move(p));
        }
        {
            parameter::data p("Attack Time ms", { 0.1, 500.0,   0.1 });
            registerCallback<4>(p); p.setDefaultValue(10.0);  d.add(std::move(p));
        }
        {
            parameter::data p("Release Time ms", { 1.0,2000.0,   1.0 });
            registerCallback<5>(p); p.setDefaultValue(100.0); d.add(std::move(p));
        }
    }
    
    SN_EMPTY_PROCESS_FRAME;
    SN_EMPTY_HANDLE_EVENT;
    
private:
    struct Compressor
    {
        Compressor(float T, float R, float W, float M, float tauA, float tauR)
        : threshold_dB(T), ratio(R), knee_dB(W), makeup_dB(M),
        attack_sec(tauA), release_sec(tauR),
        y1_prev(0.0f), yL_prev(0.0f), fs(48000.0),
        buffersAllocated(false)
        {
            updateAlphas();
        }
        
        void prepare(double sampleRate)
        {
            fs = sampleRate;
            updateAlphas();
            gainBuffer.clear();
            gainBuffer.reserve(1024);
        }
        
        void reset()
        {
            y1_prev = 0.0f;
            yL_prev = 0.0f;
        }
        
        // Modified to return gain reduction in dB for modulation output
        inline float processBlockWithMeter(float* L, float* R, int n)
        {
            if (!buffersAllocated || gainBuffer.capacity() < n)
            {
                gainBuffer.clear();
                gainBuffer.resize(n);
                buffersAllocated = true;
            }
            
            constexpr float eps = 1e-12f;
            const float    thr = threshold_dB;
            const float    halfK = knee_dB * 0.5f;
            const float    inv2K = knee_dB > 0.0f ? 1.0f / (2.0f * knee_dB) : 0.0f;
            const float    dbToLin = 0.05f * 2.302585093f;
            const float    makeupLin = std::exp(makeup_dB * dbToLin);
            const float    invLn10 = 0.4342944819f;
            const float    a = alpha_att;
            const float    r = alpha_rel;
            
            float y1 = y1_prev;
            float yL = yL_prev;
            float maxGainReductionDb = 0.0f; // Track max gain reduction in dB
            
            for (int i = 0; i < n; ++i)
            {
                float sc = L[i] + R[i];
                float mag = std::fabs(sc) + eps;
                float x_db = 20.0f * (std::log(mag) * invLn10);
                float delta = x_db - thr;
                
                float y_db;
                if (x_db < thr - halfK)
                    y_db = x_db;
                else if (x_db > thr + halfK)
                    y_db = thr + delta / ratio;
                else
                    y_db = x_db + (1.0f / ratio - 1.0f)
                    * ((delta + halfK) * (delta + halfK))
                    * inv2K;
                
                float inst = (x_db - y_db) > 0.0f ? (x_db - y_db) : 0.0f;
                float cand = r * y1 + (1.0f - r) * inst;
                y1 = inst > cand ? inst : cand;
                yL = a * yL + (1.0f - a) * y1;
                
                float finalGain = makeupLin * std::exp(-yL * dbToLin);
                gainBuffer[i] = finalGain;
                
                // Track the maximum gain reduction in dB for this block
                // yL represents the gain reduction amount in dB
                maxGainReductionDb = std::max(maxGainReductionDb, yL);
            }
            
            y1_prev = y1;
            yL_prev = yL;
            
            FloatVectorOperations::multiply(L, L, gainBuffer.data(), n);
            FloatVectorOperations::multiply(R, R, gainBuffer.data(), n);
            
            return maxGainReductionDb; // Return gain reduction in dB
        }
        
        inline void setThreshold(float v) { threshold_dB = v; }
        inline void setRatio(float v) { ratio = v; }
        inline void setKnee(float v) { knee_dB = v; }
        inline void setMakeup(float v) { makeup_dB = v; }
        inline void setAttack(float v) { attack_sec = v; updateAlphas(); }
        inline void setRelease(float v) { release_sec = v; updateAlphas(); }
        
        void updateAlphas()
        {
            alpha_att = std::exp(-1.0f / (attack_sec * (float)fs));
            alpha_rel = std::exp(-1.0f / (release_sec * (float)fs));
        }
        
        float threshold_dB, ratio, knee_dB, makeup_dB;
        float attack_sec, release_sec;
        float alpha_att, alpha_rel;
        float y1_prev, yL_prev;
        double fs;
        
        bool                buffersAllocated;
        std::vector<float>  gainBuffer;
    };
    
    Compressor comp;
    
    // Following the working gainReduction pattern exactly
    double max;  // Store the gain reduction value for the block (normalized 0-1)
};
} // namespace project

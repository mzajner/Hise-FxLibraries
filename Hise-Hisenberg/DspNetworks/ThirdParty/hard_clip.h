
//===========| Transparent Hard Clipper |===========

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
    struct hard_clip : public data::base
    {
        SNEX_NODE(hard_clip);
        struct MetadataClass { SN_NODE_ID("hard_clip"); };

        hard_clip()
            : leftEffect(0.0f, true), rightEffect(0.0f, true)
        {
        }

        static constexpr bool isModNode() { return false; }
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
            leftEffect.prepare(specs.sampleRate);
            rightEffect.prepare(specs.sampleRate);
        }
        void reset() {}

        template<typename PD>
        inline void process(PD& d)
        {
            auto& fix = d.template as<ProcessData<2>>();
            auto  blk = fix.toAudioBlock();
            float* L = blk.getChannelPointer(0);
            float* R = blk.getChannelPointer(1);
            int    n = d.getNumSamples();

            leftEffect.processBlock(L, n);
            rightEffect.processBlock(R, n);
        }

        template <int P>
        inline void setParameter(double v)
        {
            if (P == 0) { leftEffect.setDrive((float)v);  rightEffect.setDrive((float)v); }
            else if (P == 1) { bool e = (v >= 0.5); leftEffect.updateGainComp(e); rightEffect.updateGainComp(e); }
            else if (P == 2) { leftEffect.setOutGain((float)v); rightEffect.setOutGain((float)v); }
        }

        void createParameters(ParameterDataList& data)
        {
            {
                parameter::data p("Amount (dB)", { -20.0, 30.0, 0.0001 });
                registerCallback<0>(p); p.setDefaultValue(0.0); data.add(std::move(p));
            }
            {
                parameter::data p("GainCompensation", { 0.0, 1.0, 1.0 });
                registerCallback<1>(p); p.setDefaultValue(1.0); data.add(std::move(p));
            }
            {
                parameter::data p("OutGain (dB)", { -20.0, 30.0, 0.0001 });
                registerCallback<2>(p); p.setDefaultValue(0.0); data.add(std::move(p));
            }
        }

        SN_EMPTY_PROCESS_FRAME;
        SN_EMPTY_HANDLE_EVENT;

    private:
        class AudioEffect
        {
        public:
            AudioEffect(float drive_dB_, bool gainComp_)
                : drive_dB(drive_dB_), outGain_dB(-0.8f),
                gainCompensation(gainComp_), m_sampleRate(48000.0)
            {
                updateParams();
            }

            void prepare(double sr) { m_sampleRate = sr; }

            // Process a block of samples with hard clipping, vectorized drive and gain
            inline void processBlock(float* samples, int numSamples)
            {
                // constants
                constexpr float fixedDrive = 1.1f;
                constexpr float threshold = 1.0f;
                constexpr float knee = 0.03f;
                constexpr float halfKnee = knee * 0.5f;
                constexpr float lower_bound = threshold - halfKnee;
                constexpr float inv_two_knee = 1.0f / (2.0f * knee);

                // precompute
                const float effDrv = m_inGain * fixedDrive;
                const bool  doGain = gainCompensation;
                const float oGain = m_outGain;

                // apply drive 
                FloatVectorOperations::multiply(samples, samples, effDrv, numSamples);

                // clip inputs to [-1,1]
                FloatVectorOperations::clip(samples, samples, -1.0f, 1.0f, numSamples);

                // apply soft knee waveshaper
                for (int i = 0; i < numSamples; ++i)
                {
                    float x = samples[i];
                    float a = std::fabs(x);

                    if (a > lower_bound && a < threshold)
                    {
                        float d = a - lower_bound;
                        a = a - (d * d) * inv_two_knee;
                    }
                    else if (a >= threshold)
                    {
                        a = threshold;
                    }

                    // restore sign
                    samples[i] = std::copysign(a, x);
                }

                // apply output gain 
                if (doGain)
                    FloatVectorOperations::multiply(samples, samples, oGain, numSamples);
            }

            inline void setDrive(float v) { drive_dB = v; updateParams(); }
            inline void setOutGain(float v) { outGain_dB = v; updateParams(); }
            inline void updateGainComp(bool e) { gainCompensation = e; updateParams(); }

        private:
            float drive_dB, outGain_dB;
            bool  gainCompensation;
            float m_inGain, m_outGain;
            double m_sampleRate;

            inline void updateParams()
            {
                m_inGain = std::pow(10.0f, drive_dB / 20.0f);
                m_outGain = gainCompensation
                    ? std::pow(10.0f, -drive_dB / 20.0f) * std::pow(10.0f, outGain_dB / 20.0f)
                    : std::pow(10.0f, outGain_dB / 20.0f);
            }
        };

        AudioEffect leftEffect, rightEffect;
    };
} // namespace project

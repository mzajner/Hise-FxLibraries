/*
==========================| ASPIK Phaser |==========================
Six-stage all-pass filter phaser with LFO modulation
- Six 1st-order all-pass filters in series with feedback
- Adjustable LFO rate and depth for sweep control
- Variable intensity (feedback) for resonance effect
*/

#pragma once
#include <JuceHeader.h>

namespace project
{
    using namespace juce;
    using namespace hise;
    using namespace scriptnode;
    using namespace aspik;

    template <int NV>
    struct AspikModPhaser : public data::base
    {
        SNEX_NODE(AspikModPhaser);

        struct MetadataClass
        {
            SN_NODE_ID("AspikModPhaser");
        };

        static constexpr bool isModNode() { return false; }
        static constexpr bool isPolyphonic() { return NV > 1; }
        static constexpr bool hasTail() { return false; }
        static constexpr bool isSuspendedOnSilence() { return true; }
        static constexpr int getFixChannelAmount() { return 2; }

        static constexpr int NumTables = 0;
        static constexpr int NumSliderPacks = 0;
        static constexpr int NumAudioFiles = 0;
        static constexpr int NumFilters = 0;
        static constexpr int NumDisplayBuffers = 0;

        PhaseShifter leftPhaseShifter;
        PhaseShifter rightPhaseShifter;

        double lfoRate = 0.2;
        double lfoDepth = 50.0;
        double intensity = 75.0;

        AspikModPhaser()
        {
            updatePhaserParameters();
        }

        void prepare(PrepareSpecs specs)
        {
            leftPhaseShifter.reset(specs.sampleRate);
            rightPhaseShifter.reset(specs.sampleRate);
            updatePhaserParameters();
        }

        void reset()
        {
            leftPhaseShifter.reset(44100.0);
            rightPhaseShifter.reset(44100.0);
        }

        void handleHiseEvent(HiseEvent& e) {}

        template <typename T> void process(T& data)
        {
            static constexpr int NumChannels = getFixChannelAmount();
            auto& fixData = data.template as<ProcessData<NumChannels>>();
            auto fd = fixData.toFrameData();

            while (fd.next())
            {
                processFrame(fd.toSpan());
            }
        }

        template <typename T> void processFrame(T& data)
        {
            double leftInput = data[0];
            double rightInput = data[1];

            double leftOutput = leftPhaseShifter.processAudioSample(leftInput);
            double rightOutput = rightPhaseShifter.processAudioSample(rightInput);

            data[0] = static_cast<float>(leftOutput);
            data[1] = static_cast<float>(rightOutput);
        }

        int handleModulation(double& value)
        {
            return 0;
        }

        void setExternalData(const ExternalData& data, int index) {}

        template <int P> void setParameter(double v)
        {
            bool needsUpdate = false;

            if (P == 0)
            {
                double newRate = jlimit(0.02, 20.0, v);
                if (lfoRate != newRate)
                {
                    lfoRate = newRate;
                    needsUpdate = true;
                }
            }
            else if (P == 1)
            {
                double newDepth = jlimit(0.0, 100.0, v);
                if (lfoDepth != newDepth)
                {
                    lfoDepth = newDepth;
                    needsUpdate = true;
                }
            }
            else if (P == 2)
            {
                double newIntensity = jlimit(0.0, 100.0, v);
                if (intensity != newIntensity)
                {
                    intensity = newIntensity;
                    needsUpdate = true;
                }
            }

            if (needsUpdate)
            {
                updatePhaserParameters();
            }
        }

        void createParameters(ParameterDataList& data)
        {
            {
                parameter::data p("Rate", { 0.02, 20.0 });
                registerCallback<0>(p);
                p.setDefaultValue(0.2);
                p.setSkewForCentre(2.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Depth", { 0.0, 100.0 });
                registerCallback<1>(p);
                p.setDefaultValue(50.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Intensity", { 0.0, 100.0 });
                registerCallback<2>(p);
                p.setDefaultValue(75.0);
                data.add(std::move(p));
            }
        }

    private:
        void updatePhaserParameters()
        {
            PhaseShifterParameters params;
            params.lfoRate_Hz = lfoRate;
            params.lfoDepth_Pct = lfoDepth;
            params.intensity_Pct = intensity;
            params.quadPhaseLFO = false;

            leftPhaseShifter.setParameters(params);

            // Set right channel to quadrature for stereo effect
            params.quadPhaseLFO = true;
            rightPhaseShifter.setParameters(params);
        }
    };

} // namespace project

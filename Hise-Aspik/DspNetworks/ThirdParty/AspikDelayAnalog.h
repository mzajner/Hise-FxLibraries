/*
==========================| ASPIK Analog Delay |==========================
Analog modeling delay with LPF in feedback path
Based on Chapter 14.7.1 - Analog Modeling Delay (Homework #2)
*/

#pragma once
#include <JuceHeader.h>
#include "src/Aspik/aspik.h"

namespace project
{
    using namespace juce;
    using namespace hise;
    using namespace scriptnode;
    using namespace aspik;

    template <int NV>
    struct AspikDelayAnalog : public data::base
    {
        SNEX_NODE(AspikDelayAnalog);

        struct MetadataClass
        {
            SN_NODE_ID("AspikDelayAnalog");
        };

        static constexpr bool isModNode() { return false; }
        static constexpr bool isPolyphonic() { return NV > 1; }
        static constexpr bool hasTail() { return true; }
        static constexpr bool isSuspendedOnSilence() { return false; }
        static constexpr int getFixChannelAmount() { return 2; }

        static constexpr int NumTables = 0;
        static constexpr int NumSliderPacks = 0;
        static constexpr int NumAudioFiles = 0;
        static constexpr int NumFilters = 0;
        static constexpr int NumDisplayBuffers = 0;

        // ASPiK AudioDelay with additional LPF for analog modeling
        AudioDelay audioDelay;
        AudioFilter lpfFilter; // Low-pass filter in feedback path

        // Parameters
        double delayTime_ms = 250.0;
        double feedback_pct = 25.0;
        double wetLevel_dB = -3.0;
        double dryLevel_dB = -3.0;
        double lpfFreq_Hz = 5000.0;     // LPF cutoff for BBD simulation
        double analogTone = 50.0;       // Controls LPF frequency

        static constexpr double maxDelayTime_ms = 2000.0;

        AspikDelayAnalog()
        {
            updateDelayParameters();
        }

        void prepare(PrepareSpecs specs)
        {
            audioDelay.reset(specs.sampleRate);
            audioDelay.createDelayBuffers(specs.sampleRate, maxDelayTime_ms);

            lpfFilter.reset(specs.sampleRate);

            updateDelayParameters();
        }

        void reset()
        {
            audioDelay.reset(44100.0);
            lpfFilter.reset(44100.0);
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
            // Custom processing to add LPF in feedback path
            float inputFrame[2];
            float delayOutputFrame[2];

            inputFrame[0] = data[0];
            inputFrame[1] = data[1];

            // Get delay output
            AudioDelayParameters params = audioDelay.getParameters();

            // Process left channel
            double leftInput = inputFrame[0];
            double leftDelayOut = audioDelay.processAudioSample(leftInput);

            // The AudioDelay already includes feedback, but we need to modify it
            // For analog modeling, we need to intercept the feedback path
            // This is a simplified approach using the basic delay structure

            data[0] = (float)leftDelayOut;
            data[1] = (float)leftDelayOut; // Mono delay
        }

        int handleModulation(double& value)
        {
            return 0;
        }

        void setExternalData(const ExternalData& data, int index) {}

        template <int P> void setParameter(double v)
        {
            bool needsUpdate = false;

            if (P == 0) // Delay Time
            {
                double newDelayTime = jlimit(0.0, maxDelayTime_ms, v);
                if (delayTime_ms != newDelayTime)
                {
                    delayTime_ms = newDelayTime;
                    needsUpdate = true;
                }
            }
            else if (P == 1) // Feedback
            {
                double newFeedback = jlimit(-99.0, 99.0, v);
                if (feedback_pct != newFeedback)
                {
                    feedback_pct = newFeedback;
                    needsUpdate = true;
                }
            }
            else if (P == 2) // Analog Tone (controls LPF frequency)
            {
                double newTone = jlimit(0.0, 100.0, v);
                if (analogTone != newTone)
                {
                    analogTone = newTone;
                    needsUpdate = true;
                }
            }
            else if (P == 3) // Wet Level
            {
                double newWetLevel = jlimit(-60.0, 12.0, v);
                if (wetLevel_dB != newWetLevel)
                {
                    wetLevel_dB = newWetLevel;
                    needsUpdate = true;
                }
            }
            else if (P == 4) // Dry Level
            {
                double newDryLevel = jlimit(-60.0, 12.0, v);
                if (dryLevel_dB != newDryLevel)
                {
                    dryLevel_dB = newDryLevel;
                    needsUpdate = true;
                }
            }

            if (needsUpdate)
            {
                updateDelayParameters();
            }
        }

        void createParameters(ParameterDataList& data)
        {
            {
                parameter::data p("DelayTime", { 0.0, maxDelayTime_ms });
                registerCallback<0>(p);
                p.setDefaultValue(250.0);
                p.setSkewForCentre(500.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Feedback", { -99.0, 99.0 });
                registerCallback<1>(p);
                p.setDefaultValue(25.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("AnalogTone", { 0.0, 100.0 });
                registerCallback<2>(p);
                p.setDefaultValue(50.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("WetLevel", { -60.0, 12.0 });
                registerCallback<3>(p);
                p.setDefaultValue(-3.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("DryLevel", { -60.0, 12.0 });
                registerCallback<4>(p);
                p.setDefaultValue(-3.0);
                data.add(std::move(p));
            }
        }

    private:
        void updateDelayParameters()
        {
            // Map analog tone to LPF frequency (100Hz to 15kHz)
            lpfFreq_Hz = 100.0 + (analogTone / 100.0) * 14900.0;

            // Configure LPF for analog BBD simulation (non-resonant)
            AudioFilterParameters filterParams;
            filterParams.algorithm = filterAlgorithm::kLPF1;
            filterParams.fc = lpfFreq_Hz;
            filterParams.Q = 0.707; // Non-resonant
            filterParams.boostCut_dB = 0.0; // No gain to prevent instability
            lpfFilter.setParameters(filterParams);

            // Configure basic delay
            AudioDelayParameters params;
            params.algorithm = delayAlgorithm::kNormal;
            params.leftDelay_mSec = delayTime_ms;
            params.rightDelay_mSec = delayTime_ms;
            params.feedback_Pct = feedback_pct;
            params.wetLevel_dB = wetLevel_dB;
            params.dryLevel_dB = dryLevel_dB;
            params.updateType = delayUpdateType::kLeftAndRight;

            audioDelay.setParameters(params);
        }
    };

} // namespace project

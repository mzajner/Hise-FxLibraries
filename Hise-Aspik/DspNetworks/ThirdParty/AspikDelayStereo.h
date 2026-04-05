/*
==========================| ASPIK Stereo Delay |==========================
Stereo digital delay with normal and ping-pong modes
Based on Chapter 14 - Stereo Delay and Ping-Pong Delay
Independent left/right delay time controls
Switchable between Normal and Ping-Pong algorithms
Uses ASPiK AudioDelay object directly
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
    struct AspikDelayStereo : public data::base
    {
        SNEX_NODE(AspikDelayStereo);

        struct MetadataClass
        {
            SN_NODE_ID("AspikDelayStereo");
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

        // ASPiK AudioDelay object
        AudioDelay audioDelay;

        // Parameters
        double leftDelay_ms = 250.0;
        double rightDelay_ms = 375.0;
        double feedback_pct = 15.0;
        double wetLevel_dB = -3.0;
        double dryLevel_dB = -3.0;
        int delayType = 0; // 0=Normal, 1=PingPong

        static constexpr double maxDelayTime_ms = 2000.0;

        AspikDelayStereo()
        {
            updateDelayParameters();
        }

        void prepare(PrepareSpecs specs)
        {
            audioDelay.reset(specs.sampleRate);
            audioDelay.createDelayBuffers(specs.sampleRate, maxDelayTime_ms);
            updateDelayParameters();
        }

        void reset()
        {
            audioDelay.reset(44100.0);
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
            float inputFrame[2];
            float outputFrame[2];

            inputFrame[0] = data[0];
            inputFrame[1] = data[1];

            audioDelay.processAudioFrame(inputFrame, outputFrame, 2, 2);

            data[0] = outputFrame[0];
            data[1] = outputFrame[1];
        }

        int handleModulation(double& value)
        {
            return 0;
        }

        void setExternalData(const ExternalData& data, int index) {}

        template <int P> void setParameter(double v)
        {
            bool needsUpdate = false;

            if (P == 0) // Left Delay Time
            {
                double newLeftDelay = jlimit(0.0, maxDelayTime_ms, v);
                if (leftDelay_ms != newLeftDelay)
                {
                    leftDelay_ms = newLeftDelay;
                    needsUpdate = true;
                }
            }
            else if (P == 1) // Right Delay Time
            {
                double newRightDelay = jlimit(0.0, maxDelayTime_ms, v);
                if (rightDelay_ms != newRightDelay)
                {
                    rightDelay_ms = newRightDelay;
                    needsUpdate = true;
                }
            }
            else if (P == 2) // Feedback
            {
                double newFeedback = jlimit(-99.0, 99.0, v);
                if (feedback_pct != newFeedback)
                {
                    feedback_pct = newFeedback;
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
            else if (P == 5) // Delay Type
            {
                int newDelayType = jlimit(0, 1, (int)v);
                if (delayType != newDelayType)
                {
                    delayType = newDelayType;
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
                parameter::data p("LeftDelay", { 0.0, maxDelayTime_ms });
                registerCallback<0>(p);
                p.setDefaultValue(250.0);
                p.setSkewForCentre(500.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("RightDelay", { 0.0, maxDelayTime_ms });
                registerCallback<1>(p);
                p.setDefaultValue(375.0);
                p.setSkewForCentre(500.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Feedback", { -99.0, 99.0 });
                registerCallback<2>(p);
                p.setDefaultValue(15.0);
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

            {
                parameter::data p("DelayType", { 0.0, 1.0, 1.0 });
                registerCallback<5>(p);
                p.setDefaultValue(0.0);

                StringArray delayTypes;
                delayTypes.add("Normal");
                delayTypes.add("Ping-Pong");

                p.setParameterValueNames(delayTypes);
                data.add(std::move(p));
            }
        }

    private:
        void updateDelayParameters()
        {
            AudioDelayParameters params;

            // Set algorithm based on delay type
            if (delayType == 0)
                params.algorithm = delayAlgorithm::kNormal;
            else
                params.algorithm = delayAlgorithm::kPingPong;

            // Set individual left/right delay times
            params.leftDelay_mSec = leftDelay_ms;
            params.rightDelay_mSec = rightDelay_ms;

            params.feedback_Pct = feedback_pct;
            params.wetLevel_dB = wetLevel_dB;
            params.dryLevel_dB = dryLevel_dB;

            // Use individual left/right control method
            params.updateType = delayUpdateType::kLeftAndRight;

            audioDelay.setParameters(params);
        }
    };

} // namespace project

/*
==========================| ASPIK Digital Delay |==========================
Basic digital delay with feedback and wet/dry mix
Based on Chapter 14 - The Basic Digital Delay (DDL)
• Uses ASPiK AudioDelay object directly
• Supports mono input to mono/stereo output
• Fractional delay with interpolation
• Maximum 2-second delay time
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
    struct AspikDelayDigital : public data::base
    {
        SNEX_NODE(AspikDelayDigital);

        struct MetadataClass
        {
            SN_NODE_ID("AspikDelayDigital");
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

        // ASPiK AudioDelay object - this does all the heavy lifting
        AudioDelay audioDelay;

        // Parameters - mapped to AudioDelayParameters
        double delayTime_ms = 250.0;
        double feedback_pct = 15.0;
        double wetLevel_dB = -3.0;
        double dryLevel_dB = -3.0;

        // Max delay time in milliseconds (as per Chapter 14 recommendation)
        static constexpr double maxDelayTime_ms = 2000.0;

        AspikDelayDigital()
        {
            updateDelayParameters();
        }

        void prepare(PrepareSpecs specs)
        {
            // Step 1: Reset the AudioDelay object to prepare for streaming
            audioDelay.reset(specs.sampleRate);

            // Step 2: Call createDelayBuffers to set up delay lines (2 seconds max)
            audioDelay.createDelayBuffers(specs.sampleRate, maxDelayTime_ms);

            updateDelayParameters();
        }

        void reset()
        {
            // Reset flushes the delay buffers if sample rate hasn't changed
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
            // Prepare input/output frame arrays as required by AudioDelay::processAudioFrame
            float inputFrame[2];
            float outputFrame[2];

            // Fill input frame
            inputFrame[0] = data[0];  // Left input
            inputFrame[1] = data[1];  // Right input (or duplicate left if mono)

            // Step 6: Call processAudioFrame passing frame pointers and channel counts
            // This processes both left and right channels according to the algorithm
            audioDelay.processAudioFrame(inputFrame, outputFrame, 2, 2);

            // Copy processed output back to data
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
            else if (P == 2) // Wet Level
            {
                double newWetLevel = jlimit(-60.0, 12.0, v);
                if (wetLevel_dB != newWetLevel)
                {
                    wetLevel_dB = newWetLevel;
                    needsUpdate = true;
                }
            }
            else if (P == 3) // Dry Level
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
                p.setDefaultValue(15.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("WetLevel", { -60.0, 12.0 });
                registerCallback<2>(p);
                p.setDefaultValue(-3.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("DryLevel", { -60.0, 12.0 });
                registerCallback<3>(p);
                p.setDefaultValue(-3.0);
                data.add(std::move(p));
            }
        }

    private:
        void updateDelayParameters()
        {
            // Step 3: Set object parameters in AudioDelayParameters structure
            AudioDelayParameters params;

            // Configure for basic digital delay (kNormal algorithm)
            params.algorithm = delayAlgorithm::kNormal;

            // Set delay times - for basic delay, both channels get same time
            params.leftDelay_mSec = delayTime_ms;
            params.rightDelay_mSec = delayTime_ms;

            // Set feedback
            params.feedback_Pct = feedback_pct;

            // Set wet/dry levels in dB
            params.wetLevel_dB = wetLevel_dB;
            params.dryLevel_dB = dryLevel_dB;

            // Step 4: Set updateType for left and right delay calculation
            params.updateType = delayUpdateType::kLeftAndRight;

            // Step 5: Call setParameters to update the AudioDelay object
            audioDelay.setParameters(params);
        }
    };

} // namespace project

/*
==========================| ASPIK Ducking Delay |==========================
TC-2290 style ducking delay with envelope detection
Based on Chapter 14.7.4 - TC Electronics TC-2290 Dynamic Delay (Homework #4)
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
    struct AspikDelayDuck : public data::base
    {
        SNEX_NODE(AspikDelayDuck);

        struct MetadataClass
        {
            SN_NODE_ID("AspikDelayDuck");
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

        // ASPiK objects for delay and envelope detection
        AudioDelay audioDelay;
        AudioDetector envelopeDetector;

        // Parameters
        double delayTime_ms = 250.0;
        double feedback_pct = 15.0;
        double threshold_dB = -20.0;       // Ducking threshold
        double wetMin_dB = -40.0;          // Ducked (minimum) wet level
        double wetMax_dB = -3.0;           // Un-ducked (maximum) wet level
        double dryLevel_dB = -3.0;
        double attackTime_ms = 10.0;       // Envelope detector attack
        double releaseTime_ms = 100.0;     // Envelope detector release
        double sideChainGain_dB = 0.0;     // Optional side-chain gain

        double dryMix = 0.707;
        double sideChainGain = 1.0;
        double thresholdLinear = 0.1;
        double wetMinLinear = 0.01;
        double wetMaxLinear = 0.707;

        static constexpr double maxDelayTime_ms = 2000.0;

        AspikDelayDuck()
        {
            updateDelayParameters();
        }

        void prepare(PrepareSpecs specs)
        {
            audioDelay.reset(specs.sampleRate);
            audioDelay.createDelayBuffers(specs.sampleRate, maxDelayTime_ms);

            envelopeDetector.reset(specs.sampleRate);

            updateDelayParameters();
        }

        void reset()
        {
            audioDelay.reset(44100.0);
            envelopeDetector.reset(44100.0);
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
            float delayOutputFrame[2];

            inputFrame[0] = data[0];
            inputFrame[1] = data[1];

            // Detect envelope of input signal for side-chain
            double inputLevel = (inputFrame[0] + inputFrame[1]) * 0.5 * sideChainGain;
            double envelopeLevel = envelopeDetector.processAudioSample(abs(inputLevel));

            // Calculate ducking amount based on envelope vs threshold
            double duckingGain;
            if (envelopeLevel > thresholdLinear)
            {
                // Above threshold: duck the wet signal (reduce to minimum)
                double overThreshold = (envelopeLevel - thresholdLinear) / (1.0 - thresholdLinear);
                overThreshold = jlimit(0.0, 1.0, overThreshold);

                // Linear interpolation from max to min wet level
                duckingGain = wetMaxLinear * (1.0 - overThreshold) + wetMinLinear * overThreshold;
            }
            else
            {
                // Below threshold: use maximum wet level
                duckingGain = wetMaxLinear;
            }

            // Process delay
            audioDelay.processAudioFrame(inputFrame, delayOutputFrame, 2, 2);

            // Apply ducking to delay output only (preserve dry signal)
            double wetOutputL = delayOutputFrame[0] - dryMix * inputFrame[0]; // Extract wet component
            double wetOutputR = delayOutputFrame[1] - dryMix * inputFrame[1];

            wetOutputL *= duckingGain;
            wetOutputR *= duckingGain;

            // Recombine with dry signal
            data[0] = (float)(dryMix * inputFrame[0] + wetOutputL);
            data[1] = (float)(dryMix * inputFrame[1] + wetOutputR);
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
            else if (P == 2) // Threshold
            {
                double newThreshold = jlimit(-60.0, 0.0, v);
                if (threshold_dB != newThreshold)
                {
                    threshold_dB = newThreshold;
                    needsUpdate = true;
                }
            }
            else if (P == 3) // Wet Min (ducked level)
            {
                double newWetMin = jlimit(-60.0, 12.0, v);
                if (wetMin_dB != newWetMin)
                {
                    wetMin_dB = newWetMin;
                    needsUpdate = true;
                }
            }
            else if (P == 4) // Wet Max (normal level)
            {
                double newWetMax = jlimit(-60.0, 12.0, v);
                if (wetMax_dB != newWetMax)
                {
                    wetMax_dB = newWetMax;
                    needsUpdate = true;
                }
            }
            else if (P == 5) // Attack Time
            {
                double newAttack = jlimit(0.1, 500.0, v);
                if (attackTime_ms != newAttack)
                {
                    attackTime_ms = newAttack;
                    needsUpdate = true;
                }
            }
            else if (P == 6) // Release Time
            {
                double newRelease = jlimit(1.0, 5000.0, v);
                if (releaseTime_ms != newRelease)
                {
                    releaseTime_ms = newRelease;
                    needsUpdate = true;
                }
            }
            else if (P == 7) // Side-Chain Gain
            {
                double newSCGain = jlimit(-24.0, 24.0, v);
                if (sideChainGain_dB != newSCGain)
                {
                    sideChainGain_dB = newSCGain;
                    needsUpdate = true;
                }
            }
            else if (P == 8) // Dry Level
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
                parameter::data p("Threshold", { -60.0, 0.0 });
                registerCallback<2>(p);
                p.setDefaultValue(-20.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("WetMin", { -60.0, 12.0 });
                registerCallback<3>(p);
                p.setDefaultValue(-40.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("WetMax", { -60.0, 12.0 });
                registerCallback<4>(p);
                p.setDefaultValue(-3.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Attack", { 0.1, 500.0 });
                registerCallback<5>(p);
                p.setDefaultValue(10.0);
                p.setSkewForCentre(50.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Release", { 1.0, 5000.0 });
                registerCallback<6>(p);
                p.setDefaultValue(100.0);
                p.setSkewForCentre(500.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("SCGain", { -24.0, 24.0 });
                registerCallback<7>(p);
                p.setDefaultValue(0.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("DryLevel", { -60.0, 12.0 });
                registerCallback<8>(p);
                p.setDefaultValue(-3.0);
                data.add(std::move(p));
            }
        }

    private:
        void updateDelayParameters()
        {
            // Convert dB values to linear
            thresholdLinear = Decibels::decibelsToGain(threshold_dB);
            wetMinLinear = Decibels::decibelsToGain(wetMin_dB);
            wetMaxLinear = Decibels::decibelsToGain(wetMax_dB);
            dryMix = Decibels::decibelsToGain(dryLevel_dB);
            sideChainGain = Decibels::decibelsToGain(sideChainGain_dB);

            // Configure envelope detector for side-chain
            AudioDetectorParameters detectorParams;
            detectorParams.attackTime_mSec = attackTime_ms;
            detectorParams.releaseTime_mSec = releaseTime_ms;
            detectorParams.detectMode = TLD_AUDIO_DETECT_MODE_RMS; // RMS detection
            detectorParams.detect_dB = false; // Linear output
            detectorParams.clampToUnityMax = false; // Allow above unity
            envelopeDetector.setParameters(detectorParams);

            // Configure basic delay
            AudioDelayParameters params;
            params.algorithm = delayAlgorithm::kNormal;
            params.leftDelay_mSec = delayTime_ms;
            params.rightDelay_mSec = delayTime_ms;
            params.feedback_Pct = feedback_pct;
            params.wetLevel_dB = wetMax_dB; // Use max level as base
            params.dryLevel_dB = dryLevel_dB;
            params.updateType = delayUpdateType::kLeftAndRight;

            audioDelay.setParameters(params);
        }
    };

} // namespace project

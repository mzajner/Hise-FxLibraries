/*
==========================| ASPIK LCR Delay |==========================
Left-Center-Right delay based on Korg Triton
Based on Chapter 14.7.3 - LCR Delay (Homework #3)
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
    struct AspikDelayLcr : public data::base
    {
        SNEX_NODE(AspikDelayLcr);

        struct MetadataClass
        {
            SN_NODE_ID("AspikDelayLcr");
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

        // Three independent delay lines for L, C, R
        SimpleDelay leftDelay;
        SimpleDelay centerDelay;
        SimpleDelay rightDelay;

        // Filters in center feedback path (can be bypassed)
        AudioFilter centerFilter1;
        AudioFilter centerFilter2;

        // Parameters
        double leftDelay_ms = 200.0;
        double centerDelay_ms = 300.0;
        double rightDelay_ms = 250.0;
        double centerFeedback_pct = 15.0;   // Only center has feedback
        double wetLevel_dB = -3.0;
        double dryLevel_dB = -3.0;

        // Filter controls
        double filter1Freq_Hz = 2000.0;
        double filter2Freq_Hz = 8000.0;
        bool enableFilter1 = false;
        bool enableFilter2 = false;

        double wetMix = 0.707;
        double dryMix = 0.707;
        double centerFeedback = 0.15;

        static constexpr double maxDelayTime_ms = 2000.0;

        AspikDelayLcr()
        {
            updateDelayParameters();
        }

        void prepare(PrepareSpecs specs)
        {
            leftDelay.reset(specs.sampleRate);
            centerDelay.reset(specs.sampleRate);
            rightDelay.reset(specs.sampleRate);

            leftDelay.createDelayBuffer(specs.sampleRate, maxDelayTime_ms);
            centerDelay.createDelayBuffer(specs.sampleRate, maxDelayTime_ms);
            rightDelay.createDelayBuffer(specs.sampleRate, maxDelayTime_ms);

            centerFilter1.reset(specs.sampleRate);
            centerFilter2.reset(specs.sampleRate);

            updateDelayParameters();
        }

        void reset()
        {
            leftDelay.reset(44100.0);
            centerDelay.reset(44100.0);
            rightDelay.reset(44100.0);
            centerFilter1.reset(44100.0);
            centerFilter2.reset(44100.0);
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
            double inputL = data[0];
            double inputR = data[1];
            double inputCenter = (inputL + inputR) * 0.5; // Mono center

            // Read delay outputs
            double leftOut = leftDelay.readDelay();
            double centerOut = centerDelay.readDelay();
            double rightOut = rightDelay.readDelay();

            // Process center channel feedback with optional filters
            double centerFeedbackSignal = centerOut * centerFeedback;

            if (enableFilter1)
                centerFeedbackSignal = centerFilter1.processAudioSample(centerFeedbackSignal);

            if (enableFilter2)
                centerFeedbackSignal = centerFilter2.processAudioSample(centerFeedbackSignal);

            // Write inputs to delay lines (only center has feedback)
            leftDelay.writeDelay(inputL);
            centerDelay.writeDelay(inputCenter + centerFeedbackSignal);
            rightDelay.writeDelay(inputR);

            // Create L-C-R outputs
            double outputL = dryMix * inputL + wetMix * (leftOut + centerOut * 0.707);
            double outputR = dryMix * inputR + wetMix * (rightOut + centerOut * 0.707);

            data[0] = (float)outputL;
            data[1] = (float)outputR;
        }

        int handleModulation(double& value)
        {
            return 0;
        }

        void setExternalData(const ExternalData& data, int index) {}

        template <int P> void setParameter(double v)
        {
            bool needsUpdate = false;

            if (P == 0) // Left Delay
            {
                double newLeftDelay = jlimit(0.0, maxDelayTime_ms, v);
                if (leftDelay_ms != newLeftDelay)
                {
                    leftDelay_ms = newLeftDelay;
                    needsUpdate = true;
                }
            }
            else if (P == 1) // Center Delay
            {
                double newCenterDelay = jlimit(0.0, maxDelayTime_ms, v);
                if (centerDelay_ms != newCenterDelay)
                {
                    centerDelay_ms = newCenterDelay;
                    needsUpdate = true;
                }
            }
            else if (P == 2) // Right Delay
            {
                double newRightDelay = jlimit(0.0, maxDelayTime_ms, v);
                if (rightDelay_ms != newRightDelay)
                {
                    rightDelay_ms = newRightDelay;
                    needsUpdate = true;
                }
            }
            else if (P == 3) // Center Feedback
            {
                double newFeedback = jlimit(0.0, 95.0, v);
                if (centerFeedback_pct != newFeedback)
                {
                    centerFeedback_pct = newFeedback;
                    needsUpdate = true;
                }
            }
            else if (P == 4) // Filter 1 Frequency
            {
                double newFreq = jlimit(100.0, 15000.0, v);
                if (filter1Freq_Hz != newFreq)
                {
                    filter1Freq_Hz = newFreq;
                    needsUpdate = true;
                }
            }
            else if (P == 5) // Filter 2 Frequency
            {
                double newFreq = jlimit(100.0, 15000.0, v);
                if (filter2Freq_Hz != newFreq)
                {
                    filter2Freq_Hz = newFreq;
                    needsUpdate = true;
                }
            }
            else if (P == 6) // Filter 1 Enable
            {
                bool newEnable = v > 0.5;
                if (enableFilter1 != newEnable)
                {
                    enableFilter1 = newEnable;
                    needsUpdate = true;
                }
            }
            else if (P == 7) // Filter 2 Enable
            {
                bool newEnable = v > 0.5;
                if (enableFilter2 != newEnable)
                {
                    enableFilter2 = newEnable;
                    needsUpdate = true;
                }
            }
            else if (P == 8) // Wet Level
            {
                double newWetLevel = jlimit(-60.0, 12.0, v);
                if (wetLevel_dB != newWetLevel)
                {
                    wetLevel_dB = newWetLevel;
                    needsUpdate = true;
                }
            }
            else if (P == 9) // Dry Level
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
                parameter::data p("LeftDelay", { 0.0, maxDelayTime_ms });
                registerCallback<0>(p);
                p.setDefaultValue(200.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("CenterDelay", { 0.0, maxDelayTime_ms });
                registerCallback<1>(p);
                p.setDefaultValue(300.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("RightDelay", { 0.0, maxDelayTime_ms });
                registerCallback<2>(p);
                p.setDefaultValue(250.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("CenterFeedback", { 0.0, 95.0 });
                registerCallback<3>(p);
                p.setDefaultValue(15.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Filter1Freq", { 100.0, 15000.0 });
                registerCallback<4>(p);
                p.setDefaultValue(2000.0);
                p.setSkewForCentre(1000.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Filter2Freq", { 100.0, 15000.0 });
                registerCallback<5>(p);
                p.setDefaultValue(8000.0);
                p.setSkewForCentre(1000.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Filter1Enable", { 0.0, 1.0, 1.0 });
                registerCallback<6>(p);
                p.setDefaultValue(0.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Filter2Enable", { 0.0, 1.0, 1.0 });
                registerCallback<7>(p);
                p.setDefaultValue(0.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("WetLevel", { -60.0, 12.0 });
                registerCallback<8>(p);
                p.setDefaultValue(-3.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("DryLevel", { -60.0, 12.0 });
                registerCallback<9>(p);
                p.setDefaultValue(-3.0);
                data.add(std::move(p));
            }
        }

    private:
        void updateDelayParameters()
        {
            // Convert dB levels to linear
            wetMix = Decibels::decibelsToGain(wetLevel_dB);
            dryMix = Decibels::decibelsToGain(dryLevel_dB);
            centerFeedback = jlimit(0.0, 0.95, centerFeedback_pct / 100.0);

            // Update delay line parameters
            SimpleDelayParameters leftParams;
            leftParams.delayTime_mSec = leftDelay_ms;
            leftParams.interpolate = true;
            leftDelay.setParameters(leftParams);

            SimpleDelayParameters centerParams;
            centerParams.delayTime_mSec = centerDelay_ms;
            centerParams.interpolate = true;
            centerDelay.setParameters(centerParams);

            SimpleDelayParameters rightParams;
            rightParams.delayTime_mSec = rightDelay_ms;
            rightParams.interpolate = true;
            rightDelay.setParameters(rightParams);

            // Configure filters for center feedback path
            AudioFilterParameters filter1Params;
            filter1Params.algorithm = filterAlgorithm::kLPF1;
            filter1Params.fc = filter1Freq_Hz;
            filter1Params.Q = 0.707;
            filter1Params.boostCut_dB = 0.0;
            centerFilter1.setParameters(filter1Params);

            AudioFilterParameters filter2Params;
            filter2Params.algorithm = filterAlgorithm::kLPF1;
            filter2Params.fc = filter2Freq_Hz;
            filter2Params.Q = 0.707;
            filter2Params.boostCut_dB = 0.0;
            centerFilter2.setParameters(filter2Params);
        }
    };

} // namespace project

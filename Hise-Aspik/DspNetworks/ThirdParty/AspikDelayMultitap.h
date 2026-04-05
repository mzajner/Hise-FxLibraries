/*
==========================| ASPIK Multi-Tap Delay |==========================
Multi-tap delay with four taps like Roland Space Echo
Based on Chapter 14.7.2 - Multi-Tap Delay (Homework #1)
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
    struct AspikDelayMultitap : public data::base
    {
        SNEX_NODE(AspikDelayMultitap);

        struct MetadataClass
        {
            SN_NODE_ID("AspikDelayMultitap");
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

        // Use SimpleDelay for main delay line with multiple read taps
        SimpleDelay delayLine;

        // Parameters
        double delayTime_ms = 500.0;    // Main delay time
        double tap1Level_dB = -6.0;     // First tap level
        double tap2Level_dB = -9.0;     // Second tap level  
        double tap3Level_dB = -12.0;    // Third tap level
        double tap4Level_dB = -15.0;    // Fourth tap level
        double feedback_pct = 20.0;     // Only longest tap feeds back
        double dryLevel_dB = -3.0;

        // Tap timing ratios (as fractions of main delay time)
        static constexpr double tap1Ratio = 0.25;  // 1/4 delay time
        static constexpr double tap2Ratio = 0.5;   // 1/2 delay time
        static constexpr double tap3Ratio = 0.75;  // 3/4 delay time
        static constexpr double tap4Ratio = 1.0;   // Full delay time

        double tap1Mix = 0.5;
        double tap2Mix = 0.35;
        double tap3Mix = 0.25;
        double tap4Mix = 0.18;
        double dryMix = 0.707;
        double feedback = 0.2;

        static constexpr double maxDelayTime_ms = 2000.0;

        AspikDelayMultitap()
        {
            updateDelayParameters();
        }

        void prepare(PrepareSpecs specs)
        {
            delayLine.reset(specs.sampleRate);
            delayLine.createDelayBuffer(specs.sampleRate, maxDelayTime_ms);
            updateDelayParameters();
        }

        void reset()
        {
            delayLine.reset(44100.0);
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
            double input = (data[0] + data[1]) * 0.5; // Mono-ize input

            // Read all four taps at different delay times
            double tap1 = delayLine.readDelayAtTime_mSec(delayTime_ms * tap1Ratio);
            double tap2 = delayLine.readDelayAtTime_mSec(delayTime_ms * tap2Ratio);
            double tap3 = delayLine.readDelayAtTime_mSec(delayTime_ms * tap3Ratio);
            double tap4 = delayLine.readDelayAtTime_mSec(delayTime_ms * tap4Ratio);

            // Only the longest tap (tap4) provides feedback
            double delayInput = input + feedback * tap4;

            // Write input + feedback to delay line
            delayLine.writeDelay(delayInput);

            // Mix all taps together with their individual levels
            double wetOutput = tap1Mix * tap1 +
                tap2Mix * tap2 +
                tap3Mix * tap3 +
                tap4Mix * tap4;

            // Combine with dry signal
            double output = dryMix * input + wetOutput;

            data[0] = (float)output;
            data[1] = (float)output;
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
                double newDelayTime = jlimit(1.0, maxDelayTime_ms, v);
                if (delayTime_ms != newDelayTime)
                {
                    delayTime_ms = newDelayTime;
                    needsUpdate = true;
                }
            }
            else if (P == 1) // Tap 1 Level
            {
                double newTap1Level = jlimit(-60.0, 12.0, v);
                if (tap1Level_dB != newTap1Level)
                {
                    tap1Level_dB = newTap1Level;
                    needsUpdate = true;
                }
            }
            else if (P == 2) // Tap 2 Level
            {
                double newTap2Level = jlimit(-60.0, 12.0, v);
                if (tap2Level_dB != newTap2Level)
                {
                    tap2Level_dB = newTap2Level;
                    needsUpdate = true;
                }
            }
            else if (P == 3) // Tap 3 Level
            {
                double newTap3Level = jlimit(-60.0, 12.0, v);
                if (tap3Level_dB != newTap3Level)
                {
                    tap3Level_dB = newTap3Level;
                    needsUpdate = true;
                }
            }
            else if (P == 4) // Tap 4 Level
            {
                double newTap4Level = jlimit(-60.0, 12.0, v);
                if (tap4Level_dB != newTap4Level)
                {
                    tap4Level_dB = newTap4Level;
                    needsUpdate = true;
                }
            }
            else if (P == 5) // Feedback
            {
                double newFeedback = jlimit(0.0, 95.0, v);
                if (feedback_pct != newFeedback)
                {
                    feedback_pct = newFeedback;
                    needsUpdate = true;
                }
            }
            else if (P == 6) // Dry Level
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
                parameter::data p("DelayTime", { 1.0, maxDelayTime_ms });
                registerCallback<0>(p);
                p.setDefaultValue(500.0);
                p.setSkewForCentre(500.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Tap1Level", { -60.0, 12.0 });
                registerCallback<1>(p);
                p.setDefaultValue(-6.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Tap2Level", { -60.0, 12.0 });
                registerCallback<2>(p);
                p.setDefaultValue(-9.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Tap3Level", { -60.0, 12.0 });
                registerCallback<3>(p);
                p.setDefaultValue(-12.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Tap4Level", { -60.0, 12.0 });
                registerCallback<4>(p);
                p.setDefaultValue(-15.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Feedback", { 0.0, 95.0 });
                registerCallback<5>(p);
                p.setDefaultValue(20.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("DryLevel", { -60.0, 12.0 });
                registerCallback<6>(p);
                p.setDefaultValue(-3.0);
                data.add(std::move(p));
            }
        }

    private:
        void updateDelayParameters()
        {
            // Convert dB levels to linear multipliers
            tap1Mix = Decibels::decibelsToGain(tap1Level_dB);
            tap2Mix = Decibels::decibelsToGain(tap2Level_dB);
            tap3Mix = Decibels::decibelsToGain(tap3Level_dB);
            tap4Mix = Decibels::decibelsToGain(tap4Level_dB);
            dryMix = Decibels::decibelsToGain(dryLevel_dB);

            // Set feedback (limit to prevent instability)
            feedback = jlimit(0.0, 0.95, feedback_pct / 100.0);

            // Update SimpleDelay parameters
            SimpleDelayParameters params;
            params.delayTime_mSec = delayTime_ms;
            params.interpolate = true;
            delayLine.setParameters(params);
        }
    };

} // namespace project

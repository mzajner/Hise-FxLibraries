/*
==========================| ASPIK Envelope Follower |==========================
Real-time audio envelope detection with visual feedback
• Tracks Peak, RMS, or Mean-Square envelope of input signal
• Provides modulation output for parameter control
• Visual display buffer shows envelope response in real-time
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
    struct AspikUtilEnvFollower : public data::display_buffer_base<true>
    {
        SNEX_NODE(AspikUtilEnvFollower);

        struct MetadataClass
        {
            SN_NODE_ID("AspikUtilEnvFollower");
        };

        static constexpr bool isModNode() { return true; }
        static constexpr bool isPolyphonic() { return NV > 1; }
        static constexpr bool hasTail() { return false; }
        static constexpr bool isSuspendedOnSilence() { return false; }
        static constexpr int getFixChannelAmount() { return 2; }

        static constexpr int NumTables = 0;
        static constexpr int NumSliderPacks = 0;
        static constexpr int NumAudioFiles = 0;
        static constexpr int NumFilters = 0;
        static constexpr int NumDisplayBuffers = 1;

        AudioDetector detector;

        double attackTime = 1.0;
        double releaseTime = 100.0;
        int detectionMode = 2;
        bool outputInDB = false;

        double max = 0.0;

        PolyHandler* handler = nullptr;

        AspikUtilEnvFollower()
        {
            updateDetectorParameters();
        }

        void prepare(PrepareSpecs specs)
        {
            handler = specs.voiceIndex;

            if (handler != nullptr && !handler->isEnabled())
                handler = nullptr;

            display_buffer_base<true>::prepare(specs);
            detector.reset(specs.sampleRate);
            updateDetectorParameters();
            max = 0.0;
        }

        void reset()
        {
            detector.reset(44100.0);
            max = 0.0;

            if (rb != nullptr)
                rb->clear();
        }

        void handleHiseEvent(HiseEvent& e) {}

        template <typename T> void process(T& data)
        {
            static constexpr int NumChannels = getFixChannelAmount();
            auto& fixData = data.template as<ProcessData<NumChannels>>();

            max = 0.0;
            auto fd = fixData.toFrameData();

            while (fd.next())
            {
                processFrame(fd.toSpan());
            }

            if (handler == nullptr || handler->getVoiceIndex() == 0)
                updateBuffer(max, data.getNumSamples());
        }

        template <typename T> void processFrame(T& data)
        {
            double leftInput = data[0];
            double rightInput = data[1];

            double stereoInput = std::max(std::abs(leftInput), std::abs(rightInput));
            double envelopeOutput = detector.processAudioSample(stereoInput);

            // Ensure envelope output is in proper range for display [0.0, 1.0]
            double normalizedEnvelope = jlimit(0.0, 1.0, envelopeOutput);

            // Track the maximum envelope value for this block
            max = std::max(max, normalizedEnvelope);
        }

        int handleModulation(double& value)
        {
            value = max;
            return 1;
        }

        void setExternalData(const ExternalData& data, int index)
        {
            // This is crucial - the display buffer base needs this!
            display_buffer_base<true>::setExternalData(data, index);
        }

        template <int P> void setParameter(double v)
        {
            bool needsUpdate = false;

            if (P == 0)
            {
                double newAttack = jlimit(0.1, 100.0, v);
                if (attackTime != newAttack)
                {
                    attackTime = newAttack;
                    needsUpdate = true;
                }
            }
            else if (P == 1)
            {
                double newRelease = jlimit(1.0, 1000.0, v);
                if (releaseTime != newRelease)
                {
                    releaseTime = newRelease;
                    needsUpdate = true;
                }
            }
            else if (P == 2)
            {
                int newMode = jlimit(0, 2, (int)v);
                if (detectionMode != newMode)
                {
                    detectionMode = newMode;
                    needsUpdate = true;
                }
            }
            else if (P == 3)
            {
                bool newOutputDB = v >= 0.5;
                if (outputInDB != newOutputDB)
                {
                    outputInDB = newOutputDB;
                    needsUpdate = true;
                }
            }

            if (needsUpdate)
            {
                updateDetectorParameters();
            }
        }

        void createParameters(ParameterDataList& data)
        {
            {
                parameter::data p("Attack", { 0.1, 100.0 });
                registerCallback<0>(p);
                p.setDefaultValue(1.0);
                p.setSkewForCentre(10.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Release", { 1.0, 1000.0 });
                registerCallback<1>(p);
                p.setDefaultValue(100.0);
                p.setSkewForCentre(100.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Mode", { 0.0, 2.0 });
                registerCallback<2>(p);
                p.setDefaultValue(2.0);

                StringArray modeNames;
                modeNames.add("Peak");
                modeNames.add("Mean Square");
                modeNames.add("RMS");

                p.setParameterValueNames(modeNames);
                data.add(std::move(p));
            }

            {
                parameter::data p("Scale", { 0.0, 1.0 });
                registerCallback<3>(p);
                p.setDefaultValue(0.0);

                StringArray scaleNames;
                scaleNames.add("Linear");
                scaleNames.add("dB");

                p.setParameterValueNames(scaleNames);
                data.add(std::move(p));
            }
        }

    private:
        void updateDetectorParameters()
        {
            AudioDetectorParameters params;

            switch (detectionMode)
            {
            case 0: params.detectMode = TLD_AUDIO_DETECT_MODE_PEAK; break;
            case 1: params.detectMode = TLD_AUDIO_DETECT_MODE_MS; break;
            case 2: params.detectMode = TLD_AUDIO_DETECT_MODE_RMS; break;
            default: params.detectMode = TLD_AUDIO_DETECT_MODE_RMS; break;
            }

            params.attackTime_mSec = attackTime;
            params.releaseTime_mSec = releaseTime;
            params.detect_dB = outputInDB;
            params.clampToUnityMax = true;

            detector.setParameters(params);
        }
    };

} // namespace project

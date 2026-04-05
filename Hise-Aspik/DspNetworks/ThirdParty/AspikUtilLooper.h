/*
==========================| ASPIK Looper |==========================
Basic looper with reverse playback using circular buffers
Based on Chapter 14 - Homework #5: looping and tape-reverse effects
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
    struct AspikUtilLooper : public data::base
    {
        SNEX_NODE(AspikUtilLooper);

        struct MetadataClass
        {
            SN_NODE_ID("AspikUtilLooper");
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

        // Use CircularBuffer for the looper buffer
        CircularBuffer<double> loopBuffer;

        // Looper state variables
        enum class LooperState
        {
            Stopped = 0,
            Recording,
            Playing,
            Overdubbing
        };

        // Parameters
        double loopLength_sec = 4.0;           // Maximum loop length
        double feedback_pct = 95.0;            // Overdub feedback
        double wetLevel_dB = 0.0;             // Loop playback level
        double dryLevel_dB = 0.0;             // Input passthrough level
        int looperState = 0;                  // 0=Stop, 1=Record, 2=Play, 3=Overdub
        bool reversePlayback = false;         // Forward/reverse toggle
        bool clearLoop = false;               // Clear loop trigger

        // Internal state
        LooperState currentState = LooperState::Stopped;
        LooperState previousState = LooperState::Stopped;
        unsigned int loopLengthSamples = 0;
        unsigned int recordedLength = 0;      // Actual recorded length
        unsigned int recordIndex = 0;         // Current recording position
        unsigned int playbackIndex = 0;       // Current playback position
        double sampleRate = 44100.0;
        double wetMix = 1.0;
        double dryMix = 1.0;
        double feedback = 0.95;
        bool isRecording = false;
        bool hasRecordedAudio = false;

        // Manual buffer for looper (CircularBuffer is for delays)
        std::unique_ptr<double[]> looperBuffer;
        unsigned int bufferSize = 0;

        static constexpr double maxLoopLength_sec = 10.0;

        AspikUtilLooper()
        {
            updateLooperParameters();
        }

        void prepare(PrepareSpecs specs)
        {
            sampleRate = specs.sampleRate;
            bufferSize = (unsigned int)(maxLoopLength_sec * sampleRate);

            // Create our own buffer for looping
            looperBuffer.reset(new double[bufferSize]);
            memset(looperBuffer.get(), 0, bufferSize * sizeof(double));

            updateLooperParameters();
        }

        void reset()
        {
            if (looperBuffer)
                memset(looperBuffer.get(), 0, bufferSize * sizeof(double));
            recordIndex = 0;
            playbackIndex = 0;
            recordedLength = 0;
            hasRecordedAudio = false;
            currentState = LooperState::Stopped;
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
            // Get mono input (sum to mono for looper)
            double input = (data[0] + data[1]) * 0.5;
            double output = 0.0;

            // Handle clear loop trigger
            if (clearLoop)
            {
                if (looperBuffer)
                    memset(looperBuffer.get(), 0, bufferSize * sizeof(double));
                recordIndex = 0;
                playbackIndex = 0;
                recordedLength = 0;
                hasRecordedAudio = false;
                currentState = LooperState::Stopped;
                clearLoop = false; // Reset trigger
            }

            // Handle state changes
            handleStateChanges();

            // Process based on current state
            switch (currentState)
            {
            case LooperState::Stopped:
                output = 0.0;
                break;

            case LooperState::Recording:
                // Record input into buffer
                if (looperBuffer && recordIndex < bufferSize)
                {
                    looperBuffer[recordIndex] = input;
                    recordIndex++;
                    recordedLength = recordIndex; // Track how much we've recorded

                    // Check if we've reached max loop length
                    if (recordIndex >= (unsigned int)(loopLength_sec * sampleRate))
                    {
                        // Stop recording and start playing
                        currentState = LooperState::Playing;
                        playbackIndex = 0;
                        hasRecordedAudio = true;
                    }
                }

                output = input; // Pass through input during recording
                break;

            case LooperState::Playing:
                if (hasRecordedAudio && recordedLength > 0 && looperBuffer)
                {
                    // Read from buffer at playback position
                    if (reversePlayback)
                    {
                        // Read backwards
                        unsigned int reverseIndex = recordedLength - 1 - playbackIndex;
                        output = looperBuffer[reverseIndex];
                    }
                    else
                    {
                        // Read forwards
                        output = looperBuffer[playbackIndex];
                    }

                    // Advance playback position
                    playbackIndex++;
                    if (playbackIndex >= recordedLength)
                    {
                        playbackIndex = 0; // Loop back to start
                    }
                }
                else
                {
                    output = 0.0;
                }
                break;

            case LooperState::Overdubbing:
                if (hasRecordedAudio && recordedLength > 0 && looperBuffer)
                {
                    // Read existing audio
                    double existingAudio;
                    if (reversePlayback)
                    {
                        unsigned int reverseIndex = recordedLength - 1 - playbackIndex;
                        existingAudio = looperBuffer[reverseIndex];
                    }
                    else
                    {
                        existingAudio = looperBuffer[playbackIndex];
                    }

                    // Mix with new input (overdub)
                    double overdubMix = feedback * existingAudio + input;

                    // Write back to buffer (at current position)
                    looperBuffer[playbackIndex] = overdubMix;

                    // Output the existing audio
                    output = existingAudio;

                    // Advance playback position
                    playbackIndex++;
                    if (playbackIndex >= recordedLength)
                    {
                        playbackIndex = 0;
                    }
                }
                else
                {
                    output = 0.0;
                }
                break;
            }

            // Apply wet/dry mix and output
            double finalOutput = dryMix * input + wetMix * output;

            data[0] = (float)finalOutput;
            data[1] = (float)finalOutput;
        }

        int handleModulation(double& value)
        {
            return 0;
        }

        void setExternalData(const ExternalData& data, int index) {}

        template <int P> void setParameter(double v)
        {
            bool needsUpdate = false;

            if (P == 0) // Loop Length
            {
                double newLoopLength = jlimit(0.1, maxLoopLength_sec, v);
                if (loopLength_sec != newLoopLength)
                {
                    loopLength_sec = newLoopLength;
                    needsUpdate = true;
                }
            }
            else if (P == 1) // Looper State
            {
                int newState = jlimit(0, 3, (int)v);
                if (looperState != newState)
                {
                    looperState = newState;
                    needsUpdate = true;
                }
            }
            else if (P == 2) // Reverse
            {
                bool newReverse = v > 0.5;
                if (reversePlayback != newReverse)
                {
                    reversePlayback = newReverse;
                    needsUpdate = true;
                }
            }
            else if (P == 3) // Feedback (overdub)
            {
                double newFeedback = jlimit(0.0, 100.0, v);
                if (feedback_pct != newFeedback)
                {
                    feedback_pct = newFeedback;
                    needsUpdate = true;
                }
            }
            else if (P == 4) // Wet Level
            {
                double newWetLevel = jlimit(-60.0, 12.0, v);
                if (wetLevel_dB != newWetLevel)
                {
                    wetLevel_dB = newWetLevel;
                    needsUpdate = true;
                }
            }
            else if (P == 5) // Dry Level
            {
                double newDryLevel = jlimit(-60.0, 12.0, v);
                if (dryLevel_dB != newDryLevel)
                {
                    dryLevel_dB = newDryLevel;
                    needsUpdate = true;
                }
            }
            else if (P == 6) // Clear Loop
            {
                if (v > 0.5)
                {
                    clearLoop = true;
                    needsUpdate = true;
                }
            }

            if (needsUpdate)
            {
                updateLooperParameters();
            }
        }

        void createParameters(ParameterDataList& data)
        {
            {
                parameter::data p("LoopLength", { 0.1, maxLoopLength_sec });
                registerCallback<0>(p);
                p.setDefaultValue(4.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("LooperState", { 0.0, 3.0, 1.0 });
                registerCallback<1>(p);
                p.setDefaultValue(0.0);

                StringArray looperStates;
                looperStates.add("Stop");
                looperStates.add("Record");
                looperStates.add("Play");
                looperStates.add("Overdub");

                p.setParameterValueNames(looperStates);
                data.add(std::move(p));
            }

            {
                parameter::data p("Reverse", { 0.0, 1.0, 1.0 });
                registerCallback<2>(p);
                p.setDefaultValue(0.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Feedback", { 0.0, 100.0 });
                registerCallback<3>(p);
                p.setDefaultValue(95.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("WetLevel", { -60.0, 12.0 });
                registerCallback<4>(p);
                p.setDefaultValue(0.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("DryLevel", { -60.0, 12.0 });
                registerCallback<5>(p);
                p.setDefaultValue(0.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("ClearLoop", { 0.0, 1.0, 1.0 });
                registerCallback<6>(p);
                p.setDefaultValue(0.0);
                data.add(std::move(p));
            }
        }

    private:
        void updateLooperParameters()
        {
            // Convert dB to linear
            wetMix = Decibels::decibelsToGain(wetLevel_dB);
            dryMix = Decibels::decibelsToGain(dryLevel_dB);
            feedback = jlimit(0.0, 1.0, feedback_pct / 100.0);
        }

        void handleStateChanges()
        {
            LooperState newState = static_cast<LooperState>(looperState);

            if (newState != currentState)
            {
                previousState = currentState;
                currentState = newState;

                // Handle state entry actions
                switch (currentState)
                {
                case LooperState::Recording:
                    // Start fresh recording
                    if (looperBuffer)
                        memset(looperBuffer.get(), 0, bufferSize * sizeof(double));
                    recordedLength = 0;
                    recordIndex = 0;
                    playbackIndex = 0;
                    hasRecordedAudio = false;
                    break;

                case LooperState::Playing:
                    // Start playback from beginning
                    playbackIndex = 0;
                    break;

                case LooperState::Overdubbing:
                    // Continue from current playback position
                    break;

                case LooperState::Stopped:
                    // Stop everything
                    playbackIndex = 0;
                    recordIndex = 0;
                    break;
                }
            }
        }
    };

} // namespace project

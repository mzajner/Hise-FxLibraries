/*
==========================| ASPIK Moving Average Filter |==========================
Moving Average (MA) filter with user-controlled window width
Based on Chapter 16.12 - Homework #1
- Simple FIR filter that averages samples in a moving window
- All coefficients equal to 1/(M+1) where M is delay length
- Inherently low-pass smoothing operation
- Window size from 1 to 512 samples
*/

#pragma once
#include <JuceHeader.h>
#include "src/Aspik/aspik.h"

namespace project
{
    using namespace juce;
    using namespace hise;
    using namespace scriptnode;

    template <int NV>
    struct AspikFilterMA : public data::base
    {
        SNEX_NODE(AspikFilterMA);

        struct MetadataClass
        {
            SN_NODE_ID("AspikFilterMA");
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

        // Maximum window size (as shown in Chapter 16 Figure 16.10)
        static constexpr int MAX_WINDOW_SIZE = 512;

        // Circular delay buffers for L/R channels
        span<float, MAX_WINDOW_SIZE> delayBufferL;
        span<float, MAX_WINDOW_SIZE> delayBufferR;

        // Buffer indices
        int writeIndexL = 0;
        int writeIndexR = 0;

        // Running sum for efficiency (avoids recalculating entire sum each sample)
        double runningSumL = 0.0;
        double runningSumR = 0.0;

        // Parameters
        int windowSize = 5; // M+1 (current + M past samples)

        // Coefficient value (1/(M+1))
        double coefficient = 0.2; // 1/5 for default window of 5

        AspikFilterMA()
        {
            // Initialize delay buffers to zero
            for (int i = 0; i < MAX_WINDOW_SIZE; ++i)
            {
                delayBufferL[i] = 0.0f;
                delayBufferR[i] = 0.0f;
            }

            updateParameters();
        }

        void prepare(PrepareSpecs specs)
        {
            // Clear delay buffers
            for (int i = 0; i < MAX_WINDOW_SIZE; ++i)
            {
                delayBufferL[i] = 0.0f;
                delayBufferR[i] = 0.0f;
            }

            writeIndexL = 0;
            writeIndexR = 0;
            runningSumL = 0.0;
            runningSumR = 0.0;

            updateParameters();
        }

        void reset()
        {
            // Clear buffers and running sums
            for (int i = 0; i < MAX_WINDOW_SIZE; ++i)
            {
                delayBufferL[i] = 0.0f;
                delayBufferR[i] = 0.0f;
            }

            writeIndexL = 0;
            writeIndexR = 0;
            runningSumL = 0.0;
            runningSumR = 0.0;
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

            // Process Left Channel
            // Calculate the index of the sample leaving the window
            int oldIndexL = (writeIndexL - windowSize + MAX_WINDOW_SIZE) % MAX_WINDOW_SIZE;
            double oldSampleL = delayBufferL[oldIndexL];

            // Update running sum: subtract old sample, add new sample
            runningSumL = runningSumL - oldSampleL + inputL;

            // Store new sample in delay buffer
            delayBufferL[writeIndexL] = (float)inputL;

            // Calculate output as average of window
            double outputL = runningSumL * coefficient;

            // Advance write index
            writeIndexL = (writeIndexL + 1) % MAX_WINDOW_SIZE;

            // Process Right Channel (identical process)
            int oldIndexR = (writeIndexR - windowSize + MAX_WINDOW_SIZE) % MAX_WINDOW_SIZE;
            double oldSampleR = delayBufferR[oldIndexR];

            runningSumR = runningSumR - oldSampleR + inputR;
            delayBufferR[writeIndexR] = (float)inputR;
            double outputR = runningSumR * coefficient;
            writeIndexR = (writeIndexR + 1) % MAX_WINDOW_SIZE;

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
            if (P == 0) // Window Size
            {
                int newWindowSize = jlimit(1, MAX_WINDOW_SIZE, (int)v);
                if (windowSize != newWindowSize)
                {
                    windowSize = newWindowSize;
                    updateParameters();

                    // Reset running sums when window size changes
                    runningSumL = 0.0;
                    runningSumR = 0.0;

                    // Recalculate running sums for current window
                    for (int i = 0; i < windowSize; ++i)
                    {
                        int indexL = (writeIndexL - i + MAX_WINDOW_SIZE) % MAX_WINDOW_SIZE;
                        int indexR = (writeIndexR - i + MAX_WINDOW_SIZE) % MAX_WINDOW_SIZE;
                        runningSumL += delayBufferL[indexL];
                        runningSumR += delayBufferR[indexR];
                    }
                }
            }
        }

        void createParameters(ParameterDataList& data)
        {
            {
                parameter::data p("WindowSize", { 1.0, (double)MAX_WINDOW_SIZE, 1.0 });
                registerCallback<0>(p);
                p.setDefaultValue(5.0);
                data.add(std::move(p));
            }
        }

    private:
        void updateParameters()
        {
            // Calculate coefficient: 1/(windowSize)
            coefficient = 1.0 / (double)windowSize;
        }
    };

} // namespace project

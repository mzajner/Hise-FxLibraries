/*
==========================| ASPIK Integration/Differentiation Filter |==========================
FIR-based integration and differentiation filters
Based on Chapter 16.12 - Homework #2
• Integration: Trapezoidal rule (running sum with scaling)
• Differentiation: Central difference, backward difference, forward difference
• Multiple algorithms for different characteristics
• Educational tool for numerical analysis concepts
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
    struct AspikFilterIntegrationDiff : public data::base
    {
        SNEX_NODE(AspikFilterIntegrationDiff);

        struct MetadataClass
        {
            SN_NODE_ID("AspikFilterIntegrationDiff");
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

        // Delay line length for differentiation algorithms
        static constexpr int DELAY_LENGTH = 8;

        // Delay buffers for L/R channels
        span<float, DELAY_LENGTH> delayBufferL;
        span<float, DELAY_LENGTH> delayBufferR;

        int writeIndexL = 0;
        int writeIndexR = 0;

        // Running integral for integration algorithms
        double integralL = 0.0;
        double integralR = 0.0;

        // Sample rate for proper scaling
        double sampleRate = 44100.0;
        double dt = 1.0 / 44100.0; // Time step

        // Parameters
        int algorithm = 0; // 0=Integration_Trapezoidal, 1=Integration_Rectangular, 
        // 2=Diff_Forward, 3=Diff_Backward, 4=Diff_Central
        double gain = 1.0; // Output scaling
        double leakage = 0.9999; // Integration leakage to prevent DC buildup

        AspikFilterIntegrationDiff()
        {
            // Initialize delay buffers to zero
            for (int i = 0; i < DELAY_LENGTH; ++i)
            {
                delayBufferL[i] = 0.0f;
                delayBufferR[i] = 0.0f;
            }

            updateParameters();
        }

        void prepare(PrepareSpecs specs)
        {
            sampleRate = specs.sampleRate;
            dt = 1.0 / sampleRate;

            // Clear delay buffers and integrals
            for (int i = 0; i < DELAY_LENGTH; ++i)
            {
                delayBufferL[i] = 0.0f;
                delayBufferR[i] = 0.0f;
            }

            writeIndexL = 0;
            writeIndexR = 0;
            integralL = 0.0;
            integralR = 0.0;

            updateParameters();
        }

        void reset()
        {
            // Clear buffers and integrals
            for (int i = 0; i < DELAY_LENGTH; ++i)
            {
                delayBufferL[i] = 0.0f;
                delayBufferR[i] = 0.0f;
            }

            writeIndexL = 0;
            writeIndexR = 0;
            integralL = 0.0;
            integralR = 0.0;
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
            double outputL = 0.0;
            double outputR = 0.0;

            // Store input in delay buffers
            delayBufferL[writeIndexL] = (float)inputL;
            delayBufferR[writeIndexR] = (float)inputR;

            // Process based on selected algorithm
            switch (algorithm)
            {
            case 0: // Trapezoidal Integration
                outputL = processIntegrationTrapezoidal(inputL, integralL);
                outputR = processIntegrationTrapezoidal(inputR, integralR);
                break;

            case 1: // Rectangular Integration  
                outputL = processIntegrationRectangular(inputL, integralL);
                outputR = processIntegrationRectangular(inputR, integralR);
                break;

            case 2: // Forward Difference
                outputL = processForwardDifference(writeIndexL, delayBufferL);
                outputR = processForwardDifference(writeIndexR, delayBufferR);
                break;

            case 3: // Backward Difference
                outputL = processBackwardDifference(writeIndexL, delayBufferL);
                outputR = processBackwardDifference(writeIndexR, delayBufferR);
                break;

            case 4: // Central Difference
                outputL = processCentralDifference(writeIndexL, delayBufferL);
                outputR = processCentralDifference(writeIndexR, delayBufferR);
                break;
            }

            // Advance write indices
            writeIndexL = (writeIndexL + 1) % DELAY_LENGTH;
            writeIndexR = (writeIndexR + 1) % DELAY_LENGTH;

            // Apply gain
            data[0] = (float)(outputL * gain);
            data[1] = (float)(outputR * gain);
        }

        int handleModulation(double& value)
        {
            return 0;
        }

        void setExternalData(const ExternalData& data, int index) {}

        template <int P> void setParameter(double v)
        {
            if (P == 0) // Algorithm
            {
                int newAlgorithm = jlimit(0, 4, (int)v);
                if (algorithm != newAlgorithm)
                {
                    algorithm = newAlgorithm;
                    // Reset integrals when switching algorithms
                    integralL = 0.0;
                    integralR = 0.0;
                }
            }
            else if (P == 1) // Gain
            {
                gain = jlimit(0.0, 10.0, v);
            }
            else if (P == 2) // Leakage (integration only)
            {
                leakage = jlimit(0.9, 0.99999, v);
            }
        }

        void createParameters(ParameterDataList& data)
        {
            {
                parameter::data p("Algorithm", { 0.0, 4.0, 1.0 });
                registerCallback<0>(p);
                p.setDefaultValue(0.0);
                StringArray algorithms;
                algorithms.add("Integration Trapezoidal");
                algorithms.add("Integration Rectangular");
                algorithms.add("Differentiation Forward");
                algorithms.add("Differentiation Backward");
                algorithms.add("Differentiation Central");
                p.setParameterValueNames(algorithms);
                data.add(std::move(p));
            }

            {
                parameter::data p("Gain", { 0.0, 10.0 });
                registerCallback<1>(p);
                p.setDefaultValue(1.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Leakage", { 0.9, 0.99999 });
                registerCallback<2>(p);
                p.setDefaultValue(0.9999);
                data.add(std::move(p));
            }
        }

    private:
        double processIntegrationTrapezoidal(double input, double& integral)
        {
            // Get previous sample
            int prevIndex = (writeIndexL - 1 + DELAY_LENGTH) % DELAY_LENGTH;
            double prevSample = (writeIndexL == 0) ? 0.0 : delayBufferL[prevIndex];

            // Trapezoidal rule: integral += dt * (y[n] + y[n-1]) / 2
            integral = integral * leakage + dt * (input + prevSample) * 0.5;

            return integral;
        }

        double processIntegrationRectangular(double input, double& integral)
        {
            // Rectangular rule: integral += dt * y[n]
            integral = integral * leakage + dt * input;

            return integral;
        }

        double processForwardDifference(int writeIndex, span<float, DELAY_LENGTH>& buffer)
        {
            // Forward difference: y[n] = x[n+1] - x[n]
            // Since we can't look into future, approximate as x[n] - x[n-1]
            int prevIndex = (writeIndex - 1 + DELAY_LENGTH) % DELAY_LENGTH;
            double current = buffer[writeIndex];
            double previous = (writeIndex == 0) ? 0.0 : buffer[prevIndex];

            return (current - previous) / dt;
        }

        double processBackwardDifference(int writeIndex, span<float, DELAY_LENGTH>& buffer)
        {
            // Backward difference: y[n] = x[n] - x[n-1]
            int prevIndex = (writeIndex - 1 + DELAY_LENGTH) % DELAY_LENGTH;
            double current = buffer[writeIndex];
            double previous = (writeIndex == 0) ? 0.0 : buffer[prevIndex];

            return (current - previous) / dt;
        }

        double processCentralDifference(int writeIndex, span<float, DELAY_LENGTH>& buffer)
        {
            // Central difference: y[n] = (x[n+1] - x[n-1]) / (2*dt)
            // Use x[n] - x[n-2] approximation
            int prev1Index = (writeIndex - 1 + DELAY_LENGTH) % DELAY_LENGTH;
            int prev2Index = (writeIndex - 2 + DELAY_LENGTH) % DELAY_LENGTH;

            double current = buffer[writeIndex];
            double prev2 = buffer[prev2Index];

            return (current - prev2) / (2.0 * dt);
        }

        void updateParameters()
        {
            // Update time step based on sample rate
            dt = 1.0 / sampleRate;
        }
    };

} // namespace project

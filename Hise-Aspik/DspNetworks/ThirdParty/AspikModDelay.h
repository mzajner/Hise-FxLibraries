/*
==========================| ASPIK Modulated Delay |==========================
Basic modulated delay implementing flanger, chorus, and vibrato algorithms
Based on Chapter 15.3 - ModulatedDelay Object
- Uses ASPiK ModulatedDelay object directly
- Supports mono input to stereo output
- Three algorithms: Flanger, Chorus, Vibrato
- Automatic parameter configuration per algorithm type
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
    struct AspikModDelay : public data::base
    {
        SNEX_NODE(AspikModDelay);

        struct MetadataClass
        {
            SN_NODE_ID("AspikModDelay");
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

        // ASPiK ModulatedDelay object - handles all three algorithms
        ModulatedDelay modulatedDelay;

        // Parameters - mapped to ModulatedDelayParameters
        int algorithm = 0; // 0=Flanger, 1=Chorus, 2=Vibrato
        double lfoRate_Hz = 0.5;
        double lfoDepth_Pct = 50.0;
        double feedback_Pct = 15.0;

        AspikModDelay()
        {
            updateModDelayParameters();
        }

        void prepare(PrepareSpecs specs)
        {
            // Reset the ModulatedDelay object for streaming
            modulatedDelay.reset(specs.sampleRate);

            updateModDelayParameters();
        }

        void reset()
        {
            modulatedDelay.reset(44100.0);
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
            // Prepare input/output frame arrays for ModulatedDelay::processAudioFrame
            float inputFrame[2];
            float outputFrame[2];

            // Fill input frame
            inputFrame[0] = data[0];  // Left input
            inputFrame[1] = data[1];  // Right input

            // Process through ModulatedDelay object
            // This automatically handles algorithm-specific processing
            modulatedDelay.processAudioFrame(inputFrame, outputFrame, 2, 2);

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

            if (P == 0) // Algorithm Selection
            {
                int newAlgorithm = jlimit(0, 2, (int)v);
                if (algorithm != newAlgorithm)
                {
                    algorithm = newAlgorithm;
                    needsUpdate = true;
                }
            }
            else if (P == 1) // LFO Rate
            {
                double newRate = jlimit(0.02, 20.0, v);
                if (lfoRate_Hz != newRate)
                {
                    lfoRate_Hz = newRate;
                    needsUpdate = true;
                }
            }
            else if (P == 2) // LFO Depth
            {
                double newDepth = jlimit(0.0, 100.0, v);
                if (lfoDepth_Pct != newDepth)
                {
                    lfoDepth_Pct = newDepth;
                    needsUpdate = true;
                }
            }
            else if (P == 3) // Feedback (disabled for chorus/vibrato automatically)
            {
                double newFeedback = jlimit(-99.0, 99.0, v);
                if (feedback_Pct != newFeedback)
                {
                    feedback_Pct = newFeedback;
                    needsUpdate = true;
                }
            }

            if (needsUpdate)
            {
                updateModDelayParameters();
            }
        }

        void createParameters(ParameterDataList& data)
        {
            {
                parameter::data p("Algorithm", { 0.0, 2.0, 1.0 });
                registerCallback<0>(p);
                p.setDefaultValue(0.0);
                StringArray algorithmTypes;
                algorithmTypes.add("Flanger");
                algorithmTypes.add("Chorus");
                algorithmTypes.add("Vibrato");
                p.setParameterValueNames(algorithmTypes);
                data.add(std::move(p));
            }

            {
                parameter::data p("LfoRate", { 0.02, 20.0 });
                registerCallback<1>(p);
                p.setDefaultValue(0.5);
                p.setSkewForCentre(2.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("LfoDepth", { 0.0, 100.0 });
                registerCallback<2>(p);
                p.setDefaultValue(50.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Feedback", { -99.0, 99.0 });
                registerCallback<3>(p);
                p.setDefaultValue(15.0);
                data.add(std::move(p));
            }
        }

    private:
        void updateModDelayParameters()
        {
            // Configure ModulatedDelayParameters structure
            ModulatedDelayParameters params;

            // Set algorithm based on selection
            if (algorithm == 0)
                params.algorithm = modDelaylgorithm::kFlanger;
            else if (algorithm == 1)
                params.algorithm = modDelaylgorithm::kChorus;
            else if (algorithm == 2)
                params.algorithm = modDelaylgorithm::kVibrato;

            // Set LFO parameters
            params.lfoRate_Hz = lfoRate_Hz;
            params.lfoDepth_Pct = lfoDepth_Pct;

            // Set feedback (automatically disabled for chorus/vibrato by ModulatedDelay)
            params.feedback_Pct = feedback_Pct;

            // Update the ModulatedDelay object
            modulatedDelay.setParameters(params);
        }
    };

} // namespace project

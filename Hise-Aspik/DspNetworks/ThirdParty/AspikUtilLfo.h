/*
==========================| ASPIK LFO |==========================
Low Frequency Oscillator with visual feedback and modulation output
Multiple waveforms: Triangle, Sine, Sawtooth with quadrature outputs
Frequency range: 0.02 Hz to 20 Hz for parameter modulation
Visual display buffer shows real-time LFO waveform
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
    struct AspikUtilLfo : public data::display_buffer_base<true>
    {
        SNEX_NODE(AspikUtilLfo);

        struct MetadataClass
        {
            SN_NODE_ID("AspikUtilLfo");
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

        // ASPIK LFO Object
        LFO lfo;

        // Parameters
        double frequency = 1.0;
        int waveform = 0;
        double depth = 1.0;
        bool bipolar = true;
        int outputSelect = 0;

        // Internal state
        double sampleRate = 44100.0;
        double max = 0.0;

        PolyHandler* handler = nullptr;

        AspikUtilLfo()
        {
            updateLfoParameters();
        }

        void prepare(PrepareSpecs specs)
        {
            sampleRate = specs.sampleRate;
            handler = specs.voiceIndex;

            if (handler != nullptr && !handler->isEnabled())
                handler = nullptr;

            display_buffer_base<true>::prepare(specs);
            lfo.reset(sampleRate);
            updateLfoParameters();
            max = 0.0;
        }

        void reset()
        {
            lfo.reset(sampleRate);
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
            SignalGenData lfoOutput = lfo.renderAudioOutput();

            double rawOutput = 0.0;
            switch (outputSelect)
            {
            case 0: rawOutput = lfoOutput.normalOutput; break;
            case 1: rawOutput = lfoOutput.invertedOutput; break;
            case 2: rawOutput = lfoOutput.quadPhaseOutput_pos; break;
            case 3: rawOutput = lfoOutput.quadPhaseOutput_neg; break;
            default: rawOutput = lfoOutput.normalOutput; break;
            }

            // Apply depth scaling
            rawOutput *= depth;

            double finalOutput = rawOutput;
            if (!bipolar)
            {
                finalOutput = (rawOutput + 1.0) * 0.5;
            }

            // Ensure LFO output is in proper range for display
            double normalizedOutput = bipolar ? jlimit(-1.0, 1.0, finalOutput) : jlimit(0.0, 1.0, finalOutput);

            // Track the current LFO value for this block
            max = normalizedOutput;
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
            if (P == 0)
            {
                if (frequency != v)
                {
                    frequency = jlimit(0.02, 20.0, v);
                    updateLfoParameters();
                }
            }
            else if (P == 1)
            {
                int newWaveform = jlimit(0, 2, (int)v);
                if (waveform != newWaveform)
                {
                    waveform = newWaveform;
                    updateLfoParameters();
                }
            }
            else if (P == 2)
            {
                double newDepth = jlimit(0.0, 1.0, v);
                if (depth != newDepth)
                {
                    depth = newDepth;
                }
            }
            else if (P == 3)
            {
                bool newBipolar = v >= 0.5;
                if (bipolar != newBipolar)
                {
                    bipolar = newBipolar;
                }
            }
            else if (P == 4)
            {
                int newOutput = jlimit(0, 3, (int)v);
                if (outputSelect != newOutput)
                {
                    outputSelect = newOutput;
                }
            }
        }

        void createParameters(ParameterDataList& data)
        {
            {
                parameter::data p("Frequency", { 0.02, 20.0 });
                registerCallback<0>(p);
                p.setDefaultValue(1.0);
                p.setSkewForCentre(2.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Waveform", { 0.0, 2.0 });
                registerCallback<1>(p);
                p.setDefaultValue(0.0);

                StringArray waveformNames;
                waveformNames.add("Triangle");
                waveformNames.add("Sine");
                waveformNames.add("Sawtooth");

                p.setParameterValueNames(waveformNames);
                data.add(std::move(p));
            }

            {
                parameter::data p("Depth", { 0.0, 1.0 });
                registerCallback<2>(p);
                p.setDefaultValue(1.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("Mode", { 0.0, 1.0 });
                registerCallback<3>(p);
                p.setDefaultValue(1.0);

                StringArray modeNames;
                modeNames.add("Unipolar");
                modeNames.add("Bipolar");

                p.setParameterValueNames(modeNames);
                data.add(std::move(p));
            }

            {
                parameter::data p("Output", { 0.0, 3.0 });
                registerCallback<4>(p);
                p.setDefaultValue(0.0);

                StringArray outputNames;
                outputNames.add("Normal");
                outputNames.add("Inverted");
                outputNames.add("QuadPhase+");
                outputNames.add("QuadPhase-");

                p.setParameterValueNames(outputNames);
                data.add(std::move(p));
            }
        }

    private:
        void updateLfoParameters()
        {
            OscillatorParameters params;
            params.frequency_Hz = frequency;

            switch (waveform)
            {
            case 0: params.waveform = generatorWaveform::kTriangle; break;
            case 1: params.waveform = generatorWaveform::kSin; break;
            case 2: params.waveform = generatorWaveform::kSaw; break;
            default: params.waveform = generatorWaveform::kTriangle; break;
            }

            lfo.setParameters(params);
        }
    };

} // namespace project

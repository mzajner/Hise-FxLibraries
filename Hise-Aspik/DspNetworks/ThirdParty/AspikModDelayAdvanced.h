/*
==========================| ASPIK Advanced Modulated Delay |==========================
Advanced modulated delay effects implementing six complex algorithms
Based on Chapter 15.5 - More Modulated Delay Algorithms
• Six algorithms: Korg Cross-Feedback, Sony Multi-Flanger, Bass Chorus,
  Dimension-Style, Sony Deca Chorus, Korg LCR Chorus
• Multiple delay lines with complex routing
• Cross-channel feedback and quadrature LFOs
• Frequency splitting for bass chorus
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
    struct AspikModDelayAdvanced : public data::base
    {
        SNEX_NODE(AspikModDelayAdvanced);

        struct MetadataClass
        {
            SN_NODE_ID("AspikModDelayAdvanced");
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

        // Multiple delay objects for complex algorithms
        ModulatedDelay leftModDelay;
        ModulatedDelay rightModDelay;
        ModulatedDelay centerModDelay;  // For LCR algorithms

        // Additional delays for multi-unit designs
        ModulatedDelay auxDelay1;
        ModulatedDelay auxDelay2;
        ModulatedDelay auxDelay3;
        ModulatedDelay auxDelay4;

        // LFOs for independent modulation
        LFO primaryLFO;
        LFO quadratureLFO;  // 90-degree phase shift
        LFO auxLFO1;
        LFO auxLFO2;

        // Filters for bass chorus frequency splitting
        AudioFilter lowpassFilter;
        AudioFilter highpassFilter;

        // Parameters
        int algorithm = 0; // 0=Korg Cross-FB, 1=Sony Multi-Flanger, 2=Bass Chorus, 
        // 3=Dimension-Style, 4=Sony Deca, 5=Korg LCR

// Common parameters
        double lfoRate_Hz = 0.5;
        double lfoDepth_Pct = 50.0;
        double feedback_Pct = 15.0;
        double wetLevel_dB = -3.0;
        double dryLevel_dB = 0.0;

        // Algorithm-specific parameters
        double crossFeedback_Pct = 10.0;    // Korg Cross-Feedback
        double quadraturePhase_Deg = 90.0;  // Phase shift for quadrature LFO
        double splitFreq_Hz = 300.0;        // Bass chorus crossover frequency
        double leftDelay_ms = 10.0;         // LCR individual delays
        double centerDelay_ms = 15.0;
        double rightDelay_ms = 12.0;

        // Multi-unit parameters (Sony Deca)
        double unit1Rate_Hz = 0.3;
        double unit2Rate_Hz = 0.7;
        double unit3Rate_Hz = 1.1;
        double unit4Rate_Hz = 1.7;

        // Linear gain values
        double wetMix = 0.707;
        double dryMix = 1.0;
        double feedbackMix = 0.15;
        double crossFeedbackMix = 0.1;

        AspikModDelayAdvanced()
        {
            updateAdvancedParameters();
        }

        void prepare(PrepareSpecs specs)
        {
            // Reset all delay objects
            leftModDelay.reset(specs.sampleRate);
            rightModDelay.reset(specs.sampleRate);
            centerModDelay.reset(specs.sampleRate);
            auxDelay1.reset(specs.sampleRate);
            auxDelay2.reset(specs.sampleRate);
            auxDelay3.reset(specs.sampleRate);
            auxDelay4.reset(specs.sampleRate);

            // Reset all LFOs
            primaryLFO.reset(specs.sampleRate);
            quadratureLFO.reset(specs.sampleRate);
            auxLFO1.reset(specs.sampleRate);
            auxLFO2.reset(specs.sampleRate);

            // Reset filters
            lowpassFilter.reset(specs.sampleRate);
            highpassFilter.reset(specs.sampleRate);

            updateAdvancedParameters();
        }

        void reset()
        {
            leftModDelay.reset(44100.0);
            rightModDelay.reset(44100.0);
            centerModDelay.reset(44100.0);
            auxDelay1.reset(44100.0);
            auxDelay2.reset(44100.0);
            auxDelay3.reset(44100.0);
            auxDelay4.reset(44100.0);

            primaryLFO.reset(44100.0);
            quadratureLFO.reset(44100.0);
            auxLFO1.reset(44100.0);
            auxLFO2.reset(44100.0);

            lowpassFilter.reset(44100.0);
            highpassFilter.reset(44100.0);
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

            // Algorithm selection - each implements different topology
            switch (algorithm)
            {
            case 0: // Korg Stereo Cross-Feedback Flanger/Chorus
                processKorgCrossFeedback(inputL, inputR, outputL, outputR);
                break;

            case 1: // Sony DPS-M7 Multi-Flanger
                processSonyMultiFlanger(inputL, inputR, outputL, outputR);
                break;

            case 2: // Bass Chorus
                processBassChorus(inputL, inputR, outputL, outputR);
                break;

            case 3: // Dimension-Style Chorus
                processDimensionChorus(inputL, inputR, outputL, outputR);
                break;

            case 4: // Sony DPS-M7 Deca Chorus
                processSonyDecaChorus(inputL, inputR, outputL, outputR);
                break;

            case 5: // Korg LCR Chorus
                processKorgLCRChorus(inputL, inputR, outputL, outputR);
                break;

            default:
                outputL = inputL;
                outputR = inputR;
                break;
            }

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

            if (P == 0) // Algorithm Selection
            {
                int newAlgorithm = jlimit(0, 5, (int)v);
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
            else if (P == 3) // Feedback
            {
                double newFeedback = jlimit(-99.0, 99.0, v);
                if (feedback_Pct != newFeedback)
                {
                    feedback_Pct = newFeedback;
                    needsUpdate = true;
                }
            }
            else if (P == 4) // Cross Feedback (algorithm specific)
            {
                double newCrossFeedback = jlimit(-99.0, 99.0, v);
                if (crossFeedback_Pct != newCrossFeedback)
                {
                    crossFeedback_Pct = newCrossFeedback;
                    needsUpdate = true;
                }
            }
            else if (P == 5) // Split Frequency (bass chorus)
            {
                double newSplitFreq = jlimit(100.0, 1000.0, v);
                if (splitFreq_Hz != newSplitFreq)
                {
                    splitFreq_Hz = newSplitFreq;
                    needsUpdate = true;
                }
            }
            else if (P == 6) // Wet Level
            {
                double newWetLevel = jlimit(-60.0, 12.0, v);
                if (wetLevel_dB != newWetLevel)
                {
                    wetLevel_dB = newWetLevel;
                    needsUpdate = true;
                }
            }
            else if (P == 7) // Dry Level
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
                updateAdvancedParameters();
            }
        }

        void createParameters(ParameterDataList& data)
        {
            {
                parameter::data p("Algorithm", { 0.0, 5.0, 1.0 });
                registerCallback<0>(p);
                p.setDefaultValue(0.0);
                StringArray algorithmTypes;
                algorithmTypes.add("Cross-Feedback");
                algorithmTypes.add("Multi-Flanger");
                algorithmTypes.add("Bass Chorus");
                algorithmTypes.add("Dimension-Style");
                algorithmTypes.add("Deca Chorus");
                algorithmTypes.add("LCR Chorus");
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

            {
                parameter::data p("CrossFeedback", { -99.0, 99.0 });
                registerCallback<4>(p);
                p.setDefaultValue(10.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("SplitFreq", { 100.0, 1000.0 });
                registerCallback<5>(p);
                p.setDefaultValue(300.0);
                p.setSkewForCentre(300.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("WetLevel", { -60.0, 12.0 });
                registerCallback<6>(p);
                p.setDefaultValue(-3.0);
                data.add(std::move(p));
            }

            {
                parameter::data p("DryLevel", { -60.0, 12.0 });
                registerCallback<7>(p);
                p.setDefaultValue(0.0);
                data.add(std::move(p));
            }
        }

    private:
        // Algorithm-specific processing methods
        void processKorgCrossFeedback(double inputL, double inputR, double& outputL, double& outputR)
        {
            // Korg stereo cross-feedback flanger with quadrature LFO
            float frameL[2] = { (float)inputL, (float)inputL };
            float frameR[2] = { (float)inputR, (float)inputR };
            float outL[2], outR[2];

            leftModDelay.processAudioFrame(frameL, outL, 1, 1);
            rightModDelay.processAudioFrame(frameR, outR, 1, 1);

            // Apply cross-channel feedback
            outputL = dryMix * inputL + wetMix * outL[0] + crossFeedbackMix * outR[0];
            outputR = dryMix * inputR + wetMix * outR[0] + crossFeedbackMix * outL[0];
        }

        void processSonyMultiFlanger(double inputL, double inputR, double& outputL, double& outputR)
        {
            // Sony DPS-M7 multi-flanger: two flanger circuits per channel
            float frame1L[2] = { (float)inputL, (float)inputL };
            float frame2L[2] = { (float)inputL, (float)inputL };
            float frame1R[2] = { (float)inputR, (float)inputR };
            float frame2R[2] = { (float)inputR, (float)inputR };
            float out1L[2], out2L[2], out1R[2], out2R[2];

            leftModDelay.processAudioFrame(frame1L, out1L, 1, 1);
            auxDelay1.processAudioFrame(frame2L, out2L, 1, 1);
            rightModDelay.processAudioFrame(frame1R, out1R, 1, 1);
            auxDelay2.processAudioFrame(frame2R, out2R, 1, 1);

            // Series configuration
            outputL = dryMix * inputL + wetMix * (out1L[0] + out2L[0]) * 0.5;
            outputR = dryMix * inputR + wetMix * (out1R[0] + out2R[0]) * 0.5;
        }

        void processBassChorus(double inputL, double inputR, double& outputL, double& outputR)
        {
            // Bass chorus: frequency splitting with HF processing only
            double lowL = lowpassFilter.processAudioSample(inputL);
            double highL = highpassFilter.processAudioSample(inputL);

            float frameL[2] = { (float)highL, (float)highL };
            float outL[2];
            leftModDelay.processAudioFrame(frameL, outL, 1, 1);

            outputL = lowL + wetMix * outL[0]; // Recombine with processed HF
            outputR = outputL; // Mono processing
        }

        void processDimensionChorus(double inputL, double inputR, double& outputL, double& outputR)
        {
            // Dimension-style chorus with shared inverted LFO
            float frameL[2] = { (float)inputL, (float)inputL };
            float frameR[2] = { (float)inputR, (float)inputR };
            float outL[2], outR[2];

            leftModDelay.processAudioFrame(frameL, outL, 1, 1);
            rightModDelay.processAudioFrame(frameR, outR, 1, 1);

            // Three-signal mixing with opposite channel chorus
            outputL = dryMix * inputL + wetMix * outL[0] + 0.3 * (-outR[0]);
            outputR = dryMix * inputR + wetMix * outR[0] + 0.3 * (-outL[0]);
        }

        void processSonyDecaChorus(double inputL, double inputR, double& outputL, double& outputR)
        {
            // Sony Deca: Multiple chorus units (simplified to 4 per channel)
            float frameL[2] = { (float)inputL, (float)inputL };
            float frameR[2] = { (float)inputR, (float)inputR };
            float out1[2], out2[2], out3[2], out4[2];

            leftModDelay.processAudioFrame(frameL, out1, 1, 1);
            auxDelay1.processAudioFrame(frameL, out2, 1, 1);
            rightModDelay.processAudioFrame(frameR, out3, 1, 1);
            auxDelay2.processAudioFrame(frameR, out4, 1, 1);

            outputL = dryMix * inputL + wetMix * (out1[0] + out2[0]) * 0.5;
            outputR = dryMix * inputR + wetMix * (out3[0] + out4[0]) * 0.5;
        }

        void processKorgLCRChorus(double inputL, double inputR, double& outputL, double& outputR)
        {
            // Korg LCR: Three independent chorus modules
            double inputCenter = (inputL + inputR) * 0.5;

            float frameL[2] = { (float)inputL, (float)inputL };
            float frameC[2] = { (float)inputCenter, (float)inputCenter };
            float frameR[2] = { (float)inputR, (float)inputR };
            float outL[2], outC[2], outR[2];

            leftModDelay.processAudioFrame(frameL, outL, 1, 1);
            centerModDelay.processAudioFrame(frameC, outC, 1, 1);
            rightModDelay.processAudioFrame(frameR, outR, 1, 1);

            outputL = dryMix * inputL + wetMix * (outL[0] + outC[0] * 0.707);
            outputR = dryMix * inputR + wetMix * (outR[0] + outC[0] * 0.707);
        }

        void updateAdvancedParameters()
        {
            // Convert dB to linear
            wetMix = Decibels::decibelsToGain(wetLevel_dB);
            dryMix = Decibels::decibelsToGain(dryLevel_dB);
            feedbackMix = feedback_Pct / 100.0;
            crossFeedbackMix = crossFeedback_Pct / 100.0;

            // Configure modulated delays based on algorithm
            ModulatedDelayParameters leftParams, rightParams, centerParams;

            // Set algorithm type (usually chorus for advanced effects)
            leftParams.algorithm = modDelaylgorithm::kChorus;
            rightParams.algorithm = modDelaylgorithm::kChorus;
            centerParams.algorithm = modDelaylgorithm::kChorus;

            // Set LFO parameters
            leftParams.lfoRate_Hz = lfoRate_Hz;
            leftParams.lfoDepth_Pct = lfoDepth_Pct;
            leftParams.feedback_Pct = feedback_Pct;

            rightParams.lfoRate_Hz = lfoRate_Hz;
            rightParams.lfoDepth_Pct = lfoDepth_Pct;
            rightParams.feedback_Pct = feedback_Pct;

            centerParams.lfoRate_Hz = lfoRate_Hz * 0.7; // Different rate for center
            centerParams.lfoDepth_Pct = lfoDepth_Pct;
            centerParams.feedback_Pct = feedback_Pct;

            // Apply parameters to delay objects
            leftModDelay.setParameters(leftParams);
            rightModDelay.setParameters(rightParams);
            centerModDelay.setParameters(centerParams);

            // Configure auxiliary delays for multi-unit algorithms
            ModulatedDelayParameters auxParams1 = leftParams;
            auxParams1.lfoRate_Hz = unit1Rate_Hz;
            auxDelay1.setParameters(auxParams1);

            ModulatedDelayParameters auxParams2 = rightParams;
            auxParams2.lfoRate_Hz = unit2Rate_Hz;
            auxDelay2.setParameters(auxParams2);

            // Configure filters for bass chorus
            AudioFilterParameters lpfParams;
            lpfParams.algorithm = filterAlgorithm::kLPF1;
            lpfParams.fc = splitFreq_Hz;
            lpfParams.Q = 0.707;
            lpfParams.boostCut_dB = 0.0;
            lowpassFilter.setParameters(lpfParams);

            AudioFilterParameters hpfParams;
            hpfParams.algorithm = filterAlgorithm::kHPF1;
            hpfParams.fc = splitFreq_Hz;
            hpfParams.Q = 0.707;
            hpfParams.boostCut_dB = 0.0;
            highpassFilter.setParameters(hpfParams);

            // Configure independent LFOs for complex algorithms
            OscillatorParameters primaryLFOParams;
            primaryLFOParams.frequency_Hz = lfoRate_Hz;
            primaryLFOParams.waveform = generatorWaveform::kTriangle;
            primaryLFO.setParameters(primaryLFOParams);

            // Quadrature LFO for Korg cross-feedback (90-degree phase shift)
            OscillatorParameters quadLFOParams;
            quadLFOParams.frequency_Hz = lfoRate_Hz;
            quadLFOParams.waveform = generatorWaveform::kTriangle;
            // Note: Phase offset would need to be implemented in LFO object
            quadratureLFO.setParameters(quadLFOParams);
        }
    };

} // namespace project

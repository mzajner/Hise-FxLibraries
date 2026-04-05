/*
AspikDynamicsLookAhead - Look-Ahead Dynamics Processor
Uses delay line in forward path to allow detector to "preview" the signal
Based on Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed." Chapter 18.7
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

	template <int NV> struct AspikDynamicsLookahead : public data::base
	{
		SNEX_NODE(AspikDynamicsLookahead);

		struct MetadataClass
		{
			SN_NODE_ID("AspikDynamicsLookahead");
		};

		static constexpr bool isModNode() { return true; };
		static constexpr bool isPolyphonic() { return NV > 1; };
		static constexpr bool hasTail() { return true; };
		static constexpr bool isSuspendedOnSilence() { return true; };
		static constexpr int getFixChannelAmount() { return 2; };

		static constexpr int NumTables = 0;
		static constexpr int NumSliderPacks = 0;
		static constexpr int NumAudioFiles = 0;
		static constexpr int NumFilters = 0;
		static constexpr int NumDisplayBuffers = 0;

		enum Parameters
		{
			AlgorithmType,
			Threshold,
			Ratio,
			KneeWidth,
			AttackTime,
			ReleaseTime,
			OutputGain,
			SoftKnee,
			LookAheadTime
		};

		// ASPIK Objects
		DynamicsProcessor processors[2][NV];
		SimpleDelay delayLines[2][NV];
		DynamicsProcessorParameters parameters[NV];
		SimpleDelayParameters delayParams[NV];

		void prepare(PrepareSpecs specs)
		{
			for (int v = 0; v < NV; v++)
			{
				processors[0][v].reset(specs.sampleRate);
				processors[1][v].reset(specs.sampleRate);

				delayLines[0][v].reset(specs.sampleRate);
				delayLines[1][v].reset(specs.sampleRate);
				delayLines[0][v].createDelayBuffer(specs.sampleRate, 100.0);
				delayLines[1][v].createDelayBuffer(specs.sampleRate, 100.0);

				updateParameters(v);
			}
		}

		void reset()
		{
			for (int v = 0; v < NV; v++)
			{
				processors[0][v].reset(44100.0);
				processors[1][v].reset(44100.0);
				delayLines[0][v].reset(44100.0);
				delayLines[1][v].reset(44100.0);
			}
		}

		void handleHiseEvent(HiseEvent& e)
		{
		}

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
			int voiceIndex = 0;
			if constexpr (NV > 1)
			{
				voiceIndex = data.getVoiceIndex();
			}

			// Store input for sidechain (no delay)
			double inputL = static_cast<double>(data[0]);
			double inputR = static_cast<double>(data[1]);

			// Delay the forward signal path
			double delayedL = delayLines[0][voiceIndex].processAudioSample(inputL);
			double delayedR = delayLines[1][voiceIndex].processAudioSample(inputR);

			// Process delayed signal with dynamics processor using immediate input for detection
			// The detector "previews" the undelayed signal while processing the delayed signal
			double outputL = processWithLookAhead(processors[0][voiceIndex], delayedL, inputL);
			double outputR = processWithLookAhead(processors[1][voiceIndex], delayedR, inputR);

			data[0] = static_cast<float>(outputL);
			data[1] = static_cast<float>(outputR);
		}

		int handleModulation(double& value)
		{
			auto params = processors[0][0].getParameters();
			auto params2 = processors[1][0].getParameters();

			value = 1.0 - ((params.gainReduction + params2.gainReduction) * 0.5);
			return 1;
		}

		void setExternalData(const ExternalData& data, int index)
		{
		}

		template <int P> void setParameter(double v)
		{
			if (P == AlgorithmType)
			{
				int algorithm = static_cast<int>(v);
				for (int i = 0; i < NV; i++)
				{
					switch (algorithm)
					{
					case 0:
						parameters[i].calculation = dynamicsProcessorType::kCompressor;
						parameters[i].hardLimitGate = false;
						break;
					case 1:
						parameters[i].calculation = dynamicsProcessorType::kCompressor;
						parameters[i].hardLimitGate = true;
						break;
					case 2:
						parameters[i].calculation = dynamicsProcessorType::kDownwardExpander;
						parameters[i].hardLimitGate = false;
						break;
					case 3:
						parameters[i].calculation = dynamicsProcessorType::kDownwardExpander;
						parameters[i].hardLimitGate = true;
						break;
					}
					updateParameters(i);
				}
			}
			else if (P == Threshold)
			{
				for (int i = 0; i < NV; i++)
				{
					parameters[i].threshold_dB = v;
					updateParameters(i);
				}
			}
			else if (P == Ratio)
			{
				for (int i = 0; i < NV; i++)
				{
					parameters[i].ratio = v;
					updateParameters(i);
				}
			}
			else if (P == KneeWidth)
			{
				for (int i = 0; i < NV; i++)
				{
					parameters[i].kneeWidth_dB = v;
					updateParameters(i);
				}
			}
			else if (P == AttackTime)
			{
				for (int i = 0; i < NV; i++)
				{
					parameters[i].attackTime_mSec = v;
					updateParameters(i);
				}
			}
			else if (P == ReleaseTime)
			{
				for (int i = 0; i < NV; i++)
				{
					parameters[i].releaseTime_mSec = v;
					updateParameters(i);
				}
			}
			else if (P == OutputGain)
			{
				for (int i = 0; i < NV; i++)
				{
					parameters[i].outputGain_dB = v;
					updateParameters(i);
				}
			}
			else if (P == SoftKnee)
			{
				for (int i = 0; i < NV; i++)
				{
					parameters[i].softKnee = (v >= 0.5);
					updateParameters(i);
				}
			}
			else if (P == LookAheadTime)
			{
				for (int i = 0; i < NV; i++)
				{
					delayParams[i].delayTime_mSec = v;
					delayLines[0][i].setParameters(delayParams[i]);
					delayLines[1][i].setParameters(delayParams[i]);
				}
			}
		}

		void createParameters(ParameterDataList& data)
		{
			{
				parameter::data p("Algorithm", { 0.0, 3.0, 1.0 });
				registerCallback<AlgorithmType>(p);
				p.setDefaultValue(1.0);

				StringArray algorithms;
				algorithms.add("Compressor");
				algorithms.add("Limiter");
				algorithms.add("Expander");
				algorithms.add("Gate");

				p.setParameterValueNames(algorithms);
				data.add(std::move(p));
			}
			{
				parameter::data p("Threshold", { -40.0, 0.0 });
				registerCallback<Threshold>(p);
				p.setDefaultValue(-6.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("Ratio", { 1.0, 50.0 });
				registerCallback<Ratio>(p);
				p.setDefaultValue(10.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("KneeWidth", { 0.0, 20.0 });
				registerCallback<KneeWidth>(p);
				p.setDefaultValue(2.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("AttackTime", { 1.0, 100.0 });
				registerCallback<AttackTime>(p);
				p.setDefaultValue(1.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("ReleaseTime", { 1.0, 5000.0 });
				registerCallback<ReleaseTime>(p);
				p.setDefaultValue(100.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("OutputGain", { -20.0, 20.0 });
				registerCallback<OutputGain>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("SoftKnee", { 0.0, 1.0, 1.0 });
				registerCallback<SoftKnee>(p);
				p.setDefaultValue(1.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("LookAheadTime", { 1.0, 50.0 });
				registerCallback<LookAheadTime>(p);
				p.setDefaultValue(10.0);
				data.add(std::move(p));
			}
		}

	private:
		double processWithLookAhead(DynamicsProcessor& processor, double delayedSample, double immediateSample)
		{
			// Use immediate sample for sidechain detection (look-ahead)
			processor.processAuxInputAudioSample(immediateSample);

			// Enable sidechain mode temporarily
			auto params = processor.getParameters();
			bool originalSidechainState = params.enableSidechain;
			params.enableSidechain = true;
			processor.setParameters(params);

			// Process delayed sample with immediate sidechain
			double output = processor.processAudioSample(delayedSample);

			// Restore original sidechain state
			params.enableSidechain = originalSidechainState;
			processor.setParameters(params);

			return output;
		}

		void updateParameters(int voiceIndex)
		{
			parameters[voiceIndex].enableSidechain = false;
			processors[0][voiceIndex].setParameters(parameters[voiceIndex]);
			processors[1][voiceIndex].setParameters(parameters[voiceIndex]);

			delayParams[voiceIndex].delayTime_mSec = 10.0;
			delayLines[0][voiceIndex].setParameters(delayParams[voiceIndex]);
			delayLines[1][voiceIndex].setParameters(delayParams[voiceIndex]);
		}
	};
}

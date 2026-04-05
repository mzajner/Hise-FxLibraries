/*
AspikDynamicsCore - Unified Dynamics Processor
Implements compressor, limiter, expander, and gate algorithms
Based on Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed." Chapter 18
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

	template <int NV> struct AspikDynamicsCore : public data::base
	{
		SNEX_NODE(AspikDynamicsCore);

		struct MetadataClass
		{
			SN_NODE_ID("AspikDynamicsCore");
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
			HardLimitGate,
			SoftKnee
		};

		// ASPIK Objects
		DynamicsProcessor processors[2][NV];
		DynamicsProcessorParameters parameters[NV];

		void prepare(PrepareSpecs specs)
		{
			for (int v = 0; v < NV; v++)
			{
				processors[0][v].reset(specs.sampleRate);
				processors[1][v].reset(specs.sampleRate);
				updateParameters(v);
			}
		}

		void reset()
		{
			for (int v = 0; v < NV; v++)
			{
				processors[0][v].reset(44100.0);
				processors[1][v].reset(44100.0);
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

			data[0] = static_cast<float>(processors[0][voiceIndex].processAudioSample(static_cast<double>(data[0])));
			data[1] = static_cast<float>(processors[1][voiceIndex].processAudioSample(static_cast<double>(data[1])));
		}

		int handleModulation(double& value)
		{
			auto params	 = processors[0][0].getParameters();
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
				for (int i = 0; i < NV; i++)
				{
					parameters[i].calculation = (v < 0.5) ?
						dynamicsProcessorType::kCompressor :
						dynamicsProcessorType::kDownwardExpander;
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
			else if (P == HardLimitGate)
			{
				for (int i = 0; i < NV; i++)
				{
					parameters[i].hardLimitGate = (v >= 0.5);
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
		}

		void createParameters(ParameterDataList& data)
		{
			{
				parameter::data p("Algorithm", { 0.0, 1.0, 1.0 });
				registerCallback<AlgorithmType>(p);
				p.setDefaultValue(0.0);

				StringArray algorithms;
				algorithms.add("Compressor");
				algorithms.add("Expander");

				p.setParameterValueNames(algorithms);
				data.add(std::move(p));
			}
			{
				parameter::data p("Threshold", { -40.0, 0.0 });
				registerCallback<Threshold>(p);
				p.setDefaultValue(-10.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("Ratio", { 1.0, 50.0 });
				registerCallback<Ratio>(p);
				p.setDefaultValue(4.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("KneeWidth", { 0.0, 20.0 });
				registerCallback<KneeWidth>(p);
				p.setDefaultValue(5.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("AttackTime", { 1.0, 100.0 });
				registerCallback<AttackTime>(p);
				p.setDefaultValue(5.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("ReleaseTime", { 1.0, 5000.0 });
				registerCallback<ReleaseTime>(p);
				p.setDefaultValue(500.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("OutputGain", { -20.0, 20.0 });
				registerCallback<OutputGain>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("HardLimitGate", { 0.0, 1.0, 1.0 });
				registerCallback<HardLimitGate>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("SoftKnee", { 0.0, 1.0, 1.0 });
				registerCallback<SoftKnee>(p);
				p.setDefaultValue(1.0);
				data.add(std::move(p));
			}
		}

	private:
		void updateParameters(int voiceIndex)
		{
			parameters[voiceIndex].enableSidechain = false;
			processors[0][voiceIndex].setParameters(parameters[voiceIndex]);
			processors[1][voiceIndex].setParameters(parameters[voiceIndex]);
		}
	};
}

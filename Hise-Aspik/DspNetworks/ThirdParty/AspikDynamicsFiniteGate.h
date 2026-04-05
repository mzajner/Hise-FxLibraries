/*
AspikDynamicsFiniteGate - Gate with Finite Attenuation Floor
Gate mode attenuates to finite -dB instead of -∞ dB to reduce clicks and distortion
Based on Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed." Chapter 18 Homework #2
*/

#pragma once
#include <JuceHeader.h>
#include "src/Aspik/aspik.h"
#include "src/Aspik/homework.h"

namespace project
{
	using namespace juce;
	using namespace hise;
	using namespace scriptnode;
	using namespace aspik;

	template <int NV> struct AspikDynamicsFiniteGate : public data::base
	{
		SNEX_NODE(AspikDynamicsFiniteGate);

		struct MetadataClass
		{
			SN_NODE_ID("AspikDynamicsFiniteGate");
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
			Threshold,
			Ratio,
			KneeWidth,
			AttackTime,
			ReleaseTime,
			OutputGain,
			SoftKnee,
			GateFloor,
			EnableFiniteFloor
		};

		AspikDynamicsFiniteGateProcessor processors[2][NV];

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
			if constexpr (isPolyphonic())
			{
				voiceIndex = data.getVoiceIndex();
				voiceIndex = jlimit(0, NV - 1, voiceIndex);
			}

			data[0] = static_cast<float>(processors[0][voiceIndex].processAudioSample(static_cast<double>(data[0])));
			data[1] = static_cast<float>(processors[1][voiceIndex].processAudioSample(static_cast<double>(data[1])));
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
			if (P == Threshold)
			{
				for (int i = 0; i < NV; i++)
				{
					auto params = processors[0][i].getParameters();
					params.threshold_dB = v;
					processors[0][i].setParameters(params);
					processors[1][i].setParameters(params);
				}
			}
			else if (P == Ratio)
			{
				for (int i = 0; i < NV; i++)
				{
					auto params = processors[0][i].getParameters();
					params.ratio = v;
					processors[0][i].setParameters(params);
					processors[1][i].setParameters(params);
				}
			}
			else if (P == KneeWidth)
			{
				for (int i = 0; i < NV; i++)
				{
					auto params = processors[0][i].getParameters();
					params.kneeWidth_dB = v;
					processors[0][i].setParameters(params);
					processors[1][i].setParameters(params);
				}
			}
			else if (P == AttackTime)
			{
				for (int i = 0; i < NV; i++)
				{
					auto params = processors[0][i].getParameters();
					params.attackTime_mSec = v;
					processors[0][i].setParameters(params);
					processors[1][i].setParameters(params);
				}
			}
			else if (P == ReleaseTime)
			{
				for (int i = 0; i < NV; i++)
				{
					auto params = processors[0][i].getParameters();
					params.releaseTime_mSec = v;
					processors[0][i].setParameters(params);
					processors[1][i].setParameters(params);
				}
			}
			else if (P == OutputGain)
			{
				for (int i = 0; i < NV; i++)
				{
					auto params = processors[0][i].getParameters();
					params.outputGain_dB = v;
					processors[0][i].setParameters(params);
					processors[1][i].setParameters(params);
				}
			}
			else if (P == SoftKnee)
			{
				for (int i = 0; i < NV; i++)
				{
					auto params = processors[0][i].getParameters();
					params.softKnee = (v >= 0.5);
					processors[0][i].setParameters(params);
					processors[1][i].setParameters(params);
				}
			}
			else if (P == GateFloor)
			{
				for (int i = 0; i < NV; i++)
				{
					auto params = processors[0][i].getParameters();
					params.gateFloor_dB = v;
					processors[0][i].setParameters(params);
					processors[1][i].setParameters(params);
				}
			}
			else if (P == EnableFiniteFloor)
			{
				for (int i = 0; i < NV; i++)
				{
					auto params = processors[0][i].getParameters();
					params.enableFiniteFloor = (v >= 0.5);
					processors[0][i].setParameters(params);
					processors[1][i].setParameters(params);
				}
			}
		}

		void createParameters(ParameterDataList& data)
		{
			{
				parameter::data p("Threshold", { -60.0, 0.0 });
				registerCallback<Threshold>(p);
				p.setDefaultValue(-20.0);
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
				p.setDefaultValue(5.0);
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
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("GateFloor", { -100.0, 0.0 });
				registerCallback<GateFloor>(p);
				p.setDefaultValue(-60.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("EnableFiniteFloor", { 0.0, 1.0, 1.0 });
				registerCallback<EnableFiniteFloor>(p);
				p.setDefaultValue(1.0);
				data.add(std::move(p));
			}
		}

	private:
		void updateParameters(int voiceIndex)
		{
			auto params = processors[0][voiceIndex].getParameters();
			processors[0][voiceIndex].setParameters(params);
			processors[1][voiceIndex].setParameters(params);
		}
	};
}

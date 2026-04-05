/*
AspikReverbFDN - Feedback Delay Network Reverb Algorithm Third Party Node

Implements the Feedback Delay Network (FDN) reverb algorithm using ASPIK building blocks:
- Variable number of delay lines (2-8) with feedback matrix
- Unitary feedback matrix for energy preservation
- High-frequency damping filters in feedback paths
- Stereo output with decorrelated channels
- Based on Gerzon, Stautner, and Puckette research

Based on Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed."
and foundational FDN research from the 1970s-1980s
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

	template <int NV> struct AspikReverbFdn : public data::base
	{
		SNEX_NODE(AspikReverbFdn);

		struct MetadataClass
		{
			SN_NODE_ID("AspikReverbFdn");
		};

		static constexpr bool isModNode() { return false; };
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
			RT60_mSec,
			NumDelays,
			Damping,
			Wet_Level_dB,
			Dry_Level_dB,
			NumParameters
		};

		void prepare(PrepareSpecs specs)
		{
			currentSpecs = specs;

			for (int v = 0; v < NV; v++)
			{
				reverbProcessors[v].reset(specs.sampleRate);
				updateParameters(v);
			}
		}

		void reset()
		{
			for (int v = 0; v < NV; v++)
			{
				if (currentSpecs.sampleRate > 0)
				{
					reverbProcessors[v].reset(currentSpecs.sampleRate);
				}
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
			static constexpr int NumChannels = getFixChannelAmount();

			int voiceIndex = 0;
			if constexpr (isPolyphonic())
			{
				voiceIndex = data.getVoiceIndex();
				voiceIndex = jlimit(0, NV - 1, voiceIndex);
			}

			float inputSample = data[0];
			if constexpr (NumChannels == 2)
			{
				inputSample = (data[0] + data[1]) * 0.5f;
			}

			float input[1] = { inputSample };
			float output[2] = { 0.0f, 0.0f };

			reverbProcessors[voiceIndex].processAudioFrame(input, output, 1, 2);

			data[0] = output[0];
			if constexpr (NumChannels == 2)
			{
				data[1] = output[1];
			}
		}

		int handleModulation(double& value)
		{
			return 0;
		}

		void setExternalData(const ExternalData& data, int index)
		{
		}

		template <int P> void setParameter(double v)
		{
			if constexpr (P == RT60_mSec)
			{
				parameters.rt60_mSec = v;
				updateAllParameters();
			}
			else if constexpr (P == NumDelays)
			{
				parameters.numDelays = jlimit(2, 8, (int)v);
				updateAllParameters();
			}
			else if constexpr (P == Damping)
			{
				parameters.damping = v;
				updateAllParameters();
			}
			else if constexpr (P == Wet_Level_dB)
			{
				parameters.wetLevel_dB = v;
				updateAllParameters();
			}
			else if constexpr (P == Dry_Level_dB)
			{
				parameters.dryLevel_dB = v;
				updateAllParameters();
			}
		}

		void createParameters(ParameterDataList& data)
		{
			{
				parameter::data p("RT60 ms", { 100.0, 5000.0, 1.0 });
				registerCallback<RT60_mSec>(p);
				p.setDefaultValue(1000.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("NumDelays", { 2.0, 8.0, 1.0 });
				registerCallback<NumDelays>(p);
				p.setDefaultValue(4.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Damping", { 0.0, 1.0, 0.01 });
				registerCallback<Damping>(p);
				p.setDefaultValue(0.5);
				data.add(std::move(p));
			}

			{
				parameter::data p("Wet Level dB", { -60.0, 0.0, 0.1 });
				registerCallback<Wet_Level_dB>(p);
				p.setDefaultValue(-6.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Dry Level dB", { -60.0, 0.0, 0.1 });
				registerCallback<Dry_Level_dB>(p);
				p.setDefaultValue(-6.0);
				data.add(std::move(p));
			}
		}

	private:
		void updateParameters(int voiceIndex)
		{
			if (voiceIndex >= 0 && voiceIndex < NV)
			{
				reverbProcessors[voiceIndex].setParameters(parameters);
			}
		}

		void updateAllParameters()
		{
			for (int v = 0; v < NV; v++)
			{
				updateParameters(v);
			}
		}

		PrepareSpecs currentSpecs;
		FDNReverb reverbProcessors[NV];
		FDNReverbParameters parameters;
	};

	using AspikReverbFDNMono = AspikReverbFdn<1>;
	using AspikReverbFDNPoly = AspikReverbFdn<NUM_POLYPHONIC_VOICES>;

}

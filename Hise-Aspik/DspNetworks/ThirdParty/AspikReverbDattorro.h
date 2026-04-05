/*
AspikReverbDattorro - Dattorro Plate Reverb Algorithm Third Party Node

Implements the classic Dattorro plate reverb algorithm using ASPIK building blocks:
- Pre-delay for early reflection simulation
- Bandwidth LPF for input diffusion control
- 4 series all-pass filters for initial diffusion
- Figure-8 tank circuit with modulated APFs
- Damping LPFs for high-frequency control
- Multiple stereo output taps from tank delays
- Mono input to stereo output processing

Based on Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed."
and Dattorro's 1997 "Effect Design Part 1: Reverberator and Other Filters"
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

	template <int NV> struct AspikReverbDattorro : public data::base
	{
		SNEX_NODE(AspikReverbDattorro);

		struct MetadataClass
		{
			SN_NODE_ID("AspikReverbDattorro");
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
			PreDelay_mSec,
			Bandwidth,
			Damping,
			Decay,
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
			if constexpr (P == PreDelay_mSec)
			{
				parameters.preDelay_mSec = v;
				updateAllParameters();
			}
			else if constexpr (P == Bandwidth)
			{
				parameters.bandwidth = v;
				updateAllParameters();
			}
			else if constexpr (P == Damping)
			{
				parameters.damping = v;
				updateAllParameters();
			}
			else if constexpr (P == Decay)
			{
				parameters.decay = v;
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
				parameter::data p("PreDelay ms", { 0.0, 100.0, 0.1 });
				registerCallback<PreDelay_mSec>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Bandwidth", { 0.0, 1.0, 0.01 });
				registerCallback<Bandwidth>(p);
				p.setDefaultValue(0.5);
				data.add(std::move(p));
			}

			{
				parameter::data p("Damping", { 0.0, 1.0, 0.01 });
				registerCallback<Damping>(p);
				p.setDefaultValue(0.5);
				data.add(std::move(p));
			}

			{
				parameter::data p("Decay", { 0.0, 0.9999, 0.001 });
				registerCallback<Decay>(p);
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
		DattorroReverb reverbProcessors[NV];
		DattorroReverbParameters parameters;
	};

	using AspikReverbDattorroMono = AspikReverbDattorro<1>;
	using AspikReverbDattorroPoly = AspikReverbDattorro<NUM_POLYPHONIC_VOICES>;

}

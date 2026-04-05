/*
AspikReverbSchroeder - Schroeder Reverb Algorithm Third Party Node

Implements the classic Schroeder reverb algorithm using ASPIK building blocks:
- 4 parallel comb filters with feedback
- 2 series all-pass filters for diffusion
- Mono input to stereo output processing
- RT60, APF gain, and wet/dry level controls

Based on Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed."
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

	template <int NV> struct AspikReverbSchroeder : public data::base
	{
		SNEX_NODE(AspikReverbSchroeder);

		struct MetadataClass
		{
			SN_NODE_ID("AspikReverbSchroeder");
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
			APF_Gain,
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
			else if constexpr (P == APF_Gain)
			{
				parameters.apfGain = v;
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
				parameter::data p("RT60_mSec", { 100.0, 5000.0, 1.0 });
				registerCallback<RT60_mSec>(p);
				p.setDefaultValue(1000.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("APF_Gain", { 0.1, 0.99, 0.01 });
				registerCallback<APF_Gain>(p);
				p.setDefaultValue(0.7);  // Schroeder's recommended value
				data.add(std::move(p));
			}

			{
				parameter::data p("Wet_Level_dB", { -60.0, 0.0, 0.1 });
				registerCallback<Wet_Level_dB>(p);
				p.setDefaultValue(-3.0);  // Higher wet level for audible reverb
				data.add(std::move(p));
			}

			{
				parameter::data p("Dry_Level_dB", { -60.0, 0.0, 0.1 });
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
		SchroederReverb reverbProcessors[NV];
		SchroederReverbParameters parameters;
	};

	using AspikReverbSchroederMono = AspikReverbSchroeder<1>;
	using AspikReverbSchroederPoly = AspikReverbSchroeder<NUM_POLYPHONIC_VOICES>;

}

// ==================================| ASPIK Fuzz Face HISE Integration |==================================
/*
Fuzz Face - NPN Transistor Fuzz Emulation
Based on Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed." Homework 19.16.1
HISE integration for the Fuzz Face emulator using the characteristics from Figure 19.7e
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

	template <int NV> struct AspikWaveshaperFuzzFace : public data::base
	{
		// Metadata Definitions ------------------------------------------------------------------------

		SNEX_NODE(AspikWaveshaperFuzzFace);

		struct MetadataClass
		{
			SN_NODE_ID("AspikWaveshaperFuzzFace");
		};

		static constexpr bool isModNode() { return false; };
		static constexpr bool isPolyphonic() { return NV > 1; };
		static constexpr bool hasTail() { return false; };
		static constexpr bool isSuspendedOnSilence() { return true; };
		static constexpr int getFixChannelAmount() { return 2; };

		static constexpr int NumTables = 0;
		static constexpr int NumSliderPacks = 0;
		static constexpr int NumAudioFiles = 0;
		static constexpr int NumFilters = 0;
		static constexpr int NumDisplayBuffers = 0;

		// ASPIK Objects
		FuzzFace fuzzFace[2][NV];  // L/R channels per voice
		FuzzFaceParameters parameters[NV];
		double sampleRate = 44100.0;

		// Parameters
		enum Parameters
		{
			FuzzAmount = 0,
			Volume,
			Bias
		};

		// Scriptnode Callbacks ------------------------------------------------------------------------

		void prepare(PrepareSpecs specs)
		{
			sampleRate = specs.sampleRate;

			for (int v = 0; v < NV; v++)
			{
				fuzzFace[0][v].reset(specs.sampleRate);
				fuzzFace[1][v].reset(specs.sampleRate);
				updateParameters(v);
			}
		}

		void reset()
		{
			for (int v = 0; v < NV; v++)
			{
				fuzzFace[0][v].reset(sampleRate);
				fuzzFace[1][v].reset(sampleRate);
			}
		}

		void handleHiseEvent(HiseEvent& e)
		{
			// No MIDI processing needed
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

			// Process L/R channels through Fuzz Face
			data[0] = static_cast<float>(
				fuzzFace[0][voiceIndex].processAudioSample(static_cast<double>(data[0]))
				);

			if (getFixChannelAmount() > 1)
			{
				data[1] = static_cast<float>(
					fuzzFace[1][voiceIndex].processAudioSample(static_cast<double>(data[1]))
					);
			}
		}

		int handleModulation(double& value)
		{
			return 0;
		}

		void setExternalData(const ExternalData& data, int index)
		{
			// No external data needed
		}

		// Parameter Functions -------------------------------------------------------------------------

		template <int P> void setParameter(double v)
		{
			if constexpr (P == FuzzAmount)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].fuzzAmount = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == Volume)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].volume = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == Bias)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].bias = v;
					updateParameters(voice);
				}
			}
		}

		void createParameters(ParameterDataList& data)
		{
			{
				parameter::data p("Fuzz Amount", { 0.1, 10.0 });
				registerCallback<FuzzAmount>(p);
				p.setDefaultValue(5.0);
				p.setSkewForCentre(3.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Volume", { 0.0, 1.0 });
				registerCallback<Volume>(p);
				p.setDefaultValue(0.5);
				data.add(std::move(p));
			}

			{
				parameter::data p("Bias", { -0.2, 0.2 });
				registerCallback<Bias>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}
		}

	private:
		void updateParameters(int voice)
		{
			fuzzFace[0][voice].setParameters(parameters[voice]);
			fuzzFace[1][voice].setParameters(parameters[voice]);
		}
	};
}

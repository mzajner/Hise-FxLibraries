// ==================================| ASPIK Octave Up HISE Integration |==================================
/*
Octave Up - Full-Wave Rectifier Octave-Up Distortion
Based on Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed." Homework 19.16.2
HISE integration for octave-up distortion using full-wave rectifier path
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

	template <int NV> struct AspikWaveshaperOctaveUp : public data::base
	{
		// Metadata Definitions ------------------------------------------------------------------------

		SNEX_NODE(AspikWaveshaperOctaveUp);

		struct MetadataClass
		{
			SN_NODE_ID("AspikWaveshaperOctaveUp");
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
		OctaveUp octaveUp[2][NV];  // L/R channels per voice
		OctaveUpParameters parameters[NV];
		double sampleRate = 44100.0;

		// Parameters
		enum Parameters
		{
			RectifierMix = 0,
			DistortionAmount,
			OutputGain
		};

		// Scriptnode Callbacks ------------------------------------------------------------------------

		void prepare(PrepareSpecs specs)
		{
			sampleRate = specs.sampleRate;

			for (int v = 0; v < NV; v++)
			{
				octaveUp[0][v].reset(specs.sampleRate);
				octaveUp[1][v].reset(specs.sampleRate);
				updateParameters(v);
			}
		}

		void reset()
		{
			for (int v = 0; v < NV; v++)
			{
				octaveUp[0][v].reset(sampleRate);
				octaveUp[1][v].reset(sampleRate);
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

			// Process L/R channels through Octave Up distortion
			data[0] = static_cast<float>(
				octaveUp[0][voiceIndex].processAudioSample(static_cast<double>(data[0]))
				);

			if (getFixChannelAmount() > 1)
			{
				data[1] = static_cast<float>(
					octaveUp[1][voiceIndex].processAudioSample(static_cast<double>(data[1]))
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
			if constexpr (P == RectifierMix)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].rectifierMix = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == DistortionAmount)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].distortionAmount = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == OutputGain)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].outputGain = v;
					updateParameters(voice);
				}
			}
		}

		void createParameters(ParameterDataList& data)
		{
			{
				parameter::data p("Octave Mix", { 0.0, 1.0 });
				registerCallback<RectifierMix>(p);
				p.setDefaultValue(0.3);
				data.add(std::move(p));
			}

			{
				parameter::data p("Distortion", { 0.5, 5.0 });
				registerCallback<DistortionAmount>(p);
				p.setDefaultValue(2.0);
				p.setSkewForCentre(2.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Output Gain", { 0.1, 2.0 });
				registerCallback<OutputGain>(p);
				p.setDefaultValue(0.5);
				data.add(std::move(p));
			}
		}

	private:
		void updateParameters(int voice)
		{
			octaveUp[0][voice].setParameters(parameters[voice]);
			octaveUp[1][voice].setParameters(parameters[voice]);
		}
	};
}

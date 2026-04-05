// ==================================| ASPIK Virtual Bass HISE Integration |==================================
/*
Virtual Bass - Psychoacoustic Bass Enhancement
Based on Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed." Homework 19.16.4
HISE integration for virtual bass enhancement using the VB algorithm from Figure 19.10
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

	template <int NV> struct AspikWaveshaperVirtualBass : public data::base
	{
		// Metadata Definitions ------------------------------------------------------------------------

		SNEX_NODE(AspikWaveshaperVirtualBass);

		struct MetadataClass
		{
			SN_NODE_ID("AspikWaveshaperVirtualBass");
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
		VirtualBass virtualBass[2][NV];  // L/R channels per voice
		VirtualBassParameters parameters[NV];
		double sampleRate = 44100.0;

		// Parameters
		enum Parameters
		{
			CutoffFreq = 0,
			HarmonicGain,
			MixLevel
		};

		// Scriptnode Callbacks ------------------------------------------------------------------------

		void prepare(PrepareSpecs specs)
		{
			sampleRate = specs.sampleRate;

			for (int v = 0; v < NV; v++)
			{
				virtualBass[0][v].reset(specs.sampleRate);
				virtualBass[1][v].reset(specs.sampleRate);
				updateParameters(v);
			}
		}

		void reset()
		{
			for (int v = 0; v < NV; v++)
			{
				virtualBass[0][v].reset(sampleRate);
				virtualBass[1][v].reset(sampleRate);
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

			// Process L/R channels through Virtual Bass enhancement
			data[0] = static_cast<float>(
				virtualBass[0][voiceIndex].processAudioSample(static_cast<double>(data[0]))
				);

			if (getFixChannelAmount() > 1)
			{
				data[1] = static_cast<float>(
					virtualBass[1][voiceIndex].processAudioSample(static_cast<double>(data[1]))
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
			if constexpr (P == CutoffFreq)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].cutoffFreq = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == HarmonicGain)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].harmonicGain = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == MixLevel)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].mixLevel = v;
					updateParameters(voice);
				}
			}
		}

		void createParameters(ParameterDataList& data)
		{
			{
				parameter::data p("HPF Cutoff", { 40.0, 200.0 });
				registerCallback<CutoffFreq>(p);
				p.setDefaultValue(80.0);
				p.setSkewForCentre(80.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Harmonic Gain", { 0.5, 5.0 });
				registerCallback<HarmonicGain>(p);
				p.setDefaultValue(2.0);
				p.setSkewForCentre(2.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Bass Mix", { 0.0, 1.0 });
				registerCallback<MixLevel>(p);
				p.setDefaultValue(0.3);
				data.add(std::move(p));
			}
		}

	private:
		void updateParameters(int voice)
		{
			virtualBass[0][voice].setParameters(parameters[voice]);
			virtualBass[1][voice].setParameters(parameters[voice]);
		}
	};
}

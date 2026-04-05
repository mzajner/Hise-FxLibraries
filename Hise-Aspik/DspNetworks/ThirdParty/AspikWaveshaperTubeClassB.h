// ==================================| ASPIK Tube Class B HISE Integration |==================================
/*
Tube Class B - Class B Tube Emulation with Crossover Distortion
Based on Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed." Homework 19.16.5
HISE integration for Class B tube emulation with crossover distortion characteristics
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

	template <int NV> struct AspikWaveshaperTubeClassB : public data::base
	{
		// Metadata Definitions ------------------------------------------------------------------------

		SNEX_NODE(AspikWaveshaperTubeClassB);

		struct MetadataClass
		{
			SN_NODE_ID("AspikWaveshaperTubeClassB");
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
		TubeClassB tubeClassB[2][NV];  // L/R channels per voice
		TubeClassBParameters parameters[NV];
		double sampleRate = 44100.0;

		// Parameters
		enum Parameters
		{
			CrossoverThreshold = 0,
			Saturation,
			CrossoverDistortion,
			OutputGain
		};

		// Scriptnode Callbacks ------------------------------------------------------------------------

		void prepare(PrepareSpecs specs)
		{
			sampleRate = specs.sampleRate;

			for (int v = 0; v < NV; v++)
			{
				tubeClassB[0][v].reset(specs.sampleRate);
				tubeClassB[1][v].reset(specs.sampleRate);
				updateParameters(v);
			}
		}

		void reset()
		{
			for (int v = 0; v < NV; v++)
			{
				tubeClassB[0][v].reset(sampleRate);
				tubeClassB[1][v].reset(sampleRate);
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

			// Process L/R channels through Class B tube emulation
			data[0] = static_cast<float>(
				tubeClassB[0][voiceIndex].processAudioSample(static_cast<double>(data[0]))
				);

			if (getFixChannelAmount() > 1)
			{
				data[1] = static_cast<float>(
					tubeClassB[1][voiceIndex].processAudioSample(static_cast<double>(data[1]))
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
			if constexpr (P == CrossoverThreshold)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].crossoverThreshold = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == Saturation)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].saturation = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == CrossoverDistortion)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].crossoverDistortion = v;
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
				parameter::data p("Crossover Threshold", { 0.01, 0.5 });
				registerCallback<CrossoverThreshold>(p);
				p.setDefaultValue(0.1);
				p.setSkewForCentre(0.1);
				data.add(std::move(p));
			}

			{
				parameter::data p("Saturation", { 0.5, 5.0 });
				registerCallback<Saturation>(p);
				p.setDefaultValue(2.0);
				p.setSkewForCentre(2.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Crossover Distortion", { 0.0, 1.0 });
				registerCallback<CrossoverDistortion>(p);
				p.setDefaultValue(0.5);
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
			tubeClassB[0][voice].setParameters(parameters[voice]);
			tubeClassB[1][voice].setParameters(parameters[voice]);
		}
	};
}

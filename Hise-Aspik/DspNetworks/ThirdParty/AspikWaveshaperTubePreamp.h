// ==================================| ASPIK ClassA Tube Preamp |==================================
/*
ClassATubePre - Four-Stage Tube Preamp
Based on Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed." Chapter 19.13
Implements a cascade of four Class-A triode stages with:
- Four cascaded TriodeClassA stages (configurable saturation/asymmetry)
- Two-band shelving EQ between 3rd and 4th stages
- Input and output level controls
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

	template <int NV> struct AspikWaveshaperTubePreamp : public data::base
	{
		// Metadata Definitions ------------------------------------------------------------------------

		SNEX_NODE(AspikWaveshaperTubePreamp);

		struct MetadataClass
		{
			SN_NODE_ID("AspikWaveshaperTubePreamp");
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
		aspik::ClassATubePre preamps[2][NV];  // L/R channels per voice
		aspik::ClassATubePreParameters parameters[NV];
		double sampleRate = 44100.0;

		// Parameters
		enum Parameters
		{
			InputLevel = 0,
			Saturation,
			Asymmetry,
			OutputLevel,
			LowShelfFC,
			LowShelfBoostCut,
			HighShelfFC,
			HighShelfBoostCut
		};

		// Scriptnode Callbacks ------------------------------------------------------------------------

		void prepare(PrepareSpecs specs)
		{
			sampleRate = specs.sampleRate;

			for (int v = 0; v < NV; v++)
			{
				preamps[0][v].reset(specs.sampleRate);
				preamps[1][v].reset(specs.sampleRate);
				updateParameters(v);
			}
		}

		void reset()
		{
			for (int v = 0; v < NV; v++)
			{
				preamps[0][v].reset(sampleRate);
				preamps[1][v].reset(sampleRate);
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

			// Process through four-stage tube preamp
			data[0] = static_cast<float>(
				preamps[0][voiceIndex].processAudioSample(static_cast<double>(data[0]))
				);

			if (getFixChannelAmount() > 1)
			{
				data[1] = static_cast<float>(
					preamps[1][voiceIndex].processAudioSample(static_cast<double>(data[1]))
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
			if constexpr (P == InputLevel)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].inputLevel_dB = v;
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
			else if constexpr (P == Asymmetry)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].asymmetry = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == OutputLevel)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].outputLevel_dB = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == LowShelfFC)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].lowShelf_fc = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == LowShelfBoostCut)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].lowShelfBoostCut_dB = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == HighShelfFC)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].highShelf_fc = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == HighShelfBoostCut)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].highShelfBoostCut_dB = v;
					updateParameters(voice);
				}
			}
		}

		void createParameters(ParameterDataList& data)
		{
			{
				parameter::data p("Input Level", { -20.0, 20.0 });
				registerCallback<InputLevel>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Saturation", { 0.0, 10.0 });
				registerCallback<Saturation>(p);
				p.setDefaultValue(1.0);
				p.setSkewForCentre(2.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Asymmetry", { -1.0, 1.0 });
				registerCallback<Asymmetry>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Output Level", { -20.0, 20.0 });
				registerCallback<OutputLevel>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Low Shelf Freq", { 20.0, 500.0 });
				registerCallback<LowShelfFC>(p);
				p.setDefaultValue(80.0);
				p.setSkewForCentre(100.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Low Shelf Gain", { -12.0, 12.0 });
				registerCallback<LowShelfBoostCut>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("High Shelf Freq", { 1000.0, 10000.0 });
				registerCallback<HighShelfFC>(p);
				p.setDefaultValue(3000.0);
				p.setSkewForCentre(3000.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("High Shelf Gain", { -12.0, 12.0 });
				registerCallback<HighShelfBoostCut>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}
		}

	private:
		void updateParameters(int voice)
		{
			preamps[0][voice].setParameters(parameters[voice]);
			preamps[1][voice].setParameters(parameters[voice]);
		}
	};
}

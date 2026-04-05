/*
AspikDynamicsCrossover - Linkwitz-Riley Crossover Filter Bank
Two-band crossover reconstruction using Linkwitz-Riley filters
Based on Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed." Chapter 18.11
*/

/* ========== TO DO ========== 
This one was a bit tricky but it would be useful to have: 
	1. Varying channel count (2 in, 4 out),
	2. More crossover bands (3+), 4(+), 5(+), etc.
	3. Turn this into a scriptnode container for rapid deployment
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

	template <int NV> struct AspikDynamicsCrossover : public data::base
	{
		SNEX_NODE(AspikDynamicsCrossover);

		struct MetadataClass
		{
			SN_NODE_ID("AspikDynamicsCrossover");
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

		enum Parameters
		{
			CrossoverFreq,
			OutputMode,     // 0=Low Only, 1=High Only, 2=Low+High Mix
			LowLevel,       // Level control for low band
			HighLevel,      // Level control for high band
			Phase           // 0=Normal, 1=Invert High Band
		};

		// ASPIK Objects
		LRFilterBank filterBank[2][NV];  // L/R channels
		LRFilterBankParameters filterParams[NV];

		// Output control
		int outputMode[NV] = { 2 }; // Default to mixed output
		double lowLevel[NV] = { 1.0 };
		double highLevel[NV] = { 1.0 };
		bool invertHigh[NV] = { false };

		void prepare(PrepareSpecs specs)
		{
			for (int v = 0; v < NV; v++)
			{
				filterBank[0][v].reset(specs.sampleRate);
				filterBank[1][v].reset(specs.sampleRate);
				updateParameters(v);
			}
		}

		void reset()
		{
			for (int v = 0; v < NV; v++)
			{
				filterBank[0][v].reset(44100.0);
				filterBank[1][v].reset(44100.0);
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

			// Process through filter bank
			FilterBankOutput leftBands = filterBank[0][voiceIndex].processFilterBank(static_cast<double>(data[0]));
			FilterBankOutput rightBands = filterBank[1][voiceIndex].processFilterBank(static_cast<double>(data[1]));

			// Apply level controls and phase
			double lowL = leftBands.LFOut * lowLevel[voiceIndex];
			double lowR = rightBands.LFOut * lowLevel[voiceIndex];
			double highL = leftBands.HFOut * highLevel[voiceIndex] * (invertHigh[voiceIndex] ? -1.0 : 1.0);
			double highR = rightBands.HFOut * highLevel[voiceIndex] * (invertHigh[voiceIndex] ? -1.0 : 1.0);

			// Output based on mode
			switch (outputMode[voiceIndex])
			{
			case 0: // Low band only
				data[0] = static_cast<float>(lowL);
				data[1] = static_cast<float>(lowR);
				break;

			case 1: // High band only
				data[0] = static_cast<float>(highL);
				data[1] = static_cast<float>(highR);
				break;

			case 2: // Mixed output (perfect reconstruction)
			default:
				data[0] = static_cast<float>(lowL + highL);
				data[1] = static_cast<float>(lowR + highR);
				break;
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
			if (P == CrossoverFreq)
			{
				for (int i = 0; i < NV; i++)
				{
					filterParams[i].splitFrequency = v;
					filterBank[0][i].setParameters(filterParams[i]);
					filterBank[1][i].setParameters(filterParams[i]);
				}
			}
			else if (P == OutputMode)
			{
				for (int i = 0; i < NV; i++)
				{
					outputMode[i] = static_cast<int>(v);
				}
			}
			else if (P == LowLevel)
			{
				// Convert dB to linear gain
				double gainDb = jmap(v, 0.0, 1.0, -60.0, 12.0);
				for (int i = 0; i < NV; i++)
				{
					lowLevel[i] = pow(10.0, gainDb / 20.0);
				}
			}
			else if (P == HighLevel)
			{
				// Convert dB to linear gain  
				double gainDb = jmap(v, 0.0, 1.0, -60.0, 12.0);
				for (int i = 0; i < NV; i++)
				{
					highLevel[i] = pow(10.0, gainDb / 20.0);
				}
			}
			else if (P == Phase)
			{
				for (int i = 0; i < NV; i++)
				{
					invertHigh[i] = (v >= 0.5);
				}
			}
		}

		void createParameters(ParameterDataList& data)
		{
			{
				parameter::data p("CrossoverFreq", { 200.0, 5000.0 });
				registerCallback<CrossoverFreq>(p);
				p.setDefaultValue(1000.0);
				p.setSkewForCentre(1000.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("OutputMode", { 0.0, 2.0, 1.0 });
				registerCallback<OutputMode>(p);
				p.setDefaultValue(2.0);

				StringArray modes;
				modes.add("Low Only");
				modes.add("High Only");
				modes.add("Low + High");

				p.setParameterValueNames(modes);
				data.add(std::move(p));
			}
			{
				parameter::data p("LowLevel", { 0.0, 1.0 });
				registerCallback<LowLevel>(p);
				p.setDefaultValue(0.75); // ~0 dB
				data.add(std::move(p));
			}
			{
				parameter::data p("HighLevel", { 0.0, 1.0 });
				registerCallback<HighLevel>(p);
				p.setDefaultValue(0.75); // ~0 dB
				data.add(std::move(p));
			}
			{
				parameter::data p("PhaseInvert", { 0.0, 1.0, 1.0 });
				registerCallback<Phase>(p);
				p.setDefaultValue(0.0);

				StringArray phase;
				phase.add("Normal");
				phase.add("Invert High");

				p.setParameterValueNames(phase);
				data.add(std::move(p));
			}
		}

	private:
		void updateParameters(int voiceIndex)
		{
			filterParams[voiceIndex].splitFrequency = 1000.0;
			filterBank[0][voiceIndex].setParameters(filterParams[voiceIndex]);
			filterBank[1][voiceIndex].setParameters(filterParams[voiceIndex]);
		}
	};
}

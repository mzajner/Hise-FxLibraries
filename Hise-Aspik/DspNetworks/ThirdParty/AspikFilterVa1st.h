// ==================================| ASPIK VA 1st Order Filter |==================================

#pragma once
#include <JuceHeader.h>
#include "src/Aspik/aspik.h"

namespace project
{
	using namespace juce;
	using namespace hise;
	using namespace scriptnode;
	using namespace aspik;

	template <int NV> struct AspikFilterVa1st
	{
		SNEX_NODE(AspikFilterVa1st);

		struct MetadataClass
		{
			SN_NODE_ID("AspikFilterVa1st");
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

		// ASPIK VA Filter Object
		aspik::ZVAFilter vaFilter;

		// Parameters
		int vaAlgorithm = 0; // 0=LPF1, 1=HPF1, 2=APF1
		double frequency = 1000.0;
		double q = 0.707;
		bool enableGainComp = false;
		bool matchAnalogNyquist = false;
		double sampleRate = 44100.0;

		void prepare(PrepareSpecs specs)
		{
			sampleRate = specs.sampleRate;
			updateFilterParameters();
			reset();
		}

		void reset()
		{
			vaFilter.reset(sampleRate);
		}

		void handleHiseEvent(HiseEvent& e) {}

		void updateFilterParameters()
		{
			aspik::ZVAFilterParameters params;
			params.fc = frequency;
			params.Q = q;
			params.enableGainComp = enableGainComp;
			params.matchAnalogNyquistLPF = matchAnalogNyquist;

			// Set algorithm based on selection
			if (vaAlgorithm == 0)
				params.filterAlgorithm = aspik::vaFilterAlgorithm::kLPF1;
			else if (vaAlgorithm == 1)
				params.filterAlgorithm = aspik::vaFilterAlgorithm::kHPF1;
			else if (vaAlgorithm == 2)
				params.filterAlgorithm = aspik::vaFilterAlgorithm::kAPF1;

			vaFilter.setParameters(params);
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
			float inputL = data[0];
			float inputR = data[1];

			float outputL = (float)vaFilter.processAudioSample((double)inputL);
			float outputR = (float)vaFilter.processAudioSample((double)inputR);

			data[0] = outputL;
			data[1] = outputR;
		}

		int handleModulation(double& value) { return 0; }
		void setExternalData(const ExternalData& data, int index) {}

		template <int P> void setParameter(double v)
		{
			if (P == 0) // Frequency
			{
				double newFreq = jlimit(20.0, 20000.0, v);
				if (frequency != newFreq)
				{
					frequency = newFreq;
					updateFilterParameters();
				}
			}
			else if (P == 1) // Q
			{
				double newQ = jlimit(0.1, 30.0, v);
				if (q != newQ)
				{
					q = newQ;
					updateFilterParameters();
				}
			}
			else if (P == 2) // Algorithm
			{
				int newAlgorithm = jlimit(0, 2, (int)v);
				if (vaAlgorithm != newAlgorithm)
				{
					vaAlgorithm = newAlgorithm;
					updateFilterParameters();
				}
			}
			else if (P == 3) // Gain Compensation
			{
				bool newGainComp = v > 0.5;
				if (enableGainComp != newGainComp)
				{
					enableGainComp = newGainComp;
					updateFilterParameters();
				}
			}
			else if (P == 4) // Analog Nyquist Matching
			{
				bool newMatch = v > 0.5;
				if (matchAnalogNyquist != newMatch)
				{
					matchAnalogNyquist = newMatch;
					updateFilterParameters();
				}
			}
		}

		void createParameters(ParameterDataList& data)
		{
			{
				parameter::data p("Frequency", { 20.0, 20000.0 });
				registerCallback<0>(p);
				p.setDefaultValue(1000.0);
				p.setSkewForCentre(1000.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("Q", { 0.1, 30.0 });
				registerCallback<1>(p);
				p.setDefaultValue(0.707);
				p.setSkewForCentre(1.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("FilterType", { 0.0, 2.0, 1.0 });
				registerCallback<2>(p);
				p.setDefaultValue(0.0);

				StringArray vaTypes;
				vaTypes.add("Low-Pass");
				vaTypes.add("High-Pass");
				vaTypes.add("All-Pass");

				p.setParameterValueNames(vaTypes);
				data.add(std::move(p));
			}
			{
				parameter::data p("GainComp", { 0.0, 1.0, 1.0 });
				registerCallback<3>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("AnalogMatch", { 0.0, 1.0, 1.0 });
				registerCallback<4>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}
		}
	};
}

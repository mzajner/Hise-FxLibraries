// ==================================| ASPIK VA SVF Filter |==================================
#pragma once
#include <JuceHeader.h>
#include "src/Aspik/aspik.h"

namespace project
{
	using namespace juce;
	using namespace hise;
	using namespace scriptnode;
	using namespace aspik;

	template <int NV> struct AspikFilterSvf
	{
		SNEX_NODE(AspikFilterSvf);

		struct MetadataClass
		{
			SN_NODE_ID("AspikFilterSvf");
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

		// ASPIK VA SVF Filter Object
		aspik::ZVAFilter svfFilter;

		// Parameters
		int svfAlgorithm = 0; // 0=SVF_LP, 1=SVF_HP, 2=SVF_BP, 3=SVF_BS
		double frequency = 1000.0;
		double q = 0.707;
		bool enableGainComp = false;
		bool enableNLP = false;
		bool selfOscillate = false;
		double filterOutputGain = 0.0;
		double sampleRate = 44100.0;

		void prepare(PrepareSpecs specs)
		{
			sampleRate = specs.sampleRate;
			updateFilterParameters();
			reset();
		}

		void reset()
		{
			svfFilter.reset(sampleRate);
		}

		void handleHiseEvent(HiseEvent& e) {}

		void updateFilterParameters()
		{
			aspik::ZVAFilterParameters params;
			params.fc = frequency;
			params.Q = q;
			params.enableGainComp = enableGainComp;
			params.enableNLP = enableNLP;
			params.selfOscillate = selfOscillate;
			params.filterOutputGain_dB = filterOutputGain;

			// Set algorithm based on selection
			if (svfAlgorithm == 0)
				params.filterAlgorithm = aspik::vaFilterAlgorithm::kSVF_LP;
			else if (svfAlgorithm == 1)
				params.filterAlgorithm = aspik::vaFilterAlgorithm::kSVF_HP;
			else if (svfAlgorithm == 2)
				params.filterAlgorithm = aspik::vaFilterAlgorithm::kSVF_BP;
			else if (svfAlgorithm == 3)
				params.filterAlgorithm = aspik::vaFilterAlgorithm::kSVF_BS;

			svfFilter.setParameters(params);
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

			float outputL = (float)svfFilter.processAudioSample((double)inputL);
			float outputR = (float)svfFilter.processAudioSample((double)inputR);

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
				int newAlgorithm = jlimit(0, 3, (int)v);
				if (svfAlgorithm != newAlgorithm)
				{
					svfAlgorithm = newAlgorithm;
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
			else if (P == 4) // Nonlinear Processing
			{
				bool newNLP = v > 0.5;
				if (enableNLP != newNLP)
				{
					enableNLP = newNLP;
					updateFilterParameters();
				}
			}
			else if (P == 5) // Self-Oscillation
			{
				bool newOsc = v > 0.5;
				if (selfOscillate != newOsc)
				{
					selfOscillate = newOsc;
					updateFilterParameters();
				}
			}
			else if (P == 6) // Output Gain
			{
				double newGain = jlimit(-24.0, 24.0, v);
				if (filterOutputGain != newGain)
				{
					filterOutputGain = newGain;
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
				parameter::data p("FilterType", { 0.0, 3.0, 1.0 });
				registerCallback<2>(p);
				p.setDefaultValue(0.0);

				StringArray svfTypes;
				svfTypes.add("Low-Pass");
				svfTypes.add("High-Pass");
				svfTypes.add("Band-Pass");
				svfTypes.add("Band-Stop");

				p.setParameterValueNames(svfTypes);
				data.add(std::move(p));
			}
			{
				parameter::data p("GainComp", { 0.0, 1.0, 1.0 });
				registerCallback<3>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("NonlinearProc", { 0.0, 1.0, 1.0 });
				registerCallback<4>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("SelfOscillate", { 0.0, 1.0, 1.0 });
				registerCallback<5>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("OutputGain", { -24.0, 24.0 });
				registerCallback<6>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}
		}
	};
}

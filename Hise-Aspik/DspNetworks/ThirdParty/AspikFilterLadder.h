// ==================================| ASPIK Tunable Ladder Filters - FIXED |==================================
#pragma once
#include <JuceHeader.h>
#include "src/Aspik/aspik.h"

namespace project
{
	using namespace juce;
	using namespace hise;
	using namespace scriptnode;
	using namespace aspik;

	template <int NV> struct AspikFilterLadder
	{
		SNEX_NODE(AspikFilterLadder);

		struct MetadataClass
		{
			SN_NODE_ID("AspikFilterLadder");
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

		// =====================| Butterworth 3rd Order LPF - STEREO |=====================
		// Left Channel
		aspik::WdfSeriesAdaptor seriesAdaptor_L1_Butter_L;
		aspik::WdfParallelAdaptor parallelAdaptor_C1_Butter_L;
		aspik::WdfSeriesTerminatedAdaptor seriesTerminatedAdaptor_L2_Butter_L;
		// Right Channel  
		aspik::WdfSeriesAdaptor seriesAdaptor_L1_Butter_R;
		aspik::WdfParallelAdaptor parallelAdaptor_C1_Butter_R;
		aspik::WdfSeriesTerminatedAdaptor seriesTerminatedAdaptor_L2_Butter_R;

		// Normalized component values for Butterworth (at fc = 1000 Hz - more practical)
		static constexpr double butter_L1_norm = 95.49e-3;    // 95.49 mH at 1kHz
		static constexpr double butter_C1_norm = 0.5305e-6;   // 0.5305 μF at 1kHz  
		static constexpr double butter_L2_norm = 95.49e-3;    // 95.49 mH at 1kHz
		static constexpr double butter_fc_norm = 1000.0;      // Normalization frequency

		// Parameters
		int ladderType = 0; // 0=Butterworth, 1=Bessel, 2=Constant-K
		double frequency = 1000.0;
		double q = 0.707;
		bool frequencyWarping = false;
		double sampleRate = 44100.0;

		void prepare(PrepareSpecs specs)
		{
			sampleRate = specs.sampleRate;
			createAllWDFs();
			updateFilterParameters();
			reset();
		}

		void createAllWDFs()
		{
			// ===============| Create Butterworth WDF - LEFT |===============
			aspik::WdfAdaptorBase::connectAdaptors(&seriesAdaptor_L1_Butter_L, &parallelAdaptor_C1_Butter_L);
			aspik::WdfAdaptorBase::connectAdaptors(&parallelAdaptor_C1_Butter_L, &seriesTerminatedAdaptor_L2_Butter_L);
			seriesAdaptor_L1_Butter_L.setSourceResistance(600.0);
			seriesTerminatedAdaptor_L2_Butter_L.setTerminalResistance(600.0);

			// ===============| Create Butterworth WDF - RIGHT |===============
			aspik::WdfAdaptorBase::connectAdaptors(&seriesAdaptor_L1_Butter_R, &parallelAdaptor_C1_Butter_R);
			aspik::WdfAdaptorBase::connectAdaptors(&parallelAdaptor_C1_Butter_R, &seriesTerminatedAdaptor_L2_Butter_R);
			seriesAdaptor_L1_Butter_R.setSourceResistance(600.0);
			seriesTerminatedAdaptor_L2_Butter_R.setTerminalResistance(600.0);
		}

		void reset()
		{
			// Reset Butterworth Left
			seriesAdaptor_L1_Butter_L.reset(sampleRate);
			parallelAdaptor_C1_Butter_L.reset(sampleRate);
			seriesTerminatedAdaptor_L2_Butter_L.reset(sampleRate);

			// Reset Butterworth Right
			seriesAdaptor_L1_Butter_R.reset(sampleRate);
			parallelAdaptor_C1_Butter_R.reset(sampleRate);
			seriesTerminatedAdaptor_L2_Butter_R.reset(sampleRate);

			// Initialize chains AFTER reset
			seriesAdaptor_L1_Butter_L.initializeAdaptorChain();
			seriesAdaptor_L1_Butter_R.initializeAdaptorChain();
		}

		void handleHiseEvent(HiseEvent& e) {}

		void updateFilterParameters()
		{
			if (ladderType == 0) // Butterworth
			{
				updateButterworthComponents();

				// CRITICAL: Re-initialize adaptor chains after component changes
				seriesAdaptor_L1_Butter_L.initializeAdaptorChain();
				seriesAdaptor_L1_Butter_R.initializeAdaptorChain();
			}
		}

		void updateButterworthComponents()
		{
			double fc = frequency;

			// Optional frequency warping
			if (frequencyWarping)
			{
				double arg = (kPi * fc) / sampleRate;
				fc = fc * (tan(arg) / arg);
			}

			// Frequency scaling: scale from 1kHz reference
			double freq_scale = butter_fc_norm / fc;

			double L1_scaled = butter_L1_norm * freq_scale;
			double C1_scaled = butter_C1_norm * freq_scale;
			double L2_scaled = butter_L2_norm * freq_scale;

			// Update LEFT channel
			seriesAdaptor_L1_Butter_L.setComponent(aspik::wdfComponent::L, L1_scaled);
			parallelAdaptor_C1_Butter_L.setComponent(aspik::wdfComponent::C, C1_scaled);
			seriesTerminatedAdaptor_L2_Butter_L.setComponent(aspik::wdfComponent::L, L2_scaled);

			// Update RIGHT channel
			seriesAdaptor_L1_Butter_R.setComponent(aspik::wdfComponent::L, L1_scaled);
			parallelAdaptor_C1_Butter_R.setComponent(aspik::wdfComponent::C, C1_scaled);
			seriesTerminatedAdaptor_L2_Butter_R.setComponent(aspik::wdfComponent::L, L2_scaled);
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
			float outputL, outputR;

			switch (ladderType)
			{
			case 0: // Butterworth 3rd Order LPF
				// Process LEFT channel
				seriesAdaptor_L1_Butter_L.setInput1((double)inputL);
				outputL = (float)seriesTerminatedAdaptor_L2_Butter_L.getOutput2();

				// Process RIGHT channel  
				seriesAdaptor_L1_Butter_R.setInput1((double)inputR);
				outputR = (float)seriesTerminatedAdaptor_L2_Butter_R.getOutput2();
				break;

			case 1: // Bessel 3rd Order BSF
			case 2: // Constant-K 6th Order BPF
			default:
				// Temporarily pass through until we implement these
				outputL = inputL;
				outputR = inputR;
				break;
			}

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
				double newQ = jlimit(0.1, 10.0, v);
				if (q != newQ)
				{
					q = newQ;
					updateFilterParameters();
				}
			}
			else if (P == 2) // Ladder Type
			{
				int newType = jlimit(0, 2, (int)v);
				if (ladderType != newType)
				{
					ladderType = newType;
					updateFilterParameters();
				}
			}
			else if (P == 3) // Frequency Warping
			{
				bool newWarping = v > 0.5;
				if (frequencyWarping != newWarping)
				{
					frequencyWarping = newWarping;
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
				parameter::data p("Q", { 0.1, 10.0 });
				registerCallback<1>(p);
				p.setDefaultValue(0.707);
				p.setSkewForCentre(1.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("LadderType", { 0.0, 2.0, 1.0 });
				registerCallback<2>(p);
				p.setDefaultValue(0.0);

				StringArray ladderTypes;
				ladderTypes.add("Butterworth LPF");
				ladderTypes.add("Bessel BSF");
				ladderTypes.add("Constant-K BPF");

				p.setParameterValueNames(ladderTypes);
				data.add(std::move(p));
			}
			{
				parameter::data p("FreqWarping", { 0.0, 1.0, 1.0 });
				registerCallback<3>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}
		}
	};
}

#pragma once

#include <JuceHeader.h>
#include "src/Aspik/aspik.h"

/*
==========================| ASPIK Vicanek Filter HISE Node |==========================

Vicanek's Analog Matched Magnitude filters provide superior analog emulation.
• kMatchLP2A/B: Tight/loose fit LPF with finite gain at Nyquist
• kMatchBP2A/B: Tight/loose fit BPF with analog magnitude matching
• Uses impulse invariant poles combined with matched magnitude zeros
• Matches analog and digital transfer function magnitudes at multiple frequencies

Based on Will Pirkle's "Designing Audio Effect Plugins in C++" and Vicanek's research.
Reference: http://vicanek.de/articles/BiquadFits.pdf
*/

namespace project {

	using namespace juce;
	using namespace hise;
	using namespace scriptnode;
	using namespace aspik;

	template <int NV> struct AspikFilterVicanek : public data::filter_base
	{
		// Metadata Definitions ------------------------------------------------------------------------

		SNEX_NODE(AspikFilterVicanek);

		struct MetadataClass
		{
			SN_NODE_ID("AspikFilterVicanek");
		};

		// Node characteristics
		static constexpr bool isModNode() { return false; };
		static constexpr bool isPolyphonic() { return NV > 1; };
		static constexpr bool hasTail() { return false; };
		static constexpr bool isSuspendedOnSilence() { return true; };
		static constexpr int getFixChannelAmount() { return 2; };

		// External data slots (enable filter display)
		static constexpr int NumTables = 0;
		static constexpr int NumSliderPacks = 0;
		static constexpr int NumAudioFiles = 0;
		static constexpr int NumFilters = 1;  // Enable filter display
		static constexpr int NumDisplayBuffers = 0;

		// ASPIK Filter Objects (using unified namespace)
		aspik::AudioFilter leftFilter;
		aspik::AudioFilter rightFilter;

		// Filter display integration
		IIRCoefficients currentCoefficients;
		hise::FilterDataObject::CoefficientData coefficientData;
		double sampleRate = 44100.0;

		// Parameters
		double frequency = 1000.0;     // Cutoff/center frequency (Hz)
		double q = 0.707;             // Q factor
		int vicanekType = 0;          // 0=LP2A, 1=LP2B, 2=BP2A, 3=BP2B

		// Scriptnode Callbacks ------------------------------------------------------------------------

		void prepare(PrepareSpecs specs)
		{
			// Store sample rate for proper coefficient calculations
			sampleRate = specs.sampleRate;

			leftFilter.reset(specs.sampleRate);
			rightFilter.reset(specs.sampleRate);
			updateFilterParameters();

			// Notify HISE filter display system
			this->sendCoefficientUpdateMessage();
		}

		void reset()
		{
			leftFilter.reset(44100.0);
			rightFilter.reset(44100.0);
		}

		void handleHiseEvent(HiseEvent& e)
		{
			// No MIDI processing for filters
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
			data[0] = static_cast<float>(leftFilter.processAudioSample(static_cast<double>(data[0])));

			if (getFixChannelAmount() > 1)
			{
				data[1] = static_cast<float>(rightFilter.processAudioSample(static_cast<double>(data[1])));
			}
		}

		int handleModulation(double& value)
		{
			return 0;
		}

		void setExternalData(const ExternalData& data, int index) override
		{
			if (index == 0)
			{
				filter_base::setExternalData(data, index);
			}
		}

		// Parameter Functions -------------------------------------------------------------------------

		template <int P> void setParameter(double v)
		{
			if (P == 0) // Frequency
			{
				double newFreq = jlimit(20.0, 20000.0, v);
				if (frequency != newFreq)
				{
					frequency = newFreq;
					updateFilterParameters();
					this->sendCoefficientUpdateMessage();  // Update display
				}
			}
			else if (P == 1) // Q factor
			{
				double newQ = jlimit(0.1, 30.0, v);
				if (q != newQ)
				{
					q = newQ;
					updateFilterParameters();
					this->sendCoefficientUpdateMessage();  // Update display
				}
			}
			else if (P == 2) // Vicanek Type
			{
				int newType = jlimit(0, 3, (int)v);
				if (vicanekType != newType)
				{
					vicanekType = newType;
					updateFilterParameters();
					this->sendCoefficientUpdateMessage();  // Update display
				}
			}
		}

		void createParameters(ParameterDataList& data)
		{
			// Frequency parameter
			{
				parameter::data p("Frequency", { 20.0, 20000.0 });
				registerCallback<0>(p);
				p.setDefaultValue(1000.0);
				p.setSkewForCentre(1000.0); // Logarithmic scaling
				data.add(std::move(p));
			}

			// Q parameter
			{
				parameter::data p("Q", { 0.1, 30.0 });
				registerCallback<1>(p);
				p.setDefaultValue(0.707);
				p.setSkewForCentre(1.0);
				data.add(std::move(p));
			}

			// Vicanek Type parameter
			{
				parameter::data p("VicanekType", { 0.0, 3.0, 1.0 });
				registerCallback<2>(p);
				p.setDefaultValue(0.0);

				StringArray vicanekNames;
				vicanekNames.add("LPF");   // 0: kMatchLP2A - tight fit lowpass
				vicanekNames.add("LPF");   // 1: kMatchLP2B - loose fit lowpass
				vicanekNames.add("BPF");   // 2: kMatchBP2A - tight fit bandpass
				vicanekNames.add("BPF");   // 3: kMatchBP2B - loose fit bandpass

				p.setParameterValueNames(vicanekNames);
				data.add(std::move(p));
			}
		}

		// Filter Display Integration ------------------------------------------------------------------

		hise::FilterDataObject::CoefficientData getApproximateCoefficients() const override
		{
			return coefficientData;
		}

	private:
		// Helper Functions ----------------------------------------------------------------------------

		void updateFilterParameters()
		{
			aspik::AudioFilterParameters params;
			params.fc = frequency;
			params.Q = q;
			params.boostCut_dB = 0.0; // Not used for Vicanek filters

			// Select Vicanek algorithm based on type
			switch (vicanekType)
			{
			case 0: params.algorithm = aspik::filterAlgorithm::kMatchLP2A; break; // Tight fit LPF
			case 1: params.algorithm = aspik::filterAlgorithm::kMatchLP2B; break; // Loose fit LPF
			case 2: params.algorithm = aspik::filterAlgorithm::kMatchBP2A; break; // Tight fit BPF
			case 3: params.algorithm = aspik::filterAlgorithm::kMatchBP2B; break; // Loose fit BPF
			default: params.algorithm = aspik::filterAlgorithm::kMatchLP2A; break;
			}

			leftFilter.setParameters(params);
			rightFilter.setParameters(params);

			// Update JUCE coefficients for display approximation
			updateDisplayCoefficients();
		}

		void updateDisplayCoefficients()
		{
			// Approximate Vicanek response with standard JUCE filters
			// Vicanek filters have finite gain at Nyquist and special magnitude matching

			switch (vicanekType)
			{
			case 0: // LPF Tight Fit
			case 1: // LPF Loose Fit
				// Use standard lowpass - Vicanek LPF has similar shape but finite Nyquist gain
				currentCoefficients = IIRCoefficients::makeLowPass(sampleRate, frequency, q);
				break;

			case 2: // BPF Tight Fit  
			case 3: // BPF Loose Fit
				// Use standard bandpass - Vicanek BPF has matched magnitude characteristics
				currentCoefficients = IIRCoefficients::makeBandPass(sampleRate, frequency, q);
				break;

			default:
				currentCoefficients = IIRCoefficients::makeLowPass(sampleRate, frequency, q);
				break;
			}

			// Update coefficient data for HISE display
			coefficientData.first = currentCoefficients;
			coefficientData.second = 1;
			coefficientData.obj = nullptr;
			coefficientData.customFunction = nullptr;
		}
	};

} // namespace project

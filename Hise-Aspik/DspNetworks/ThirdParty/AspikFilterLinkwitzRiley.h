#pragma once

#include <JuceHeader.h>
#include "src/Aspik/aspik.h"

/*
==========================| ASPIK LinkwitzRiley Filter HISE Node |==========================

Linkwitz-Riley filters provide perfect crossover reconstruction for audio splitting.
• 2nd-order filters with -12dB/octave rolloff, designed for complementary use
• LPF and HPF outputs sum to perfect reconstruction of original signal
• Essential for speaker crossovers and multiband processing applications

Based on Will Pirkle's "Designing Audio Effect Plugins in C++" LWRLPF2 and LWRHPF2 algorithms.
*/

namespace project {

	using namespace juce;
	using namespace hise;
	using namespace scriptnode;
	using namespace aspik;

	template <int NV> struct AspikFilterLinkwitzRiley : public data::filter_base
	{
		// Metadata Definitions ------------------------------------------------------------------------

		SNEX_NODE(AspikFilterLinkwitzRiley);

		struct MetadataClass
		{
			SN_NODE_ID("AspikFilterLinkwitzRiley");
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
		FilterDataObject::CoefficientData coefficientData;
		double sampleRate = 44100.0;

		// Parameters
		double frequency = 1000.0;
		int filterType = 0; // 0 = LPF, 1 = HPF

		// Scriptnode Callbacks ------------------------------------------------------------------------

		void prepare(PrepareSpecs specs)
		{
			// Store sample rate for proper coefficient calculations
			sampleRate = specs.sampleRate;

			// Initialize both channel filters with sample rate
			leftFilter.reset(specs.sampleRate);
			rightFilter.reset(specs.sampleRate);

			// Set initial filter parameters
			updateFilterParameters();

			// Notify HISE filter display system
			this->sendCoefficientUpdateMessage();
		}

		void reset()
		{
			// Reset filter states
			leftFilter.reset(44100.0);
			rightFilter.reset(44100.0);
		}

		void handleHiseEvent(HiseEvent& e)
		{
			// No MIDI processing needed for filters
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
			// Process each channel through the ASPIK filters
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
			if (P == 0) // Frequency parameter
			{
				double newFreq = jlimit(20.0, 20000.0, v);
				if (frequency != newFreq)
				{
					frequency = newFreq;
					updateFilterParameters();
					this->sendCoefficientUpdateMessage();  // Update display
				}
			}
			else if (P == 1) // Filter Type parameter
			{
				int newType = jlimit(0, 1, (int)v);
				if (filterType != newType)
				{
					filterType = newType;
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
				p.setSkewForCentre(1000.0);
				data.add(std::move(p));
			}

			// Filter Type parameter
			{
				parameter::data p("FilterType", { 0.0, 1.0, 1.0 });
				registerCallback<1>(p);
				p.setDefaultValue(0.0);

				StringArray filterNames;
				filterNames.add("LowPass");   // 0: LWRLPF2
				filterNames.add("HighPass");  // 1: LWRHPF2

				p.setParameterValueNames(filterNames);
				data.add(std::move(p));
			}
		}

		// Filter Display Integration ------------------------------------------------------------------

		FilterDataObject::CoefficientData getApproximateCoefficients() const override
		{
			return coefficientData;
		}

	private:
		// Helper Functions ----------------------------------------------------------------------------

		void updateFilterParameters()
		{
			// Create parameter structure for ASPIK filters
			aspik::AudioFilterParameters params;
			params.fc = frequency;
			params.Q = 0.707; // Not used for Linkwitz-Riley but required by structure
			params.boostCut_dB = 0.0; // Not used for Linkwitz-Riley

			// Set the appropriate Linkwitz-Riley algorithm
			if (filterType == 0)
			{
				params.algorithm = aspik::filterAlgorithm::kLWRLPF2; // Linkwitz-Riley Low Pass
			}
			else
			{
				params.algorithm = aspik::filterAlgorithm::kLWRHPF2; // Linkwitz-Riley High Pass
			}

			// Apply parameters to both channel filters
			leftFilter.setParameters(params);
			rightFilter.setParameters(params);

			// Update JUCE coefficients for display
			updateDisplayCoefficients();
		}

		void updateDisplayCoefficients()
		{
			// Use HISE's built-in coefficient mappings for Linkwitz-Riley filters
			// Linkwitz-Riley is essentially a 2nd-order Butterworth filter

			if (filterType == 0) // Low Pass
			{
				// Use standard lowpass with Q=0.707 (Butterworth response)
				currentCoefficients = IIRCoefficients::makeLowPass(sampleRate, frequency, 0.707);
			}
			else // High Pass
			{
				// Use standard highpass with Q=0.707 (Butterworth response)
				currentCoefficients = IIRCoefficients::makeHighPass(sampleRate, frequency, 0.707);
			}

			// Update coefficient data for HISE display
			coefficientData.first = currentCoefficients;
			coefficientData.second = 1;
			coefficientData.obj = nullptr;
			coefficientData.customFunction = nullptr;
		}
	};

} // namespace project

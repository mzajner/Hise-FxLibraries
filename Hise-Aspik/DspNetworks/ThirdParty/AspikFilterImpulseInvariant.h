#pragma once

#include <JuceHeader.h>
#include "src/Aspik/aspik.h"

/*
==========================| ASPIK Impulse Invariant Filter HISE Node |==========================

Impulse Invariant filters preserve time domain characteristics of analog filters.
• kImpInvLP1: 1st-order impulse invariant lowpass - exponential decay impulse response
• kImpInvLP2: 2nd-order impulse invariant lowpass - complex pole placement
• Trade frequency domain accuracy for perfect time domain impulse response
• Limited to lowpass designs due to aliasing issues with other types

Based on Will Pirkle's "Designing Audio Effect Plugins in C++" Impulse Invariant algorithms.
Mathematical foundation: Inverse Laplace → sample → Z-transform method.
*/

namespace project {

	using namespace juce;
	using namespace hise;
	using namespace scriptnode;
	using namespace aspik;

	template <int NV> struct AspikFilterImpulseInvariant : public data::filter_base
	{
		// Metadata Definitions ------------------------------------------------------------------------

		SNEX_NODE(AspikFilterImpulseInvariant);

		struct MetadataClass
		{
			SN_NODE_ID("AspikFilterImpulseInvariant");
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
		double frequency = 1000.0;     // Cutoff frequency (Hz)
		double q = 0.707;             // Q factor (for 2nd order)
		int impulseType = 0;          // 0 = 1st order, 1 = 2nd order

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
			else if (P == 1) // Q (for 2nd order only)
			{
				double newQ = jlimit(0.1, 30.0, v);
				if (q != newQ)
				{
					q = newQ;
					updateFilterParameters();
					this->sendCoefficientUpdateMessage();  // Update display
				}
			}
			else if (P == 2) // Impulse Type
			{
				int newType = jlimit(0, 1, (int)v);
				if (impulseType != newType)
				{
					impulseType = newType;
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

			// Q parameter (primarily for 2nd order)
			{
				parameter::data p("Q", { 0.1, 30.0 });
				registerCallback<1>(p);
				p.setDefaultValue(0.707);
				p.setSkewForCentre(1.0);
				data.add(std::move(p));
			}

			// Impulse Type parameter
			{
				parameter::data p("ImpulseType", { 0.0, 1.0, 1.0 });
				registerCallback<2>(p);
				p.setDefaultValue(0.0);

				StringArray impulseNames;
				impulseNames.add("1st Order");   // 0: kImpInvLP1 - simple exponential decay
				impulseNames.add("2nd Order");   // 1: kImpInvLP2 - complex pole placement

				p.setParameterValueNames(impulseNames);
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
			params.boostCut_dB = 0.0; // Not used for impulse invariant filters

			// Select impulse invariant algorithm based on order
			if (impulseType == 0)
			{
				params.algorithm = aspik::filterAlgorithm::kImpInvLP1; // 1st order impulse invariant
			}
			else
			{
				params.algorithm = aspik::filterAlgorithm::kImpInvLP2; // 2nd order impulse invariant
			}

			leftFilter.setParameters(params);
			rightFilter.setParameters(params);

			// Update JUCE coefficients for display approximation
			updateDisplayCoefficients();
		}

		void updateDisplayCoefficients()
		{
			// Approximate Impulse Invariant response with standard JUCE lowpass
			// This is a "best effort" approximation since Impulse Invariant has unique characteristics

			if (impulseType == 0) // 1st order
			{
				// Use 1st order lowpass approximation
				// Impulse Invariant 1st order has exponential decay: h(t) = ωc * e^(-ωc*t)
				// Approximate with standard 1st order lowpass
				double omega = 2.0 * M_PI * frequency / sampleRate;
				double gamma = std::cos(omega) / (1.0 + std::sin(omega));

				// Create simple 1st order lowpass coefficients
				currentCoefficients = IIRCoefficients::makeLowPass(sampleRate, frequency);
			}
			else // 2nd order
			{
				// Use 2nd order lowpass with Q factor
				// Impulse Invariant 2nd order uses complex pole placement
				// The frequency response will differ but this gives visual reference
				currentCoefficients = IIRCoefficients::makeLowPass(sampleRate, frequency, q);
			}

			// Update coefficient data for HISE display
			coefficientData.first = currentCoefficients;
			coefficientData.second = 1;
			coefficientData.obj = nullptr;
			coefficientData.customFunction = nullptr;
		}
	};

} // namespace project

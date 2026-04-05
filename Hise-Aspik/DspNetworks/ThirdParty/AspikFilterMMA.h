#pragma once

#include <JuceHeader.h>
#include "src/Aspik/aspik.h"

/*
==========================| ASPIK MMA Filter HISE Node |==========================

Musical Magnitude Approximation (MMA) filters based on DLS Level II specification.
• kMMALPF2: MMA lowpass with automatic gain reduction as Q increases (Moog-like behavior)
• kMMALPF2B: MMA lowpass with gain reduction disabled (pure response)
• Designed directly in z-plane with conjugate pole pairs for musical resonance
• Asymptotic cutoff frequency design - less sensitive to resonant peak height

Based on Will Pirkle's "Designing Audio Effect Plugins in C++" MMA algorithms.
Features the same gain reduction behavior as the famous Moog ladder filter.
*/

namespace project {

	using namespace juce;
	using namespace hise;
	using namespace scriptnode;
	using namespace aspik;

	template <int NV> struct AspikFilterMMA : public data::filter_base
	{
		// Metadata Definitions ------------------------------------------------------------------------

		SNEX_NODE(AspikFilterMMA);

		struct MetadataClass
		{
			SN_NODE_ID("AspikFilterMMA");
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
		double frequency = 1000.0;     // Cutoff/peak frequency (Hz)
		double q = 0.707;             // Q factor - controls resonance
		int mmaType = 0;              // 0 = with gain reduction, 1 = without

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
			else if (P == 2) // MMA Type
			{
				int newType = jlimit(0, 1, (int)v);
				if (mmaType != newType)
				{
					mmaType = newType;
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

			// MMA Type parameter
			{
				parameter::data p("MMAType", { 0.0, 1.0, 1.0 });
				registerCallback<2>(p);
				p.setDefaultValue(0.0);

				StringArray mmaNames;
				mmaNames.add("With Gain Reduction");    // 0: kMMALPF2 - Moog-like gain reduction
				mmaNames.add("Without Gain Reduction"); // 1: kMMALPF2B - pure response

				p.setParameterValueNames(mmaNames);
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
			params.boostCut_dB = 0.0; // Not used for MMA filters

			// Select MMA algorithm based on gain reduction setting
			if (mmaType == 0)
			{
				params.algorithm = aspik::filterAlgorithm::kMMALPF2; // With gain reduction (Moog-like)
			}
			else
			{
				params.algorithm = aspik::filterAlgorithm::kMMALPF2B; // Without gain reduction
			}

			leftFilter.setParameters(params);
			rightFilter.setParameters(params);

			// Update JUCE coefficients for display approximation
			updateDisplayCoefficients();
		}

		void updateDisplayCoefficients()
		{
			// Approximate MMA response with standard JUCE lowpass
			// MMA has finite gain at Nyquist and special Q behavior

			double displayQ = q;

			// For type 0 (with gain reduction), simulate the Moog-like gain reduction
			if (mmaType == 0 && q > 0.707)
			{
				// MMA reduces gain by half the resonant peak gain in dB
				// This affects the visual representation of the peak
				displayQ = std::min(q * 0.8, 10.0); // Approximate visual reduction
			}

			// Use standard lowpass but with modified Q to approximate MMA behavior
			currentCoefficients = IIRCoefficients::makeLowPass(sampleRate, frequency, displayQ);

			// Update coefficient data for HISE display
			coefficientData.first = currentCoefficients;
			coefficientData.second = 1;
			coefficientData.obj = nullptr;
			coefficientData.customFunction = nullptr;
		}
	};

} // namespace project

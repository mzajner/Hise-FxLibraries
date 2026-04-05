#pragma once

#include <JuceHeader.h>
#include "src/Aspik/aspik.h"

/*
==========================| ASPIK ReverbTank HISE Node |==========================

Professional reverb tank based on Will Pirkle's "Designing Audio Effects Plugins in C++"
Implementation of the enhanced Spin Semiconductor-style reverb tank with:
• Four-branch tank circuit with nested all-pass filters
• LFO modulation for natural sound variation
• Low-pass filtering for high-frequency damping
• Two-band shelving EQ for frequency shaping
• Prime number-based output taps for stereo width
• Configurable density (thick/sparse) settings

This is a high-quality algorithmic reverb suitable for professional applications.
*/

namespace project {

	using namespace juce;
	using namespace hise;
	using namespace scriptnode;
	using namespace aspik;

	// ==========================| ASPIK ReverbTank Node |==========================

	template <int NV> struct AspikReverbTank : public data::base
	{
		// Metadata Definitions ------------------------------------------------------------------------

		SNEX_NODE(AspikReverbTank);

		struct MetadataClass
		{
			SN_NODE_ID("AspikReverbTank");
		};

		// Node characteristics
		static constexpr bool isModNode() { return false; };
		static constexpr bool isPolyphonic() { return NV > 1; };
		static constexpr bool hasTail() { return true; };  // Reverb produces a tail
		static constexpr bool isSuspendedOnSilence() { return false; }; // Don't suspend reverb
		static constexpr int getFixChannelAmount() { return 2; };

		// External data slots
		static constexpr int NumTables = 0;
		static constexpr int NumSliderPacks = 0;
		static constexpr int NumAudioFiles = 0;
		static constexpr int NumFilters = 0;
		static constexpr int NumDisplayBuffers = 0;

		// ASPIK ReverbTank Object -----------------------------------------------------------------
		aspik::ReverbTank reverbTank;

		// Parameter storage for efficient processing
		double currentSampleRate = 44100.0;

		// Parameter values (HISE range: 0.0 to 1.0)
		double reverbTime = 0.5;        // kRT parameter (0.0 to 1.0)
		double damping = 0.3;           // lpf_g parameter (0.0 to 1.0) 
		double preDelay = 0.0;          // Pre-delay time (0.0 to 1.0 = 0 to 100ms)
		double lowShelfFreq = 0.25;     // Low shelf frequency (0.0 to 1.0 = 50Hz to 500Hz)
		double lowShelfGain = 0.5;      // Low shelf gain (0.0 to 1.0 = -12dB to +12dB)
		double highShelfFreq = 0.75;    // High shelf frequency (0.0 to 1.0 = 5kHz to 15kHz)
		double highShelfGain = 0.4;     // High shelf gain (0.0 to 1.0 = -12dB to +12dB)
		double wetLevel = 0.7;          // Wet level (0.0 to 1.0 = -96dB to 0dB)
		double dryLevel = 0.7;          // Dry level (0.0 to 1.0 = -96dB to 0dB)
		double density = 0.0;           // Density: 0.0 = sparse, 1.0 = thick

		// Advanced tweaker parameters (normally hidden from user)
		double apfDelayMax = 0.5;       // APF max delay (0.0 to 1.0 = 1ms to 10ms)
		double apfDelayWeight = 1.0;    // APF delay weighting (0.0 to 1.0)
		double fixedDelayMax = 0.5;     // Fixed delay max (0.0 to 1.0 = 10ms to 100ms)
		double fixedDelayWeight = 1.0;  // Fixed delay weighting (0.0 to 1.0)

		// Scriptnode Callbacks ------------------------------------------------------------------------

		void prepare(PrepareSpecs specs)
		{
			currentSampleRate = specs.sampleRate;

			// Initialize the ReverbTank
			reverbTank.reset(currentSampleRate);

			// Apply initial parameters
			updateReverbParameters();
		}

		void reset()
		{
			reverbTank.reset(currentSampleRate);
			updateReverbParameters();
		}

		void handleHiseEvent(HiseEvent& e)
		{
			// ReverbTank doesn't need MIDI events
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
			// Prepare input frame (HISE uses double, ASPIK uses float)
			float inputFrame[2] = {
				static_cast<float>(data[0]),
				static_cast<float>(data.size() > 1 ? data[1] : data[0])
			};

			float outputFrame[2] = { 0.0f, 0.0f };

			// Process through ASPIK ReverbTank
			reverbTank.processAudioFrame(inputFrame, outputFrame, 2, 2);

			// Write back to HISE (convert float to double)
			data[0] = static_cast<double>(outputFrame[0]);
			if (data.size() > 1)
				data[1] = static_cast<double>(outputFrame[1]);
		}

		int handleModulation(double& value)
		{
			return 0;
		}

		void setExternalData(const ExternalData& data, int index)
		{
			// No external data required
		}

		// Parameter Functions -------------------------------------------------------------------------

		template <int P> void setParameter(double v)
		{
			bool needsUpdate = false;

			if (P == 0) // Reverb Time
			{
				if (reverbTime != v) { reverbTime = jlimit(0.0, 1.0, v); needsUpdate = true; }
			}
			else if (P == 1) // Damping
			{
				if (damping != v) { damping = jlimit(0.0, 1.0, v); needsUpdate = true; }
			}
			else if (P == 2) // Pre-Delay
			{
				if (preDelay != v) { preDelay = jlimit(0.0, 1.0, v); needsUpdate = true; }
			}
			else if (P == 3) // Low Shelf Frequency
			{
				if (lowShelfFreq != v) { lowShelfFreq = jlimit(0.0, 1.0, v); needsUpdate = true; }
			}
			else if (P == 4) // Low Shelf Gain
			{
				if (lowShelfGain != v) { lowShelfGain = jlimit(0.0, 1.0, v); needsUpdate = true; }
			}
			else if (P == 5) // High Shelf Frequency
			{
				if (highShelfFreq != v) { highShelfFreq = jlimit(0.0, 1.0, v); needsUpdate = true; }
			}
			else if (P == 6) // High Shelf Gain
			{
				if (highShelfGain != v) { highShelfGain = jlimit(0.0, 1.0, v); needsUpdate = true; }
			}
			else if (P == 7) // Wet Level
			{
				if (wetLevel != v) { wetLevel = jlimit(0.0, 1.0, v); needsUpdate = true; }
			}
			else if (P == 8) // Dry Level
			{
				if (dryLevel != v) { dryLevel = jlimit(0.0, 1.0, v); needsUpdate = true; }
			}
			else if (P == 9) // Density
			{
				if (density != v) { density = jlimit(0.0, 1.0, v); needsUpdate = true; }
			}
			else if (P == 10) // APF Delay Max (tweaker)
			{
				if (apfDelayMax != v) { apfDelayMax = jlimit(0.0, 1.0, v); needsUpdate = true; }
			}
			else if (P == 11) // APF Delay Weight (tweaker)
			{
				if (apfDelayWeight != v) { apfDelayWeight = jlimit(0.0, 1.0, v); needsUpdate = true; }
			}
			else if (P == 12) // Fixed Delay Max (tweaker)
			{
				if (fixedDelayMax != v) { fixedDelayMax = jlimit(0.0, 1.0, v); needsUpdate = true; }
			}
			else if (P == 13) // Fixed Delay Weight (tweaker)
			{
				if (fixedDelayWeight != v) { fixedDelayWeight = jlimit(0.0, 1.0, v); needsUpdate = true; }
			}

			if (needsUpdate)
			{
				updateReverbParameters();
			}
		}

		void createParameters(ParameterDataList& data)
		{
			// Main reverb parameters
			{
				parameter::data p("ReverbTime", { 0.0, 1.0 });
				registerCallback<0>(p);
				p.setDefaultValue(0.5);
				data.add(std::move(p));
			}

			{
				parameter::data p("Damping", { 0.0, 1.0 });
				registerCallback<1>(p);
				p.setDefaultValue(0.3);
				data.add(std::move(p));
			}

			{
				parameter::data p("PreDelay", { 0.0, 1.0 });
				registerCallback<2>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("LowShelfFreq", { 0.0, 1.0 });
				registerCallback<3>(p);
				p.setDefaultValue(0.25);
				data.add(std::move(p));
			}

			{
				parameter::data p("LowShelfGain", { 0.0, 1.0 });
				registerCallback<4>(p);
				p.setDefaultValue(0.5);
				data.add(std::move(p));
			}

			{
				parameter::data p("HighShelfFreq", { 0.0, 1.0 });
				registerCallback<5>(p);
				p.setDefaultValue(0.75);
				data.add(std::move(p));
			}

			{
				parameter::data p("HighShelfGain", { 0.0, 1.0 });
				registerCallback<6>(p);
				p.setDefaultValue(0.4);
				data.add(std::move(p));
			}

			{
				parameter::data p("WetLevel", { 0.0, 1.0 });
				registerCallback<7>(p);
				p.setDefaultValue(0.7);
				data.add(std::move(p));
			}

			{
				parameter::data p("DryLevel", { 0.0, 1.0 });
				registerCallback<8>(p);
				p.setDefaultValue(0.7);
				data.add(std::move(p));
			}

			{
				parameter::data p("Density", { 0.0, 1.0 });
				registerCallback<9>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}

			// Advanced tweaker parameters (for sound design)
			{
				parameter::data p("APF_DelayMax", { 0.0, 1.0 });
				registerCallback<10>(p);
				p.setDefaultValue(0.5);
				data.add(std::move(p));
			}

			{
				parameter::data p("APF_DelayWeight", { 0.0, 1.0 });
				registerCallback<11>(p);
				p.setDefaultValue(1.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Fixed_DelayMax", { 0.0, 1.0 });
				registerCallback<12>(p);
				p.setDefaultValue(0.5);
				data.add(std::move(p));
			}

			{
				parameter::data p("Fixed_DelayWeight", { 0.0, 1.0 });
				registerCallback<13>(p);
				p.setDefaultValue(1.0);
				data.add(std::move(p));
			}
		}

	private:

		// Helper function to update ASPIK ReverbTank parameters
		void updateReverbParameters()
		{
			aspik::ReverbTankParameters params = reverbTank.getParameters();

			// Convert HISE normalized values (0.0-1.0) to ASPIK parameter ranges

			// Core reverb parameters
			params.kRT = reverbTime;  // 0.0 to 1.0 direct mapping
			params.lpf_g = damping;   // 0.0 to 1.0 direct mapping

			// Pre-delay: 0.0 to 1.0 maps to 0.0 to 100.0 ms
			params.preDelayTime_mSec = preDelay * 100.0;

			// Low shelf frequency: 0.0 to 1.0 maps to 50Hz to 500Hz (log scale)
			params.lowShelf_fc = 50.0 * std::pow(10.0, lowShelfFreq);  // 50Hz to 500Hz

			// Low shelf gain: 0.0 to 1.0 maps to -12dB to +12dB
			params.lowShelfBoostCut_dB = (lowShelfGain - 0.5) * 24.0;  // -12dB to +12dB

			// High shelf frequency: 0.0 to 1.0 maps to 5kHz to 15kHz
			params.highShelf_fc = 5000.0 + (highShelfFreq * 10000.0);  // 5kHz to 15kHz

			// High shelf gain: 0.0 to 1.0 maps to -12dB to +12dB  
			params.highShelfBoostCut_dB = (highShelfGain - 0.5) * 24.0;  // -12dB to +12dB

			// Wet/Dry levels: 0.0 to 1.0 maps to -96dB to 0dB
			params.wetLevel_dB = (wetLevel == 0.0) ? -96.0 : (wetLevel - 1.0) * 96.0;  // -96dB to 0dB
			params.dryLevel_dB = (dryLevel == 0.0) ? -96.0 : (dryLevel - 1.0) * 96.0;  // -96dB to 0dB

			// Density: convert to enum
			params.density = (density > 0.5) ? aspik::reverbDensity::kThick : aspik::reverbDensity::kSparse;

			// Advanced tweaker parameters
			// APF delay max: 0.0 to 1.0 maps to 1.0ms to 10.0ms
			params.apfDelayMax_mSec = 1.0 + (apfDelayMax * 9.0);  // 1ms to 10ms

			// APF delay weighting: 0.0 to 1.0 maps to 10% to 100%
			params.apfDelayWeight_Pct = 10.0 + (apfDelayWeight * 90.0);  // 10% to 100%

			// Fixed delay max: 0.0 to 1.0 maps to 10.0ms to 100.0ms
			params.fixeDelayMax_mSec = 10.0 + (fixedDelayMax * 90.0);  // 10ms to 100ms

			// Fixed delay weighting: 0.0 to 1.0 maps to 10% to 100%
			params.fixeDelayWeight_Pct = 10.0 + (fixedDelayWeight * 90.0);  // 10% to 100%

			// Apply parameters to reverb tank
			reverbTank.setParameters(params);
		}
	};

} // namespace project

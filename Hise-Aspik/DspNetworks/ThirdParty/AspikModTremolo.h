#pragma once
#include <JuceHeader.h>
#include "src/Aspik/aspik.h"

/*
 ==========================| ASPIK Tremolo |==========================
 Classic amplitude modulation effect using LFO
 - LFO modulates gain coefficient for tremolo effect
 - Max-down modulation: increasing depth attenuates signal more
 - Stereo version uses inverted LFO for one channel
 */

namespace project
{
	using namespace juce;
	using namespace hise;
	using namespace scriptnode;
	using namespace aspik;

	// ==========================| The node class with all required callbacks |==========================

	template <int NV> struct AspikModTremolo : public data::base
	{
		SNEX_NODE(AspikModTremolo);

		struct MetadataClass
		{
			SN_NODE_ID("AspikModTremolo");
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

		// ASPIK LFO Object
		aspik::LFO lfo;

		// Parameters
		double lfoRate = 5.0;
		double depth = 50.0;
		int waveform = 1;
		bool stereoMode = false;
		bool dBMode = false; // false=linear gain, true=dB-based attenuation

		void prepare(PrepareSpecs specs)
		{
			lfo.reset(specs.sampleRate);
			updateLfoParameters();
		}

		void reset()
		{
			lfo.reset(44100.0);
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
			// Generate LFO output
			aspik::SignalGenData lfoOutput = lfo.renderAudioOutput();

			// Get input samples
			double leftInput = data[0];
			double rightInput = data[1];

			// Calculate gain modulation using max-down approach
			// Convert depth from percentage to coefficient [0.0, 1.0]
			double depthCoeff = depth / 100.0;

			// Left channel: use normal LFO output
			double leftLfoValue = lfoOutput.normalOutput;
			double leftGain = calculateMaxDownGain(leftLfoValue, depthCoeff);

			// Right channel: use inverted LFO if stereo mode, otherwise same as left
			double rightLfoValue = stereoMode ? lfoOutput.invertedOutput : leftLfoValue;
			double rightGain = calculateMaxDownGain(rightLfoValue, depthCoeff);

			// Apply tremolo effect
			data[0] = static_cast<float>(leftInput * leftGain);
			data[1] = static_cast<float>(rightInput * rightGain);
		}

		int handleModulation(double& value)
		{
			return 0;
		}

		void setExternalData(const ExternalData& data, int index)
		{

		}

		// Parameter Functions -------------------------------------------------------------------------

		template <int P> void setParameter(double v)
		{
			bool needsUpdate = false;

			if (P == 0) // LFO Rate
			{
				double newRate = jlimit(0.1, 20.0, v);
				if (lfoRate != newRate)
				{
					lfoRate = newRate;
					needsUpdate = true;
				}
			}
			else if (P == 1) // Depth
			{
				double newDepth = jlimit(0.0, 100.0, v);
				if (depth != newDepth)
				{
					depth = newDepth;
				}
			}
			else if (P == 2) // Waveform
			{
				int newWaveform = jlimit(0, 2, (int)v);
				if (waveform != newWaveform)
				{
					waveform = newWaveform;
					needsUpdate = true;
				}
			}
			else if (P == 3) // Stereo Mode
			{
				bool newStereoMode = v >= 0.5;
				if (stereoMode != newStereoMode)
				{
					stereoMode = newStereoMode;
				}
			}
			else if (P == 4) // dB Mode
			{
				bool newDbMode = v >= 0.5;
				if (dBMode != newDbMode)
				{
					dBMode = newDbMode;
				}
			}

			if (needsUpdate)
			{
				updateLfoParameters();
			}
		}

		void createParameters(ParameterDataList& data)
		{
			{
				parameter::data p("Rate", { 0.1, 20.0 });
				registerCallback<0>(p);
				p.setDefaultValue(5.0);
				p.setSkewForCentre(2.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Depth", { 0.0, 100.0 });
				registerCallback<1>(p);
				p.setDefaultValue(50.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Waveform", { 0.0, 2.0 });
				registerCallback<2>(p);
				p.setDefaultValue(1.0);

				StringArray waveformNames;
				waveformNames.add("Triangle");
				waveformNames.add("Sine");
				waveformNames.add("Sawtooth");

				p.setParameterValueNames(waveformNames);
				data.add(std::move(p));
			}

			{
				parameter::data p("Stereo", { 0.0, 1.0 });
				registerCallback<3>(p);
				p.setDefaultValue(0.0);

				StringArray stereoNames;
				stereoNames.add("Mono");
				stereoNames.add("Stereo");

				p.setParameterValueNames(stereoNames);
				data.add(std::move(p));
			}

			{
				parameter::data p("Mode", { 0.0, 1.0 });
				registerCallback<4>(p);
				p.setDefaultValue(0.0);

				StringArray modeNames;
				modeNames.add("Linear");
				modeNames.add("dB");

				p.setParameterValueNames(modeNames);
				data.add(std::move(p));
			}
		}

	private:
		void updateLfoParameters()
		{
			aspik::OscillatorParameters params;
			params.frequency_Hz = lfoRate;

			switch (waveform)
			{
			case 0: params.waveform = aspik::generatorWaveform::kTriangle; break;
			case 1: params.waveform = aspik::generatorWaveform::kSin; break;
			case 2: params.waveform = aspik::generatorWaveform::kSaw; break;
			default: params.waveform = aspik::generatorWaveform::kSin; break;
			}

			lfo.setParameters(params);
		}

		// Max-down modulation as described in homework section
		double calculateMaxDownGain(double lfoValue, double depthCoeff)
		{
			// Convert bipolar LFO [-1, +1] to unipolar [0, +1]
			double unipolarLfo = (lfoValue + 1.0) * 0.5;

			// Max-down modulation: modulate from maximum (1.0) downward
			// When depth = 0, gain = 1.0 (no effect)
			// When depth = 1.0, gain varies from 1.0 to 0.0
			double gain = 1.0 - (depthCoeff * unipolarLfo);

			// Apply dB mode if selected
			if (dBMode)
			{
				// Convert to dB, apply attenuation, convert back to linear
				double gainDb = juce::Decibels::gainToDecibels(gain, -60.0);
				return juce::Decibels::decibelsToGain(gainDb);
			}
			else
			{
				// Linear gain mode
				return jlimit(0.0, 1.0, gain);
			}
		}
	};

}

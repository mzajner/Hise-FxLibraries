/*
==========================| ASPIK Direct Form Oscillator |==========================
Direct Form Sinusoid Waveform Oscillator for modulating external signal.
Useful for the creation of vibrato, tremolo, and ring modulator. 
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

template <int NV> struct AspikModOsc: public data::base
{
	SNEX_NODE(AspikModOsc);
	
	struct MetadataClass
	{
		SN_NODE_ID("AspikModOsc");
	};
	
	static constexpr bool isModNode() { return true; };
	static constexpr bool isPolyphonic() { return NV > 1; };
	static constexpr bool hasTail() { return false; };
	static constexpr bool isSuspendedOnSilence() { return false; };
	//static constexpr int getFixChannelAmount() { return 2; };
	
	static constexpr int NumTables = 0;
	static constexpr int NumSliderPacks = 0;
	static constexpr int NumAudioFiles = 0;
	static constexpr int NumFilters = 0;
	static constexpr int NumDisplayBuffers = 0;
	
    // ASPIK Objects
	aspik::OscillatorParameters parameters[NV];
	aspik::DFOscillator dfo[NV];
	double sampleRate = 44100.0;

	// Paramters
	enum Parameters
	{
		Frequency = 0
	};


	// Scriptnode Callbacks ------------------------------------------------------------------------
	
	void prepare(PrepareSpecs specs)
	{
		sampleRate = specs.sampleRate;
		for (int v = 0; v < NV; v++)
		{
			dfo[v].reset(specs.sampleRate);
			updateParameters(v);
		}
	}
	
	void reset()
	{
		for (int v = 0; v < NV; v++)
		{
			dfo[v].reset(sampleRate);
		}
	}
	
	void handleHiseEvent(HiseEvent& e)
	{
		// We'll ignore MIDI events for now
	}
	
	template <typename T> void process(T& data)
	{
		
		auto numSamples = data.getNumSamples();	
		auto numChannels = data.getNumChannels();	

		for (int c = 0; c < jmin(numChannels, 2); c++)
		{
			for (int s = 0; s < numSamples; s++)
			{
				int voiceIndex = 0;
				if constexpr (NV > 1)
				{
					voiceIndex = 0;
				}
				
				auto oscillatorOutput = dfo[voiceIndex].renderAudioOutput();
				float modValue = static_cast<float>(oscillatorOutput.normalOutput);

				data[c][s] = data[c][s] * modValue;
			}
		}
		
	}
	
	template <typename T> void processFrame(T& data)
	{
		int voiceIndex = 0;
		if constexpr (NV > 1)
		{
			voiceIndex = 0;
		}
		auto oscillatorOutput = dfo[voiceIndex].renderAudioOutput();
		float modValue = static_cast<float>(oscillatorOutput.normalOutput);
		for (int channel = 0; channel < jmin((int)data.size(), 2); channel++)
		{
			data[channel] = data[channel] * modValue;
		}
	}
	
	int handleModulation(double& value)
	{
		auto oscillatorOutput = dfo[0].renderAudioOutput();
		value = oscillatorOutput.normalOutput;
		return 1;
	}
	
	void setExternalData(const ExternalData& data, int index)
	{
		
	}
	// Parameter Functions -------------------------------------------------------------------------
	
	template <int P> void setParameter(double v)
	{
		if (P == Frequency)
		{
			for (int voice = 0; voice < NV; voice++)  // Use 'voice' not 'v'
			{
				parameters[voice].frequency_Hz = jlimit(0.1, 20000.0, v);
				updateParameters(voice);
			}
		}
	}
	
	void createParameters(ParameterDataList& data)
	{
		{
			parameter::data p("Frequency", { 0.1, 20000.0 });
			registerCallback<0>(p);
			p.setDefaultValue(1.0);
			p.setSkewForCentre(440.0);
			data.add(std::move(p));
		}
	}

	private:
		void updateParameters(int voice)
		{
			parameters[voice].waveform = generatorWaveform::kSin;
			dfo[voice].setParameters(parameters[voice]);
		}
};
}



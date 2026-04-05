// ==================================| Third Party Node Template |==================================

#pragma once
#include <JuceHeader.h>
#include "src/Aspik/aspik.h"
#include "src/Aspik/homework.h"

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

// ==========================| The node class with all required callbacks |==========================

template <int NV> struct AspikWaveshaperBitcrush: public data::base
{
	// Metadata Definitions ------------------------------------------------------------------------
	
	SNEX_NODE(AspikWaveshaperBitcrush);
	
	struct MetadataClass
	{
		SN_NODE_ID("AspikWaveshaperBitcrush");
	};
	
	static constexpr bool isModNode() { return false; };
	static constexpr bool isPolyphonic() { return NV > 1; };
	static constexpr bool hasTail() { return false; };
	static constexpr bool isSuspendedOnSilence() { return true; };
	// constexpr int getFixChannelAmount() { return 2; };
	
	static constexpr int NumTables = 0;
	static constexpr int NumSliderPacks = 0;
	static constexpr int NumAudioFiles = 0;
	static constexpr int NumFilters = 0;
	static constexpr int NumDisplayBuffers = 0;
	
	static constexpr int CHANNELS = 8;
	aspik::BitCrusher bitcrusher [CHANNELS][NV];
	aspik::BitCrusherParameters parameters[NV];
	double sampleRate = 44100.0;

	enum Parameters
	{
		BitDepth = 0
	};

	// Scriptnode Callbacks ------------------------------------------------------------------------
	
	void prepare(PrepareSpecs specs)
	{
		sampleRate = specs.sampleRate;
		const int numChannels = specs.numChannels;
		for (int v = 0; v < NV; v++)
		{
			for (int c = 0; c < jmin(numChannels, CHANNELS); c++)
			{
				bitcrusher[c][v].reset(specs.sampleRate);
			}
			updateParameters(v);
		}
	}
	
	// Resst all voices
	void reset()
	{
		for (int v = 0; v < NV; v++)
		{
			for (int c = 0; c < CHANNELS; c++)
			{
				bitcrusher[c][v].reset(sampleRate);
			}
		}
	}
	
	void handleHiseEvent(HiseEvent& e)
	{
		
	}
	
	template <typename T> void process(T& data)
	{
		auto numSamples = data.getNumSamples();
		auto numChannels = data.getNumChannels();

		for (int c = 0; c < jmin(numChannels, CHANNELS); c++)
		{
			for (int s = 0; s < numSamples; s++)
			{
				int voiceIndex = 0;
				if constexpr (NV > 1)
				{
					voiceIndex = 0; 
				}

				auto input = static_cast<double>(data[c][s]);
				auto processed = bitcrusher[c][voiceIndex].processAudioSample(input);
				data[c][s] = static_cast<float>(processed);
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

		for (int channel = 0; channel < jmin((int)data.size(), CHANNELS); channel++)
		{
			data[channel] = static_cast<float>(
				bitcrusher[channel][voiceIndex].processAudioSample(static_cast<double>(data[channel]))
				);
		}
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
		if (P == BitDepth)
		{
			for (int voice = 0; voice < NV; voice++)
			{
				parameters[voice].quantizedBitDepth = v;
				updateParameters(voice);
			}
		}
	}
	
	void createParameters(ParameterDataList& data)
	{
		{
			parameter::data p("Bitcrush", { 1.0, 24.0 });
			registerCallback<0>(p);
			p.setDefaultValue(4.0);
			data.add(std::move(p));
		}
	}

	private:
		void updateParameters(int voice)
		{
			for (int c = 0; c < CHANNELS; c++)
			{
				bitcrusher[c][voice].setParameters(parameters[voice]);
			}
		}
	};  
} 



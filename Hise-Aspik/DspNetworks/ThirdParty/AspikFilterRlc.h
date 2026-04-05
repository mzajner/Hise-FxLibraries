// ==================================| ASPIK RLC Filter |==================================

// The WDFIdealRLCLPF object implements an ideal RLC LPF using the WDF library.

#pragma once
#include <JuceHeader.h>
#include "src/Aspik/aspik.h"

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;
using namespace aspik;

// ==========================| ASPIK WDF Filter Node |==========================

template <int NV> struct AspikFilterRlc
{
	// Metadata Definitions ------------------------------------------------------------------------
	
	SNEX_NODE(AspikFilterRlc);
	
	struct MetadataClass
	{
		SN_NODE_ID("AspikFilterRlc");
	};
	
	// set to true if you want this node to have a modulation dragger
	static constexpr bool isModNode() { return false; };
	static constexpr bool isPolyphonic() { return NV > 1; };
	static constexpr bool hasTail() { return false; };
	static constexpr bool isSuspendedOnSilence() { return true; };
	static constexpr int getFixChannelAmount() { return 2; };
	
	// Define the amount and types of external data slots you want to use
	static constexpr int NumTables = 0;
	static constexpr int NumSliderPacks = 0;
	static constexpr int NumAudioFiles = 0;
	static constexpr int NumFilters = 0;
	static constexpr int NumDisplayBuffers = 0;
	
	// ASPIK WDF Filter Objects - one for each filter type
	aspik::WDFIdealRLCLPF rlcLPF;
	aspik::WDFIdealRLCHPF rlcHPF;
	aspik::WDFIdealRLCBPF rlcBPF;
	aspik::WDFIdealRLCBSF rlcBSF;

	// Current filter type selection
	int rlcType = 0; // 0=LPF, 1=HPF, 2=BPF, 3=BSF

	// Parameters
	double frequency = 1000.0;
	double q = 0.707;
	double boostCut = 0.0;
	bool frequencyWarping = true;
	double sampleRate = 44100.0; 

	// Scriptnode Callbacks ------------------------------------------------------------------------
	
	void prepare(PrepareSpecs specs)
	{
		sampleRate = specs.sampleRate;
		updateFilterParameters();
		reset();
	}
	
	void reset()
	{
		// Reset all filter objects
		rlcLPF.reset(sampleRate);
		rlcHPF.reset(sampleRate);
		rlcBPF.reset(sampleRate);
		rlcBSF.reset(sampleRate);
	}
	
	void handleHiseEvent(HiseEvent& e)
	{
		
	}
	
	void updateFilterParameters()
	{
		// Update the filter parameters based on the current settings
		aspik::WDFParameters params;
		params.fc = frequency;
		params.Q = q;
		params.boostCut_dB = boostCut;
		params.frequencyWarping = frequencyWarping;

		// Update all filters with same parameters
		rlcLPF.setParameters(params);
		rlcHPF.setParameters(params);
		rlcBPF.setParameters(params);
		rlcBSF.setParameters(params);

	}

	template <typename T> void process(T& data)
	{
		
		static constexpr int NumChannels = getFixChannelAmount();
		// Cast the dynamic channel data to a fixed channel amount
		auto& fixData = data.template as<ProcessData<NumChannels>>();
		
		// Create a FrameProcessor object
		auto fd = fixData.toFrameData();
		
		while(fd.next())
		{
			// Forward to frame processing
			processFrame(fd.toSpan());
		}
		
	}
	
	template <typename T> void processFrame(T& data)
	{
		float inputL = data[0];
		float inputR = data[1];
		float outputL, outputR;

		switch (rlcType)
		{
		case 0: // Low-pass filter
			outputL = rlcLPF.processAudioSample(static_cast<double>(inputL));
			outputR = rlcLPF.processAudioSample(static_cast<double>(inputR));
			break;
		case 1: // High-pass filter
			outputL = rlcHPF.processAudioSample(static_cast<double>(inputL));
			outputR = rlcHPF.processAudioSample(static_cast<double>(inputR));
			break;
		case 2: // Band-pass filter
			outputL = rlcBPF.processAudioSample(static_cast<double>(inputL));
			outputR = rlcBPF.processAudioSample(static_cast<double>(inputR));
			break;
		case 3: // Band-stop filter
			outputL = rlcBSF.processAudioSample(static_cast<double>(inputL));
			outputR = rlcBSF.processAudioSample(static_cast<double>(inputR));
			break;
		default:
			outputL = inputL; // No filtering
			outputR = inputR;
			break;
		}

		data[0] = outputL;
		data[1] = outputR;	
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
		if (P == 0)
		{
			double newFreq = jlimit(20.0, 20000.0, v);
			if (frequency != newFreq)
			{
				frequency = newFreq;
				updateFilterParameters();
			}
		}
		else if (P == 1)
		{
			double newQ = jlimit(0.1, 30.0, v);
			if (q != newQ)
			{
				q = newQ;
				updateFilterParameters();
			}
		}
		else if (P == 2)
		{
			double newBoostCut = jlimit(-24.0, 24.0, v);
			if (boostCut != newBoostCut)
			{
				boostCut = newBoostCut;
				updateFilterParameters();
			}
		}
		else if (P == 3)
		{
			frequencyWarping = v > 0.5;
			updateFilterParameters();
		}
		else if (P == 4) // Filter Type
		{
			int newType = jlimit(0, 3, (int)v);
			if (rlcType != newType)
			{
				rlcType = newType;
				updateFilterParameters();
			}
		}
		
	}
	
	void createParameters(ParameterDataList& data)
	{
		{
			parameter::data p("Frequency (Hz)", { 20.0, 20000 });
			registerCallback<0>(p);
			p.setDefaultValue(1000);
			p.setSkewForCentre(1000.0); 
			data.add(std::move(p));
		}
		{
			parameter::data p("Q", { 0.707, 20.0 });
			registerCallback<1>(p);
			p.setDefaultValue(0.707);
			p.setSkewForCentre(1.0);
			data.add(std::move(p));
		}
		{
			parameter::data p("Boost/Cut (dB)", { -24.0, 24.0 });
			registerCallback<2>(p);
			p.setDefaultValue(0.0);
			p.setSkewForCentre(0.0);
			data.add(std::move(p));
		}
		{
			parameter::data p("Freq. Warping", { 0.0, 1.0, 1.0 });
			registerCallback<3>(p);
			p.setDefaultValue(1.0);
			data.add(std::move(p));
		}
		{
			parameter::data p("Filter Type", { 0.0, 3.0, 1.0 });
			registerCallback<4>(p);
			p.setDefaultValue(0.0);

			StringArray rlcTypes;
			rlcTypes.add("LPF");
			rlcTypes.add("BPF"); 
			rlcTypes.add("BPF");
			rlcTypes.add("BSF");

			p.setParameterValueNames(rlcTypes);
			data.add(std::move(p));
		}
	}
};
}



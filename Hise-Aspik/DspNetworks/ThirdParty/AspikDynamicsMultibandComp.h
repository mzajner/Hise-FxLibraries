/*
AspikeDynamicsMultibandComp - Two-Band Dynamics Processor
Uses Linkwitz-Riley crossover to split signal into low/high bands for independent processing
Based on Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed." Chapter 18.5
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

	template <int NV> struct AspikDynamicsMultibandComp : public data::base
	{
		SNEX_NODE(AspikDynamicsMultibandComp);

		struct MetadataClass
		{
			SN_NODE_ID("AspikDynamicsMultibandComp");
		};

		static constexpr bool isModNode() { return true; };
		static constexpr bool isPolyphonic() { return NV > 1; };
		static constexpr bool hasTail() { return true; };
		static constexpr bool isSuspendedOnSilence() { return true; };
		static constexpr int getFixChannelAmount() { return 2; };

		static constexpr int NumTables = 0;
		static constexpr int NumSliderPacks = 0;
		static constexpr int NumAudioFiles = 0;
		static constexpr int NumFilters = 0;
		static constexpr int NumDisplayBuffers = 0;

		enum Parameters
		{
			CrossoverFreq,
			LowAlgorithm,
			LowThreshold,
			LowRatio,
			LowAttack,
			LowRelease,
			HighAlgorithm,
			HighThreshold,
			HighRatio,
			HighAttack,
			HighRelease,
			OutputGain
		};

		// ASPIK Objects
		LRFilterBank filterBank[2][NV];
		DynamicsProcessor lowProcessors[2][NV];
		DynamicsProcessor highProcessors[2][NV];
		LRFilterBankParameters filterParams[NV];
		DynamicsProcessorParameters lowParams[NV];
		DynamicsProcessorParameters highParams[NV];

		void prepare(PrepareSpecs specs)
		{
			for (int v = 0; v < NV; v++)
			{
				filterBank[0][v].reset(specs.sampleRate);
				filterBank[1][v].reset(specs.sampleRate);
				lowProcessors[0][v].reset(specs.sampleRate);
				lowProcessors[1][v].reset(specs.sampleRate);
				highProcessors[0][v].reset(specs.sampleRate);
				highProcessors[1][v].reset(specs.sampleRate);
				updateParameters(v);
			}
		}

		void reset()
		{
			for (int v = 0; v < NV; v++)
			{
				filterBank[0][v].reset(44100.0);
				filterBank[1][v].reset(44100.0);
				lowProcessors[0][v].reset(44100.0);
				lowProcessors[1][v].reset(44100.0);
				highProcessors[0][v].reset(44100.0);
				highProcessors[1][v].reset(44100.0);
			}
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
			int voiceIndex = 0;
			if constexpr (NV > 1)
			{
				voiceIndex = data.getVoiceIndex();
			}

			// Split into low/high bands
			FilterBankOutput leftBands = filterBank[0][voiceIndex].processFilterBank(static_cast<double>(data[0]));
			FilterBankOutput rightBands = filterBank[1][voiceIndex].processFilterBank(static_cast<double>(data[1]));

			// Process low band through low dynamics processor
			double lowL = lowProcessors[0][voiceIndex].processAudioSample(leftBands.LFOut);
			double lowR = lowProcessors[1][voiceIndex].processAudioSample(rightBands.LFOut);

			// Process high band through high dynamics processor
			double highL = highProcessors[0][voiceIndex].processAudioSample(leftBands.HFOut);
			double highR = highProcessors[1][voiceIndex].processAudioSample(rightBands.HFOut);

			// Recombine bands
			data[0] = static_cast<float>(lowL + highL);
			data[1] = static_cast<float>(lowR + highR);
		}

		int handleModulation(double& value)
		{
			auto lowL = lowProcessors[0][0].getParameters();
			auto lowR = lowProcessors[1][0].getParameters();
			auto highL = highProcessors[0][0].getParameters();
			auto highR = highProcessors[1][0].getParameters();

			double avgGR = (lowL.gainReduction + lowR.gainReduction +
				highL.gainReduction + highR.gainReduction) * 0.25;
			value = 1.0 - avgGR;
			return 2;
		}

		void setExternalData(const ExternalData& data, int index)
		{
		}

		template <int P> void setParameter(double v)
		{
			if (P == CrossoverFreq)
			{
				for (int i = 0; i < NV; i++)
				{
					filterParams[i].splitFrequency = v;
					filterBank[0][i].setParameters(filterParams[i]);
					filterBank[1][i].setParameters(filterParams[i]);
				}
			}
			else if (P == LowAlgorithm)
			{
				setAlgorithmType(v, lowParams, lowProcessors);
			}
			else if (P == LowThreshold)
			{
				for (int i = 0; i < NV; i++)
				{
					lowParams[i].threshold_dB = v;
					updateLowProcessors(i);
				}
			}
			else if (P == LowRatio)
			{
				for (int i = 0; i < NV; i++)
				{
					lowParams[i].ratio = v;
					updateLowProcessors(i);
				}
			}
			else if (P == LowAttack)
			{
				for (int i = 0; i < NV; i++)
				{
					lowParams[i].attackTime_mSec = v;
					updateLowProcessors(i);
				}
			}
			else if (P == LowRelease)
			{
				for (int i = 0; i < NV; i++)
				{
					lowParams[i].releaseTime_mSec = v;
					updateLowProcessors(i);
				}
			}
			else if (P == HighAlgorithm)
			{
				setAlgorithmType(v, highParams, highProcessors);
			}
			else if (P == HighThreshold)
			{
				for (int i = 0; i < NV; i++)
				{
					highParams[i].threshold_dB = v;
					updateHighProcessors(i);
				}
			}
			else if (P == HighRatio)
			{
				for (int i = 0; i < NV; i++)
				{
					highParams[i].ratio = v;
					updateHighProcessors(i);
				}
			}
			else if (P == HighAttack)
			{
				for (int i = 0; i < NV; i++)
				{
					highParams[i].attackTime_mSec = v;
					updateHighProcessors(i);
				}
			}
			else if (P == HighRelease)
			{
				for (int i = 0; i < NV; i++)
				{
					highParams[i].releaseTime_mSec = v;
					updateHighProcessors(i);
				}
			}
			else if (P == OutputGain)
			{
				for (int i = 0; i < NV; i++)
				{
					lowParams[i].outputGain_dB = v;
					highParams[i].outputGain_dB = v;
					updateLowProcessors(i);
					updateHighProcessors(i);
				}
			}
		}

		void createParameters(ParameterDataList& data)
		{
			{
				parameter::data p("CrossoverFreq", { 200.0, 5000.0 });
				registerCallback<CrossoverFreq>(p);
				p.setDefaultValue(1000.0);
				p.setSkewForCentre(1000.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("LowAlgorithm", { 0.0, 3.0, 1.0 });
				registerCallback<LowAlgorithm>(p);
				p.setDefaultValue(0.0);

				StringArray algorithms;
				algorithms.add("Compressor");
				algorithms.add("Limiter");
				algorithms.add("Expander");
				algorithms.add("Gate");

				p.setParameterValueNames(algorithms);
				data.add(std::move(p));
			}
			{
				parameter::data p("LowThreshold", { -40.0, 0.0 });
				registerCallback<LowThreshold>(p);
				p.setDefaultValue(-15.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("LowRatio", { 1.0, 50.0 });
				registerCallback<LowRatio>(p);
				p.setDefaultValue(3.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("LowAttack", { 1.0, 100.0 });
				registerCallback<LowAttack>(p);
				p.setDefaultValue(10.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("LowRelease", { 1.0, 5000.0 });
				registerCallback<LowRelease>(p);
				p.setDefaultValue(800.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("HighAlgorithm", { 0.0, 3.0, 1.0 });
				registerCallback<HighAlgorithm>(p);
				p.setDefaultValue(0.0);

				StringArray algorithms;
				algorithms.add("Compressor");
				algorithms.add("Limiter");
				algorithms.add("Expander");
				algorithms.add("Gate");

				p.setParameterValueNames(algorithms);
				data.add(std::move(p));
			}
			{
				parameter::data p("HighThreshold", { -40.0, 0.0 });
				registerCallback<HighThreshold>(p);
				p.setDefaultValue(-10.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("HighRatio", { 1.0, 50.0 });
				registerCallback<HighRatio>(p);
				p.setDefaultValue(4.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("HighAttack", { 1.0, 100.0 });
				registerCallback<HighAttack>(p);
				p.setDefaultValue(3.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("HighRelease", { 1.0, 5000.0 });
				registerCallback<HighRelease>(p);
				p.setDefaultValue(300.0);
				data.add(std::move(p));
			}
			{
				parameter::data p("OutputGain", { -20.0, 20.0 });
				registerCallback<OutputGain>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}
		}

	private:
		void setAlgorithmType(double v, DynamicsProcessorParameters params[], DynamicsProcessor processors[][NV])
		{
			int algorithm = static_cast<int>(v);
			for (int i = 0; i < NV; i++)
			{
				switch (algorithm)
				{
				case 0:
					params[i].calculation = dynamicsProcessorType::kCompressor;
					params[i].hardLimitGate = false;
					break;
				case 1:
					params[i].calculation = dynamicsProcessorType::kCompressor;
					params[i].hardLimitGate = true;
					break;
				case 2:
					params[i].calculation = dynamicsProcessorType::kDownwardExpander;
					params[i].hardLimitGate = false;
					break;
				case 3:
					params[i].calculation = dynamicsProcessorType::kDownwardExpander;
					params[i].hardLimitGate = true;
					break;
				}
				processors[0][i].setParameters(params[i]);
				processors[1][i].setParameters(params[i]);
			}
		}

		void updateParameters(int voiceIndex)
		{
			filterParams[voiceIndex].splitFrequency = 1000.0;
			filterBank[0][voiceIndex].setParameters(filterParams[voiceIndex]);
			filterBank[1][voiceIndex].setParameters(filterParams[voiceIndex]);

			lowParams[voiceIndex].enableSidechain = false;
			lowParams[voiceIndex].softKnee = true;
			highParams[voiceIndex].enableSidechain = false;
			highParams[voiceIndex].softKnee = true;

			updateLowProcessors(voiceIndex);
			updateHighProcessors(voiceIndex);
		}

		void updateLowProcessors(int voiceIndex)
		{
			lowProcessors[0][voiceIndex].setParameters(lowParams[voiceIndex]);
			lowProcessors[1][voiceIndex].setParameters(lowParams[voiceIndex]);
		}

		void updateHighProcessors(int voiceIndex)
		{
			highProcessors[0][voiceIndex].setParameters(highParams[voiceIndex]);
			highProcessors[1][voiceIndex].setParameters(highParams[voiceIndex]);
		}
	};
}

// ==================================| ASPIK TriodeClassA Waveshaper |==================================
/*
TriodeClassA - Single Tube Stage Waveshaper
Based on Will Pirkle's "Designing Audio Effects Plugins in C++ 2nd Ed." Chapter 19.12
Implements a single Class-A triode stage with:
- Selectable waveshaper models (Soft Clip, ArcTan, Fuzz Asymmetric)
- Output high-pass filter (simulates DC blocking capacitor)
- Low shelf filter (simulates cathode bypass cap effect)
- Output gain control (simulates resistor voltage divider)
*/

#pragma once
#include <JuceHeader.h>
#include "src/Aspik/aspik.h"
#include "src/Aspik/homework.h"

namespace project
{
	using namespace juce;
	using namespace hise;
	using namespace scriptnode;

	template <int NV> struct AspikWaveshaperTriode : public data::base
	{
		// Metadata Definitions ------------------------------------------------------------------------

		SNEX_NODE(AspikWaveshaperTriode);

		struct MetadataClass
		{
			SN_NODE_ID("AspikWaveshaperTriode");
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

		// ASPIK Objects
		aspik::TriodeClassA triodes[2][NV];  // L/R channels per voice
		aspik::TriodeClassAParameters parameters[NV];
		double sampleRate = 44100.0;

		// Parameters
		enum Parameters
		{
			Waveshaper = 0,
			Saturation,
			Asymmetry,
			OutputGain,
			InvertOutput,
			EnableHPF,
			EnableLSF,
			HPFCutoff,
			LSFShelf,
			LSFBoostCut
		};

		// Scriptnode Callbacks ------------------------------------------------------------------------

		void prepare(PrepareSpecs specs)
		{
			sampleRate = specs.sampleRate;

			for (int v = 0; v < NV; v++)
			{
				triodes[0][v].reset(specs.sampleRate);
				triodes[1][v].reset(specs.sampleRate);
				updateParameters(v);
			}
		}

		void reset()
		{
			for (int v = 0; v < NV; v++)
			{
				triodes[0][v].reset(sampleRate);
				triodes[1][v].reset(sampleRate);
			}
		}

		void handleHiseEvent(HiseEvent& e)
		{
			// No MIDI processing needed
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

			// Process L/R channels through triode waveshaper
			data[0] = static_cast<float>(
				triodes[0][voiceIndex].processAudioSample(static_cast<double>(data[0]))
				);

			if (getFixChannelAmount() > 1)
			{
				data[1] = static_cast<float>(
					triodes[1][voiceIndex].processAudioSample(static_cast<double>(data[1]))
					);
			}
		}

		int handleModulation(double& value)
		{
			return 0;
		}

		void setExternalData(const ExternalData& data, int index)
		{
			// No external data needed
		}

		// Parameter Functions -------------------------------------------------------------------------

		template <int P> void setParameter(double v)
		{
			if constexpr (P == Waveshaper)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					// Map to distortionModel enum: 0=SoftClip, 1=ArcTan, 2=FuzzAsym
					if (v < 0.5)
						parameters[voice].waveshaper = aspik::distortionModel::kSoftClip;
					else if (v < 1.5)
						parameters[voice].waveshaper = aspik::distortionModel::kArcTan;
					else
						parameters[voice].waveshaper = aspik::distortionModel::kFuzzAsym;
					updateParameters(voice);
				}
			}
			else if constexpr (P == Saturation)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].saturation = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == Asymmetry)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].asymmetry = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == OutputGain)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].outputGain = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == InvertOutput)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].invertOutput = v >= 0.5;
					updateParameters(voice);
				}
			}
			else if constexpr (P == EnableHPF)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].enableHPF = v >= 0.5;
					updateParameters(voice);
				}
			}
			else if constexpr (P == EnableLSF)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].enableLSF = v >= 0.5;
					updateParameters(voice);
				}
			}
			else if constexpr (P == HPFCutoff)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].hpf_Fc = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == LSFShelf)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].lsf_Fshelf = v;
					updateParameters(voice);
				}
			}
			else if constexpr (P == LSFBoostCut)
			{
				for (int voice = 0; voice < NV; voice++)
				{
					parameters[voice].lsf_BoostCut_dB = v;
					updateParameters(voice);
				}
			}
		}

		void createParameters(ParameterDataList& data)
		{
			{
				parameter::data p("Waveshaper", { 0.0, 2.0, 1.0 });
				registerCallback<Waveshaper>(p);
				p.setDefaultValue(0.0);

				StringArray waveshapers;
				waveshapers.add("Soft Clip");
				waveshapers.add("ArcTan");
				waveshapers.add("Fuzz Asym");

				p.setParameterValueNames(waveshapers);
				data.add(std::move(p));
			}

			{
				parameter::data p("Saturation", { 0.1, 10.0 });
				registerCallback<Saturation>(p);
				p.setDefaultValue(1.0);
				p.setSkewForCentre(2.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Asymmetry", { -1.0, 1.0 });
				registerCallback<Asymmetry>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Output Gain", { 0.1, 3.0 });
				registerCallback<OutputGain>(p);
				p.setDefaultValue(1.0);
				p.setSkewForCentre(1.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Invert Output", { 0.0, 1.0, 1.0 });
				registerCallback<InvertOutput>(p);
				p.setDefaultValue(1.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Enable HPF", { 0.0, 1.0, 1.0 });
				registerCallback<EnableHPF>(p);
				p.setDefaultValue(1.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Enable LSF", { 0.0, 1.0, 1.0 });
				registerCallback<EnableLSF>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("HPF Cutoff", { 1.0, 100.0 });
				registerCallback<HPFCutoff>(p);
				p.setDefaultValue(1.0);
				p.setSkewForCentre(10.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("LSF Shelf", { 20.0, 200.0 });
				registerCallback<LSFShelf>(p);
				p.setDefaultValue(80.0);
				p.setSkewForCentre(80.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("LSF Boost/Cut", { -12.0, 12.0 });
				registerCallback<LSFBoostCut>(p);
				p.setDefaultValue(0.0);
				data.add(std::move(p));
			}
		}

	private:
		void updateParameters(int voice)
		{
			triodes[0][voice].setParameters(parameters[voice]);
			triodes[1][voice].setParameters(parameters[voice]);
		}
	};
}

/*
==========================| ASPIK Modulated Filter |==========================
Envelope-following filter that tracks input signal amplitude
- Filter cutoff follows input envelope above adjustable threshold
- Configurable sensitivity for modulation intensity
- Attack/release controls for envelope response
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

	template <int NV> struct AspikModFilter : public data::base
	{
		SNEX_NODE(AspikModFilter);

		struct MetadataClass
		{
			SN_NODE_ID("AspikModFilter");
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
		aspik::EnvelopeFollower leftEnvFollower;
		aspik::EnvelopeFollower rightEnvFollower;

		// Parameters
		double filterFc = 1000.0;
		double filterQ = 0.707;
		double attackTime = 1.0;
		double releaseTime = 100.0;
		double threshold = -12.0;
		double sensitivity = 1.0;

		// Scriptnode Callbacks ------------------------------------------------------------------------

		void prepare(PrepareSpecs specs)
		{
			leftEnvFollower.reset(specs.sampleRate);
			rightEnvFollower.reset(specs.sampleRate);
			updateFilterParameters();
		}

		void reset()
		{
			leftEnvFollower.reset(44100.0);
			rightEnvFollower.reset(44100.0);
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
			double leftInput = data[0];
			double rightInput = data[1];

			double leftOutput = leftEnvFollower.processAudioSample(leftInput);
			double rightOutput = rightEnvFollower.processAudioSample(rightInput);

			data[0] = static_cast<float>(leftOutput);
			data[1] = static_cast<float>(rightOutput);
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

			if (P == 0)
			{
				double newFc = jlimit(20.0, 20000.0, v);
				if (filterFc != newFc)
				{
					filterFc = newFc;
					needsUpdate = true;
				}
			}
			else if (P == 1)
			{
				double newQ = jlimit(0.1, 30.0, v);
				if (filterQ != newQ)
				{
					filterQ = newQ;
					needsUpdate = true;
				}
			}
			else if (P == 2)
			{
				double newAttack = jlimit(0.1, 100.0, v);
				if (attackTime != newAttack)
				{
					attackTime = newAttack;
					needsUpdate = true;
				}
			}
			else if (P == 3)
			{
				double newRelease = jlimit(1.0, 1000.0, v);
				if (releaseTime != newRelease)
				{
					releaseTime = newRelease;
					needsUpdate = true;
				}
			}
			else if (P == 4)
			{
				double newThreshold = jlimit(-60.0, 0.0, v);
				if (threshold != newThreshold)
				{
					threshold = newThreshold;
					needsUpdate = true;
				}
			}
			else if (P == 5)
			{
				double newSensitivity = jlimit(0.1, 10.0, v);
				if (sensitivity != newSensitivity)
				{
					sensitivity = newSensitivity;
					needsUpdate = true;
				}
			}

			if (needsUpdate)
			{
				updateFilterParameters();
			}
		}

		void createParameters(ParameterDataList& data)
		{
			{
				parameter::data p("Frequency", { 20.0, 20000.0 });
				registerCallback<0>(p);
				p.setDefaultValue(1000.0);
				p.setSkewForCentre(1000.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Q", { 0.1, 30.0 });
				registerCallback<1>(p);
				p.setDefaultValue(0.707);
				p.setSkewForCentre(1.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Attack", { 0.1, 100.0 });
				registerCallback<2>(p);
				p.setDefaultValue(1.0);
				p.setSkewForCentre(10.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Release", { 1.0, 1000.0 });
				registerCallback<3>(p);
				p.setDefaultValue(100.0);
				p.setSkewForCentre(100.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Threshold", { -60.0, 0.0 });
				registerCallback<4>(p);
				p.setDefaultValue(-12.0);
				data.add(std::move(p));
			}

			{
				parameter::data p("Sensitivity", { 0.1, 10.0 });
				registerCallback<5>(p);
				p.setDefaultValue(1.0);
				p.setSkewForCentre(1.0);
				data.add(std::move(p));
			}
		}

	private:
		void updateFilterParameters()
		{
			aspik::EnvelopeFollowerParameters params;
			params.fc = filterFc;
			params.Q = filterQ;
			params.attackTime_mSec = attackTime;
			params.releaseTime_mSec = releaseTime;
			params.threshold_dB = threshold;
			params.sensitivity = sensitivity;

			leftEnvFollower.setParameters(params);
			rightEnvFollower.setParameters(params);
		}
	};

}

/* ------------------------------------------------------------
name: "Compressor1176"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _Compressor1176 -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___Compressor1176_H__
#define  ___Compressor1176_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _Compressor1176
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif


struct _Compressor1176 final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	float fRec2[2];
	float fConst3;
	FAUSTFLOAT fHslider1;
	float fRec3[2];
	float fRec1[2];
	FAUSTFLOAT fHslider2;
	float fRec4[2];
	FAUSTFLOAT fHslider3;
	float fRec5[2];
	float fRec0[2];
	
	_Compressor1176() {
	}
	
	_Compressor1176(const _Compressor1176&) = default;
	
	virtual ~_Compressor1176() = default;
	
	_Compressor1176& operator=(const _Compressor1176&) = default;
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/amp_follower_ar:author", "Jonatan Liljedahl, revised by Romain Michon");
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.3.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _Compressor1176 -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("compressors.lib/compression_gain_mono:author", "Julius O. Smith III");
		m->declare("compressors.lib/compression_gain_mono:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compression_gain_mono:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/compressor_stereo:author", "Julius O. Smith III");
		m->declare("compressors.lib/compressor_stereo:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compressor_stereo:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/name", "Faust Compressor Effect Library");
		m->declare("compressors.lib/version", "1.6.0");
		m->declare("filename", "Compressor1176.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "Compressor1176");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/onePoleSwitching:author", "Jonatan Liljedahl, revised by Dario Sanfilippo");
		m->declare("signals.lib/onePoleSwitching:licence", "STK-4.3");
		m->declare("signals.lib/version", "1.6.0");
	}

	static constexpr int getStaticNumInputs() {
		return 2;
	}
	static constexpr int getStaticNumOutputs() {
		return 2;
	}
	int getNumInputs() {
		return 2;
	}
	int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 1.0f / fConst0;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(0.125f);
		fHslider1 = static_cast<FAUSTFLOAT>(2e-05f);
		fHslider2 = static_cast<FAUSTFLOAT>(-6.0f);
		fHslider3 = static_cast<FAUSTFLOAT>(4.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec2[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec3[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec4[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec0[l5] = 0.0f;
		}
	}
	
	void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	_Compressor1176* clone() {
		return new _Compressor1176(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Compressor1176");
		ui_interface->addHorizontalSlider("attack", &fHslider1, FAUSTFLOAT(2e-05f), FAUSTFLOAT(2e-05f), FAUSTFLOAT(0.08f), FAUSTFLOAT(1e-05f));
		ui_interface->addHorizontalSlider("ratio", &fHslider3, FAUSTFLOAT(4.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(4.0f));
		ui_interface->addHorizontalSlider("release", &fHslider0, FAUSTFLOAT(0.125f), FAUSTFLOAT(0.05f), FAUSTFLOAT(1.1f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("threshold", &fHslider2, FAUSTFLOAT(-6.0f), FAUSTFLOAT(-3e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst1 * std::max<float>(0.05f, std::min<float>(1.1f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst1 * std::max<float>(2e-05f, std::min<float>(0.08f, static_cast<float>(fHslider1)));
		float fSlow2 = fConst1 * std::max<float>(-3e+01f, std::min<float>(0.0f, static_cast<float>(fHslider2)));
		float fSlow3 = fConst1 * std::max<float>(0.0f, std::min<float>(2e+01f, static_cast<float>(fHslider3)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			float fTemp1 = static_cast<float>(input1[i0]);
			float fTemp2 = std::fabs(std::fabs(fTemp0) + std::fabs(fTemp1));
			fRec2[0] = fSlow0 + fConst2 * fRec2[1];
			int iTemp3 = std::fabs(fRec2[0]) < 1.1920929e-07f;
			fRec3[0] = fSlow1 + fConst2 * fRec3[1];
			int iTemp4 = std::fabs(fRec3[0]) < 1.1920929e-07f;
			float fTemp5 = ((fTemp2 > fRec1[1]) ? ((iTemp4) ? 0.0f : std::exp(-(fConst3 / ((iTemp4) ? 1.0f : fRec3[0])))) : ((iTemp3) ? 0.0f : std::exp(-(fConst3 / ((iTemp3) ? 1.0f : fRec2[0])))));
			fRec1[0] = fTemp2 * (1.0f - fTemp5) + fRec1[1] * fTemp5;
			fRec4[0] = fSlow2 + fConst2 * fRec4[1];
			float fTemp6 = 0.5f * fRec3[0];
			int iTemp7 = std::fabs(fTemp6) < 1.1920929e-07f;
			float fTemp8 = ((iTemp7) ? 0.0f : std::exp(-(fConst3 / ((iTemp7) ? 1.0f : fTemp6))));
			fRec5[0] = fSlow3 + fConst2 * fRec5[1];
			fRec0[0] = std::max<float>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, fRec1[0])) - fRec4[0], 0.0f) * (1.0f - fTemp8) * (1.0f / std::max<float>(1.1920929e-07f, fRec5[0]) + -1.0f) + fTemp8 * fRec0[1];
			float fTemp9 = std::pow(1e+01f, 0.05f * fRec0[0]);
			output0[i0] = static_cast<FAUSTFLOAT>(fTemp0 * fTemp9);
			output1[i0] = static_cast<FAUSTFLOAT>(fTemp1 * fTemp9);
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec1[1] = fRec1[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec0[1] = fRec0[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "Compressor1176.dsp"
	#define FAUST_CLASS_NAME "_Compressor1176"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _Compressor1176 -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 4
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("attack", fHslider1, 2e-05f, 2e-05f, 0.08f, 1e-05f);
	FAUST_ADDHORIZONTALSLIDER("ratio", fHslider3, 4.0f, 0.0f, 2e+01f, 4.0f);
	FAUST_ADDHORIZONTALSLIDER("release", fHslider0, 0.125f, 0.05f, 1.1f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("threshold", fHslider2, -6.0f, -3e+01f, 0.0f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, attack, "attack", fHslider1, 2e-05f, 2e-05f, 0.08f, 1e-05f) \
		p(HORIZONTALSLIDER, ratio, "ratio", fHslider3, 4.0f, 0.0f, 2e+01f, 4.0f) \
		p(HORIZONTALSLIDER, release, "release", fHslider0, 0.125f, 0.05f, 1.1f, 0.01f) \
		p(HORIZONTALSLIDER, threshold, "threshold", fHslider2, -6.0f, -3e+01f, 0.0f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

/* ------------------------------------------------------------
author: "Christopher Arndt"
license: "MIT-style STK-4.3 license"
name: "Korg35LPF"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _korg35lpf -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___korg35lpf_H__
#define  ___korg35lpf_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _korg35lpf
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


struct _korg35lpf final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	float fConst3;
	float fRec4[2];
	FAUSTFLOAT fHslider1;
	float fRec5[2];
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	float fConst4;
	float fConst5;
	float fRec9[2];
	float fRec10[2];
	float fRec11[2];
	float fConst6;
	float fConst7;
	float fRec7[2];
	float fRec6[2];
	
	_korg35lpf() {
	}
	
	_korg35lpf(const _korg35lpf&) = default;
	
	virtual ~_korg35lpf() = default;
	
	_korg35lpf& operator=(const _korg35lpf&) = default;
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/amp_follower_ar:author", "Jonatan Liljedahl, revised by Romain Michon");
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.3.0");
		m->declare("author", "Christopher Arndt");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _korg35lpf -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("compressors.lib/compression_gain_mono:author", "Julius O. Smith III");
		m->declare("compressors.lib/compression_gain_mono:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compression_gain_mono:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/compressor_stereo:author", "Julius O. Smith III");
		m->declare("compressors.lib/compressor_stereo:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compressor_stereo:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/limiter_1176_R4_stereo:author", "Julius O. Smith III");
		m->declare("compressors.lib/limiter_1176_R4_stereo:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/limiter_1176_R4_stereo:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/name", "Faust Compressor Effect Library");
		m->declare("compressors.lib/version", "1.6.0");
		m->declare("description", "FAUST Korg 35 24 dB LPF");
		m->declare("filename", "korg35lpf.dsp");
		m->declare("korg35lpf.dsp/korg35LPF:author", "Eric Tarr");
		m->declare("korg35lpf.dsp/korg35LPF:license", "MIT-style STK-4.3 license");
		m->declare("license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "Korg35LPF");
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
		fConst1 = 3.1415927f / fConst0;
		fConst2 = 44.1f / fConst0;
		fConst3 = 1.0f - fConst2;
		fConst4 = std::exp(-(2.5e+03f / fConst0));
		fConst5 = 0.75f * (1.0f - fConst4);
		fConst6 = std::exp(-(2.0f / fConst0));
		fConst7 = std::exp(-(1.25e+03f / fConst0));
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(2e+04f);
		fHslider1 = static_cast<FAUSTFLOAT>(1.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec4[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec5[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec2[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec3[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec9[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec10[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec11[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec7[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec6[l9] = 0.0f;
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
	
	_korg35lpf* clone() {
		return new _korg35lpf(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Korg35LPF");
		ui_interface->declare(&fHslider0, "0", "");
		ui_interface->declare(&fHslider0, "abbrev", "cutoff");
		ui_interface->declare(&fHslider0, "scale", "log");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "symbol", "cutoff");
		ui_interface->declare(&fHslider0, "unit", "hz");
		ui_interface->addHorizontalSlider("Cutoff frequency", &fHslider0, FAUSTFLOAT(2e+04f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "abbrev", "q");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "symbol", "q");
		ui_interface->addHorizontalSlider("Q", &fHslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.5f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst2 * std::max<float>(2e+01f, std::min<float>(2e+04f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst2 * std::max<float>(0.5f, std::min<float>(1e+01f, static_cast<float>(fHslider1)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec4[0] = fSlow0 + fConst3 * fRec4[1];
			float fTemp0 = std::tan(fConst1 * fRec4[0]);
			float fTemp1 = (static_cast<float>(input0[i0]) - fRec3[1]) * fTemp0;
			fRec5[0] = fSlow1 + fConst3 * fRec5[1];
			float fTemp2 = fRec5[0] + -0.707f;
			float fTemp3 = fTemp0 + 1.0f;
			float fTemp4 = 1.0f - fTemp0 / fTemp3;
			float fTemp5 = 1.0f - 0.21521576f * (fTemp0 * fTemp2 * fTemp4 / fTemp3);
			float fTemp6 = fTemp0 * ((fRec3[1] + (fTemp1 + 0.21521576f * fRec1[1] * fTemp2 * fTemp4 - fRec2[1]) / fTemp3) / fTemp5 - fRec1[1]) / fTemp3;
			float fTemp7 = fRec1[1] + fTemp6;
			float fRec0 = fTemp7;
			fRec1[0] = fRec1[1] + 2.0f * fTemp6;
			fRec2[0] = fRec2[1] + 2.0f * (fTemp0 * (0.21521576f * fTemp2 * fTemp7 - fRec2[1]) / fTemp3);
			fRec3[0] = fRec3[1] + 2.0f * (fTemp1 / fTemp3);
			float fTemp8 = fTemp0 * (static_cast<float>(input1[i0]) - fRec11[1]);
			float fTemp9 = fTemp0 * ((fRec11[1] + (fTemp8 + 0.21521576f * fTemp2 * fTemp4 * fRec9[1] - fRec10[1]) / fTemp3) / fTemp5 - fRec9[1]) / fTemp3;
			float fTemp10 = fRec9[1] + fTemp9;
			float fRec8 = fTemp10;
			fRec9[0] = fRec9[1] + 2.0f * fTemp9;
			fRec10[0] = fRec10[1] + 2.0f * (fTemp0 * (0.21521576f * fTemp2 * fTemp10 - fRec10[1]) / fTemp3);
			fRec11[0] = fRec11[1] + 2.0f * (fTemp8 / fTemp3);
			float fTemp11 = std::fabs(std::fabs(fRec0) + std::fabs(fRec8));
			float fTemp12 = ((fTemp11 > fRec7[1]) ? fConst7 : fConst6);
			fRec7[0] = fTemp11 * (1.0f - fTemp12) + fRec7[1] * fTemp12;
			fRec6[0] = fConst4 * fRec6[1] - fConst5 * std::max<float>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, fRec7[0])) + 6.0f, 0.0f);
			float fTemp13 = std::pow(1e+01f, 0.05f * fRec6[0]);
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0 * fTemp13);
			output1[i0] = static_cast<FAUSTFLOAT>(fRec8 * fTemp13);
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "korg35lpf.dsp"
	#define FAUST_CLASS_NAME "_korg35lpf"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _korg35lpf -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Cutoff frequency", fHslider0, 2e+04f, 2e+01f, 2e+04f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Q", fHslider1, 1.0f, 0.5f, 1e+01f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Cutoff_frequency, "Cutoff frequency", fHslider0, 2e+04f, 2e+01f, 2e+04f, 0.1f) \
		p(HORIZONTALSLIDER, Q, "Q", fHslider1, 1.0f, 0.5f, 1e+01f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

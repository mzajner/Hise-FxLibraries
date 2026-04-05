/* ------------------------------------------------------------
author: "Christopher Arndt"
license: "MIT license"
name: "StereoCrossDelay"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _DelayFaust -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___DelayFaust_H__
#define  ___DelayFaust_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _DelayFaust
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

static float _DelayFaust_faustpower2_f(float value) {
	return value * value;
}

struct _DelayFaust final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	FAUSTFLOAT fHslider1;
	float fConst3;
	float fRec2[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fRec4[3];
	float fRec3[3];
	int IOTA0;
	float fVec0[524288];
	float fConst4;
	float fConst5;
	FAUSTFLOAT fHslider4;
	float fRec9[2];
	float fRec5[2];
	float fRec6[2];
	float fRec7[2];
	float fRec8[2];
	FAUSTFLOAT fHslider5;
	float fRec10[2];
	float fRec12[3];
	float fRec11[3];
	float fVec1[524288];
	FAUSTFLOAT fHslider6;
	float fRec17[2];
	float fRec13[2];
	float fRec14[2];
	float fRec15[2];
	float fRec16[2];
	float fRec0[2];
	float fRec1[2];
	
	_DelayFaust() {
	}
	
	_DelayFaust(const _DelayFaust&) = default;
	
	virtual ~_DelayFaust() = default;
	
	_DelayFaust& operator=(const _DelayFaust&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Christopher Arndt");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _DelayFaust -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.2.0");
		m->declare("description", "A stereo delay with feedback and cross-mixing");
		m->declare("filename", "DelayFaust.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("license", "MIT license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "StereoCrossDelay");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
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
		fConst4 = 2.0f * fConst0;
		fConst5 = 0.0441f / fConst0;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(6e+01f);
		fHslider1 = static_cast<FAUSTFLOAT>(2e+01f);
		fHslider2 = static_cast<FAUSTFLOAT>(1.2e+04f);
		fHslider3 = static_cast<FAUSTFLOAT>(0.1f);
		fHslider4 = static_cast<FAUSTFLOAT>(2.5e+02f);
		fHslider5 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider6 = static_cast<FAUSTFLOAT>(166.7f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec2[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 3; l1 = l1 + 1) {
			fRec4[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 3; l2 = l2 + 1) {
			fRec3[l2] = 0.0f;
		}
		IOTA0 = 0;
		for (int l3 = 0; l3 < 524288; l3 = l3 + 1) {
			fVec0[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec9[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec5[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec6[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec7[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec8[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec10[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec12[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec11[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 524288; l12 = l12 + 1) {
			fVec1[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec17[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec13[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec14[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec15[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec16[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec0[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec1[l19] = 0.0f;
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
	
	_DelayFaust* clone() {
		return new _DelayFaust(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("StereoCrossDelay");
		ui_interface->declare(&fHslider4, "0", "");
		ui_interface->declare(&fHslider4, "symbol", "delay_l");
		ui_interface->declare(&fHslider4, "unit", "ms");
		ui_interface->addHorizontalSlider("Delay Left", &fHslider4, FAUSTFLOAT(2.5e+02f), FAUSTFLOAT(0.0f), FAUSTFLOAT(2e+03f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider6, "1", "");
		ui_interface->declare(&fHslider6, "symbol", "delay_r");
		ui_interface->declare(&fHslider6, "unit", "ms");
		ui_interface->addHorizontalSlider("Delay Right", &fHslider6, FAUSTFLOAT(166.7f), FAUSTFLOAT(0.0f), FAUSTFLOAT(2e+03f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "symbol", "feedback");
		ui_interface->declare(&fHslider1, "unit", "%");
		ui_interface->addHorizontalSlider("Feedback", &fHslider1, FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider2, "3", "");
		ui_interface->declare(&fHslider2, "scale", "log");
		ui_interface->declare(&fHslider2, "symbol", "lp_feedback");
		ui_interface->declare(&fHslider2, "unit", "hz");
		ui_interface->addHorizontalSlider("Feedback Lowpass", &fHslider2, FAUSTFLOAT(1.2e+04f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider0, "4", "");
		ui_interface->declare(&fHslider0, "scale", "log");
		ui_interface->declare(&fHslider0, "symbol", "hp_feedback");
		ui_interface->declare(&fHslider0, "unit", "hz");
		ui_interface->addHorizontalSlider("Feedback Highpass", &fHslider0, FAUSTFLOAT(6e+01f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider3, "5", "");
		ui_interface->declare(&fHslider3, "symbol", "dist_feedback");
		ui_interface->addHorizontalSlider("Distortion", &fHslider3, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.1f), FAUSTFLOAT(5e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider5, "6", "");
		ui_interface->declare(&fHslider5, "symbol", "crossfeed");
		ui_interface->declare(&fHslider5, "unit", "%");
		ui_interface->addHorizontalSlider("Crossmix", &fHslider5, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = std::tan(fConst1 * std::max<float>(2e+01f, std::min<float>(2e+04f, static_cast<float>(fHslider0))));
		float fSlow1 = _DelayFaust_faustpower2_f(fSlow0);
		float fSlow2 = 1.0f / fSlow0;
		float fSlow3 = (fSlow2 + 1.4142135f) / fSlow0 + 1.0f;
		float fSlow4 = 0.01f / (fSlow1 * fSlow3);
		float fSlow5 = fConst2 * std::max<float>(0.0f, std::min<float>(1e+02f, static_cast<float>(fHslider1)));
		float fSlow6 = std::tan(fConst1 * std::max<float>(2e+01f, std::min<float>(2e+04f, static_cast<float>(fHslider2))));
		float fSlow7 = 1.0f / fSlow6;
		float fSlow8 = 1.0f / ((fSlow7 + 1.4142135f) / fSlow6 + 1.0f);
		float fSlow9 = std::max<float>(0.1f, std::min<float>(5e+01f, static_cast<float>(fHslider3)));
		float fSlow10 = 1.0f / std::atan(fSlow9);
		float fSlow11 = (fSlow7 + -1.4142135f) / fSlow6 + 1.0f;
		float fSlow12 = 2.0f * (1.0f - 1.0f / _DelayFaust_faustpower2_f(fSlow6));
		float fSlow13 = 1.0f / fSlow3;
		float fSlow14 = (fSlow2 + -1.4142135f) / fSlow0 + 1.0f;
		float fSlow15 = 2.0f * (1.0f - 1.0f / fSlow1);
		float fSlow16 = fConst5 * std::max<float>(0.0f, std::min<float>(2e+03f, static_cast<float>(fHslider4)));
		float fSlow17 = fConst2 * std::max<float>(0.0f, std::min<float>(1e+02f, static_cast<float>(fHslider5)));
		float fSlow18 = fConst5 * std::max<float>(0.0f, std::min<float>(2e+03f, static_cast<float>(fHslider6)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec2[0] = fSlow5 + fConst3 * fRec2[1];
			fRec4[0] = fSlow10 * std::atan(fSlow9 * fRec0[1]) - fSlow8 * (fSlow11 * fRec4[2] + fSlow12 * fRec4[1]);
			fRec3[0] = fSlow8 * (fRec4[2] + fRec4[0] + 2.0f * fRec4[1]) - fSlow13 * (fSlow14 * fRec3[2] + fSlow15 * fRec3[1]);
			float fTemp0 = static_cast<float>(input0[i0]) + fSlow4 * fRec2[0] * (fRec3[2] + (fRec3[0] - 2.0f * fRec3[1]));
			fVec0[IOTA0 & 524287] = fTemp0;
			fRec9[0] = fSlow16 + fConst3 * fRec9[1];
			float fTemp1 = fConst0 * fRec9[0];
			float fTemp2 = ((fRec5[1] != 0.0f) ? (((fRec6[1] > 0.0f) & (fRec6[1] < 1.0f)) ? fRec5[1] : 0.0f) : (((fRec6[1] == 0.0f) & (fTemp1 != fRec7[1])) ? 0.001953125f : (((fRec6[1] == 1.0f) & (fTemp1 != fRec8[1])) ? -0.001953125f : 0.0f)));
			fRec5[0] = fTemp2;
			fRec6[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec6[1] + fTemp2));
			fRec7[0] = (((fRec6[1] >= 1.0f) & (fRec8[1] != fTemp1)) ? fTemp1 : fRec7[1]);
			fRec8[0] = (((fRec6[1] <= 0.0f) & (fRec7[1] != fTemp1)) ? fTemp1 : fRec8[1]);
			float fTemp3 = fVec0[(IOTA0 - static_cast<int>(std::min<float>(fConst4, std::max<float>(0.0f, fRec7[0])))) & 524287];
			float fTemp4 = fTemp3 + fRec6[0] * (fVec0[(IOTA0 - static_cast<int>(std::min<float>(fConst4, std::max<float>(0.0f, fRec8[0])))) & 524287] - fTemp3);
			fRec10[0] = fSlow17 + fConst3 * fRec10[1];
			float fTemp5 = 1.0f - 0.01f * fRec10[0];
			fRec12[0] = fSlow10 * std::atan(fSlow9 * fRec1[1]) - fSlow8 * (fSlow11 * fRec12[2] + fSlow12 * fRec12[1]);
			fRec11[0] = fSlow8 * (fRec12[2] + fRec12[0] + 2.0f * fRec12[1]) - fSlow13 * (fSlow14 * fRec11[2] + fSlow15 * fRec11[1]);
			float fTemp6 = static_cast<float>(input1[i0]) + fSlow4 * fRec2[0] * (fRec11[2] + (fRec11[0] - 2.0f * fRec11[1]));
			fVec1[IOTA0 & 524287] = fTemp6;
			fRec17[0] = fSlow18 + fConst3 * fRec17[1];
			float fTemp7 = fConst0 * fRec17[0];
			float fTemp8 = ((fRec13[1] != 0.0f) ? (((fRec14[1] > 0.0f) & (fRec14[1] < 1.0f)) ? fRec13[1] : 0.0f) : (((fRec14[1] == 0.0f) & (fTemp7 != fRec15[1])) ? 0.001953125f : (((fRec14[1] == 1.0f) & (fTemp7 != fRec16[1])) ? -0.001953125f : 0.0f)));
			fRec13[0] = fTemp8;
			fRec14[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec14[1] + fTemp8));
			fRec15[0] = (((fRec14[1] >= 1.0f) & (fRec16[1] != fTemp7)) ? fTemp7 : fRec15[1]);
			fRec16[0] = (((fRec14[1] <= 0.0f) & (fRec15[1] != fTemp7)) ? fTemp7 : fRec16[1]);
			float fTemp9 = fVec1[(IOTA0 - static_cast<int>(std::min<float>(fConst4, std::max<float>(0.0f, fRec15[0])))) & 524287];
			float fTemp10 = fTemp9 + fRec14[0] * (fVec1[(IOTA0 - static_cast<int>(std::min<float>(fConst4, std::max<float>(0.0f, fRec16[0])))) & 524287] - fTemp9);
			fRec0[0] = fTemp4 * fTemp5 + 0.01f * fRec10[0] * fTemp10;
			fRec1[0] = fTemp5 * fTemp10 + 0.01f * fRec10[0] * fTemp4;
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0[0]);
			output1[i0] = static_cast<FAUSTFLOAT>(fRec1[0]);
			fRec2[1] = fRec2[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			IOTA0 = IOTA0 + 1;
			fRec9[1] = fRec9[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec10[1] = fRec10[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec17[1] = fRec17[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "DelayFaust.dsp"
	#define FAUST_CLASS_NAME "_DelayFaust"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _DelayFaust -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 7
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Delay Left", fHslider4, 2.5e+02f, 0.0f, 2e+03f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Delay Right", fHslider6, 166.7f, 0.0f, 2e+03f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Feedback", fHslider1, 2e+01f, 0.0f, 1e+02f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Feedback Lowpass", fHslider2, 1.2e+04f, 2e+01f, 2e+04f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Feedback Highpass", fHslider0, 6e+01f, 2e+01f, 2e+04f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Distortion", fHslider3, 0.1f, 0.1f, 5e+01f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Crossmix", fHslider5, 0.0f, 0.0f, 1e+02f, 0.1f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Delay_Left, "Delay Left", fHslider4, 2.5e+02f, 0.0f, 2e+03f, 0.1f) \
		p(HORIZONTALSLIDER, Delay_Right, "Delay Right", fHslider6, 166.7f, 0.0f, 2e+03f, 0.1f) \
		p(HORIZONTALSLIDER, Feedback, "Feedback", fHslider1, 2e+01f, 0.0f, 1e+02f, 0.1f) \
		p(HORIZONTALSLIDER, Feedback_Lowpass, "Feedback Lowpass", fHslider2, 1.2e+04f, 2e+01f, 2e+04f, 0.1f) \
		p(HORIZONTALSLIDER, Feedback_Highpass, "Feedback Highpass", fHslider0, 6e+01f, 2e+01f, 2e+04f, 0.1f) \
		p(HORIZONTALSLIDER, Distortion, "Distortion", fHslider3, 0.1f, 0.1f, 5e+01f, 0.1f) \
		p(HORIZONTALSLIDER, Crossmix, "Crossmix", fHslider5, 0.0f, 0.0f, 1e+02f, 0.1f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

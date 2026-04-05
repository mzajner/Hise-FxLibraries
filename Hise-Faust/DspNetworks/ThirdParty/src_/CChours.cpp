/* ------------------------------------------------------------
author: "Christopher Arndt"
license: "MIT License"
name: "CChorus"
version: "0.5"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _CChours -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___CChours_H__
#define  ___CChours_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _CChours
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

static float _CChours_faustpower2_f(float value) {
	return value * value;
}

struct _CChours final : public ::faust::dsp {
	
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider0;
	int IOTA0;
	float fVec0[524288];
	FAUSTFLOAT fHslider1;
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	FAUSTFLOAT fHslider2;
	float fConst4;
	float fRec2[2];
	FAUSTFLOAT fHslider3;
	float fRec3[2];
	FAUSTFLOAT fHslider4;
	float fConst5;
	FAUSTFLOAT fHslider5;
	float fRec4[2];
	float fConst6;
	FAUSTFLOAT fHslider6;
	float fRec5[2];
	float fRec1[3];
	FAUSTFLOAT fHslider7;
	float fRec6[2];
	float fRec0[3];
	FAUSTFLOAT fHslider8;
	float fRec9[2];
	float fConst7;
	FAUSTFLOAT fHslider9;
	float fRec10[2];
	float fRec8[3];
	float fRec7[3];
	
	_CChours() {
	}
	
	_CChours(const _CChours&) = default;
	
	virtual ~_CChours() = default;
	
	_CChours& operator=(const _CChours&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Christopher Arndt");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _CChours -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.2.0");
		m->declare("description", "Versatile stereo chorus effect");
		m->declare("filename", "CChours.dsp");
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
		m->declare("license", "MIT License");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "CChorus");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("version", "0.5");
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
		fConst1 = 2.0f * fConst0 + 1.0f;
		fConst2 = 0.001f * fConst0;
		fConst3 = 44.1f / fConst0;
		fConst4 = 1.0f - fConst3;
		fConst5 = 1.0f / fConst0;
		fConst6 = 3.1415927f / fConst0;
		fConst7 = 7.018733f / fConst0;
	}
	
	void instanceResetUserInterface() {
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider0 = static_cast<FAUSTFLOAT>(-3.5f);
		fHslider1 = static_cast<FAUSTFLOAT>(-3.5f);
		fHslider2 = static_cast<FAUSTFLOAT>(3.5f);
		fHslider3 = static_cast<FAUSTFLOAT>(0.35f);
		fHslider4 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider5 = static_cast<FAUSTFLOAT>(0.8f);
		fHslider6 = static_cast<FAUSTFLOAT>(2e+04f);
		fHslider7 = static_cast<FAUSTFLOAT>(2e+01f);
		fHslider8 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider9 = static_cast<FAUSTFLOAT>(9e+01f);
	}
	
	void instanceClear() {
		IOTA0 = 0;
		for (int l0 = 0; l0 < 524288; l0 = l0 + 1) {
			fVec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec2[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec3[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec4[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 3; l5 = l5 + 1) {
			fRec1[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec6[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 3; l7 = l7 + 1) {
			fRec0[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec9[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec10[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec8[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec7[l11] = 0.0f;
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
	
	_CChours* clone() {
		return new _CChours(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("CChorus");
		ui_interface->openHorizontalBox("Delay");
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->declare(&fHslider2, "unit", "ms");
		ui_interface->addHorizontalSlider("Delay", &fHslider2, FAUSTFLOAT(3.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(0.0001f));
		ui_interface->declare(&fHslider3, "2", "");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("Mod Amount", &fHslider3, FAUSTFLOAT(0.35f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider6, "3", "");
		ui_interface->declare(&fHslider6, "scale", "log");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->declare(&fHslider6, "unit", "Hz");
		ui_interface->addHorizontalSlider("LPF Cutoff", &fHslider6, FAUSTFLOAT(2e+04f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider7, "4", "");
		ui_interface->declare(&fHslider7, "scale", "log");
		ui_interface->declare(&fHslider7, "style", "knob");
		ui_interface->declare(&fHslider7, "unit", "Hz");
		ui_interface->addHorizontalSlider("HPF Cutoff", &fHslider7, FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("LFO");
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "style", "radio{'Sine':0;'Triangle':1}");
		ui_interface->addHorizontalSlider("Waveform", &fHslider4, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->declare(&fHslider5, "unit", "Hz");
		ui_interface->addHorizontalSlider("Freq L", &fHslider5, FAUSTFLOAT(0.8f), FAUSTFLOAT(0.001f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.0001f));
		ui_interface->declare(&fHslider8, "3", "");
		ui_interface->declare(&fHslider8, "style", "knob");
		ui_interface->addHorizontalSlider("Freq R Ratio", &fHslider8, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider9, "4", "");
		ui_interface->declare(&fHslider9, "style", "knob");
		ui_interface->declare(&fHslider9, "unit", "°");
		ui_interface->addHorizontalSlider("L/R Phase Offset", &fHslider9, FAUSTFLOAT(9e+01f), FAUSTFLOAT(-1.8e+02f), FAUSTFLOAT(1.8e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output");
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Dry", &fHslider0, FAUSTFLOAT(-3.5f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "unit", "dB");
		ui_interface->addHorizontalSlider("Wet", &fHslider1, FAUSTFLOAT(-3.5f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fCheckbox0, "3", "");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		int iSlow0 = static_cast<int>(static_cast<float>(fCheckbox0));
		float fSlow1 = std::pow(1e+01f, 0.05f * std::max<float>(-6e+01f, std::min<float>(1e+01f, static_cast<float>(fHslider0))));
		float fSlow2 = std::pow(1e+01f, 0.05f * std::max<float>(-6e+01f, std::min<float>(1e+01f, static_cast<float>(fHslider1))));
		float fSlow3 = fConst3 * std::max<float>(0.0f, std::min<float>(1e+03f, static_cast<float>(fHslider2)));
		float fSlow4 = fConst3 * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider3)));
		int iSlow5 = static_cast<int>(std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider4))));
		float fSlow6 = std::max<float>(0.001f, std::min<float>(2e+01f, static_cast<float>(fHslider5)));
		float fSlow7 = fConst5 * fSlow6;
		float fSlow8 = fConst3 * std::max<float>(2e+01f, std::min<float>(2e+04f, static_cast<float>(fHslider6)));
		float fSlow9 = fConst3 * std::max<float>(2e+01f, std::min<float>(2e+04f, static_cast<float>(fHslider7)));
		float fSlow10 = fConst5 * fSlow6 * std::max<float>(0.01f, std::min<float>(5.0f, static_cast<float>(fHslider8)));
		float fSlow11 = fConst7 * std::max<float>(-1.8e+02f, std::min<float>(1.8e+02f, static_cast<float>(fHslider9)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			fVec0[IOTA0 & 524287] = fTemp0;
			float fTemp1 = fSlow1 * fTemp0;
			fRec2[0] = fSlow3 + fConst4 * fRec2[1];
			fRec3[0] = fSlow4 + fConst4 * fRec3[1];
			fRec4[0] = fSlow7 + (fRec4[1] - std::floor(fSlow7 + fRec4[1]));
			float fTemp2 = std::floor(fRec4[0]);
			float fTemp3 = fConst2 * fRec2[0] * (fRec3[0] * ((iSlow5) ? std::fabs(4.0f * (fRec4[0] + (-0.25f - (fTemp2 + std::floor(fRec4[0] + (-0.25f - fTemp2))))) + -2.0f) + -1.0f : std::sin(6.2831855f * (fRec4[0] - fTemp2))) + 1.0f);
			int iTemp4 = static_cast<int>(fTemp3);
			float fTemp5 = std::floor(fTemp3);
			fRec5[0] = fSlow8 + fConst4 * fRec5[1];
			float fTemp6 = std::tan(fConst6 * fRec5[0]);
			float fTemp7 = 1.0f / fTemp6;
			float fTemp8 = (fTemp7 + -1.4142135f) / fTemp6 + 1.0f;
			float fTemp9 = 1.0f - 1.0f / _CChours_faustpower2_f(fTemp6);
			float fTemp10 = (fTemp7 + 1.4142135f) / fTemp6 + 1.0f;
			fRec1[0] = fVec0[(IOTA0 - static_cast<int>(std::min<float>(fConst1, static_cast<float>(std::max<int>(0, iTemp4))))) & 524287] * (fTemp5 + (1.0f - fTemp3)) + (fTemp3 - fTemp5) * fVec0[(IOTA0 - static_cast<int>(std::min<float>(fConst1, static_cast<float>(std::max<int>(0, iTemp4 + 1))))) & 524287] - (fRec1[2] * fTemp8 + 2.0f * fRec1[1] * fTemp9) / fTemp10;
			fRec6[0] = fSlow9 + fConst4 * fRec6[1];
			float fTemp11 = std::tan(fConst6 * fRec6[0]);
			float fTemp12 = 1.0f / fTemp11;
			float fTemp13 = (fTemp12 + -1.4142135f) / fTemp11 + 1.0f;
			float fTemp14 = _CChours_faustpower2_f(fTemp11);
			float fTemp15 = 1.0f - 1.0f / fTemp14;
			float fTemp16 = (fTemp12 + 1.4142135f) / fTemp11 + 1.0f;
			fRec0[0] = (fRec1[2] + fRec1[0] + 2.0f * fRec1[1]) / fTemp10 - (fRec0[2] * fTemp13 + 2.0f * fRec0[1] * fTemp15) / fTemp16;
			float fTemp17 = fTemp14 * fTemp16;
			float fTemp18 = static_cast<float>(input1[i0]);
			output0[i0] = static_cast<FAUSTFLOAT>(((iSlow0) ? fTemp18 : fTemp1 + fSlow2 * ((fRec0[2] + (fRec0[0] - 2.0f * fRec0[1])) / fTemp17)));
			fRec9[0] = fSlow10 + (fRec9[1] - std::floor(fSlow10 + fRec9[1]));
			fRec10[0] = fSlow11 + fConst4 * fRec10[1];
			float fTemp19 = fRec9[0] + 0.15915494f * fRec10[0];
			float fTemp20 = std::floor(fTemp19);
			float fTemp21 = fConst2 * fRec2[0] * (fRec3[0] * ((iSlow5) ? std::fabs(4.0f * (fTemp19 + (-0.25f - (fTemp20 + std::floor(fTemp19 + (-0.25f - fTemp20))))) + -2.0f) + -1.0f : std::sin(6.2831855f * (fTemp19 - fTemp20))) + 1.0f);
			int iTemp22 = static_cast<int>(fTemp21);
			float fTemp23 = std::floor(fTemp21);
			fRec8[0] = fVec0[(IOTA0 - static_cast<int>(std::min<float>(fConst1, static_cast<float>(std::max<int>(0, iTemp22))))) & 524287] * (fTemp23 + (1.0f - fTemp21)) + (fTemp21 - fTemp23) * fVec0[(IOTA0 - static_cast<int>(std::min<float>(fConst1, static_cast<float>(std::max<int>(0, iTemp22 + 1))))) & 524287] - (fTemp8 * fRec8[2] + 2.0f * fTemp9 * fRec8[1]) / fTemp10;
			fRec7[0] = (fRec8[2] + fRec8[0] + 2.0f * fRec8[1]) / fTemp10 - (fTemp13 * fRec7[2] + 2.0f * fTemp15 * fRec7[1]) / fTemp16;
			output1[i0] = static_cast<FAUSTFLOAT>(((iSlow0) ? fTemp18 : fTemp1 + fSlow2 * ((fRec7[2] + (fRec7[0] - 2.0f * fRec7[1])) / fTemp17)));
			IOTA0 = IOTA0 + 1;
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec6[1] = fRec6[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "CChours.dsp"
	#define FAUST_CLASS_NAME "_CChours"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _CChours -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 11
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Delay/Delay", fHslider2, 3.5f, 0.0f, 1e+03f, 0.0001f);
	FAUST_ADDHORIZONTALSLIDER("Delay/Mod Amount", fHslider3, 0.35f, 0.0f, 1.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("Delay/LPF Cutoff", fHslider6, 2e+04f, 2e+01f, 2e+04f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Delay/HPF Cutoff", fHslider7, 2e+01f, 2e+01f, 2e+04f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("LFO/Waveform", fHslider4, 1.0f, 0.0f, 1.0f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("LFO/Freq L", fHslider5, 0.8f, 0.001f, 2e+01f, 0.0001f);
	FAUST_ADDHORIZONTALSLIDER("LFO/Freq R Ratio", fHslider8, 1.0f, 0.01f, 5.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("LFO/L/R Phase Offset", fHslider9, 9e+01f, -1.8e+02f, 1.8e+02f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("Output/Dry", fHslider0, -3.5f, -6e+01f, 1e+01f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Output/Wet", fHslider1, -3.5f, -6e+01f, 1e+01f, 0.1f);
	FAUST_ADDCHECKBOX("Output/Bypass", fCheckbox0);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Delay, "Delay/Delay", fHslider2, 3.5f, 0.0f, 1e+03f, 0.0001f) \
		p(HORIZONTALSLIDER, Mod_Amount, "Delay/Mod Amount", fHslider3, 0.35f, 0.0f, 1.0f, 0.001f) \
		p(HORIZONTALSLIDER, LPF_Cutoff, "Delay/LPF Cutoff", fHslider6, 2e+04f, 2e+01f, 2e+04f, 0.1f) \
		p(HORIZONTALSLIDER, HPF_Cutoff, "Delay/HPF Cutoff", fHslider7, 2e+01f, 2e+01f, 2e+04f, 0.1f) \
		p(HORIZONTALSLIDER, Waveform, "LFO/Waveform", fHslider4, 1.0f, 0.0f, 1.0f, 1.0f) \
		p(HORIZONTALSLIDER, Freq_L, "LFO/Freq L", fHslider5, 0.8f, 0.001f, 2e+01f, 0.0001f) \
		p(HORIZONTALSLIDER, Freq_R_Ratio, "LFO/Freq R Ratio", fHslider8, 1.0f, 0.01f, 5.0f, 0.001f) \
		p(HORIZONTALSLIDER, L/R_Phase_Offset, "LFO/L/R Phase Offset", fHslider9, 9e+01f, -1.8e+02f, 1.8e+02f, 1.0f) \
		p(HORIZONTALSLIDER, Dry, "Output/Dry", fHslider0, -3.5f, -6e+01f, 1e+01f, 0.1f) \
		p(HORIZONTALSLIDER, Wet, "Output/Wet", fHslider1, -3.5f, -6e+01f, 1e+01f, 0.1f) \
		p(CHECKBOX, Bypass, "Output/Bypass", fCheckbox0, 0.0f, 0.0f, 1.0f, 1.0f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

/* ------------------------------------------------------------
name: "WahWah"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _wahWah -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___wahWah_H__
#define  ___wahWah_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _wahWah
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

struct _wahWahSIG0 {
	
	int getNumInputs_wahWahSIG0() {
		return 0;
	}
	int getNumOutputs_wahWahSIG0() {
		return 1;
	}
	
	void instanceInit_wahWahSIG0(int sample_rate) {
	}
	
	void fill_wahWahSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			table[i1] = 0.0f;
		}
	}

};

static _wahWahSIG0* new_wahWahSIG0() { return (_wahWahSIG0*)new _wahWahSIG0(); }
static void delete_wahWahSIG0(_wahWahSIG0* dsp) { delete dsp; }

static float _wahWah_faustpower2_f(float value) {
	return value * value;
}

struct _wahWah final : public ::faust::dsp {
	
	FAUSTFLOAT fHslider0;
	int iVec0[2];
	float fRec0[2];
	float ftbl0[16];
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	float fRec4[2];
	int iRec3[2];
	int iVec1[2];
	FAUSTFLOAT fHslider2;
	float fVec2[2];
	float fRec5[2];
	int iRec6[2];
	float fRec2[2];
	float fConst2;
	float fConst3;
	float fRec7[2];
	float fRec8[2];
	float fRec1[3];
	float fRec9[3];
	
	_wahWah() {
	}
	
	_wahWah(const _wahWah&) = default;
	
	virtual ~_wahWah() = default;
	
	_wahWah& operator=(const _wahWah&) = default;
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _wahWah -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "wahWah.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "WahWah");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m->declare("vaeffects.lib/version", "1.4.0");
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
		_wahWahSIG0* sig0 = new_wahWahSIG0();
		sig0->instanceInit_wahWahSIG0(sample_rate);
		sig0->fill_wahWahSIG0(16, ftbl0);
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = 6e+01f * fConst0;
		fConst2 = 1413.7167f / fConst0;
		fConst3 = 2827.4333f / fConst0;
		delete_wahWahSIG0(sig0);
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(6e+01f);
		fHslider1 = static_cast<FAUSTFLOAT>(5.4e+02f);
		fHslider2 = static_cast<FAUSTFLOAT>(0.6f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec4[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			iRec3[l3] = 0;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			iVec1[l4] = 0;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fVec2[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec5[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			iRec6[l7] = 0;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec2[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec7[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec8[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec1[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 3; l12 = l12 + 1) {
			fRec9[l12] = 0.0f;
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
	
	_wahWah* clone() {
		return new _wahWah(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("WahWah");
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "acc", "0 1 -10 0 10");
		ui_interface->addHorizontalSlider("Wah Wah", &fHslider2, FAUSTFLOAT(0.6f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "acc", "0 1 -10 0 10");
		ui_interface->addHorizontalSlider("Speed", &fHslider1, FAUSTFLOAT(5.4e+02f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(7.8e+02f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->declare(&fHslider0, "acc", "1 0 -10 0 10");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "unit", "%");
		ui_interface->addHorizontalSlider("Wah wah intensity", &fHslider0, FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = 1e-05f * std::max<float>(0.0f, std::min<float>(1e+02f, static_cast<float>(fHslider0)));
		float fSlow1 = 0.001f * std::max<float>(1e+01f, std::min<float>(7.8e+02f, static_cast<float>(fHslider1)));
		float fSlow2 = std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider2)));
		int iSlow3 = fSlow2 <= 0.0f;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			iVec0[0] = 1;
			fRec0[0] = fSlow0 + 0.999f * fRec0[1];
			float fTemp1 = std::max<float>(0.0f, std::min<float>(1.0f, fRec0[0]));
			float fTemp2 = 1.0f - fTemp1;
			fRec4[0] = fSlow1 + 0.999f * fRec4[1];
			iRec3[0] = (iVec0[1] + iRec3[1]) % static_cast<int>(fConst1 / static_cast<float>(static_cast<int>(std::max<float>(3.6e+02f, std::min<float>(1e+01f, fRec4[0])))));
			int iTemp3 = iRec3[0] <= iRec3[1];
			iVec1[0] = iTemp3;
			fVec2[0] = fSlow2;
			fRec5[0] = ((iVec1[1]) ? 0.0f : fRec5[1] + std::fabs(fSlow2 - fVec2[1]));
			iRec6[0] = (iTemp3 + iRec6[1]) % 15;
			ftbl0[std::max<int>(0, std::min<int>(((iTemp3 & ((fRec5[0] > 0.0f) | iSlow3)) ? iRec6[0] : 15), 15))] = fSlow2;
			float fTemp4 = ftbl0[std::max<int>(0, std::min<int>(iRec6[0], 15))];
			fRec2[0] = 0.0001f * std::pow(4.0f, fTemp4) + 0.999f * fRec2[1];
			float fTemp5 = std::pow(2.0f, 2.3f * fTemp4);
			float fTemp6 = 1.0f - fConst2 * (fTemp5 / std::pow(2.0f, 2.0f * (1.0f - fTemp4) + 1.0f));
			fRec7[0] = 0.999f * fRec7[1] - 0.002f * fTemp6 * std::cos(fConst3 * fTemp5);
			fRec8[0] = 0.001f * _wahWah_faustpower2_f(fTemp6) + 0.999f * fRec8[1];
			fRec1[0] = fTemp0 * fRec2[0] - (fRec7[0] * fRec1[1] + fRec8[0] * fRec1[2]);
			output0[i0] = static_cast<FAUSTFLOAT>(fTemp0 * fTemp2 + fTemp1 * (fRec1[0] - fRec1[1]));
			float fTemp7 = static_cast<float>(input1[i0]);
			fRec9[0] = fTemp7 * fRec2[0] - (fRec7[0] * fRec9[1] + fRec8[0] * fRec9[2]);
			output1[i0] = static_cast<FAUSTFLOAT>(fTemp7 * fTemp2 + fTemp1 * (fRec9[0] - fRec9[1]));
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			fRec4[1] = fRec4[0];
			iRec3[1] = iRec3[0];
			iVec1[1] = iVec1[0];
			fVec2[1] = fVec2[0];
			fRec5[1] = fRec5[0];
			iRec6[1] = iRec6[0];
			fRec2[1] = fRec2[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "wahWah.dsp"
	#define FAUST_CLASS_NAME "_wahWah"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _wahWah -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 3
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("WahWah/Wah Wah", fHslider2, 0.6f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("WahWah/Speed", fHslider1, 5.4e+02f, 1e+01f, 7.8e+02f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("WahWah/Wah wah intensity", fHslider0, 6e+01f, 0.0f, 1e+02f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Wah_Wah, "WahWah/Wah Wah", fHslider2, 0.6f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, Speed, "WahWah/Speed", fHslider1, 5.4e+02f, 1e+01f, 7.8e+02f, 0.1f) \
		p(HORIZONTALSLIDER, Wah_wah_intensity, "WahWah/Wah wah intensity", fHslider0, 6e+01f, 0.0f, 1e+02f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

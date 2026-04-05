/* ------------------------------------------------------------
name: "cryBaby"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _cryBaby -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___cryBaby_H__
#define  ___cryBaby_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _cryBaby
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

static float _cryBaby_faustpower2_f(float value) {
	return value * value;
}

struct _cryBaby final : public ::faust::dsp {
	
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider0;
	float fRec1[2];
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fRec2[2];
	float fRec3[2];
	float fRec0[3];
	float fRec4[3];
	
	_cryBaby() {
	}
	
	_cryBaby(const _cryBaby&) = default;
	
	virtual ~_cryBaby() = default;
	
	_cryBaby& operator=(const _cryBaby&) = default;
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/bypass1:author", "Julius Smith");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _cryBaby -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("demos.lib/crybaby_demo:author", "Julius O. Smith III");
		m->declare("demos.lib/crybaby_demo:licence", "MIT");
		m->declare("demos.lib/name", "Faust Demos Library");
		m->declare("demos.lib/version", "1.4.0");
		m->declare("description", "Application demonstrating the CryBaby wah pedal emulation");
		m->declare("filename", "cryBaby.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
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
		m->declare("name", "cryBaby");
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
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = 1413.7167f / fConst0;
		fConst2 = 2827.4333f / fConst0;
	}
	
	void instanceResetUserInterface() {
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider0 = static_cast<FAUSTFLOAT>(0.8f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec2[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec3[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 3; l3 = l3 + 1) {
			fRec0[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 3; l4 = l4 + 1) {
			fRec4[l4] = 0.0f;
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
	
	_cryBaby* clone() {
		return new _cryBaby(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->declare(0, "tooltip", "Reference:         https://ccrma.stanford.edu/~jos/pasp/vegf.html");
		ui_interface->openHorizontalBox("CRYBABY");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the wah         pedal has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "tooltip", "wah pedal angle between         0 (rocked back) and 1 (rocked forward)");
		ui_interface->addHorizontalSlider("Wah parameter", &fHslider0, FAUSTFLOAT(0.8f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		int iSlow0 = static_cast<int>(static_cast<float>(fCheckbox0));
		float fSlow1 = std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider0)));
		float fSlow2 = 0.0001f * std::pow(4.0f, fSlow1);
		float fSlow3 = std::pow(2.0f, 2.3f * fSlow1);
		float fSlow4 = 1.0f - fConst1 * (fSlow3 / std::pow(2.0f, 2.0f * (1.0f - fSlow1) + 1.0f));
		float fSlow5 = 0.002f * fSlow4 * std::cos(fConst2 * fSlow3);
		float fSlow6 = 0.001f * _cryBaby_faustpower2_f(fSlow4);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec1[0] = fSlow2 + 0.999f * fRec1[1];
			float fTemp0 = static_cast<float>(input0[i0]);
			fRec2[0] = 0.999f * fRec2[1] - fSlow5;
			fRec3[0] = fSlow6 + 0.999f * fRec3[1];
			fRec0[0] = fRec1[0] * ((iSlow0) ? 0.0f : fTemp0) - (fRec2[0] * fRec0[1] + fRec3[0] * fRec0[2]);
			output0[i0] = static_cast<FAUSTFLOAT>(((iSlow0) ? fTemp0 : fRec0[0] - fRec0[1]));
			float fTemp1 = static_cast<float>(input1[i0]);
			fRec4[0] = fRec1[0] * ((iSlow0) ? 0.0f : fTemp1) - (fRec2[0] * fRec4[1] + fRec3[0] * fRec4[2]);
			output1[i0] = static_cast<FAUSTFLOAT>(((iSlow0) ? fTemp1 : fRec4[0] - fRec4[1]));
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "cryBaby.dsp"
	#define FAUST_CLASS_NAME "_cryBaby"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _cryBaby -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDCHECKBOX("CRYBABY [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/vegf.html]/Bypass", fCheckbox0);
	FAUST_ADDHORIZONTALSLIDER("CRYBABY [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/vegf.html]/Wah parameter", fHslider0, 0.8f, 0.0f, 1.0f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(CHECKBOX, Bypass, "CRYBABY [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/vegf.html]/Bypass", fCheckbox0, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(HORIZONTALSLIDER, Wah_parameter, "CRYBABY [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/vegf.html]/Wah parameter", fHslider0, 0.8f, 0.0f, 1.0f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

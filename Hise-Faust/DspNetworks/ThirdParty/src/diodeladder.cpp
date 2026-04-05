/* ------------------------------------------------------------
author: "Christopher Arndt"
license: "MIT-style STK-4.3 license"
name: "DiodeLadder"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _diodeladder -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___diodeladder_H__
#define  ___diodeladder_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _diodeladder
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

static float _diodeladder_faustpower2_f(float value) {
	return value * value;
}
static float _diodeladder_faustpower3_f(float value) {
	return value * value * value;
}
static float _diodeladder_faustpower4_f(float value) {
	return value * value * value * value;
}

struct _diodeladder final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	float fConst3;
	float fRec5[2];
	FAUSTFLOAT fHslider1;
	float fRec6[2];
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	float fRec4[2];
	float fRec8[2];
	float fRec9[2];
	float fRec10[2];
	float fRec11[2];
	
	_diodeladder() {
	}
	
	_diodeladder(const _diodeladder&) = default;
	
	virtual ~_diodeladder() = default;
	
	_diodeladder& operator=(const _diodeladder&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Christopher Arndt");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _diodeladder -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("description", "FAUST Diode Ladder 24 dB LPF");
		m->declare("diodeladder.dsp/diodeLadder:author", "Eric Tarr");
		m->declare("diodeladder.dsp/diodeLadder:license", "MIT-style STK-4.3 license");
		m->declare("filename", "diodeladder.dsp");
		m->declare("license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("misceffects.lib/cubicnl:author", "Julius O. Smith III");
		m->declare("misceffects.lib/cubicnl:license", "STK-4.3");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.5.1");
		m->declare("name", "DiodeLadder");
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
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(2e+04f);
		fHslider1 = static_cast<FAUSTFLOAT>(4.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec5[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec6[l1] = 0.0f;
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
			fRec4[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec8[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec9[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec10[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec11[l9] = 0.0f;
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
	
	_diodeladder* clone() {
		return new _diodeladder(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("DiodeLadder");
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
		ui_interface->addHorizontalSlider("Q", &fHslider1, FAUSTFLOAT(4.0f), FAUSTFLOAT(0.7072f), FAUSTFLOAT(25.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst2 * std::max<float>(2e+01f, std::min<float>(2e+04f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst2 * std::max<float>(0.7072f, std::min<float>(25.0f, static_cast<float>(fHslider1)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec5[0] = fSlow0 + fConst3 * fRec5[1];
			float fTemp0 = std::tan(fConst1 * fRec5[0]);
			float fTemp1 = std::max<float>(-1.0f, std::min<float>(1.0f, 1e+02f * static_cast<float>(input0[i0])));
			float fTemp2 = 17.0f - 9.7f * std::pow(-(0.33333334f * (1.0f - (std::log10(fRec5[0]) + -0.30103f))), 1e+01f);
			fRec6[0] = fSlow1 + fConst3 * fRec6[1];
			float fTemp3 = fRec6[0] + -0.707f;
			float fTemp4 = fTemp2 * fTemp3;
			float fTemp5 = fTemp0 + 1.0f;
			float fTemp6 = 0.5f * (fRec1[1] * fTemp0 / fTemp5) + fRec2[1];
			float fTemp7 = fTemp0 * (1.0f - 0.25f * (fTemp0 / fTemp5)) + 1.0f;
			float fTemp8 = fTemp0 * fTemp6 / fTemp7;
			float fTemp9 = 0.5f * fTemp8;
			float fTemp10 = fTemp9 + fRec3[1];
			float fTemp11 = fTemp0 * (1.0f - 0.25f * (fTemp0 / fTemp7)) + 1.0f;
			float fTemp12 = fTemp0 * fTemp10 / fTemp11;
			float fTemp13 = _diodeladder_faustpower3_f(fTemp0);
			float fTemp14 = fTemp12 + fRec4[1];
			float fTemp15 = fTemp7 * fTemp11;
			float fTemp16 = fTemp0 * (1.0f - 0.5f * (fTemp0 / fTemp11)) + 1.0f;
			float fTemp17 = fTemp15 * fTemp16;
			float fTemp18 = _diodeladder_faustpower2_f(fTemp0);
			float fTemp19 = 0.5f * (fTemp18 / (fTemp11 * fTemp16)) + 1.0f;
			float fTemp20 = fTemp5 * fTemp7;
			float fTemp21 = 0.0051455153f * (_diodeladder_faustpower4_f(fTemp0) * fTemp2 * fTemp3 / (fTemp20 * fTemp11 * fTemp16)) + 1.0f;
			float fTemp22 = fTemp0 * ((1.5f * fTemp1 * (1.0f - 0.33333334f * _diodeladder_faustpower2_f(fTemp1)) - fTemp4 * (0.041164123f * fRec1[1] + 0.020582061f * fTemp8 + 0.020582061f * fTemp12 + 0.0051455153f * (fTemp13 * fTemp14 / fTemp17)) / fTemp5) * fTemp19 / fTemp21 + (fTemp10 + 0.5f * (fTemp0 * fTemp14 / fTemp16)) / fTemp11 - fRec4[1]) / fTemp5;
			float fTemp23 = 0.25f * (fTemp18 / fTemp15) + 1.0f;
			float fTemp24 = fTemp0 * (0.5f * ((fRec4[1] + fTemp22) * fTemp23 + (fTemp6 + 0.5f * fTemp12) / fTemp7) - fRec3[1]) / fTemp5;
			float fTemp25 = 0.25f * (fTemp18 / fTemp20) + 1.0f;
			float fTemp26 = fTemp0 * (0.5f * ((fRec3[1] + fTemp24) * fTemp25 + (fRec1[1] + fTemp9) / fTemp5) - fRec2[1]) / fTemp5;
			float fTemp27 = fTemp0 * (0.5f * (fRec2[1] + fTemp26) - fRec1[1]) / fTemp5;
			float fRec0 = fRec1[1] + fTemp27;
			fRec1[0] = fRec1[1] + 2.0f * fTemp27;
			fRec2[0] = fRec2[1] + 2.0f * fTemp26;
			fRec3[0] = fRec3[1] + 2.0f * fTemp24;
			fRec4[0] = fRec4[1] + 2.0f * fTemp22;
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0);
			float fTemp28 = std::max<float>(-1.0f, std::min<float>(1.0f, 1e+02f * static_cast<float>(input1[i0])));
			float fTemp29 = 0.5f * (fTemp0 * fRec8[1] / fTemp5) + fRec9[1];
			float fTemp30 = fTemp0 * fTemp29 / fTemp7;
			float fTemp31 = 0.5f * fTemp30;
			float fTemp32 = fTemp31 + fRec10[1];
			float fTemp33 = fTemp0 * fTemp32 / fTemp11;
			float fTemp34 = fTemp33 + fRec11[1];
			float fTemp35 = fTemp0 * (fTemp19 * (1.5f * fTemp28 * (1.0f - 0.33333334f * _diodeladder_faustpower2_f(fTemp28)) - fTemp4 * (0.041164123f * fRec8[1] + 0.020582061f * fTemp30 + 0.020582061f * fTemp33 + 0.0051455153f * (fTemp13 * fTemp34 / fTemp17)) / fTemp5) / fTemp21 + (fTemp32 + 0.5f * (fTemp0 * fTemp34 / fTemp16)) / fTemp11 - fRec11[1]) / fTemp5;
			float fTemp36 = fTemp0 * (0.5f * (fTemp23 * (fRec11[1] + fTemp35) + (fTemp29 + 0.5f * fTemp33) / fTemp7) - fRec10[1]) / fTemp5;
			float fTemp37 = fTemp0 * (0.5f * (fTemp25 * (fRec10[1] + fTemp36) + (fRec8[1] + fTemp31) / fTemp5) - fRec9[1]) / fTemp5;
			float fTemp38 = fTemp0 * (0.5f * (fRec9[1] + fTemp37) - fRec8[1]) / fTemp5;
			float fRec7 = fRec8[1] + fTemp38;
			fRec8[0] = fRec8[1] + 2.0f * fTemp38;
			fRec9[0] = fRec9[1] + 2.0f * fTemp37;
			fRec10[0] = fRec10[1] + 2.0f * fTemp36;
			fRec11[0] = fRec11[1] + 2.0f * fTemp35;
			output1[i0] = static_cast<FAUSTFLOAT>(fRec7);
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "diodeladder.dsp"
	#define FAUST_CLASS_NAME "_diodeladder"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _diodeladder -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Cutoff frequency", fHslider0, 2e+04f, 2e+01f, 2e+04f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Q", fHslider1, 4.0f, 0.7072f, 25.0f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Cutoff_frequency, "Cutoff frequency", fHslider0, 2e+04f, 2e+01f, 2e+04f, 0.1f) \
		p(HORIZONTALSLIDER, Q, "Q", fHslider1, 4.0f, 0.7072f, 25.0f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

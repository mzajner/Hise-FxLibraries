/* ------------------------------------------------------------
author: "Christopher Arndt"
license: "MIT-style STK-4.3 license"
name: "DiodeLadder"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _DiodeLadderLpf2Poles -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___DiodeLadderLpf2Poles_H__
#define  ___DiodeLadderLpf2Poles_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _DiodeLadderLpf2Poles
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

static float _DiodeLadderLpf2Poles_faustpower2_f(float value) {
	return value * value;
}

struct _DiodeLadderLpf2Poles final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	float fConst3;
	float fRec3[2];
	FAUSTFLOAT fHslider1;
	float fRec4[2];
	FAUSTFLOAT fHslider2;
	float fRec1[2];
	float fRec2[2];
	float fRec6[2];
	float fRec7[2];
	
	_DiodeLadderLpf2Poles() {
	}
	
	_DiodeLadderLpf2Poles(const _DiodeLadderLpf2Poles&) = default;
	
	virtual ~_DiodeLadderLpf2Poles() = default;
	
	_DiodeLadderLpf2Poles& operator=(const _DiodeLadderLpf2Poles&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Christopher Arndt");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _DiodeLadderLpf2Poles -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("description", "FAUST Diode Ladder 24 dB LPF");
		m->declare("filename", "DiodeLadderLpf2Poles.dsp");
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
		fHslider1 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider2 = static_cast<FAUSTFLOAT>(1.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec3[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec4[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec2[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec6[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec7[l5] = 0.0f;
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
	
	_DiodeLadderLpf2Poles* clone() {
		return new _DiodeLadderLpf2Poles(*this);
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
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "abbrev", "q");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->declare(&fHslider2, "symbol", "q");
		ui_interface->addHorizontalSlider("Q", &fHslider2, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.7072f), FAUSTFLOAT(25.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("drive", &fHslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst2 * std::max<float>(2e+01f, std::min<float>(2e+04f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst2 * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider1)));
		float fSlow2 = std::max<float>(0.7072f, std::min<float>(25.0f, static_cast<float>(fHslider2))) + -0.707f;
		float fSlow3 = 0.020582061f * fSlow2;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec3[0] = fSlow0 + fConst3 * fRec3[1];
			float fTemp0 = std::tan(fConst1 * fRec3[0]);
			fRec4[0] = fSlow1 + fConst3 * fRec4[1];
			float fTemp1 = std::pow(1e+01f, 2.0f * fRec4[0]);
			float fTemp2 = std::max<float>(-1.0f, std::min<float>(1.0f, static_cast<float>(input0[i0]) * fTemp1));
			float fTemp3 = 17.0f - 9.7f * std::pow(-(0.33333334f * (1.0f - (std::log10(fRec3[0]) + -0.30103f))), 1e+01f);
			float fTemp4 = fTemp0 + 1.0f;
			float fTemp5 = fTemp0 * (1.0f - 0.5f * (fTemp0 / fTemp4)) + 1.0f;
			float fTemp6 = fTemp0 * (fRec1[1] * fTemp0 / fTemp4 + fRec2[1]) / fTemp5;
			float fTemp7 = _DiodeLadderLpf2Poles_faustpower2_f(fTemp0);
			float fTemp8 = fTemp4 * fTemp5;
			float fTemp9 = 0.5f * (fTemp7 / fTemp8) + 1.0f;
			float fTemp10 = fSlow3 * (fTemp7 * fTemp3 / fTemp8) + 1.0f;
			float fTemp11 = fTemp0 * ((1.5f * fTemp2 * (1.0f - 0.33333334f * _DiodeLadderLpf2Poles_faustpower2_f(fTemp2)) - fSlow2 * (fTemp3 * (0.041164123f * fRec1[1] + 0.020582061f * fTemp6) / fTemp4)) * fTemp9 / fTemp10 + (fRec1[1] + 0.5f * fTemp6) / fTemp4 - fRec2[1]) / fTemp4;
			float fTemp12 = fTemp0 * (0.5f * (fRec2[1] + fTemp11) - fRec1[1]) / fTemp4;
			float fRec0 = fRec1[1] + fTemp12;
			fRec1[0] = fRec1[1] + 2.0f * fTemp12;
			fRec2[0] = fRec2[1] + 2.0f * fTemp11;
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0);
			float fTemp13 = std::max<float>(-1.0f, std::min<float>(1.0f, static_cast<float>(input1[i0]) * fTemp1));
			float fTemp14 = fTemp0 * (fTemp0 * fRec6[1] / fTemp4 + fRec7[1]) / fTemp5;
			float fTemp15 = fTemp0 * (fTemp9 * (1.5f * fTemp13 * (1.0f - 0.33333334f * _DiodeLadderLpf2Poles_faustpower2_f(fTemp13)) - fSlow2 * (fTemp3 * (0.041164123f * fRec6[1] + 0.020582061f * fTemp14) / fTemp4)) / fTemp10 + (fRec6[1] + 0.5f * fTemp14) / fTemp4 - fRec7[1]) / fTemp4;
			float fTemp16 = fTemp0 * (0.5f * (fRec7[1] + fTemp15) - fRec6[1]) / fTemp4;
			float fRec5 = fRec6[1] + fTemp16;
			fRec6[0] = fRec6[1] + 2.0f * fTemp16;
			fRec7[0] = fRec7[1] + 2.0f * fTemp15;
			output1[i0] = static_cast<FAUSTFLOAT>(fRec5);
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "DiodeLadderLpf2Poles.dsp"
	#define FAUST_CLASS_NAME "_DiodeLadderLpf2Poles"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _DiodeLadderLpf2Poles -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 3
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Cutoff frequency", fHslider0, 2e+04f, 2e+01f, 2e+04f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Q", fHslider2, 1.0f, 0.7072f, 25.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("drive", fHslider1, 0.5f, 0.0f, 1.0f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Cutoff_frequency, "Cutoff frequency", fHslider0, 2e+04f, 2e+01f, 2e+04f, 0.1f) \
		p(HORIZONTALSLIDER, Q, "Q", fHslider2, 1.0f, 0.7072f, 25.0f, 0.01f) \
		p(HORIZONTALSLIDER, drive, "drive", fHslider1, 0.5f, 0.0f, 1.0f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

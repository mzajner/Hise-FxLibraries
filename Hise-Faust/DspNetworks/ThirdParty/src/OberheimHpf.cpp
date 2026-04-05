/* ------------------------------------------------------------
author: "Eric Tarr"
name: "oberheimLPF"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _OberheimHpf -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___OberheimHpf_H__
#define  ___OberheimHpf_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _OberheimHpf
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

static float _OberheimHpf_faustpower2_f(float value) {
	return value * value;
}

struct _OberheimHpf final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	float fRec3[2];
	float fConst3;
	FAUSTFLOAT fHslider1;
	float fRec4[2];
	float fRec1[2];
	float fRec2[2];
	float fRec6[2];
	float fRec7[2];
	
	_OberheimHpf() {
	}
	
	_OberheimHpf(const _OberheimHpf&) = default;
	
	virtual ~_OberheimHpf() = default;
	
	_OberheimHpf& operator=(const _OberheimHpf&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Eric Tarr");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _OberheimHpf -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("description", "Demonstration of the Oberheim High-Pass Filter");
		m->declare("filename", "OberheimHpf.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("misceffects.lib/cubicnl:author", "Julius O. Smith III");
		m->declare("misceffects.lib/cubicnl:license", "STK-4.3");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.5.1");
		m->declare("name", "oberheimLPF");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m->declare("vaeffects.lib/oberheim:author", "Eric Tarr");
		m->declare("vaeffects.lib/oberheim:license", "MIT-style STK-4.3 license");
		m->declare("vaeffects.lib/oberheimHPF:author", "Eric Tarr");
		m->declare("vaeffects.lib/oberheimHPF:license", "MIT-style STK-4.3 license");
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
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 6.2831855f / fConst0;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.5f);
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
	
	_OberheimHpf* clone() {
		return new _OberheimHpf(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("oberheimLPF");
		ui_interface->addHorizontalSlider("Q", &fHslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.5f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("freq", &fHslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst1 * std::max<float>(0.5f, std::min<float>(1e+01f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst1 * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider1)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec3[0] = fSlow0 + fConst2 * fRec3[1];
			fRec4[0] = fSlow1 + fConst2 * fRec4[1];
			float fTemp0 = std::tan(fConst3 * std::pow(1e+01f, 3.0f * fRec4[0] + 1.0f));
			float fTemp1 = 1.0f / fRec3[0] + fTemp0;
			float fTemp2 = static_cast<float>(input0[i0]) - (fRec1[1] + fRec2[1] * fTemp1);
			float fTemp3 = fTemp0 * fTemp1 + 1.0f;
			float fTemp4 = fTemp2 / fTemp3;
			float fRec0 = fTemp4;
			float fTemp5 = fTemp0 * fTemp2 / fTemp3;
			float fTemp6 = std::max<float>(-1.0f, std::min<float>(1.0f, fRec2[1] + fTemp5));
			float fTemp7 = 1.0f - 0.33333334f * _OberheimHpf_faustpower2_f(fTemp6);
			float fTemp8 = fTemp0 * fTemp6 * fTemp7;
			fRec1[0] = fRec1[1] + 2.0f * fTemp8;
			float fTemp9 = fTemp6 * fTemp7;
			fRec2[0] = fTemp5 + fTemp9;
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0);
			float fTemp10 = static_cast<float>(input1[i0]) - (fRec6[1] + fTemp1 * fRec7[1]);
			float fTemp11 = fTemp10 / fTemp3;
			float fRec5 = fTemp11;
			float fTemp12 = fTemp0 * fTemp10 / fTemp3;
			float fTemp13 = std::max<float>(-1.0f, std::min<float>(1.0f, fRec7[1] + fTemp12));
			float fTemp14 = 1.0f - 0.33333334f * _OberheimHpf_faustpower2_f(fTemp13);
			float fTemp15 = fTemp0 * fTemp13 * fTemp14;
			fRec6[0] = fRec6[1] + 2.0f * fTemp15;
			float fTemp16 = fTemp13 * fTemp14;
			fRec7[0] = fTemp12 + fTemp16;
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
	
	#define FAUST_FILE_NAME "OberheimHpf.dsp"
	#define FAUST_CLASS_NAME "_OberheimHpf"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _OberheimHpf -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Q", fHslider0, 1.0f, 0.5f, 1e+01f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("freq", fHslider1, 0.5f, 0.0f, 1.0f, 0.001f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Q, "Q", fHslider0, 1.0f, 0.5f, 1e+01f, 0.01f) \
		p(HORIZONTALSLIDER, freq, "freq", fHslider1, 0.5f, 0.0f, 1.0f, 0.001f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

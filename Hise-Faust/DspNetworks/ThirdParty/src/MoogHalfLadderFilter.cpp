/* ------------------------------------------------------------
author: "Eric Tarr"
name: "moogHalfLadder"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _MoogHalfLadderFilter -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___MoogHalfLadderFilter_H__
#define  ___MoogHalfLadderFilter_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _MoogHalfLadderFilter
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

static float _MoogHalfLadderFilter_faustpower2_f(float value) {
	return value * value;
}

struct _MoogHalfLadderFilter final : public ::faust::dsp {
	
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
	float fRec7[2];
	float fRec8[2];
	float fRec9[2];
	
	_MoogHalfLadderFilter() {
	}
	
	_MoogHalfLadderFilter(const _MoogHalfLadderFilter&) = default;
	
	virtual ~_MoogHalfLadderFilter() = default;
	
	_MoogHalfLadderFilter& operator=(const _MoogHalfLadderFilter&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Eric Tarr");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _MoogHalfLadderFilter -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("description", "Demonstration of moogHalfLadder");
		m->declare("filename", "MoogHalfLadderFilter.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "moogHalfLadder");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("vaeffects.lib/moogHalfLadder:author", "Eric Tarr");
		m->declare("vaeffects.lib/moogHalfLadder:license", "MIT-style STK-4.3 license");
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
		fConst1 = 6.2831855f / fConst0;
		fConst2 = 44.1f / fConst0;
		fConst3 = 1.0f - fConst2;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(0.1f);
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
			fRec7[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec8[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec9[l7] = 0.0f;
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
	
	_MoogHalfLadderFilter* clone() {
		return new _MoogHalfLadderFilter(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("moogHalfLadder");
		ui_interface->addHorizontalSlider("Q", &fHslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.7072f), FAUSTFLOAT(25.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("freq", &fHslider0, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst2 * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst2 * std::max<float>(0.7072f, std::min<float>(25.0f, static_cast<float>(fHslider1)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec4[0] = fSlow0 + fConst3 * fRec4[1];
			float fTemp0 = std::tan(fConst1 * std::pow(1e+01f, 3.0f * fRec4[0] + 1.0f));
			fRec5[0] = fSlow1 + fConst3 * fRec5[1];
			float fTemp1 = fRec5[0] + -0.70710677f;
			float fTemp2 = fTemp0 + 1.0f;
			float fTemp3 = 2.0f * (fTemp0 / fTemp2) + -1.0f;
			float fTemp4 = fTemp0 * fTemp3;
			float fTemp5 = 0.0823286f * (_MoogHalfLadderFilter_faustpower2_f(fTemp0) * fTemp1 * fTemp3 / _MoogHalfLadderFilter_faustpower2_f(fTemp2)) + 1.0f;
			float fTemp6 = fTemp0 * ((static_cast<float>(input0[i0]) - fTemp1 * (0.1646572f * fRec1[1] + 0.0823286f * fRec2[1] * fTemp3 + 0.0823286f * (fTemp4 * fRec3[1] / fTemp2)) / fTemp2) / fTemp5 - fRec3[1]) / fTemp2;
			float fTemp7 = fTemp0 * (fRec3[1] + fTemp6 - fRec2[1]) / fTemp2;
			float fTemp8 = fRec2[1] + fTemp7;
			float fTemp9 = fTemp0 * (fTemp8 - fRec1[1]) / fTemp2;
			float fRec0 = 2.0f * (fRec1[1] + fTemp9) - fTemp8;
			fRec1[0] = fRec1[1] + 2.0f * fTemp9;
			fRec2[0] = fRec2[1] + 2.0f * fTemp7;
			fRec3[0] = fRec3[1] + 2.0f * fTemp6;
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0);
			float fTemp10 = fTemp0 * ((static_cast<float>(input1[i0]) - fTemp1 * (0.1646572f * fRec7[1] + 0.0823286f * fTemp3 * fRec8[1] + 0.0823286f * (fTemp4 * fRec9[1] / fTemp2)) / fTemp2) / fTemp5 - fRec9[1]) / fTemp2;
			float fTemp11 = fTemp0 * (fRec9[1] + fTemp10 - fRec8[1]) / fTemp2;
			float fTemp12 = fRec8[1] + fTemp11;
			float fTemp13 = fTemp0 * (fTemp12 - fRec7[1]) / fTemp2;
			float fRec6 = 2.0f * (fRec7[1] + fTemp13) - fTemp12;
			fRec7[0] = fRec7[1] + 2.0f * fTemp13;
			fRec8[0] = fRec8[1] + 2.0f * fTemp11;
			fRec9[0] = fRec9[1] + 2.0f * fTemp10;
			output1[i0] = static_cast<FAUSTFLOAT>(fRec6);
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "MoogHalfLadderFilter.dsp"
	#define FAUST_CLASS_NAME "_MoogHalfLadderFilter"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _MoogHalfLadderFilter -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Q", fHslider1, 1.0f, 0.7072f, 25.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("freq", fHslider0, 0.1f, 0.0f, 1.0f, 0.001f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Q, "Q", fHslider1, 1.0f, 0.7072f, 25.0f, 0.01f) \
		p(HORIZONTALSLIDER, freq, "freq", fHslider0, 0.1f, 0.0f, 1.0f, 0.001f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

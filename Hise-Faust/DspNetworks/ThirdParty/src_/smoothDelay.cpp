/* ------------------------------------------------------------
author: "Yann Orlarey"
copyright: "Grame"
license: "STK-4.3"
name: "smoothDelay"
version: "1.0"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _smoothDelay -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___smoothDelay_H__
#define  ___smoothDelay_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _smoothDelay
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


struct _smoothDelay final : public ::faust::dsp {
	
	FAUSTFLOAT fHslider0;
	int IOTA0;
	float fVec0[262144];
	FAUSTFLOAT fHslider1;
	int fSampleRate;
	float fConst0;
	float fRec5[2];
	FAUSTFLOAT fHslider2;
	float fRec6[2];
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	float fRec4[2];
	float fRec0[2];
	float fVec1[262144];
	float fRec7[2];
	
	_smoothDelay() {
	}
	
	_smoothDelay(const _smoothDelay&) = default;
	
	virtual ~_smoothDelay() = default;
	
	_smoothDelay& operator=(const _smoothDelay&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Yann Orlarey");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _smoothDelay -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("copyright", "Grame");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.2.0");
		m->declare("filename", "smoothDelay.dsp");
		m->declare("license", "STK-4.3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "smoothDelay");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("version", "1.0");
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
		fConst0 = 1.0f - 44.1f / std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(1e+01f);
	}
	
	void instanceClear() {
		IOTA0 = 0;
		for (int l0 = 0; l0 < 262144; l0 = l0 + 1) {
			fVec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec5[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec6[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec1[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec2[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec3[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec4[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec0[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 262144; l8 = l8 + 1) {
			fVec1[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec7[l9] = 0.0f;
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
	
	_smoothDelay* clone() {
		return new _smoothDelay(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("smoothDelay");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("delay", &fHslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->addHorizontalSlider("feedback", &fHslider0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(85.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->declare(&fHslider2, "unit", "ms");
		ui_interface->addHorizontalSlider("interpolation", &fHslider2, FAUSTFLOAT(1e+01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = 0.01f * std::max<float>(0.0f, std::min<float>(85.0f, static_cast<float>(fHslider0)));
		float fSlow1 = 0.0441f * std::max<float>(0.0f, std::min<float>(1e+03f, static_cast<float>(fHslider1)));
		float fSlow2 = 0.0441f * std::max<float>(1.0f, std::min<float>(1e+02f, static_cast<float>(fHslider2)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]) + fSlow0 * fRec0[1];
			fVec0[IOTA0 & 262143] = fTemp0;
			fRec5[0] = fSlow1 + fConst0 * fRec5[1];
			fRec6[0] = fSlow2 + fConst0 * fRec6[1];
			float fTemp1 = 1.0f / fRec6[0];
			float fTemp2 = ((fRec1[1] != 0.0f) ? (((fRec2[1] > 0.0f) & (fRec2[1] < 1.0f)) ? fRec1[1] : 0.0f) : (((fRec2[1] == 0.0f) & (fRec5[0] != fRec3[1])) ? fTemp1 : (((fRec2[1] == 1.0f) & (fRec5[0] != fRec4[1])) ? -fTemp1 : 0.0f)));
			fRec1[0] = fTemp2;
			fRec2[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec2[1] + fTemp2));
			fRec3[0] = (((fRec2[1] >= 1.0f) & (fRec4[1] != fRec5[0])) ? fRec5[0] : fRec3[1]);
			fRec4[0] = (((fRec2[1] <= 0.0f) & (fRec3[1] != fRec5[0])) ? fRec5[0] : fRec4[1]);
			int iTemp3 = static_cast<int>(std::min<float>(2.4e+05f, std::max<float>(0.0f, fRec3[0])));
			float fTemp4 = fVec0[(IOTA0 - iTemp3) & 262143];
			int iTemp5 = static_cast<int>(std::min<float>(2.4e+05f, std::max<float>(0.0f, fRec4[0])));
			fRec0[0] = fTemp4 + fRec2[0] * (fVec0[(IOTA0 - iTemp5) & 262143] - fTemp4);
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0[0]);
			float fTemp6 = static_cast<float>(input1[i0]) + fSlow0 * fRec7[1];
			fVec1[IOTA0 & 262143] = fTemp6;
			float fTemp7 = fVec1[(IOTA0 - iTemp3) & 262143];
			fRec7[0] = fTemp7 + fRec2[0] * (fVec1[(IOTA0 - iTemp5) & 262143] - fTemp7);
			output1[i0] = static_cast<FAUSTFLOAT>(fRec7[0]);
			IOTA0 = IOTA0 + 1;
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec0[1] = fRec0[0];
			fRec7[1] = fRec7[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "smoothDelay.dsp"
	#define FAUST_CLASS_NAME "_smoothDelay"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _smoothDelay -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 3
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("delay", fHslider1, 0.0f, 0.0f, 1e+03f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("feedback", fHslider0, 0.0f, 0.0f, 85.0f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("interpolation", fHslider2, 1e+01f, 1.0f, 1e+02f, 0.1f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, delay, "delay", fHslider1, 0.0f, 0.0f, 1e+03f, 0.1f) \
		p(HORIZONTALSLIDER, feedback, "feedback", fHslider0, 0.0f, 0.0f, 85.0f, 0.1f) \
		p(HORIZONTALSLIDER, interpolation, "interpolation", fHslider2, 1e+01f, 1.0f, 1e+02f, 0.1f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

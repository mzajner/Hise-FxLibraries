/* ------------------------------------------------------------
author: "Albert Graef"
name: "echo"
version: "1.0"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _EchoDelays -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___EchoDelays_H__
#define  ___EchoDelays_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _EchoDelays
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


struct _EchoDelays final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	float fRec0[2];
	FAUSTFLOAT fHslider1;
	float fRec3[2];
	FAUSTFLOAT fHslider2;
	float fRec4[2];
	int IOTA0;
	float fVec0[262144];
	FAUSTFLOAT fHslider3;
	float fRec5[2];
	float fRec1[2];
	float fVec1[262144];
	float fRec2[2];
	
	_EchoDelays() {
	}
	
	_EchoDelays(const _EchoDelays&) = default;
	
	virtual ~_EchoDelays() = default;
	
	_EchoDelays& operator=(const _EchoDelays&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Albert Graef");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _EchoDelays -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("description", "stereo delay effect");
		m->declare("filename", "EchoDelays.dsp");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/version", "1.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "echo");
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
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider3 = static_cast<FAUSTFLOAT>(1.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec3[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec4[l2] = 0.0f;
		}
		IOTA0 = 0;
		for (int l3 = 0; l3 < 262144; l3 = l3 + 1) {
			fVec0[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec1[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 262144; l6 = l6 + 1) {
			fVec1[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec2[l7] = 0.0f;
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
	
	_EchoDelays* clone() {
		return new _EchoDelays(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("echo");
		ui_interface->addHorizontalSlider("delay", &fHslider3, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("feedback", &fHslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.95f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("level", &fHslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("stereo", &fHslider2, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst1 * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst1 * std::max<float>(0.0f, std::min<float>(0.95f, static_cast<float>(fHslider1)));
		float fSlow2 = fConst1 * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider2)));
		float fSlow3 = fConst1 * std::max<float>(0.0f, std::min<float>(5.0f, static_cast<float>(fHslider3)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			fRec0[0] = fSlow0 + fConst2 * fRec0[1];
			fRec3[0] = fSlow1 + fConst2 * fRec3[1];
			fRec4[0] = fSlow2 + fConst2 * fRec4[1];
			float fTemp1 = 1.0f - fRec4[0];
			float fTemp2 = fTemp0 + fRec3[0] * (fTemp1 * fRec1[1] + fRec4[0] * fRec2[1]);
			fVec0[IOTA0 & 262143] = fTemp2;
			fRec5[0] = fSlow3 + fConst2 * fRec5[1];
			float fTemp3 = fConst0 * fRec5[0];
			int iTemp4 = static_cast<int>(fTemp3);
			int iTemp5 = iTemp4 & 262143;
			float fTemp6 = static_cast<float>(iTemp4);
			float fTemp7 = fTemp6 + (1.0f - fTemp3);
			float fTemp8 = fTemp3 - fTemp6;
			int iTemp9 = (iTemp4 + 1) & 262143;
			fRec1[0] = fVec0[(IOTA0 - iTemp5) & 262143] * fTemp7 + fTemp8 * fVec0[(IOTA0 - iTemp9) & 262143];
			float fTemp10 = static_cast<float>(input1[i0]);
			float fTemp11 = fTemp10 + fRec3[0] * (fTemp1 * fRec2[1] + fRec4[0] * fRec1[1]);
			fVec1[IOTA0 & 262143] = fTemp11;
			fRec2[0] = fTemp7 * fVec1[(IOTA0 - iTemp5) & 262143] + fTemp8 * fVec1[(IOTA0 - iTemp9) & 262143];
			float fTemp12 = fRec0[0] + 1.0f;
			output0[i0] = static_cast<FAUSTFLOAT>((fTemp0 + fRec0[0] * (fRec1[0] * fTemp1 + fRec4[0] * fRec2[0])) / fTemp12);
			output1[i0] = static_cast<FAUSTFLOAT>((fTemp10 + fRec0[0] * (fRec2[0] * fTemp1 + fRec4[0] * fRec1[0])) / fTemp12);
			fRec0[1] = fRec0[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			IOTA0 = IOTA0 + 1;
			fRec5[1] = fRec5[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "EchoDelays.dsp"
	#define FAUST_CLASS_NAME "_EchoDelays"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _EchoDelays -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 4
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("echo/delay", fHslider3, 1.0f, 0.0f, 5.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("echo/feedback", fHslider1, 0.0f, 0.0f, 0.95f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("echo/level", fHslider0, 1.0f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("echo/stereo", fHslider2, 0.0f, 0.0f, 1.0f, 0.001f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, delay, "echo/delay", fHslider3, 1.0f, 0.0f, 5.0f, 0.001f) \
		p(HORIZONTALSLIDER, feedback, "echo/feedback", fHslider1, 0.0f, 0.0f, 0.95f, 0.001f) \
		p(HORIZONTALSLIDER, level, "echo/level", fHslider0, 1.0f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, stereo, "echo/stereo", fHslider2, 0.0f, 0.0f, 1.0f, 0.001f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

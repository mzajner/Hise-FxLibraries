/* ------------------------------------------------------------
author: "Albert Graef"
name: "flanger -- stereo flanger with feedback"
version: "1.0"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _FlangerFeedback -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___FlangerFeedback_H__
#define  ___FlangerFeedback_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _FlangerFeedback
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

struct _FlangerFeedbackSIG0 {
	int iRec6[2];
	
	int getNumInputs_FlangerFeedbackSIG0() {
		return 0;
	}
	int getNumOutputs_FlangerFeedbackSIG0() {
		return 1;
	}
	
	void instanceInit_FlangerFeedbackSIG0(int sample_rate) {
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			iRec6[l6] = 0;
		}
	}
	
	void fill_FlangerFeedbackSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iRec6[0] = iRec6[1] + 1;
			float fTemp5 = static_cast<float>(iRec6[0] + -1);
			float fTemp6 = 9.58738e-05f * fTemp5;
			float fTemp7 = 0.0001917476f * fTemp5;
			table[i1] = 0.31830987f * (static_cast<float>((0.0f <= fTemp6) & (fTemp6 <= 3.1415927f)) * (fTemp7 + -3.1415927f) + static_cast<float>((3.1415927f < fTemp6) & (fTemp6 <= 6.2831855f)) * (9.424778f - fTemp7));
			iRec6[1] = iRec6[0];
		}
	}

};

static _FlangerFeedbackSIG0* new_FlangerFeedbackSIG0() { return (_FlangerFeedbackSIG0*)new _FlangerFeedbackSIG0(); }
static void delete_FlangerFeedbackSIG0(_FlangerFeedbackSIG0* dsp) { delete dsp; }

static float ftbl0_FlangerFeedbackSIG0[65536];

struct _FlangerFeedback final : public ::faust::dsp {
	
	FAUSTFLOAT fHslider0;
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	float fConst2;
	float fRec1[2];
	int IOTA0;
	float fVec0[65536];
	float fConst3;
	FAUSTFLOAT fHslider2;
	float fRec2[2];
	FAUSTFLOAT fHslider3;
	float fRec3[2];
	float fConst4;
	FAUSTFLOAT fHslider4;
	float fRec5[2];
	float fRec4[2];
	float fRec0[2];
	float fVec1[65536];
	FAUSTFLOAT fHslider5;
	float fRec7[2];
	
	_FlangerFeedback() {
	}
	
	_FlangerFeedback(const _FlangerFeedback&) = default;
	
	virtual ~_FlangerFeedback() = default;
	
	_FlangerFeedback& operator=(const _FlangerFeedback&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Albert Graef");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _FlangerFeedback -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "FlangerFeedback.dsp");
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
		m->declare("name", "flanger -- stereo flanger with feedback");
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
		_FlangerFeedbackSIG0* sig0 = new_FlangerFeedbackSIG0();
		sig0->instanceInit_FlangerFeedbackSIG0(sample_rate);
		sig0->fill_FlangerFeedbackSIG0(65536, ftbl0_FlangerFeedbackSIG0);
		delete_FlangerFeedbackSIG0(sig0);
	}
	
	void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 0.5f * fConst0;
		fConst4 = 1.0f / fConst0;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.01f);
		fHslider2 = static_cast<FAUSTFLOAT>(0.0001f);
		fHslider3 = static_cast<FAUSTFLOAT>(0.0002f);
		fHslider4 = static_cast<FAUSTFLOAT>(2.0f);
		fHslider5 = static_cast<FAUSTFLOAT>(1.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec1[l0] = 0.0f;
		}
		IOTA0 = 0;
		for (int l1 = 0; l1 < 65536; l1 = l1 + 1) {
			fVec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec2[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec3[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec4[l5] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec0[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 65536; l8 = l8 + 1) {
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
	
	_FlangerFeedback* clone() {
		return new _FlangerFeedback(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("flanger");
		ui_interface->addHorizontalSlider("delay", &fHslider2, FAUSTFLOAT(0.0001f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.05f), FAUSTFLOAT(0.0001f));
		ui_interface->addHorizontalSlider("depth", &fHslider3, FAUSTFLOAT(0.0002f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.0001f));
		ui_interface->addHorizontalSlider("feedback", &fHslider1, FAUSTFLOAT(0.01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.95f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("freq", &fHslider4, FAUSTFLOAT(2.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("level", &fHslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("stereo", &fHslider5, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider0)));
		float fSlow1 = 1.0f / (fSlow0 + 1.0f);
		float fSlow2 = fConst1 * std::max<float>(0.0f, std::min<float>(0.95f, static_cast<float>(fHslider1)));
		float fSlow3 = 0.001f * std::max<float>(0.0f, std::min<float>(0.05f, static_cast<float>(fHslider2)));
		float fSlow4 = fConst1 * std::max<float>(0.0f, std::min<float>(0.1f, static_cast<float>(fHslider3)));
		float fSlow5 = fConst1 * std::max<float>(0.0f, std::min<float>(1e+01f, static_cast<float>(fHslider4)));
		float fSlow6 = 0.5f * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider5)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			fRec1[0] = fSlow2 + fConst2 * fRec1[1];
			float fTemp1 = fTemp0 + fRec1[0] * fRec0[1];
			fVec0[IOTA0 & 65535] = fTemp1;
			fRec2[0] = fSlow3 + 0.999f * fRec2[1];
			fRec3[0] = fSlow4 + fConst2 * fRec3[1];
			fRec5[0] = fSlow5 + fConst2 * fRec5[1];
			float fTemp2 = fRec4[1] + fConst4 * fRec5[0];
			fRec4[0] = fTemp2 - std::floor(fTemp2);
			float fTemp3 = 65536.0f * (fRec4[0] - std::floor(fRec4[0]));
			float fTemp4 = std::floor(fTemp3);
			int iTemp8 = static_cast<int>(fTemp4);
			float fTemp9 = fConst3 * fRec2[0] * (fRec3[0] * ((fTemp4 + (1.0f - fTemp3)) * ftbl0_FlangerFeedbackSIG0[iTemp8 & 65535] + (fTemp3 - fTemp4) * ftbl0_FlangerFeedbackSIG0[(iTemp8 + 1) & 65535]) + 1.0f);
			int iTemp10 = static_cast<int>(fTemp9);
			float fTemp11 = static_cast<float>(iTemp10);
			fRec0[0] = fVec0[(IOTA0 - (iTemp10 & 65535)) & 65535] * (fTemp11 + (1.0f - fTemp9)) + (fTemp9 - fTemp11) * fVec0[(IOTA0 - ((iTemp10 + 1) & 65535)) & 65535];
			output0[i0] = static_cast<FAUSTFLOAT>(fSlow1 * (fTemp0 + fSlow0 * fRec0[0]));
			float fTemp12 = static_cast<float>(input1[i0]);
			float fTemp13 = fTemp12 + fRec1[0] * fRec7[1];
			fVec1[IOTA0 & 65535] = fTemp13;
			float fTemp14 = 65536.0f * (fSlow6 + (fRec4[0] - std::floor(fSlow6 + fRec4[0])));
			float fTemp15 = std::floor(fTemp14);
			int iTemp16 = static_cast<int>(fTemp15);
			float fTemp17 = fConst3 * fRec2[0] * (fRec3[0] * ((fTemp15 + (1.0f - fTemp14)) * ftbl0_FlangerFeedbackSIG0[iTemp16 & 65535] + (fTemp14 - fTemp15) * ftbl0_FlangerFeedbackSIG0[(iTemp16 + 1) & 65535]) + 1.0f);
			int iTemp18 = static_cast<int>(fTemp17);
			float fTemp19 = static_cast<float>(iTemp18);
			fRec7[0] = fVec1[(IOTA0 - (iTemp18 & 65535)) & 65535] * (fTemp19 + (1.0f - fTemp17)) + (fTemp17 - fTemp19) * fVec1[(IOTA0 - ((iTemp18 + 1) & 65535)) & 65535];
			output1[i0] = static_cast<FAUSTFLOAT>(fSlow1 * (fTemp12 + fSlow0 * fRec7[0]));
			fRec1[1] = fRec1[0];
			IOTA0 = IOTA0 + 1;
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec0[1] = fRec0[0];
			fRec7[1] = fRec7[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "FlangerFeedback.dsp"
	#define FAUST_CLASS_NAME "_FlangerFeedback"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _FlangerFeedback -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 6
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("flanger/delay", fHslider2, 0.0001f, 0.0f, 0.05f, 0.0001f);
	FAUST_ADDHORIZONTALSLIDER("flanger/depth", fHslider3, 0.0002f, 0.0f, 0.1f, 0.0001f);
	FAUST_ADDHORIZONTALSLIDER("flanger/feedback", fHslider1, 0.01f, 0.0f, 0.95f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("flanger/freq", fHslider4, 2.0f, 0.0f, 1e+01f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("flanger/level", fHslider0, 1.0f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("flanger/stereo", fHslider5, 1.0f, 0.0f, 1.0f, 0.001f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, delay, "flanger/delay", fHslider2, 0.0001f, 0.0f, 0.05f, 0.0001f) \
		p(HORIZONTALSLIDER, depth, "flanger/depth", fHslider3, 0.0002f, 0.0f, 0.1f, 0.0001f) \
		p(HORIZONTALSLIDER, feedback, "flanger/feedback", fHslider1, 0.01f, 0.0f, 0.95f, 0.001f) \
		p(HORIZONTALSLIDER, freq, "flanger/freq", fHslider4, 2.0f, 0.0f, 1e+01f, 0.01f) \
		p(HORIZONTALSLIDER, level, "flanger/level", fHslider0, 1.0f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, stereo, "flanger/stereo", fHslider5, 1.0f, 0.0f, 1.0f, 0.001f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

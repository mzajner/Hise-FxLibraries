/* ------------------------------------------------------------
name: "QuadraticDistortion"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _QuadraticDistortion -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___QuadraticDistortion_H__
#define  ___QuadraticDistortion_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _QuadraticDistortion
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

static float _QuadraticDistortion_faustpower2_f(float value) {
	return value * value;
}

struct _QuadraticDistortion final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	float fConst3;
	float fRec1[2];
	FAUSTFLOAT fHslider1;
	float fRec2[2];
	float fVec0[2];
	float fRec0[2];
	float fVec1[2];
	float fRec3[2];
	
	_QuadraticDistortion() {
	}
	
	_QuadraticDistortion(const _QuadraticDistortion&) = default;
	
	virtual ~_QuadraticDistortion() = default;
	
	_QuadraticDistortion& operator=(const _QuadraticDistortion&) = default;
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _QuadraticDistortion -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "QuadraticDistortion.dsp");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("filter.lib/version", "1.29");
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
		m->declare("name", "QuadraticDistortion");
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
		fHslider0 = static_cast<FAUSTFLOAT>(35.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.5f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec2[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fVec0[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec0[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fVec1[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec3[l5] = 0.0f;
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
	
	_QuadraticDistortion* clone() {
		return new _QuadraticDistortion(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("QuadraticDistortion");
		ui_interface->declare(&fHslider0, "Hz", "");
		ui_interface->addHorizontalSlider("Break Frequency", &fHslider0, FAUSTFLOAT(35.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("Drive", &fHslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst2 * std::max<float>(2e+01f, std::min<float>(2e+02f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst2 * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider1)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec1[0] = fSlow0 + fConst3 * fRec1[1];
			float fTemp0 = fConst1 * fRec1[0];
			float fTemp1 = 1.0f - fTemp0;
			fRec2[0] = fSlow1 + fConst3 * fRec2[1];
			float fTemp2 = std::pow(1e+01f, 2.0f * fRec2[0]);
			float fTemp3 = static_cast<float>(input0[i0]) * fTemp2;
			int iTemp4 = fTemp3 < 0.0f;
			float fTemp5 = ((iTemp4) ? -fTemp3 : fTemp3);
			float fTemp6 = ((fTemp5 <= 0.33333334f) ? 2.0f * fTemp5 : ((fTemp5 <= 0.6666667f) ? 0.33333334f * (3.0f - _QuadraticDistortion_faustpower2_f(2.0f - 3.0f * fTemp5)) : 1.0f));
			float fTemp7 = ((iTemp4) ? -fTemp6 : fTemp6);
			float fTemp8 = fTemp0 + 1.0f;
			fVec0[0] = fTemp7 / fTemp8;
			fRec0[0] = (fRec0[1] * fTemp1 + fTemp7) / fTemp8 - fVec0[1];
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0[0]);
			float fTemp9 = static_cast<float>(input1[i0]) * fTemp2;
			int iTemp10 = fTemp9 < 0.0f;
			float fTemp11 = ((iTemp10) ? -fTemp9 : fTemp9);
			float fTemp12 = ((fTemp11 <= 0.33333334f) ? 2.0f * fTemp11 : ((fTemp11 <= 0.6666667f) ? 0.33333334f * (3.0f - _QuadraticDistortion_faustpower2_f(2.0f - 3.0f * fTemp11)) : 1.0f));
			float fTemp13 = ((iTemp10) ? -fTemp12 : fTemp12);
			fVec1[0] = fTemp13 / fTemp8;
			fRec3[0] = (fTemp1 * fRec3[1] + fTemp13) / fTemp8 - fVec1[1];
			output1[i0] = static_cast<FAUSTFLOAT>(fRec3[0]);
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fVec0[1] = fVec0[0];
			fRec0[1] = fRec0[0];
			fVec1[1] = fVec1[0];
			fRec3[1] = fRec3[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "QuadraticDistortion.dsp"
	#define FAUST_CLASS_NAME "_QuadraticDistortion"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _QuadraticDistortion -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Break Frequency", fHslider0, 35.0f, 2e+01f, 2e+02f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("Drive", fHslider1, 0.5f, 0.0f, 1.0f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Break_Frequency, "Break Frequency", fHslider0, 35.0f, 2e+01f, 2e+02f, 1.0f) \
		p(HORIZONTALSLIDER, Drive, "Drive", fHslider1, 0.5f, 0.0f, 1.0f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

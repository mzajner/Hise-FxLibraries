/* ------------------------------------------------------------
author: "Abraham Walters"
copyright: "(c)quid 2021"
license: "BSD"
name: "autopanner"
version: "1.0"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _autoPanner -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___autoPanner_H__
#define  ___autoPanner_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _autoPanner
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

struct _autoPannerSIG0 {
	int iRec1[2];
	
	int getNumInputs_autoPannerSIG0() {
		return 0;
	}
	int getNumOutputs_autoPannerSIG0() {
		return 1;
	}
	
	void instanceInit_autoPannerSIG0(int sample_rate) {
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			iRec1[l1] = 0;
		}
	}
	
	void fill_autoPannerSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iRec1[0] = iRec1[1] + 1;
			table[i1] = std::sin(9.58738e-05f * static_cast<float>(iRec1[0] + -1));
			iRec1[1] = iRec1[0];
		}
	}

};

static _autoPannerSIG0* new_autoPannerSIG0() { return (_autoPannerSIG0*)new _autoPannerSIG0(); }
static void delete_autoPannerSIG0(_autoPannerSIG0* dsp) { delete dsp; }

static float ftbl0_autoPannerSIG0[65536];

struct _autoPanner final : public ::faust::dsp {
	
	FAUSTFLOAT fHslider0;
	float fRec0[2];
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider1;
	float fRec3[2];
	float fRec2[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider2;
	float fRec5[2];
	float fRec4[2];
	
	_autoPanner() {
	}
	
	_autoPanner(const _autoPanner&) = default;
	
	virtual ~_autoPanner() = default;
	
	_autoPanner& operator=(const _autoPanner&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Abraham Walters");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _autoPanner -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("copyright", "(c)quid 2021");
		m->declare("filename", "autoPanner.dsp");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("filter.lib/version", "1.29");
		m->declare("license", "BSD");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/version", "1.0");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "autopanner");
		m->declare("version", "1.0");
	}

	static constexpr int getStaticNumInputs() {
		return 1;
	}
	static constexpr int getStaticNumOutputs() {
		return 2;
	}
	int getNumInputs() {
		return 1;
	}
	int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
		_autoPannerSIG0* sig0 = new_autoPannerSIG0();
		sig0->instanceInit_autoPannerSIG0(sample_rate);
		sig0->fill_autoPannerSIG0(65536, ftbl0_autoPannerSIG0);
		delete_autoPannerSIG0(sig0);
	}
	
	void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = 1.0f / std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(0.1f);
		fHslider1 = static_cast<FAUSTFLOAT>(1.0f);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(1.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec3[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec2[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec4[l5] = 0.0f;
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
	
	_autoPanner* clone() {
		return new _autoPanner(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("autopanner");
		ui_interface->addHorizontalSlider("gain", &fHslider0, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("rate", &fHslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.01f));
		ui_interface->openHorizontalBox("tremolo");
		ui_interface->addHorizontalSlider("depth", &fHslider2, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(15.0f), FAUSTFLOAT(0.01f));
		ui_interface->addCheckButton("enabled", &fCheckbox0);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = 0.001f * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider0)));
		float fSlow1 = 0.001f * std::max<float>(1.0f, std::min<float>(2e+01f, static_cast<float>(fHslider1)));
		float fSlow2 = static_cast<float>(fCheckbox0);
		float fSlow3 = 0.001f * std::max<float>(0.0f, std::min<float>(15.0f, static_cast<float>(fHslider2)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[0] = fSlow0 + 0.999f * fRec0[1];
			float fTemp0 = static_cast<float>(input0[i0]) * fRec0[0];
			fRec3[0] = fSlow1 + 0.999f * fRec3[1];
			float fTemp1 = fRec2[1] + fConst0 * fRec3[0];
			fRec2[0] = fTemp1 - std::floor(fTemp1);
			float fTemp2 = ftbl0_autoPannerSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec2[0]), 65535))];
			fRec5[0] = fSlow3 + 0.999f * fRec5[1];
			float fTemp3 = fRec4[1] + fConst0 * fRec5[0];
			fRec4[0] = fTemp3 - std::floor(fTemp3);
			float fTemp4 = fSlow2 * ftbl0_autoPannerSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec4[0]), 65535))] + 1.0f;
			output0[i0] = static_cast<FAUSTFLOAT>(fTemp0 * (fTemp2 + 1.0f) * fTemp4);
			output1[i0] = static_cast<FAUSTFLOAT>(fTemp0 * fTemp4 * (1.0f - fTemp2));
			fRec0[1] = fRec0[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "autoPanner.dsp"
	#define FAUST_CLASS_NAME "_autoPanner"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _autoPanner -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 1
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 4
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("gain", fHslider0, 0.1f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("rate", fHslider1, 1.0f, 1.0f, 2e+01f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("tremolo/depth", fHslider2, 1.0f, 0.0f, 15.0f, 0.01f);
	FAUST_ADDCHECKBOX("tremolo/enabled", fCheckbox0);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, gain, "gain", fHslider0, 0.1f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, rate, "rate", fHslider1, 1.0f, 1.0f, 2e+01f, 0.01f) \
		p(HORIZONTALSLIDER, depth, "tremolo/depth", fHslider2, 1.0f, 0.0f, 15.0f, 0.01f) \
		p(CHECKBOX, enabled, "tremolo/enabled", fCheckbox0, 0.0f, 0.0f, 1.0f, 1.0f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

/* ------------------------------------------------------------
name: "CubicDistortion"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _CubicDistortion -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___CubicDistortion_H__
#define  ___CubicDistortion_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _CubicDistortion
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

static float _CubicDistortion_faustpower2_f(float value) {
	return value * value;
}

struct _CubicDistortion final : public ::faust::dsp {
	
	FAUSTFLOAT fHslider0;
	float fRec1[2];
	FAUSTFLOAT fHslider1;
	float fRec2[2];
	float fVec0[2];
	float fRec0[2];
	int fSampleRate;
	
	_CubicDistortion() {
	}
	
	_CubicDistortion(const _CubicDistortion&) = default;
	
	virtual ~_CubicDistortion() = default;
	
	_CubicDistortion& operator=(const _CubicDistortion&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _CubicDistortion -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "CubicDistortion.dsp");
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
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "CubicDistortion");
	}

	static constexpr int getStaticNumInputs() {
		return 1;
	}
	static constexpr int getStaticNumOutputs() {
		return 1;
	}
	int getNumInputs() {
		return 1;
	}
	int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.0f);
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
	
	_CubicDistortion* clone() {
		return new _CubicDistortion(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("CubicDistortion");
		ui_interface->addHorizontalSlider("Drive", &fHslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("Offset", &fHslider0, FAUSTFLOAT(0.0f), FAUSTFLOAT(-0.25f), FAUSTFLOAT(0.25f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = 0.001f * std::max<float>(-0.25f, std::min<float>(0.25f, static_cast<float>(fHslider0)));
		float fSlow1 = 0.001f * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider1)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec1[0] = fSlow0 + 0.999f * fRec1[1];
			fRec2[0] = fSlow1 + 0.999f * fRec2[1];
			float fTemp0 = std::max<float>(-1.0f, std::min<float>(1.0f, (static_cast<float>(input0[i0]) + fRec1[0]) * std::pow(1e+01f, 2.0f * fRec2[0])));
			float fTemp1 = fTemp0 * (1.0f - 0.33333334f * _CubicDistortion_faustpower2_f(fTemp0));
			fVec0[0] = fTemp1;
			fRec0[0] = 0.995f * fRec0[1] + fTemp1 - fVec0[1];
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0[0]);
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fVec0[1] = fVec0[0];
			fRec0[1] = fRec0[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "CubicDistortion.dsp"
	#define FAUST_CLASS_NAME "_CubicDistortion"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _CubicDistortion -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 1
	#define FAUST_OUTPUTS 1
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Drive", fHslider1, 0.0f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Offset", fHslider0, 0.0f, -0.25f, 0.25f, 0.001f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Drive, "Drive", fHslider1, 0.0f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, Offset, "Offset", fHslider0, 0.0f, -0.25f, 0.25f, 0.001f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

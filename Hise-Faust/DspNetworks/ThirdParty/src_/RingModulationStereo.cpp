/* ------------------------------------------------------------
name: "RingModulationStereo"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _RingModulationStereo -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___RingModulationStereo_H__
#define  ___RingModulationStereo_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _RingModulationStereo
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

struct _RingModulationStereoSIG0 {
	int iRec2[2];
	
	int getNumInputs_RingModulationStereoSIG0() {
		return 0;
	}
	int getNumOutputs_RingModulationStereoSIG0() {
		return 1;
	}
	
	void instanceInit_RingModulationStereoSIG0(int sample_rate) {
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			iRec2[l2] = 0;
		}
	}
	
	void fill_RingModulationStereoSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iRec2[0] = iRec2[1] + 1;
			table[i1] = std::sin(9.58738e-05f * static_cast<float>(iRec2[0] + -1));
			iRec2[1] = iRec2[0];
		}
	}

};

static _RingModulationStereoSIG0* new_RingModulationStereoSIG0() { return (_RingModulationStereoSIG0*)new _RingModulationStereoSIG0(); }
static void delete_RingModulationStereoSIG0(_RingModulationStereoSIG0* dsp) { delete dsp; }

static float ftbl0_RingModulationStereoSIG0[65536];

struct _RingModulationStereo final : public ::faust::dsp {
	
	FAUSTFLOAT fHslider0;
	float fRec0[2];
	FAUSTFLOAT fHslider1;
	float fRec1[2];
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider2;
	float fRec4[2];
	float fRec3[2];
	
	_RingModulationStereo() {
	}
	
	_RingModulationStereo(const _RingModulationStereo&) = default;
	
	virtual ~_RingModulationStereo() = default;
	
	_RingModulationStereo& operator=(const _RingModulationStereo&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _RingModulationStereo -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "RingModulationStereo.dsp");
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
		m->declare("name", "RingModulationStereo");
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
		_RingModulationStereoSIG0* sig0 = new_RingModulationStereoSIG0();
		sig0->instanceInit_RingModulationStereoSIG0(sample_rate);
		sig0->fill_RingModulationStereoSIG0(65536, ftbl0_RingModulationStereoSIG0);
		delete_RingModulationStereoSIG0(sig0);
	}
	
	void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = 1.0f / std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(2.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec1[l1] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec4[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec3[l4] = 0.0f;
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
	
	_RingModulationStereo* clone() {
		return new _RingModulationStereo(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("RingModulationStereo");
		ui_interface->addHorizontalSlider("depth", &fHslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("freq", &fHslider2, FAUSTFLOAT(2.0f), FAUSTFLOAT(0.001f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("gain", &fHslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = 0.001f * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider0)));
		float fSlow1 = 0.001f * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider1)));
		float fSlow2 = 0.001f * std::max<float>(0.001f, std::min<float>(1e+04f, static_cast<float>(fHslider2)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[0] = fSlow0 + 0.999f * fRec0[1];
			float fTemp0 = static_cast<float>(input0[i0]) * fRec0[0];
			fRec1[0] = fSlow1 + 0.999f * fRec1[1];
			fRec4[0] = fSlow2 + 0.999f * fRec4[1];
			float fTemp1 = fRec3[1] + fConst0 * fRec4[0];
			fRec3[0] = fTemp1 - std::floor(fTemp1);
			float fTemp2 = fRec1[0] * ftbl0_RingModulationStereoSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec3[0]), 65535))] + 1.0f;
			output0[i0] = static_cast<FAUSTFLOAT>(fTemp0 * (1.0f - 0.5f * fTemp2));
			output1[i0] = static_cast<FAUSTFLOAT>(0.5f * fTemp0 * fTemp2);
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "RingModulationStereo.dsp"
	#define FAUST_CLASS_NAME "_RingModulationStereo"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _RingModulationStereo -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 1
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 3
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("depth", fHslider1, 1.0f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("freq", fHslider2, 2.0f, 0.001f, 1e+04f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("gain", fHslider0, 1.0f, 0.0f, 1.0f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, depth, "depth", fHslider1, 1.0f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, freq, "freq", fHslider2, 2.0f, 0.001f, 1e+04f, 0.001f) \
		p(HORIZONTALSLIDER, gain, "gain", fHslider0, 1.0f, 0.0f, 1.0f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

/* ------------------------------------------------------------
author: "MNTRA.io"
name: "Hard Clipping"
version: "1.0"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _WaveshapeHardClipDistortion -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___WaveshapeHardClipDistortion_H__
#define  ___WaveshapeHardClipDistortion_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _WaveshapeHardClipDistortion
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

static float _WaveshapeHardClipDistortion_faustpower2_f(float value) {
	return value * value;
}

struct _WaveshapeHardClipDistortion final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider0;
	float fConst1;
	float fRec0[2];
	FAUSTFLOAT fHslider1;
	float fRec1[2];
	
	_WaveshapeHardClipDistortion() {
	}
	
	_WaveshapeHardClipDistortion(const _WaveshapeHardClipDistortion&) = default;
	
	virtual ~_WaveshapeHardClipDistortion() = default;
	
	_WaveshapeHardClipDistortion& operator=(const _WaveshapeHardClipDistortion&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "MNTRA.io");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _WaveshapeHardClipDistortion -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "WaveshapeHardClipDistortion.dsp");
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
		m->declare("name", "Hard Clipping");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("version", "1.0");
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
		fConst0 = 44.1f / std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = 1.0f - fConst0;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(5e+01f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec1[l1] = 0.0f;
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
	
	_WaveshapeHardClipDistortion* clone() {
		return new _WaveshapeHardClipDistortion(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("distortion");
		ui_interface->addHorizontalSlider("distortion", &fHslider1, FAUSTFLOAT(5e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.1f));
		ui_interface->addHorizontalSlider("gain", &fHslider0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(24.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = fConst0 * std::max<float>(0.0f, std::min<float>(24.0f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst0 * std::max<float>(0.0f, std::min<float>(1e+02f, static_cast<float>(fHslider1)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			fRec0[0] = fSlow0 + fConst1 * fRec0[1];
			float fTemp1 = std::fabs(fTemp0);
			fRec1[0] = fSlow1 + fConst1 * fRec1[1];
			float fTemp2 = std::pow(1e+01f, 0.05f * fRec1[0]);
			output0[i0] = static_cast<FAUSTFLOAT>(fTemp0 * std::pow(1e+01f, 0.05f * fRec0[0]) * (fTemp1 + fTemp2) / (std::sqrt(fRec1[0] + 1.0f) * (_WaveshapeHardClipDistortion_faustpower2_f(fTemp0) + fTemp1 * (fTemp2 + -1.0f) + 1.0f)));
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "WaveshapeHardClipDistortion.dsp"
	#define FAUST_CLASS_NAME "_WaveshapeHardClipDistortion"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _WaveshapeHardClipDistortion -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 1
	#define FAUST_OUTPUTS 1
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("distortion/distortion", fHslider1, 5e+01f, 0.0f, 1e+02f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("distortion/gain", fHslider0, 0.0f, 0.0f, 24.0f, 0.1f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, distortion, "distortion/distortion", fHslider1, 5e+01f, 0.0f, 1e+02f, 0.1f) \
		p(HORIZONTALSLIDER, gain, "distortion/gain", fHslider0, 0.0f, 0.0f, 24.0f, 0.1f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

/* ------------------------------------------------------------
name: "Comb Filter"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _FilterComb -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___FilterComb_H__
#define  ___FilterComb_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _FilterComb
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


struct _FilterComb final : public ::faust::dsp {
	
	int IOTA0;
	float fVec0[131072];
	FAUSTFLOAT fHslider0;
	float fRec0[2];
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider1;
	float fRec2[2];
	float fRec1[2];
	
	_FilterComb() {
	}
	
	_FilterComb(const _FilterComb&) = default;
	
	virtual ~_FilterComb() = default;
	
	_FilterComb& operator=(const _FilterComb&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _FilterComb -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.2.0");
		m->declare("filename", "FilterComb.dsp");
		m->declare("filters.lib/ff_fcomb:author", "Julius O. Smith III");
		m->declare("filters.lib/ff_fcomb:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/ff_fcomb:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "Comb Filter");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
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
		fConst0 = 0.01f * std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(8e+01f);
		fHslider1 = static_cast<FAUSTFLOAT>(2.5e+03f);
	}
	
	void instanceClear() {
		IOTA0 = 0;
		for (int l0 = 0; l0 < 131072; l0 = l0 + 1) {
			fVec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec2[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec1[l3] = 0.0f;
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
	
	_FilterComb* clone() {
		return new _FilterComb(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("CombFilter");
		ui_interface->declare(&fHslider1, "acc", "0 1 -10 0 10");
		ui_interface->addHorizontalSlider("Frequency", &fHslider1, FAUSTFLOAT(2.5e+03f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider0, "acc", "1 0 -10 0 10");
		ui_interface->addHorizontalSlider("Intensity", &fHslider0, FAUSTFLOAT(8e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(95.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = 0.0001f * std::max<float>(0.0f, std::min<float>(95.0f, static_cast<float>(fHslider0)));
		float fSlow1 = 0.01f / std::max<float>(1e+02f, std::min<float>(2e+04f, static_cast<float>(fHslider1)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			fVec0[IOTA0 & 131071] = fTemp0;
			fRec0[0] = fSlow0 + 0.99f * fRec0[1];
			fRec2[0] = fSlow1 + 0.99f * fRec2[1];
			fRec1[0] = fConst0 * fRec2[0] + 0.99f * fRec1[1];
			int iTemp1 = static_cast<int>(fRec1[0]);
			float fTemp2 = std::floor(fRec1[0]);
			output0[i0] = static_cast<FAUSTFLOAT>(fTemp0 + std::max<float>(0.0f, std::min<float>(0.999f, fRec0[0])) * (fVec0[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp1))) & 131071] * (fTemp2 + (1.0f - fRec1[0])) + (fRec1[0] - fTemp2) * fVec0[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp1 + 1))) & 131071]));
			IOTA0 = IOTA0 + 1;
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "FilterComb.dsp"
	#define FAUST_CLASS_NAME "_FilterComb"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _FilterComb -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 1
	#define FAUST_OUTPUTS 1
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("CombFilter/Frequency", fHslider1, 2.5e+03f, 1e+02f, 2e+04f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("CombFilter/Intensity", fHslider0, 8e+01f, 0.0f, 95.0f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Frequency, "CombFilter/Frequency", fHslider1, 2.5e+03f, 1e+02f, 2e+04f, 0.001f) \
		p(HORIZONTALSLIDER, Intensity, "CombFilter/Intensity", fHslider0, 8e+01f, 0.0f, 95.0f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

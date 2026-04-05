/* ------------------------------------------------------------
author: "Eric Tarr"
license: "MIT-style STK-4.3 license"
name: "SallenKeyOnePoleLPF"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _SallenKeyBpf -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___SallenKeyBpf_H__
#define  ___SallenKeyBpf_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _SallenKeyBpf
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


struct _SallenKeyBpf final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	float fConst3;
	float fRec3[2];
	FAUSTFLOAT fHslider1;
	float fRec4[2];
	float fRec1[2];
	float fRec2[2];
	float fRec6[2];
	float fRec7[2];
	
	_SallenKeyBpf() {
	}
	
	_SallenKeyBpf(const _SallenKeyBpf&) = default;
	
	virtual ~_SallenKeyBpf() = default;
	
	_SallenKeyBpf& operator=(const _SallenKeyBpf&) = default;
	
	void metadata(Meta* m) { 
		m->declare("SallenKeyBpf.dsp/sallenKey2ndOrder:author", "Eric Tarr");
		m->declare("SallenKeyBpf.dsp/sallenKey2ndOrder:license", "MIT-style STK-4.3 license");
		m->declare("author", "Eric Tarr");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _SallenKeyBpf -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "SallenKeyBpf.dsp");
		m->declare("license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "SallenKeyOnePoleLPF");
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
		fHslider0 = static_cast<FAUSTFLOAT>(1e+03f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.5f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec3[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec4[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec2[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec6[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec7[l5] = 0.0f;
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
	
	_SallenKeyBpf* clone() {
		return new _SallenKeyBpf(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("SallenKeyOnePoleLPF");
		ui_interface->declare(&fHslider0, "cutoff", "");
		ui_interface->addHorizontalSlider("Cutoff Frequency", &fHslider0, FAUSTFLOAT(1e+03f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider1, "Q", "");
		ui_interface->addHorizontalSlider("Q", &fHslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.3f), FAUSTFLOAT(8.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst2 * std::max<float>(2e+01f, std::min<float>(2e+04f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst2 * std::max<float>(0.3f, std::min<float>(8.0f, static_cast<float>(fHslider1)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec3[0] = fSlow0 + fConst3 * fRec3[1];
			float fTemp0 = std::tan(fConst1 * fRec3[0]);
			fRec4[0] = fSlow1 + fConst3 * fRec4[1];
			float fTemp1 = 1.0f / fRec4[0] + fTemp0;
			float fTemp2 = fTemp0 * fTemp1 + 1.0f;
			float fTemp3 = fTemp0 * (static_cast<float>(input0[i0]) - (fRec1[1] + fRec2[1] * fTemp1)) / fTemp2;
			float fTemp4 = fRec2[1] + fTemp3;
			float fRec0 = fTemp4;
			fRec1[0] = fRec1[1] + 2.0f * fTemp0 * fTemp4;
			fRec2[0] = fRec2[1] + 2.0f * fTemp3;
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0);
			float fTemp5 = fTemp0 * (static_cast<float>(input1[i0]) - (fRec6[1] + fTemp1 * fRec7[1])) / fTemp2;
			float fTemp6 = fRec7[1] + fTemp5;
			float fRec5 = fTemp6;
			fRec6[0] = fRec6[1] + 2.0f * fTemp0 * fTemp6;
			fRec7[0] = fRec7[1] + 2.0f * fTemp5;
			output1[i0] = static_cast<FAUSTFLOAT>(fRec5);
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "SallenKeyBpf.dsp"
	#define FAUST_CLASS_NAME "_SallenKeyBpf"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _SallenKeyBpf -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Cutoff Frequency", fHslider0, 1e+03f, 2e+01f, 2e+04f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Q", fHslider1, 0.5f, 0.3f, 8.0f, 0.1f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Cutoff_Frequency, "Cutoff Frequency", fHslider0, 1e+03f, 2e+01f, 2e+04f, 0.1f) \
		p(HORIZONTALSLIDER, Q, "Q", fHslider1, 0.5f, 0.3f, 8.0f, 0.1f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

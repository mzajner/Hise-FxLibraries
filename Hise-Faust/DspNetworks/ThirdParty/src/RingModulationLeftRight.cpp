/* ------------------------------------------------------------
name: "RingModulationLeftRight"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _RingModulationLeftRight -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___RingModulationLeftRight_H__
#define  ___RingModulationLeftRight_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _RingModulationLeftRight
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


struct _RingModulationLeftRight final : public ::faust::dsp {
	
	FAUSTFLOAT fHslider0;
	int iVec0[2];
	float fRec0[2];
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider1;
	float fRec3[2];
	float fRec4[2];
	float fRec2[2];
	float fRec1[2];
	
	_RingModulationLeftRight() {
	}
	
	_RingModulationLeftRight(const _RingModulationLeftRight&) = default;
	
	virtual ~_RingModulationLeftRight() = default;
	
	_RingModulationLeftRight& operator=(const _RingModulationLeftRight&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _RingModulationLeftRight -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "RingModulationLeftRight.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "RingModulationLeftRight");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "1.6.0");
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
		fConst0 = 6.2831855f / std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(5e+01f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.6f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec3[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec4[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec2[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec1[l5] = 0.0f;
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
	
	_RingModulationLeftRight* clone() {
		return new _RingModulationLeftRight(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("RingModulationLeftRight");
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "acc", "1 0 -10 0 10");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->addHorizontalSlider("Modulation Frequency", &fHslider1, FAUSTFLOAT(0.6f), FAUSTFLOAT(0.001f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "acc", "1 0 -10 0 10");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "unit", "%");
		ui_interface->addHorizontalSlider("Modulation intensity", &fHslider0, FAUSTFLOAT(5e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = 1e-05f * std::max<float>(0.0f, std::min<float>(1e+02f, static_cast<float>(fHslider0)));
		float fSlow1 = 0.001f * std::max<float>(0.001f, std::min<float>(1e+04f, static_cast<float>(fHslider1)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec0[0] = 1;
			fRec0[0] = fSlow0 + 0.999f * fRec0[1];
			fRec3[0] = fSlow1 + 0.999f * fRec3[1];
			fRec4[0] = fRec4[1] - fConst0 * fRec3[0] * fRec1[1];
			fRec2[0] = fConst0 * fRec3[0] * fRec4[0] + static_cast<float>(1 - iVec0[1]) + fRec2[1];
			fRec1[0] = fRec2[0];
			output0[i0] = static_cast<FAUSTFLOAT>(static_cast<float>(input0[i0]) * (1.0f - fRec0[0] + fRec0[0] * fRec1[0]));
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "RingModulationLeftRight.dsp"
	#define FAUST_CLASS_NAME "_RingModulationLeftRight"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _RingModulationLeftRight -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 1
	#define FAUST_OUTPUTS 1
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Modulation Frequency", fHslider1, 0.6f, 0.001f, 1e+04f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("Modulation intensity", fHslider0, 5e+01f, 0.0f, 1e+02f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Modulation_Frequency, "Modulation Frequency", fHslider1, 0.6f, 0.001f, 1e+04f, 0.001f) \
		p(HORIZONTALSLIDER, Modulation_intensity, "Modulation intensity", fHslider0, 5e+01f, 0.0f, 1e+02f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

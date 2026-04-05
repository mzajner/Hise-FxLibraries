/* ------------------------------------------------------------
name: "PhaseOffset"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _PhaseOffset -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___PhaseOffset_H__
#define  ___PhaseOffset_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _PhaseOffset
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


struct _PhaseOffset final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider0;
	float fConst1;
	float fRec0[2];
	
	_PhaseOffset() {
	}
	
	_PhaseOffset(const _PhaseOffset&) = default;
	
	virtual ~_PhaseOffset() = default;
	
	_PhaseOffset& operator=(const _PhaseOffset&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _PhaseOffset -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "PhaseOffset.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "PhaseOffset");
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
		fConst0 = 44.1f / std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = 1.0f - fConst0;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(1.8e+02f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
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
	
	_PhaseOffset* clone() {
		return new _PhaseOffset(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("PhaseOffset");
		ui_interface->addHorizontalSlider("Phase Offset", &fHslider0, FAUSTFLOAT(1.8e+02f), FAUSTFLOAT(0.0f), FAUSTFLOAT(3.6e+02f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = fConst0 * std::max<float>(0.0f, std::min<float>(3.6e+02f, static_cast<float>(fHslider0)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[0] = fSlow0 + fConst1 * fRec0[1];
			output0[i0] = static_cast<FAUSTFLOAT>(static_cast<float>(input0[i0]) * std::cos(0.017453292f * fRec0[0]));
			fRec0[1] = fRec0[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "PhaseOffset.dsp"
	#define FAUST_CLASS_NAME "_PhaseOffset"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _PhaseOffset -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 1
	#define FAUST_OUTPUTS 1
	#define FAUST_ACTIVES 1
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Phase Offset", fHslider0, 1.8e+02f, 0.0f, 3.6e+02f, 0.1f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Phase_Offset, "Phase Offset", fHslider0, 1.8e+02f, 0.0f, 3.6e+02f, 0.1f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

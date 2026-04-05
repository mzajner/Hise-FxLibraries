/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2007"
license: "BSD"
name: "stereoEcho"
version: "1.0"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _stereoEcho -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___stereoEcho_H__
#define  ___stereoEcho_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _stereoEcho
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


struct _stereoEcho final : public ::faust::dsp {
	
	FAUSTFLOAT fHslider0;
	int IOTA0;
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider1;
	float fRec0[131072];
	float fRec1[131072];
	
	_stereoEcho() {
	}
	
	_stereoEcho(const _stereoEcho&) = default;
	
	virtual ~_stereoEcho() = default;
	
	_stereoEcho& operator=(const _stereoEcho&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _stereoEcho -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("copyright", "(c)GRAME 2007");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.2.0");
		m->declare("filename", "stereoEcho.dsp");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.5.1");
		m->declare("name", "stereoEcho");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
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
	}
	
	void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = 0.001f * std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.0f);
	}
	
	void instanceClear() {
		IOTA0 = 0;
		for (int l0 = 0; l0 < 131072; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 131072; l1 = l1 + 1) {
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
	
	_stereoEcho* clone() {
		return new _stereoEcho(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("stereo echo");
		ui_interface->openVerticalBox("echo 1000");
		ui_interface->addHorizontalSlider("feedback", &fHslider0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.1f));
		ui_interface->addHorizontalSlider("millisecond", &fHslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = 0.01f * std::max<float>(0.0f, std::min<float>(1e+02f, static_cast<float>(fHslider0)));
		int iSlow1 = std::min<int>(65536, std::max<int>(0, static_cast<int>(fConst0 * std::max<float>(0.0f, std::min<float>(1e+03f, static_cast<float>(fHslider1)))) + -1)) + 1;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[IOTA0 & 131071] = static_cast<float>(input0[i0]) + fSlow0 * fRec0[(IOTA0 - iSlow1) & 131071];
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0[IOTA0 & 131071]);
			fRec1[IOTA0 & 131071] = static_cast<float>(input1[i0]) + fSlow0 * fRec1[(IOTA0 - iSlow1) & 131071];
			output1[i0] = static_cast<FAUSTFLOAT>(fRec1[IOTA0 & 131071]);
			IOTA0 = IOTA0 + 1;
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "stereoEcho.dsp"
	#define FAUST_CLASS_NAME "_stereoEcho"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _stereoEcho -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("stereo echo/echo 1000/feedback", fHslider0, 0.0f, 0.0f, 1e+02f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("stereo echo/echo 1000/millisecond", fHslider1, 0.0f, 0.0f, 1e+03f, 0.1f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, feedback, "stereo echo/echo 1000/feedback", fHslider0, 0.0f, 0.0f, 1e+02f, 0.1f) \
		p(HORIZONTALSLIDER, millisecond, "stereo echo/echo 1000/millisecond", fHslider1, 0.0f, 0.0f, 1e+03f, 0.1f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

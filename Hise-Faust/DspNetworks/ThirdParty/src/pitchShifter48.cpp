/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "pitchShifter"
version: "1.0"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _pitchShifter48 -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___pitchShifter48_H__
#define  ___pitchShifter48_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _pitchShifter48
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


struct _pitchShifter48 final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider0;
	float fConst1;
	float fRec1[2];
	FAUSTFLOAT fHslider1;
	float fRec2[2];
	float fRec0[2];
	FAUSTFLOAT fHslider2;
	float fRec3[2];
	int IOTA0;
	float fVec0[131072];
	float fVec1[131072];
	
	_pitchShifter48() {
	}
	
	_pitchShifter48(const _pitchShifter48&) = default;
	
	virtual ~_pitchShifter48() = default;
	
	_pitchShifter48& operator=(const _pitchShifter48&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _pitchShifter48 -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.2.0");
		m->declare("filename", "pitchShifter48.dsp");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.5.1");
		m->declare("name", "pitchShifter");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
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
		fConst0 = 44.1f / std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = 1.0f - fConst0;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(1e+03f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(2.5e+02f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec2[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec0[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec3[l3] = 0.0f;
		}
		IOTA0 = 0;
		for (int l4 = 0; l4 < 131072; l4 = l4 + 1) {
			fVec0[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 131072; l5 = l5 + 1) {
			fVec1[l5] = 0.0f;
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
	
	_pitchShifter48* clone() {
		return new _pitchShifter48(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Pitch Shifter");
		ui_interface->addHorizontalSlider("shift (semitones)", &fHslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(-48.0f), FAUSTFLOAT(48.0f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("window (samples)", &fHslider0, FAUSTFLOAT(1e+03f), FAUSTFLOAT(5e+01f), FAUSTFLOAT(9.6e+04f), FAUSTFLOAT(1.0f));
		ui_interface->addHorizontalSlider("xfade (samples)", &fHslider2, FAUSTFLOAT(2.5e+02f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst0 * std::max<float>(5e+01f, std::min<float>(9.6e+04f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst0 * std::max<float>(-48.0f, std::min<float>(48.0f, static_cast<float>(fHslider1)));
		float fSlow2 = fConst0 * std::max<float>(1e+02f, std::min<float>(1e+03f, static_cast<float>(fHslider2)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec1[0] = fSlow0 + fConst1 * fRec1[1];
			fRec2[0] = fSlow1 + fConst1 * fRec2[1];
			fRec0[0] = std::fmod(fRec1[0] + fRec0[1] + (1.0f - std::pow(2.0f, 0.083333336f * fRec2[0])), fRec1[0]);
			fRec3[0] = fSlow2 + fConst1 * fRec3[1];
			float fTemp0 = std::min<float>(fRec0[0] / fRec3[0], 1.0f);
			float fTemp1 = static_cast<float>(input0[i0]);
			fVec0[IOTA0 & 131071] = fTemp1;
			int iTemp2 = static_cast<int>(fRec0[0]);
			int iTemp3 = std::min<int>(65537, std::max<int>(0, iTemp2));
			float fTemp4 = std::floor(fRec0[0]);
			float fTemp5 = fTemp4 + (1.0f - fRec0[0]);
			float fTemp6 = fRec0[0] - fTemp4;
			int iTemp7 = std::min<int>(65537, std::max<int>(0, iTemp2 + 1));
			float fTemp8 = 1.0f - fTemp0;
			float fTemp9 = fRec1[0] + fRec0[0];
			int iTemp10 = static_cast<int>(fTemp9);
			int iTemp11 = std::min<int>(65537, std::max<int>(0, iTemp10));
			float fTemp12 = std::floor(fTemp9);
			float fTemp13 = fTemp12 + (1.0f - fTemp9);
			float fTemp14 = fTemp9 - fTemp12;
			int iTemp15 = std::min<int>(65537, std::max<int>(0, iTemp10 + 1));
			output0[i0] = static_cast<FAUSTFLOAT>(fTemp0 * (fVec0[(IOTA0 - iTemp3) & 131071] * fTemp5 + fTemp6 * fVec0[(IOTA0 - iTemp7) & 131071]) + fTemp8 * (fVec0[(IOTA0 - iTemp11) & 131071] * fTemp13 + fTemp14 * fVec0[(IOTA0 - iTemp15) & 131071]));
			float fTemp16 = static_cast<float>(input1[i0]);
			fVec1[IOTA0 & 131071] = fTemp16;
			output1[i0] = static_cast<FAUSTFLOAT>(fTemp0 * (fVec1[(IOTA0 - iTemp3) & 131071] * fTemp5 + fTemp6 * fVec1[(IOTA0 - iTemp7) & 131071]) + fTemp8 * (fTemp13 * fVec1[(IOTA0 - iTemp11) & 131071] + fTemp14 * fVec1[(IOTA0 - iTemp15) & 131071]));
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
			fRec3[1] = fRec3[0];
			IOTA0 = IOTA0 + 1;
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "pitchShifter48.dsp"
	#define FAUST_CLASS_NAME "_pitchShifter48"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _pitchShifter48 -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 3
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Pitch Shifter/shift (semitones)", fHslider1, 0.0f, -48.0f, 48.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("Pitch Shifter/window (samples)", fHslider0, 1e+03f, 5e+01f, 9.6e+04f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("Pitch Shifter/xfade (samples)", fHslider2, 2.5e+02f, 1e+02f, 1e+03f, 1.0f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, shift_(semitones), "Pitch Shifter/shift (semitones)", fHslider1, 0.0f, -48.0f, 48.0f, 0.001f) \
		p(HORIZONTALSLIDER, window_(samples), "Pitch Shifter/window (samples)", fHslider0, 1e+03f, 5e+01f, 9.6e+04f, 1.0f) \
		p(HORIZONTALSLIDER, xfade_(samples), "Pitch Shifter/xfade (samples)", fHslider2, 2.5e+02f, 1e+02f, 1e+03f, 1.0f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

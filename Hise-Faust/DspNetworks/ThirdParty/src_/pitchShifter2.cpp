/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "pitch-shifter"
version: "1.0"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _pitchShifter2 -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___pitchShifter2_H__
#define  ___pitchShifter2_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _pitchShifter2
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


struct _pitchShifter2 final : public ::faust::dsp {
	
	FAUSTFLOAT fHslider0;
	int IOTA0;
	float fVec0[131072];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fRec0[2];
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider4;
	float fConst1;
	float fRec1[2];
	float fVec1[131072];
	
	_pitchShifter2() {
	}
	
	_pitchShifter2(const _pitchShifter2&) = default;
	
	virtual ~_pitchShifter2() = default;
	
	_pitchShifter2& operator=(const _pitchShifter2&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _pitchShifter2 -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.2.0");
		m->declare("filename", "pitchShifter2.dsp");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.5.1");
		m->declare("name", "pitch-shifter");
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
		fHslider0 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider1 = static_cast<FAUSTFLOAT>(1e+03f);
		fHslider2 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider3 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider4 = static_cast<FAUSTFLOAT>(1e+01f);
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
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 131072; l3 = l3 + 1) {
			fVec1[l3] = 0.0f;
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
	
	_pitchShifter2* clone() {
		return new _pitchShifter2(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("pitch-shifter");
		ui_interface->declare(&fHslider4, "OWL", "PARAMETER_C");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("Crossfade", &fHslider4, FAUSTFLOAT(1e+01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider0, "OWL", "PARAMETER_D");
		ui_interface->addHorizontalSlider("Dry/Wet", &fHslider0, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider2, "OWL", "PARAMETER_A");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("Pitch Shift", &fHslider2, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider3, "OWL", "PARAMETER_E");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("Super Pitch", &fHslider3, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f));
		ui_interface->addHorizontalSlider("window (samples)", &fHslider1, FAUSTFLOAT(1e+03f), FAUSTFLOAT(5e+01f), FAUSTFLOAT(1e+05f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider0)));
		float fSlow1 = 1.0f - fSlow0;
		float fSlow2 = std::max<float>(5e+01f, std::min<float>(1e+05f, static_cast<float>(fHslider1)));
		float fSlow3 = std::pow(2.0f, 0.083333336f * (std::max<float>(-12.0f, std::min<float>(12.0f, static_cast<float>(fHslider2))) + std::max<float>(0.0f, std::min<float>(12.0f, static_cast<float>(fHslider3)))));
		float fSlow4 = fConst0 * std::max<float>(1.0f, std::min<float>(1e+04f, static_cast<float>(fHslider4)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			fVec0[IOTA0 & 131071] = fTemp0;
			fRec0[0] = std::fmod(fSlow2 + (fRec0[1] + 1.0f - fSlow3), fSlow2);
			fRec1[0] = fSlow4 + fConst1 * fRec1[1];
			float fTemp1 = std::min<float>(fRec0[0] / fRec1[0], 1.0f);
			int iTemp2 = static_cast<int>(fRec0[0]);
			int iTemp3 = std::min<int>(65537, std::max<int>(0, iTemp2));
			float fTemp4 = std::floor(fRec0[0]);
			float fTemp5 = 1.0f - fRec0[0];
			float fTemp6 = fTemp4 + fTemp5;
			float fTemp7 = fRec0[0] - fTemp4;
			int iTemp8 = std::min<int>(65537, std::max<int>(0, iTemp2 + 1));
			float fTemp9 = 1.0f - fTemp1;
			float fTemp10 = fSlow2 + fRec0[0];
			int iTemp11 = static_cast<int>(fTemp10);
			int iTemp12 = std::min<int>(65537, std::max<int>(0, iTemp11));
			float fTemp13 = std::floor(fTemp10);
			float fTemp14 = fTemp13 + fTemp5 - fSlow2;
			float fTemp15 = fSlow2 + (fRec0[0] - fTemp13);
			int iTemp16 = std::min<int>(65537, std::max<int>(0, iTemp11 + 1));
			output0[i0] = static_cast<FAUSTFLOAT>(fSlow1 * fTemp0 + fSlow0 * (fTemp1 * (fVec0[(IOTA0 - iTemp3) & 131071] * fTemp6 + fTemp7 * fVec0[(IOTA0 - iTemp8) & 131071]) + fTemp9 * (fVec0[(IOTA0 - iTemp12) & 131071] * fTemp14 + fTemp15 * fVec0[(IOTA0 - iTemp16) & 131071])));
			float fTemp17 = static_cast<float>(input1[i0]);
			fVec1[IOTA0 & 131071] = fTemp17;
			output1[i0] = static_cast<FAUSTFLOAT>(fSlow1 * fTemp17 + fSlow0 * (fTemp1 * (fVec1[(IOTA0 - iTemp3) & 131071] * fTemp6 + fTemp7 * fVec1[(IOTA0 - iTemp8) & 131071]) + fTemp9 * (fTemp14 * fVec1[(IOTA0 - iTemp12) & 131071] + fTemp15 * fVec1[(IOTA0 - iTemp16) & 131071])));
			IOTA0 = IOTA0 + 1;
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "pitchShifter2.dsp"
	#define FAUST_CLASS_NAME "_pitchShifter2"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _pitchShifter2 -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 5
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Crossfade", fHslider4, 1e+01f, 1.0f, 1e+04f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("Dry/Wet", fHslider0, 0.5f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Pitch Shift", fHslider2, 0.0f, -12.0f, 12.0f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("Super Pitch", fHslider3, 0.0f, 0.0f, 12.0f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("window (samples)", fHslider1, 1e+03f, 5e+01f, 1e+05f, 1.0f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Crossfade, "Crossfade", fHslider4, 1e+01f, 1.0f, 1e+04f, 1.0f) \
		p(HORIZONTALSLIDER, Dry/Wet, "Dry/Wet", fHslider0, 0.5f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, Pitch_Shift, "Pitch Shift", fHslider2, 0.0f, -12.0f, 12.0f, 1.0f) \
		p(HORIZONTALSLIDER, Super_Pitch, "Super Pitch", fHslider3, 0.0f, 0.0f, 12.0f, 1.0f) \
		p(HORIZONTALSLIDER, window_(samples), "window (samples)", fHslider1, 1e+03f, 5e+01f, 1e+05f, 1.0f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

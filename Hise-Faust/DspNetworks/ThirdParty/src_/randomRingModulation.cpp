/* ------------------------------------------------------------
name: "Random Ring Modulator"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _randomRingModulation -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___randomRingModulation_H__
#define  ___randomRingModulation_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _randomRingModulation
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


struct _randomRingModulation final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	int iVec0[2];
	float fConst5;
	float fConst6;
	FAUSTFLOAT fHslider0;
	float fVec1[2];
	float fConst7;
	float fRec6[2];
	float fConst8;
	FAUSTFLOAT fHslider1;
	float fVec2[2];
	float fRec9[2];
	float fRec8[2];
	float fVec3[2];
	int iRec10[2];
	float fRec7[2];
	int IOTA0;
	int iVec4[128];
	int iVec5[2];
	int iRec5[2];
	float fRec4[2];
	FAUSTFLOAT fHslider2;
	float fRec11[2];
	float fRec3[2];
	float fRec2[2];
	float fRec12[2];
	float fRec1[2];
	float fRec0[2];
	
	_randomRingModulation() {
	}
	
	_randomRingModulation(const _randomRingModulation&) = default;
	
	virtual ~_randomRingModulation() = default;
	
	_randomRingModulation& operator=(const _randomRingModulation&) = default;
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _randomRingModulation -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "randomRingModulation.dsp");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "Random Ring Modulator");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "1.5.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "1.6.0");
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
		fConst1 = 6.2831855f / fConst0;
		fConst2 = 1.0f / std::tan(9424.778f / fConst0);
		fConst3 = 1.0f / (fConst2 + 1.0f);
		fConst4 = 1.0f - fConst2;
		fConst5 = 1.0f / std::tan(3.1415927f / fConst0);
		fConst6 = 1.0f / (fConst5 + 1.0f);
		fConst7 = 1.0f - fConst5;
		fConst8 = 1.0f / fConst0;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(88.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(4.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(2e+01f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fVec1[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec6[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fVec2[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec9[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec8[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fVec3[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			iRec10[l7] = 0;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec7[l8] = 0.0f;
		}
		IOTA0 = 0;
		for (int l9 = 0; l9 < 128; l9 = l9 + 1) {
			iVec4[l9] = 0;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			iVec5[l10] = 0;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			iRec5[l11] = 0;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec4[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec11[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec3[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec2[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec12[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec1[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec0[l18] = 0.0f;
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
	
	_randomRingModulation* clone() {
		return new _randomRingModulation(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("RandomRingModulation");
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "acc", "2 0 -10 0 10");
		ui_interface->declare(&fHslider2, "scale", "log");
		ui_interface->addHorizontalSlider("Ring Modulation Speed Range", &fHslider2, FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "acc", "0 1 -10 0 10");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("Occurrence Speed (Granulator)", &fHslider1, FAUSTFLOAT(4.0f), FAUSTFLOAT(0.001f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.0001f));
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->declare(&fHslider0, "acc", "0 1 -10 0 10");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "unit", "%");
		ui_interface->addHorizontalSlider("Probability(Granulator)", &fHslider0, FAUSTFLOAT(88.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(1.5e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = std::max<float>(1.0f, std::min<float>(1.5e+02f, static_cast<float>(fHslider0)));
		float fSlow1 = std::max<float>(0.001f, std::min<float>(1e+01f, static_cast<float>(fHslider1)));
		float fSlow2 = 0.01f * std::max<float>(0.0f, std::min<float>(1e+04f, static_cast<float>(fHslider2)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec0[0] = 1;
			fVec1[0] = fSlow0;
			fRec6[0] = fConst6 * (0.01f * (fSlow0 + fVec1[1]) - fConst7 * fRec6[1]);
			fVec2[0] = fSlow1;
			fRec9[0] = -(fConst6 * (fConst7 * fRec9[1] - (fSlow1 + fVec2[1])));
			fRec8[0] = std::fmod(fRec8[1] + fConst8 * fRec9[0], 1.0f);
			float fTemp0 = fRec8[0] + -0.001f;
			fVec3[0] = fTemp0;
			int iTemp1 = (fVec3[1] <= 0.0f) & (fTemp0 > 0.0f);
			iRec10[0] = 1103515245 * iRec10[1] + 12345;
			float fTemp2 = 4.656613e-10f * static_cast<float>(iRec10[0]);
			fRec7[0] = fRec7[1] * static_cast<float>(1 - iTemp1) + std::fabs(fTemp2) * static_cast<float>(iTemp1);
			iVec4[IOTA0 & 127] = fTemp0 < 0.5f;
			int iTemp3 = (fRec6[0] > fRec7[0]) * iVec4[(IOTA0 - 100) & 127];
			iVec5[0] = iTemp3;
			iRec5[0] = (iRec5[1] + 1) * (1 - (static_cast<float>(std::abs(iTemp3 - iVec5[1])) > 0.5f));
			fRec4[0] = (((iRec5[0] + -3) <= 0) ? fTemp2 : fRec4[1]);
			fRec11[0] = fSlow2 + 0.99f * fRec11[1];
			fRec3[0] = 0.01f * fRec4[0] * std::max<float>(1.0f, std::min<float>(1e+04f, fRec11[0])) + 0.99f * fRec3[1];
			fRec2[0] = -(fConst3 * (fConst4 * fRec2[1] - (fRec3[0] + fRec3[1])));
			fRec12[0] = fRec12[1] - fConst1 * fRec2[0] * fRec0[1];
			fRec1[0] = fConst1 * fRec2[0] * fRec12[0] + static_cast<float>(1 - iVec0[1]) + fRec1[1];
			fRec0[0] = fRec1[0];
			output0[i0] = static_cast<FAUSTFLOAT>(static_cast<float>(input0[i0]) * fRec0[0]);
			output1[i0] = static_cast<FAUSTFLOAT>(static_cast<float>(input1[i0]) * fRec0[0]);
			iVec0[1] = iVec0[0];
			fVec1[1] = fVec1[0];
			fRec6[1] = fRec6[0];
			fVec2[1] = fVec2[0];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fVec3[1] = fVec3[0];
			iRec10[1] = iRec10[0];
			fRec7[1] = fRec7[0];
			IOTA0 = IOTA0 + 1;
			iVec5[1] = iVec5[0];
			iRec5[1] = iRec5[0];
			fRec4[1] = fRec4[0];
			fRec11[1] = fRec11[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec12[1] = fRec12[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "randomRingModulation.dsp"
	#define FAUST_CLASS_NAME "_randomRingModulation"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _randomRingModulation -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 3
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("RandomRingModulation/Ring Modulation Speed Range", fHslider2, 2e+01f, 0.0f, 1e+04f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("RandomRingModulation/Occurrence Speed (Granulator)", fHslider1, 4.0f, 0.001f, 1e+01f, 0.0001f);
	FAUST_ADDHORIZONTALSLIDER("RandomRingModulation/Probability(Granulator)", fHslider0, 88.0f, 1.0f, 1.5e+02f, 1.0f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Ring_Modulation_Speed_Range, "RandomRingModulation/Ring Modulation Speed Range", fHslider2, 2e+01f, 0.0f, 1e+04f, 1.0f) \
		p(HORIZONTALSLIDER, Occurrence_Speed_(Granulator), "RandomRingModulation/Occurrence Speed (Granulator)", fHslider1, 4.0f, 0.001f, 1e+01f, 0.0001f) \
		p(HORIZONTALSLIDER, Probability(Granulator), "RandomRingModulation/Probability(Granulator)", fHslider0, 88.0f, 1.0f, 1.5e+02f, 1.0f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

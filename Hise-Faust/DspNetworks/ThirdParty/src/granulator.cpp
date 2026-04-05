/* ------------------------------------------------------------
author: "Adapted from sfIter by Christophe Lebreton"
name: "Granulator"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _granulator -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___granulator_H__
#define  ___granulator_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _granulator
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


struct _granulator final : public ::faust::dsp {
	
	int iRec2[2];
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	float fConst3;
	float fRec4[2];
	float fConst4;
	FAUSTFLOAT fHslider1;
	float fRec7[2];
	float fRec6[2];
	float fVec0[2];
	float fRec5[2];
	int IOTA0;
	int iVec1[128];
	int iVec2[2];
	FAUSTFLOAT fHslider2;
	float fRec8[2];
	float fRec3[2];
	float fRec1[2];
	float fRec0[2];
	float fRec9[2];
	
	_granulator() {
	}
	
	_granulator(const _granulator&) = default;
	
	virtual ~_granulator() = default;
	
	_granulator& operator=(const _granulator&) = default;
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.3.0");
		m->declare("author", "Adapted from sfIter by Christophe Lebreton");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _granulator -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "granulator.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "Granulator");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "1.5.0");
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
		fConst1 = 0.441f / fConst0;
		fConst2 = 44.1f / fConst0;
		fConst3 = 1.0f - fConst2;
		fConst4 = 1.0f / fConst0;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(7e+01f);
		fHslider1 = static_cast<FAUSTFLOAT>(1e+01f);
		fHslider2 = static_cast<FAUSTFLOAT>(2e+02f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iRec2[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec4[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec7[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec6[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fVec0[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec5[l5] = 0.0f;
		}
		IOTA0 = 0;
		for (int l6 = 0; l6 < 128; l6 = l6 + 1) {
			iVec1[l6] = 0;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			iVec2[l7] = 0;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec8[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec3[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec1[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec0[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec9[l12] = 0.0f;
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
	
	_granulator* clone() {
		return new _granulator(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Granulator");
		ui_interface->openHorizontalBox("Granulator");
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "acc", "2 0 -10 0 10");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("Grain Size", &fHslider2, FAUSTFLOAT(2e+02f), FAUSTFLOAT(5.0f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "acc", "0 1 -10 0 10");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("Speed", &fHslider1, FAUSTFLOAT(1e+01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.0001f));
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->declare(&fHslider0, "acc", "1 0 -10 0 10");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "unit", "%");
		ui_interface->addHorizontalSlider("Probability", &fHslider0, FAUSTFLOAT(7e+01f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst1 * std::max<float>(2e+01f, std::min<float>(1e+02f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst2 * std::max<float>(1.0f, std::min<float>(2e+01f, static_cast<float>(fHslider1)));
		float fSlow2 = fConst2 * std::max<float>(5.0f, std::min<float>(1e+04f, static_cast<float>(fHslider2)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iRec2[0] = 1103515245 * iRec2[1] + 12345;
			float fTemp0 = static_cast<float>(iRec2[0]);
			fRec4[0] = fSlow0 + fConst3 * fRec4[1];
			fRec7[0] = fSlow1 + fConst3 * fRec7[1];
			fRec6[0] = std::fmod(fRec6[1] + fConst4 * fRec7[0], 1.0f);
			float fTemp1 = fRec6[0] + -0.001f;
			fVec0[0] = fTemp1;
			int iTemp2 = (fVec0[1] <= 0.0f) & (fTemp1 > 0.0f);
			fRec5[0] = fRec5[1] * static_cast<float>(1 - iTemp2) + std::fabs(4.656613e-10f * fTemp0) * static_cast<float>(iTemp2);
			iVec1[IOTA0 & 127] = fTemp1 < 0.5f;
			int iTemp3 = (fRec4[0] > fRec5[0]) * iVec1[(IOTA0 - 100) & 127];
			iVec2[0] = iTemp3;
			fRec8[0] = fSlow2 + fConst3 * fRec8[1];
			fRec3[0] = fRec3[1] + static_cast<float>((iTemp3 - iVec2[1]) > 0) - static_cast<float>(fRec3[1] > 0.0f) / fRec8[0];
			float fTemp4 = std::fabs(4.656613e-10f * fTemp0 * static_cast<float>(fRec3[0] > 0.0f));
			float fTemp5 = 0.0625f / fRec7[0];
			int iTemp6 = std::fabs(fTemp5) < 1.1920929e-07f;
			float fTemp7 = ((iTemp6) ? 0.0f : std::exp(-(fConst4 / ((iTemp6) ? 1.0f : fTemp5))));
			float fTemp8 = 1.0f - fTemp7;
			fRec1[0] = std::max<float>(fTemp4, fTemp7 * fRec1[1] + fTemp8 * fTemp4);
			fRec0[0] = fRec1[0] * fTemp8 + fTemp7 * fRec0[1];
			output0[i0] = static_cast<FAUSTFLOAT>(static_cast<float>(input0[i0]) * fRec0[0]);
			fRec9[0] = fConst2 * static_cast<float>(input1[i0]) * fRec0[0] + fConst3 * fRec9[1];
			output1[i0] = static_cast<FAUSTFLOAT>(fRec9[0]);
			iRec2[1] = iRec2[0];
			fRec4[1] = fRec4[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fVec0[1] = fVec0[0];
			fRec5[1] = fRec5[0];
			IOTA0 = IOTA0 + 1;
			iVec2[1] = iVec2[0];
			fRec8[1] = fRec8[0];
			fRec3[1] = fRec3[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec9[1] = fRec9[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "granulator.dsp"
	#define FAUST_CLASS_NAME "_granulator"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _granulator -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 3
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Granulator/Granulator/Grain Size", fHslider2, 2e+02f, 5.0f, 1e+04f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("Granulator/Granulator/Speed", fHslider1, 1e+01f, 1.0f, 2e+01f, 0.0001f);
	FAUST_ADDHORIZONTALSLIDER("Granulator/Granulator/Probability", fHslider0, 7e+01f, 2e+01f, 1e+02f, 1.0f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Grain_Size, "Granulator/Granulator/Grain Size", fHslider2, 2e+02f, 5.0f, 1e+04f, 1.0f) \
		p(HORIZONTALSLIDER, Speed, "Granulator/Granulator/Speed", fHslider1, 1e+01f, 1.0f, 2e+01f, 0.0001f) \
		p(HORIZONTALSLIDER, Probability, "Granulator/Granulator/Probability", fHslider0, 7e+01f, 2e+01f, 1e+02f, 1.0f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

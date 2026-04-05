/* ------------------------------------------------------------
author: "Evermind"
name: "Whetstone Transient Shaper"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _TransientShaper -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___TransientShaper_H__
#define  ___TransientShaper_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _TransientShaper
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

static float _TransientShaper_faustpower2_f(float value) {
	return value * value;
}

struct _TransientShaper final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	int IOTA0;
	float fConst4;
	float fConst5;
	FAUSTFLOAT fHslider0;
	float fConst6;
	float fRec4[2];
	float fRec3[3];
	FAUSTFLOAT fHslider1;
	float fRec5[2];
	float fRec2[3];
	float fRec1[8192];
	int iConst7;
	float fRec6[2];
	FAUSTFLOAT fHslider2;
	float fRec7[2];
	FAUSTFLOAT fHslider3;
	float fRec8[2];
	float fRec0[2];
	FAUSTFLOAT fButton0;
	float fVec0[2];
	int iRec9[2];
	FAUSTFLOAT fVbargraph0;
	float fRec10[3];
	float fRec14[3];
	float fRec13[3];
	float fRec12[8192];
	float fRec15[2];
	float fRec11[2];
	float fRec16[3];
	
	_TransientShaper() {
	}
	
	_TransientShaper(const _TransientShaper&) = default;
	
	virtual ~_TransientShaper() = default;
	
	_TransientShaper& operator=(const _TransientShaper&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Evermind");
		m->declare("basics.lib/bypass1:author", "Julius Smith");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/toggle:author", "Vince");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _TransientShaper -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "TransientShaper.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/integrator:author", "Julius O. Smith III");
		m->declare("filters.lib/integrator:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/integrator:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/resonhp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonhp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonhp:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/resonlp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonlp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonlp:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "Whetstone Transient Shaper");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/onePoleSwitching:author", "Jonatan Liljedahl, revised by Dario Sanfilippo");
		m->declare("signals.lib/onePoleSwitching:licence", "STK-4.3");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("spats.lib/name", "Faust Spatialization Library");
		m->declare("spats.lib/version", "1.2.1");
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
		fConst1 = 33.333332f / fConst0;
		fConst2 = std::exp(-fConst1);
		fConst3 = 1.0f - fConst2;
		fConst4 = 3.1415927f / fConst0;
		fConst5 = 44.1f / fConst0;
		fConst6 = 1.0f - fConst5;
		iConst7 = static_cast<int>(std::max<float>(0.0f, 0.03f * fConst0));
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(1e+01f);
		fHslider1 = static_cast<FAUSTFLOAT>(2e+04f);
		fHslider2 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider3 = static_cast<FAUSTFLOAT>(0.0f);
		fButton0 = static_cast<FAUSTFLOAT>(0.0f);
	}
	
	void instanceClear() {
		IOTA0 = 0;
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec4[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 3; l1 = l1 + 1) {
			fRec3[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec5[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 3; l3 = l3 + 1) {
			fRec2[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 8192; l4 = l4 + 1) {
			fRec1[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec6[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec7[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec8[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec0[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fVec0[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			iRec9[l10] = 0;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec10[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 3; l12 = l12 + 1) {
			fRec14[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 3; l13 = l13 + 1) {
			fRec13[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 8192; l14 = l14 + 1) {
			fRec12[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec15[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec11[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 3; l17 = l17 + 1) {
			fRec16[l17] = 0.0f;
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
	
	_TransientShaper* clone() {
		return new _TransientShaper(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Whetstone Transient Shaper");
		ui_interface->declare(&fHslider3, "0", "");
		ui_interface->declare(&fHslider3, "unit", "dB");
		ui_interface->addHorizontalSlider("Attack", &fHslider3, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "unit", "dB");
		ui_interface->addHorizontalSlider("Sustain", &fHslider2, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("Low Cutoff", &fHslider0, FAUSTFLOAT(1e+01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fHslider1, "3", "");
		ui_interface->declare(&fHslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("High Cutoff", &fHslider1, FAUSTFLOAT(2e+04f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(0, "4", "");
		ui_interface->openHorizontalBox("Monitoring");
		ui_interface->declare(&fButton0, "0", "");
		ui_interface->addButton("Monitor selected band", &fButton0);
		ui_interface->declare(&fVbargraph0, "1", "");
		ui_interface->declare(&fVbargraph0, "style", "led");
		ui_interface->addVerticalBargraph("ON", &fVbargraph0, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst5 * std::max<float>(1e+01f, std::min<float>(2e+04f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst5 * std::max<float>(2e+01f, std::min<float>(2e+04f, static_cast<float>(fHslider1)));
		float fSlow2 = fConst5 * std::pow(1e+01f, 0.05f * std::max<float>(-12.0f, std::min<float>(12.0f, static_cast<float>(fHslider2))));
		float fSlow3 = fConst5 * std::pow(1e+01f, 0.05f * std::max<float>(-12.0f, std::min<float>(12.0f, static_cast<float>(fHslider3))));
		float fSlow4 = static_cast<float>(fButton0);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			fRec4[0] = fSlow0 + fConst6 * fRec4[1];
			float fTemp1 = std::tan(fConst4 * fRec4[0]);
			float fTemp2 = 1.0f / fTemp1;
			float fTemp3 = 1.0f - (1.0f - fTemp2) / fTemp1;
			float fTemp4 = 1.0f - 1.0f / _TransientShaper_faustpower2_f(fTemp1);
			float fTemp5 = (fTemp2 + 1.0f) / fTemp1 + 1.0f;
			fRec3[0] = fTemp0 - (fRec3[2] * fTemp3 + 2.0f * fRec3[1] * fTemp4) / fTemp5;
			float fTemp6 = (fRec3[2] + fRec3[0] + 2.0f * fRec3[1]) / fTemp5;
			fRec5[0] = fSlow1 + fConst6 * fRec5[1];
			float fTemp7 = std::tan(fConst4 * fRec5[0]);
			float fTemp8 = 1.0f / fTemp7;
			float fTemp9 = 1.0f - (1.0f - fTemp8) / fTemp7;
			float fTemp10 = 1.0f - 1.0f / _TransientShaper_faustpower2_f(fTemp7);
			float fTemp11 = (fTemp8 + 1.0f) / fTemp7 + 1.0f;
			fRec2[0] = fTemp0 - (fTemp6 + (fRec2[2] * fTemp9 + 2.0f * fRec2[1] * fTemp10) / fTemp11);
			float fTemp12 = fRec2[2] + fRec2[0] + 2.0f * fRec2[1];
			fRec1[IOTA0 & 8191] = fRec1[(IOTA0 - 1) & 8191] + _TransientShaper_faustpower2_f(fTemp12 / fTemp11);
			float fTemp13 = std::sqrt(fConst1 * (fRec1[IOTA0 & 8191] - fRec1[(IOTA0 - iConst7) & 8191]));
			fRec6[0] = fConst3 * fTemp13 + fConst2 * fRec6[1];
			fRec7[0] = fSlow2 + fConst6 * fRec7[1];
			fRec8[0] = fSlow3 + fConst6 * fRec8[1];
			fRec0[0] = fConst3 * (((fTemp13 - fRec6[0]) > 0.0f) ? fRec8[0] : fRec7[0]) + fConst2 * fRec0[1];
			fVec0[0] = fSlow4;
			iRec9[0] = iRec9[1] != ((fSlow4 - fVec0[1]) == 1.0f);
			fVbargraph0 = static_cast<FAUSTFLOAT>(static_cast<float>(iRec9[0]));
			int iTemp14 = fVbargraph0 != 1.0f;
			fRec10[0] = fTemp0 - (fTemp9 * fRec10[2] + 2.0f * fTemp10 * fRec10[1]) / fTemp11;
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0[0] * fTemp12 / fTemp11 + ((iTemp14) ? fTemp0 + fTemp6 - (fRec10[2] + fRec10[0] + 2.0f * fRec10[1]) / fTemp11 : 0.0f));
			float fTemp15 = static_cast<float>(input1[i0]);
			fRec14[0] = fTemp15 - (fTemp3 * fRec14[2] + 2.0f * fTemp4 * fRec14[1]) / fTemp5;
			float fTemp16 = (fRec14[2] + fRec14[0] + 2.0f * fRec14[1]) / fTemp5;
			fRec13[0] = fTemp15 - (fTemp16 + (fTemp9 * fRec13[2] + 2.0f * fTemp10 * fRec13[1]) / fTemp11);
			float fTemp17 = fRec13[2] + fRec13[0] + 2.0f * fRec13[1];
			fRec12[IOTA0 & 8191] = fRec12[(IOTA0 - 1) & 8191] + _TransientShaper_faustpower2_f(fTemp17 / fTemp11);
			float fTemp18 = std::sqrt(fConst1 * (fRec12[IOTA0 & 8191] - fRec12[(IOTA0 - iConst7) & 8191]));
			fRec15[0] = fConst3 * fTemp18 + fConst2 * fRec15[1];
			fRec11[0] = fConst3 * (((fTemp18 - fRec15[0]) > 0.0f) ? fRec8[0] : fRec7[0]) + fConst2 * fRec11[1];
			fRec16[0] = fTemp15 - (fTemp9 * fRec16[2] + 2.0f * fTemp10 * fRec16[1]) / fTemp11;
			output1[i0] = static_cast<FAUSTFLOAT>(fRec11[0] * fTemp17 / fTemp11 + ((iTemp14) ? fTemp15 + fTemp16 - (fRec16[2] + fRec16[0] + 2.0f * fRec16[1]) / fTemp11 : 0.0f));
			IOTA0 = IOTA0 + 1;
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec5[1] = fRec5[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec0[1] = fRec0[0];
			fVec0[1] = fVec0[0];
			iRec9[1] = iRec9[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec15[1] = fRec15[0];
			fRec11[1] = fRec11[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "TransientShaper.dsp"
	#define FAUST_CLASS_NAME "_TransientShaper"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _TransientShaper -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 5
	#define FAUST_PASSIVES 1

	FAUST_ADDHORIZONTALSLIDER("Whetstone Transient Shaper/Attack", fHslider3, 0.0f, -12.0f, 12.0f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Whetstone Transient Shaper/Sustain", fHslider2, 0.0f, -12.0f, 12.0f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Whetstone Transient Shaper/Low Cutoff", fHslider0, 1e+01f, 1e+01f, 2e+04f, 1e+01f);
	FAUST_ADDHORIZONTALSLIDER("Whetstone Transient Shaper/High Cutoff", fHslider1, 2e+04f, 2e+01f, 2e+04f, 1e+01f);
	FAUST_ADDBUTTON("Whetstone Transient Shaper/[4]Monitoring/Monitor selected band", fButton0);
	FAUST_ADDVERTICALBARGRAPH("Whetstone Transient Shaper/[4]Monitoring/ON", fVbargraph0, 0.0f, 1.0f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Attack, "Whetstone Transient Shaper/Attack", fHslider3, 0.0f, -12.0f, 12.0f, 0.1f) \
		p(HORIZONTALSLIDER, Sustain, "Whetstone Transient Shaper/Sustain", fHslider2, 0.0f, -12.0f, 12.0f, 0.1f) \
		p(HORIZONTALSLIDER, Low_Cutoff, "Whetstone Transient Shaper/Low Cutoff", fHslider0, 1e+01f, 1e+01f, 2e+04f, 1e+01f) \
		p(HORIZONTALSLIDER, High_Cutoff, "Whetstone Transient Shaper/High Cutoff", fHslider1, 2e+04f, 2e+01f, 2e+04f, 1e+01f) \
		p(BUTTON, Monitor_selected_band, "Whetstone Transient Shaper/[4]Monitoring/Monitor selected band", fButton0, 0.0f, 0.0f, 1.0f, 1.0f) \

	#define FAUST_LIST_PASSIVES(p) \
		p(VERTICALBARGRAPH, ON, "Whetstone Transient Shaper/[4]Monitoring/ON", fVbargraph0, 0.0, 0.0f, 1.0f, 0.0) \

#endif

#endif

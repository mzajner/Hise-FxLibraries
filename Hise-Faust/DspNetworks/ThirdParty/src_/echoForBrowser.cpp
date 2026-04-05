/* ------------------------------------------------------------
name: "echoForBrowser"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _echoForBrowser -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___echoForBrowser_H__
#define  ___echoForBrowser_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _echoForBrowser
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

static float _echoForBrowser_faustpower2_f(float value) {
	return value * value;
}

struct _echoForBrowser final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fVslider0;
	float fRec0[2];
	float fConst3;
	FAUSTFLOAT fVslider1;
	float fConst4;
	float fRec4[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	float fRec5[2];
	int IOTA0;
	float fRec3[65536];
	FAUSTFLOAT fVslider4;
	float fRec7[2];
	FAUSTFLOAT fVslider5;
	float fRec8[2];
	float fConst5;
	float fRec6[2];
	float fRec1[2];
	FAUSTFLOAT fVslider6;
	float fRec11[2];
	float fRec10[2];
	float fRec12[2];
	float fRec9[2];
	float fRec15[65536];
	float fRec13[2];
	
	_echoForBrowser() {
	}
	
	_echoForBrowser(const _echoForBrowser&) = default;
	
	virtual ~_echoForBrowser() = default;
	
	_echoForBrowser& operator=(const _echoForBrowser&) = default;
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _echoForBrowser -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.2.0");
		m->declare("designer", "Robert A. Moog");
		m->declare("filename", "echoForBrowser.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "echoForBrowser");
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
		fConst1 = std::exp(-(44.12234f / fConst0));
		fConst2 = 1.0f - fConst1;
		fConst3 = 44.1f / fConst0;
		fConst4 = 1.0f - fConst3;
		fConst5 = 6.91f / fConst0;
	}
	
	void instanceResetUserInterface() {
		fVslider0 = static_cast<FAUSTFLOAT>(1.0f);
		fVslider1 = static_cast<FAUSTFLOAT>(0.6f);
		fVslider2 = static_cast<FAUSTFLOAT>(1.0f);
		fVslider3 = static_cast<FAUSTFLOAT>(0.85f);
		fVslider4 = static_cast<FAUSTFLOAT>(0.5f);
		fVslider5 = static_cast<FAUSTFLOAT>(0.5f);
		fVslider6 = static_cast<FAUSTFLOAT>(0.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec4[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec5[l2] = 0.0f;
		}
		IOTA0 = 0;
		for (int l3 = 0; l3 < 65536; l3 = l3 + 1) {
			fRec3[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec7[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec8[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec6[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec1[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec11[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec10[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec12[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec9[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 65536; l12 = l12 + 1) {
			fRec15[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec13[l13] = 0.0f;
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
	
	_echoForBrowser* clone() {
		return new _echoForBrowser(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openHorizontalBox("echoForBrowser");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("Effects");
		ui_interface->declare(0, "4", "");
		ui_interface->openHorizontalBox("Echo");
		ui_interface->declare(0, "0", "");
		ui_interface->openVerticalBox("Knobs");
		ui_interface->declare(&fVslider4, "0", "");
		ui_interface->declare(&fVslider4, "midi", "ctrl 4");
		ui_interface->declare(&fVslider4, "style", "knob");
		ui_interface->addVerticalSlider("Delay", &fVslider4, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.001f), FAUSTFLOAT(0.6816667f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fVslider6, "0", "");
		ui_interface->declare(&fVslider6, "midi", "ctrl 62");
		ui_interface->declare(&fVslider6, "style", "knob");
		ui_interface->addVerticalSlider("Warp", &fVslider6, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fVslider5, "1", "");
		ui_interface->declare(&fVslider5, "midi", "ctrl 60");
		ui_interface->declare(&fVslider5, "style", "knob");
		ui_interface->addVerticalSlider("DelayT60", &fVslider5, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fVslider3, "2", "");
		ui_interface->declare(&fVslider3, "midi", "ctrl 3");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->addVerticalSlider("Feedback", &fVslider3, FAUSTFLOAT(0.85f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.95f), FAUSTFLOAT(0.0001f));
		ui_interface->declare(&fVslider0, "3", "");
		ui_interface->declare(&fVslider0, "midi", "ctrl 2");
		ui_interface->declare(&fVslider0, "style", "knob");
		ui_interface->addVerticalSlider("Amp", &fVslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fVslider1, "5", "");
		ui_interface->declare(&fVslider1, "midi", "ctrl 76");
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->addVerticalSlider("FeedbackSm", &fVslider1, FAUSTFLOAT(0.6f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.6f), FAUSTFLOAT(1e-05f));
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Switches");
		ui_interface->declare(&fVslider2, "7", "");
		ui_interface->declare(&fVslider2, "midi", "ctrl 105");
		ui_interface->declare(&fVslider2, "style", "knob");
		ui_interface->addVerticalSlider("EnableEcho", &fVslider2, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst2 * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fVslider0)));
		float fSlow1 = fConst3 * std::max<float>(0.0f, std::min<float>(0.6f, static_cast<float>(fVslider1)));
		int iSlow2 = static_cast<int>(1.0f - std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fVslider2))));
		float fSlow3 = fConst3 * std::max<float>(0.0f, std::min<float>(0.95f, static_cast<float>(fVslider3)));
		float fSlow4 = 44.1f * std::max<float>(0.001f, std::min<float>(0.6816667f, static_cast<float>(fVslider4)));
		float fSlow5 = fConst3 * std::max<float>(0.0f, std::min<float>(1e+02f, static_cast<float>(fVslider5)));
		float fSlow6 = fConst3 * std::max<float>(-1.0f, std::min<float>(1.0f, static_cast<float>(fVslider6)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[0] = fSlow0 + fConst1 * fRec0[1];
			fRec4[0] = fSlow1 + fConst4 * fRec4[1];
			float fTemp0 = std::pow(2.0f, -(5.997942f * fRec4[0]));
			fRec5[0] = fSlow3 + fConst4 * fRec5[1];
			float fTemp1 = 1.0f - fTemp0;
			fRec3[IOTA0 & 65535] = fTemp0 * (((iSlow2) ? 0.0f : static_cast<float>(input0[i0])) + fRec5[0] * fRec1[1]) + fTemp1 * fRec3[(IOTA0 - 1) & 65535];
			fRec7[0] = fSlow4 + fConst4 * fRec7[1];
			fRec8[0] = fSlow5 + fConst4 * fRec8[1];
			float fTemp2 = (((0.1447178f * fRec8[0]) > 0.0f) ? std::exp(-(fConst5 / fRec8[0])) : 0.0f);
			float fTemp3 = 1.0f - fTemp2;
			float fTemp4 = fRec7[0] * fTemp3;
			fRec6[0] = fTemp4 + fTemp2 * fRec6[1];
			int iTemp5 = static_cast<int>(fRec6[0]);
			int iTemp6 = std::min<int>(32769, std::max<int>(0, iTemp5));
			float fTemp7 = std::floor(fRec6[0]);
			float fTemp8 = fTemp7 + (1.0f - fRec6[0]);
			float fTemp9 = fRec6[0] - fTemp7;
			int iTemp10 = std::min<int>(32769, std::max<int>(0, iTemp5 + 1));
			fRec1[0] = fRec3[(IOTA0 - iTemp6) & 65535] * fTemp8 + fTemp9 * fRec3[(IOTA0 - iTemp10) & 65535];
			fRec11[0] = fSlow6 + fConst4 * fRec11[1];
			fRec10[0] = fRec11[0] * fTemp3 + fTemp2 * fRec10[1];
			fRec12[0] = fTemp2 * fRec12[1];
			fRec9[0] = fTemp4 * (fRec10[0] + _echoForBrowser_faustpower2_f(fRec12[0]) + 1.0f) + fTemp2 * fRec9[1];
			int iTemp11 = static_cast<int>(fRec9[0]);
			int iTemp12 = std::min<int>(32769, std::max<int>(0, iTemp11));
			float fTemp13 = std::floor(fRec9[0]);
			float fTemp14 = fTemp13 + (1.0f - fRec9[0]);
			float fTemp15 = fRec9[0] - fTemp13;
			int iTemp16 = std::min<int>(32769, std::max<int>(0, iTemp11 + 1));
			float fRec2 = fRec3[(IOTA0 - iTemp12) & 65535] * fTemp14 + fTemp15 * fRec3[(IOTA0 - iTemp16) & 65535];
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0[0] * fRec2);
			fRec15[IOTA0 & 65535] = fTemp0 * (((iSlow2) ? 0.0f : static_cast<float>(input1[i0])) + fRec5[0] * fRec13[1]) + fTemp1 * fRec15[(IOTA0 - 1) & 65535];
			fRec13[0] = fTemp8 * fRec15[(IOTA0 - iTemp6) & 65535] + fTemp9 * fRec15[(IOTA0 - iTemp10) & 65535];
			float fRec14 = fTemp14 * fRec15[(IOTA0 - iTemp12) & 65535] + fTemp15 * fRec15[(IOTA0 - iTemp16) & 65535];
			output1[i0] = static_cast<FAUSTFLOAT>(fRec0[0] * fRec14);
			fRec0[1] = fRec0[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			IOTA0 = IOTA0 + 1;
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec6[1] = fRec6[0];
			fRec1[1] = fRec1[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec12[1] = fRec12[0];
			fRec9[1] = fRec9[0];
			fRec13[1] = fRec13[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "echoForBrowser.dsp"
	#define FAUST_CLASS_NAME "_echoForBrowser"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _echoForBrowser -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 7
	#define FAUST_PASSIVES 0

	FAUST_ADDVERTICALSLIDER("[1] Effects/[4] Echo/[0] Knobs/Delay", fVslider4, 0.5f, 0.001f, 0.6816667f, 0.001f);
	FAUST_ADDVERTICALSLIDER("[1] Effects/[4] Echo/[0] Knobs/Warp", fVslider6, 0.0f, -1.0f, 1.0f, 0.001f);
	FAUST_ADDVERTICALSLIDER("[1] Effects/[4] Echo/[0] Knobs/DelayT60", fVslider5, 0.5f, 0.0f, 1e+02f, 0.001f);
	FAUST_ADDVERTICALSLIDER("[1] Effects/[4] Echo/[0] Knobs/Feedback", fVslider3, 0.85f, 0.0f, 0.95f, 0.0001f);
	FAUST_ADDVERTICALSLIDER("[1] Effects/[4] Echo/[0] Knobs/Amp", fVslider0, 1.0f, 0.0f, 1.0f, 0.001f);
	FAUST_ADDVERTICALSLIDER("[1] Effects/[4] Echo/[0] Knobs/FeedbackSm", fVslider1, 0.6f, 0.0f, 0.6f, 1e-05f);
	FAUST_ADDVERTICALSLIDER("[1] Effects/[4] Echo/[1] Switches/EnableEcho", fVslider2, 1.0f, 0.0f, 1.0f, 1.0f);

	#define FAUST_LIST_ACTIVES(p) \
		p(VERTICALSLIDER, Delay, "[1] Effects/[4] Echo/[0] Knobs/Delay", fVslider4, 0.5f, 0.001f, 0.6816667f, 0.001f) \
		p(VERTICALSLIDER, Warp, "[1] Effects/[4] Echo/[0] Knobs/Warp", fVslider6, 0.0f, -1.0f, 1.0f, 0.001f) \
		p(VERTICALSLIDER, DelayT60, "[1] Effects/[4] Echo/[0] Knobs/DelayT60", fVslider5, 0.5f, 0.0f, 1e+02f, 0.001f) \
		p(VERTICALSLIDER, Feedback, "[1] Effects/[4] Echo/[0] Knobs/Feedback", fVslider3, 0.85f, 0.0f, 0.95f, 0.0001f) \
		p(VERTICALSLIDER, Amp, "[1] Effects/[4] Echo/[0] Knobs/Amp", fVslider0, 1.0f, 0.0f, 1.0f, 0.001f) \
		p(VERTICALSLIDER, FeedbackSm, "[1] Effects/[4] Echo/[0] Knobs/FeedbackSm", fVslider1, 0.6f, 0.0f, 0.6f, 1e-05f) \
		p(VERTICALSLIDER, EnableEcho, "[1] Effects/[4] Echo/[1] Switches/EnableEcho", fVslider2, 1.0f, 0.0f, 1.0f, 1.0f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

/* ------------------------------------------------------------
author: "JOS, revised by RM"
name: "phaser"
version: "0.0"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _Phaser -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___Phaser_H__
#define  ___Phaser_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _Phaser
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

static float _Phaser_faustpower2_f(float value) {
	return value * value;
}
static float _Phaser_faustpower3_f(float value) {
	return value * value * value;
}
static float _Phaser_faustpower4_f(float value) {
	return value * value * value * value;
}

struct _Phaser final : public ::faust::dsp {
	
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	int iVec0[2];
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider3;
	float fConst2;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	float fConst3;
	FAUSTFLOAT fHslider7;
	float fRec5[2];
	float fRec6[2];
	float fRec4[3];
	float fRec3[3];
	float fRec2[3];
	float fRec1[3];
	float fRec0[2];
	FAUSTFLOAT fCheckbox2;
	float fRec11[3];
	float fRec10[3];
	float fRec9[3];
	float fRec8[3];
	float fRec7[2];
	
	_Phaser() {
	}
	
	_Phaser(const _Phaser&) = default;
	
	virtual ~_Phaser() = default;
	
	_Phaser& operator=(const _Phaser&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "JOS, revised by RM");
		m->declare("basics.lib/bypass2:author", "Julius Smith");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _Phaser -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("demos.lib/name", "Faust Demos Library");
		m->declare("demos.lib/phaser2_demo:author", "Julius O. Smith III");
		m->declare("demos.lib/phaser2_demo:licence", "MIT");
		m->declare("demos.lib/version", "1.4.0");
		m->declare("description", "Phaser demo application.");
		m->declare("filename", "Phaser.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/nlf2:author", "Julius O. Smith III");
		m->declare("filters.lib/nlf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/nlf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "phaser");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "1.6.0");
		m->declare("phaflangers.lib/name", "Faust Phaser and Flanger Library");
		m->declare("phaflangers.lib/version", "1.1.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "1.2.0");
		m->declare("version", "0.0");
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
		fConst2 = 1.0f / fConst0;
		fConst3 = 6.2831855f / fConst0;
	}
	
	void instanceResetUserInterface() {
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider0 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider3 = static_cast<FAUSTFLOAT>(1e+03f);
		fHslider4 = static_cast<FAUSTFLOAT>(1.5f);
		fHslider5 = static_cast<FAUSTFLOAT>(1e+02f);
		fHslider6 = static_cast<FAUSTFLOAT>(8e+02f);
		fHslider7 = static_cast<FAUSTFLOAT>(0.5f);
		fCheckbox2 = static_cast<FAUSTFLOAT>(0.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec5[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec6[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 3; l3 = l3 + 1) {
			fRec4[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 3; l4 = l4 + 1) {
			fRec3[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 3; l5 = l5 + 1) {
			fRec2[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 3; l6 = l6 + 1) {
			fRec1[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec0[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 3; l8 = l8 + 1) {
			fRec11[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec10[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec9[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec8[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec7[l12] = 0.0f;
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
	
	_Phaser* clone() {
		return new _Phaser(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->declare(0, "tooltip", "Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html");
		ui_interface->openVerticalBox("PHASER2");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the phaser         has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fCheckbox2, "1", "");
		ui_interface->addCheckButton("Invert Internal Phaser Sum", &fCheckbox2);
		ui_interface->declare(&fCheckbox1, "2", "");
		ui_interface->addCheckButton("Vibrato Mode", &fCheckbox1);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider7, "1", "");
		ui_interface->declare(&fHslider7, "style", "knob");
		ui_interface->declare(&fHslider7, "unit", "Hz");
		ui_interface->addHorizontalSlider("Speed", &fHslider7, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("Notch Depth (Intensity)", &fHslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider2, "3", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("Feedback Gain", &fHslider2, FAUSTFLOAT(0.0f), FAUSTFLOAT(-0.999f), FAUSTFLOAT(0.999f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider3, "1", "");
		ui_interface->declare(&fHslider3, "scale", "log");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->declare(&fHslider3, "unit", "Hz");
		ui_interface->addHorizontalSlider("Notch width", &fHslider3, FAUSTFLOAT(1e+03f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(5e+03f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->declare(&fHslider5, "scale", "log");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->declare(&fHslider5, "unit", "Hz");
		ui_interface->addHorizontalSlider("Min Notch1 Freq", &fHslider5, FAUSTFLOAT(1e+02f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(5e+03f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider6, "3", "");
		ui_interface->declare(&fHslider6, "scale", "log");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->declare(&fHslider6, "unit", "Hz");
		ui_interface->addHorizontalSlider("Max Notch1 Freq", &fHslider6, FAUSTFLOAT(8e+02f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider4, "4", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("Notch Freq Ratio: NotchFreq(n+1)/NotchFreq(n)", &fHslider4, FAUSTFLOAT(1.5f), FAUSTFLOAT(1.1f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Phaser Output Level", &fHslider0, FAUSTFLOAT(0.0f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		int iSlow0 = static_cast<int>(static_cast<float>(fCheckbox0));
		float fSlow1 = std::pow(1e+01f, 0.05f * std::max<float>(-6e+01f, std::min<float>(1e+01f, static_cast<float>(fHslider0))));
		float fSlow2 = 0.5f * ((static_cast<int>(static_cast<float>(fCheckbox1))) ? 2.0f : std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider1))));
		float fSlow3 = 1.0f - fSlow2;
		float fSlow4 = std::max<float>(-0.999f, std::min<float>(0.999f, static_cast<float>(fHslider2)));
		float fSlow5 = std::exp(-(fConst1 * std::max<float>(1e+01f, std::min<float>(5e+03f, static_cast<float>(fHslider3)))));
		float fSlow6 = 2.0f * fSlow5;
		float fSlow7 = std::max<float>(1.1f, std::min<float>(4.0f, static_cast<float>(fHslider4)));
		float fSlow8 = fConst2 * fSlow7;
		float fSlow9 = std::max<float>(2e+01f, std::min<float>(5e+03f, static_cast<float>(fHslider5)));
		float fSlow10 = 6.2831855f * fSlow9;
		float fSlow11 = 3.1415927f * (fSlow9 - std::max<float>(fSlow9, std::max<float>(2e+01f, std::min<float>(1e+04f, static_cast<float>(fHslider6)))));
		float fSlow12 = fConst3 * std::max<float>(0.0f, std::min<float>(1e+01f, static_cast<float>(fHslider7)));
		float fSlow13 = std::sin(fSlow12);
		float fSlow14 = std::cos(fSlow12);
		float fSlow15 = _Phaser_faustpower2_f(fSlow5);
		float fSlow16 = fConst2 * _Phaser_faustpower2_f(fSlow7);
		float fSlow17 = fConst2 * _Phaser_faustpower3_f(fSlow7);
		float fSlow18 = fConst2 * _Phaser_faustpower4_f(fSlow7);
		float fSlow19 = ((static_cast<int>(static_cast<float>(fCheckbox2))) ? -fSlow2 : fSlow2);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			float fTemp1 = ((iSlow0) ? 0.0f : fTemp0);
			iVec0[0] = 1;
			fRec5[0] = fSlow13 * fRec6[1] + fSlow14 * fRec5[1];
			fRec6[0] = static_cast<float>(1 - iVec0[1]) + fSlow14 * fRec6[1] - fSlow13 * fRec5[1];
			float fTemp2 = fSlow10 - fSlow11 * (1.0f - fRec5[0]);
			float fTemp3 = fRec4[1] * std::cos(fSlow8 * fTemp2);
			fRec4[0] = fSlow1 * fTemp1 + fSlow4 * fRec0[1] + fSlow6 * fTemp3 - fSlow15 * fRec4[2];
			float fTemp4 = fRec3[1] * std::cos(fSlow16 * fTemp2);
			fRec3[0] = fRec4[2] + fSlow15 * (fRec4[0] - fRec3[2]) - fSlow6 * (fTemp3 - fTemp4);
			float fTemp5 = fRec2[1] * std::cos(fSlow17 * fTemp2);
			fRec2[0] = fRec3[2] + fSlow15 * (fRec3[0] - fRec2[2]) - fSlow6 * (fTemp4 - fTemp5);
			float fTemp6 = fRec1[1] * std::cos(fSlow18 * fTemp2);
			fRec1[0] = fRec2[2] + fSlow15 * (fRec2[0] - fRec1[2]) - fSlow6 * (fTemp5 - fTemp6);
			fRec0[0] = fRec1[2] + fSlow15 * fRec1[0] - fSlow6 * fTemp6;
			output0[i0] = static_cast<FAUSTFLOAT>(((iSlow0) ? fTemp0 : fSlow1 * fTemp1 * fSlow3 + fRec0[0] * fSlow19));
			float fTemp7 = static_cast<float>(input1[i0]);
			float fTemp8 = ((iSlow0) ? 0.0f : fTemp7);
			float fTemp9 = fSlow10 - fSlow11 * (1.0f - fRec6[0]);
			float fTemp10 = fRec11[1] * std::cos(fSlow8 * fTemp9);
			fRec11[0] = fSlow1 * fTemp8 + fSlow4 * fRec7[1] + fSlow6 * fTemp10 - fSlow15 * fRec11[2];
			float fTemp11 = fRec10[1] * std::cos(fSlow16 * fTemp9);
			fRec10[0] = fRec11[2] + fSlow15 * (fRec11[0] - fRec10[2]) - fSlow6 * (fTemp10 - fTemp11);
			float fTemp12 = fRec9[1] * std::cos(fSlow17 * fTemp9);
			fRec9[0] = fRec10[2] + fSlow15 * (fRec10[0] - fRec9[2]) - fSlow6 * (fTemp11 - fTemp12);
			float fTemp13 = fRec8[1] * std::cos(fSlow18 * fTemp9);
			fRec8[0] = fRec9[2] + fSlow15 * (fRec9[0] - fRec8[2]) - fSlow6 * (fTemp12 - fTemp13);
			fRec7[0] = fRec8[2] + fSlow15 * fRec8[0] - fSlow6 * fTemp13;
			output1[i0] = static_cast<FAUSTFLOAT>(((iSlow0) ? fTemp7 : fSlow1 * fTemp8 * fSlow3 + fRec7[0] * fSlow19));
			iVec0[1] = iVec0[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "Phaser.dsp"
	#define FAUST_CLASS_NAME "_Phaser"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _Phaser -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 11
	#define FAUST_PASSIVES 0

	FAUST_ADDCHECKBOX("PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[0]/Bypass", fCheckbox0);
	FAUST_ADDCHECKBOX("PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[0]/Invert Internal Phaser Sum", fCheckbox2);
	FAUST_ADDCHECKBOX("PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[0]/Vibrato Mode", fCheckbox1);
	FAUST_ADDHORIZONTALSLIDER("PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[1]/Speed", fHslider7, 0.5f, 0.0f, 1e+01f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[1]/Notch Depth (Intensity)", fHslider1, 1.0f, 0.0f, 1.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[1]/Feedback Gain", fHslider2, 0.0f, -0.999f, 0.999f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[2]/Notch width", fHslider3, 1e+03f, 1e+01f, 5e+03f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[2]/Min Notch1 Freq", fHslider5, 1e+02f, 2e+01f, 5e+03f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[2]/Max Notch1 Freq", fHslider6, 8e+02f, 2e+01f, 1e+04f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[2]/Notch Freq Ratio: NotchFreq(n+1)/NotchFreq(n)", fHslider4, 1.5f, 1.1f, 4.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[3]/Phaser Output Level", fHslider0, 0.0f, -6e+01f, 1e+01f, 0.1f);

	#define FAUST_LIST_ACTIVES(p) \
		p(CHECKBOX, Bypass, "PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[0]/Bypass", fCheckbox0, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(CHECKBOX, Invert_Internal_Phaser_Sum, "PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[0]/Invert Internal Phaser Sum", fCheckbox2, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(CHECKBOX, Vibrato_Mode, "PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[0]/Vibrato Mode", fCheckbox1, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(HORIZONTALSLIDER, Speed, "PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[1]/Speed", fHslider7, 0.5f, 0.0f, 1e+01f, 0.001f) \
		p(HORIZONTALSLIDER, Notch_Depth_(Intensity), "PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[1]/Notch Depth (Intensity)", fHslider1, 1.0f, 0.0f, 1.0f, 0.001f) \
		p(HORIZONTALSLIDER, Feedback_Gain, "PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[1]/Feedback Gain", fHslider2, 0.0f, -0.999f, 0.999f, 0.001f) \
		p(HORIZONTALSLIDER, Notch_width, "PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[2]/Notch width", fHslider3, 1e+03f, 1e+01f, 5e+03f, 1.0f) \
		p(HORIZONTALSLIDER, Min_Notch1_Freq, "PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[2]/Min Notch1 Freq", fHslider5, 1e+02f, 2e+01f, 5e+03f, 1.0f) \
		p(HORIZONTALSLIDER, Max_Notch1_Freq, "PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[2]/Max Notch1 Freq", fHslider6, 8e+02f, 2e+01f, 1e+04f, 1.0f) \
		p(HORIZONTALSLIDER, Notch_Freq_Ratio:_NotchFreq(n+1)/NotchFreq(n), "PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[2]/Notch Freq Ratio: NotchFreq(n+1)/NotchFreq(n)", fHslider4, 1.5f, 1.1f, 4.0f, 0.001f) \
		p(HORIZONTALSLIDER, Phaser_Output_Level, "PHASER2 [tooltip: Reference:         https://ccrma.stanford.edu/~jos/pasp/Flanging.html]/[3]/Phaser Output Level", fHslider0, 0.0f, -6e+01f, 1e+01f, 0.1f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

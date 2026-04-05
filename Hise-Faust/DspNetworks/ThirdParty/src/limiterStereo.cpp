/* ------------------------------------------------------------
name: "limiterStereo"
version: "0.4.0"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _limiterStereo -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___limiterStereo_H__
#define  ___limiterStereo_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _limiterStereo
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


struct _limiterStereo final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fCheckbox0;
	float fConst2;
	float fRec2[2];
	float fConst3;
	FAUSTFLOAT fHslider0;
	float fRec8[2];
	float fRec3[2];
	float fRec4[2];
	float fRec5[2];
	float fRec6[2];
	FAUSTFLOAT fHslider1;
	float fRec9[2];
	int IOTA0;
	float fVec0[32768];
	float fConst4;
	FAUSTFLOAT fHslider2;
	float fRec10[2];
	float fVec1[32768];
	FAUSTFLOAT fHslider3;
	float fRec31[2];
	int iRec29[2];
	float fRec30[2];
	int iRec27[2];
	float fRec28[2];
	int iRec25[2];
	float fRec26[2];
	int iRec23[2];
	float fRec24[2];
	int iRec21[2];
	float fRec22[2];
	int iRec19[2];
	float fRec20[2];
	int iRec17[2];
	float fRec18[2];
	int iRec15[2];
	float fRec16[2];
	float fConst5;
	FAUSTFLOAT fHslider4;
	float fRec32[2];
	float fRec14[2];
	float fRec13[2];
	float fRec12[2];
	float fRec11[2];
	FAUSTFLOAT fVbargraph0;
	float fConst6;
	int iRec0[2];
	float fRec1[2];
	FAUSTFLOAT fVbargraph1;
	float fRec35[2];
	float fRec36[2];
	float fRec37[2];
	float fRec38[2];
	int iRec33[2];
	float fRec34[2];
	FAUSTFLOAT fVbargraph2;
	
	_limiterStereo() {
	}
	
	_limiterStereo(const _limiterStereo&) = default;
	
	virtual ~_limiterStereo() = default;
	
	_limiterStereo& operator=(const _limiterStereo&) = default;
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _limiterStereo -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.2.0");
		m->declare("filename", "limiterStereo.dsp");
		m->declare("limiterStereo.dsp/limiterStereo:author", "Dario Sanfilippo");
		m->declare("limiterStereo.dsp/limiterStereo:copyright", "Copyright (C) 2022 Dario Sanfilippo <sanfilippo.dario@gmail.com>");
		m->declare("limiterStereo.dsp/limiterStereo:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "limiterStereo");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("version", "0.4.0");
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
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 0.125f * fConst0;
		fConst4 = 0.1f * fConst0;
		fConst5 = 14.444787f / fConst0;
		fConst6 = std::rint(3.0f * fConst0);
	}
	
	void instanceResetUserInterface() {
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider0 = static_cast<FAUSTFLOAT>(0.01f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider3 = static_cast<FAUSTFLOAT>(0.05f);
		fHslider4 = static_cast<FAUSTFLOAT>(0.15f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec2[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec8[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec3[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec4[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec6[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec9[l6] = 0.0f;
		}
		IOTA0 = 0;
		for (int l7 = 0; l7 < 32768; l7 = l7 + 1) {
			fVec0[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec10[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 32768; l9 = l9 + 1) {
			fVec1[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec31[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			iRec29[l11] = 0;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec30[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			iRec27[l13] = 0;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec28[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			iRec25[l15] = 0;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec26[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			iRec23[l17] = 0;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec24[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			iRec21[l19] = 0;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fRec22[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			iRec19[l21] = 0;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fRec20[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			iRec17[l23] = 0;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fRec18[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			iRec15[l25] = 0;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			fRec16[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec32[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			fRec14[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			fRec13[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			fRec12[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec11[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 2; l32 = l32 + 1) {
			iRec0[l32] = 0;
		}
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			fRec1[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			fRec35[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			fRec36[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 2; l36 = l36 + 1) {
			fRec37[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 2; l37 = l37 + 1) {
			fRec38[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 2; l38 = l38 + 1) {
			iRec33[l38] = 0;
		}
		for (int l39 = 0; l39 < 2; l39 = l39 + 1) {
			fRec34[l39] = 0.0f;
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
	
	_limiterStereo* clone() {
		return new _limiterStereo(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openHorizontalBox("Look-ahead IIR Stereo Limiter");
		ui_interface->openVerticalBox("Control");
		ui_interface->declare(&fCheckbox0, "00", "");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fHslider1, "01", "");
		ui_interface->addHorizontalSlider("Pre Gain (dB)", &fHslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.2e+02f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider2, "02", "");
		ui_interface->addHorizontalSlider("Threshold (dB)", &fHslider2, FAUSTFLOAT(0.0f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider0, "03", "");
		ui_interface->addHorizontalSlider("Attack (s)", &fHslider0, FAUSTFLOAT(0.01f), FAUSTFLOAT(0.001f), FAUSTFLOAT(0.05f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider3, "04", "");
		ui_interface->addHorizontalSlider("Hold (s)", &fHslider3, FAUSTFLOAT(0.05f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider4, "05", "");
		ui_interface->addHorizontalSlider("Release (s)", &fHslider4, FAUSTFLOAT(0.15f), FAUSTFLOAT(0.05f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Display");
		ui_interface->openHorizontalBox("Peaks");
		ui_interface->declare(&fVbargraph1, "06", "");
		ui_interface->declare(&fVbargraph1, "style", "numerical");
		ui_interface->addVerticalBargraph("Left Peak (dB)", &fVbargraph1, FAUSTFLOAT(-6e+01f), FAUSTFLOAT(6e+01f));
		ui_interface->declare(&fVbargraph2, "07", "");
		ui_interface->declare(&fVbargraph2, "style", "numerical");
		ui_interface->addVerticalBargraph("Right Peak (dB)", &fVbargraph2, FAUSTFLOAT(-6e+01f), FAUSTFLOAT(6e+01f));
		ui_interface->closeBox();
		ui_interface->declare(&fVbargraph0, "09", "");
		ui_interface->addVerticalBargraph("Attenuation (dB)", &fVbargraph0, FAUSTFLOAT(-1.2e+02f), FAUSTFLOAT(0.0f));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst1 * static_cast<float>(fCheckbox0);
		float fSlow1 = fConst1 * std::max<float>(0.001f, std::min<float>(0.05f, static_cast<float>(fHslider0)));
		float fSlow2 = fConst1 * std::pow(1e+01f, 0.05f * std::max<float>(0.0f, std::min<float>(1.2e+02f, static_cast<float>(fHslider1))));
		float fSlow3 = fConst1 * std::pow(1e+01f, 0.05f * std::max<float>(-6e+01f, std::min<float>(0.0f, static_cast<float>(fHslider2))));
		float fSlow4 = fConst1 * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider3)));
		float fSlow5 = fConst1 * std::max<float>(0.05f, std::min<float>(1.0f, static_cast<float>(fHslider4)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			fRec2[0] = fSlow0 + fConst2 * fRec2[1];
			int iTemp1 = fRec3[1] == 1.0f;
			fRec8[0] = fSlow1 + fConst2 * fRec8[1];
			float fTemp2 = std::rint(fConst3 * fRec8[0]);
			float fTemp3 = 8.0f * fTemp2;
			int iTemp4 = fRec3[1] == 0.0f;
			float fTemp5 = 0.125f / fTemp2;
			float fTemp6 = ((iTemp1 & (fTemp3 != fRec6[1])) ? -fTemp5 : ((iTemp4 & (fTemp3 != fRec5[1])) ? fTemp5 : fRec4[1]));
			float fTemp7 = std::max<float>(0.0f, std::min<float>(1.0f, fRec3[1] + fTemp6));
			fRec3[0] = fTemp7;
			fRec4[0] = fTemp6;
			float fTemp8 = ((iTemp1) ? fTemp3 : fRec5[1]);
			fRec5[0] = fTemp8;
			float fTemp9 = ((iTemp4) ? fTemp3 : fRec6[1]);
			fRec6[0] = fTemp9;
			fRec9[0] = fSlow2 + fConst2 * fRec9[1];
			float fTemp10 = fTemp0 * fRec9[0];
			fVec0[IOTA0 & 32767] = fTemp10;
			float fRec7 = fVec0[(IOTA0 - static_cast<int>(std::min<float>(fConst4, std::max<float>(0.0f, fTemp8)))) & 32767] * (1.0f - fTemp7) + fTemp7 * fVec0[(IOTA0 - static_cast<int>(std::min<float>(fConst4, std::max<float>(0.0f, fTemp9)))) & 32767];
			fRec10[0] = fSlow3 + fConst2 * fRec10[1];
			float fTemp11 = static_cast<float>(input1[i0]);
			float fTemp12 = fTemp11 * fRec9[0];
			fVec1[IOTA0 & 32767] = fTemp12;
			float fTemp13 = std::fabs(std::max<float>(std::fabs(fTemp10), std::fabs(fTemp12)));
			fRec31[0] = fSlow4 + fConst2 * fRec31[1];
			float fTemp14 = std::rint(fConst3 * (fRec8[0] + fRec31[0]));
			int iTemp15 = (fTemp13 >= fRec30[1]) | (static_cast<float>(iRec29[1]) >= fTemp14);
			iRec29[0] = (1 - iTemp15) * (iRec29[1] + 1);
			fRec30[0] = fRec30[1] + static_cast<float>(iTemp15) * (fTemp13 - fRec30[1]);
			float fTemp16 = std::fabs(fRec30[0]);
			int iTemp17 = (fTemp16 >= fRec28[1]) | (static_cast<float>(iRec27[1]) >= fTemp14);
			iRec27[0] = (1 - iTemp17) * (iRec27[1] + 1);
			fRec28[0] = fRec28[1] + static_cast<float>(iTemp17) * (fTemp16 - fRec28[1]);
			float fTemp18 = std::fabs(fRec28[0]);
			int iTemp19 = (fTemp18 >= fRec26[1]) | (static_cast<float>(iRec25[1]) >= fTemp14);
			iRec25[0] = (1 - iTemp19) * (iRec25[1] + 1);
			fRec26[0] = fRec26[1] + static_cast<float>(iTemp19) * (fTemp18 - fRec26[1]);
			float fTemp20 = std::fabs(fRec26[0]);
			int iTemp21 = (fTemp20 >= fRec24[1]) | (static_cast<float>(iRec23[1]) >= fTemp14);
			iRec23[0] = (1 - iTemp21) * (iRec23[1] + 1);
			fRec24[0] = fRec24[1] + static_cast<float>(iTemp21) * (fTemp20 - fRec24[1]);
			float fTemp22 = std::fabs(fRec24[0]);
			int iTemp23 = (fTemp22 >= fRec22[1]) | (static_cast<float>(iRec21[1]) >= fTemp14);
			iRec21[0] = (1 - iTemp23) * (iRec21[1] + 1);
			fRec22[0] = fRec22[1] + static_cast<float>(iTemp23) * (fTemp22 - fRec22[1]);
			float fTemp24 = std::fabs(fRec22[0]);
			int iTemp25 = (fTemp24 >= fRec20[1]) | (static_cast<float>(iRec19[1]) >= fTemp14);
			iRec19[0] = (1 - iTemp25) * (iRec19[1] + 1);
			fRec20[0] = fRec20[1] + static_cast<float>(iTemp25) * (fTemp24 - fRec20[1]);
			float fTemp26 = std::fabs(fRec20[0]);
			int iTemp27 = (fTemp26 >= fRec18[1]) | (static_cast<float>(iRec17[1]) >= fTemp14);
			iRec17[0] = (1 - iTemp27) * (iRec17[1] + 1);
			fRec18[0] = fRec18[1] + static_cast<float>(iTemp27) * (fTemp26 - fRec18[1]);
			float fTemp28 = std::fabs(fRec18[0]);
			int iTemp29 = (fTemp28 >= fRec16[1]) | (static_cast<float>(iRec15[1]) >= fTemp14);
			iRec15[0] = (1 - iTemp29) * (iRec15[1] + 1);
			fRec16[0] = fRec16[1] + static_cast<float>(iTemp29) * (fTemp28 - fRec16[1]);
			float fTemp30 = std::max<float>(fRec10[0], fRec16[0]);
			fRec32[0] = fSlow5 + fConst2 * fRec32[1];
			float fTemp31 = std::exp(-(fConst5 / fRec32[0]));
			float fTemp32 = std::exp(-(fConst5 / fRec8[0]));
			float fTemp33 = ((fTemp30 > fRec14[1]) ? fTemp32 : fTemp31);
			fRec14[0] = fRec14[1] * fTemp33 + fTemp30 * (1.0f - fTemp33);
			float fTemp34 = ((fRec14[0] > fRec13[1]) ? fTemp32 : fTemp31);
			fRec13[0] = fRec13[1] * fTemp34 + fRec14[0] * (1.0f - fTemp34);
			float fTemp35 = ((fRec13[0] > fRec12[1]) ? fTemp32 : fTemp31);
			fRec12[0] = fRec12[1] * fTemp35 + fRec13[0] * (1.0f - fTemp35);
			float fTemp36 = ((fRec12[0] > fRec11[1]) ? fTemp32 : fTemp31);
			fRec11[0] = fRec11[1] * fTemp36 + fRec12[0] * (1.0f - fTemp36);
			float fTemp37 = fRec10[0] / fRec11[0];
			fVbargraph0 = static_cast<FAUSTFLOAT>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, fTemp37)));
			float fTemp38 = fTemp37;
			float fTemp39 = 1.0f - fRec2[0];
			float fTemp40 = fTemp0 * fRec2[0] + fRec7 * fTemp38 * fTemp39;
			float fTemp41 = std::fabs(fTemp40);
			int iTemp42 = (fTemp41 >= fRec1[1]) | (static_cast<float>(iRec0[1]) >= fConst6);
			iRec0[0] = (1 - iTemp42) * (iRec0[1] + 1);
			fRec1[0] = fRec1[1] + static_cast<float>(iTemp42) * (fTemp41 - fRec1[1]);
			fVbargraph1 = static_cast<FAUSTFLOAT>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, fRec1[0])));
			output0[i0] = static_cast<FAUSTFLOAT>(fTemp40);
			int iTemp43 = fRec35[1] == 1.0f;
			int iTemp44 = fRec35[1] == 0.0f;
			float fTemp45 = ((iTemp43 & (fTemp3 != fRec38[1])) ? -fTemp5 : ((iTemp44 & (fTemp3 != fRec37[1])) ? fTemp5 : fRec36[1]));
			float fTemp46 = std::max<float>(0.0f, std::min<float>(1.0f, fRec35[1] + fTemp45));
			fRec35[0] = fTemp46;
			fRec36[0] = fTemp45;
			float fTemp47 = ((iTemp43) ? fTemp3 : fRec37[1]);
			fRec37[0] = fTemp47;
			float fTemp48 = ((iTemp44) ? fTemp3 : fRec38[1]);
			fRec38[0] = fTemp48;
			float fRec39 = fVec1[(IOTA0 - static_cast<int>(std::min<float>(fConst4, std::max<float>(0.0f, fTemp47)))) & 32767] * (1.0f - fTemp46) + fTemp46 * fVec1[(IOTA0 - static_cast<int>(std::min<float>(fConst4, std::max<float>(0.0f, fTemp48)))) & 32767];
			float fTemp49 = fTemp11 * fRec2[0] + fTemp38 * fRec39 * fTemp39;
			float fTemp50 = std::fabs(fTemp49);
			int iTemp51 = (fTemp50 >= fRec34[1]) | (static_cast<float>(iRec33[1]) >= fConst6);
			iRec33[0] = (1 - iTemp51) * (iRec33[1] + 1);
			fRec34[0] = fRec34[1] + static_cast<float>(iTemp51) * (fTemp50 - fRec34[1]);
			fVbargraph2 = static_cast<FAUSTFLOAT>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, fRec34[0])));
			output1[i0] = static_cast<FAUSTFLOAT>(fTemp49);
			fRec2[1] = fRec2[0];
			fRec8[1] = fRec8[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec9[1] = fRec9[0];
			IOTA0 = IOTA0 + 1;
			fRec10[1] = fRec10[0];
			fRec31[1] = fRec31[0];
			iRec29[1] = iRec29[0];
			fRec30[1] = fRec30[0];
			iRec27[1] = iRec27[0];
			fRec28[1] = fRec28[0];
			iRec25[1] = iRec25[0];
			fRec26[1] = fRec26[0];
			iRec23[1] = iRec23[0];
			fRec24[1] = fRec24[0];
			iRec21[1] = iRec21[0];
			fRec22[1] = fRec22[0];
			iRec19[1] = iRec19[0];
			fRec20[1] = fRec20[0];
			iRec17[1] = iRec17[0];
			fRec18[1] = fRec18[0];
			iRec15[1] = iRec15[0];
			fRec16[1] = fRec16[0];
			fRec32[1] = fRec32[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			iRec0[1] = iRec0[0];
			fRec1[1] = fRec1[0];
			fRec35[1] = fRec35[0];
			fRec36[1] = fRec36[0];
			fRec37[1] = fRec37[0];
			fRec38[1] = fRec38[0];
			iRec33[1] = iRec33[0];
			fRec34[1] = fRec34[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "limiterStereo.dsp"
	#define FAUST_CLASS_NAME "_limiterStereo"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _limiterStereo -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 6
	#define FAUST_PASSIVES 3

	FAUST_ADDCHECKBOX("Look-ahead IIR Stereo Limiter/Control/Bypass", fCheckbox0);
	FAUST_ADDHORIZONTALSLIDER("Look-ahead IIR Stereo Limiter/Control/Pre Gain (dB)", fHslider1, 0.0f, 0.0f, 1.2e+02f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("Look-ahead IIR Stereo Limiter/Control/Threshold (dB)", fHslider2, 0.0f, -6e+01f, 0.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("Look-ahead IIR Stereo Limiter/Control/Attack (s)", fHslider0, 0.01f, 0.001f, 0.05f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("Look-ahead IIR Stereo Limiter/Control/Hold (s)", fHslider3, 0.05f, 0.0f, 1.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("Look-ahead IIR Stereo Limiter/Control/Release (s)", fHslider4, 0.15f, 0.05f, 1.0f, 0.001f);
	FAUST_ADDVERTICALBARGRAPH("Look-ahead IIR Stereo Limiter/Display/Peaks/Left Peak (dB)", fVbargraph1, -6e+01f, 6e+01f);
	FAUST_ADDVERTICALBARGRAPH("Look-ahead IIR Stereo Limiter/Display/Peaks/Right Peak (dB)", fVbargraph2, -6e+01f, 6e+01f);
	FAUST_ADDVERTICALBARGRAPH("Look-ahead IIR Stereo Limiter/Display/Attenuation (dB)", fVbargraph0, -1.2e+02f, 0.0f);

	#define FAUST_LIST_ACTIVES(p) \
		p(CHECKBOX, Bypass, "Look-ahead IIR Stereo Limiter/Control/Bypass", fCheckbox0, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(HORIZONTALSLIDER, Pre_Gain_(dB), "Look-ahead IIR Stereo Limiter/Control/Pre Gain (dB)", fHslider1, 0.0f, 0.0f, 1.2e+02f, 0.001f) \
		p(HORIZONTALSLIDER, Threshold_(dB), "Look-ahead IIR Stereo Limiter/Control/Threshold (dB)", fHslider2, 0.0f, -6e+01f, 0.0f, 0.001f) \
		p(HORIZONTALSLIDER, Attack_(s), "Look-ahead IIR Stereo Limiter/Control/Attack (s)", fHslider0, 0.01f, 0.001f, 0.05f, 0.001f) \
		p(HORIZONTALSLIDER, Hold_(s), "Look-ahead IIR Stereo Limiter/Control/Hold (s)", fHslider3, 0.05f, 0.0f, 1.0f, 0.001f) \
		p(HORIZONTALSLIDER, Release_(s), "Look-ahead IIR Stereo Limiter/Control/Release (s)", fHslider4, 0.15f, 0.05f, 1.0f, 0.001f) \

	#define FAUST_LIST_PASSIVES(p) \
		p(VERTICALBARGRAPH, Left_Peak_(dB), "Look-ahead IIR Stereo Limiter/Display/Peaks/Left Peak (dB)", fVbargraph1, 0.0, -6e+01f, 6e+01f, 0.0) \
		p(VERTICALBARGRAPH, Right_Peak_(dB), "Look-ahead IIR Stereo Limiter/Display/Peaks/Right Peak (dB)", fVbargraph2, 0.0, -6e+01f, 6e+01f, 0.0) \
		p(VERTICALBARGRAPH, Attenuation_(dB), "Look-ahead IIR Stereo Limiter/Display/Attenuation (dB)", fVbargraph0, 0.0, -1.2e+02f, 0.0f, 0.0) \

#endif

#endif

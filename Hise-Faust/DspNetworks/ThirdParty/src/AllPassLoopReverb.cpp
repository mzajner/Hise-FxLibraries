/* ------------------------------------------------------------
author: "Luca Spanedda"
copyright: "Copyright(c) 2023 Luca Spanedda"
name: "Luca Spanedda's KBVerb"
version: "0.8"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _AllPassLoopReverb -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___AllPassLoopReverb_H__
#define  ___AllPassLoopReverb_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _AllPassLoopReverb
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

struct _AllPassLoopReverbSIG0 {
	int iVec6[2];
	int iRec52[2];
	
	int getNumInputs_AllPassLoopReverbSIG0() {
		return 0;
	}
	int getNumOutputs_AllPassLoopReverbSIG0() {
		return 1;
	}
	
	void instanceInit_AllPassLoopReverbSIG0(int sample_rate) {
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			iVec6[l29] = 0;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			iRec52[l30] = 0;
		}
	}
	
	void fill_AllPassLoopReverbSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec6[0] = 1;
			iRec52[0] = (iVec6[1] + iRec52[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * static_cast<float>(iRec52[0]));
			iVec6[1] = iVec6[0];
			iRec52[1] = iRec52[0];
		}
	}

};

static _AllPassLoopReverbSIG0* new_AllPassLoopReverbSIG0() { return (_AllPassLoopReverbSIG0*)new _AllPassLoopReverbSIG0(); }
static void delete_AllPassLoopReverbSIG0(_AllPassLoopReverbSIG0* dsp) { delete dsp; }

static float ftbl0_AllPassLoopReverbSIG0[65536];

struct _AllPassLoopReverb final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	int iVec0[2];
	float fRec0[2];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider1;
	float fRec10[2];
	FAUSTFLOAT fHslider2;
	float fRec17[2];
	FAUSTFLOAT fHslider3;
	float fRec18[2];
	float fConst3;
	float fConst4;
	float fConst5;
	float fRec21[2];
	float fRec19[2];
	int IOTA0;
	float fRec20[131072];
	FAUSTFLOAT fHslider4;
	float fRec23[2];
	FAUSTFLOAT fHslider5;
	float fRec24[2];
	float fRec22[2];
	float fVec1[2048];
	float fRec15[2];
	float fRec33[2];
	float fRec31[2];
	float fRec32[131072];
	float fVec2[2048];
	float fRec29[2];
	float fRec42[2];
	float fRec40[2];
	float fRec41[131072];
	float fVec3[2048];
	float fRec38[2];
	float fRec51[2];
	float fRec49[2];
	float fRec50[131072];
	float fVec4[2048];
	float fRec47[2];
	float fVec5[4096];
	float fConst6;
	float fRec53[2];
	float fRec45[2];
	float fVec7[8192];
	float fRec43[2];
	float fVec8[16384];
	float fVec9[4096];
	float fConst7;
	float fRec54[2];
	float fRec36[2];
	float fVec10[4096];
	float fRec34[2];
	float fVec11[8192];
	float fVec12[4096];
	float fConst8;
	float fRec55[2];
	float fRec27[2];
	float fVec13[4096];
	float fRec25[2];
	float fVec14[8192];
	float fVec15[2048];
	float fConst9;
	float fRec56[2];
	float fRec13[2];
	float fVec16[2048];
	float fRec11[2];
	float fVec17[8192];
	float fRec5[2];
	float fRec1[3];
	float fRec2[3];
	float fRec3[3];
	float fRec4[3];
	
	_AllPassLoopReverb() {
	}
	
	_AllPassLoopReverb(const _AllPassLoopReverb&) = default;
	
	virtual ~_AllPassLoopReverb() = default;
	
	_AllPassLoopReverb& operator=(const _AllPassLoopReverb&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Luca Spanedda");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _AllPassLoopReverb -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("copyright", "Copyright(c) 2023 Luca Spanedda");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.2.0");
		m->declare("filename", "AllPassLoopReverb.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "Luca Spanedda's KBVerb");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "1.6.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("version", "0.8");
	}

	static constexpr int getStaticNumInputs() {
		return 1;
	}
	static constexpr int getStaticNumOutputs() {
		return 2;
	}
	int getNumInputs() {
		return 1;
	}
	int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
		_AllPassLoopReverbSIG0* sig0 = new_AllPassLoopReverbSIG0();
		sig0->instanceInit_AllPassLoopReverbSIG0(sample_rate);
		sig0->fill_AllPassLoopReverbSIG0(65536, ftbl0_AllPassLoopReverbSIG0);
		delete_AllPassLoopReverbSIG0(sig0);
	}
	
	void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = std::tan(47123.89f / fConst0);
		fConst4 = fConst3 / (fConst3 + 1.0f);
		fConst5 = 2.0f * fConst4;
		fConst6 = 0.2143f / fConst0;
		fConst7 = 0.1583f / fConst0;
		fConst8 = 0.2003f / fConst0;
		fConst9 = 0.1181f / fConst0;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(0.5f);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.8f);
		fHslider2 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider3 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider4 = static_cast<FAUSTFLOAT>(12.0f);
		fHslider5 = static_cast<FAUSTFLOAT>(0.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec10[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec17[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec18[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec21[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec19[l6] = 0.0f;
		}
		IOTA0 = 0;
		for (int l7 = 0; l7 < 131072; l7 = l7 + 1) {
			fRec20[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec23[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec24[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec22[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2048; l11 = l11 + 1) {
			fVec1[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec15[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec33[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec31[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 131072; l15 = l15 + 1) {
			fRec32[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2048; l16 = l16 + 1) {
			fVec2[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec29[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec42[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec40[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 131072; l20 = l20 + 1) {
			fRec41[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2048; l21 = l21 + 1) {
			fVec3[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fRec38[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec51[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fRec49[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 131072; l25 = l25 + 1) {
			fRec50[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 2048; l26 = l26 + 1) {
			fVec4[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec47[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 4096; l28 = l28 + 1) {
			fVec5[l28] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec53[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 2; l32 = l32 + 1) {
			fRec45[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 8192; l33 = l33 + 1) {
			fVec7[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			fRec43[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 16384; l35 = l35 + 1) {
			fVec8[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 4096; l36 = l36 + 1) {
			fVec9[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 2; l37 = l37 + 1) {
			fRec54[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 2; l38 = l38 + 1) {
			fRec36[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 4096; l39 = l39 + 1) {
			fVec10[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			fRec34[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 8192; l41 = l41 + 1) {
			fVec11[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 4096; l42 = l42 + 1) {
			fVec12[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec55[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 2; l44 = l44 + 1) {
			fRec27[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 4096; l45 = l45 + 1) {
			fVec13[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 2; l46 = l46 + 1) {
			fRec25[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 8192; l47 = l47 + 1) {
			fVec14[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 2048; l48 = l48 + 1) {
			fVec15[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 2; l49 = l49 + 1) {
			fRec56[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 2; l50 = l50 + 1) {
			fRec13[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 2048; l51 = l51 + 1) {
			fVec16[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 2; l52 = l52 + 1) {
			fRec11[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 8192; l53 = l53 + 1) {
			fVec17[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 2; l54 = l54 + 1) {
			fRec5[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 3; l55 = l55 + 1) {
			fRec1[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 3; l56 = l56 + 1) {
			fRec2[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 3; l57 = l57 + 1) {
			fRec3[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 3; l58 = l58 + 1) {
			fRec4[l58] = 0.0f;
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
	
	_AllPassLoopReverb* clone() {
		return new _AllPassLoopReverb(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Luca Spanedda's KBVerb");
		ui_interface->openHorizontalBox("Dry/Wet");
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("KRT Decay", &fHslider1, FAUSTFLOAT(0.8f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.98f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->addHorizontalSlider("Dry Sound", &fHslider0, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider2, "3", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("Reverb IN", &fHslider2, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Freeze");
		ui_interface->addCheckButton("Freeze", &fCheckbox0);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Shimmer");
		ui_interface->declare(&fHslider3, "5", "");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("Shimmer", &fHslider3, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.01f), FAUSTFLOAT(0.99f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider4, "6", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("Frequency", &fHslider4, FAUSTFLOAT(12.0f), FAUSTFLOAT(-24.0f), FAUSTFLOAT(24.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider5, "7", "");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->addHorizontalSlider("Fine Tune", &fHslider5, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst1 * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider0)));
		float fSlow1 = static_cast<float>(fCheckbox0);
		float fSlow2 = 1.0f - fSlow1;
		float fSlow3 = fConst1 * std::max<float>(0.0f, std::min<float>(0.98f, static_cast<float>(fHslider1)));
		float fSlow4 = fConst1 * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider2)));
		float fSlow5 = fConst1 * std::max<float>(0.01f, std::min<float>(0.99f, static_cast<float>(fHslider3)));
		float fSlow6 = fConst1 * std::max<float>(-24.0f, std::min<float>(24.0f, static_cast<float>(fHslider4)));
		float fSlow7 = fConst1 * std::max<float>(-1.0f, std::min<float>(1.0f, static_cast<float>(fHslider5)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			iVec0[0] = 1;
			fRec0[0] = fSlow0 + fConst2 * fRec0[1];
			float fTemp1 = fTemp0 * fRec0[0];
			fRec10[0] = fSlow3 + fConst2 * fRec10[1];
			float fTemp2 = fSlow1 + fSlow2 * fRec10[0];
			fRec17[0] = fSlow4 + fConst2 * fRec17[1];
			fRec18[0] = fSlow5 + fConst2 * fRec18[1];
			float fTemp3 = fTemp0 * fRec17[0] * (1.0f - fRec18[0]);
			fRec21[0] = 0.8f * fRec21[1] + fRec4[1] - fRec4[2];
			float fTemp4 = fRec21[0] - fRec19[1];
			fRec19[0] = fRec19[1] + fConst5 * fTemp4;
			float fTemp5 = fRec19[1] + fConst4 * fTemp4;
			fRec20[IOTA0 & 131071] = fTemp5;
			fRec23[0] = fSlow6 + fConst2 * fRec23[1];
			fRec24[0] = fSlow7 + fConst2 * fRec24[1];
			fRec22[0] = std::fmod(fRec22[1] + (10001.0f - std::pow(2.0f, 0.083333336f * (fRec23[0] + fRec24[0]))), 1e+04f);
			int iTemp6 = static_cast<int>(fRec22[0]);
			int iTemp7 = std::min<int>(65537, std::max<int>(0, iTemp6));
			float fTemp8 = std::floor(fRec22[0]);
			float fTemp9 = fTemp8 + (1.0f - fRec22[0]);
			float fTemp10 = fRec22[0] - fTemp8;
			int iTemp11 = std::min<int>(65537, std::max<int>(0, iTemp6 + 1));
			float fTemp12 = std::min<float>(fRec22[0], 1.0f);
			float fTemp13 = fRec22[0] + 1e+04f;
			int iTemp14 = static_cast<int>(fTemp13);
			int iTemp15 = std::min<int>(65537, std::max<int>(0, iTemp14));
			float fTemp16 = std::floor(fTemp13);
			float fTemp17 = fTemp16 + (-9999.0f - fRec22[0]);
			float fTemp18 = fRec22[0] + (1e+04f - fTemp16);
			int iTemp19 = std::min<int>(65537, std::max<int>(0, iTemp14 + 1));
			float fTemp20 = 1.0f - fTemp12;
			float fTemp21 = fSlow2 * (fTemp3 + fRec18[0] * ((fRec20[(IOTA0 - iTemp7) & 131071] * fTemp9 + fTemp10 * fRec20[(IOTA0 - iTemp11) & 131071]) * fTemp12 + (fRec20[(IOTA0 - iTemp15) & 131071] * fTemp17 + fTemp18 * fRec20[(IOTA0 - iTemp19) & 131071]) * fTemp20)) - 0.65f * fRec15[1];
			fVec1[IOTA0 & 2047] = fTemp21;
			fRec15[0] = fVec1[(IOTA0 - 1343) & 2047];
			float fRec16 = 0.65f * fTemp21;
			fRec33[0] = 0.8f * fRec33[1] + fRec3[1] - fRec3[2];
			float fTemp22 = fRec33[0] - fRec31[1];
			fRec31[0] = fRec31[1] + fConst5 * fTemp22;
			float fTemp23 = fRec31[1] + fConst4 * fTemp22;
			fRec32[IOTA0 & 131071] = fTemp23;
			float fTemp24 = fSlow2 * (fTemp3 + fRec18[0] * (fTemp12 * (fTemp9 * fRec32[(IOTA0 - iTemp7) & 131071] + fTemp10 * fRec32[(IOTA0 - iTemp11) & 131071]) + fTemp20 * (fTemp17 * fRec32[(IOTA0 - iTemp15) & 131071] + fTemp18 * fRec32[(IOTA0 - iTemp19) & 131071]))) - 0.65f * fRec29[1];
			fVec2[IOTA0 & 2047] = fTemp24;
			fRec29[0] = fVec2[(IOTA0 - 1443) & 2047];
			float fRec30 = 0.65f * fTemp24;
			fRec42[0] = 0.8f * fRec42[1] + fRec2[1] - fRec2[2];
			float fTemp25 = fRec42[0] - fRec40[1];
			fRec40[0] = fRec40[1] + fConst5 * fTemp25;
			float fTemp26 = fRec40[1] + fConst4 * fTemp25;
			fRec41[IOTA0 & 131071] = fTemp26;
			float fTemp27 = fSlow2 * (fTemp3 + fRec18[0] * (fTemp12 * (fTemp9 * fRec41[(IOTA0 - iTemp7) & 131071] + fTemp10 * fRec41[(IOTA0 - iTemp11) & 131071]) + fTemp20 * (fTemp17 * fRec41[(IOTA0 - iTemp15) & 131071] + fTemp18 * fRec41[(IOTA0 - iTemp19) & 131071]))) - 0.65f * fRec38[1];
			fVec3[IOTA0 & 2047] = fTemp27;
			fRec38[0] = fVec3[(IOTA0 - 1751) & 2047];
			float fRec39 = 0.65f * fTemp27;
			fRec51[0] = 0.8f * fRec51[1] + fRec1[1] - fRec1[2];
			float fTemp28 = fRec51[0] - fRec49[1];
			fRec49[0] = fRec49[1] + fConst5 * fTemp28;
			float fTemp29 = fRec49[1] + fConst4 * fTemp28;
			fRec50[IOTA0 & 131071] = fTemp29;
			float fTemp30 = fSlow2 * (fTemp3 + fRec18[0] * (fTemp12 * (fTemp9 * fRec50[(IOTA0 - iTemp7) & 131071] + fTemp10 * fRec50[(IOTA0 - iTemp11) & 131071]) + fTemp20 * (fTemp17 * fRec50[(IOTA0 - iTemp15) & 131071] + fTemp18 * fRec50[(IOTA0 - iTemp19) & 131071]))) - 0.65f * fRec47[1];
			fVec4[IOTA0 & 2047] = fTemp30;
			fRec47[0] = fVec4[(IOTA0 - 1251) & 2047];
			float fRec48 = 0.65f * fTemp30;
			float fTemp31 = fRec47[1] + fRec48 + fRec5[1] - 0.65f * fRec45[1];
			fVec5[IOTA0 & 4095] = fTemp31;
			int iTemp32 = 1 - iVec0[1];
			float fTemp33 = ((iTemp32) ? 0.0f : fConst6 + fRec53[1]);
			fRec53[0] = fTemp33 - std::floor(fTemp33);
			float fTemp34 = 98.5f * (ftbl0_AllPassLoopReverbSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec53[0]), 65535))] + 1.0f);
			float fTemp35 = 3823.0f - fTemp34;
			int iTemp36 = static_cast<int>(fTemp35);
			float fTemp37 = fTemp34 + std::floor(fTemp35);
			fRec45[0] = fVec5[(IOTA0 - std::min<int>(3824, std::max<int>(0, iTemp36))) & 4095] * (fTemp37 + -3822.0f) + (3823.0f - fTemp37) * fVec5[(IOTA0 - std::min<int>(3824, std::max<int>(0, iTemp36 + 1))) & 4095];
			float fRec46 = 0.65f * fTemp31;
			float fTemp38 = fRec46 + fRec45[1] - 0.65f * fRec43[1];
			fVec7[IOTA0 & 8191] = fTemp38;
			fRec43[0] = fVec7[(IOTA0 - 4732) & 8191];
			float fRec44 = 0.65f * fTemp38;
			fVec8[IOTA0 & 16383] = fRec44 + fRec43[1];
			float fTemp39 = fVec8[(IOTA0 - 8501) & 16383];
			float fTemp40 = fRec39 + fRec38[1] + fTemp39 * fTemp2 - 0.65f * fRec36[1];
			fVec9[IOTA0 & 4095] = fTemp40;
			float fTemp41 = ((iTemp32) ? 0.0f : fConst7 + fRec54[1]);
			fRec54[0] = fTemp41 - std::floor(fTemp41);
			float fTemp42 = 165.5f * (ftbl0_AllPassLoopReverbSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec54[0]), 65535))] + 1.0f);
			float fTemp43 = 2204.0f - fTemp42;
			int iTemp44 = static_cast<int>(fTemp43);
			float fTemp45 = fTemp42 + std::floor(fTemp43);
			fRec36[0] = fVec9[(IOTA0 - std::min<int>(2205, std::max<int>(0, iTemp44))) & 4095] * (fTemp45 + -2203.0f) + (2204.0f - fTemp45) * fVec9[(IOTA0 - std::min<int>(2205, std::max<int>(0, iTemp44 + 1))) & 4095];
			float fRec37 = 0.65f * fTemp40;
			float fTemp46 = fRec37 + fRec36[1] - 0.65f * fRec34[1];
			fVec10[IOTA0 & 4095] = fTemp46;
			fRec34[0] = fVec10[(IOTA0 - 2701) & 4095];
			float fRec35 = 0.65f * fTemp46;
			fVec11[IOTA0 & 8191] = fRec35 + fRec34[1];
			float fTemp47 = fVec11[(IOTA0 - 7237) & 8191];
			float fTemp48 = fRec30 + fRec29[1] + fTemp2 * fTemp47 - 0.65f * fRec27[1];
			fVec12[IOTA0 & 4095] = fTemp48;
			float fTemp49 = ((iTemp32) ? 0.0f : fConst8 + fRec55[1]);
			fRec55[0] = fTemp49 - std::floor(fTemp49);
			float fTemp50 = 105.5f * (ftbl0_AllPassLoopReverbSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec55[0]), 65535))] + 1.0f);
			float fTemp51 = 2532.0f - fTemp50;
			int iTemp52 = static_cast<int>(fTemp51);
			float fTemp53 = fTemp50 + std::floor(fTemp51);
			fRec27[0] = fVec12[(IOTA0 - std::min<int>(2533, std::max<int>(0, iTemp52))) & 4095] * (fTemp53 + -2531.0f) + (2532.0f - fTemp53) * fVec12[(IOTA0 - std::min<int>(2533, std::max<int>(0, iTemp52 + 1))) & 4095];
			float fRec28 = 0.65f * fTemp48;
			float fTemp54 = fRec28 + fRec27[1] - 0.65f * fRec25[1];
			fVec13[IOTA0 & 4095] = fTemp54;
			fRec25[0] = fVec13[(IOTA0 - 2201) & 4095];
			float fRec26 = 0.65f * fTemp54;
			fVec14[IOTA0 & 8191] = fRec26 + fRec25[1];
			float fTemp55 = fVec14[(IOTA0 - 6337) & 8191];
			float fTemp56 = fRec16 + fRec15[1] + fTemp2 * fTemp55 - 0.65f * fRec13[1];
			fVec15[IOTA0 & 2047] = fTemp56;
			float fTemp57 = ((iTemp32) ? 0.0f : fConst9 + fRec56[1]);
			fRec56[0] = fTemp57 - std::floor(fTemp57);
			float fTemp58 = 156.5f * (ftbl0_AllPassLoopReverbSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec56[0]), 65535))] + 1.0f);
			float fTemp59 = 1553.0f - fTemp58;
			int iTemp60 = static_cast<int>(fTemp59);
			float fTemp61 = fTemp58 + std::floor(fTemp59);
			fRec13[0] = fVec15[(IOTA0 - std::min<int>(1554, std::max<int>(0, iTemp60))) & 2047] * (fTemp61 + -1552.0f) + (1553.0f - fTemp61) * fVec15[(IOTA0 - std::min<int>(1554, std::max<int>(0, iTemp60 + 1))) & 2047];
			float fRec14 = 0.65f * fTemp56;
			float fTemp62 = fRec14 + fRec13[1] - 0.65f * fRec11[1];
			fVec16[IOTA0 & 2047] = fTemp62;
			fRec11[0] = fVec16[(IOTA0 - 1583) & 2047];
			float fRec12 = 0.65f * fTemp62;
			fVec17[IOTA0 & 8191] = fRec12 + fRec11[1];
			float fTemp63 = fVec17[(IOTA0 - 5867) & 8191];
			fRec5[0] = fTemp2 * fTemp63;
			float fRec6 = fTemp63;
			float fRec7 = fTemp55;
			float fRec8 = fTemp47;
			float fRec9 = fTemp39;
			fRec1[0] = fRec6;
			fRec2[0] = fRec7;
			fRec3[0] = fRec8;
			fRec4[0] = fRec9;
			output0[i0] = static_cast<FAUSTFLOAT>(fTemp1 + 0.5f * (fRec1[0] + fRec3[0]));
			output1[i0] = static_cast<FAUSTFLOAT>(fTemp1 + 0.5f * (fRec2[0] + fRec4[0]));
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			fRec10[1] = fRec10[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fRec21[1] = fRec21[0];
			fRec19[1] = fRec19[0];
			IOTA0 = IOTA0 + 1;
			fRec23[1] = fRec23[0];
			fRec24[1] = fRec24[0];
			fRec22[1] = fRec22[0];
			fRec15[1] = fRec15[0];
			fRec33[1] = fRec33[0];
			fRec31[1] = fRec31[0];
			fRec29[1] = fRec29[0];
			fRec42[1] = fRec42[0];
			fRec40[1] = fRec40[0];
			fRec38[1] = fRec38[0];
			fRec51[1] = fRec51[0];
			fRec49[1] = fRec49[0];
			fRec47[1] = fRec47[0];
			fRec53[1] = fRec53[0];
			fRec45[1] = fRec45[0];
			fRec43[1] = fRec43[0];
			fRec54[1] = fRec54[0];
			fRec36[1] = fRec36[0];
			fRec34[1] = fRec34[0];
			fRec55[1] = fRec55[0];
			fRec27[1] = fRec27[0];
			fRec25[1] = fRec25[0];
			fRec56[1] = fRec56[0];
			fRec13[1] = fRec13[0];
			fRec11[1] = fRec11[0];
			fRec5[1] = fRec5[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "AllPassLoopReverb.dsp"
	#define FAUST_CLASS_NAME "_AllPassLoopReverb"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _AllPassLoopReverb -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 1
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 7
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Dry/Wet/KRT Decay", fHslider1, 0.8f, 0.0f, 0.98f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("Dry/Wet/Dry Sound", fHslider0, 0.5f, 0.0f, 1.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("Dry/Wet/Reverb IN", fHslider2, 1.0f, 0.0f, 1.0f, 0.001f);
	FAUST_ADDCHECKBOX("Freeze/Freeze", fCheckbox0);
	FAUST_ADDHORIZONTALSLIDER("Shimmer/Shimmer", fHslider3, 0.5f, 0.01f, 0.99f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("Shimmer/Frequency", fHslider4, 12.0f, -24.0f, 24.0f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Shimmer/Fine Tune", fHslider5, 0.0f, -1.0f, 1.0f, 0.001f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, KRT_Decay, "Dry/Wet/KRT Decay", fHslider1, 0.8f, 0.0f, 0.98f, 0.001f) \
		p(HORIZONTALSLIDER, Dry_Sound, "Dry/Wet/Dry Sound", fHslider0, 0.5f, 0.0f, 1.0f, 0.001f) \
		p(HORIZONTALSLIDER, Reverb_IN, "Dry/Wet/Reverb IN", fHslider2, 1.0f, 0.0f, 1.0f, 0.001f) \
		p(CHECKBOX, Freeze, "Freeze/Freeze", fCheckbox0, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(HORIZONTALSLIDER, Shimmer, "Shimmer/Shimmer", fHslider3, 0.5f, 0.01f, 0.99f, 0.001f) \
		p(HORIZONTALSLIDER, Frequency, "Shimmer/Frequency", fHslider4, 12.0f, -24.0f, 24.0f, 0.1f) \
		p(HORIZONTALSLIDER, Fine_Tune, "Shimmer/Fine Tune", fHslider5, 0.0f, -1.0f, 1.0f, 0.001f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

/* ------------------------------------------------------------
author: "Grame"
copyright: "(c) GRAME 2006"
license: "BSD"
name: "freeverb"
version: "1.0"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _freeverb -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___freeverb_H__
#define  ___freeverb_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _freeverb
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


struct _freeverb final : public ::faust::dsp {
	
	FAUSTFLOAT fHslider0;
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	float fConst2;
	float fConst3;
	float fRec10[2];
	float fRec9[2];
	FAUSTFLOAT fHslider2;
	float fRec11[2];
	int IOTA0;
	float fVec0[2048];
	float fRec8[2];
	float fRec13[2];
	float fVec1[2048];
	float fRec12[2];
	float fRec15[2];
	float fVec2[2048];
	float fRec14[2];
	float fRec17[2];
	float fVec3[2048];
	float fRec16[2];
	float fRec19[2];
	float fVec4[2048];
	float fRec18[2];
	float fRec21[2];
	float fVec5[2048];
	float fRec20[2];
	float fRec23[2];
	float fVec6[2048];
	float fRec22[2];
	float fRec25[2];
	float fVec7[2048];
	float fRec24[2];
	float fVec8[1024];
	float fRec6[2];
	float fVec9[512];
	float fRec4[2];
	float fVec10[512];
	float fRec2[2];
	float fVec11[256];
	float fRec0[2];
	float fRec35[2];
	float fVec12[2048];
	float fRec34[2];
	float fRec37[2];
	float fVec13[2048];
	float fRec36[2];
	float fRec39[2];
	float fVec14[2048];
	float fRec38[2];
	float fRec41[2];
	float fVec15[2048];
	float fRec40[2];
	float fRec43[2];
	float fVec16[2048];
	float fRec42[2];
	float fRec45[2];
	float fVec17[2048];
	float fRec44[2];
	float fRec47[2];
	float fVec18[2048];
	float fRec46[2];
	float fRec49[2];
	float fVec19[2048];
	float fRec48[2];
	float fVec20[1024];
	float fRec32[2];
	float fVec21[512];
	float fRec30[2];
	float fVec22[512];
	float fRec28[2];
	float fVec23[256];
	float fRec26[2];
	
	_freeverb() {
	}
	
	_freeverb(const _freeverb&) = default;
	
	virtual ~_freeverb() = default;
	
	_freeverb& operator=(const _freeverb&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _freeverb -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("copyright", "(c) GRAME 2006");
		m->declare("filename", "freeverb.dsp");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "freeverb");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("reference", "https://ccrma.stanford.edu/~jos/pasp/Freeverb.html");
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
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = 17.64f / fConst0;
		fConst2 = 44.1f / fConst0;
		fConst3 = 1.0f - fConst2;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(0.99f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider2 = static_cast<FAUSTFLOAT>(0.5f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec10[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec9[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec11[l2] = 0.0f;
		}
		IOTA0 = 0;
		for (int l3 = 0; l3 < 2048; l3 = l3 + 1) {
			fVec0[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec8[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec13[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2048; l6 = l6 + 1) {
			fVec1[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec12[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec15[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2048; l9 = l9 + 1) {
			fVec2[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec14[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec17[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2048; l12 = l12 + 1) {
			fVec3[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec16[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec19[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2048; l15 = l15 + 1) {
			fVec4[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec18[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec21[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2048; l18 = l18 + 1) {
			fVec5[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec20[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fRec23[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2048; l21 = l21 + 1) {
			fVec6[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fRec22[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec25[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 2048; l24 = l24 + 1) {
			fVec7[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fRec24[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 1024; l26 = l26 + 1) {
			fVec8[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec6[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 512; l28 = l28 + 1) {
			fVec9[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			fRec4[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 512; l30 = l30 + 1) {
			fVec10[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec2[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 256; l32 = l32 + 1) {
			fVec11[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			fRec0[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			fRec35[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 2048; l35 = l35 + 1) {
			fVec12[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 2; l36 = l36 + 1) {
			fRec34[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 2; l37 = l37 + 1) {
			fRec37[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 2048; l38 = l38 + 1) {
			fVec13[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 2; l39 = l39 + 1) {
			fRec36[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			fRec39[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 2048; l41 = l41 + 1) {
			fVec14[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 2; l42 = l42 + 1) {
			fRec38[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec41[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 2048; l44 = l44 + 1) {
			fVec15[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 2; l45 = l45 + 1) {
			fRec40[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 2; l46 = l46 + 1) {
			fRec43[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 2048; l47 = l47 + 1) {
			fVec16[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 2; l48 = l48 + 1) {
			fRec42[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 2; l49 = l49 + 1) {
			fRec45[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 2048; l50 = l50 + 1) {
			fVec17[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 2; l51 = l51 + 1) {
			fRec44[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 2; l52 = l52 + 1) {
			fRec47[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 2048; l53 = l53 + 1) {
			fVec18[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 2; l54 = l54 + 1) {
			fRec46[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 2; l55 = l55 + 1) {
			fRec49[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 2048; l56 = l56 + 1) {
			fVec19[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 2; l57 = l57 + 1) {
			fRec48[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 1024; l58 = l58 + 1) {
			fVec20[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 2; l59 = l59 + 1) {
			fRec32[l59] = 0.0f;
		}
		for (int l60 = 0; l60 < 512; l60 = l60 + 1) {
			fVec21[l60] = 0.0f;
		}
		for (int l61 = 0; l61 < 2; l61 = l61 + 1) {
			fRec30[l61] = 0.0f;
		}
		for (int l62 = 0; l62 < 512; l62 = l62 + 1) {
			fVec22[l62] = 0.0f;
		}
		for (int l63 = 0; l63 < 2; l63 = l63 + 1) {
			fRec28[l63] = 0.0f;
		}
		for (int l64 = 0; l64 < 256; l64 = l64 + 1) {
			fVec23[l64] = 0.0f;
		}
		for (int l65 = 0; l65 < 2; l65 = l65 + 1) {
			fRec26[l65] = 0.0f;
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
	
	_freeverb* clone() {
		return new _freeverb(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Freeverb");
		ui_interface->declare(&fHslider1, "OWL", "PARAMETER_B");
		ui_interface->addHorizontalSlider("Damp", &fHslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.025f));
		ui_interface->declare(&fHslider0, "OWL", "PARAMETER_D");
		ui_interface->addHorizontalSlider("Dry/Wet", &fHslider0, FAUSTFLOAT(0.99f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.025f));
		ui_interface->declare(&fHslider2, "OWL", "PARAMETER_A");
		ui_interface->addHorizontalSlider("Room Size", &fHslider2, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.025f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst1 * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider1)));
		float fSlow2 = fConst2 * (0.28f * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider2))) + 0.7f);
		float fSlow3 = 1.0f - fSlow0;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec10[0] = fSlow1 + fConst3 * fRec10[1];
			float fTemp0 = 1.0f - fRec10[0];
			fRec9[0] = fRec10[0] * fRec9[1] + fTemp0 * fRec8[1];
			fRec11[0] = fSlow2 + fConst3 * fRec11[1];
			float fTemp1 = static_cast<float>(input0[i0]);
			float fTemp2 = 0.015f * fTemp1;
			fVec0[IOTA0 & 2047] = fRec9[0] * fRec11[0] + fTemp2;
			fRec8[0] = fVec0[(IOTA0 - 1116) & 2047];
			fRec13[0] = fRec10[0] * fRec13[1] + fTemp0 * fRec12[1];
			fVec1[IOTA0 & 2047] = fTemp2 + fRec11[0] * fRec13[0];
			fRec12[0] = fVec1[(IOTA0 - 1188) & 2047];
			fRec15[0] = fRec10[0] * fRec15[1] + fTemp0 * fRec14[1];
			fVec2[IOTA0 & 2047] = fTemp2 + fRec11[0] * fRec15[0];
			fRec14[0] = fVec2[(IOTA0 - 1277) & 2047];
			fRec17[0] = fRec10[0] * fRec17[1] + fTemp0 * fRec16[1];
			fVec3[IOTA0 & 2047] = fTemp2 + fRec11[0] * fRec17[0];
			fRec16[0] = fVec3[(IOTA0 - 1356) & 2047];
			fRec19[0] = fRec10[0] * fRec19[1] + fTemp0 * fRec18[1];
			fVec4[IOTA0 & 2047] = fTemp2 + fRec11[0] * fRec19[0];
			fRec18[0] = fVec4[(IOTA0 - 1422) & 2047];
			fRec21[0] = fRec10[0] * fRec21[1] + fTemp0 * fRec20[1];
			fVec5[IOTA0 & 2047] = fTemp2 + fRec11[0] * fRec21[0];
			fRec20[0] = fVec5[(IOTA0 - 1491) & 2047];
			fRec23[0] = fRec10[0] * fRec23[1] + fTemp0 * fRec22[1];
			fVec6[IOTA0 & 2047] = fTemp2 + fRec11[0] * fRec23[0];
			fRec22[0] = fVec6[(IOTA0 - 1557) & 2047];
			fRec25[0] = fRec10[0] * fRec25[1] + fTemp0 * fRec24[1];
			fVec7[IOTA0 & 2047] = fTemp2 + fRec11[0] * fRec25[0];
			fRec24[0] = fVec7[(IOTA0 - 1617) & 2047];
			float fTemp3 = fRec8[0] + fRec12[0] + fRec14[0] + fRec16[0] + fRec18[0] + fRec20[0] + fRec22[0] + fRec24[0];
			fVec8[IOTA0 & 1023] = fTemp3 + 0.5f * fRec6[1];
			fRec6[0] = fVec8[(IOTA0 - 556) & 1023];
			float fRec7 = fRec6[1] - fTemp3;
			fVec9[IOTA0 & 511] = fRec7 + 0.5f * fRec4[1];
			fRec4[0] = fVec9[(IOTA0 - 441) & 511];
			float fRec5 = fRec4[1] - fRec7;
			fVec10[IOTA0 & 511] = fRec5 + 0.5f * fRec2[1];
			fRec2[0] = fVec10[(IOTA0 - 341) & 511];
			float fRec3 = fRec2[1] - fRec5;
			fVec11[IOTA0 & 255] = fRec3 + 0.5f * fRec0[1];
			fRec0[0] = fVec11[(IOTA0 - 225) & 255];
			float fRec1 = fRec0[1] - fRec3;
			output0[i0] = static_cast<FAUSTFLOAT>(fSlow0 * fRec1 + fSlow3 * fTemp1);
			fRec35[0] = fRec10[0] * fRec35[1] + fTemp0 * fRec34[1];
			float fTemp4 = static_cast<float>(input1[i0]);
			float fTemp5 = 0.015f * fTemp4;
			fVec12[IOTA0 & 2047] = fRec11[0] * fRec35[0] + fTemp5;
			fRec34[0] = fVec12[(IOTA0 - 1116) & 2047];
			fRec37[0] = fRec10[0] * fRec37[1] + fTemp0 * fRec36[1];
			fVec13[IOTA0 & 2047] = fTemp5 + fRec11[0] * fRec37[0];
			fRec36[0] = fVec13[(IOTA0 - 1188) & 2047];
			fRec39[0] = fRec10[0] * fRec39[1] + fTemp0 * fRec38[1];
			fVec14[IOTA0 & 2047] = fTemp5 + fRec11[0] * fRec39[0];
			fRec38[0] = fVec14[(IOTA0 - 1277) & 2047];
			fRec41[0] = fRec10[0] * fRec41[1] + fTemp0 * fRec40[1];
			fVec15[IOTA0 & 2047] = fTemp5 + fRec11[0] * fRec41[0];
			fRec40[0] = fVec15[(IOTA0 - 1356) & 2047];
			fRec43[0] = fRec10[0] * fRec43[1] + fTemp0 * fRec42[1];
			fVec16[IOTA0 & 2047] = fTemp5 + fRec11[0] * fRec43[0];
			fRec42[0] = fVec16[(IOTA0 - 1422) & 2047];
			fRec45[0] = fRec10[0] * fRec45[1] + fTemp0 * fRec44[1];
			fVec17[IOTA0 & 2047] = fTemp5 + fRec11[0] * fRec45[0];
			fRec44[0] = fVec17[(IOTA0 - 1491) & 2047];
			fRec47[0] = fRec10[0] * fRec47[1] + fTemp0 * fRec46[1];
			fVec18[IOTA0 & 2047] = fTemp5 + fRec11[0] * fRec47[0];
			fRec46[0] = fVec18[(IOTA0 - 1557) & 2047];
			fRec49[0] = fRec10[0] * fRec49[1] + fTemp0 * fRec48[1];
			fVec19[IOTA0 & 2047] = fTemp5 + fRec11[0] * fRec49[0];
			fRec48[0] = fVec19[(IOTA0 - 1617) & 2047];
			float fTemp6 = fRec34[0] + fRec36[0] + fRec38[0] + fRec40[0] + fRec42[0] + fRec44[0] + fRec46[0] + fRec48[0];
			fVec20[IOTA0 & 1023] = fTemp6 + 0.5f * fRec32[1];
			fRec32[0] = fVec20[(IOTA0 - 556) & 1023];
			float fRec33 = fRec32[1] - fTemp6;
			fVec21[IOTA0 & 511] = fRec33 + 0.5f * fRec30[1];
			fRec30[0] = fVec21[(IOTA0 - 441) & 511];
			float fRec31 = fRec30[1] - fRec33;
			fVec22[IOTA0 & 511] = fRec31 + 0.5f * fRec28[1];
			fRec28[0] = fVec22[(IOTA0 - 341) & 511];
			float fRec29 = fRec28[1] - fRec31;
			fVec23[IOTA0 & 255] = fRec29 + 0.5f * fRec26[1];
			fRec26[0] = fVec23[(IOTA0 - 225) & 255];
			float fRec27 = fRec26[1] - fRec29;
			output1[i0] = static_cast<FAUSTFLOAT>(fSlow0 * fRec27 + fSlow3 * fTemp4);
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fRec11[1] = fRec11[0];
			IOTA0 = IOTA0 + 1;
			fRec8[1] = fRec8[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			fRec6[1] = fRec6[0];
			fRec4[1] = fRec4[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
			fRec35[1] = fRec35[0];
			fRec34[1] = fRec34[0];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
			fRec39[1] = fRec39[0];
			fRec38[1] = fRec38[0];
			fRec41[1] = fRec41[0];
			fRec40[1] = fRec40[0];
			fRec43[1] = fRec43[0];
			fRec42[1] = fRec42[0];
			fRec45[1] = fRec45[0];
			fRec44[1] = fRec44[0];
			fRec47[1] = fRec47[0];
			fRec46[1] = fRec46[0];
			fRec49[1] = fRec49[0];
			fRec48[1] = fRec48[0];
			fRec32[1] = fRec32[0];
			fRec30[1] = fRec30[0];
			fRec28[1] = fRec28[0];
			fRec26[1] = fRec26[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "freeverb.dsp"
	#define FAUST_CLASS_NAME "_freeverb"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _freeverb -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 3
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Freeverb/Damp", fHslider1, 0.5f, 0.0f, 1.0f, 0.025f);
	FAUST_ADDHORIZONTALSLIDER("Freeverb/Dry/Wet", fHslider0, 0.99f, 0.0f, 1.0f, 0.025f);
	FAUST_ADDHORIZONTALSLIDER("Freeverb/Room Size", fHslider2, 0.5f, 0.0f, 1.0f, 0.025f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Damp, "Freeverb/Damp", fHslider1, 0.5f, 0.0f, 1.0f, 0.025f) \
		p(HORIZONTALSLIDER, Dry/Wet, "Freeverb/Dry/Wet", fHslider0, 0.99f, 0.0f, 1.0f, 0.025f) \
		p(HORIZONTALSLIDER, Room_Size, "Freeverb/Room Size", fHslider2, 0.5f, 0.0f, 1.0f, 0.025f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

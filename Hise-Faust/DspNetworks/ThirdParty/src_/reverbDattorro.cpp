/* ------------------------------------------------------------
author: "Jakob Zerbian"
name: "dattorro"
version: "0.1"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _reverbDattorro -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___reverbDattorro_H__
#define  ___reverbDattorro_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _reverbDattorro
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


struct _reverbDattorro final : public ::faust::dsp {
	
	FAUSTFLOAT fHslider0;
	float fVec0[2];
	FAUSTFLOAT fHslider1;
	float fRec10[3];
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider2;
	float fConst1;
	float fRec11[2];
	int IOTA0;
	float fVec1[256];
	float fRec8[2];
	float fVec2[128];
	float fRec6[2];
	FAUSTFLOAT fHslider3;
	float fRec12[2];
	float fVec3[512];
	float fRec4[2];
	float fVec4[512];
	float fRec2[2];
	FAUSTFLOAT fHslider4;
	float fRec13[2];
	FAUSTFLOAT fHslider5;
	float fRec17[2];
	FAUSTFLOAT fHslider6;
	float fRec20[2];
	float fVec5[1024];
	float fRec18[2];
	float fVec6[8192];
	float fRec16[2];
	FAUSTFLOAT fHslider7;
	float fRec21[2];
	float fVec7[4096];
	float fRec14[2];
	float fVec8[4096];
	float fRec0[2];
	float fVec9[1024];
	float fRec25[2];
	float fVec10[8192];
	float fRec24[2];
	float fVec11[2048];
	float fRec22[2];
	float fVec12[2048];
	float fRec1[2];
	
	_reverbDattorro() {
	}
	
	_reverbDattorro(const _reverbDattorro&) = default;
	
	virtual ~_reverbDattorro() = default;
	
	_reverbDattorro& operator=(const _reverbDattorro&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Jakob Zerbian");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _reverbDattorro -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("description", "Dattorro Reverb edited MNTRA");
		m->declare("filename", "reverbDattorro.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "dattorro");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("reverbs.lib/dattorro_rev:author", "Jakob Zerbian");
		m->declare("reverbs.lib/dattorro_rev:licence", "MIT-style STK-4.3 license");
		m->declare("reverbs.lib/name", "Faust Reverb Library");
		m->declare("reverbs.lib/version", "1.5.1");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "1.2.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("version", "0.1");
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
		fHslider0 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider2 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider3 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider4 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider5 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider6 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider7 = static_cast<FAUSTFLOAT>(0.5f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fVec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 3; l1 = l1 + 1) {
			fRec10[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec11[l2] = 0.0f;
		}
		IOTA0 = 0;
		for (int l3 = 0; l3 < 256; l3 = l3 + 1) {
			fVec1[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec8[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 128; l5 = l5 + 1) {
			fVec2[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec6[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec12[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 512; l8 = l8 + 1) {
			fVec3[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec4[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 512; l10 = l10 + 1) {
			fVec4[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec2[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec13[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec17[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec20[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 1024; l15 = l15 + 1) {
			fVec5[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec18[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 8192; l17 = l17 + 1) {
			fVec6[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec16[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec21[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 4096; l20 = l20 + 1) {
			fVec7[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			fRec14[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 4096; l22 = l22 + 1) {
			fVec8[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec0[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 1024; l24 = l24 + 1) {
			fVec9[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fRec25[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 8192; l26 = l26 + 1) {
			fVec10[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec24[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 2048; l28 = l28 + 1) {
			fVec11[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			fRec22[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 2048; l30 = l30 + 1) {
			fVec12[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec1[l31] = 0.0f;
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
	
	_reverbDattorro* clone() {
		return new _reverbDattorro(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("dattorro");
		ui_interface->addHorizontalSlider("bw", &fHslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("dampings", &fHslider5, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("decayrate", &fHslider4, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("diffusion1", &fHslider2, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.95f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("diffusion2", &fHslider3, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.95f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("diffusiond1", &fHslider6, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.95f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("diffusiond2", &fHslider7, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.95f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("predelay", &fHslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider0)));
		float fSlow1 = 1.0f - fSlow0;
		float fSlow2 = 0.5f * fSlow0;
		int iSlow3 = static_cast<int>(std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider1))));
		float fSlow4 = fConst0 * std::max<float>(0.0f, std::min<float>(0.95f, static_cast<float>(fHslider2)));
		float fSlow5 = fConst0 * std::max<float>(0.0f, std::min<float>(0.95f, static_cast<float>(fHslider3)));
		float fSlow6 = 0.01f * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider4)));
		float fSlow7 = 0.01f * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider5)));
		float fSlow8 = fConst0 * std::max<float>(0.0f, std::min<float>(0.95f, static_cast<float>(fHslider6)));
		float fSlow9 = fConst0 * std::max<float>(0.0f, std::min<float>(0.95f, static_cast<float>(fHslider7)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fVec0[0] = static_cast<float>(input0[i0]) + static_cast<float>(input1[i0]);
			fRec10[0] = fSlow1 * fRec10[2] + fSlow2 * fVec0[iSlow3];
			fRec11[0] = fSlow4 + fConst1 * fRec11[1];
			float fTemp0 = fRec10[0] - fRec11[0] * fRec8[1];
			fVec1[IOTA0 & 255] = fTemp0;
			fRec8[0] = fVec1[(IOTA0 - 142) & 255];
			float fRec9 = fRec11[0] * fTemp0;
			float fTemp1 = fRec9 + fRec8[1] - fRec11[0] * fRec6[1];
			fVec2[IOTA0 & 127] = fTemp1;
			fRec6[0] = fVec2[(IOTA0 - 107) & 127];
			float fRec7 = fRec11[0] * fTemp1;
			fRec12[0] = fSlow5 + fConst1 * fRec12[1];
			float fTemp2 = fRec7 + fRec6[1] - fRec12[0] * fRec4[1];
			fVec3[IOTA0 & 511] = fTemp2;
			fRec4[0] = fVec3[(IOTA0 - 379) & 511];
			float fRec5 = fRec12[0] * fTemp2;
			float fTemp3 = fRec5 + fRec4[1] - fRec12[0] * fRec2[1];
			fVec4[IOTA0 & 511] = fTemp3;
			fRec2[0] = fVec4[(IOTA0 - 277) & 511];
			float fRec3 = fRec12[0] * fTemp3;
			fRec13[0] = fSlow6 + 0.99f * fRec13[1];
			fRec17[0] = fSlow7 + 0.99f * fRec17[1];
			float fTemp4 = 1.0f - fRec17[0];
			fRec20[0] = fSlow8 + fConst1 * fRec20[1];
			float fTemp5 = fRec20[0] * fRec18[1] + fRec1[1];
			fVec5[IOTA0 & 1023] = fTemp5;
			fRec18[0] = fVec5[(IOTA0 - 908) & 1023];
			float fRec19 = -(fRec20[0] * fTemp5);
			fVec6[IOTA0 & 8191] = fRec19 + fRec18[1];
			fRec16[0] = fRec17[0] * fRec16[1] + fTemp4 * fVec6[(IOTA0 - 4217) & 8191];
			fRec21[0] = fSlow9 + fConst1 * fRec21[1];
			float fTemp6 = fRec16[0] * fRec13[0] - fRec21[0] * fRec14[1];
			fVec7[IOTA0 & 4095] = fTemp6;
			fRec14[0] = fVec7[(IOTA0 - 2656) & 4095];
			float fRec15 = fRec21[0] * fTemp6;
			fVec8[IOTA0 & 4095] = fRec15 + fRec14[1];
			fRec0[0] = fRec2[1] + fRec3 + fRec13[0] * fVec8[(IOTA0 - 2656) & 4095];
			float fTemp7 = fRec20[0] * fRec25[1] + fRec0[1];
			fVec9[IOTA0 & 1023] = fTemp7;
			fRec25[0] = fVec9[(IOTA0 - 672) & 1023];
			float fRec26 = -(fRec20[0] * fTemp7);
			fVec10[IOTA0 & 8191] = fRec26 + fRec25[1];
			fRec24[0] = fRec17[0] * fRec24[1] + fTemp4 * fVec10[(IOTA0 - 4453) & 8191];
			float fTemp8 = fRec13[0] * fRec24[0] - fRec21[0] * fRec22[1];
			fVec11[IOTA0 & 2047] = fTemp8;
			fRec22[0] = fVec11[(IOTA0 - 1800) & 2047];
			float fRec23 = fRec21[0] * fTemp8;
			fVec12[IOTA0 & 2047] = fRec23 + fRec22[1];
			fRec1[0] = fRec3 + fRec2[1] + fRec13[0] * fVec12[(IOTA0 - 1800) & 2047];
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0[0]);
			output1[i0] = static_cast<FAUSTFLOAT>(fRec1[0]);
			fVec0[1] = fVec0[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			IOTA0 = IOTA0 + 1;
			fRec8[1] = fRec8[0];
			fRec6[1] = fRec6[0];
			fRec12[1] = fRec12[0];
			fRec4[1] = fRec4[0];
			fRec2[1] = fRec2[0];
			fRec13[1] = fRec13[0];
			fRec17[1] = fRec17[0];
			fRec20[1] = fRec20[0];
			fRec18[1] = fRec18[0];
			fRec16[1] = fRec16[0];
			fRec21[1] = fRec21[0];
			fRec14[1] = fRec14[0];
			fRec0[1] = fRec0[0];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			fRec22[1] = fRec22[0];
			fRec1[1] = fRec1[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "reverbDattorro.dsp"
	#define FAUST_CLASS_NAME "_reverbDattorro"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _reverbDattorro -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 8
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("bw", fHslider0, 1.0f, 0.0f, 1.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("dampings", fHslider5, 0.5f, 0.0f, 1.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("decayrate", fHslider4, 0.5f, 0.0f, 1.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("diffusion1", fHslider2, 0.5f, 0.0f, 0.95f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("diffusion2", fHslider3, 0.5f, 0.0f, 0.95f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("diffusiond1", fHslider6, 0.5f, 0.0f, 0.95f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("diffusiond2", fHslider7, 0.5f, 0.0f, 0.95f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("predelay", fHslider1, 0.5f, 0.0f, 1.0f, 0.001f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, bw, "bw", fHslider0, 1.0f, 0.0f, 1.0f, 0.001f) \
		p(HORIZONTALSLIDER, dampings, "dampings", fHslider5, 0.5f, 0.0f, 1.0f, 0.001f) \
		p(HORIZONTALSLIDER, decayrate, "decayrate", fHslider4, 0.5f, 0.0f, 1.0f, 0.001f) \
		p(HORIZONTALSLIDER, diffusion1, "diffusion1", fHslider2, 0.5f, 0.0f, 0.95f, 0.001f) \
		p(HORIZONTALSLIDER, diffusion2, "diffusion2", fHslider3, 0.5f, 0.0f, 0.95f, 0.001f) \
		p(HORIZONTALSLIDER, diffusiond1, "diffusiond1", fHslider6, 0.5f, 0.0f, 0.95f, 0.001f) \
		p(HORIZONTALSLIDER, diffusiond2, "diffusiond2", fHslider7, 0.5f, 0.0f, 0.95f, 0.001f) \
		p(HORIZONTALSLIDER, predelay, "predelay", fHslider1, 0.5f, 0.0f, 1.0f, 0.001f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

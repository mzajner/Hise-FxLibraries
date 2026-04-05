/* ------------------------------------------------------------
name: "PowerAmp"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _PowerAmp -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___PowerAmp_H__
#define  ___PowerAmp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _PowerAmp
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

struct _PowerAmpSIG0 {
	int iVec3[2];
	int iRec21[2];
	
	int getNumInputs_PowerAmpSIG0() {
		return 0;
	}
	int getNumOutputs_PowerAmpSIG0() {
		return 1;
	}
	
	void instanceInit_PowerAmpSIG0(int sample_rate) {
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			iVec3[l6] = 0;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			iRec21[l7] = 0;
		}
	}
	
	void fill_PowerAmpSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec3[0] = 1;
			iRec21[0] = (iVec3[1] + iRec21[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * static_cast<float>(iRec21[0]));
			iVec3[1] = iVec3[0];
			iRec21[1] = iRec21[0];
		}
	}

};

static _PowerAmpSIG0* new_PowerAmpSIG0() { return (_PowerAmpSIG0*)new _PowerAmpSIG0(); }
static void delete_PowerAmpSIG0(_PowerAmpSIG0* dsp) { delete dsp; }

static float _PowerAmp_faustpower2_f(float value) {
	return value * value;
}
static float _PowerAmp_faustpower3_f(float value) {
	return value * value * value;
}
static float ftbl0_PowerAmpSIG0[65536];

struct _PowerAmp final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	float fConst7;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	float fConst8;
	float fConst9;
	FAUSTFLOAT fVslider4;
	float fConst10;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fVslider7;
	float fConst11;
	float fConst12;
	float fConst13;
	int iVec0[2];
	float fConst14;
	float fConst15;
	float fConst16;
	FAUSTFLOAT fVslider8;
	float fVec1[2];
	float fConst17;
	float fRec17[2];
	float fRec16[2];
	float fConst18;
	float fConst19;
	float fConst20;
	float fConst21;
	float fVec2[2];
	int IOTA0;
	float fRec20[32];
	float fConst22;
	float fConst23;
	float fConst24;
	FAUSTFLOAT fVslider9;
	float fConst25;
	float fRec23[2];
	FAUSTFLOAT fVslider10;
	float fRec24[2];
	FAUSTFLOAT fVslider11;
	FAUSTFLOAT fCheckbox1;
	float fVec4[2];
	float fRec25[2];
	int iRec26[2];
	float fRec22[2];
	float fRec19[3];
	float fConst26;
	FAUSTFLOAT fVslider12;
	float fConst27;
	float fRec18[3];
	float fRec27[2];
	float fConst28;
	float fConst29;
	float fRec28[2];
	float fRec15[4];
	float fConst30;
	float fRec31[3];
	float fRec30[3];
	float fRec29[4];
	float fVec5[256];
	float fRec14[3];
	float fVec6[256];
	float fRec12[2];
	float fVec7[128];
	float fRec10[2];
	float fVec8[512];
	float fRec8[2];
	float fVec9[512];
	float fRec6[2];
	float fVec10[1024];
	float fRec35[2];
	float fVec11[8192];
	float fRec34[2];
	float fVec12[4096];
	float fRec32[2];
	float fVec13[4096];
	float fRec4[2];
	float fVec14[1024];
	float fRec40[2];
	float fVec15[8192];
	float fRec39[2];
	float fVec16[2048];
	float fRec37[2];
	float fVec17[2048];
	float fRec5[2];
	float fVec18[2];
	float fConst31;
	float fRec3[2];
	float fRec2[2];
	float fConst32;
	float fConst33;
	float fRec1[3];
	float fConst34;
	float fRec0[3];
	float fVec19[2];
	float fRec45[2];
	float fRec44[2];
	float fRec43[3];
	float fRec42[3];
	
	_PowerAmp() {
	}
	
	_PowerAmp(const _PowerAmp&) = default;
	
	virtual ~_PowerAmp() = default;
	
	_PowerAmp& operator=(const _PowerAmp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/bypass2:author", "Julius Smith");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _PowerAmp -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.2.0");
		m->declare("envelopes.lib/asr:author", "Yann Orlarey, Stéphane Letz");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "1.3.0");
		m->declare("filename", "PowerAmp.dsp");
		m->declare("filters.lib/dcblockerat:author", "Julius O. Smith III");
		m->declare("filters.lib/dcblockerat:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/dcblockerat:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/peak_eq:author", "Julius O. Smith III");
		m->declare("filters.lib/peak_eq:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/peak_eq:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/peak_eq_cq:author", "Julius O. Smith III");
		m->declare("filters.lib/peak_eq_cq:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/peak_eq_cq:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/resonlp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonlp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonlp:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("filters.lib/zero:author", "Julius O. Smith III");
		m->declare("filters.lib/zero:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/zero:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/speakerbp:author", "Julius O. Smith III");
		m->declare("misceffects.lib/speakerbp:license", "STK-4.3");
		m->declare("misceffects.lib/version", "2.5.1");
		m->declare("name", "PowerAmp");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "1.6.0");
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
		m->declare("spats.lib/name", "Faust Spatialization Library");
		m->declare("spats.lib/version", "1.2.1");
		m->declare("tonestacks.lib/author", "Guitarix project (<http://guitarix.sourceforge.net/>)");
		m->declare("tonestacks.lib/copyright", "Guitarix project");
		m->declare("tonestacks.lib/license", "LGPL");
		m->declare("tonestacks.lib/name", "Faust Tonestack Emulation Library");
		m->declare("tonestacks.lib/version", "1.28.0");
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
		_PowerAmpSIG0* sig0 = new_PowerAmpSIG0();
		sig0->instanceInit_PowerAmpSIG0(sample_rate);
		sig0->fill_PowerAmpSIG0(65536, ftbl0_PowerAmpSIG0);
		delete_PowerAmpSIG0(sig0);
	}
	
	void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = std::tan(15707.963f / fConst0);
		fConst2 = 1.0f / fConst1;
		fConst3 = 1.0f / ((fConst2 + 0.76536685f) / fConst1 + 1.0f);
		fConst4 = 1.0f / ((fConst2 + 1.847759f) / fConst1 + 1.0f);
		fConst5 = 251.32741f / fConst0;
		fConst6 = 1.0f / (fConst5 + 1.0f);
		fConst7 = 2.0f * fConst0;
		fConst8 = _PowerAmp_faustpower2_f(fConst7);
		fConst9 = _PowerAmp_faustpower3_f(fConst7);
		fConst10 = 3.0f * fConst9;
		fConst11 = 1.0f / std::tan(628.31854f / fConst0);
		fConst12 = 1.0f / (fConst11 + 1.0f);
		fConst13 = 1.0f - fConst11;
		fConst14 = std::tan(2513.2742f / fConst0);
		fConst15 = 1.0f / fConst14;
		fConst16 = 1.0f / (fConst15 + 1.0f);
		fConst17 = 1.0f - fConst15;
		fConst18 = 6283.1855f / fConst0;
		fConst19 = std::tan(fConst18);
		fConst20 = 2.0f * (1.0f - 1.0f / _PowerAmp_faustpower2_f(fConst19));
		fConst21 = 0.903221f / fConst14;
		fConst22 = 0.03f * fConst0 + 1.0f;
		fConst23 = 1.0f / fConst0;
		fConst24 = 44.1f / fConst0;
		fConst25 = 1.0f - fConst24;
		fConst26 = 1.0f / fConst19;
		fConst27 = 15707.963f / (fConst0 * std::sin(12566.371f / fConst0));
		fConst28 = 0.8264463f / fConst0;
		fConst29 = 3.0f * fConst0;
		fConst30 = 3.1415927f / fConst0;
		fConst31 = 1.0f - fConst5;
		fConst32 = (fConst2 + -1.847759f) / fConst1 + 1.0f;
		fConst33 = 2.0f * (1.0f - 1.0f / _PowerAmp_faustpower2_f(fConst1));
		fConst34 = (fConst2 + -0.76536685f) / fConst1 + 1.0f;
	}
	
	void instanceResetUserInterface() {
		fVslider0 = static_cast<FAUSTFLOAT>(0.25f);
		fVslider1 = static_cast<FAUSTFLOAT>(7.5f);
		fVslider2 = static_cast<FAUSTFLOAT>(4.5f);
		fVslider3 = static_cast<FAUSTFLOAT>(5.0f);
		fVslider4 = static_cast<FAUSTFLOAT>(6.0f);
		fVslider5 = static_cast<FAUSTFLOAT>(1.0f);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0f);
		fVslider6 = static_cast<FAUSTFLOAT>(1.0f);
		fVslider7 = static_cast<FAUSTFLOAT>(1.0f);
		fVslider8 = static_cast<FAUSTFLOAT>(1.0f);
		fVslider9 = static_cast<FAUSTFLOAT>(0.5f);
		fVslider10 = static_cast<FAUSTFLOAT>(6.0f);
		fVslider11 = static_cast<FAUSTFLOAT>(2.0f);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0f);
		fVslider12 = static_cast<FAUSTFLOAT>(5.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fVec1[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec17[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec16[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fVec2[l4] = 0.0f;
		}
		IOTA0 = 0;
		for (int l5 = 0; l5 < 32; l5 = l5 + 1) {
			fRec20[l5] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec23[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec24[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fVec4[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec25[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			iRec26[l12] = 0;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec22[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 3; l14 = l14 + 1) {
			fRec19[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 3; l15 = l15 + 1) {
			fRec18[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec27[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec28[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 4; l18 = l18 + 1) {
			fRec15[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 3; l19 = l19 + 1) {
			fRec31[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 3; l20 = l20 + 1) {
			fRec30[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 4; l21 = l21 + 1) {
			fRec29[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 256; l22 = l22 + 1) {
			fVec5[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 3; l23 = l23 + 1) {
			fRec14[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 256; l24 = l24 + 1) {
			fVec6[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fRec12[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 128; l26 = l26 + 1) {
			fVec7[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec10[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 512; l28 = l28 + 1) {
			fVec8[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			fRec8[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 512; l30 = l30 + 1) {
			fVec9[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec6[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 1024; l32 = l32 + 1) {
			fVec10[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			fRec35[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 8192; l34 = l34 + 1) {
			fVec11[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			fRec34[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 4096; l36 = l36 + 1) {
			fVec12[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 2; l37 = l37 + 1) {
			fRec32[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 4096; l38 = l38 + 1) {
			fVec13[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 2; l39 = l39 + 1) {
			fRec4[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 1024; l40 = l40 + 1) {
			fVec14[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 2; l41 = l41 + 1) {
			fRec40[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 8192; l42 = l42 + 1) {
			fVec15[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec39[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 2048; l44 = l44 + 1) {
			fVec16[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 2; l45 = l45 + 1) {
			fRec37[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 2048; l46 = l46 + 1) {
			fVec17[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 2; l47 = l47 + 1) {
			fRec5[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 2; l48 = l48 + 1) {
			fVec18[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 2; l49 = l49 + 1) {
			fRec3[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 2; l50 = l50 + 1) {
			fRec2[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 3; l51 = l51 + 1) {
			fRec1[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 3; l52 = l52 + 1) {
			fRec0[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 2; l53 = l53 + 1) {
			fVec19[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 2; l54 = l54 + 1) {
			fRec45[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 2; l55 = l55 + 1) {
			fRec44[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 3; l56 = l56 + 1) {
			fRec43[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 3; l57 = l57 + 1) {
			fRec42[l57] = 0.0f;
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
	
	_PowerAmp* clone() {
		return new _PowerAmp(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openHorizontalBox("Signal Chain");
		ui_interface->openHorizontalBox("British Amp");
		ui_interface->declare(&fVslider5, "01", "");
		ui_interface->declare(&fVslider5, "style", "knob");
		ui_interface->addVerticalSlider("Gain", &fVslider5, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fVslider1, "02", "");
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->addVerticalSlider("Volume", &fVslider1, FAUSTFLOAT(7.5f), FAUSTFLOAT(0.001f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fVslider3, "03", "");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->addVerticalSlider("Bass", &fVslider3, FAUSTFLOAT(5.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fVslider2, "04", "");
		ui_interface->declare(&fVslider2, "style", "knob");
		ui_interface->addVerticalSlider("Middle", &fVslider2, FAUSTFLOAT(4.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fVslider4, "05", "");
		ui_interface->declare(&fVslider4, "style", "knob");
		ui_interface->addVerticalSlider("Treble", &fVslider4, FAUSTFLOAT(6.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fVslider0, "06", "");
		ui_interface->declare(&fVslider0, "style", "knob");
		ui_interface->addVerticalSlider("Reverb", &fVslider0, FAUSTFLOAT(0.25f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Rotary");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->addCheckButton("Chorale/Tremolo", &fCheckbox1);
		ui_interface->declare(&fVslider8, "02", "");
		ui_interface->declare(&fVslider8, "style", "knob");
		ui_interface->addVerticalSlider("Gain", &fVslider8, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fVslider6, "03", "");
		ui_interface->declare(&fVslider6, "style", "knob");
		ui_interface->addVerticalSlider("Volume", &fVslider6, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fVslider9, "04", "");
		ui_interface->declare(&fVslider9, "style", "knob");
		ui_interface->addVerticalSlider("Chorale", &fVslider9, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.1f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fVslider11, "04", "");
		ui_interface->declare(&fVslider11, "style", "knob");
		ui_interface->addVerticalSlider("Ramp", &fVslider11, FAUSTFLOAT(2.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(3.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fVslider10, "04", "");
		ui_interface->declare(&fVslider10, "style", "knob");
		ui_interface->addVerticalSlider("Tremolo", &fVslider10, FAUSTFLOAT(6.0f), FAUSTFLOAT(4.0f), FAUSTFLOAT(8.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fVslider7, "05", "");
		ui_interface->declare(&fVslider7, "style", "knob");
		ui_interface->addVerticalSlider("Mix", &fVslider7, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fVslider12, "07", "");
		ui_interface->declare(&fVslider12, "style", "knob");
		ui_interface->addVerticalSlider("Horn", &fVslider12, FAUSTFLOAT(5.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fVslider0)));
		float fSlow1 = std::max<float>(0.001f, std::min<float>(1e+01f, static_cast<float>(fVslider1)));
		float fSlow2 = std::max<float>(0.0f, std::min<float>(1e+01f, static_cast<float>(fVslider2)));
		float fSlow3 = 4.84e-05f * fSlow2;
		float fSlow4 = std::exp(3.4f * (0.1f * std::max<float>(0.0f, std::min<float>(1e+01f, static_cast<float>(fVslider3))) + -1.0f));
		float fSlow5 = 0.02247f * fSlow4;
		float fSlow6 = fConst7 * (fSlow3 + fSlow5 + 0.00204974f);
		float fSlow7 = 2.3926057e-09f * fSlow2;
		float fSlow8 = fConst8 * (fSlow2 * (1.087548e-06f * fSlow4 + -6.207784e-09f - fSlow7) + 1.892924e-05f * fSlow4 + 5.6658007e-07f);
		float fSlow9 = fSlow6 + fSlow8;
		float fSlow10 = 1.2661537e-10f * fSlow4 - 2.7855382e-13f * fSlow2;
		float fSlow11 = fConst9 * (fSlow2 * (fSlow10 + -8.477725e-13f) + 1.6515048e-09f * fSlow4 + 3.6333107e-11f);
		float fSlow12 = -1.0f - (fSlow9 + fSlow11);
		float fSlow13 = 0.1f * (fSlow1 / fSlow12);
		float fSlow14 = std::max<float>(0.0f, std::min<float>(1e+01f, static_cast<float>(fVslider4)));
		float fSlow15 = fConst8 * (1.501368e-08f * fSlow14 + fSlow2 * (2.8930616e-08f - fSlow7) + fSlow4 * (1.087548e-06f * fSlow2 + 2.95724e-06f) + 6.505928e-08f);
		float fSlow16 = fSlow2 * (fSlow10 + 2.785538e-12f) + fSlow14 * (3.6333107e-12f - 3.6333106e-13f * fSlow2 + 1.6515048e-10f * fSlow4);
		float fSlow17 = fConst10 * fSlow16;
		float fSlow18 = fConst7 * (fSlow5 + fSlow3 + 1.034e-05f * fSlow14 + 0.00049434f);
		float fSlow19 = fSlow15 + fSlow17 - fSlow18;
		float fSlow20 = 2.0f * _PowerAmp_faustpower2_f(std::max<float>(0.1f, std::min<float>(1e+01f, static_cast<float>(fVslider5))));
		int iSlow21 = static_cast<int>(static_cast<float>(fCheckbox0));
		float fSlow22 = std::max<float>(0.001f, std::min<float>(2.0f, static_cast<float>(fVslider6)));
		float fSlow23 = std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fVslider7)));
		float fSlow24 = 1.0f - fSlow23;
		float fSlow25 = 2.0f * std::max<float>(0.1f, std::min<float>(1e+01f, static_cast<float>(fVslider8)));
		float fSlow26 = fConst24 * std::max<float>(0.1f, std::min<float>(1.0f, static_cast<float>(fVslider9)));
		float fSlow27 = fConst24 * std::max<float>(4.0f, std::min<float>(8.0f, static_cast<float>(fVslider10)));
		float fSlow28 = std::max<float>(1.0f, std::min<float>(3.0f, static_cast<float>(fVslider11)));
		float fSlow29 = 1.0f / std::max<float>(1.0f, fConst0 * fSlow28);
		float fSlow30 = static_cast<float>(fCheckbox1);
		int iSlow31 = fSlow30 == 0.0f;
		float fSlow32 = std::max<float>(0.0f, std::min<float>(1e+01f, static_cast<float>(fVslider12)));
		int iSlow33 = fSlow32 > 0.0f;
		float fSlow34 = fConst27 * std::pow(1e+01f, 0.05f * std::fabs(fSlow32));
		float fSlow35 = ((iSlow33) ? fConst27 : fSlow34);
		float fSlow36 = fConst26 * (fConst26 - fSlow35) + 1.0f;
		float fSlow37 = fConst26 * (fConst26 + fSlow35) + 1.0f;
		float fSlow38 = ((iSlow33) ? fSlow34 : fConst27);
		float fSlow39 = fConst26 * (fConst26 + fSlow38) + 1.0f;
		float fSlow40 = fConst26 * (fConst26 - fSlow38) + 1.0f;
		float fSlow41 = 1.0f / std::max<float>(1.0f, fConst29 * fSlow28);
		float fSlow42 = 1.0f / fSlow12;
		float fSlow43 = fSlow8 - (fSlow6 + 3.0f * (1.0f - fSlow11));
		float fSlow44 = fSlow9 - 3.0f * (fSlow11 + 1.0f);
		float fSlow45 = fSlow6 + fSlow11 + (-1.0f - fSlow8);
		float fSlow46 = fSlow18 + fSlow15;
		float fSlow47 = fSlow46 - fSlow17;
		float fSlow48 = fConst9 * fSlow16;
		float fSlow49 = fSlow18 + fSlow48 - fSlow15;
		float fSlow50 = fSlow46 + fSlow48;
		float fSlow51 = 0.2f * (fSlow1 * (1.0f - fSlow0) / fSlow12);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			float fTemp1 = ((iSlow21) ? 0.0f : fTemp0);
			iVec0[0] = 1;
			float fTemp2 = std::atan(fSlow25 * fTemp1);
			fVec1[0] = fTemp2;
			fRec17[0] = fConst16 * (0.903221f * (fTemp2 + fVec1[1]) - fConst17 * fRec17[1]);
			fRec16[0] = -(fConst12 * (fConst13 * fRec16[1] - (fRec17[0] + fRec17[1])));
			float fTemp3 = static_cast<float>(input1[i0]);
			float fTemp4 = ((iSlow21) ? 0.0f : fTemp3);
			float fTemp5 = std::atan(fSlow25 * fTemp4);
			fVec2[0] = fTemp5;
			fRec20[IOTA0 & 31] = fConst16 * (fConst21 * (fTemp5 - fVec2[1]) - fConst17 * fRec20[(IOTA0 - 1) & 31]);
			int iTemp6 = 1 - iVec0[1];
			fRec23[0] = fSlow26 + fConst25 * fRec23[1];
			fRec24[0] = fSlow27 + fConst25 * fRec24[1];
			fVec4[0] = fSlow30;
			fRec25[0] = fSlow30 + fRec25[1] * static_cast<float>(fVec4[1] >= fSlow30);
			iRec26[0] = iSlow31 * (iRec26[1] + 1);
			float fTemp7 = static_cast<float>(iRec26[0]);
			float fTemp8 = ((iTemp6) ? 0.0f : fRec22[1] + fConst23 * (fRec23[0] + fRec24[0] * std::max<float>(0.0f, std::min<float>(fSlow29 * fRec25[0], 1.0f) - fSlow29 * fTemp7)));
			fRec22[0] = fTemp8 - std::floor(fTemp8);
			float fTemp9 = ftbl0_PowerAmpSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec22[0]), 65535))] + 1.0f;
			float fTemp10 = 15.0f * fTemp9;
			int iTemp11 = static_cast<int>(fTemp10);
			float fTemp12 = std::floor(fTemp10);
			float fTemp13 = 1.0f - 0.5f * fTemp9;
			float fTemp14 = std::tan(fConst18 * (fTemp13 + 1.0f));
			float fTemp15 = 1.0f / fTemp14;
			float fTemp16 = (fTemp15 + 1.4285715f) / fTemp14 + 1.0f;
			fRec19[0] = (fRec20[(IOTA0 - static_cast<int>(std::min<float>(fConst22, static_cast<float>(std::max<int>(0, iTemp11))))) & 31] * (fTemp12 + (1.0f - fTemp10)) + (fTemp10 - fTemp12) * fRec20[(IOTA0 - static_cast<int>(std::min<float>(fConst22, static_cast<float>(std::max<int>(0, iTemp11 + 1))))) & 31]) * (1.0f - 0.3f * fTemp9) - (fRec19[2] * ((fTemp15 + -1.4285715f) / fTemp14 + 1.0f) + 2.0f * fRec19[1] * (1.0f - 1.0f / _PowerAmp_faustpower2_f(fTemp14))) / fTemp16;
			float fTemp17 = fConst20 * fRec18[1];
			fRec18[0] = (fRec19[2] + fRec19[0] + 2.0f * fRec19[1]) / fTemp16 - (fRec18[2] * fSlow36 + fTemp17) / fSlow37;
			fRec27[0] = -(fConst12 * (fConst13 * fRec27[1] - fConst11 * (fRec17[0] - fRec17[1])));
			float fTemp18 = ((iTemp6) ? 0.0f : fRec28[1] + fConst28 * (fRec23[0] + fRec24[0] * std::max<float>(0.0f, std::min<float>(fSlow41 * fRec25[0], 1.0f) - fSlow41 * fTemp7)));
			fRec28[0] = fTemp18 - std::floor(fTemp18);
			float fTemp19 = 0.5f * fRec27[0] * (ftbl0_PowerAmpSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec28[0]), 65535))] + 1.0f);
			fRec15[0] = 0.903221f * std::atan(fSlow20 * ((iSlow21) ? fTemp0 : fSlow22 * (fSlow24 * fTemp1 + fSlow23 * (fRec16[0] + (fTemp17 + fRec18[0] * fSlow39 + fRec18[2] * fSlow40) / fSlow37 - fTemp19)))) - fSlow42 * (fSlow43 * fRec15[1] + fSlow44 * fRec15[2] + fSlow45 * fRec15[3]);
			float fTemp20 = fSlow19 * fRec15[1] + fSlow47 * fRec15[2] + fSlow49 * fRec15[3] - fSlow50 * fRec15[0];
			float fTemp21 = 3e+01f - fTemp10;
			int iTemp22 = static_cast<int>(fTemp21);
			float fTemp23 = fTemp10 + std::floor(fTemp21);
			float fTemp24 = std::tan(fConst30 * (1e+03f * fTemp9 + 2e+03f));
			float fTemp25 = 1.0f / fTemp24;
			float fTemp26 = (fTemp25 + 1.4285715f) / fTemp24 + 1.0f;
			fRec31[0] = (fRec20[(IOTA0 - static_cast<int>(std::min<float>(fConst22, static_cast<float>(std::max<int>(0, iTemp22))))) & 31] * (fTemp23 + -29.0f) + (3e+01f - fTemp23) * fRec20[(IOTA0 - static_cast<int>(std::min<float>(fConst22, static_cast<float>(std::max<int>(0, iTemp22 + 1))))) & 31]) * (1.0f - 0.6f * fTemp13) - (fRec31[2] * ((fTemp25 + -1.4285715f) / fTemp24 + 1.0f) + 2.0f * fRec31[1] * (1.0f - 1.0f / _PowerAmp_faustpower2_f(fTemp24))) / fTemp26;
			float fTemp27 = fConst20 * fRec30[1];
			fRec30[0] = (fRec31[2] + fRec31[0] + 2.0f * fRec31[1]) / fTemp26 - (fSlow36 * fRec30[2] + fTemp27) / fSlow37;
			fRec29[0] = 0.903221f * std::atan(fSlow20 * ((iSlow21) ? fTemp3 : fSlow22 * (fSlow24 * fTemp4 + fSlow23 * (fRec16[0] + (fTemp27 + fRec30[0] * fSlow39 + fSlow40 * fRec30[2]) / fSlow37 - fTemp19)))) - fSlow42 * (fSlow43 * fRec29[1] + fSlow44 * fRec29[2] + fSlow45 * fRec29[3]);
			float fTemp28 = fSlow19 * fRec29[1] + fSlow47 * fRec29[2] + fSlow49 * fRec29[3] - fSlow50 * fRec29[0];
			fVec5[IOTA0 & 255] = fSlow13 * (fTemp20 + fTemp28);
			fRec14[0] = 0.01f * fRec14[2] + 0.99f * fVec5[(IOTA0 - 128) & 255];
			float fTemp29 = fRec14[0] - 0.75f * fRec12[1];
			fVec6[IOTA0 & 255] = fTemp29;
			fRec12[0] = fVec6[(IOTA0 - 142) & 255];
			float fRec13 = 0.75f * fTemp29;
			float fTemp30 = fRec13 + fRec12[1] - 0.75f * fRec10[1];
			fVec7[IOTA0 & 127] = fTemp30;
			fRec10[0] = fVec7[(IOTA0 - 107) & 127];
			float fRec11 = 0.75f * fTemp30;
			float fTemp31 = fRec11 + fRec10[1] - 0.625f * fRec8[1];
			fVec8[IOTA0 & 511] = fTemp31;
			fRec8[0] = fVec8[(IOTA0 - 379) & 511];
			float fRec9 = 0.625f * fTemp31;
			float fTemp32 = fRec9 + fRec8[1] - 0.625f * fRec6[1];
			fVec9[IOTA0 & 511] = fTemp32;
			fRec6[0] = fVec9[(IOTA0 - 277) & 511];
			float fRec7 = 0.625f * fTemp32;
			float fTemp33 = 0.7f * fRec35[1] + fRec5[1];
			fVec10[IOTA0 & 1023] = fTemp33;
			fRec35[0] = fVec10[(IOTA0 - 908) & 1023];
			float fRec36 = -(0.7f * fTemp33);
			fVec11[IOTA0 & 8191] = fRec36 + fRec35[1];
			fRec34[0] = 0.001f * fRec34[1] + 0.999f * fVec11[(IOTA0 - 4217) & 8191];
			float fTemp34 = fRec34[0] - fRec32[1];
			fVec12[IOTA0 & 4095] = fTemp34;
			fRec32[0] = 0.5f * fVec12[(IOTA0 - 2656) & 4095];
			float fRec33 = 0.25f * fTemp34;
			fVec13[IOTA0 & 4095] = fRec33 + fRec32[1];
			fRec4[0] = fRec6[1] + fRec7 + 0.5f * fVec13[(IOTA0 - 2656) & 4095];
			float fTemp35 = 0.7f * fRec40[1] + fRec4[1];
			fVec14[IOTA0 & 1023] = fTemp35;
			fRec40[0] = fVec14[(IOTA0 - 672) & 1023];
			float fRec41 = -(0.7f * fTemp35);
			fVec15[IOTA0 & 8191] = fRec41 + fRec40[1];
			fRec39[0] = 0.001f * fRec39[1] + 0.999f * fVec15[(IOTA0 - 4453) & 8191];
			float fTemp36 = fRec39[0] - fRec37[1];
			fVec16[IOTA0 & 2047] = fTemp36;
			fRec37[0] = 0.5f * fVec16[(IOTA0 - 1800) & 2047];
			float fRec38 = 0.25f * fTemp36;
			fVec17[IOTA0 & 2047] = fRec38 + fRec37[1];
			fRec5[0] = fRec7 + fRec6[1] + 0.5f * fVec17[(IOTA0 - 1800) & 2047];
			float fTemp37 = fSlow0 * fRec4[0] + fSlow51 * fTemp20;
			fVec18[0] = fTemp37;
			fRec3[0] = fConst6 * (fTemp37 - fVec18[1] + fConst31 * fRec3[1]);
			fRec2[0] = fConst6 * (fRec3[0] - fRec3[1] + fConst31 * fRec2[1]);
			fRec1[0] = fRec2[0] - fConst4 * (fConst32 * fRec1[2] + fConst33 * fRec1[1]);
			fRec0[0] = fConst4 * (fRec1[2] + fRec1[0] + 2.0f * fRec1[1]) - fConst3 * (fConst34 * fRec0[2] + fConst33 * fRec0[1]);
			output0[i0] = static_cast<FAUSTFLOAT>(fConst3 * (fRec0[2] + fRec0[0] + 2.0f * fRec0[1]));
			float fTemp38 = fSlow0 * fRec5[0] + fSlow51 * fTemp28;
			fVec19[0] = fTemp38;
			fRec45[0] = fConst6 * (fTemp38 - fVec19[1] + fConst31 * fRec45[1]);
			fRec44[0] = fConst6 * (fRec45[0] - fRec45[1] + fConst31 * fRec44[1]);
			fRec43[0] = fRec44[0] - fConst4 * (fConst32 * fRec43[2] + fConst33 * fRec43[1]);
			fRec42[0] = fConst4 * (fRec43[2] + fRec43[0] + 2.0f * fRec43[1]) - fConst3 * (fConst34 * fRec42[2] + fConst33 * fRec42[1]);
			output1[i0] = static_cast<FAUSTFLOAT>(fConst3 * (fRec42[2] + fRec42[0] + 2.0f * fRec42[1]));
			iVec0[1] = iVec0[0];
			fVec1[1] = fVec1[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fVec2[1] = fVec2[0];
			IOTA0 = IOTA0 + 1;
			fRec23[1] = fRec23[0];
			fRec24[1] = fRec24[0];
			fVec4[1] = fVec4[0];
			fRec25[1] = fRec25[0];
			iRec26[1] = iRec26[0];
			fRec22[1] = fRec22[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fRec27[1] = fRec27[0];
			fRec28[1] = fRec28[0];
			for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
				fRec15[j0] = fRec15[j0 - 1];
			}
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			for (int j1 = 3; j1 > 0; j1 = j1 - 1) {
				fRec29[j1] = fRec29[j1 - 1];
			}
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec12[1] = fRec12[0];
			fRec10[1] = fRec10[0];
			fRec8[1] = fRec8[0];
			fRec6[1] = fRec6[0];
			fRec35[1] = fRec35[0];
			fRec34[1] = fRec34[0];
			fRec32[1] = fRec32[0];
			fRec4[1] = fRec4[0];
			fRec40[1] = fRec40[0];
			fRec39[1] = fRec39[0];
			fRec37[1] = fRec37[0];
			fRec5[1] = fRec5[0];
			fVec18[1] = fVec18[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fVec19[1] = fVec19[0];
			fRec45[1] = fRec45[0];
			fRec44[1] = fRec44[0];
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "PowerAmp.dsp"
	#define FAUST_CLASS_NAME "_PowerAmp"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _PowerAmp -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 15
	#define FAUST_PASSIVES 0

	FAUST_ADDVERTICALSLIDER("Signal Chain/British Amp/Gain", fVslider5, 1.0f, 0.1f, 1e+01f, 0.1f);
	FAUST_ADDVERTICALSLIDER("Signal Chain/British Amp/Volume", fVslider1, 7.5f, 0.001f, 1e+01f, 0.001f);
	FAUST_ADDVERTICALSLIDER("Signal Chain/British Amp/Bass", fVslider3, 5.0f, 0.0f, 1e+01f, 0.01f);
	FAUST_ADDVERTICALSLIDER("Signal Chain/British Amp/Middle", fVslider2, 4.5f, 0.0f, 1e+01f, 0.01f);
	FAUST_ADDVERTICALSLIDER("Signal Chain/British Amp/Treble", fVslider4, 6.0f, 0.0f, 1e+01f, 0.01f);
	FAUST_ADDVERTICALSLIDER("Signal Chain/British Amp/Reverb", fVslider0, 0.25f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDCHECKBOX("Signal Chain/Rotary/Bypass", fCheckbox0);
	FAUST_ADDCHECKBOX("Signal Chain/Rotary/Chorale/Tremolo", fCheckbox1);
	FAUST_ADDVERTICALSLIDER("Signal Chain/Rotary/Gain", fVslider8, 1.0f, 0.1f, 1e+01f, 0.1f);
	FAUST_ADDVERTICALSLIDER("Signal Chain/Rotary/Volume", fVslider6, 1.0f, 0.001f, 2.0f, 0.01f);
	FAUST_ADDVERTICALSLIDER("Signal Chain/Rotary/Chorale", fVslider9, 0.5f, 0.1f, 1.0f, 0.01f);
	FAUST_ADDVERTICALSLIDER("Signal Chain/Rotary/Ramp", fVslider11, 2.0f, 1.0f, 3.0f, 0.01f);
	FAUST_ADDVERTICALSLIDER("Signal Chain/Rotary/Tremolo", fVslider10, 6.0f, 4.0f, 8.0f, 0.01f);
	FAUST_ADDVERTICALSLIDER("Signal Chain/Rotary/Mix", fVslider7, 1.0f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDVERTICALSLIDER("Signal Chain/Rotary/Horn", fVslider12, 5.0f, 0.0f, 1e+01f, 0.1f);

	#define FAUST_LIST_ACTIVES(p) \
		p(VERTICALSLIDER, Gain, "Signal Chain/British Amp/Gain", fVslider5, 1.0f, 0.1f, 1e+01f, 0.1f) \
		p(VERTICALSLIDER, Volume, "Signal Chain/British Amp/Volume", fVslider1, 7.5f, 0.001f, 1e+01f, 0.001f) \
		p(VERTICALSLIDER, Bass, "Signal Chain/British Amp/Bass", fVslider3, 5.0f, 0.0f, 1e+01f, 0.01f) \
		p(VERTICALSLIDER, Middle, "Signal Chain/British Amp/Middle", fVslider2, 4.5f, 0.0f, 1e+01f, 0.01f) \
		p(VERTICALSLIDER, Treble, "Signal Chain/British Amp/Treble", fVslider4, 6.0f, 0.0f, 1e+01f, 0.01f) \
		p(VERTICALSLIDER, Reverb, "Signal Chain/British Amp/Reverb", fVslider0, 0.25f, 0.0f, 1.0f, 0.01f) \
		p(CHECKBOX, Bypass, "Signal Chain/Rotary/Bypass", fCheckbox0, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(CHECKBOX, Chorale/Tremolo, "Signal Chain/Rotary/Chorale/Tremolo", fCheckbox1, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(VERTICALSLIDER, Gain, "Signal Chain/Rotary/Gain", fVslider8, 1.0f, 0.1f, 1e+01f, 0.1f) \
		p(VERTICALSLIDER, Volume, "Signal Chain/Rotary/Volume", fVslider6, 1.0f, 0.001f, 2.0f, 0.01f) \
		p(VERTICALSLIDER, Chorale, "Signal Chain/Rotary/Chorale", fVslider9, 0.5f, 0.1f, 1.0f, 0.01f) \
		p(VERTICALSLIDER, Ramp, "Signal Chain/Rotary/Ramp", fVslider11, 2.0f, 1.0f, 3.0f, 0.01f) \
		p(VERTICALSLIDER, Tremolo, "Signal Chain/Rotary/Tremolo", fVslider10, 6.0f, 4.0f, 8.0f, 0.01f) \
		p(VERTICALSLIDER, Mix, "Signal Chain/Rotary/Mix", fVslider7, 1.0f, 0.0f, 1.0f, 0.01f) \
		p(VERTICALSLIDER, Horn, "Signal Chain/Rotary/Horn", fVslider12, 5.0f, 0.0f, 1e+01f, 0.1f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

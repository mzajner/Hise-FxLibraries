/* ------------------------------------------------------------
author: "JOS, Revised by RM"
name: "zitaRev"
version: "0.0"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _zitaRev -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___zitaRev_H__
#define  ___zitaRev_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _zitaRev
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

static float _zitaRev_faustpower2_f(float value) {
	return value * value;
}

struct _zitaRev final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fVslider0;
	float fConst2;
	float fRec0[2];
	int IOTA0;
	float fVec0[16384];
	FAUSTFLOAT fVslider1;
	float fRec1[2];
	float fConst3;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fVslider5;
	float fConst4;
	float fConst5;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fVslider8;
	float fConst6;
	FAUSTFLOAT fVslider9;
	float fRec15[2];
	float fRec14[2];
	float fVec1[32768];
	float fConst7;
	int iConst8;
	float fVec2[16384];
	float fConst9;
	FAUSTFLOAT fVslider10;
	float fVec3[2048];
	int iConst10;
	float fRec12[2];
	float fConst11;
	float fConst12;
	float fRec19[2];
	float fRec18[2];
	float fVec4[32768];
	float fConst13;
	int iConst14;
	float fVec5[4096];
	int iConst15;
	float fRec16[2];
	float fConst16;
	float fConst17;
	float fRec23[2];
	float fRec22[2];
	float fVec6[16384];
	float fConst18;
	int iConst19;
	float fVec7[4096];
	int iConst20;
	float fRec20[2];
	float fConst21;
	float fConst22;
	float fRec27[2];
	float fRec26[2];
	float fVec8[32768];
	float fConst23;
	int iConst24;
	float fVec9[4096];
	int iConst25;
	float fRec24[2];
	float fConst26;
	float fConst27;
	float fRec31[2];
	float fRec30[2];
	float fVec10[16384];
	float fConst28;
	int iConst29;
	float fVec11[2048];
	int iConst30;
	float fRec28[2];
	float fConst31;
	float fConst32;
	float fRec35[2];
	float fRec34[2];
	float fVec12[16384];
	float fConst33;
	int iConst34;
	float fVec13[4096];
	int iConst35;
	float fRec32[2];
	float fConst36;
	float fConst37;
	float fRec39[2];
	float fRec38[2];
	float fVec14[16384];
	float fConst38;
	int iConst39;
	float fVec15[4096];
	int iConst40;
	float fRec36[2];
	float fConst41;
	float fConst42;
	float fRec43[2];
	float fRec42[2];
	float fVec16[16384];
	float fConst43;
	int iConst44;
	float fVec17[2048];
	int iConst45;
	float fRec40[2];
	float fRec4[3];
	float fRec5[3];
	float fRec6[3];
	float fRec7[3];
	float fRec8[3];
	float fRec9[3];
	float fRec10[3];
	float fRec11[3];
	float fRec3[3];
	float fRec2[3];
	float fRec45[3];
	float fRec44[3];
	
	_zitaRev() {
	}
	
	_zitaRev(const _zitaRev&) = default;
	
	virtual ~_zitaRev() = default;
	
	_zitaRev& operator=(const _zitaRev&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "JOS, Revised by RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _zitaRev -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.2.0");
		m->declare("demos.lib/name", "Faust Demos Library");
		m->declare("demos.lib/version", "1.4.0");
		m->declare("demos.lib/zita_rev1:author", "Julius O. Smith III");
		m->declare("demos.lib/zita_rev1:licence", "MIT");
		m->declare("description", "Example GUI for `zita_rev1_stereo` (mostly following the Linux `zita-rev1` GUI).");
		m->declare("filename", "zitaRev.dsp");
		m->declare("filters.lib/allpass_comb:author", "Julius O. Smith III");
		m->declare("filters.lib/allpass_comb:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/allpass_comb:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/peak_eq_rm:author", "Julius O. Smith III");
		m->declare("filters.lib/peak_eq_rm:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/peak_eq_rm:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "zitaRev");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("reverbs.lib/name", "Faust Reverb Library");
		m->declare("reverbs.lib/version", "1.5.1");
		m->declare("routes.lib/hadamard:author", "Remy Muller, revised by Romain Michon");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "1.2.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
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
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 6.2831855f / fConst0;
		fConst4 = std::floor(0.219991f * fConst0 + 0.5f);
		fConst5 = 6.9077554f * (fConst4 / fConst0);
		fConst6 = 3.1415927f / fConst0;
		fConst7 = std::floor(0.019123f * fConst0 + 0.5f);
		iConst8 = static_cast<int>(std::min<float>(16384.0f, std::max<float>(0.0f, fConst4 - fConst7)));
		fConst9 = 0.001f * fConst0;
		iConst10 = static_cast<int>(std::min<float>(1024.0f, std::max<float>(0.0f, fConst7 + -1.0f)));
		fConst11 = std::floor(0.256891f * fConst0 + 0.5f);
		fConst12 = 6.9077554f * (fConst11 / fConst0);
		fConst13 = std::floor(0.027333f * fConst0 + 0.5f);
		iConst14 = static_cast<int>(std::min<float>(16384.0f, std::max<float>(0.0f, fConst11 - fConst13)));
		iConst15 = static_cast<int>(std::min<float>(2048.0f, std::max<float>(0.0f, fConst13 + -1.0f)));
		fConst16 = std::floor(0.192303f * fConst0 + 0.5f);
		fConst17 = 6.9077554f * (fConst16 / fConst0);
		fConst18 = std::floor(0.029291f * fConst0 + 0.5f);
		iConst19 = static_cast<int>(std::min<float>(8192.0f, std::max<float>(0.0f, fConst16 - fConst18)));
		iConst20 = static_cast<int>(std::min<float>(2048.0f, std::max<float>(0.0f, fConst18 + -1.0f)));
		fConst21 = std::floor(0.210389f * fConst0 + 0.5f);
		fConst22 = 6.9077554f * (fConst21 / fConst0);
		fConst23 = std::floor(0.024421f * fConst0 + 0.5f);
		iConst24 = static_cast<int>(std::min<float>(16384.0f, std::max<float>(0.0f, fConst21 - fConst23)));
		iConst25 = static_cast<int>(std::min<float>(2048.0f, std::max<float>(0.0f, fConst23 + -1.0f)));
		fConst26 = std::floor(0.125f * fConst0 + 0.5f);
		fConst27 = 6.9077554f * (fConst26 / fConst0);
		fConst28 = std::floor(0.013458f * fConst0 + 0.5f);
		iConst29 = static_cast<int>(std::min<float>(8192.0f, std::max<float>(0.0f, fConst26 - fConst28)));
		iConst30 = static_cast<int>(std::min<float>(1024.0f, std::max<float>(0.0f, fConst28 + -1.0f)));
		fConst31 = std::floor(0.127837f * fConst0 + 0.5f);
		fConst32 = 6.9077554f * (fConst31 / fConst0);
		fConst33 = std::floor(0.031604f * fConst0 + 0.5f);
		iConst34 = static_cast<int>(std::min<float>(8192.0f, std::max<float>(0.0f, fConst31 - fConst33)));
		iConst35 = static_cast<int>(std::min<float>(2048.0f, std::max<float>(0.0f, fConst33 + -1.0f)));
		fConst36 = std::floor(0.174713f * fConst0 + 0.5f);
		fConst37 = 6.9077554f * (fConst36 / fConst0);
		fConst38 = std::floor(0.022904f * fConst0 + 0.5f);
		iConst39 = static_cast<int>(std::min<float>(8192.0f, std::max<float>(0.0f, fConst36 - fConst38)));
		iConst40 = static_cast<int>(std::min<float>(2048.0f, std::max<float>(0.0f, fConst38 + -1.0f)));
		fConst41 = std::floor(0.153129f * fConst0 + 0.5f);
		fConst42 = 6.9077554f * (fConst41 / fConst0);
		fConst43 = std::floor(0.020346f * fConst0 + 0.5f);
		iConst44 = static_cast<int>(std::min<float>(8192.0f, std::max<float>(0.0f, fConst41 - fConst43)));
		iConst45 = static_cast<int>(std::min<float>(1024.0f, std::max<float>(0.0f, fConst43 + -1.0f)));
	}
	
	void instanceResetUserInterface() {
		fVslider0 = static_cast<FAUSTFLOAT>(-2e+01f);
		fVslider1 = static_cast<FAUSTFLOAT>(0.0f);
		fVslider2 = static_cast<FAUSTFLOAT>(1.5e+03f);
		fVslider3 = static_cast<FAUSTFLOAT>(0.0f);
		fVslider4 = static_cast<FAUSTFLOAT>(315.0f);
		fVslider5 = static_cast<FAUSTFLOAT>(0.0f);
		fVslider6 = static_cast<FAUSTFLOAT>(2.0f);
		fVslider7 = static_cast<FAUSTFLOAT>(6e+03f);
		fVslider8 = static_cast<FAUSTFLOAT>(3.0f);
		fVslider9 = static_cast<FAUSTFLOAT>(2e+02f);
		fVslider10 = static_cast<FAUSTFLOAT>(6e+01f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		IOTA0 = 0;
		for (int l1 = 0; l1 < 16384; l1 = l1 + 1) {
			fVec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec15[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec14[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 32768; l5 = l5 + 1) {
			fVec1[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 16384; l6 = l6 + 1) {
			fVec2[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2048; l7 = l7 + 1) {
			fVec3[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec12[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec19[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec18[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 32768; l11 = l11 + 1) {
			fVec4[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 4096; l12 = l12 + 1) {
			fVec5[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec16[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec23[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec22[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 16384; l16 = l16 + 1) {
			fVec6[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 4096; l17 = l17 + 1) {
			fVec7[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec20[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec27[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fRec26[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 32768; l21 = l21 + 1) {
			fVec8[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 4096; l22 = l22 + 1) {
			fVec9[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec24[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fRec31[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fRec30[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 16384; l26 = l26 + 1) {
			fVec10[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2048; l27 = l27 + 1) {
			fVec11[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			fRec28[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			fRec35[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			fRec34[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 16384; l31 = l31 + 1) {
			fVec12[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 4096; l32 = l32 + 1) {
			fVec13[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			fRec32[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			fRec39[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			fRec38[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 16384; l36 = l36 + 1) {
			fVec14[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 4096; l37 = l37 + 1) {
			fVec15[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 2; l38 = l38 + 1) {
			fRec36[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 2; l39 = l39 + 1) {
			fRec43[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			fRec42[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 16384; l41 = l41 + 1) {
			fVec16[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 2048; l42 = l42 + 1) {
			fVec17[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec40[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 3; l44 = l44 + 1) {
			fRec4[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 3; l45 = l45 + 1) {
			fRec5[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 3; l46 = l46 + 1) {
			fRec6[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 3; l47 = l47 + 1) {
			fRec7[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 3; l48 = l48 + 1) {
			fRec8[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 3; l49 = l49 + 1) {
			fRec9[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 3; l50 = l50 + 1) {
			fRec10[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 3; l51 = l51 + 1) {
			fRec11[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 3; l52 = l52 + 1) {
			fRec3[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 3; l53 = l53 + 1) {
			fRec2[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 3; l54 = l54 + 1) {
			fRec45[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 3; l55 = l55 + 1) {
			fRec44[l55] = 0.0f;
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
	
	_zitaRev* clone() {
		return new _zitaRev(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references");
		ui_interface->openHorizontalBox("Zita_Rev1");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("Input");
		ui_interface->declare(&fVslider10, "1", "");
		ui_interface->declare(&fVslider10, "style", "knob");
		ui_interface->declare(&fVslider10, "tooltip", "Delay in ms         before reverberation begins");
		ui_interface->declare(&fVslider10, "unit", "ms");
		ui_interface->addVerticalSlider("In Delay", &fVslider10, FAUSTFLOAT(6e+01f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Decay Times in Bands (see tooltips)");
		ui_interface->declare(&fVslider9, "1", "");
		ui_interface->declare(&fVslider9, "scale", "log");
		ui_interface->declare(&fVslider9, "style", "knob");
		ui_interface->declare(&fVslider9, "tooltip", "Crossover frequency (Hz) separating low and middle frequencies");
		ui_interface->declare(&fVslider9, "unit", "Hz");
		ui_interface->addVerticalSlider("LF X", &fVslider9, FAUSTFLOAT(2e+02f), FAUSTFLOAT(5e+01f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fVslider8, "2", "");
		ui_interface->declare(&fVslider8, "scale", "log");
		ui_interface->declare(&fVslider8, "style", "knob");
		ui_interface->declare(&fVslider8, "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band");
		ui_interface->declare(&fVslider8, "unit", "s");
		ui_interface->addVerticalSlider("Low RT60", &fVslider8, FAUSTFLOAT(3.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(8.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fVslider6, "3", "");
		ui_interface->declare(&fVslider6, "scale", "log");
		ui_interface->declare(&fVslider6, "style", "knob");
		ui_interface->declare(&fVslider6, "tooltip", "T60 = time (in seconds) to decay 60dB in middle band");
		ui_interface->declare(&fVslider6, "unit", "s");
		ui_interface->addVerticalSlider("Mid RT60", &fVslider6, FAUSTFLOAT(2.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(8.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fVslider7, "4", "");
		ui_interface->declare(&fVslider7, "scale", "log");
		ui_interface->declare(&fVslider7, "style", "knob");
		ui_interface->declare(&fVslider7, "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60");
		ui_interface->declare(&fVslider7, "unit", "Hz");
		ui_interface->addVerticalSlider("HF Damping", &fVslider7, FAUSTFLOAT(6e+03f), FAUSTFLOAT(1.5e+03f), FAUSTFLOAT(2.352e+04f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("RM Peaking Equalizer 1");
		ui_interface->declare(&fVslider4, "1", "");
		ui_interface->declare(&fVslider4, "scale", "log");
		ui_interface->declare(&fVslider4, "style", "knob");
		ui_interface->declare(&fVslider4, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 1");
		ui_interface->declare(&fVslider4, "unit", "Hz");
		ui_interface->addVerticalSlider("Eq1 Freq", &fVslider4, FAUSTFLOAT(315.0f), FAUSTFLOAT(4e+01f), FAUSTFLOAT(2.5e+03f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fVslider5, "2", "");
		ui_interface->declare(&fVslider5, "style", "knob");
		ui_interface->declare(&fVslider5, "tooltip", "Peak level         in dB of second-order Regalia-Mitra peaking equalizer section 1");
		ui_interface->declare(&fVslider5, "unit", "dB");
		ui_interface->addVerticalSlider("Eq1 Level", &fVslider5, FAUSTFLOAT(0.0f), FAUSTFLOAT(-15.0f), FAUSTFLOAT(15.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openHorizontalBox("RM Peaking Equalizer 2");
		ui_interface->declare(&fVslider2, "1", "");
		ui_interface->declare(&fVslider2, "scale", "log");
		ui_interface->declare(&fVslider2, "style", "knob");
		ui_interface->declare(&fVslider2, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 2");
		ui_interface->declare(&fVslider2, "unit", "Hz");
		ui_interface->addVerticalSlider("Eq2 Freq", &fVslider2, FAUSTFLOAT(1.5e+03f), FAUSTFLOAT(1.6e+02f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fVslider3, "2", "");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->declare(&fVslider3, "tooltip", "Peak level         in dB of second-order Regalia-Mitra peaking equalizer section 2");
		ui_interface->declare(&fVslider3, "unit", "dB");
		ui_interface->addVerticalSlider("Eq2 Level", &fVslider3, FAUSTFLOAT(0.0f), FAUSTFLOAT(-15.0f), FAUSTFLOAT(15.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->declare(0, "5", "");
		ui_interface->openHorizontalBox("Output");
		ui_interface->declare(&fVslider1, "1", "");
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->declare(&fVslider1, "tooltip", "Ratio of dry and wet signal. -1 = fully wet, +1 = fully dry");
		ui_interface->addVerticalSlider("Wet/Dry Mix", &fVslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fVslider0, "2", "");
		ui_interface->declare(&fVslider0, "style", "knob");
		ui_interface->declare(&fVslider0, "tooltip", "Output scale         factor");
		ui_interface->declare(&fVslider0, "unit", "dB");
		ui_interface->addVerticalSlider("Level", &fVslider0, FAUSTFLOAT(-2e+01f), FAUSTFLOAT(-7e+01f), FAUSTFLOAT(4e+01f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst1 * std::pow(1e+01f, 0.05f * std::max<float>(-7e+01f, std::min<float>(4e+01f, static_cast<float>(fVslider0))));
		float fSlow1 = fConst1 * std::max<float>(-1.0f, std::min<float>(1.0f, static_cast<float>(fVslider1)));
		float fSlow2 = std::max<float>(1.6e+02f, std::min<float>(1e+04f, static_cast<float>(fVslider2)));
		float fSlow3 = std::pow(1e+01f, 0.05f * std::max<float>(-15.0f, std::min<float>(15.0f, static_cast<float>(fVslider3))));
		float fSlow4 = fConst3 * (fSlow2 / std::sqrt(std::max<float>(0.0f, fSlow3)));
		float fSlow5 = (1.0f - fSlow4) / (fSlow4 + 1.0f);
		float fSlow6 = std::max<float>(4e+01f, std::min<float>(2.5e+03f, static_cast<float>(fVslider4)));
		float fSlow7 = std::pow(1e+01f, 0.05f * std::max<float>(-15.0f, std::min<float>(15.0f, static_cast<float>(fVslider5))));
		float fSlow8 = fConst3 * (fSlow6 / std::sqrt(std::max<float>(0.0f, fSlow7)));
		float fSlow9 = (1.0f - fSlow8) / (fSlow8 + 1.0f);
		float fSlow10 = std::max<float>(1.0f, std::min<float>(8.0f, static_cast<float>(fVslider6)));
		float fSlow11 = std::exp(-(fConst5 / fSlow10));
		float fSlow12 = std::cos(fConst3 * std::max<float>(1.5e+03f, std::min<float>(2.352e+04f, static_cast<float>(fVslider7))));
		float fSlow13 = _zitaRev_faustpower2_f(fSlow11);
		float fSlow14 = 1.0f - fSlow12 * fSlow13;
		float fSlow15 = 1.0f - fSlow13;
		float fSlow16 = std::sqrt(std::max<float>(0.0f, _zitaRev_faustpower2_f(fSlow14) / _zitaRev_faustpower2_f(fSlow15) + -1.0f));
		float fSlow17 = fSlow14 / fSlow15;
		float fSlow18 = fSlow11 * (fSlow16 + (1.0f - fSlow17));
		float fSlow19 = std::max<float>(1.0f, std::min<float>(8.0f, static_cast<float>(fVslider8)));
		float fSlow20 = std::exp(-(fConst5 / fSlow19)) / fSlow11 + -1.0f;
		float fSlow21 = 1.0f / std::tan(fConst6 * std::max<float>(5e+01f, std::min<float>(1e+03f, static_cast<float>(fVslider9))));
		float fSlow22 = 1.0f / (fSlow21 + 1.0f);
		float fSlow23 = 1.0f - fSlow21;
		float fSlow24 = fSlow17 - fSlow16;
		int iSlow25 = static_cast<int>(std::min<float>(8192.0f, std::max<float>(0.0f, fConst9 * std::max<float>(2e+01f, std::min<float>(1e+02f, static_cast<float>(fVslider10))))));
		float fSlow26 = std::exp(-(fConst12 / fSlow10));
		float fSlow27 = _zitaRev_faustpower2_f(fSlow26);
		float fSlow28 = 1.0f - fSlow12 * fSlow27;
		float fSlow29 = 1.0f - fSlow27;
		float fSlow30 = std::sqrt(std::max<float>(0.0f, _zitaRev_faustpower2_f(fSlow28) / _zitaRev_faustpower2_f(fSlow29) + -1.0f));
		float fSlow31 = fSlow28 / fSlow29;
		float fSlow32 = fSlow26 * (fSlow30 + (1.0f - fSlow31));
		float fSlow33 = std::exp(-(fConst12 / fSlow19)) / fSlow26 + -1.0f;
		float fSlow34 = fSlow31 - fSlow30;
		float fSlow35 = std::exp(-(fConst17 / fSlow10));
		float fSlow36 = _zitaRev_faustpower2_f(fSlow35);
		float fSlow37 = 1.0f - fSlow12 * fSlow36;
		float fSlow38 = 1.0f - fSlow36;
		float fSlow39 = std::sqrt(std::max<float>(0.0f, _zitaRev_faustpower2_f(fSlow37) / _zitaRev_faustpower2_f(fSlow38) + -1.0f));
		float fSlow40 = fSlow37 / fSlow38;
		float fSlow41 = fSlow35 * (fSlow39 + (1.0f - fSlow40));
		float fSlow42 = std::exp(-(fConst17 / fSlow19)) / fSlow35 + -1.0f;
		float fSlow43 = fSlow40 - fSlow39;
		float fSlow44 = std::exp(-(fConst22 / fSlow10));
		float fSlow45 = _zitaRev_faustpower2_f(fSlow44);
		float fSlow46 = 1.0f - fSlow12 * fSlow45;
		float fSlow47 = 1.0f - fSlow45;
		float fSlow48 = std::sqrt(std::max<float>(0.0f, _zitaRev_faustpower2_f(fSlow46) / _zitaRev_faustpower2_f(fSlow47) + -1.0f));
		float fSlow49 = fSlow46 / fSlow47;
		float fSlow50 = fSlow44 * (fSlow48 + (1.0f - fSlow49));
		float fSlow51 = std::exp(-(fConst22 / fSlow19)) / fSlow44 + -1.0f;
		float fSlow52 = fSlow49 - fSlow48;
		float fSlow53 = std::exp(-(fConst27 / fSlow10));
		float fSlow54 = _zitaRev_faustpower2_f(fSlow53);
		float fSlow55 = 1.0f - fSlow12 * fSlow54;
		float fSlow56 = 1.0f - fSlow54;
		float fSlow57 = std::sqrt(std::max<float>(0.0f, _zitaRev_faustpower2_f(fSlow55) / _zitaRev_faustpower2_f(fSlow56) + -1.0f));
		float fSlow58 = fSlow55 / fSlow56;
		float fSlow59 = fSlow53 * (fSlow57 + (1.0f - fSlow58));
		float fSlow60 = std::exp(-(fConst27 / fSlow19)) / fSlow53 + -1.0f;
		float fSlow61 = fSlow58 - fSlow57;
		float fSlow62 = std::exp(-(fConst32 / fSlow10));
		float fSlow63 = _zitaRev_faustpower2_f(fSlow62);
		float fSlow64 = 1.0f - fSlow12 * fSlow63;
		float fSlow65 = 1.0f - fSlow63;
		float fSlow66 = std::sqrt(std::max<float>(0.0f, _zitaRev_faustpower2_f(fSlow64) / _zitaRev_faustpower2_f(fSlow65) + -1.0f));
		float fSlow67 = fSlow64 / fSlow65;
		float fSlow68 = fSlow62 * (fSlow66 + (1.0f - fSlow67));
		float fSlow69 = std::exp(-(fConst32 / fSlow19)) / fSlow62 + -1.0f;
		float fSlow70 = fSlow67 - fSlow66;
		float fSlow71 = std::exp(-(fConst37 / fSlow10));
		float fSlow72 = _zitaRev_faustpower2_f(fSlow71);
		float fSlow73 = 1.0f - fSlow12 * fSlow72;
		float fSlow74 = 1.0f - fSlow72;
		float fSlow75 = std::sqrt(std::max<float>(0.0f, _zitaRev_faustpower2_f(fSlow73) / _zitaRev_faustpower2_f(fSlow74) + -1.0f));
		float fSlow76 = fSlow73 / fSlow74;
		float fSlow77 = fSlow71 * (fSlow75 + (1.0f - fSlow76));
		float fSlow78 = std::exp(-(fConst37 / fSlow19)) / fSlow71 + -1.0f;
		float fSlow79 = fSlow76 - fSlow75;
		float fSlow80 = std::exp(-(fConst42 / fSlow10));
		float fSlow81 = _zitaRev_faustpower2_f(fSlow80);
		float fSlow82 = 1.0f - fSlow81 * fSlow12;
		float fSlow83 = 1.0f - fSlow81;
		float fSlow84 = std::sqrt(std::max<float>(0.0f, _zitaRev_faustpower2_f(fSlow82) / _zitaRev_faustpower2_f(fSlow83) + -1.0f));
		float fSlow85 = fSlow82 / fSlow83;
		float fSlow86 = fSlow80 * (fSlow84 + (1.0f - fSlow85));
		float fSlow87 = std::exp(-(fConst42 / fSlow19)) / fSlow80 + -1.0f;
		float fSlow88 = fSlow85 - fSlow84;
		float fSlow89 = std::cos(fConst3 * fSlow6) * (fSlow9 + 1.0f);
		float fSlow90 = std::cos(fConst3 * fSlow2) * (fSlow5 + 1.0f);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[0] = fSlow0 + fConst2 * fRec0[1];
			float fTemp0 = static_cast<float>(input0[i0]);
			fVec0[IOTA0 & 16383] = fTemp0;
			fRec1[0] = fSlow1 + fConst2 * fRec1[1];
			float fTemp1 = fRec1[0] + 1.0f;
			float fTemp2 = 1.0f - 0.5f * fTemp1;
			fRec15[0] = -(fSlow22 * (fSlow23 * fRec15[1] - (fRec11[1] + fRec11[2])));
			fRec14[0] = fSlow18 * (fRec11[1] + fSlow20 * fRec15[0]) + fSlow24 * fRec14[1];
			fVec1[IOTA0 & 32767] = 0.35355338f * fRec14[0] + 1e-20f;
			float fTemp3 = 0.6f * fRec12[1] + fVec1[(IOTA0 - iConst8) & 32767];
			float fTemp4 = static_cast<float>(input1[i0]);
			fVec2[IOTA0 & 16383] = fTemp4;
			float fTemp5 = 0.3f * fVec2[(IOTA0 - iSlow25) & 16383];
			fVec3[IOTA0 & 2047] = fTemp3 - fTemp5;
			fRec12[0] = fVec3[(IOTA0 - iConst10) & 2047];
			float fRec13 = 0.6f * (fTemp5 - fTemp3);
			fRec19[0] = -(fSlow22 * (fSlow23 * fRec19[1] - (fRec7[1] + fRec7[2])));
			fRec18[0] = fSlow32 * (fRec7[1] + fSlow33 * fRec19[0]) + fSlow34 * fRec18[1];
			fVec4[IOTA0 & 32767] = 0.35355338f * fRec18[0] + 1e-20f;
			float fTemp6 = 0.6f * fRec16[1] + fVec4[(IOTA0 - iConst14) & 32767];
			fVec5[IOTA0 & 4095] = fTemp6 - fTemp5;
			fRec16[0] = fVec5[(IOTA0 - iConst15) & 4095];
			float fRec17 = 0.6f * (fTemp5 - fTemp6);
			fRec23[0] = -(fSlow22 * (fSlow23 * fRec23[1] - (fRec9[1] + fRec9[2])));
			fRec22[0] = fSlow41 * (fRec9[1] + fSlow42 * fRec23[0]) + fSlow43 * fRec22[1];
			fVec6[IOTA0 & 16383] = 0.35355338f * fRec22[0] + 1e-20f;
			float fTemp7 = fVec6[(IOTA0 - iConst19) & 16383] + fTemp5 + 0.6f * fRec20[1];
			fVec7[IOTA0 & 4095] = fTemp7;
			fRec20[0] = fVec7[(IOTA0 - iConst20) & 4095];
			float fRec21 = -(0.6f * fTemp7);
			fRec27[0] = -(fSlow22 * (fSlow23 * fRec27[1] - (fRec5[1] + fRec5[2])));
			fRec26[0] = fSlow50 * (fRec5[1] + fSlow51 * fRec27[0]) + fSlow52 * fRec26[1];
			fVec8[IOTA0 & 32767] = 0.35355338f * fRec26[0] + 1e-20f;
			float fTemp8 = fTemp5 + 0.6f * fRec24[1] + fVec8[(IOTA0 - iConst24) & 32767];
			fVec9[IOTA0 & 4095] = fTemp8;
			fRec24[0] = fVec9[(IOTA0 - iConst25) & 4095];
			float fRec25 = -(0.6f * fTemp8);
			fRec31[0] = -(fSlow22 * (fSlow23 * fRec31[1] - (fRec10[1] + fRec10[2])));
			fRec30[0] = fSlow59 * (fRec10[1] + fSlow60 * fRec31[0]) + fSlow61 * fRec30[1];
			fVec10[IOTA0 & 16383] = 0.35355338f * fRec30[0] + 1e-20f;
			float fTemp9 = 0.3f * fVec0[(IOTA0 - iSlow25) & 16383];
			float fTemp10 = fVec10[(IOTA0 - iConst29) & 16383] - (fTemp9 + 0.6f * fRec28[1]);
			fVec11[IOTA0 & 2047] = fTemp10;
			fRec28[0] = fVec11[(IOTA0 - iConst30) & 2047];
			float fRec29 = 0.6f * fTemp10;
			fRec35[0] = -(fSlow22 * (fSlow23 * fRec35[1] - (fRec6[1] + fRec6[2])));
			fRec34[0] = fSlow68 * (fRec6[1] + fSlow69 * fRec35[0]) + fSlow70 * fRec34[1];
			fVec12[IOTA0 & 16383] = 0.35355338f * fRec34[0] + 1e-20f;
			float fTemp11 = fVec12[(IOTA0 - iConst34) & 16383] - (fTemp9 + 0.6f * fRec32[1]);
			fVec13[IOTA0 & 4095] = fTemp11;
			fRec32[0] = fVec13[(IOTA0 - iConst35) & 4095];
			float fRec33 = 0.6f * fTemp11;
			fRec39[0] = -(fSlow22 * (fSlow23 * fRec39[1] - (fRec8[1] + fRec8[2])));
			fRec38[0] = fSlow77 * (fRec8[1] + fSlow78 * fRec39[0]) + fSlow79 * fRec38[1];
			fVec14[IOTA0 & 16383] = 0.35355338f * fRec38[0] + 1e-20f;
			float fTemp12 = fTemp9 + fVec14[(IOTA0 - iConst39) & 16383] - 0.6f * fRec36[1];
			fVec15[IOTA0 & 4095] = fTemp12;
			fRec36[0] = fVec15[(IOTA0 - iConst40) & 4095];
			float fRec37 = 0.6f * fTemp12;
			fRec43[0] = -(fSlow22 * (fSlow23 * fRec43[1] - (fRec4[1] + fRec4[2])));
			fRec42[0] = fSlow86 * (fRec4[1] + fSlow87 * fRec43[0]) + fSlow88 * fRec42[1];
			fVec16[IOTA0 & 16383] = 0.35355338f * fRec42[0] + 1e-20f;
			float fTemp13 = fVec16[(IOTA0 - iConst44) & 16383] + fTemp9 - 0.6f * fRec40[1];
			fVec17[IOTA0 & 2047] = fTemp13;
			fRec40[0] = fVec17[(IOTA0 - iConst45) & 2047];
			float fRec41 = 0.6f * fTemp13;
			float fTemp14 = fRec41 + fRec37;
			float fTemp15 = fRec29 + fRec33 + fTemp14;
			fRec4[0] = fRec12[1] + fRec16[1] + fRec20[1] + fRec24[1] + fRec28[1] + fRec32[1] + fRec36[1] + fRec40[1] + fRec13 + fRec17 + fRec21 + fRec25 + fTemp15;
			fRec5[0] = fRec28[1] + fRec32[1] + fRec36[1] + fRec40[1] + fTemp15 - (fRec12[1] + fRec16[1] + fRec20[1] + fRec24[1] + fRec13 + fRec17 + fRec25 + fRec21);
			float fTemp16 = fRec33 + fRec29;
			fRec6[0] = fRec20[1] + fRec24[1] + fRec36[1] + fRec40[1] + fRec21 + fRec25 + fTemp14 - (fRec12[1] + fRec16[1] + fRec28[1] + fRec32[1] + fRec13 + fRec17 + fTemp16);
			fRec7[0] = fRec12[1] + fRec16[1] + fRec36[1] + fRec40[1] + fRec13 + fRec17 + fTemp14 - (fRec20[1] + fRec24[1] + fRec28[1] + fRec32[1] + fRec21 + fRec25 + fTemp16);
			float fTemp17 = fRec41 + fRec33;
			float fTemp18 = fRec37 + fRec29;
			fRec8[0] = fRec16[1] + fRec24[1] + fRec32[1] + fRec40[1] + fRec17 + fRec25 + fTemp17 - (fRec12[1] + fRec20[1] + fRec28[1] + fRec36[1] + fRec13 + fRec21 + fTemp18);
			fRec9[0] = fRec12[1] + fRec20[1] + fRec32[1] + fRec40[1] + fRec13 + fRec21 + fTemp17 - (fRec16[1] + fRec24[1] + fRec28[1] + fRec36[1] + fRec17 + fRec25 + fTemp18);
			float fTemp19 = fRec41 + fRec29;
			float fTemp20 = fRec37 + fRec33;
			fRec10[0] = fRec12[1] + fRec24[1] + fRec28[1] + fRec40[1] + fRec13 + fRec25 + fTemp19 - (fRec16[1] + fRec20[1] + fRec32[1] + fRec36[1] + fRec17 + fRec21 + fTemp20);
			fRec11[0] = fRec16[1] + fRec20[1] + fRec28[1] + fRec40[1] + fRec17 + fRec21 + fTemp19 - (fRec12[1] + fRec24[1] + fRec32[1] + fRec36[1] + fRec13 + fRec25 + fTemp20);
			float fTemp21 = 0.37f * (fRec5[0] + fRec6[0]);
			float fTemp22 = fSlow89 * fRec3[1];
			float fTemp23 = fTemp21 + fTemp22;
			fRec3[0] = fTemp23 - fSlow9 * fRec3[2];
			float fTemp24 = fSlow9 * fRec3[0];
			float fTemp25 = 0.5f * (fTemp24 + fTemp21 + fRec3[2] - fTemp22 + fSlow7 * (fRec3[2] + fTemp24 - fTemp23));
			float fTemp26 = fSlow90 * fRec2[1];
			float fTemp27 = fTemp25 + fTemp26;
			fRec2[0] = fTemp27 - fSlow5 * fRec2[2];
			float fTemp28 = fSlow5 * fRec2[0];
			output0[i0] = static_cast<FAUSTFLOAT>(0.5f * fRec0[0] * (fTemp0 * fTemp1 + fTemp2 * (fTemp28 + fTemp25 + fRec2[2] - fTemp26 + fSlow3 * (fRec2[2] + fTemp28 - fTemp27))));
			float fTemp29 = 0.37f * (fRec5[0] - fRec6[0]);
			float fTemp30 = fSlow89 * fRec45[1];
			float fTemp31 = fTemp29 + fTemp30;
			fRec45[0] = fTemp31 - fSlow9 * fRec45[2];
			float fTemp32 = fSlow9 * fRec45[0];
			float fTemp33 = 0.5f * (fTemp32 + fTemp29 + fRec45[2] - fTemp30 + fSlow7 * (fRec45[2] + fTemp32 - fTemp31));
			float fTemp34 = fSlow90 * fRec44[1];
			float fTemp35 = fTemp33 + fTemp34;
			fRec44[0] = fTemp35 - fSlow5 * fRec44[2];
			float fTemp36 = fSlow5 * fRec44[0];
			output1[i0] = static_cast<FAUSTFLOAT>(0.5f * fRec0[0] * (fTemp4 * fTemp1 + fTemp2 * (fTemp36 + fTemp33 + fRec44[2] - fTemp34 + fSlow3 * (fRec44[2] + fTemp36 - fTemp35))));
			fRec0[1] = fRec0[0];
			IOTA0 = IOTA0 + 1;
			fRec1[1] = fRec1[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec12[1] = fRec12[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec16[1] = fRec16[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec20[1] = fRec20[0];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			fRec24[1] = fRec24[0];
			fRec31[1] = fRec31[0];
			fRec30[1] = fRec30[0];
			fRec28[1] = fRec28[0];
			fRec35[1] = fRec35[0];
			fRec34[1] = fRec34[0];
			fRec32[1] = fRec32[0];
			fRec39[1] = fRec39[0];
			fRec38[1] = fRec38[0];
			fRec36[1] = fRec36[0];
			fRec43[1] = fRec43[0];
			fRec42[1] = fRec42[0];
			fRec40[1] = fRec40[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "zitaRev.dsp"
	#define FAUST_CLASS_NAME "_zitaRev"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _zitaRev -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 11
	#define FAUST_PASSIVES 0

	FAUST_ADDVERTICALSLIDER("[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[1] Input/In Delay", fVslider10, 6e+01f, 2e+01f, 1e+02f, 1.0f);
	FAUST_ADDVERTICALSLIDER("[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[2] Decay Times in Bands (see tooltips)/LF X", fVslider9, 2e+02f, 5e+01f, 1e+03f, 1.0f);
	FAUST_ADDVERTICALSLIDER("[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[2] Decay Times in Bands (see tooltips)/Low RT60", fVslider8, 3.0f, 1.0f, 8.0f, 0.1f);
	FAUST_ADDVERTICALSLIDER("[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[2] Decay Times in Bands (see tooltips)/Mid RT60", fVslider6, 2.0f, 1.0f, 8.0f, 0.1f);
	FAUST_ADDVERTICALSLIDER("[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[2] Decay Times in Bands (see tooltips)/HF Damping", fVslider7, 6e+03f, 1.5e+03f, 2.352e+04f, 1.0f);
	FAUST_ADDVERTICALSLIDER("[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[3] RM Peaking Equalizer 1/Eq1 Freq", fVslider4, 315.0f, 4e+01f, 2.5e+03f, 1.0f);
	FAUST_ADDVERTICALSLIDER("[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[3] RM Peaking Equalizer 1/Eq1 Level", fVslider5, 0.0f, -15.0f, 15.0f, 0.1f);
	FAUST_ADDVERTICALSLIDER("[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[4] RM Peaking Equalizer 2/Eq2 Freq", fVslider2, 1.5e+03f, 1.6e+02f, 1e+04f, 1.0f);
	FAUST_ADDVERTICALSLIDER("[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[4] RM Peaking Equalizer 2/Eq2 Level", fVslider3, 0.0f, -15.0f, 15.0f, 0.1f);
	FAUST_ADDVERTICALSLIDER("[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[5] Output/Wet/Dry Mix", fVslider1, 0.0f, -1.0f, 1.0f, 0.01f);
	FAUST_ADDVERTICALSLIDER("[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[5] Output/Level", fVslider0, -2e+01f, -7e+01f, 4e+01f, 0.1f);

	#define FAUST_LIST_ACTIVES(p) \
		p(VERTICALSLIDER, In_Delay, "[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[1] Input/In Delay", fVslider10, 6e+01f, 2e+01f, 1e+02f, 1.0f) \
		p(VERTICALSLIDER, LF_X, "[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[2] Decay Times in Bands (see tooltips)/LF X", fVslider9, 2e+02f, 5e+01f, 1e+03f, 1.0f) \
		p(VERTICALSLIDER, Low_RT60, "[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[2] Decay Times in Bands (see tooltips)/Low RT60", fVslider8, 3.0f, 1.0f, 8.0f, 0.1f) \
		p(VERTICALSLIDER, Mid_RT60, "[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[2] Decay Times in Bands (see tooltips)/Mid RT60", fVslider6, 2.0f, 1.0f, 8.0f, 0.1f) \
		p(VERTICALSLIDER, HF_Damping, "[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[2] Decay Times in Bands (see tooltips)/HF Damping", fVslider7, 6e+03f, 1.5e+03f, 2.352e+04f, 1.0f) \
		p(VERTICALSLIDER, Eq1_Freq, "[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[3] RM Peaking Equalizer 1/Eq1 Freq", fVslider4, 315.0f, 4e+01f, 2.5e+03f, 1.0f) \
		p(VERTICALSLIDER, Eq1_Level, "[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[3] RM Peaking Equalizer 1/Eq1 Level", fVslider5, 0.0f, -15.0f, 15.0f, 0.1f) \
		p(VERTICALSLIDER, Eq2_Freq, "[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[4] RM Peaking Equalizer 2/Eq2 Freq", fVslider2, 1.5e+03f, 1.6e+02f, 1e+04f, 1.0f) \
		p(VERTICALSLIDER, Eq2_Level, "[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[4] RM Peaking Equalizer 2/Eq2 Level", fVslider3, 0.0f, -15.0f, 15.0f, 0.1f) \
		p(VERTICALSLIDER, Wet/Dry_Mix, "[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[5] Output/Wet/Dry Mix", fVslider1, 0.0f, -1.0f, 1.0f, 0.01f) \
		p(VERTICALSLIDER, Level, "[0] Zita_Rev1 [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER     ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverbs.lib for documentation and     references]/[5] Output/Level", fVslider0, -2e+01f, -7e+01f, 4e+01f, 0.1f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

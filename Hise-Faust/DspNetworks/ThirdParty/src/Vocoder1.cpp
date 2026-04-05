/* ------------------------------------------------------------
author: "RM"
name: "Vocoder"
version: "0.0"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _Vocoder1 -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___Vocoder1_H__
#define  ___Vocoder1_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _Vocoder1
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

static float _Vocoder1_faustpower2_f(float value) {
	return value * value;
}

struct _Vocoder1 final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	float fConst3;
	int iVec0[2];
	float fRec1[3];
	FAUSTFLOAT fHslider1;
	float fConst4;
	FAUSTFLOAT fHslider2;
	float fRec0[2];
	float fConst5;
	FAUSTFLOAT fVslider0;
	float fConst6;
	float fRec3[2];
	FAUSTFLOAT fHslider3;
	float fRec4[2];
	float fRec2[3];
	float fConst7;
	float fConst8;
	float fConst9;
	float fRec6[3];
	float fRec5[2];
	float fRec7[3];
	float fConst10;
	float fConst11;
	float fConst12;
	float fRec9[3];
	float fRec8[2];
	float fRec10[3];
	float fConst13;
	float fConst14;
	float fConst15;
	float fRec12[3];
	float fRec11[2];
	float fRec13[3];
	float fConst16;
	float fConst17;
	float fConst18;
	float fRec15[3];
	float fRec14[2];
	float fRec16[3];
	float fConst19;
	float fConst20;
	float fConst21;
	float fRec18[3];
	float fRec17[2];
	float fRec19[3];
	float fConst22;
	float fConst23;
	float fConst24;
	float fRec21[3];
	float fRec20[2];
	float fRec22[3];
	float fConst25;
	float fConst26;
	float fConst27;
	float fRec24[3];
	float fRec23[2];
	float fRec25[3];
	float fConst28;
	float fConst29;
	float fConst30;
	float fRec27[3];
	float fRec26[2];
	float fRec28[3];
	float fConst31;
	float fConst32;
	float fConst33;
	float fRec30[3];
	float fRec29[2];
	float fRec31[3];
	float fConst34;
	float fConst35;
	float fConst36;
	float fRec33[3];
	float fRec32[2];
	float fRec34[3];
	float fConst37;
	float fConst38;
	float fConst39;
	float fRec36[3];
	float fRec35[2];
	float fRec37[3];
	float fConst40;
	float fConst41;
	float fConst42;
	float fRec39[3];
	float fRec38[2];
	float fRec40[3];
	float fConst43;
	float fConst44;
	float fConst45;
	float fRec42[3];
	float fRec41[2];
	float fRec43[3];
	float fConst46;
	float fConst47;
	float fConst48;
	float fRec45[3];
	float fRec44[2];
	float fRec46[3];
	float fConst49;
	float fConst50;
	float fConst51;
	float fRec48[3];
	float fRec47[2];
	float fRec49[3];
	float fConst52;
	float fConst53;
	float fConst54;
	float fRec51[3];
	float fRec50[2];
	float fRec52[3];
	float fConst55;
	float fConst56;
	float fConst57;
	float fRec54[3];
	float fRec53[2];
	float fRec55[3];
	float fConst58;
	float fConst59;
	float fConst60;
	float fRec57[3];
	float fRec56[2];
	float fRec58[3];
	float fConst61;
	float fConst62;
	float fConst63;
	float fRec60[3];
	float fRec59[2];
	float fRec61[3];
	float fConst64;
	float fConst65;
	float fConst66;
	float fRec63[3];
	float fRec62[2];
	float fRec64[3];
	float fConst67;
	float fConst68;
	float fConst69;
	float fRec66[3];
	float fRec65[2];
	float fRec67[3];
	float fConst70;
	float fConst71;
	float fConst72;
	float fRec69[3];
	float fRec68[2];
	float fRec70[3];
	float fConst73;
	float fConst74;
	float fConst75;
	float fRec72[3];
	float fRec71[2];
	float fRec73[3];
	float fConst76;
	float fConst77;
	float fConst78;
	float fRec75[3];
	float fRec74[2];
	float fRec76[3];
	float fConst79;
	float fConst80;
	float fConst81;
	float fRec78[3];
	float fRec77[2];
	float fRec79[3];
	float fConst82;
	float fConst83;
	float fConst84;
	float fRec81[3];
	float fRec80[2];
	float fRec82[3];
	float fConst85;
	float fConst86;
	float fConst87;
	float fRec84[3];
	float fRec83[2];
	float fRec85[3];
	float fConst88;
	float fConst89;
	float fConst90;
	float fRec87[3];
	float fRec86[2];
	float fRec88[3];
	float fConst91;
	float fConst92;
	float fConst93;
	float fRec90[3];
	float fRec89[2];
	float fRec91[3];
	float fConst94;
	float fConst95;
	float fConst96;
	float fRec93[3];
	float fRec92[2];
	float fRec94[3];
	float fConst97;
	float fConst98;
	float fConst99;
	float fRec96[3];
	float fRec95[2];
	float fRec97[3];
	float fRec99[3];
	float fRec98[2];
	float fRec101[3];
	float fRec100[2];
	float fRec103[3];
	float fRec102[2];
	float fRec105[3];
	float fRec104[2];
	float fRec107[3];
	float fRec106[2];
	float fRec109[3];
	float fRec108[2];
	float fRec111[3];
	float fRec110[2];
	float fRec113[3];
	float fRec112[2];
	float fRec115[3];
	float fRec114[2];
	float fRec117[3];
	float fRec116[2];
	float fRec119[3];
	float fRec118[2];
	float fRec121[3];
	float fRec120[2];
	float fRec123[3];
	float fRec122[2];
	float fRec125[3];
	float fRec124[2];
	float fRec127[3];
	float fRec126[2];
	float fRec129[3];
	float fRec128[2];
	float fRec131[3];
	float fRec130[2];
	float fRec133[3];
	float fRec132[2];
	float fRec135[3];
	float fRec134[2];
	float fRec137[3];
	float fRec136[2];
	float fRec139[3];
	float fRec138[2];
	float fRec141[3];
	float fRec140[2];
	float fRec143[3];
	float fRec142[2];
	float fRec145[3];
	float fRec144[2];
	float fRec147[3];
	float fRec146[2];
	float fRec149[3];
	float fRec148[2];
	float fRec151[3];
	float fRec150[2];
	float fRec153[3];
	float fRec152[2];
	float fRec155[3];
	float fRec154[2];
	float fRec157[3];
	float fRec156[2];
	float fRec159[3];
	float fRec158[2];
	float fRec161[3];
	float fRec160[2];
	
	_Vocoder1() {
	}
	
	_Vocoder1(const _Vocoder1&) = default;
	
	virtual ~_Vocoder1() = default;
	
	_Vocoder1& operator=(const _Vocoder1&) = default;
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/amp_follower_ar:author", "Jonatan Liljedahl, revised by Romain Michon");
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.3.0");
		m->declare("author", "RM");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _Vocoder1 -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("demos.lib/name", "Faust Demos Library");
		m->declare("demos.lib/version", "1.4.0");
		m->declare("demos.lib/vocoder_demo:author", "Romain Michon");
		m->declare("demos.lib/vocoder_demo:licence", "LGPL");
		m->declare("description", "Use example of the vocoder function where an impulse train is used as excitation.");
		m->declare("filename", "Vocoder1.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/resonbp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonbp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonbp:license", "MIT-style STK-4.3 license");
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
		m->declare("name", "Vocoder");
		m->declare("oscillators.lib/lf_sawpos:author", "Bart Brouns, revised by Stéphane Letz");
		m->declare("oscillators.lib/lf_sawpos:licence", "STK-4.3");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "1.6.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/onePoleSwitching:author", "Jonatan Liljedahl, revised by Dario Sanfilippo");
		m->declare("signals.lib/onePoleSwitching:licence", "STK-4.3");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m->declare("vaeffects.lib/oneVocoderBand:author", "Romain Michon");
		m->declare("vaeffects.lib/version", "1.4.0");
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
		fConst1 = std::tan(95.445305f / fConst0);
		fConst2 = 1.0f / fConst1;
		fConst3 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst1));
		fConst4 = 1.0f / fConst0;
		fConst5 = 44.1f / fConst0;
		fConst6 = 1.0f - fConst5;
		fConst7 = std::tan(115.989655f / fConst0);
		fConst8 = 1.0f / fConst7;
		fConst9 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst7));
		fConst10 = std::tan(140.95612f / fConst0);
		fConst11 = 1.0f / fConst10;
		fConst12 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst10));
		fConst13 = std::tan(171.29655f / fConst0);
		fConst14 = 1.0f / fConst13;
		fConst15 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst13));
		fConst16 = std::tan(208.16768f / fConst0);
		fConst17 = 1.0f / fConst16;
		fConst18 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst16));
		fConst19 = std::tan(252.97523f / fConst0);
		fConst20 = 1.0f / fConst19;
		fConst21 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst19));
		fConst22 = std::tan(307.4275f / fConst0);
		fConst23 = 1.0f / fConst22;
		fConst24 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst22));
		fConst25 = std::tan(373.60043f / fConst0);
		fConst26 = 1.0f / fConst25;
		fConst27 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst25));
		fConst28 = std::tan(454.01694f / fConst0);
		fConst29 = 1.0f / fConst28;
		fConst30 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst28));
		fConst31 = std::tan(551.74286f / fConst0);
		fConst32 = 1.0f / fConst31;
		fConst33 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst31));
		fConst34 = std::tan(670.5041f / fConst0);
		fConst35 = 1.0f / fConst34;
		fConst36 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst34));
		fConst37 = std::tan(814.8283f / fConst0);
		fConst38 = 1.0f / fConst37;
		fConst39 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst37));
		fConst40 = std::tan(990.21796f / fConst0);
		fConst41 = 1.0f / fConst40;
		fConst42 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst40));
		fConst43 = std::tan(1203.3597f / fConst0);
		fConst44 = 1.0f / fConst43;
		fConst45 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst43));
		fConst46 = std::tan(1462.3798f / fConst0);
		fConst47 = 1.0f / fConst46;
		fConst48 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst46));
		fConst49 = std::tan(1777.1532f / fConst0);
		fConst50 = 1.0f / fConst49;
		fConst51 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst49));
		fConst52 = std::tan(2159.6807f / fConst0);
		fConst53 = 1.0f / fConst52;
		fConst54 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst52));
		fConst55 = std::tan(2624.5464f / fConst0);
		fConst56 = 1.0f / fConst55;
		fConst57 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst55));
		fConst58 = std::tan(3189.473f / fConst0);
		fConst59 = 1.0f / fConst58;
		fConst60 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst58));
		fConst61 = std::tan(3875.9985f / fConst0);
		fConst62 = 1.0f / fConst61;
		fConst63 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst61));
		fConst64 = std::tan(4710.297f / fConst0);
		fConst65 = 1.0f / fConst64;
		fConst66 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst64));
		fConst67 = std::tan(5724.176f / fConst0);
		fConst68 = 1.0f / fConst67;
		fConst69 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst67));
		fConst70 = std::tan(6956.2896f / fConst0);
		fConst71 = 1.0f / fConst70;
		fConst72 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst70));
		fConst73 = std::tan(8453.613f / fConst0);
		fConst74 = 1.0f / fConst73;
		fConst75 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst73));
		fConst76 = std::tan(10273.23f / fConst0);
		fConst77 = 1.0f / fConst76;
		fConst78 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst76));
		fConst79 = std::tan(12484.517f / fConst0);
		fConst80 = 1.0f / fConst79;
		fConst81 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst79));
		fConst82 = std::tan(15171.775f / fConst0);
		fConst83 = 1.0f / fConst82;
		fConst84 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst82));
		fConst85 = std::tan(18437.46f / fConst0);
		fConst86 = 1.0f / fConst85;
		fConst87 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst85));
		fConst88 = std::tan(22406.074f / fConst0);
		fConst89 = 1.0f / fConst88;
		fConst90 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst88));
		fConst91 = std::tan(27228.924f / fConst0);
		fConst92 = 1.0f / fConst91;
		fConst93 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst91));
		fConst94 = std::tan(33089.88f / fConst0);
		fConst95 = 1.0f / fConst94;
		fConst96 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst94));
		fConst97 = std::tan(40212.387f / fConst0);
		fConst98 = 1.0f / fConst97;
		fConst99 = 2.0f * (1.0f - 1.0f / _Vocoder1_faustpower2_f(fConst97));
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider1 = static_cast<FAUSTFLOAT>(5.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(5.0f);
		fVslider0 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider3 = static_cast<FAUSTFLOAT>(3.3e+02f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 3; l1 = l1 + 1) {
			fRec1[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec0[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec3[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec4[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 3; l5 = l5 + 1) {
			fRec2[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 3; l6 = l6 + 1) {
			fRec6[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec5[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 3; l8 = l8 + 1) {
			fRec7[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec9[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec8[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec10[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 3; l12 = l12 + 1) {
			fRec12[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec11[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 3; l14 = l14 + 1) {
			fRec13[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 3; l15 = l15 + 1) {
			fRec15[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec14[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 3; l17 = l17 + 1) {
			fRec16[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 3; l18 = l18 + 1) {
			fRec18[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec17[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 3; l20 = l20 + 1) {
			fRec19[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 3; l21 = l21 + 1) {
			fRec21[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fRec20[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 3; l23 = l23 + 1) {
			fRec22[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 3; l24 = l24 + 1) {
			fRec24[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fRec23[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 3; l26 = l26 + 1) {
			fRec25[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 3; l27 = l27 + 1) {
			fRec27[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			fRec26[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 3; l29 = l29 + 1) {
			fRec28[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 3; l30 = l30 + 1) {
			fRec30[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec29[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 3; l32 = l32 + 1) {
			fRec31[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 3; l33 = l33 + 1) {
			fRec33[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			fRec32[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 3; l35 = l35 + 1) {
			fRec34[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 3; l36 = l36 + 1) {
			fRec36[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 2; l37 = l37 + 1) {
			fRec35[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 3; l38 = l38 + 1) {
			fRec37[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 3; l39 = l39 + 1) {
			fRec39[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			fRec38[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 3; l41 = l41 + 1) {
			fRec40[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 3; l42 = l42 + 1) {
			fRec42[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec41[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 3; l44 = l44 + 1) {
			fRec43[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 3; l45 = l45 + 1) {
			fRec45[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 2; l46 = l46 + 1) {
			fRec44[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 3; l47 = l47 + 1) {
			fRec46[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 3; l48 = l48 + 1) {
			fRec48[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 2; l49 = l49 + 1) {
			fRec47[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 3; l50 = l50 + 1) {
			fRec49[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 3; l51 = l51 + 1) {
			fRec51[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 2; l52 = l52 + 1) {
			fRec50[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 3; l53 = l53 + 1) {
			fRec52[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 3; l54 = l54 + 1) {
			fRec54[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 2; l55 = l55 + 1) {
			fRec53[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 3; l56 = l56 + 1) {
			fRec55[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 3; l57 = l57 + 1) {
			fRec57[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 2; l58 = l58 + 1) {
			fRec56[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 3; l59 = l59 + 1) {
			fRec58[l59] = 0.0f;
		}
		for (int l60 = 0; l60 < 3; l60 = l60 + 1) {
			fRec60[l60] = 0.0f;
		}
		for (int l61 = 0; l61 < 2; l61 = l61 + 1) {
			fRec59[l61] = 0.0f;
		}
		for (int l62 = 0; l62 < 3; l62 = l62 + 1) {
			fRec61[l62] = 0.0f;
		}
		for (int l63 = 0; l63 < 3; l63 = l63 + 1) {
			fRec63[l63] = 0.0f;
		}
		for (int l64 = 0; l64 < 2; l64 = l64 + 1) {
			fRec62[l64] = 0.0f;
		}
		for (int l65 = 0; l65 < 3; l65 = l65 + 1) {
			fRec64[l65] = 0.0f;
		}
		for (int l66 = 0; l66 < 3; l66 = l66 + 1) {
			fRec66[l66] = 0.0f;
		}
		for (int l67 = 0; l67 < 2; l67 = l67 + 1) {
			fRec65[l67] = 0.0f;
		}
		for (int l68 = 0; l68 < 3; l68 = l68 + 1) {
			fRec67[l68] = 0.0f;
		}
		for (int l69 = 0; l69 < 3; l69 = l69 + 1) {
			fRec69[l69] = 0.0f;
		}
		for (int l70 = 0; l70 < 2; l70 = l70 + 1) {
			fRec68[l70] = 0.0f;
		}
		for (int l71 = 0; l71 < 3; l71 = l71 + 1) {
			fRec70[l71] = 0.0f;
		}
		for (int l72 = 0; l72 < 3; l72 = l72 + 1) {
			fRec72[l72] = 0.0f;
		}
		for (int l73 = 0; l73 < 2; l73 = l73 + 1) {
			fRec71[l73] = 0.0f;
		}
		for (int l74 = 0; l74 < 3; l74 = l74 + 1) {
			fRec73[l74] = 0.0f;
		}
		for (int l75 = 0; l75 < 3; l75 = l75 + 1) {
			fRec75[l75] = 0.0f;
		}
		for (int l76 = 0; l76 < 2; l76 = l76 + 1) {
			fRec74[l76] = 0.0f;
		}
		for (int l77 = 0; l77 < 3; l77 = l77 + 1) {
			fRec76[l77] = 0.0f;
		}
		for (int l78 = 0; l78 < 3; l78 = l78 + 1) {
			fRec78[l78] = 0.0f;
		}
		for (int l79 = 0; l79 < 2; l79 = l79 + 1) {
			fRec77[l79] = 0.0f;
		}
		for (int l80 = 0; l80 < 3; l80 = l80 + 1) {
			fRec79[l80] = 0.0f;
		}
		for (int l81 = 0; l81 < 3; l81 = l81 + 1) {
			fRec81[l81] = 0.0f;
		}
		for (int l82 = 0; l82 < 2; l82 = l82 + 1) {
			fRec80[l82] = 0.0f;
		}
		for (int l83 = 0; l83 < 3; l83 = l83 + 1) {
			fRec82[l83] = 0.0f;
		}
		for (int l84 = 0; l84 < 3; l84 = l84 + 1) {
			fRec84[l84] = 0.0f;
		}
		for (int l85 = 0; l85 < 2; l85 = l85 + 1) {
			fRec83[l85] = 0.0f;
		}
		for (int l86 = 0; l86 < 3; l86 = l86 + 1) {
			fRec85[l86] = 0.0f;
		}
		for (int l87 = 0; l87 < 3; l87 = l87 + 1) {
			fRec87[l87] = 0.0f;
		}
		for (int l88 = 0; l88 < 2; l88 = l88 + 1) {
			fRec86[l88] = 0.0f;
		}
		for (int l89 = 0; l89 < 3; l89 = l89 + 1) {
			fRec88[l89] = 0.0f;
		}
		for (int l90 = 0; l90 < 3; l90 = l90 + 1) {
			fRec90[l90] = 0.0f;
		}
		for (int l91 = 0; l91 < 2; l91 = l91 + 1) {
			fRec89[l91] = 0.0f;
		}
		for (int l92 = 0; l92 < 3; l92 = l92 + 1) {
			fRec91[l92] = 0.0f;
		}
		for (int l93 = 0; l93 < 3; l93 = l93 + 1) {
			fRec93[l93] = 0.0f;
		}
		for (int l94 = 0; l94 < 2; l94 = l94 + 1) {
			fRec92[l94] = 0.0f;
		}
		for (int l95 = 0; l95 < 3; l95 = l95 + 1) {
			fRec94[l95] = 0.0f;
		}
		for (int l96 = 0; l96 < 3; l96 = l96 + 1) {
			fRec96[l96] = 0.0f;
		}
		for (int l97 = 0; l97 < 2; l97 = l97 + 1) {
			fRec95[l97] = 0.0f;
		}
		for (int l98 = 0; l98 < 3; l98 = l98 + 1) {
			fRec97[l98] = 0.0f;
		}
		for (int l99 = 0; l99 < 3; l99 = l99 + 1) {
			fRec99[l99] = 0.0f;
		}
		for (int l100 = 0; l100 < 2; l100 = l100 + 1) {
			fRec98[l100] = 0.0f;
		}
		for (int l101 = 0; l101 < 3; l101 = l101 + 1) {
			fRec101[l101] = 0.0f;
		}
		for (int l102 = 0; l102 < 2; l102 = l102 + 1) {
			fRec100[l102] = 0.0f;
		}
		for (int l103 = 0; l103 < 3; l103 = l103 + 1) {
			fRec103[l103] = 0.0f;
		}
		for (int l104 = 0; l104 < 2; l104 = l104 + 1) {
			fRec102[l104] = 0.0f;
		}
		for (int l105 = 0; l105 < 3; l105 = l105 + 1) {
			fRec105[l105] = 0.0f;
		}
		for (int l106 = 0; l106 < 2; l106 = l106 + 1) {
			fRec104[l106] = 0.0f;
		}
		for (int l107 = 0; l107 < 3; l107 = l107 + 1) {
			fRec107[l107] = 0.0f;
		}
		for (int l108 = 0; l108 < 2; l108 = l108 + 1) {
			fRec106[l108] = 0.0f;
		}
		for (int l109 = 0; l109 < 3; l109 = l109 + 1) {
			fRec109[l109] = 0.0f;
		}
		for (int l110 = 0; l110 < 2; l110 = l110 + 1) {
			fRec108[l110] = 0.0f;
		}
		for (int l111 = 0; l111 < 3; l111 = l111 + 1) {
			fRec111[l111] = 0.0f;
		}
		for (int l112 = 0; l112 < 2; l112 = l112 + 1) {
			fRec110[l112] = 0.0f;
		}
		for (int l113 = 0; l113 < 3; l113 = l113 + 1) {
			fRec113[l113] = 0.0f;
		}
		for (int l114 = 0; l114 < 2; l114 = l114 + 1) {
			fRec112[l114] = 0.0f;
		}
		for (int l115 = 0; l115 < 3; l115 = l115 + 1) {
			fRec115[l115] = 0.0f;
		}
		for (int l116 = 0; l116 < 2; l116 = l116 + 1) {
			fRec114[l116] = 0.0f;
		}
		for (int l117 = 0; l117 < 3; l117 = l117 + 1) {
			fRec117[l117] = 0.0f;
		}
		for (int l118 = 0; l118 < 2; l118 = l118 + 1) {
			fRec116[l118] = 0.0f;
		}
		for (int l119 = 0; l119 < 3; l119 = l119 + 1) {
			fRec119[l119] = 0.0f;
		}
		for (int l120 = 0; l120 < 2; l120 = l120 + 1) {
			fRec118[l120] = 0.0f;
		}
		for (int l121 = 0; l121 < 3; l121 = l121 + 1) {
			fRec121[l121] = 0.0f;
		}
		for (int l122 = 0; l122 < 2; l122 = l122 + 1) {
			fRec120[l122] = 0.0f;
		}
		for (int l123 = 0; l123 < 3; l123 = l123 + 1) {
			fRec123[l123] = 0.0f;
		}
		for (int l124 = 0; l124 < 2; l124 = l124 + 1) {
			fRec122[l124] = 0.0f;
		}
		for (int l125 = 0; l125 < 3; l125 = l125 + 1) {
			fRec125[l125] = 0.0f;
		}
		for (int l126 = 0; l126 < 2; l126 = l126 + 1) {
			fRec124[l126] = 0.0f;
		}
		for (int l127 = 0; l127 < 3; l127 = l127 + 1) {
			fRec127[l127] = 0.0f;
		}
		for (int l128 = 0; l128 < 2; l128 = l128 + 1) {
			fRec126[l128] = 0.0f;
		}
		for (int l129 = 0; l129 < 3; l129 = l129 + 1) {
			fRec129[l129] = 0.0f;
		}
		for (int l130 = 0; l130 < 2; l130 = l130 + 1) {
			fRec128[l130] = 0.0f;
		}
		for (int l131 = 0; l131 < 3; l131 = l131 + 1) {
			fRec131[l131] = 0.0f;
		}
		for (int l132 = 0; l132 < 2; l132 = l132 + 1) {
			fRec130[l132] = 0.0f;
		}
		for (int l133 = 0; l133 < 3; l133 = l133 + 1) {
			fRec133[l133] = 0.0f;
		}
		for (int l134 = 0; l134 < 2; l134 = l134 + 1) {
			fRec132[l134] = 0.0f;
		}
		for (int l135 = 0; l135 < 3; l135 = l135 + 1) {
			fRec135[l135] = 0.0f;
		}
		for (int l136 = 0; l136 < 2; l136 = l136 + 1) {
			fRec134[l136] = 0.0f;
		}
		for (int l137 = 0; l137 < 3; l137 = l137 + 1) {
			fRec137[l137] = 0.0f;
		}
		for (int l138 = 0; l138 < 2; l138 = l138 + 1) {
			fRec136[l138] = 0.0f;
		}
		for (int l139 = 0; l139 < 3; l139 = l139 + 1) {
			fRec139[l139] = 0.0f;
		}
		for (int l140 = 0; l140 < 2; l140 = l140 + 1) {
			fRec138[l140] = 0.0f;
		}
		for (int l141 = 0; l141 < 3; l141 = l141 + 1) {
			fRec141[l141] = 0.0f;
		}
		for (int l142 = 0; l142 < 2; l142 = l142 + 1) {
			fRec140[l142] = 0.0f;
		}
		for (int l143 = 0; l143 < 3; l143 = l143 + 1) {
			fRec143[l143] = 0.0f;
		}
		for (int l144 = 0; l144 < 2; l144 = l144 + 1) {
			fRec142[l144] = 0.0f;
		}
		for (int l145 = 0; l145 < 3; l145 = l145 + 1) {
			fRec145[l145] = 0.0f;
		}
		for (int l146 = 0; l146 < 2; l146 = l146 + 1) {
			fRec144[l146] = 0.0f;
		}
		for (int l147 = 0; l147 < 3; l147 = l147 + 1) {
			fRec147[l147] = 0.0f;
		}
		for (int l148 = 0; l148 < 2; l148 = l148 + 1) {
			fRec146[l148] = 0.0f;
		}
		for (int l149 = 0; l149 < 3; l149 = l149 + 1) {
			fRec149[l149] = 0.0f;
		}
		for (int l150 = 0; l150 < 2; l150 = l150 + 1) {
			fRec148[l150] = 0.0f;
		}
		for (int l151 = 0; l151 < 3; l151 = l151 + 1) {
			fRec151[l151] = 0.0f;
		}
		for (int l152 = 0; l152 < 2; l152 = l152 + 1) {
			fRec150[l152] = 0.0f;
		}
		for (int l153 = 0; l153 < 3; l153 = l153 + 1) {
			fRec153[l153] = 0.0f;
		}
		for (int l154 = 0; l154 < 2; l154 = l154 + 1) {
			fRec152[l154] = 0.0f;
		}
		for (int l155 = 0; l155 < 3; l155 = l155 + 1) {
			fRec155[l155] = 0.0f;
		}
		for (int l156 = 0; l156 < 2; l156 = l156 + 1) {
			fRec154[l156] = 0.0f;
		}
		for (int l157 = 0; l157 < 3; l157 = l157 + 1) {
			fRec157[l157] = 0.0f;
		}
		for (int l158 = 0; l158 < 2; l158 = l158 + 1) {
			fRec156[l158] = 0.0f;
		}
		for (int l159 = 0; l159 < 3; l159 = l159 + 1) {
			fRec159[l159] = 0.0f;
		}
		for (int l160 = 0; l160 < 2; l160 = l160 + 1) {
			fRec158[l160] = 0.0f;
		}
		for (int l161 = 0; l161 < 3; l161 = l161 + 1) {
			fRec161[l161] = 0.0f;
		}
		for (int l162 = 0; l162 < 2; l162 = l162 + 1) {
			fRec160[l162] = 0.0f;
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
	
	_Vocoder1* clone() {
		return new _Vocoder1(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openHorizontalBox("My Vocoder");
		ui_interface->openVerticalBox("Excitation");
		ui_interface->declare(&fHslider3, "0", "");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("Freq", &fHslider3, FAUSTFLOAT(3.3e+02f), FAUSTFLOAT(5e+01f), FAUSTFLOAT(2e+03f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fVslider0, "1", "");
		ui_interface->addVerticalSlider("Gain", &fVslider0, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Vocoder");
		ui_interface->declare(&fHslider2, "0", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->declare(&fHslider2, "tooltip", "Attack time in seconds");
		ui_interface->addHorizontalSlider("Attack", &fHslider2, FAUSTFLOAT(5.0f), FAUSTFLOAT(0.1f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "tooltip", "Release time in seconds");
		ui_interface->addHorizontalSlider("Release", &fHslider1, FAUSTFLOAT(5.0f), FAUSTFLOAT(0.1f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "tooltip", "Coefficient to adjust the         bandwidth of each band");
		ui_interface->addHorizontalSlider("BW", &fHslider0, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.1f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = std::max<float>(0.1f, std::min<float>(2.0f, static_cast<float>(fHslider0)));
		float fSlow1 = 0.17712227f * fSlow0;
		float fSlow2 = fConst2 * (fConst2 + fSlow1) + 1.0f;
		float fSlow3 = fConst2 / fSlow2;
		float fSlow4 = 1.0f / fSlow2;
		float fSlow5 = fConst2 * (fConst2 - fSlow1) + 1.0f;
		float fSlow6 = 0.001f * std::max<float>(0.1f, std::min<float>(1e+02f, static_cast<float>(fHslider1)));
		int iSlow7 = std::fabs(fSlow6) < 1.1920929e-07f;
		float fSlow8 = ((iSlow7) ? 0.0f : std::exp(-(fConst4 / ((iSlow7) ? 1.0f : fSlow6))));
		float fSlow9 = 0.001f * std::max<float>(0.1f, std::min<float>(1e+02f, static_cast<float>(fHslider2)));
		int iSlow10 = std::fabs(fSlow9) < 1.1920929e-07f;
		float fSlow11 = ((iSlow10) ? 0.0f : std::exp(-(fConst4 / ((iSlow10) ? 1.0f : fSlow9))));
		float fSlow12 = fConst5 * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fVslider0)));
		float fSlow13 = fConst4 * std::max<float>(5e+01f, std::min<float>(2e+03f, static_cast<float>(fHslider3)));
		float fSlow14 = 0.17712227f * fSlow0;
		float fSlow15 = fConst8 * (fConst8 + fSlow14) + 1.0f;
		float fSlow16 = fConst8 / fSlow15;
		float fSlow17 = 1.0f / fSlow15;
		float fSlow18 = fConst8 * (fConst8 - fSlow14) + 1.0f;
		float fSlow19 = fConst11 * (fConst11 + fSlow1) + 1.0f;
		float fSlow20 = fConst11 / fSlow19;
		float fSlow21 = 1.0f / fSlow19;
		float fSlow22 = fConst11 * (fConst11 - fSlow1) + 1.0f;
		float fSlow23 = 0.17712227f * fSlow0;
		float fSlow24 = fConst14 * (fConst14 + fSlow23) + 1.0f;
		float fSlow25 = fConst14 / fSlow24;
		float fSlow26 = 1.0f / fSlow24;
		float fSlow27 = fConst14 * (fConst14 - fSlow23) + 1.0f;
		float fSlow28 = 0.17712227f * fSlow0;
		float fSlow29 = fConst17 * (fConst17 + fSlow28) + 1.0f;
		float fSlow30 = fConst17 / fSlow29;
		float fSlow31 = 1.0f / fSlow29;
		float fSlow32 = fConst17 * (fConst17 - fSlow28) + 1.0f;
		float fSlow33 = 0.17712227f * fSlow0;
		float fSlow34 = fConst20 * (fConst20 + fSlow33) + 1.0f;
		float fSlow35 = fConst20 / fSlow34;
		float fSlow36 = 1.0f / fSlow34;
		float fSlow37 = fConst20 * (fConst20 - fSlow33) + 1.0f;
		float fSlow38 = 0.17712227f * fSlow0;
		float fSlow39 = fConst23 * (fConst23 + fSlow38) + 1.0f;
		float fSlow40 = fConst23 / fSlow39;
		float fSlow41 = 1.0f / fSlow39;
		float fSlow42 = fConst23 * (fConst23 - fSlow38) + 1.0f;
		float fSlow43 = fConst26 * (fConst26 + fSlow1) + 1.0f;
		float fSlow44 = fConst26 / fSlow43;
		float fSlow45 = 1.0f / fSlow43;
		float fSlow46 = fConst26 * (fConst26 - fSlow1) + 1.0f;
		float fSlow47 = fConst29 * (fConst29 + fSlow28) + 1.0f;
		float fSlow48 = fConst29 / fSlow47;
		float fSlow49 = 1.0f / fSlow47;
		float fSlow50 = fConst29 * (fConst29 - fSlow28) + 1.0f;
		float fSlow51 = fConst32 * (fConst32 + fSlow14) + 1.0f;
		float fSlow52 = fConst32 / fSlow51;
		float fSlow53 = 1.0f / fSlow51;
		float fSlow54 = fConst32 * (fConst32 - fSlow14) + 1.0f;
		float fSlow55 = 0.17712227f * fSlow0;
		float fSlow56 = fConst35 * (fConst35 + fSlow55) + 1.0f;
		float fSlow57 = fConst35 / fSlow56;
		float fSlow58 = 1.0f / fSlow56;
		float fSlow59 = fConst35 * (fConst35 - fSlow55) + 1.0f;
		float fSlow60 = 0.17712227f * fSlow0;
		float fSlow61 = fConst38 * (fConst38 + fSlow60) + 1.0f;
		float fSlow62 = fConst38 / fSlow61;
		float fSlow63 = 1.0f / fSlow61;
		float fSlow64 = fConst38 * (fConst38 - fSlow60) + 1.0f;
		float fSlow65 = fConst41 * (fConst41 + fSlow55) + 1.0f;
		float fSlow66 = fConst41 / fSlow65;
		float fSlow67 = 1.0f / fSlow65;
		float fSlow68 = fConst41 * (fConst41 - fSlow55) + 1.0f;
		float fSlow69 = 0.17712227f * fSlow0;
		float fSlow70 = fConst44 * (fConst44 + fSlow69) + 1.0f;
		float fSlow71 = fConst44 / fSlow70;
		float fSlow72 = 1.0f / fSlow70;
		float fSlow73 = fConst44 * (fConst44 - fSlow69) + 1.0f;
		float fSlow74 = fConst47 * (fConst47 + fSlow23) + 1.0f;
		float fSlow75 = fConst47 / fSlow74;
		float fSlow76 = 1.0f / fSlow74;
		float fSlow77 = fConst47 * (fConst47 - fSlow23) + 1.0f;
		float fSlow78 = fConst50 * (fConst50 + fSlow23) + 1.0f;
		float fSlow79 = fConst50 / fSlow78;
		float fSlow80 = 1.0f / fSlow78;
		float fSlow81 = fConst50 * (fConst50 - fSlow23) + 1.0f;
		float fSlow82 = fConst53 * (fConst53 + fSlow14) + 1.0f;
		float fSlow83 = fConst53 / fSlow82;
		float fSlow84 = 1.0f / fSlow82;
		float fSlow85 = fConst53 * (fConst53 - fSlow14) + 1.0f;
		float fSlow86 = 0.17712227f * fSlow0;
		float fSlow87 = fConst56 * (fConst56 + fSlow86) + 1.0f;
		float fSlow88 = fConst56 / fSlow87;
		float fSlow89 = 1.0f / fSlow87;
		float fSlow90 = fConst56 * (fConst56 - fSlow86) + 1.0f;
		float fSlow91 = fConst59 * (fConst59 + fSlow28) + 1.0f;
		float fSlow92 = fConst59 / fSlow91;
		float fSlow93 = 1.0f / fSlow91;
		float fSlow94 = fConst59 * (fConst59 - fSlow28) + 1.0f;
		float fSlow95 = fConst62 * (fConst62 + fSlow69) + 1.0f;
		float fSlow96 = fConst62 / fSlow95;
		float fSlow97 = 1.0f / fSlow95;
		float fSlow98 = fConst62 * (fConst62 - fSlow69) + 1.0f;
		float fSlow99 = fConst65 * (fConst65 + fSlow38) + 1.0f;
		float fSlow100 = fConst65 / fSlow99;
		float fSlow101 = 1.0f / fSlow99;
		float fSlow102 = fConst65 * (fConst65 - fSlow38) + 1.0f;
		float fSlow103 = fConst68 * (fConst68 + fSlow69) + 1.0f;
		float fSlow104 = fConst68 / fSlow103;
		float fSlow105 = 1.0f / fSlow103;
		float fSlow106 = fConst68 * (fConst68 - fSlow69) + 1.0f;
		float fSlow107 = fConst71 * (fConst71 + fSlow38) + 1.0f;
		float fSlow108 = fConst71 / fSlow107;
		float fSlow109 = 1.0f / fSlow107;
		float fSlow110 = fConst71 * (fConst71 - fSlow38) + 1.0f;
		float fSlow111 = 0.17712227f * fSlow0;
		float fSlow112 = fConst74 * (fConst74 + fSlow111) + 1.0f;
		float fSlow113 = fConst74 / fSlow112;
		float fSlow114 = 1.0f / fSlow112;
		float fSlow115 = fConst74 * (fConst74 - fSlow111) + 1.0f;
		float fSlow116 = fConst77 * (fConst77 + fSlow23) + 1.0f;
		float fSlow117 = fConst77 / fSlow116;
		float fSlow118 = 1.0f / fSlow116;
		float fSlow119 = fConst77 * (fConst77 - fSlow23) + 1.0f;
		float fSlow120 = fConst80 * (fConst80 + fSlow1) + 1.0f;
		float fSlow121 = fConst80 / fSlow120;
		float fSlow122 = 1.0f / fSlow120;
		float fSlow123 = fConst80 * (fConst80 - fSlow1) + 1.0f;
		float fSlow124 = fConst83 * (fConst83 + fSlow55) + 1.0f;
		float fSlow125 = fConst83 / fSlow124;
		float fSlow126 = 1.0f / fSlow124;
		float fSlow127 = fConst83 * (fConst83 - fSlow55) + 1.0f;
		float fSlow128 = 0.17712227f * fSlow0;
		float fSlow129 = fConst86 * (fConst86 + fSlow128) + 1.0f;
		float fSlow130 = fConst86 / fSlow129;
		float fSlow131 = 1.0f / fSlow129;
		float fSlow132 = fConst86 * (fConst86 - fSlow128) + 1.0f;
		float fSlow133 = fConst89 * (fConst89 + fSlow1) + 1.0f;
		float fSlow134 = fConst89 / fSlow133;
		float fSlow135 = 1.0f / fSlow133;
		float fSlow136 = fConst89 * (fConst89 - fSlow1) + 1.0f;
		float fSlow137 = fConst92 * (fConst92 + fSlow69) + 1.0f;
		float fSlow138 = fConst92 / fSlow137;
		float fSlow139 = 1.0f / fSlow137;
		float fSlow140 = fConst92 * (fConst92 - fSlow69) + 1.0f;
		float fSlow141 = 0.17712227f * fSlow0;
		float fSlow142 = fConst95 * (fConst95 + fSlow141) + 1.0f;
		float fSlow143 = fConst95 / fSlow142;
		float fSlow144 = 1.0f / fSlow142;
		float fSlow145 = fConst95 * (fConst95 - fSlow141) + 1.0f;
		float fSlow146 = fConst98 * (fConst98 + fSlow111) + 1.0f;
		float fSlow147 = fConst98 / fSlow146;
		float fSlow148 = 1.0f / fSlow146;
		float fSlow149 = fConst98 * (fConst98 - fSlow111) + 1.0f;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			iVec0[0] = 1;
			fRec1[0] = fTemp0 - fSlow4 * (fSlow5 * fRec1[2] + fConst3 * fRec1[1]);
			float fTemp1 = std::fabs(fSlow3 * (fRec1[0] - fRec1[2]));
			float fTemp2 = ((fTemp1 > fRec0[1]) ? fSlow11 : fSlow8);
			fRec0[0] = fTemp1 * (1.0f - fTemp2) + fRec0[1] * fTemp2;
			fRec3[0] = fSlow12 + fConst6 * fRec3[1];
			float fTemp3 = ((1 - iVec0[1]) ? 0.0f : fSlow13 + fRec4[1]);
			fRec4[0] = fTemp3 - std::floor(fTemp3);
			float fTemp4 = fRec3[0] * static_cast<float>((fRec4[0] - fRec4[1]) < 0.0f);
			fRec2[0] = fTemp4 - fSlow4 * (fSlow5 * fRec2[2] + fConst3 * fRec2[1]);
			float fTemp5 = fRec2[0] - fRec2[2];
			fRec6[0] = fTemp0 - fSlow17 * (fSlow18 * fRec6[2] + fConst9 * fRec6[1]);
			float fTemp6 = std::fabs(fSlow16 * (fRec6[0] - fRec6[2]));
			float fTemp7 = ((fTemp6 > fRec5[1]) ? fSlow11 : fSlow8);
			fRec5[0] = fTemp6 * (1.0f - fTemp7) + fRec5[1] * fTemp7;
			fRec7[0] = fTemp4 - fSlow17 * (fSlow18 * fRec7[2] + fConst9 * fRec7[1]);
			float fTemp8 = fRec7[0] - fRec7[2];
			fRec9[0] = fTemp0 - fSlow21 * (fSlow22 * fRec9[2] + fConst12 * fRec9[1]);
			float fTemp9 = std::fabs(fSlow20 * (fRec9[0] - fRec9[2]));
			float fTemp10 = ((fTemp9 > fRec8[1]) ? fSlow11 : fSlow8);
			fRec8[0] = fTemp9 * (1.0f - fTemp10) + fRec8[1] * fTemp10;
			fRec10[0] = fTemp4 - fSlow21 * (fSlow22 * fRec10[2] + fConst12 * fRec10[1]);
			float fTemp11 = fRec10[0] - fRec10[2];
			fRec12[0] = fTemp0 - fSlow26 * (fSlow27 * fRec12[2] + fConst15 * fRec12[1]);
			float fTemp12 = std::fabs(fSlow25 * (fRec12[0] - fRec12[2]));
			float fTemp13 = ((fTemp12 > fRec11[1]) ? fSlow11 : fSlow8);
			fRec11[0] = fTemp12 * (1.0f - fTemp13) + fRec11[1] * fTemp13;
			fRec13[0] = fTemp4 - fSlow26 * (fSlow27 * fRec13[2] + fConst15 * fRec13[1]);
			float fTemp14 = fRec13[0] - fRec13[2];
			fRec15[0] = fTemp0 - fSlow31 * (fSlow32 * fRec15[2] + fConst18 * fRec15[1]);
			float fTemp15 = std::fabs(fSlow30 * (fRec15[0] - fRec15[2]));
			float fTemp16 = ((fTemp15 > fRec14[1]) ? fSlow11 : fSlow8);
			fRec14[0] = fTemp15 * (1.0f - fTemp16) + fRec14[1] * fTemp16;
			fRec16[0] = fTemp4 - fSlow31 * (fSlow32 * fRec16[2] + fConst18 * fRec16[1]);
			float fTemp17 = fRec16[0] - fRec16[2];
			fRec18[0] = fTemp0 - fSlow36 * (fSlow37 * fRec18[2] + fConst21 * fRec18[1]);
			float fTemp18 = std::fabs(fSlow35 * (fRec18[0] - fRec18[2]));
			float fTemp19 = ((fTemp18 > fRec17[1]) ? fSlow11 : fSlow8);
			fRec17[0] = fTemp18 * (1.0f - fTemp19) + fRec17[1] * fTemp19;
			fRec19[0] = fTemp4 - fSlow36 * (fSlow37 * fRec19[2] + fConst21 * fRec19[1]);
			float fTemp20 = fRec19[0] - fRec19[2];
			fRec21[0] = fTemp0 - fSlow41 * (fSlow42 * fRec21[2] + fConst24 * fRec21[1]);
			float fTemp21 = std::fabs(fSlow40 * (fRec21[0] - fRec21[2]));
			float fTemp22 = ((fTemp21 > fRec20[1]) ? fSlow11 : fSlow8);
			fRec20[0] = fTemp21 * (1.0f - fTemp22) + fRec20[1] * fTemp22;
			fRec22[0] = fTemp4 - fSlow41 * (fSlow42 * fRec22[2] + fConst24 * fRec22[1]);
			float fTemp23 = fRec22[0] - fRec22[2];
			fRec24[0] = fTemp0 - fSlow45 * (fSlow46 * fRec24[2] + fConst27 * fRec24[1]);
			float fTemp24 = std::fabs(fSlow44 * (fRec24[0] - fRec24[2]));
			float fTemp25 = ((fTemp24 > fRec23[1]) ? fSlow11 : fSlow8);
			fRec23[0] = fTemp24 * (1.0f - fTemp25) + fRec23[1] * fTemp25;
			fRec25[0] = fTemp4 - fSlow45 * (fSlow46 * fRec25[2] + fConst27 * fRec25[1]);
			float fTemp26 = fRec25[0] - fRec25[2];
			fRec27[0] = fTemp0 - fSlow49 * (fSlow50 * fRec27[2] + fConst30 * fRec27[1]);
			float fTemp27 = std::fabs(fSlow48 * (fRec27[0] - fRec27[2]));
			float fTemp28 = ((fTemp27 > fRec26[1]) ? fSlow11 : fSlow8);
			fRec26[0] = fTemp27 * (1.0f - fTemp28) + fRec26[1] * fTemp28;
			fRec28[0] = fTemp4 - fSlow49 * (fSlow50 * fRec28[2] + fConst30 * fRec28[1]);
			float fTemp29 = fRec28[0] - fRec28[2];
			fRec30[0] = fTemp0 - fSlow53 * (fSlow54 * fRec30[2] + fConst33 * fRec30[1]);
			float fTemp30 = std::fabs(fSlow52 * (fRec30[0] - fRec30[2]));
			float fTemp31 = ((fTemp30 > fRec29[1]) ? fSlow11 : fSlow8);
			fRec29[0] = fTemp30 * (1.0f - fTemp31) + fRec29[1] * fTemp31;
			fRec31[0] = fTemp4 - fSlow53 * (fSlow54 * fRec31[2] + fConst33 * fRec31[1]);
			float fTemp32 = fRec31[0] - fRec31[2];
			fRec33[0] = fTemp0 - fSlow58 * (fSlow59 * fRec33[2] + fConst36 * fRec33[1]);
			float fTemp33 = std::fabs(fSlow57 * (fRec33[0] - fRec33[2]));
			float fTemp34 = ((fTemp33 > fRec32[1]) ? fSlow11 : fSlow8);
			fRec32[0] = fTemp33 * (1.0f - fTemp34) + fRec32[1] * fTemp34;
			fRec34[0] = fTemp4 - fSlow58 * (fSlow59 * fRec34[2] + fConst36 * fRec34[1]);
			float fTemp35 = fRec34[0] - fRec34[2];
			fRec36[0] = fTemp0 - fSlow63 * (fSlow64 * fRec36[2] + fConst39 * fRec36[1]);
			float fTemp36 = std::fabs(fSlow62 * (fRec36[0] - fRec36[2]));
			float fTemp37 = ((fTemp36 > fRec35[1]) ? fSlow11 : fSlow8);
			fRec35[0] = fTemp36 * (1.0f - fTemp37) + fRec35[1] * fTemp37;
			fRec37[0] = fTemp4 - fSlow63 * (fSlow64 * fRec37[2] + fConst39 * fRec37[1]);
			float fTemp38 = fRec37[0] - fRec37[2];
			fRec39[0] = fTemp0 - fSlow67 * (fSlow68 * fRec39[2] + fConst42 * fRec39[1]);
			float fTemp39 = std::fabs(fSlow66 * (fRec39[0] - fRec39[2]));
			float fTemp40 = ((fTemp39 > fRec38[1]) ? fSlow11 : fSlow8);
			fRec38[0] = fTemp39 * (1.0f - fTemp40) + fRec38[1] * fTemp40;
			fRec40[0] = fTemp4 - fSlow67 * (fSlow68 * fRec40[2] + fConst42 * fRec40[1]);
			float fTemp41 = fRec40[0] - fRec40[2];
			fRec42[0] = fTemp0 - fSlow72 * (fSlow73 * fRec42[2] + fConst45 * fRec42[1]);
			float fTemp42 = std::fabs(fSlow71 * (fRec42[0] - fRec42[2]));
			float fTemp43 = ((fTemp42 > fRec41[1]) ? fSlow11 : fSlow8);
			fRec41[0] = fTemp42 * (1.0f - fTemp43) + fRec41[1] * fTemp43;
			fRec43[0] = fTemp4 - fSlow72 * (fSlow73 * fRec43[2] + fConst45 * fRec43[1]);
			float fTemp44 = fRec43[0] - fRec43[2];
			fRec45[0] = fTemp0 - fSlow76 * (fSlow77 * fRec45[2] + fConst48 * fRec45[1]);
			float fTemp45 = std::fabs(fSlow75 * (fRec45[0] - fRec45[2]));
			float fTemp46 = ((fTemp45 > fRec44[1]) ? fSlow11 : fSlow8);
			fRec44[0] = fTemp45 * (1.0f - fTemp46) + fRec44[1] * fTemp46;
			fRec46[0] = fTemp4 - fSlow76 * (fSlow77 * fRec46[2] + fConst48 * fRec46[1]);
			float fTemp47 = fRec46[0] - fRec46[2];
			fRec48[0] = fTemp0 - fSlow80 * (fSlow81 * fRec48[2] + fConst51 * fRec48[1]);
			float fTemp48 = std::fabs(fSlow79 * (fRec48[0] - fRec48[2]));
			float fTemp49 = ((fTemp48 > fRec47[1]) ? fSlow11 : fSlow8);
			fRec47[0] = fTemp48 * (1.0f - fTemp49) + fRec47[1] * fTemp49;
			fRec49[0] = fTemp4 - fSlow80 * (fSlow81 * fRec49[2] + fConst51 * fRec49[1]);
			float fTemp50 = fRec49[0] - fRec49[2];
			fRec51[0] = fTemp0 - fSlow84 * (fSlow85 * fRec51[2] + fConst54 * fRec51[1]);
			float fTemp51 = std::fabs(fSlow83 * (fRec51[0] - fRec51[2]));
			float fTemp52 = ((fTemp51 > fRec50[1]) ? fSlow11 : fSlow8);
			fRec50[0] = fTemp51 * (1.0f - fTemp52) + fRec50[1] * fTemp52;
			fRec52[0] = fTemp4 - fSlow84 * (fSlow85 * fRec52[2] + fConst54 * fRec52[1]);
			float fTemp53 = fRec52[0] - fRec52[2];
			fRec54[0] = fTemp0 - fSlow89 * (fSlow90 * fRec54[2] + fConst57 * fRec54[1]);
			float fTemp54 = std::fabs(fSlow88 * (fRec54[0] - fRec54[2]));
			float fTemp55 = ((fTemp54 > fRec53[1]) ? fSlow11 : fSlow8);
			fRec53[0] = fTemp54 * (1.0f - fTemp55) + fRec53[1] * fTemp55;
			fRec55[0] = fTemp4 - fSlow89 * (fSlow90 * fRec55[2] + fConst57 * fRec55[1]);
			float fTemp56 = fRec55[0] - fRec55[2];
			fRec57[0] = fTemp0 - fSlow93 * (fSlow94 * fRec57[2] + fConst60 * fRec57[1]);
			float fTemp57 = std::fabs(fSlow92 * (fRec57[0] - fRec57[2]));
			float fTemp58 = ((fTemp57 > fRec56[1]) ? fSlow11 : fSlow8);
			fRec56[0] = fTemp57 * (1.0f - fTemp58) + fRec56[1] * fTemp58;
			fRec58[0] = fTemp4 - fSlow93 * (fSlow94 * fRec58[2] + fConst60 * fRec58[1]);
			float fTemp59 = fRec58[0] - fRec58[2];
			fRec60[0] = fTemp0 - fSlow97 * (fSlow98 * fRec60[2] + fConst63 * fRec60[1]);
			float fTemp60 = std::fabs(fSlow96 * (fRec60[0] - fRec60[2]));
			float fTemp61 = ((fTemp60 > fRec59[1]) ? fSlow11 : fSlow8);
			fRec59[0] = fTemp60 * (1.0f - fTemp61) + fRec59[1] * fTemp61;
			fRec61[0] = fTemp4 - fSlow97 * (fSlow98 * fRec61[2] + fConst63 * fRec61[1]);
			float fTemp62 = fRec61[0] - fRec61[2];
			fRec63[0] = fTemp0 - fSlow101 * (fSlow102 * fRec63[2] + fConst66 * fRec63[1]);
			float fTemp63 = std::fabs(fSlow100 * (fRec63[0] - fRec63[2]));
			float fTemp64 = ((fTemp63 > fRec62[1]) ? fSlow11 : fSlow8);
			fRec62[0] = fTemp63 * (1.0f - fTemp64) + fRec62[1] * fTemp64;
			fRec64[0] = fTemp4 - fSlow101 * (fSlow102 * fRec64[2] + fConst66 * fRec64[1]);
			float fTemp65 = fRec64[0] - fRec64[2];
			fRec66[0] = fTemp0 - fSlow105 * (fSlow106 * fRec66[2] + fConst69 * fRec66[1]);
			float fTemp66 = std::fabs(fSlow104 * (fRec66[0] - fRec66[2]));
			float fTemp67 = ((fTemp66 > fRec65[1]) ? fSlow11 : fSlow8);
			fRec65[0] = fTemp66 * (1.0f - fTemp67) + fRec65[1] * fTemp67;
			fRec67[0] = fTemp4 - fSlow105 * (fSlow106 * fRec67[2] + fConst69 * fRec67[1]);
			float fTemp68 = fRec67[0] - fRec67[2];
			fRec69[0] = fTemp0 - fSlow109 * (fSlow110 * fRec69[2] + fConst72 * fRec69[1]);
			float fTemp69 = std::fabs(fSlow108 * (fRec69[0] - fRec69[2]));
			float fTemp70 = ((fTemp69 > fRec68[1]) ? fSlow11 : fSlow8);
			fRec68[0] = fTemp69 * (1.0f - fTemp70) + fRec68[1] * fTemp70;
			fRec70[0] = fTemp4 - fSlow109 * (fSlow110 * fRec70[2] + fConst72 * fRec70[1]);
			float fTemp71 = fRec70[0] - fRec70[2];
			fRec72[0] = fTemp0 - fSlow114 * (fSlow115 * fRec72[2] + fConst75 * fRec72[1]);
			float fTemp72 = std::fabs(fSlow113 * (fRec72[0] - fRec72[2]));
			float fTemp73 = ((fTemp72 > fRec71[1]) ? fSlow11 : fSlow8);
			fRec71[0] = fTemp72 * (1.0f - fTemp73) + fRec71[1] * fTemp73;
			fRec73[0] = fTemp4 - fSlow114 * (fSlow115 * fRec73[2] + fConst75 * fRec73[1]);
			float fTemp74 = fRec73[0] - fRec73[2];
			fRec75[0] = fTemp0 - fSlow118 * (fSlow119 * fRec75[2] + fConst78 * fRec75[1]);
			float fTemp75 = std::fabs(fSlow117 * (fRec75[0] - fRec75[2]));
			float fTemp76 = ((fTemp75 > fRec74[1]) ? fSlow11 : fSlow8);
			fRec74[0] = fTemp75 * (1.0f - fTemp76) + fRec74[1] * fTemp76;
			fRec76[0] = fTemp4 - fSlow118 * (fSlow119 * fRec76[2] + fConst78 * fRec76[1]);
			float fTemp77 = fRec76[0] - fRec76[2];
			fRec78[0] = fTemp0 - fSlow122 * (fSlow123 * fRec78[2] + fConst81 * fRec78[1]);
			float fTemp78 = std::fabs(fSlow121 * (fRec78[0] - fRec78[2]));
			float fTemp79 = ((fTemp78 > fRec77[1]) ? fSlow11 : fSlow8);
			fRec77[0] = fTemp78 * (1.0f - fTemp79) + fRec77[1] * fTemp79;
			fRec79[0] = fTemp4 - fSlow122 * (fSlow123 * fRec79[2] + fConst81 * fRec79[1]);
			float fTemp80 = fRec79[0] - fRec79[2];
			fRec81[0] = fTemp0 - fSlow126 * (fSlow127 * fRec81[2] + fConst84 * fRec81[1]);
			float fTemp81 = std::fabs(fSlow125 * (fRec81[0] - fRec81[2]));
			float fTemp82 = ((fTemp81 > fRec80[1]) ? fSlow11 : fSlow8);
			fRec80[0] = fTemp81 * (1.0f - fTemp82) + fRec80[1] * fTemp82;
			fRec82[0] = fTemp4 - fSlow126 * (fSlow127 * fRec82[2] + fConst84 * fRec82[1]);
			float fTemp83 = fRec82[0] - fRec82[2];
			fRec84[0] = fTemp0 - fSlow131 * (fSlow132 * fRec84[2] + fConst87 * fRec84[1]);
			float fTemp84 = std::fabs(fSlow130 * (fRec84[0] - fRec84[2]));
			float fTemp85 = ((fTemp84 > fRec83[1]) ? fSlow11 : fSlow8);
			fRec83[0] = fTemp84 * (1.0f - fTemp85) + fRec83[1] * fTemp85;
			fRec85[0] = fTemp4 - fSlow131 * (fSlow132 * fRec85[2] + fConst87 * fRec85[1]);
			float fTemp86 = fRec85[0] - fRec85[2];
			fRec87[0] = fTemp0 - fSlow135 * (fSlow136 * fRec87[2] + fConst90 * fRec87[1]);
			float fTemp87 = std::fabs(fSlow134 * (fRec87[0] - fRec87[2]));
			float fTemp88 = ((fTemp87 > fRec86[1]) ? fSlow11 : fSlow8);
			fRec86[0] = fTemp87 * (1.0f - fTemp88) + fRec86[1] * fTemp88;
			fRec88[0] = fTemp4 - fSlow135 * (fSlow136 * fRec88[2] + fConst90 * fRec88[1]);
			float fTemp89 = fRec88[0] - fRec88[2];
			fRec90[0] = fTemp0 - fSlow139 * (fSlow140 * fRec90[2] + fConst93 * fRec90[1]);
			float fTemp90 = std::fabs(fSlow138 * (fRec90[0] - fRec90[2]));
			float fTemp91 = ((fTemp90 > fRec89[1]) ? fSlow11 : fSlow8);
			fRec89[0] = fTemp90 * (1.0f - fTemp91) + fRec89[1] * fTemp91;
			fRec91[0] = fTemp4 - fSlow139 * (fSlow140 * fRec91[2] + fConst93 * fRec91[1]);
			float fTemp92 = fRec91[0] - fRec91[2];
			fRec93[0] = fTemp0 - fSlow144 * (fSlow145 * fRec93[2] + fConst96 * fRec93[1]);
			float fTemp93 = std::fabs(fSlow143 * (fRec93[0] - fRec93[2]));
			float fTemp94 = ((fTemp93 > fRec92[1]) ? fSlow11 : fSlow8);
			fRec92[0] = fTemp93 * (1.0f - fTemp94) + fRec92[1] * fTemp94;
			fRec94[0] = fTemp4 - fSlow144 * (fSlow145 * fRec94[2] + fConst96 * fRec94[1]);
			float fTemp95 = fRec94[0] - fRec94[2];
			fRec96[0] = fTemp0 - fSlow148 * (fSlow149 * fRec96[2] + fConst99 * fRec96[1]);
			float fTemp96 = std::fabs(fSlow147 * (fRec96[0] - fRec96[2]));
			float fTemp97 = ((fTemp96 > fRec95[1]) ? fSlow11 : fSlow8);
			fRec95[0] = fTemp96 * (1.0f - fTemp97) + fRec95[1] * fTemp97;
			fRec97[0] = fTemp4 - fSlow148 * (fSlow149 * fRec97[2] + fConst99 * fRec97[1]);
			float fTemp98 = fRec97[0] - fRec97[2];
			output0[i0] = static_cast<FAUSTFLOAT>(2.0f * (fSlow3 * fRec0[0] * fTemp5 + fSlow16 * fRec5[0] * fTemp8 + fSlow20 * fRec8[0] * fTemp11 + fSlow25 * fRec11[0] * fTemp14 + fSlow30 * fRec14[0] * fTemp17 + fSlow35 * fRec17[0] * fTemp20 + fSlow40 * fRec20[0] * fTemp23 + fSlow44 * fRec23[0] * fTemp26 + fSlow48 * fRec26[0] * fTemp29 + fSlow52 * fRec29[0] * fTemp32 + fSlow57 * fRec32[0] * fTemp35 + fSlow62 * fRec35[0] * fTemp38 + fSlow66 * fRec38[0] * fTemp41 + fSlow71 * fRec41[0] * fTemp44 + fSlow75 * fRec44[0] * fTemp47 + fSlow79 * fRec47[0] * fTemp50 + fSlow83 * fRec50[0] * fTemp53 + fSlow88 * fRec53[0] * fTemp56 + fSlow92 * fRec56[0] * fTemp59 + fSlow96 * fRec59[0] * fTemp62 + fSlow100 * fRec62[0] * fTemp65 + fSlow104 * fRec65[0] * fTemp68 + fSlow108 * fRec68[0] * fTemp71 + fSlow113 * fRec71[0] * fTemp74 + fSlow117 * fRec74[0] * fTemp77 + fSlow121 * fRec77[0] * fTemp80 + fSlow125 * fRec80[0] * fTemp83 + fSlow130 * fRec83[0] * fTemp86 + fSlow134 * fRec86[0] * fTemp89 + fSlow138 * fRec89[0] * fTemp92 + fSlow143 * fRec92[0] * fTemp95 + fSlow147 * fRec95[0] * fTemp98));
			float fTemp99 = static_cast<float>(input1[i0]);
			fRec99[0] = fTemp99 - fSlow4 * (fSlow5 * fRec99[2] + fConst3 * fRec99[1]);
			float fTemp100 = std::fabs(fSlow3 * (fRec99[0] - fRec99[2]));
			float fTemp101 = ((fTemp100 > fRec98[1]) ? fSlow11 : fSlow8);
			fRec98[0] = fTemp100 * (1.0f - fTemp101) + fRec98[1] * fTemp101;
			fRec101[0] = fTemp99 - fSlow17 * (fSlow18 * fRec101[2] + fConst9 * fRec101[1]);
			float fTemp102 = std::fabs(fSlow16 * (fRec101[0] - fRec101[2]));
			float fTemp103 = ((fTemp102 > fRec100[1]) ? fSlow11 : fSlow8);
			fRec100[0] = fTemp102 * (1.0f - fTemp103) + fRec100[1] * fTemp103;
			fRec103[0] = fTemp99 - fSlow21 * (fSlow22 * fRec103[2] + fConst12 * fRec103[1]);
			float fTemp104 = std::fabs(fSlow20 * (fRec103[0] - fRec103[2]));
			float fTemp105 = ((fTemp104 > fRec102[1]) ? fSlow11 : fSlow8);
			fRec102[0] = fTemp104 * (1.0f - fTemp105) + fRec102[1] * fTemp105;
			fRec105[0] = fTemp99 - fSlow26 * (fSlow27 * fRec105[2] + fConst15 * fRec105[1]);
			float fTemp106 = std::fabs(fSlow25 * (fRec105[0] - fRec105[2]));
			float fTemp107 = ((fTemp106 > fRec104[1]) ? fSlow11 : fSlow8);
			fRec104[0] = fTemp106 * (1.0f - fTemp107) + fRec104[1] * fTemp107;
			fRec107[0] = fTemp99 - fSlow31 * (fSlow32 * fRec107[2] + fConst18 * fRec107[1]);
			float fTemp108 = std::fabs(fSlow30 * (fRec107[0] - fRec107[2]));
			float fTemp109 = ((fTemp108 > fRec106[1]) ? fSlow11 : fSlow8);
			fRec106[0] = fTemp108 * (1.0f - fTemp109) + fRec106[1] * fTemp109;
			fRec109[0] = fTemp99 - fSlow36 * (fSlow37 * fRec109[2] + fConst21 * fRec109[1]);
			float fTemp110 = std::fabs(fSlow35 * (fRec109[0] - fRec109[2]));
			float fTemp111 = ((fTemp110 > fRec108[1]) ? fSlow11 : fSlow8);
			fRec108[0] = fTemp110 * (1.0f - fTemp111) + fRec108[1] * fTemp111;
			fRec111[0] = fTemp99 - fSlow41 * (fSlow42 * fRec111[2] + fConst24 * fRec111[1]);
			float fTemp112 = std::fabs(fSlow40 * (fRec111[0] - fRec111[2]));
			float fTemp113 = ((fTemp112 > fRec110[1]) ? fSlow11 : fSlow8);
			fRec110[0] = fTemp112 * (1.0f - fTemp113) + fRec110[1] * fTemp113;
			fRec113[0] = fTemp99 - fSlow45 * (fSlow46 * fRec113[2] + fConst27 * fRec113[1]);
			float fTemp114 = std::fabs(fSlow44 * (fRec113[0] - fRec113[2]));
			float fTemp115 = ((fTemp114 > fRec112[1]) ? fSlow11 : fSlow8);
			fRec112[0] = fTemp114 * (1.0f - fTemp115) + fRec112[1] * fTemp115;
			fRec115[0] = fTemp99 - fSlow49 * (fSlow50 * fRec115[2] + fConst30 * fRec115[1]);
			float fTemp116 = std::fabs(fSlow48 * (fRec115[0] - fRec115[2]));
			float fTemp117 = ((fTemp116 > fRec114[1]) ? fSlow11 : fSlow8);
			fRec114[0] = fTemp116 * (1.0f - fTemp117) + fRec114[1] * fTemp117;
			fRec117[0] = fTemp99 - fSlow53 * (fSlow54 * fRec117[2] + fConst33 * fRec117[1]);
			float fTemp118 = std::fabs(fSlow52 * (fRec117[0] - fRec117[2]));
			float fTemp119 = ((fTemp118 > fRec116[1]) ? fSlow11 : fSlow8);
			fRec116[0] = fTemp118 * (1.0f - fTemp119) + fRec116[1] * fTemp119;
			fRec119[0] = fTemp99 - fSlow58 * (fSlow59 * fRec119[2] + fConst36 * fRec119[1]);
			float fTemp120 = std::fabs(fSlow57 * (fRec119[0] - fRec119[2]));
			float fTemp121 = ((fTemp120 > fRec118[1]) ? fSlow11 : fSlow8);
			fRec118[0] = fTemp120 * (1.0f - fTemp121) + fRec118[1] * fTemp121;
			fRec121[0] = fTemp99 - fSlow63 * (fSlow64 * fRec121[2] + fConst39 * fRec121[1]);
			float fTemp122 = std::fabs(fSlow62 * (fRec121[0] - fRec121[2]));
			float fTemp123 = ((fTemp122 > fRec120[1]) ? fSlow11 : fSlow8);
			fRec120[0] = fTemp122 * (1.0f - fTemp123) + fRec120[1] * fTemp123;
			fRec123[0] = fTemp99 - fSlow67 * (fSlow68 * fRec123[2] + fConst42 * fRec123[1]);
			float fTemp124 = std::fabs(fSlow66 * (fRec123[0] - fRec123[2]));
			float fTemp125 = ((fTemp124 > fRec122[1]) ? fSlow11 : fSlow8);
			fRec122[0] = fTemp124 * (1.0f - fTemp125) + fRec122[1] * fTemp125;
			fRec125[0] = fTemp99 - fSlow72 * (fSlow73 * fRec125[2] + fConst45 * fRec125[1]);
			float fTemp126 = std::fabs(fSlow71 * (fRec125[0] - fRec125[2]));
			float fTemp127 = ((fTemp126 > fRec124[1]) ? fSlow11 : fSlow8);
			fRec124[0] = fTemp126 * (1.0f - fTemp127) + fRec124[1] * fTemp127;
			fRec127[0] = fTemp99 - fSlow76 * (fSlow77 * fRec127[2] + fConst48 * fRec127[1]);
			float fTemp128 = std::fabs(fSlow75 * (fRec127[0] - fRec127[2]));
			float fTemp129 = ((fTemp128 > fRec126[1]) ? fSlow11 : fSlow8);
			fRec126[0] = fTemp128 * (1.0f - fTemp129) + fRec126[1] * fTemp129;
			fRec129[0] = fTemp99 - fSlow80 * (fSlow81 * fRec129[2] + fConst51 * fRec129[1]);
			float fTemp130 = std::fabs(fSlow79 * (fRec129[0] - fRec129[2]));
			float fTemp131 = ((fTemp130 > fRec128[1]) ? fSlow11 : fSlow8);
			fRec128[0] = fTemp130 * (1.0f - fTemp131) + fRec128[1] * fTemp131;
			fRec131[0] = fTemp99 - fSlow84 * (fSlow85 * fRec131[2] + fConst54 * fRec131[1]);
			float fTemp132 = std::fabs(fSlow83 * (fRec131[0] - fRec131[2]));
			float fTemp133 = ((fTemp132 > fRec130[1]) ? fSlow11 : fSlow8);
			fRec130[0] = fTemp132 * (1.0f - fTemp133) + fRec130[1] * fTemp133;
			fRec133[0] = fTemp99 - fSlow89 * (fSlow90 * fRec133[2] + fConst57 * fRec133[1]);
			float fTemp134 = std::fabs(fSlow88 * (fRec133[0] - fRec133[2]));
			float fTemp135 = ((fTemp134 > fRec132[1]) ? fSlow11 : fSlow8);
			fRec132[0] = fTemp134 * (1.0f - fTemp135) + fRec132[1] * fTemp135;
			fRec135[0] = fTemp99 - fSlow93 * (fSlow94 * fRec135[2] + fConst60 * fRec135[1]);
			float fTemp136 = std::fabs(fSlow92 * (fRec135[0] - fRec135[2]));
			float fTemp137 = ((fTemp136 > fRec134[1]) ? fSlow11 : fSlow8);
			fRec134[0] = fTemp136 * (1.0f - fTemp137) + fRec134[1] * fTemp137;
			fRec137[0] = fTemp99 - fSlow97 * (fSlow98 * fRec137[2] + fConst63 * fRec137[1]);
			float fTemp138 = std::fabs(fSlow96 * (fRec137[0] - fRec137[2]));
			float fTemp139 = ((fTemp138 > fRec136[1]) ? fSlow11 : fSlow8);
			fRec136[0] = fTemp138 * (1.0f - fTemp139) + fRec136[1] * fTemp139;
			fRec139[0] = fTemp99 - fSlow101 * (fSlow102 * fRec139[2] + fConst66 * fRec139[1]);
			float fTemp140 = std::fabs(fSlow100 * (fRec139[0] - fRec139[2]));
			float fTemp141 = ((fTemp140 > fRec138[1]) ? fSlow11 : fSlow8);
			fRec138[0] = fTemp140 * (1.0f - fTemp141) + fRec138[1] * fTemp141;
			fRec141[0] = fTemp99 - fSlow105 * (fSlow106 * fRec141[2] + fConst69 * fRec141[1]);
			float fTemp142 = std::fabs(fSlow104 * (fRec141[0] - fRec141[2]));
			float fTemp143 = ((fTemp142 > fRec140[1]) ? fSlow11 : fSlow8);
			fRec140[0] = fTemp142 * (1.0f - fTemp143) + fRec140[1] * fTemp143;
			fRec143[0] = fTemp99 - fSlow109 * (fSlow110 * fRec143[2] + fConst72 * fRec143[1]);
			float fTemp144 = std::fabs(fSlow108 * (fRec143[0] - fRec143[2]));
			float fTemp145 = ((fTemp144 > fRec142[1]) ? fSlow11 : fSlow8);
			fRec142[0] = fTemp144 * (1.0f - fTemp145) + fRec142[1] * fTemp145;
			fRec145[0] = fTemp99 - fSlow114 * (fSlow115 * fRec145[2] + fConst75 * fRec145[1]);
			float fTemp146 = std::fabs(fSlow113 * (fRec145[0] - fRec145[2]));
			float fTemp147 = ((fTemp146 > fRec144[1]) ? fSlow11 : fSlow8);
			fRec144[0] = fTemp146 * (1.0f - fTemp147) + fRec144[1] * fTemp147;
			fRec147[0] = fTemp99 - fSlow118 * (fSlow119 * fRec147[2] + fConst78 * fRec147[1]);
			float fTemp148 = std::fabs(fSlow117 * (fRec147[0] - fRec147[2]));
			float fTemp149 = ((fTemp148 > fRec146[1]) ? fSlow11 : fSlow8);
			fRec146[0] = fTemp148 * (1.0f - fTemp149) + fRec146[1] * fTemp149;
			fRec149[0] = fTemp99 - fSlow122 * (fSlow123 * fRec149[2] + fConst81 * fRec149[1]);
			float fTemp150 = std::fabs(fSlow121 * (fRec149[0] - fRec149[2]));
			float fTemp151 = ((fTemp150 > fRec148[1]) ? fSlow11 : fSlow8);
			fRec148[0] = fTemp150 * (1.0f - fTemp151) + fRec148[1] * fTemp151;
			fRec151[0] = fTemp99 - fSlow126 * (fSlow127 * fRec151[2] + fConst84 * fRec151[1]);
			float fTemp152 = std::fabs(fSlow125 * (fRec151[0] - fRec151[2]));
			float fTemp153 = ((fTemp152 > fRec150[1]) ? fSlow11 : fSlow8);
			fRec150[0] = fTemp152 * (1.0f - fTemp153) + fRec150[1] * fTemp153;
			fRec153[0] = fTemp99 - fSlow131 * (fSlow132 * fRec153[2] + fConst87 * fRec153[1]);
			float fTemp154 = std::fabs(fSlow130 * (fRec153[0] - fRec153[2]));
			float fTemp155 = ((fTemp154 > fRec152[1]) ? fSlow11 : fSlow8);
			fRec152[0] = fTemp154 * (1.0f - fTemp155) + fRec152[1] * fTemp155;
			fRec155[0] = fTemp99 - fSlow135 * (fSlow136 * fRec155[2] + fConst90 * fRec155[1]);
			float fTemp156 = std::fabs(fSlow134 * (fRec155[0] - fRec155[2]));
			float fTemp157 = ((fTemp156 > fRec154[1]) ? fSlow11 : fSlow8);
			fRec154[0] = fTemp156 * (1.0f - fTemp157) + fRec154[1] * fTemp157;
			fRec157[0] = fTemp99 - fSlow139 * (fSlow140 * fRec157[2] + fConst93 * fRec157[1]);
			float fTemp158 = std::fabs(fSlow138 * (fRec157[0] - fRec157[2]));
			float fTemp159 = ((fTemp158 > fRec156[1]) ? fSlow11 : fSlow8);
			fRec156[0] = fTemp158 * (1.0f - fTemp159) + fRec156[1] * fTemp159;
			fRec159[0] = fTemp99 - fSlow144 * (fSlow145 * fRec159[2] + fConst96 * fRec159[1]);
			float fTemp160 = std::fabs(fSlow143 * (fRec159[0] - fRec159[2]));
			float fTemp161 = ((fTemp160 > fRec158[1]) ? fSlow11 : fSlow8);
			fRec158[0] = fTemp160 * (1.0f - fTemp161) + fRec158[1] * fTemp161;
			fRec161[0] = fTemp99 - fSlow148 * (fSlow149 * fRec161[2] + fConst99 * fRec161[1]);
			float fTemp162 = std::fabs(fSlow147 * (fRec161[0] - fRec161[2]));
			float fTemp163 = ((fTemp162 > fRec160[1]) ? fSlow11 : fSlow8);
			fRec160[0] = fTemp162 * (1.0f - fTemp163) + fRec160[1] * fTemp163;
			output1[i0] = static_cast<FAUSTFLOAT>(2.0f * (fSlow3 * fRec98[0] * fTemp5 + fSlow16 * fRec100[0] * fTemp8 + fSlow20 * fRec102[0] * fTemp11 + fSlow25 * fRec104[0] * fTemp14 + fSlow30 * fRec106[0] * fTemp17 + fSlow35 * fRec108[0] * fTemp20 + fSlow40 * fRec110[0] * fTemp23 + fSlow44 * fRec112[0] * fTemp26 + fSlow48 * fRec114[0] * fTemp29 + fSlow52 * fRec116[0] * fTemp32 + fSlow57 * fRec118[0] * fTemp35 + fSlow62 * fRec120[0] * fTemp38 + fSlow66 * fRec122[0] * fTemp41 + fSlow71 * fRec124[0] * fTemp44 + fSlow75 * fRec126[0] * fTemp47 + fSlow79 * fRec128[0] * fTemp50 + fSlow83 * fRec130[0] * fTemp53 + fSlow88 * fRec132[0] * fTemp56 + fSlow92 * fRec134[0] * fTemp59 + fSlow96 * fRec136[0] * fTemp62 + fSlow100 * fRec138[0] * fTemp65 + fSlow104 * fRec140[0] * fTemp68 + fSlow108 * fRec142[0] * fTemp71 + fSlow113 * fRec144[0] * fTemp74 + fSlow117 * fRec146[0] * fTemp77 + fSlow121 * fRec148[0] * fTemp80 + fSlow125 * fRec150[0] * fTemp83 + fSlow130 * fRec152[0] * fTemp86 + fSlow134 * fRec154[0] * fTemp89 + fSlow138 * fRec156[0] * fTemp92 + fSlow143 * fRec158[0] * fTemp95 + fSlow147 * fRec160[0] * fTemp98));
			iVec0[1] = iVec0[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fRec29[1] = fRec29[0];
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			fRec32[1] = fRec32[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fRec35[1] = fRec35[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];
			fRec38[1] = fRec38[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec41[1] = fRec41[0];
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec44[1] = fRec44[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec47[1] = fRec47[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec50[1] = fRec50[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec53[1] = fRec53[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fRec56[1] = fRec56[0];
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];
			fRec59[1] = fRec59[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec63[2] = fRec63[1];
			fRec63[1] = fRec63[0];
			fRec62[1] = fRec62[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fRec65[1] = fRec65[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec68[1] = fRec68[0];
			fRec70[2] = fRec70[1];
			fRec70[1] = fRec70[0];
			fRec72[2] = fRec72[1];
			fRec72[1] = fRec72[0];
			fRec71[1] = fRec71[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			fRec75[2] = fRec75[1];
			fRec75[1] = fRec75[0];
			fRec74[1] = fRec74[0];
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
			fRec78[2] = fRec78[1];
			fRec78[1] = fRec78[0];
			fRec77[1] = fRec77[0];
			fRec79[2] = fRec79[1];
			fRec79[1] = fRec79[0];
			fRec81[2] = fRec81[1];
			fRec81[1] = fRec81[0];
			fRec80[1] = fRec80[0];
			fRec82[2] = fRec82[1];
			fRec82[1] = fRec82[0];
			fRec84[2] = fRec84[1];
			fRec84[1] = fRec84[0];
			fRec83[1] = fRec83[0];
			fRec85[2] = fRec85[1];
			fRec85[1] = fRec85[0];
			fRec87[2] = fRec87[1];
			fRec87[1] = fRec87[0];
			fRec86[1] = fRec86[0];
			fRec88[2] = fRec88[1];
			fRec88[1] = fRec88[0];
			fRec90[2] = fRec90[1];
			fRec90[1] = fRec90[0];
			fRec89[1] = fRec89[0];
			fRec91[2] = fRec91[1];
			fRec91[1] = fRec91[0];
			fRec93[2] = fRec93[1];
			fRec93[1] = fRec93[0];
			fRec92[1] = fRec92[0];
			fRec94[2] = fRec94[1];
			fRec94[1] = fRec94[0];
			fRec96[2] = fRec96[1];
			fRec96[1] = fRec96[0];
			fRec95[1] = fRec95[0];
			fRec97[2] = fRec97[1];
			fRec97[1] = fRec97[0];
			fRec99[2] = fRec99[1];
			fRec99[1] = fRec99[0];
			fRec98[1] = fRec98[0];
			fRec101[2] = fRec101[1];
			fRec101[1] = fRec101[0];
			fRec100[1] = fRec100[0];
			fRec103[2] = fRec103[1];
			fRec103[1] = fRec103[0];
			fRec102[1] = fRec102[0];
			fRec105[2] = fRec105[1];
			fRec105[1] = fRec105[0];
			fRec104[1] = fRec104[0];
			fRec107[2] = fRec107[1];
			fRec107[1] = fRec107[0];
			fRec106[1] = fRec106[0];
			fRec109[2] = fRec109[1];
			fRec109[1] = fRec109[0];
			fRec108[1] = fRec108[0];
			fRec111[2] = fRec111[1];
			fRec111[1] = fRec111[0];
			fRec110[1] = fRec110[0];
			fRec113[2] = fRec113[1];
			fRec113[1] = fRec113[0];
			fRec112[1] = fRec112[0];
			fRec115[2] = fRec115[1];
			fRec115[1] = fRec115[0];
			fRec114[1] = fRec114[0];
			fRec117[2] = fRec117[1];
			fRec117[1] = fRec117[0];
			fRec116[1] = fRec116[0];
			fRec119[2] = fRec119[1];
			fRec119[1] = fRec119[0];
			fRec118[1] = fRec118[0];
			fRec121[2] = fRec121[1];
			fRec121[1] = fRec121[0];
			fRec120[1] = fRec120[0];
			fRec123[2] = fRec123[1];
			fRec123[1] = fRec123[0];
			fRec122[1] = fRec122[0];
			fRec125[2] = fRec125[1];
			fRec125[1] = fRec125[0];
			fRec124[1] = fRec124[0];
			fRec127[2] = fRec127[1];
			fRec127[1] = fRec127[0];
			fRec126[1] = fRec126[0];
			fRec129[2] = fRec129[1];
			fRec129[1] = fRec129[0];
			fRec128[1] = fRec128[0];
			fRec131[2] = fRec131[1];
			fRec131[1] = fRec131[0];
			fRec130[1] = fRec130[0];
			fRec133[2] = fRec133[1];
			fRec133[1] = fRec133[0];
			fRec132[1] = fRec132[0];
			fRec135[2] = fRec135[1];
			fRec135[1] = fRec135[0];
			fRec134[1] = fRec134[0];
			fRec137[2] = fRec137[1];
			fRec137[1] = fRec137[0];
			fRec136[1] = fRec136[0];
			fRec139[2] = fRec139[1];
			fRec139[1] = fRec139[0];
			fRec138[1] = fRec138[0];
			fRec141[2] = fRec141[1];
			fRec141[1] = fRec141[0];
			fRec140[1] = fRec140[0];
			fRec143[2] = fRec143[1];
			fRec143[1] = fRec143[0];
			fRec142[1] = fRec142[0];
			fRec145[2] = fRec145[1];
			fRec145[1] = fRec145[0];
			fRec144[1] = fRec144[0];
			fRec147[2] = fRec147[1];
			fRec147[1] = fRec147[0];
			fRec146[1] = fRec146[0];
			fRec149[2] = fRec149[1];
			fRec149[1] = fRec149[0];
			fRec148[1] = fRec148[0];
			fRec151[2] = fRec151[1];
			fRec151[1] = fRec151[0];
			fRec150[1] = fRec150[0];
			fRec153[2] = fRec153[1];
			fRec153[1] = fRec153[0];
			fRec152[1] = fRec152[0];
			fRec155[2] = fRec155[1];
			fRec155[1] = fRec155[0];
			fRec154[1] = fRec154[0];
			fRec157[2] = fRec157[1];
			fRec157[1] = fRec157[0];
			fRec156[1] = fRec156[0];
			fRec159[2] = fRec159[1];
			fRec159[1] = fRec159[0];
			fRec158[1] = fRec158[0];
			fRec161[2] = fRec161[1];
			fRec161[1] = fRec161[0];
			fRec160[1] = fRec160[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "Vocoder1.dsp"
	#define FAUST_CLASS_NAME "_Vocoder1"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _Vocoder1 -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 5
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("My Vocoder/Excitation/Freq", fHslider3, 3.3e+02f, 5e+01f, 2e+03f, 0.1f);
	FAUST_ADDVERTICALSLIDER("My Vocoder/Excitation/Gain", fVslider0, 0.5f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("My Vocoder/Vocoder/Attack", fHslider2, 5.0f, 0.1f, 1e+02f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("My Vocoder/Vocoder/Release", fHslider1, 5.0f, 0.1f, 1e+02f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("My Vocoder/Vocoder/BW", fHslider0, 0.5f, 0.1f, 2.0f, 0.001f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Freq, "My Vocoder/Excitation/Freq", fHslider3, 3.3e+02f, 5e+01f, 2e+03f, 0.1f) \
		p(VERTICALSLIDER, Gain, "My Vocoder/Excitation/Gain", fVslider0, 0.5f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, Attack, "My Vocoder/Vocoder/Attack", fHslider2, 5.0f, 0.1f, 1e+02f, 0.1f) \
		p(HORIZONTALSLIDER, Release, "My Vocoder/Vocoder/Release", fHslider1, 5.0f, 0.1f, 1e+02f, 0.1f) \
		p(HORIZONTALSLIDER, BW, "My Vocoder/Vocoder/BW", fHslider0, 0.5f, 0.1f, 2.0f, 0.001f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

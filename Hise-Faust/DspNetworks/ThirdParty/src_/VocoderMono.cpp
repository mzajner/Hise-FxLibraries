/* ------------------------------------------------------------
name: "VocoderMono"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _VocoderMono -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___VocoderMono_H__
#define  ___VocoderMono_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _VocoderMono
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

static float _VocoderMono_faustpower2_f(float value) {
	return value * value;
}

struct _VocoderMono final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	FAUSTFLOAT fHslider0;
	float fConst4;
	float fRec3[2];
	float fConst5;
	float fRec2[3];
	float fConst6;
	FAUSTFLOAT fHslider1;
	float fRec4[2];
	float fConst7;
	float fRec1[2];
	FAUSTFLOAT fHslider2;
	float fRec5[2];
	float fRec0[2];
	FAUSTFLOAT fHslider3;
	float fRec9[2];
	float fRec7[2];
	float fRec6[3];
	float fConst8;
	float fConst9;
	float fConst10;
	float fRec12[3];
	float fRec11[2];
	float fRec10[2];
	float fRec13[3];
	float fConst11;
	float fConst12;
	float fConst13;
	float fRec16[3];
	float fRec15[2];
	float fRec14[2];
	float fRec17[3];
	float fConst14;
	float fConst15;
	float fConst16;
	float fRec20[3];
	float fRec19[2];
	float fRec18[2];
	float fRec21[3];
	float fConst17;
	float fConst18;
	float fConst19;
	float fRec24[3];
	float fRec23[2];
	float fRec22[2];
	float fRec25[3];
	float fConst20;
	float fConst21;
	float fConst22;
	float fRec28[3];
	float fRec27[2];
	float fRec26[2];
	float fRec29[3];
	float fConst23;
	float fConst24;
	float fConst25;
	float fRec32[3];
	float fRec31[2];
	float fRec30[2];
	float fRec33[3];
	float fConst26;
	float fConst27;
	float fConst28;
	float fRec36[3];
	float fRec35[2];
	float fRec34[2];
	float fRec37[3];
	float fConst29;
	float fConst30;
	float fConst31;
	float fRec40[3];
	float fRec39[2];
	float fRec38[2];
	float fRec41[3];
	float fConst32;
	float fConst33;
	float fConst34;
	float fRec44[3];
	float fRec43[2];
	float fRec42[2];
	float fRec45[3];
	float fConst35;
	float fConst36;
	float fConst37;
	float fRec48[3];
	float fRec47[2];
	float fRec46[2];
	float fRec49[3];
	float fConst38;
	float fConst39;
	float fConst40;
	float fRec52[3];
	float fRec51[2];
	float fRec50[2];
	float fRec53[3];
	float fConst41;
	float fConst42;
	float fConst43;
	float fRec56[3];
	float fRec55[2];
	float fRec54[2];
	float fRec57[3];
	float fConst44;
	float fConst45;
	float fConst46;
	float fRec60[3];
	float fRec59[2];
	float fRec58[2];
	float fRec61[3];
	float fConst47;
	float fConst48;
	float fConst49;
	float fRec64[3];
	float fRec63[2];
	float fRec62[2];
	float fRec65[3];
	float fConst50;
	float fConst51;
	float fConst52;
	float fRec68[3];
	float fRec67[2];
	float fRec66[2];
	float fRec69[3];
	float fConst53;
	float fConst54;
	float fConst55;
	float fRec72[3];
	float fRec71[2];
	float fRec70[2];
	float fRec73[3];
	float fConst56;
	float fConst57;
	float fConst58;
	float fRec76[3];
	float fRec75[2];
	float fRec74[2];
	float fRec77[3];
	float fConst59;
	float fConst60;
	float fConst61;
	float fRec80[3];
	float fRec79[2];
	float fRec78[2];
	float fRec81[3];
	float fConst62;
	float fConst63;
	float fConst64;
	float fRec84[3];
	float fRec83[2];
	float fRec82[2];
	float fRec85[3];
	float fConst65;
	float fConst66;
	float fConst67;
	float fRec88[3];
	float fRec87[2];
	float fRec86[2];
	float fRec89[3];
	float fConst68;
	float fConst69;
	float fConst70;
	float fRec92[3];
	float fRec91[2];
	float fRec90[2];
	float fRec93[3];
	float fConst71;
	float fConst72;
	float fConst73;
	float fRec96[3];
	float fRec95[2];
	float fRec94[2];
	float fRec97[3];
	float fConst74;
	float fConst75;
	float fConst76;
	float fRec100[3];
	float fRec99[2];
	float fRec98[2];
	float fRec101[3];
	float fConst77;
	float fConst78;
	float fConst79;
	float fRec104[3];
	float fRec103[2];
	float fRec102[2];
	float fRec105[3];
	float fConst80;
	float fConst81;
	float fConst82;
	float fRec108[3];
	float fRec107[2];
	float fRec106[2];
	float fRec109[3];
	float fConst83;
	float fConst84;
	float fConst85;
	float fRec112[3];
	float fRec111[2];
	float fRec110[2];
	float fRec113[3];
	float fConst86;
	float fConst87;
	float fConst88;
	float fRec116[3];
	float fRec115[2];
	float fRec114[2];
	float fRec117[3];
	float fConst89;
	float fConst90;
	float fConst91;
	float fRec120[3];
	float fRec119[2];
	float fRec118[2];
	float fRec121[3];
	float fConst92;
	float fConst93;
	float fConst94;
	float fRec124[3];
	float fRec123[2];
	float fRec122[2];
	float fRec125[3];
	float fConst95;
	float fConst96;
	float fConst97;
	float fRec128[3];
	float fRec127[2];
	float fRec126[2];
	float fRec129[3];
	float fConst98;
	float fConst99;
	float fConst100;
	float fRec132[3];
	float fRec131[2];
	float fRec130[2];
	float fRec133[3];
	float fRec136[3];
	float fRec135[2];
	float fRec134[2];
	float fRec139[3];
	float fRec138[2];
	float fRec137[2];
	float fRec142[3];
	float fRec141[2];
	float fRec140[2];
	float fRec145[3];
	float fRec144[2];
	float fRec143[2];
	float fRec148[3];
	float fRec147[2];
	float fRec146[2];
	float fRec151[3];
	float fRec150[2];
	float fRec149[2];
	float fRec154[3];
	float fRec153[2];
	float fRec152[2];
	float fRec157[3];
	float fRec156[2];
	float fRec155[2];
	float fRec160[3];
	float fRec159[2];
	float fRec158[2];
	float fRec163[3];
	float fRec162[2];
	float fRec161[2];
	float fRec166[3];
	float fRec165[2];
	float fRec164[2];
	float fRec169[3];
	float fRec168[2];
	float fRec167[2];
	float fRec172[3];
	float fRec171[2];
	float fRec170[2];
	float fRec175[3];
	float fRec174[2];
	float fRec173[2];
	float fRec178[3];
	float fRec177[2];
	float fRec176[2];
	float fRec181[3];
	float fRec180[2];
	float fRec179[2];
	float fRec184[3];
	float fRec183[2];
	float fRec182[2];
	float fRec187[3];
	float fRec186[2];
	float fRec185[2];
	float fRec190[3];
	float fRec189[2];
	float fRec188[2];
	float fRec193[3];
	float fRec192[2];
	float fRec191[2];
	float fRec196[3];
	float fRec195[2];
	float fRec194[2];
	float fRec199[3];
	float fRec198[2];
	float fRec197[2];
	float fRec202[3];
	float fRec201[2];
	float fRec200[2];
	float fRec205[3];
	float fRec204[2];
	float fRec203[2];
	float fRec208[3];
	float fRec207[2];
	float fRec206[2];
	float fRec211[3];
	float fRec210[2];
	float fRec209[2];
	float fRec214[3];
	float fRec213[2];
	float fRec212[2];
	float fRec217[3];
	float fRec216[2];
	float fRec215[2];
	float fRec220[3];
	float fRec219[2];
	float fRec218[2];
	float fRec223[3];
	float fRec222[2];
	float fRec221[2];
	float fRec226[3];
	float fRec225[2];
	float fRec224[2];
	float fRec229[3];
	float fRec228[2];
	float fRec227[2];
	
	_VocoderMono() {
	}
	
	_VocoderMono(const _VocoderMono&) = default;
	
	virtual ~_VocoderMono() = default;
	
	_VocoderMono& operator=(const _VocoderMono&) = default;
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.3.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _VocoderMono -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "VocoderMono.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
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
		m->declare("name", "VocoderMono");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/saw2ptr:author", "Julius O. Smith III");
		m->declare("oscillators.lib/saw2ptr:license", "STK-4.3");
		m->declare("oscillators.lib/version", "1.6.0");
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
		fConst1 = std::tan(95.445305f / fConst0);
		fConst2 = 1.0f / fConst1;
		fConst3 = 44.1f / fConst0;
		fConst4 = 1.0f - fConst3;
		fConst5 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst1));
		fConst6 = 0.0441f / fConst0;
		fConst7 = 1.0f / fConst0;
		fConst8 = std::tan(115.989655f / fConst0);
		fConst9 = 1.0f / fConst8;
		fConst10 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst8));
		fConst11 = std::tan(140.95612f / fConst0);
		fConst12 = 1.0f / fConst11;
		fConst13 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst11));
		fConst14 = std::tan(171.29655f / fConst0);
		fConst15 = 1.0f / fConst14;
		fConst16 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst14));
		fConst17 = std::tan(208.16768f / fConst0);
		fConst18 = 1.0f / fConst17;
		fConst19 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst17));
		fConst20 = std::tan(252.97523f / fConst0);
		fConst21 = 1.0f / fConst20;
		fConst22 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst20));
		fConst23 = std::tan(307.4275f / fConst0);
		fConst24 = 1.0f / fConst23;
		fConst25 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst23));
		fConst26 = std::tan(373.60043f / fConst0);
		fConst27 = 1.0f / fConst26;
		fConst28 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst26));
		fConst29 = std::tan(454.01694f / fConst0);
		fConst30 = 1.0f / fConst29;
		fConst31 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst29));
		fConst32 = std::tan(551.74286f / fConst0);
		fConst33 = 1.0f / fConst32;
		fConst34 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst32));
		fConst35 = std::tan(670.5041f / fConst0);
		fConst36 = 1.0f / fConst35;
		fConst37 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst35));
		fConst38 = std::tan(814.8283f / fConst0);
		fConst39 = 1.0f / fConst38;
		fConst40 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst38));
		fConst41 = std::tan(990.21796f / fConst0);
		fConst42 = 1.0f / fConst41;
		fConst43 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst41));
		fConst44 = std::tan(1203.3597f / fConst0);
		fConst45 = 1.0f / fConst44;
		fConst46 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst44));
		fConst47 = std::tan(1462.3798f / fConst0);
		fConst48 = 1.0f / fConst47;
		fConst49 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst47));
		fConst50 = std::tan(1777.1532f / fConst0);
		fConst51 = 1.0f / fConst50;
		fConst52 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst50));
		fConst53 = std::tan(2159.6807f / fConst0);
		fConst54 = 1.0f / fConst53;
		fConst55 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst53));
		fConst56 = std::tan(2624.5464f / fConst0);
		fConst57 = 1.0f / fConst56;
		fConst58 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst56));
		fConst59 = std::tan(3189.473f / fConst0);
		fConst60 = 1.0f / fConst59;
		fConst61 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst59));
		fConst62 = std::tan(3875.9985f / fConst0);
		fConst63 = 1.0f / fConst62;
		fConst64 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst62));
		fConst65 = std::tan(4710.297f / fConst0);
		fConst66 = 1.0f / fConst65;
		fConst67 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst65));
		fConst68 = std::tan(5724.176f / fConst0);
		fConst69 = 1.0f / fConst68;
		fConst70 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst68));
		fConst71 = std::tan(6956.2896f / fConst0);
		fConst72 = 1.0f / fConst71;
		fConst73 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst71));
		fConst74 = std::tan(8453.613f / fConst0);
		fConst75 = 1.0f / fConst74;
		fConst76 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst74));
		fConst77 = std::tan(10273.23f / fConst0);
		fConst78 = 1.0f / fConst77;
		fConst79 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst77));
		fConst80 = std::tan(12484.517f / fConst0);
		fConst81 = 1.0f / fConst80;
		fConst82 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst80));
		fConst83 = std::tan(15171.775f / fConst0);
		fConst84 = 1.0f / fConst83;
		fConst85 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst83));
		fConst86 = std::tan(18437.46f / fConst0);
		fConst87 = 1.0f / fConst86;
		fConst88 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst86));
		fConst89 = std::tan(22406.074f / fConst0);
		fConst90 = 1.0f / fConst89;
		fConst91 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst89));
		fConst92 = std::tan(27228.924f / fConst0);
		fConst93 = 1.0f / fConst92;
		fConst94 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst92));
		fConst95 = std::tan(33089.88f / fConst0);
		fConst96 = 1.0f / fConst95;
		fConst97 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst95));
		fConst98 = std::tan(40212.387f / fConst0);
		fConst99 = 1.0f / fConst98;
		fConst100 = 2.0f * (1.0f - 1.0f / _VocoderMono_faustpower2_f(fConst98));
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(15.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(0.1f);
		fHslider3 = static_cast<FAUSTFLOAT>(1.5e+02f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec3[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 3; l1 = l1 + 1) {
			fRec2[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec4[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec1[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec0[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec9[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec7[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 3; l8 = l8 + 1) {
			fRec6[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec12[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec11[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec10[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 3; l12 = l12 + 1) {
			fRec13[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 3; l13 = l13 + 1) {
			fRec16[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec15[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec14[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 3; l16 = l16 + 1) {
			fRec17[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 3; l17 = l17 + 1) {
			fRec20[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec19[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec18[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 3; l20 = l20 + 1) {
			fRec21[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 3; l21 = l21 + 1) {
			fRec24[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fRec23[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec22[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 3; l24 = l24 + 1) {
			fRec25[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 3; l25 = l25 + 1) {
			fRec28[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			fRec27[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec26[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 3; l28 = l28 + 1) {
			fRec29[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 3; l29 = l29 + 1) {
			fRec32[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			fRec31[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec30[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 3; l32 = l32 + 1) {
			fRec33[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 3; l33 = l33 + 1) {
			fRec36[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			fRec35[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			fRec34[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 3; l36 = l36 + 1) {
			fRec37[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 3; l37 = l37 + 1) {
			fRec40[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 2; l38 = l38 + 1) {
			fRec39[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 2; l39 = l39 + 1) {
			fRec38[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 3; l40 = l40 + 1) {
			fRec41[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 3; l41 = l41 + 1) {
			fRec44[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 2; l42 = l42 + 1) {
			fRec43[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec42[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 3; l44 = l44 + 1) {
			fRec45[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 3; l45 = l45 + 1) {
			fRec48[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 2; l46 = l46 + 1) {
			fRec47[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 2; l47 = l47 + 1) {
			fRec46[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 3; l48 = l48 + 1) {
			fRec49[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 3; l49 = l49 + 1) {
			fRec52[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 2; l50 = l50 + 1) {
			fRec51[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 2; l51 = l51 + 1) {
			fRec50[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 3; l52 = l52 + 1) {
			fRec53[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 3; l53 = l53 + 1) {
			fRec56[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 2; l54 = l54 + 1) {
			fRec55[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 2; l55 = l55 + 1) {
			fRec54[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 3; l56 = l56 + 1) {
			fRec57[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 3; l57 = l57 + 1) {
			fRec60[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 2; l58 = l58 + 1) {
			fRec59[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 2; l59 = l59 + 1) {
			fRec58[l59] = 0.0f;
		}
		for (int l60 = 0; l60 < 3; l60 = l60 + 1) {
			fRec61[l60] = 0.0f;
		}
		for (int l61 = 0; l61 < 3; l61 = l61 + 1) {
			fRec64[l61] = 0.0f;
		}
		for (int l62 = 0; l62 < 2; l62 = l62 + 1) {
			fRec63[l62] = 0.0f;
		}
		for (int l63 = 0; l63 < 2; l63 = l63 + 1) {
			fRec62[l63] = 0.0f;
		}
		for (int l64 = 0; l64 < 3; l64 = l64 + 1) {
			fRec65[l64] = 0.0f;
		}
		for (int l65 = 0; l65 < 3; l65 = l65 + 1) {
			fRec68[l65] = 0.0f;
		}
		for (int l66 = 0; l66 < 2; l66 = l66 + 1) {
			fRec67[l66] = 0.0f;
		}
		for (int l67 = 0; l67 < 2; l67 = l67 + 1) {
			fRec66[l67] = 0.0f;
		}
		for (int l68 = 0; l68 < 3; l68 = l68 + 1) {
			fRec69[l68] = 0.0f;
		}
		for (int l69 = 0; l69 < 3; l69 = l69 + 1) {
			fRec72[l69] = 0.0f;
		}
		for (int l70 = 0; l70 < 2; l70 = l70 + 1) {
			fRec71[l70] = 0.0f;
		}
		for (int l71 = 0; l71 < 2; l71 = l71 + 1) {
			fRec70[l71] = 0.0f;
		}
		for (int l72 = 0; l72 < 3; l72 = l72 + 1) {
			fRec73[l72] = 0.0f;
		}
		for (int l73 = 0; l73 < 3; l73 = l73 + 1) {
			fRec76[l73] = 0.0f;
		}
		for (int l74 = 0; l74 < 2; l74 = l74 + 1) {
			fRec75[l74] = 0.0f;
		}
		for (int l75 = 0; l75 < 2; l75 = l75 + 1) {
			fRec74[l75] = 0.0f;
		}
		for (int l76 = 0; l76 < 3; l76 = l76 + 1) {
			fRec77[l76] = 0.0f;
		}
		for (int l77 = 0; l77 < 3; l77 = l77 + 1) {
			fRec80[l77] = 0.0f;
		}
		for (int l78 = 0; l78 < 2; l78 = l78 + 1) {
			fRec79[l78] = 0.0f;
		}
		for (int l79 = 0; l79 < 2; l79 = l79 + 1) {
			fRec78[l79] = 0.0f;
		}
		for (int l80 = 0; l80 < 3; l80 = l80 + 1) {
			fRec81[l80] = 0.0f;
		}
		for (int l81 = 0; l81 < 3; l81 = l81 + 1) {
			fRec84[l81] = 0.0f;
		}
		for (int l82 = 0; l82 < 2; l82 = l82 + 1) {
			fRec83[l82] = 0.0f;
		}
		for (int l83 = 0; l83 < 2; l83 = l83 + 1) {
			fRec82[l83] = 0.0f;
		}
		for (int l84 = 0; l84 < 3; l84 = l84 + 1) {
			fRec85[l84] = 0.0f;
		}
		for (int l85 = 0; l85 < 3; l85 = l85 + 1) {
			fRec88[l85] = 0.0f;
		}
		for (int l86 = 0; l86 < 2; l86 = l86 + 1) {
			fRec87[l86] = 0.0f;
		}
		for (int l87 = 0; l87 < 2; l87 = l87 + 1) {
			fRec86[l87] = 0.0f;
		}
		for (int l88 = 0; l88 < 3; l88 = l88 + 1) {
			fRec89[l88] = 0.0f;
		}
		for (int l89 = 0; l89 < 3; l89 = l89 + 1) {
			fRec92[l89] = 0.0f;
		}
		for (int l90 = 0; l90 < 2; l90 = l90 + 1) {
			fRec91[l90] = 0.0f;
		}
		for (int l91 = 0; l91 < 2; l91 = l91 + 1) {
			fRec90[l91] = 0.0f;
		}
		for (int l92 = 0; l92 < 3; l92 = l92 + 1) {
			fRec93[l92] = 0.0f;
		}
		for (int l93 = 0; l93 < 3; l93 = l93 + 1) {
			fRec96[l93] = 0.0f;
		}
		for (int l94 = 0; l94 < 2; l94 = l94 + 1) {
			fRec95[l94] = 0.0f;
		}
		for (int l95 = 0; l95 < 2; l95 = l95 + 1) {
			fRec94[l95] = 0.0f;
		}
		for (int l96 = 0; l96 < 3; l96 = l96 + 1) {
			fRec97[l96] = 0.0f;
		}
		for (int l97 = 0; l97 < 3; l97 = l97 + 1) {
			fRec100[l97] = 0.0f;
		}
		for (int l98 = 0; l98 < 2; l98 = l98 + 1) {
			fRec99[l98] = 0.0f;
		}
		for (int l99 = 0; l99 < 2; l99 = l99 + 1) {
			fRec98[l99] = 0.0f;
		}
		for (int l100 = 0; l100 < 3; l100 = l100 + 1) {
			fRec101[l100] = 0.0f;
		}
		for (int l101 = 0; l101 < 3; l101 = l101 + 1) {
			fRec104[l101] = 0.0f;
		}
		for (int l102 = 0; l102 < 2; l102 = l102 + 1) {
			fRec103[l102] = 0.0f;
		}
		for (int l103 = 0; l103 < 2; l103 = l103 + 1) {
			fRec102[l103] = 0.0f;
		}
		for (int l104 = 0; l104 < 3; l104 = l104 + 1) {
			fRec105[l104] = 0.0f;
		}
		for (int l105 = 0; l105 < 3; l105 = l105 + 1) {
			fRec108[l105] = 0.0f;
		}
		for (int l106 = 0; l106 < 2; l106 = l106 + 1) {
			fRec107[l106] = 0.0f;
		}
		for (int l107 = 0; l107 < 2; l107 = l107 + 1) {
			fRec106[l107] = 0.0f;
		}
		for (int l108 = 0; l108 < 3; l108 = l108 + 1) {
			fRec109[l108] = 0.0f;
		}
		for (int l109 = 0; l109 < 3; l109 = l109 + 1) {
			fRec112[l109] = 0.0f;
		}
		for (int l110 = 0; l110 < 2; l110 = l110 + 1) {
			fRec111[l110] = 0.0f;
		}
		for (int l111 = 0; l111 < 2; l111 = l111 + 1) {
			fRec110[l111] = 0.0f;
		}
		for (int l112 = 0; l112 < 3; l112 = l112 + 1) {
			fRec113[l112] = 0.0f;
		}
		for (int l113 = 0; l113 < 3; l113 = l113 + 1) {
			fRec116[l113] = 0.0f;
		}
		for (int l114 = 0; l114 < 2; l114 = l114 + 1) {
			fRec115[l114] = 0.0f;
		}
		for (int l115 = 0; l115 < 2; l115 = l115 + 1) {
			fRec114[l115] = 0.0f;
		}
		for (int l116 = 0; l116 < 3; l116 = l116 + 1) {
			fRec117[l116] = 0.0f;
		}
		for (int l117 = 0; l117 < 3; l117 = l117 + 1) {
			fRec120[l117] = 0.0f;
		}
		for (int l118 = 0; l118 < 2; l118 = l118 + 1) {
			fRec119[l118] = 0.0f;
		}
		for (int l119 = 0; l119 < 2; l119 = l119 + 1) {
			fRec118[l119] = 0.0f;
		}
		for (int l120 = 0; l120 < 3; l120 = l120 + 1) {
			fRec121[l120] = 0.0f;
		}
		for (int l121 = 0; l121 < 3; l121 = l121 + 1) {
			fRec124[l121] = 0.0f;
		}
		for (int l122 = 0; l122 < 2; l122 = l122 + 1) {
			fRec123[l122] = 0.0f;
		}
		for (int l123 = 0; l123 < 2; l123 = l123 + 1) {
			fRec122[l123] = 0.0f;
		}
		for (int l124 = 0; l124 < 3; l124 = l124 + 1) {
			fRec125[l124] = 0.0f;
		}
		for (int l125 = 0; l125 < 3; l125 = l125 + 1) {
			fRec128[l125] = 0.0f;
		}
		for (int l126 = 0; l126 < 2; l126 = l126 + 1) {
			fRec127[l126] = 0.0f;
		}
		for (int l127 = 0; l127 < 2; l127 = l127 + 1) {
			fRec126[l127] = 0.0f;
		}
		for (int l128 = 0; l128 < 3; l128 = l128 + 1) {
			fRec129[l128] = 0.0f;
		}
		for (int l129 = 0; l129 < 3; l129 = l129 + 1) {
			fRec132[l129] = 0.0f;
		}
		for (int l130 = 0; l130 < 2; l130 = l130 + 1) {
			fRec131[l130] = 0.0f;
		}
		for (int l131 = 0; l131 < 2; l131 = l131 + 1) {
			fRec130[l131] = 0.0f;
		}
		for (int l132 = 0; l132 < 3; l132 = l132 + 1) {
			fRec133[l132] = 0.0f;
		}
		for (int l133 = 0; l133 < 3; l133 = l133 + 1) {
			fRec136[l133] = 0.0f;
		}
		for (int l134 = 0; l134 < 2; l134 = l134 + 1) {
			fRec135[l134] = 0.0f;
		}
		for (int l135 = 0; l135 < 2; l135 = l135 + 1) {
			fRec134[l135] = 0.0f;
		}
		for (int l136 = 0; l136 < 3; l136 = l136 + 1) {
			fRec139[l136] = 0.0f;
		}
		for (int l137 = 0; l137 < 2; l137 = l137 + 1) {
			fRec138[l137] = 0.0f;
		}
		for (int l138 = 0; l138 < 2; l138 = l138 + 1) {
			fRec137[l138] = 0.0f;
		}
		for (int l139 = 0; l139 < 3; l139 = l139 + 1) {
			fRec142[l139] = 0.0f;
		}
		for (int l140 = 0; l140 < 2; l140 = l140 + 1) {
			fRec141[l140] = 0.0f;
		}
		for (int l141 = 0; l141 < 2; l141 = l141 + 1) {
			fRec140[l141] = 0.0f;
		}
		for (int l142 = 0; l142 < 3; l142 = l142 + 1) {
			fRec145[l142] = 0.0f;
		}
		for (int l143 = 0; l143 < 2; l143 = l143 + 1) {
			fRec144[l143] = 0.0f;
		}
		for (int l144 = 0; l144 < 2; l144 = l144 + 1) {
			fRec143[l144] = 0.0f;
		}
		for (int l145 = 0; l145 < 3; l145 = l145 + 1) {
			fRec148[l145] = 0.0f;
		}
		for (int l146 = 0; l146 < 2; l146 = l146 + 1) {
			fRec147[l146] = 0.0f;
		}
		for (int l147 = 0; l147 < 2; l147 = l147 + 1) {
			fRec146[l147] = 0.0f;
		}
		for (int l148 = 0; l148 < 3; l148 = l148 + 1) {
			fRec151[l148] = 0.0f;
		}
		for (int l149 = 0; l149 < 2; l149 = l149 + 1) {
			fRec150[l149] = 0.0f;
		}
		for (int l150 = 0; l150 < 2; l150 = l150 + 1) {
			fRec149[l150] = 0.0f;
		}
		for (int l151 = 0; l151 < 3; l151 = l151 + 1) {
			fRec154[l151] = 0.0f;
		}
		for (int l152 = 0; l152 < 2; l152 = l152 + 1) {
			fRec153[l152] = 0.0f;
		}
		for (int l153 = 0; l153 < 2; l153 = l153 + 1) {
			fRec152[l153] = 0.0f;
		}
		for (int l154 = 0; l154 < 3; l154 = l154 + 1) {
			fRec157[l154] = 0.0f;
		}
		for (int l155 = 0; l155 < 2; l155 = l155 + 1) {
			fRec156[l155] = 0.0f;
		}
		for (int l156 = 0; l156 < 2; l156 = l156 + 1) {
			fRec155[l156] = 0.0f;
		}
		for (int l157 = 0; l157 < 3; l157 = l157 + 1) {
			fRec160[l157] = 0.0f;
		}
		for (int l158 = 0; l158 < 2; l158 = l158 + 1) {
			fRec159[l158] = 0.0f;
		}
		for (int l159 = 0; l159 < 2; l159 = l159 + 1) {
			fRec158[l159] = 0.0f;
		}
		for (int l160 = 0; l160 < 3; l160 = l160 + 1) {
			fRec163[l160] = 0.0f;
		}
		for (int l161 = 0; l161 < 2; l161 = l161 + 1) {
			fRec162[l161] = 0.0f;
		}
		for (int l162 = 0; l162 < 2; l162 = l162 + 1) {
			fRec161[l162] = 0.0f;
		}
		for (int l163 = 0; l163 < 3; l163 = l163 + 1) {
			fRec166[l163] = 0.0f;
		}
		for (int l164 = 0; l164 < 2; l164 = l164 + 1) {
			fRec165[l164] = 0.0f;
		}
		for (int l165 = 0; l165 < 2; l165 = l165 + 1) {
			fRec164[l165] = 0.0f;
		}
		for (int l166 = 0; l166 < 3; l166 = l166 + 1) {
			fRec169[l166] = 0.0f;
		}
		for (int l167 = 0; l167 < 2; l167 = l167 + 1) {
			fRec168[l167] = 0.0f;
		}
		for (int l168 = 0; l168 < 2; l168 = l168 + 1) {
			fRec167[l168] = 0.0f;
		}
		for (int l169 = 0; l169 < 3; l169 = l169 + 1) {
			fRec172[l169] = 0.0f;
		}
		for (int l170 = 0; l170 < 2; l170 = l170 + 1) {
			fRec171[l170] = 0.0f;
		}
		for (int l171 = 0; l171 < 2; l171 = l171 + 1) {
			fRec170[l171] = 0.0f;
		}
		for (int l172 = 0; l172 < 3; l172 = l172 + 1) {
			fRec175[l172] = 0.0f;
		}
		for (int l173 = 0; l173 < 2; l173 = l173 + 1) {
			fRec174[l173] = 0.0f;
		}
		for (int l174 = 0; l174 < 2; l174 = l174 + 1) {
			fRec173[l174] = 0.0f;
		}
		for (int l175 = 0; l175 < 3; l175 = l175 + 1) {
			fRec178[l175] = 0.0f;
		}
		for (int l176 = 0; l176 < 2; l176 = l176 + 1) {
			fRec177[l176] = 0.0f;
		}
		for (int l177 = 0; l177 < 2; l177 = l177 + 1) {
			fRec176[l177] = 0.0f;
		}
		for (int l178 = 0; l178 < 3; l178 = l178 + 1) {
			fRec181[l178] = 0.0f;
		}
		for (int l179 = 0; l179 < 2; l179 = l179 + 1) {
			fRec180[l179] = 0.0f;
		}
		for (int l180 = 0; l180 < 2; l180 = l180 + 1) {
			fRec179[l180] = 0.0f;
		}
		for (int l181 = 0; l181 < 3; l181 = l181 + 1) {
			fRec184[l181] = 0.0f;
		}
		for (int l182 = 0; l182 < 2; l182 = l182 + 1) {
			fRec183[l182] = 0.0f;
		}
		for (int l183 = 0; l183 < 2; l183 = l183 + 1) {
			fRec182[l183] = 0.0f;
		}
		for (int l184 = 0; l184 < 3; l184 = l184 + 1) {
			fRec187[l184] = 0.0f;
		}
		for (int l185 = 0; l185 < 2; l185 = l185 + 1) {
			fRec186[l185] = 0.0f;
		}
		for (int l186 = 0; l186 < 2; l186 = l186 + 1) {
			fRec185[l186] = 0.0f;
		}
		for (int l187 = 0; l187 < 3; l187 = l187 + 1) {
			fRec190[l187] = 0.0f;
		}
		for (int l188 = 0; l188 < 2; l188 = l188 + 1) {
			fRec189[l188] = 0.0f;
		}
		for (int l189 = 0; l189 < 2; l189 = l189 + 1) {
			fRec188[l189] = 0.0f;
		}
		for (int l190 = 0; l190 < 3; l190 = l190 + 1) {
			fRec193[l190] = 0.0f;
		}
		for (int l191 = 0; l191 < 2; l191 = l191 + 1) {
			fRec192[l191] = 0.0f;
		}
		for (int l192 = 0; l192 < 2; l192 = l192 + 1) {
			fRec191[l192] = 0.0f;
		}
		for (int l193 = 0; l193 < 3; l193 = l193 + 1) {
			fRec196[l193] = 0.0f;
		}
		for (int l194 = 0; l194 < 2; l194 = l194 + 1) {
			fRec195[l194] = 0.0f;
		}
		for (int l195 = 0; l195 < 2; l195 = l195 + 1) {
			fRec194[l195] = 0.0f;
		}
		for (int l196 = 0; l196 < 3; l196 = l196 + 1) {
			fRec199[l196] = 0.0f;
		}
		for (int l197 = 0; l197 < 2; l197 = l197 + 1) {
			fRec198[l197] = 0.0f;
		}
		for (int l198 = 0; l198 < 2; l198 = l198 + 1) {
			fRec197[l198] = 0.0f;
		}
		for (int l199 = 0; l199 < 3; l199 = l199 + 1) {
			fRec202[l199] = 0.0f;
		}
		for (int l200 = 0; l200 < 2; l200 = l200 + 1) {
			fRec201[l200] = 0.0f;
		}
		for (int l201 = 0; l201 < 2; l201 = l201 + 1) {
			fRec200[l201] = 0.0f;
		}
		for (int l202 = 0; l202 < 3; l202 = l202 + 1) {
			fRec205[l202] = 0.0f;
		}
		for (int l203 = 0; l203 < 2; l203 = l203 + 1) {
			fRec204[l203] = 0.0f;
		}
		for (int l204 = 0; l204 < 2; l204 = l204 + 1) {
			fRec203[l204] = 0.0f;
		}
		for (int l205 = 0; l205 < 3; l205 = l205 + 1) {
			fRec208[l205] = 0.0f;
		}
		for (int l206 = 0; l206 < 2; l206 = l206 + 1) {
			fRec207[l206] = 0.0f;
		}
		for (int l207 = 0; l207 < 2; l207 = l207 + 1) {
			fRec206[l207] = 0.0f;
		}
		for (int l208 = 0; l208 < 3; l208 = l208 + 1) {
			fRec211[l208] = 0.0f;
		}
		for (int l209 = 0; l209 < 2; l209 = l209 + 1) {
			fRec210[l209] = 0.0f;
		}
		for (int l210 = 0; l210 < 2; l210 = l210 + 1) {
			fRec209[l210] = 0.0f;
		}
		for (int l211 = 0; l211 < 3; l211 = l211 + 1) {
			fRec214[l211] = 0.0f;
		}
		for (int l212 = 0; l212 < 2; l212 = l212 + 1) {
			fRec213[l212] = 0.0f;
		}
		for (int l213 = 0; l213 < 2; l213 = l213 + 1) {
			fRec212[l213] = 0.0f;
		}
		for (int l214 = 0; l214 < 3; l214 = l214 + 1) {
			fRec217[l214] = 0.0f;
		}
		for (int l215 = 0; l215 < 2; l215 = l215 + 1) {
			fRec216[l215] = 0.0f;
		}
		for (int l216 = 0; l216 < 2; l216 = l216 + 1) {
			fRec215[l216] = 0.0f;
		}
		for (int l217 = 0; l217 < 3; l217 = l217 + 1) {
			fRec220[l217] = 0.0f;
		}
		for (int l218 = 0; l218 < 2; l218 = l218 + 1) {
			fRec219[l218] = 0.0f;
		}
		for (int l219 = 0; l219 < 2; l219 = l219 + 1) {
			fRec218[l219] = 0.0f;
		}
		for (int l220 = 0; l220 < 3; l220 = l220 + 1) {
			fRec223[l220] = 0.0f;
		}
		for (int l221 = 0; l221 < 2; l221 = l221 + 1) {
			fRec222[l221] = 0.0f;
		}
		for (int l222 = 0; l222 < 2; l222 = l222 + 1) {
			fRec221[l222] = 0.0f;
		}
		for (int l223 = 0; l223 < 3; l223 = l223 + 1) {
			fRec226[l223] = 0.0f;
		}
		for (int l224 = 0; l224 < 2; l224 = l224 + 1) {
			fRec225[l224] = 0.0f;
		}
		for (int l225 = 0; l225 < 2; l225 = l225 + 1) {
			fRec224[l225] = 0.0f;
		}
		for (int l226 = 0; l226 < 3; l226 = l226 + 1) {
			fRec229[l226] = 0.0f;
		}
		for (int l227 = 0; l227 < 2; l227 = l227 + 1) {
			fRec228[l227] = 0.0f;
		}
		for (int l228 = 0; l228 < 2; l228 = l228 + 1) {
			fRec227[l228] = 0.0f;
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
	
	_VocoderMono* clone() {
		return new _VocoderMono(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("VocoderMono");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("Vocoder");
		ui_interface->declare(&fHslider2, "0", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->declare(&fHslider2, "unit", "ms");
		ui_interface->addHorizontalSlider("Attack Duration", &fHslider2, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("Release Duration", &fHslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->addHorizontalSlider("Q", &fHslider0, FAUSTFLOAT(15.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(3e+01f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Sawtooth");
		ui_interface->declare(&fHslider3, "unit", "Hz");
		ui_interface->addHorizontalSlider("Excitation Frequency", &fHslider3, FAUSTFLOAT(1.5e+02f), FAUSTFLOAT(7e+01f), FAUSTFLOAT(1.5e+04f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst3 * std::max<float>(1.0f, std::min<float>(3e+01f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst6 * std::max<float>(0.01f, std::min<float>(1e+02f, static_cast<float>(fHslider1)));
		float fSlow2 = fConst6 * std::max<float>(0.01f, std::min<float>(1e+02f, static_cast<float>(fHslider2)));
		float fSlow3 = fConst3 * std::max<float>(7e+01f, std::min<float>(1.5e+04f, static_cast<float>(fHslider3)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			fRec3[0] = fSlow0 + fConst4 * fRec3[1];
			float fTemp1 = 1.0f / fRec3[0];
			float fTemp2 = fConst2 * (fConst2 - fTemp1) + 1.0f;
			float fTemp3 = fConst2 * (fConst2 + fTemp1) + 1.0f;
			fRec2[0] = fTemp0 - (fTemp2 * fRec2[2] + fConst5 * fRec2[1]) / fTemp3;
			float fTemp4 = std::fabs(fConst2 * ((fRec2[0] - fRec2[2]) / fTemp3));
			fRec4[0] = fSlow1 + fConst4 * fRec4[1];
			int iTemp5 = std::fabs(fRec4[0]) < 1.1920929e-07f;
			float fTemp6 = ((iTemp5) ? 0.0f : std::exp(-(fConst7 / ((iTemp5) ? 1.0f : fRec4[0]))));
			float fTemp7 = 1.0f - fTemp6;
			fRec1[0] = std::max<float>(fTemp4, fRec1[1] * fTemp6 + fTemp4 * fTemp7);
			fRec5[0] = fSlow2 + fConst4 * fRec5[1];
			int iTemp8 = std::fabs(fRec5[0]) < 1.1920929e-07f;
			float fTemp9 = ((iTemp8) ? 0.0f : std::exp(-(fConst7 / ((iTemp8) ? 1.0f : fRec5[0]))));
			float fTemp10 = 1.0f - fTemp9;
			fRec0[0] = fRec1[0] * fTemp10 + fTemp9 * fRec0[1];
			fRec9[0] = fSlow3 + fConst4 * fRec9[1];
			float fTemp11 = std::max<float>(1.1920929e-07f, std::fabs(fRec9[0]));
			float fTemp12 = fRec7[1] + fConst7 * fTemp11;
			float fTemp13 = fTemp12 + -1.0f;
			int iTemp14 = fTemp13 < 0.0f;
			fRec7[0] = ((iTemp14) ? fTemp12 : fTemp13);
			float fRec8 = ((iTemp14) ? fTemp12 : fTemp12 + (1.0f - fConst0 / fTemp11) * fTemp13);
			float fTemp15 = 2.0f * fRec8;
			fRec6[0] = fTemp15 + (-1.0f - (fRec6[2] * fTemp2 + fConst5 * fRec6[1]) / fTemp3);
			float fTemp16 = fRec6[0] - fRec6[2];
			float fTemp17 = fConst9 * (fConst9 - fTemp1) + 1.0f;
			float fTemp18 = fConst9 * (fConst9 + fTemp1) + 1.0f;
			fRec12[0] = fTemp0 - (fTemp17 * fRec12[2] + fConst10 * fRec12[1]) / fTemp18;
			float fTemp19 = std::fabs(fConst9 * ((fRec12[0] - fRec12[2]) / fTemp18));
			fRec11[0] = std::max<float>(fTemp19, fTemp6 * fRec11[1] + fTemp7 * fTemp19);
			fRec10[0] = fRec11[0] * fTemp10 + fTemp9 * fRec10[1];
			fRec13[0] = fTemp15 + (-1.0f - (fRec13[2] * fTemp17 + fConst10 * fRec13[1]) / fTemp18);
			float fTemp20 = fRec13[0] - fRec13[2];
			float fTemp21 = fConst12 * (fConst12 - fTemp1) + 1.0f;
			float fTemp22 = fConst12 * (fConst12 + fTemp1) + 1.0f;
			fRec16[0] = fTemp0 - (fTemp21 * fRec16[2] + fConst13 * fRec16[1]) / fTemp22;
			float fTemp23 = std::fabs(fConst12 * ((fRec16[0] - fRec16[2]) / fTemp22));
			fRec15[0] = std::max<float>(fTemp23, fTemp6 * fRec15[1] + fTemp7 * fTemp23);
			fRec14[0] = fRec15[0] * fTemp10 + fTemp9 * fRec14[1];
			fRec17[0] = fTemp15 + (-1.0f - (fRec17[2] * fTemp21 + fConst13 * fRec17[1]) / fTemp22);
			float fTemp24 = fRec17[0] - fRec17[2];
			float fTemp25 = fConst15 * (fConst15 - fTemp1) + 1.0f;
			float fTemp26 = fConst15 * (fConst15 + fTemp1) + 1.0f;
			fRec20[0] = fTemp0 - (fTemp25 * fRec20[2] + fConst16 * fRec20[1]) / fTemp26;
			float fTemp27 = std::fabs(fConst15 * ((fRec20[0] - fRec20[2]) / fTemp26));
			fRec19[0] = std::max<float>(fTemp27, fTemp6 * fRec19[1] + fTemp7 * fTemp27);
			fRec18[0] = fRec19[0] * fTemp10 + fTemp9 * fRec18[1];
			fRec21[0] = fTemp15 + (-1.0f - (fRec21[2] * fTemp25 + fConst16 * fRec21[1]) / fTemp26);
			float fTemp28 = fRec21[0] - fRec21[2];
			float fTemp29 = fConst18 * (fConst18 - fTemp1) + 1.0f;
			float fTemp30 = fConst18 * (fConst18 + fTemp1) + 1.0f;
			fRec24[0] = fTemp0 - (fTemp29 * fRec24[2] + fConst19 * fRec24[1]) / fTemp30;
			float fTemp31 = std::fabs(fConst18 * ((fRec24[0] - fRec24[2]) / fTemp30));
			fRec23[0] = std::max<float>(fTemp31, fTemp6 * fRec23[1] + fTemp7 * fTemp31);
			fRec22[0] = fRec23[0] * fTemp10 + fTemp9 * fRec22[1];
			fRec25[0] = fTemp15 + (-1.0f - (fRec25[2] * fTemp29 + fConst19 * fRec25[1]) / fTemp30);
			float fTemp32 = fRec25[0] - fRec25[2];
			float fTemp33 = fConst21 * (fConst21 - fTemp1) + 1.0f;
			float fTemp34 = fConst21 * (fConst21 + fTemp1) + 1.0f;
			fRec28[0] = fTemp0 - (fTemp33 * fRec28[2] + fConst22 * fRec28[1]) / fTemp34;
			float fTemp35 = std::fabs(fConst21 * ((fRec28[0] - fRec28[2]) / fTemp34));
			fRec27[0] = std::max<float>(fTemp35, fTemp6 * fRec27[1] + fTemp7 * fTemp35);
			fRec26[0] = fRec27[0] * fTemp10 + fTemp9 * fRec26[1];
			fRec29[0] = fTemp15 + (-1.0f - (fRec29[2] * fTemp33 + fConst22 * fRec29[1]) / fTemp34);
			float fTemp36 = fRec29[0] - fRec29[2];
			float fTemp37 = fConst24 * (fConst24 - fTemp1) + 1.0f;
			float fTemp38 = fConst24 * (fConst24 + fTemp1) + 1.0f;
			fRec32[0] = fTemp0 - (fTemp37 * fRec32[2] + fConst25 * fRec32[1]) / fTemp38;
			float fTemp39 = std::fabs(fConst24 * ((fRec32[0] - fRec32[2]) / fTemp38));
			fRec31[0] = std::max<float>(fTemp39, fTemp6 * fRec31[1] + fTemp7 * fTemp39);
			fRec30[0] = fRec31[0] * fTemp10 + fTemp9 * fRec30[1];
			fRec33[0] = fTemp15 + (-1.0f - (fRec33[2] * fTemp37 + fConst25 * fRec33[1]) / fTemp38);
			float fTemp40 = fRec33[0] - fRec33[2];
			float fTemp41 = fConst27 * (fConst27 - fTemp1) + 1.0f;
			float fTemp42 = fConst27 * (fConst27 + fTemp1) + 1.0f;
			fRec36[0] = fTemp0 - (fTemp41 * fRec36[2] + fConst28 * fRec36[1]) / fTemp42;
			float fTemp43 = std::fabs(fConst27 * ((fRec36[0] - fRec36[2]) / fTemp42));
			fRec35[0] = std::max<float>(fTemp43, fTemp6 * fRec35[1] + fTemp7 * fTemp43);
			fRec34[0] = fRec35[0] * fTemp10 + fTemp9 * fRec34[1];
			fRec37[0] = fTemp15 + (-1.0f - (fRec37[2] * fTemp41 + fConst28 * fRec37[1]) / fTemp42);
			float fTemp44 = fRec37[0] - fRec37[2];
			float fTemp45 = fConst30 * (fConst30 - fTemp1) + 1.0f;
			float fTemp46 = fConst30 * (fConst30 + fTemp1) + 1.0f;
			fRec40[0] = fTemp0 - (fTemp45 * fRec40[2] + fConst31 * fRec40[1]) / fTemp46;
			float fTemp47 = std::fabs(fConst30 * ((fRec40[0] - fRec40[2]) / fTemp46));
			fRec39[0] = std::max<float>(fTemp47, fTemp6 * fRec39[1] + fTemp7 * fTemp47);
			fRec38[0] = fRec39[0] * fTemp10 + fTemp9 * fRec38[1];
			fRec41[0] = fTemp15 + (-1.0f - (fRec41[2] * fTemp45 + fConst31 * fRec41[1]) / fTemp46);
			float fTemp48 = fRec41[0] - fRec41[2];
			float fTemp49 = fConst33 * (fConst33 - fTemp1) + 1.0f;
			float fTemp50 = fConst33 * (fConst33 + fTemp1) + 1.0f;
			fRec44[0] = fTemp0 - (fTemp49 * fRec44[2] + fConst34 * fRec44[1]) / fTemp50;
			float fTemp51 = std::fabs(fConst33 * ((fRec44[0] - fRec44[2]) / fTemp50));
			fRec43[0] = std::max<float>(fTemp51, fTemp6 * fRec43[1] + fTemp7 * fTemp51);
			fRec42[0] = fRec43[0] * fTemp10 + fTemp9 * fRec42[1];
			fRec45[0] = fTemp15 + (-1.0f - (fRec45[2] * fTemp49 + fConst34 * fRec45[1]) / fTemp50);
			float fTemp52 = fRec45[0] - fRec45[2];
			float fTemp53 = fConst36 * (fConst36 - fTemp1) + 1.0f;
			float fTemp54 = fConst36 * (fConst36 + fTemp1) + 1.0f;
			fRec48[0] = fTemp0 - (fTemp53 * fRec48[2] + fConst37 * fRec48[1]) / fTemp54;
			float fTemp55 = std::fabs(fConst36 * ((fRec48[0] - fRec48[2]) / fTemp54));
			fRec47[0] = std::max<float>(fTemp55, fTemp6 * fRec47[1] + fTemp7 * fTemp55);
			fRec46[0] = fRec47[0] * fTemp10 + fTemp9 * fRec46[1];
			fRec49[0] = fTemp15 + (-1.0f - (fRec49[2] * fTemp53 + fConst37 * fRec49[1]) / fTemp54);
			float fTemp56 = fRec49[0] - fRec49[2];
			float fTemp57 = fConst39 * (fConst39 - fTemp1) + 1.0f;
			float fTemp58 = fConst39 * (fConst39 + fTemp1) + 1.0f;
			fRec52[0] = fTemp0 - (fTemp57 * fRec52[2] + fConst40 * fRec52[1]) / fTemp58;
			float fTemp59 = std::fabs(fConst39 * ((fRec52[0] - fRec52[2]) / fTemp58));
			fRec51[0] = std::max<float>(fTemp59, fTemp6 * fRec51[1] + fTemp7 * fTemp59);
			fRec50[0] = fRec51[0] * fTemp10 + fTemp9 * fRec50[1];
			fRec53[0] = fTemp15 + (-1.0f - (fRec53[2] * fTemp57 + fConst40 * fRec53[1]) / fTemp58);
			float fTemp60 = fRec53[0] - fRec53[2];
			float fTemp61 = fConst42 * (fConst42 - fTemp1) + 1.0f;
			float fTemp62 = fConst42 * (fConst42 + fTemp1) + 1.0f;
			fRec56[0] = fTemp0 - (fTemp61 * fRec56[2] + fConst43 * fRec56[1]) / fTemp62;
			float fTemp63 = std::fabs(fConst42 * ((fRec56[0] - fRec56[2]) / fTemp62));
			fRec55[0] = std::max<float>(fTemp63, fTemp6 * fRec55[1] + fTemp7 * fTemp63);
			fRec54[0] = fRec55[0] * fTemp10 + fTemp9 * fRec54[1];
			fRec57[0] = fTemp15 + (-1.0f - (fRec57[2] * fTemp61 + fConst43 * fRec57[1]) / fTemp62);
			float fTemp64 = fRec57[0] - fRec57[2];
			float fTemp65 = fConst45 * (fConst45 - fTemp1) + 1.0f;
			float fTemp66 = fConst45 * (fConst45 + fTemp1) + 1.0f;
			fRec60[0] = fTemp0 - (fTemp65 * fRec60[2] + fConst46 * fRec60[1]) / fTemp66;
			float fTemp67 = std::fabs(fConst45 * ((fRec60[0] - fRec60[2]) / fTemp66));
			fRec59[0] = std::max<float>(fTemp67, fTemp6 * fRec59[1] + fTemp7 * fTemp67);
			fRec58[0] = fRec59[0] * fTemp10 + fTemp9 * fRec58[1];
			fRec61[0] = fTemp15 + (-1.0f - (fRec61[2] * fTemp65 + fConst46 * fRec61[1]) / fTemp66);
			float fTemp68 = fRec61[0] - fRec61[2];
			float fTemp69 = fConst48 * (fConst48 - fTemp1) + 1.0f;
			float fTemp70 = fConst48 * (fConst48 + fTemp1) + 1.0f;
			fRec64[0] = fTemp0 - (fTemp69 * fRec64[2] + fConst49 * fRec64[1]) / fTemp70;
			float fTemp71 = std::fabs(fConst48 * ((fRec64[0] - fRec64[2]) / fTemp70));
			fRec63[0] = std::max<float>(fTemp71, fTemp6 * fRec63[1] + fTemp7 * fTemp71);
			fRec62[0] = fRec63[0] * fTemp10 + fTemp9 * fRec62[1];
			fRec65[0] = fTemp15 + (-1.0f - (fRec65[2] * fTemp69 + fConst49 * fRec65[1]) / fTemp70);
			float fTemp72 = fRec65[0] - fRec65[2];
			float fTemp73 = fConst51 * (fConst51 - fTemp1) + 1.0f;
			float fTemp74 = fConst51 * (fConst51 + fTemp1) + 1.0f;
			fRec68[0] = fTemp0 - (fTemp73 * fRec68[2] + fConst52 * fRec68[1]) / fTemp74;
			float fTemp75 = std::fabs(fConst51 * ((fRec68[0] - fRec68[2]) / fTemp74));
			fRec67[0] = std::max<float>(fTemp75, fTemp6 * fRec67[1] + fTemp7 * fTemp75);
			fRec66[0] = fRec67[0] * fTemp10 + fTemp9 * fRec66[1];
			fRec69[0] = fTemp15 + (-1.0f - (fRec69[2] * fTemp73 + fConst52 * fRec69[1]) / fTemp74);
			float fTemp76 = fRec69[0] - fRec69[2];
			float fTemp77 = fConst54 * (fConst54 - fTemp1) + 1.0f;
			float fTemp78 = fConst54 * (fConst54 + fTemp1) + 1.0f;
			fRec72[0] = fTemp0 - (fTemp77 * fRec72[2] + fConst55 * fRec72[1]) / fTemp78;
			float fTemp79 = std::fabs(fConst54 * ((fRec72[0] - fRec72[2]) / fTemp78));
			fRec71[0] = std::max<float>(fTemp79, fTemp6 * fRec71[1] + fTemp7 * fTemp79);
			fRec70[0] = fRec71[0] * fTemp10 + fTemp9 * fRec70[1];
			fRec73[0] = fTemp15 + (-1.0f - (fRec73[2] * fTemp77 + fConst55 * fRec73[1]) / fTemp78);
			float fTemp80 = fRec73[0] - fRec73[2];
			float fTemp81 = fConst57 * (fConst57 - fTemp1) + 1.0f;
			float fTemp82 = fConst57 * (fConst57 + fTemp1) + 1.0f;
			fRec76[0] = fTemp0 - (fTemp81 * fRec76[2] + fConst58 * fRec76[1]) / fTemp82;
			float fTemp83 = std::fabs(fConst57 * ((fRec76[0] - fRec76[2]) / fTemp82));
			fRec75[0] = std::max<float>(fTemp83, fTemp6 * fRec75[1] + fTemp7 * fTemp83);
			fRec74[0] = fRec75[0] * fTemp10 + fTemp9 * fRec74[1];
			fRec77[0] = fTemp15 + (-1.0f - (fRec77[2] * fTemp81 + fConst58 * fRec77[1]) / fTemp82);
			float fTemp84 = fRec77[0] - fRec77[2];
			float fTemp85 = fConst60 * (fConst60 - fTemp1) + 1.0f;
			float fTemp86 = fConst60 * (fConst60 + fTemp1) + 1.0f;
			fRec80[0] = fTemp0 - (fTemp85 * fRec80[2] + fConst61 * fRec80[1]) / fTemp86;
			float fTemp87 = std::fabs(fConst60 * ((fRec80[0] - fRec80[2]) / fTemp86));
			fRec79[0] = std::max<float>(fTemp87, fTemp6 * fRec79[1] + fTemp7 * fTemp87);
			fRec78[0] = fRec79[0] * fTemp10 + fTemp9 * fRec78[1];
			fRec81[0] = fTemp15 + (-1.0f - (fRec81[2] * fTemp85 + fConst61 * fRec81[1]) / fTemp86);
			float fTemp88 = fRec81[0] - fRec81[2];
			float fTemp89 = fConst63 * (fConst63 - fTemp1) + 1.0f;
			float fTemp90 = fConst63 * (fConst63 + fTemp1) + 1.0f;
			fRec84[0] = fTemp0 - (fTemp89 * fRec84[2] + fConst64 * fRec84[1]) / fTemp90;
			float fTemp91 = std::fabs(fConst63 * ((fRec84[0] - fRec84[2]) / fTemp90));
			fRec83[0] = std::max<float>(fTemp91, fTemp6 * fRec83[1] + fTemp7 * fTemp91);
			fRec82[0] = fRec83[0] * fTemp10 + fTemp9 * fRec82[1];
			fRec85[0] = fTemp15 + (-1.0f - (fRec85[2] * fTemp89 + fConst64 * fRec85[1]) / fTemp90);
			float fTemp92 = fRec85[0] - fRec85[2];
			float fTemp93 = fConst66 * (fConst66 - fTemp1) + 1.0f;
			float fTemp94 = fConst66 * (fConst66 + fTemp1) + 1.0f;
			fRec88[0] = fTemp0 - (fTemp93 * fRec88[2] + fConst67 * fRec88[1]) / fTemp94;
			float fTemp95 = std::fabs(fConst66 * ((fRec88[0] - fRec88[2]) / fTemp94));
			fRec87[0] = std::max<float>(fTemp95, fTemp6 * fRec87[1] + fTemp7 * fTemp95);
			fRec86[0] = fRec87[0] * fTemp10 + fTemp9 * fRec86[1];
			fRec89[0] = fTemp15 + (-1.0f - (fRec89[2] * fTemp93 + fConst67 * fRec89[1]) / fTemp94);
			float fTemp96 = fRec89[0] - fRec89[2];
			float fTemp97 = fConst69 * (fConst69 - fTemp1) + 1.0f;
			float fTemp98 = fConst69 * (fConst69 + fTemp1) + 1.0f;
			fRec92[0] = fTemp0 - (fTemp97 * fRec92[2] + fConst70 * fRec92[1]) / fTemp98;
			float fTemp99 = std::fabs(fConst69 * ((fRec92[0] - fRec92[2]) / fTemp98));
			fRec91[0] = std::max<float>(fTemp99, fTemp6 * fRec91[1] + fTemp7 * fTemp99);
			fRec90[0] = fRec91[0] * fTemp10 + fTemp9 * fRec90[1];
			fRec93[0] = fTemp15 + (-1.0f - (fRec93[2] * fTemp97 + fConst70 * fRec93[1]) / fTemp98);
			float fTemp100 = fRec93[0] - fRec93[2];
			float fTemp101 = fConst72 * (fConst72 - fTemp1) + 1.0f;
			float fTemp102 = fConst72 * (fConst72 + fTemp1) + 1.0f;
			fRec96[0] = fTemp0 - (fTemp101 * fRec96[2] + fConst73 * fRec96[1]) / fTemp102;
			float fTemp103 = std::fabs(fConst72 * ((fRec96[0] - fRec96[2]) / fTemp102));
			fRec95[0] = std::max<float>(fTemp103, fTemp6 * fRec95[1] + fTemp7 * fTemp103);
			fRec94[0] = fRec95[0] * fTemp10 + fTemp9 * fRec94[1];
			fRec97[0] = fTemp15 + (-1.0f - (fRec97[2] * fTemp101 + fConst73 * fRec97[1]) / fTemp102);
			float fTemp104 = fRec97[0] - fRec97[2];
			float fTemp105 = fConst75 * (fConst75 - fTemp1) + 1.0f;
			float fTemp106 = fConst75 * (fConst75 + fTemp1) + 1.0f;
			fRec100[0] = fTemp0 - (fTemp105 * fRec100[2] + fConst76 * fRec100[1]) / fTemp106;
			float fTemp107 = std::fabs(fConst75 * ((fRec100[0] - fRec100[2]) / fTemp106));
			fRec99[0] = std::max<float>(fTemp107, fTemp6 * fRec99[1] + fTemp7 * fTemp107);
			fRec98[0] = fRec99[0] * fTemp10 + fTemp9 * fRec98[1];
			fRec101[0] = fTemp15 + (-1.0f - (fRec101[2] * fTemp105 + fConst76 * fRec101[1]) / fTemp106);
			float fTemp108 = fRec101[0] - fRec101[2];
			float fTemp109 = fConst78 * (fConst78 - fTemp1) + 1.0f;
			float fTemp110 = fConst78 * (fConst78 + fTemp1) + 1.0f;
			fRec104[0] = fTemp0 - (fTemp109 * fRec104[2] + fConst79 * fRec104[1]) / fTemp110;
			float fTemp111 = std::fabs(fConst78 * ((fRec104[0] - fRec104[2]) / fTemp110));
			fRec103[0] = std::max<float>(fTemp111, fTemp6 * fRec103[1] + fTemp7 * fTemp111);
			fRec102[0] = fRec103[0] * fTemp10 + fTemp9 * fRec102[1];
			fRec105[0] = fTemp15 + (-1.0f - (fRec105[2] * fTemp109 + fConst79 * fRec105[1]) / fTemp110);
			float fTemp112 = fRec105[0] - fRec105[2];
			float fTemp113 = fConst81 * (fConst81 - fTemp1) + 1.0f;
			float fTemp114 = fConst81 * (fConst81 + fTemp1) + 1.0f;
			fRec108[0] = fTemp0 - (fTemp113 * fRec108[2] + fConst82 * fRec108[1]) / fTemp114;
			float fTemp115 = std::fabs(fConst81 * ((fRec108[0] - fRec108[2]) / fTemp114));
			fRec107[0] = std::max<float>(fTemp115, fTemp6 * fRec107[1] + fTemp7 * fTemp115);
			fRec106[0] = fRec107[0] * fTemp10 + fTemp9 * fRec106[1];
			fRec109[0] = fTemp15 + (-1.0f - (fRec109[2] * fTemp113 + fConst82 * fRec109[1]) / fTemp114);
			float fTemp116 = fRec109[0] - fRec109[2];
			float fTemp117 = fConst84 * (fConst84 - fTemp1) + 1.0f;
			float fTemp118 = fConst84 * (fConst84 + fTemp1) + 1.0f;
			fRec112[0] = fTemp0 - (fTemp117 * fRec112[2] + fConst85 * fRec112[1]) / fTemp118;
			float fTemp119 = std::fabs(fConst84 * ((fRec112[0] - fRec112[2]) / fTemp118));
			fRec111[0] = std::max<float>(fTemp119, fTemp6 * fRec111[1] + fTemp7 * fTemp119);
			fRec110[0] = fRec111[0] * fTemp10 + fTemp9 * fRec110[1];
			fRec113[0] = fTemp15 + (-1.0f - (fRec113[2] * fTemp117 + fConst85 * fRec113[1]) / fTemp118);
			float fTemp120 = fRec113[0] - fRec113[2];
			float fTemp121 = fConst87 * (fConst87 - fTemp1) + 1.0f;
			float fTemp122 = fConst87 * (fConst87 + fTemp1) + 1.0f;
			fRec116[0] = fTemp0 - (fTemp121 * fRec116[2] + fConst88 * fRec116[1]) / fTemp122;
			float fTemp123 = std::fabs(fConst87 * ((fRec116[0] - fRec116[2]) / fTemp122));
			fRec115[0] = std::max<float>(fTemp123, fTemp6 * fRec115[1] + fTemp7 * fTemp123);
			fRec114[0] = fRec115[0] * fTemp10 + fTemp9 * fRec114[1];
			fRec117[0] = fTemp15 + (-1.0f - (fRec117[2] * fTemp121 + fConst88 * fRec117[1]) / fTemp122);
			float fTemp124 = fRec117[0] - fRec117[2];
			float fTemp125 = fConst90 * (fConst90 - fTemp1) + 1.0f;
			float fTemp126 = fConst90 * (fConst90 + fTemp1) + 1.0f;
			fRec120[0] = fTemp0 - (fTemp125 * fRec120[2] + fConst91 * fRec120[1]) / fTemp126;
			float fTemp127 = std::fabs(fConst90 * ((fRec120[0] - fRec120[2]) / fTemp126));
			fRec119[0] = std::max<float>(fTemp127, fTemp6 * fRec119[1] + fTemp7 * fTemp127);
			fRec118[0] = fRec119[0] * fTemp10 + fTemp9 * fRec118[1];
			fRec121[0] = fTemp15 + (-1.0f - (fRec121[2] * fTemp125 + fConst91 * fRec121[1]) / fTemp126);
			float fTemp128 = fRec121[0] - fRec121[2];
			float fTemp129 = fConst93 * (fConst93 - fTemp1) + 1.0f;
			float fTemp130 = fConst93 * (fConst93 + fTemp1) + 1.0f;
			fRec124[0] = fTemp0 - (fTemp129 * fRec124[2] + fConst94 * fRec124[1]) / fTemp130;
			float fTemp131 = std::fabs(fConst93 * ((fRec124[0] - fRec124[2]) / fTemp130));
			fRec123[0] = std::max<float>(fTemp131, fTemp6 * fRec123[1] + fTemp7 * fTemp131);
			fRec122[0] = fRec123[0] * fTemp10 + fTemp9 * fRec122[1];
			fRec125[0] = fTemp15 + (-1.0f - (fRec125[2] * fTemp129 + fConst94 * fRec125[1]) / fTemp130);
			float fTemp132 = fRec125[0] - fRec125[2];
			float fTemp133 = fConst96 * (fConst96 - fTemp1) + 1.0f;
			float fTemp134 = fConst96 * (fConst96 + fTemp1) + 1.0f;
			fRec128[0] = fTemp0 - (fTemp133 * fRec128[2] + fConst97 * fRec128[1]) / fTemp134;
			float fTemp135 = std::fabs(fConst96 * ((fRec128[0] - fRec128[2]) / fTemp134));
			fRec127[0] = std::max<float>(fTemp135, fTemp6 * fRec127[1] + fTemp7 * fTemp135);
			fRec126[0] = fRec127[0] * fTemp10 + fTemp9 * fRec126[1];
			fRec129[0] = fTemp15 + (-1.0f - (fRec129[2] * fTemp133 + fConst97 * fRec129[1]) / fTemp134);
			float fTemp136 = fRec129[0] - fRec129[2];
			float fTemp137 = fConst99 * (fConst99 - fTemp1) + 1.0f;
			float fTemp138 = fConst99 * (fConst99 + fTemp1) + 1.0f;
			fRec132[0] = fTemp0 - (fTemp137 * fRec132[2] + fConst100 * fRec132[1]) / fTemp138;
			float fTemp139 = std::fabs(fConst99 * ((fRec132[0] - fRec132[2]) / fTemp138));
			fRec131[0] = std::max<float>(fTemp139, fTemp6 * fRec131[1] + fTemp7 * fTemp139);
			fRec130[0] = fRec131[0] * fTemp10 + fTemp9 * fRec130[1];
			fRec133[0] = fTemp15 + (-1.0f - (fRec133[2] * fTemp137 + fConst100 * fRec133[1]) / fTemp138);
			float fTemp140 = fRec133[0] - fRec133[2];
			output0[i0] = static_cast<FAUSTFLOAT>(fConst2 * (fRec0[0] * fTemp16 / fTemp3) + fConst9 * (fRec10[0] * fTemp20 / fTemp18) + fConst12 * (fRec14[0] * fTemp24 / fTemp22) + fConst15 * (fRec18[0] * fTemp28 / fTemp26) + fConst18 * (fRec22[0] * fTemp32 / fTemp30) + fConst21 * (fRec26[0] * fTemp36 / fTemp34) + fConst24 * (fRec30[0] * fTemp40 / fTemp38) + fConst27 * (fRec34[0] * fTemp44 / fTemp42) + fConst30 * (fRec38[0] * fTemp48 / fTemp46) + fConst33 * (fRec42[0] * fTemp52 / fTemp50) + fConst36 * (fRec46[0] * fTemp56 / fTemp54) + fConst39 * (fRec50[0] * fTemp60 / fTemp58) + fConst42 * (fRec54[0] * fTemp64 / fTemp62) + fConst45 * (fRec58[0] * fTemp68 / fTemp66) + fConst48 * (fRec62[0] * fTemp72 / fTemp70) + fConst51 * (fRec66[0] * fTemp76 / fTemp74) + fConst54 * (fRec70[0] * fTemp80 / fTemp78) + fConst57 * (fRec74[0] * fTemp84 / fTemp82) + fConst60 * (fRec78[0] * fTemp88 / fTemp86) + fConst63 * (fRec82[0] * fTemp92 / fTemp90) + fConst66 * (fRec86[0] * fTemp96 / fTemp94) + fConst69 * (fRec90[0] * fTemp100 / fTemp98) + fConst72 * (fRec94[0] * fTemp104 / fTemp102) + fConst75 * (fRec98[0] * fTemp108 / fTemp106) + fConst78 * (fRec102[0] * fTemp112 / fTemp110) + fConst81 * (fRec106[0] * fTemp116 / fTemp114) + fConst84 * (fRec110[0] * fTemp120 / fTemp118) + fConst87 * (fRec114[0] * fTemp124 / fTemp122) + fConst90 * (fRec118[0] * fTemp128 / fTemp126) + fConst93 * (fRec122[0] * fTemp132 / fTemp130) + fConst96 * (fRec126[0] * fTemp136 / fTemp134) + fConst99 * (fRec130[0] * fTemp140 / fTemp138));
			float fTemp141 = static_cast<float>(input1[i0]);
			fRec136[0] = fTemp141 - (fTemp2 * fRec136[2] + fConst5 * fRec136[1]) / fTemp3;
			float fTemp142 = std::fabs(fConst2 * ((fRec136[0] - fRec136[2]) / fTemp3));
			fRec135[0] = std::max<float>(fTemp142, fTemp6 * fRec135[1] + fTemp7 * fTemp142);
			fRec134[0] = fRec135[0] * fTemp10 + fTemp9 * fRec134[1];
			fRec139[0] = fTemp141 - (fTemp17 * fRec139[2] + fConst10 * fRec139[1]) / fTemp18;
			float fTemp143 = std::fabs(fConst9 * ((fRec139[0] - fRec139[2]) / fTemp18));
			fRec138[0] = std::max<float>(fTemp143, fTemp6 * fRec138[1] + fTemp7 * fTemp143);
			fRec137[0] = fRec138[0] * fTemp10 + fTemp9 * fRec137[1];
			fRec142[0] = fTemp141 - (fTemp21 * fRec142[2] + fConst13 * fRec142[1]) / fTemp22;
			float fTemp144 = std::fabs(fConst12 * ((fRec142[0] - fRec142[2]) / fTemp22));
			fRec141[0] = std::max<float>(fTemp144, fTemp6 * fRec141[1] + fTemp7 * fTemp144);
			fRec140[0] = fRec141[0] * fTemp10 + fTemp9 * fRec140[1];
			fRec145[0] = fTemp141 - (fTemp25 * fRec145[2] + fConst16 * fRec145[1]) / fTemp26;
			float fTemp145 = std::fabs(fConst15 * ((fRec145[0] - fRec145[2]) / fTemp26));
			fRec144[0] = std::max<float>(fTemp145, fTemp6 * fRec144[1] + fTemp7 * fTemp145);
			fRec143[0] = fRec144[0] * fTemp10 + fTemp9 * fRec143[1];
			fRec148[0] = fTemp141 - (fTemp29 * fRec148[2] + fConst19 * fRec148[1]) / fTemp30;
			float fTemp146 = std::fabs(fConst18 * ((fRec148[0] - fRec148[2]) / fTemp30));
			fRec147[0] = std::max<float>(fTemp146, fTemp6 * fRec147[1] + fTemp7 * fTemp146);
			fRec146[0] = fRec147[0] * fTemp10 + fTemp9 * fRec146[1];
			fRec151[0] = fTemp141 - (fTemp33 * fRec151[2] + fConst22 * fRec151[1]) / fTemp34;
			float fTemp147 = std::fabs(fConst21 * ((fRec151[0] - fRec151[2]) / fTemp34));
			fRec150[0] = std::max<float>(fTemp147, fTemp6 * fRec150[1] + fTemp7 * fTemp147);
			fRec149[0] = fRec150[0] * fTemp10 + fTemp9 * fRec149[1];
			fRec154[0] = fTemp141 - (fTemp37 * fRec154[2] + fConst25 * fRec154[1]) / fTemp38;
			float fTemp148 = std::fabs(fConst24 * ((fRec154[0] - fRec154[2]) / fTemp38));
			fRec153[0] = std::max<float>(fTemp148, fTemp6 * fRec153[1] + fTemp7 * fTemp148);
			fRec152[0] = fRec153[0] * fTemp10 + fTemp9 * fRec152[1];
			fRec157[0] = fTemp141 - (fTemp41 * fRec157[2] + fConst28 * fRec157[1]) / fTemp42;
			float fTemp149 = std::fabs(fConst27 * ((fRec157[0] - fRec157[2]) / fTemp42));
			fRec156[0] = std::max<float>(fTemp149, fTemp6 * fRec156[1] + fTemp7 * fTemp149);
			fRec155[0] = fRec156[0] * fTemp10 + fTemp9 * fRec155[1];
			fRec160[0] = fTemp141 - (fTemp45 * fRec160[2] + fConst31 * fRec160[1]) / fTemp46;
			float fTemp150 = std::fabs(fConst30 * ((fRec160[0] - fRec160[2]) / fTemp46));
			fRec159[0] = std::max<float>(fTemp150, fTemp6 * fRec159[1] + fTemp7 * fTemp150);
			fRec158[0] = fRec159[0] * fTemp10 + fTemp9 * fRec158[1];
			fRec163[0] = fTemp141 - (fTemp49 * fRec163[2] + fConst34 * fRec163[1]) / fTemp50;
			float fTemp151 = std::fabs(fConst33 * ((fRec163[0] - fRec163[2]) / fTemp50));
			fRec162[0] = std::max<float>(fTemp151, fTemp6 * fRec162[1] + fTemp7 * fTemp151);
			fRec161[0] = fRec162[0] * fTemp10 + fTemp9 * fRec161[1];
			fRec166[0] = fTemp141 - (fTemp53 * fRec166[2] + fConst37 * fRec166[1]) / fTemp54;
			float fTemp152 = std::fabs(fConst36 * ((fRec166[0] - fRec166[2]) / fTemp54));
			fRec165[0] = std::max<float>(fTemp152, fTemp6 * fRec165[1] + fTemp7 * fTemp152);
			fRec164[0] = fRec165[0] * fTemp10 + fTemp9 * fRec164[1];
			fRec169[0] = fTemp141 - (fTemp57 * fRec169[2] + fConst40 * fRec169[1]) / fTemp58;
			float fTemp153 = std::fabs(fConst39 * ((fRec169[0] - fRec169[2]) / fTemp58));
			fRec168[0] = std::max<float>(fTemp153, fTemp6 * fRec168[1] + fTemp7 * fTemp153);
			fRec167[0] = fRec168[0] * fTemp10 + fTemp9 * fRec167[1];
			fRec172[0] = fTemp141 - (fTemp61 * fRec172[2] + fConst43 * fRec172[1]) / fTemp62;
			float fTemp154 = std::fabs(fConst42 * ((fRec172[0] - fRec172[2]) / fTemp62));
			fRec171[0] = std::max<float>(fTemp154, fTemp6 * fRec171[1] + fTemp7 * fTemp154);
			fRec170[0] = fRec171[0] * fTemp10 + fTemp9 * fRec170[1];
			fRec175[0] = fTemp141 - (fTemp65 * fRec175[2] + fConst46 * fRec175[1]) / fTemp66;
			float fTemp155 = std::fabs(fConst45 * ((fRec175[0] - fRec175[2]) / fTemp66));
			fRec174[0] = std::max<float>(fTemp155, fTemp6 * fRec174[1] + fTemp7 * fTemp155);
			fRec173[0] = fRec174[0] * fTemp10 + fTemp9 * fRec173[1];
			fRec178[0] = fTemp141 - (fTemp69 * fRec178[2] + fConst49 * fRec178[1]) / fTemp70;
			float fTemp156 = std::fabs(fConst48 * ((fRec178[0] - fRec178[2]) / fTemp70));
			fRec177[0] = std::max<float>(fTemp156, fTemp6 * fRec177[1] + fTemp7 * fTemp156);
			fRec176[0] = fRec177[0] * fTemp10 + fTemp9 * fRec176[1];
			fRec181[0] = fTemp141 - (fTemp73 * fRec181[2] + fConst52 * fRec181[1]) / fTemp74;
			float fTemp157 = std::fabs(fConst51 * ((fRec181[0] - fRec181[2]) / fTemp74));
			fRec180[0] = std::max<float>(fTemp157, fTemp6 * fRec180[1] + fTemp7 * fTemp157);
			fRec179[0] = fRec180[0] * fTemp10 + fTemp9 * fRec179[1];
			fRec184[0] = fTemp141 - (fTemp77 * fRec184[2] + fConst55 * fRec184[1]) / fTemp78;
			float fTemp158 = std::fabs(fConst54 * ((fRec184[0] - fRec184[2]) / fTemp78));
			fRec183[0] = std::max<float>(fTemp158, fTemp6 * fRec183[1] + fTemp7 * fTemp158);
			fRec182[0] = fRec183[0] * fTemp10 + fTemp9 * fRec182[1];
			fRec187[0] = fTemp141 - (fTemp81 * fRec187[2] + fConst58 * fRec187[1]) / fTemp82;
			float fTemp159 = std::fabs(fConst57 * ((fRec187[0] - fRec187[2]) / fTemp82));
			fRec186[0] = std::max<float>(fTemp159, fTemp6 * fRec186[1] + fTemp7 * fTemp159);
			fRec185[0] = fRec186[0] * fTemp10 + fTemp9 * fRec185[1];
			fRec190[0] = fTemp141 - (fTemp85 * fRec190[2] + fConst61 * fRec190[1]) / fTemp86;
			float fTemp160 = std::fabs(fConst60 * ((fRec190[0] - fRec190[2]) / fTemp86));
			fRec189[0] = std::max<float>(fTemp160, fTemp6 * fRec189[1] + fTemp7 * fTemp160);
			fRec188[0] = fRec189[0] * fTemp10 + fTemp9 * fRec188[1];
			fRec193[0] = fTemp141 - (fTemp89 * fRec193[2] + fConst64 * fRec193[1]) / fTemp90;
			float fTemp161 = std::fabs(fConst63 * ((fRec193[0] - fRec193[2]) / fTemp90));
			fRec192[0] = std::max<float>(fTemp161, fTemp6 * fRec192[1] + fTemp7 * fTemp161);
			fRec191[0] = fRec192[0] * fTemp10 + fTemp9 * fRec191[1];
			fRec196[0] = fTemp141 - (fTemp93 * fRec196[2] + fConst67 * fRec196[1]) / fTemp94;
			float fTemp162 = std::fabs(fConst66 * ((fRec196[0] - fRec196[2]) / fTemp94));
			fRec195[0] = std::max<float>(fTemp162, fTemp6 * fRec195[1] + fTemp7 * fTemp162);
			fRec194[0] = fRec195[0] * fTemp10 + fTemp9 * fRec194[1];
			fRec199[0] = fTemp141 - (fTemp97 * fRec199[2] + fConst70 * fRec199[1]) / fTemp98;
			float fTemp163 = std::fabs(fConst69 * ((fRec199[0] - fRec199[2]) / fTemp98));
			fRec198[0] = std::max<float>(fTemp163, fTemp6 * fRec198[1] + fTemp7 * fTemp163);
			fRec197[0] = fRec198[0] * fTemp10 + fTemp9 * fRec197[1];
			fRec202[0] = fTemp141 - (fTemp101 * fRec202[2] + fConst73 * fRec202[1]) / fTemp102;
			float fTemp164 = std::fabs(fConst72 * ((fRec202[0] - fRec202[2]) / fTemp102));
			fRec201[0] = std::max<float>(fTemp164, fTemp6 * fRec201[1] + fTemp7 * fTemp164);
			fRec200[0] = fRec201[0] * fTemp10 + fTemp9 * fRec200[1];
			fRec205[0] = fTemp141 - (fTemp105 * fRec205[2] + fConst76 * fRec205[1]) / fTemp106;
			float fTemp165 = std::fabs(fConst75 * ((fRec205[0] - fRec205[2]) / fTemp106));
			fRec204[0] = std::max<float>(fTemp165, fTemp6 * fRec204[1] + fTemp7 * fTemp165);
			fRec203[0] = fRec204[0] * fTemp10 + fTemp9 * fRec203[1];
			fRec208[0] = fTemp141 - (fTemp109 * fRec208[2] + fConst79 * fRec208[1]) / fTemp110;
			float fTemp166 = std::fabs(fConst78 * ((fRec208[0] - fRec208[2]) / fTemp110));
			fRec207[0] = std::max<float>(fTemp166, fTemp6 * fRec207[1] + fTemp7 * fTemp166);
			fRec206[0] = fRec207[0] * fTemp10 + fTemp9 * fRec206[1];
			fRec211[0] = fTemp141 - (fTemp113 * fRec211[2] + fConst82 * fRec211[1]) / fTemp114;
			float fTemp167 = std::fabs(fConst81 * ((fRec211[0] - fRec211[2]) / fTemp114));
			fRec210[0] = std::max<float>(fTemp167, fTemp6 * fRec210[1] + fTemp7 * fTemp167);
			fRec209[0] = fRec210[0] * fTemp10 + fTemp9 * fRec209[1];
			fRec214[0] = fTemp141 - (fTemp117 * fRec214[2] + fConst85 * fRec214[1]) / fTemp118;
			float fTemp168 = std::fabs(fConst84 * ((fRec214[0] - fRec214[2]) / fTemp118));
			fRec213[0] = std::max<float>(fTemp168, fTemp6 * fRec213[1] + fTemp7 * fTemp168);
			fRec212[0] = fRec213[0] * fTemp10 + fTemp9 * fRec212[1];
			fRec217[0] = fTemp141 - (fTemp121 * fRec217[2] + fConst88 * fRec217[1]) / fTemp122;
			float fTemp169 = std::fabs(fConst87 * ((fRec217[0] - fRec217[2]) / fTemp122));
			fRec216[0] = std::max<float>(fTemp169, fTemp6 * fRec216[1] + fTemp7 * fTemp169);
			fRec215[0] = fRec216[0] * fTemp10 + fTemp9 * fRec215[1];
			fRec220[0] = fTemp141 - (fTemp125 * fRec220[2] + fConst91 * fRec220[1]) / fTemp126;
			float fTemp170 = std::fabs(fConst90 * ((fRec220[0] - fRec220[2]) / fTemp126));
			fRec219[0] = std::max<float>(fTemp170, fTemp6 * fRec219[1] + fTemp7 * fTemp170);
			fRec218[0] = fRec219[0] * fTemp10 + fTemp9 * fRec218[1];
			fRec223[0] = fTemp141 - (fTemp129 * fRec223[2] + fConst94 * fRec223[1]) / fTemp130;
			float fTemp171 = std::fabs(fConst93 * ((fRec223[0] - fRec223[2]) / fTemp130));
			fRec222[0] = std::max<float>(fTemp171, fTemp6 * fRec222[1] + fTemp7 * fTemp171);
			fRec221[0] = fRec222[0] * fTemp10 + fTemp9 * fRec221[1];
			fRec226[0] = fTemp141 - (fTemp133 * fRec226[2] + fConst97 * fRec226[1]) / fTemp134;
			float fTemp172 = std::fabs(fConst96 * ((fRec226[0] - fRec226[2]) / fTemp134));
			fRec225[0] = std::max<float>(fTemp172, fTemp6 * fRec225[1] + fTemp7 * fTemp172);
			fRec224[0] = fRec225[0] * fTemp10 + fTemp9 * fRec224[1];
			fRec229[0] = fTemp141 - (fTemp137 * fRec229[2] + fConst100 * fRec229[1]) / fTemp138;
			float fTemp173 = std::fabs(fConst99 * ((fRec229[0] - fRec229[2]) / fTemp138));
			fRec228[0] = std::max<float>(fTemp173, fTemp6 * fRec228[1] + fTemp7 * fTemp173);
			fRec227[0] = fRec228[0] * fTemp10 + fTemp9 * fRec227[1];
			output1[i0] = static_cast<FAUSTFLOAT>(fConst2 * (fRec134[0] * fTemp16 / fTemp3) + fConst9 * (fRec137[0] * fTemp20 / fTemp18) + fConst12 * (fRec140[0] * fTemp24 / fTemp22) + fConst15 * (fRec143[0] * fTemp28 / fTemp26) + fConst18 * (fRec146[0] * fTemp32 / fTemp30) + fConst21 * (fRec149[0] * fTemp36 / fTemp34) + fConst24 * (fRec152[0] * fTemp40 / fTemp38) + fConst27 * (fRec155[0] * fTemp44 / fTemp42) + fConst30 * (fRec158[0] * fTemp48 / fTemp46) + fConst33 * (fRec161[0] * fTemp52 / fTemp50) + fConst36 * (fRec164[0] * fTemp56 / fTemp54) + fConst39 * (fRec167[0] * fTemp60 / fTemp58) + fConst42 * (fRec170[0] * fTemp64 / fTemp62) + fConst45 * (fRec173[0] * fTemp68 / fTemp66) + fConst48 * (fRec176[0] * fTemp72 / fTemp70) + fConst51 * (fRec179[0] * fTemp76 / fTemp74) + fConst54 * (fRec182[0] * fTemp80 / fTemp78) + fConst57 * (fRec185[0] * fTemp84 / fTemp82) + fConst60 * (fRec188[0] * fTemp88 / fTemp86) + fConst63 * (fRec191[0] * fTemp92 / fTemp90) + fConst66 * (fRec194[0] * fTemp96 / fTemp94) + fConst69 * (fRec197[0] * fTemp100 / fTemp98) + fConst72 * (fRec200[0] * fTemp104 / fTemp102) + fConst75 * (fRec203[0] * fTemp108 / fTemp106) + fConst78 * (fRec206[0] * fTemp112 / fTemp110) + fConst81 * (fRec209[0] * fTemp116 / fTemp114) + fConst84 * (fRec212[0] * fTemp120 / fTemp118) + fConst87 * (fRec215[0] * fTemp124 / fTemp122) + fConst90 * (fRec218[0] * fTemp128 / fTemp126) + fConst93 * (fRec221[0] * fTemp132 / fTemp130) + fConst96 * (fRec224[0] * fTemp136 / fTemp134) + fConst99 * (fRec227[0] * fTemp140 / fTemp138));
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec4[1] = fRec4[0];
			fRec1[1] = fRec1[0];
			fRec5[1] = fRec5[0];
			fRec0[1] = fRec0[0];
			fRec9[1] = fRec9[0];
			fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec17[2] = fRec17[1];
			fRec17[1] = fRec17[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			fRec29[2] = fRec29[1];
			fRec29[1] = fRec29[0];
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
			fRec31[1] = fRec31[0];
			fRec30[1] = fRec30[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fRec35[1] = fRec35[0];
			fRec34[1] = fRec34[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec39[1] = fRec39[0];
			fRec38[1] = fRec38[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			fRec43[1] = fRec43[0];
			fRec42[1] = fRec42[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec47[1] = fRec47[0];
			fRec46[1] = fRec46[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec51[1] = fRec51[0];
			fRec50[1] = fRec50[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec55[1] = fRec55[0];
			fRec54[1] = fRec54[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];
			fRec59[1] = fRec59[0];
			fRec58[1] = fRec58[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fRec63[1] = fRec63[0];
			fRec62[1] = fRec62[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec67[1] = fRec67[0];
			fRec66[1] = fRec66[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec72[2] = fRec72[1];
			fRec72[1] = fRec72[0];
			fRec71[1] = fRec71[0];
			fRec70[1] = fRec70[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
			fRec75[1] = fRec75[0];
			fRec74[1] = fRec74[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			fRec80[2] = fRec80[1];
			fRec80[1] = fRec80[0];
			fRec79[1] = fRec79[0];
			fRec78[1] = fRec78[0];
			fRec81[2] = fRec81[1];
			fRec81[1] = fRec81[0];
			fRec84[2] = fRec84[1];
			fRec84[1] = fRec84[0];
			fRec83[1] = fRec83[0];
			fRec82[1] = fRec82[0];
			fRec85[2] = fRec85[1];
			fRec85[1] = fRec85[0];
			fRec88[2] = fRec88[1];
			fRec88[1] = fRec88[0];
			fRec87[1] = fRec87[0];
			fRec86[1] = fRec86[0];
			fRec89[2] = fRec89[1];
			fRec89[1] = fRec89[0];
			fRec92[2] = fRec92[1];
			fRec92[1] = fRec92[0];
			fRec91[1] = fRec91[0];
			fRec90[1] = fRec90[0];
			fRec93[2] = fRec93[1];
			fRec93[1] = fRec93[0];
			fRec96[2] = fRec96[1];
			fRec96[1] = fRec96[0];
			fRec95[1] = fRec95[0];
			fRec94[1] = fRec94[0];
			fRec97[2] = fRec97[1];
			fRec97[1] = fRec97[0];
			fRec100[2] = fRec100[1];
			fRec100[1] = fRec100[0];
			fRec99[1] = fRec99[0];
			fRec98[1] = fRec98[0];
			fRec101[2] = fRec101[1];
			fRec101[1] = fRec101[0];
			fRec104[2] = fRec104[1];
			fRec104[1] = fRec104[0];
			fRec103[1] = fRec103[0];
			fRec102[1] = fRec102[0];
			fRec105[2] = fRec105[1];
			fRec105[1] = fRec105[0];
			fRec108[2] = fRec108[1];
			fRec108[1] = fRec108[0];
			fRec107[1] = fRec107[0];
			fRec106[1] = fRec106[0];
			fRec109[2] = fRec109[1];
			fRec109[1] = fRec109[0];
			fRec112[2] = fRec112[1];
			fRec112[1] = fRec112[0];
			fRec111[1] = fRec111[0];
			fRec110[1] = fRec110[0];
			fRec113[2] = fRec113[1];
			fRec113[1] = fRec113[0];
			fRec116[2] = fRec116[1];
			fRec116[1] = fRec116[0];
			fRec115[1] = fRec115[0];
			fRec114[1] = fRec114[0];
			fRec117[2] = fRec117[1];
			fRec117[1] = fRec117[0];
			fRec120[2] = fRec120[1];
			fRec120[1] = fRec120[0];
			fRec119[1] = fRec119[0];
			fRec118[1] = fRec118[0];
			fRec121[2] = fRec121[1];
			fRec121[1] = fRec121[0];
			fRec124[2] = fRec124[1];
			fRec124[1] = fRec124[0];
			fRec123[1] = fRec123[0];
			fRec122[1] = fRec122[0];
			fRec125[2] = fRec125[1];
			fRec125[1] = fRec125[0];
			fRec128[2] = fRec128[1];
			fRec128[1] = fRec128[0];
			fRec127[1] = fRec127[0];
			fRec126[1] = fRec126[0];
			fRec129[2] = fRec129[1];
			fRec129[1] = fRec129[0];
			fRec132[2] = fRec132[1];
			fRec132[1] = fRec132[0];
			fRec131[1] = fRec131[0];
			fRec130[1] = fRec130[0];
			fRec133[2] = fRec133[1];
			fRec133[1] = fRec133[0];
			fRec136[2] = fRec136[1];
			fRec136[1] = fRec136[0];
			fRec135[1] = fRec135[0];
			fRec134[1] = fRec134[0];
			fRec139[2] = fRec139[1];
			fRec139[1] = fRec139[0];
			fRec138[1] = fRec138[0];
			fRec137[1] = fRec137[0];
			fRec142[2] = fRec142[1];
			fRec142[1] = fRec142[0];
			fRec141[1] = fRec141[0];
			fRec140[1] = fRec140[0];
			fRec145[2] = fRec145[1];
			fRec145[1] = fRec145[0];
			fRec144[1] = fRec144[0];
			fRec143[1] = fRec143[0];
			fRec148[2] = fRec148[1];
			fRec148[1] = fRec148[0];
			fRec147[1] = fRec147[0];
			fRec146[1] = fRec146[0];
			fRec151[2] = fRec151[1];
			fRec151[1] = fRec151[0];
			fRec150[1] = fRec150[0];
			fRec149[1] = fRec149[0];
			fRec154[2] = fRec154[1];
			fRec154[1] = fRec154[0];
			fRec153[1] = fRec153[0];
			fRec152[1] = fRec152[0];
			fRec157[2] = fRec157[1];
			fRec157[1] = fRec157[0];
			fRec156[1] = fRec156[0];
			fRec155[1] = fRec155[0];
			fRec160[2] = fRec160[1];
			fRec160[1] = fRec160[0];
			fRec159[1] = fRec159[0];
			fRec158[1] = fRec158[0];
			fRec163[2] = fRec163[1];
			fRec163[1] = fRec163[0];
			fRec162[1] = fRec162[0];
			fRec161[1] = fRec161[0];
			fRec166[2] = fRec166[1];
			fRec166[1] = fRec166[0];
			fRec165[1] = fRec165[0];
			fRec164[1] = fRec164[0];
			fRec169[2] = fRec169[1];
			fRec169[1] = fRec169[0];
			fRec168[1] = fRec168[0];
			fRec167[1] = fRec167[0];
			fRec172[2] = fRec172[1];
			fRec172[1] = fRec172[0];
			fRec171[1] = fRec171[0];
			fRec170[1] = fRec170[0];
			fRec175[2] = fRec175[1];
			fRec175[1] = fRec175[0];
			fRec174[1] = fRec174[0];
			fRec173[1] = fRec173[0];
			fRec178[2] = fRec178[1];
			fRec178[1] = fRec178[0];
			fRec177[1] = fRec177[0];
			fRec176[1] = fRec176[0];
			fRec181[2] = fRec181[1];
			fRec181[1] = fRec181[0];
			fRec180[1] = fRec180[0];
			fRec179[1] = fRec179[0];
			fRec184[2] = fRec184[1];
			fRec184[1] = fRec184[0];
			fRec183[1] = fRec183[0];
			fRec182[1] = fRec182[0];
			fRec187[2] = fRec187[1];
			fRec187[1] = fRec187[0];
			fRec186[1] = fRec186[0];
			fRec185[1] = fRec185[0];
			fRec190[2] = fRec190[1];
			fRec190[1] = fRec190[0];
			fRec189[1] = fRec189[0];
			fRec188[1] = fRec188[0];
			fRec193[2] = fRec193[1];
			fRec193[1] = fRec193[0];
			fRec192[1] = fRec192[0];
			fRec191[1] = fRec191[0];
			fRec196[2] = fRec196[1];
			fRec196[1] = fRec196[0];
			fRec195[1] = fRec195[0];
			fRec194[1] = fRec194[0];
			fRec199[2] = fRec199[1];
			fRec199[1] = fRec199[0];
			fRec198[1] = fRec198[0];
			fRec197[1] = fRec197[0];
			fRec202[2] = fRec202[1];
			fRec202[1] = fRec202[0];
			fRec201[1] = fRec201[0];
			fRec200[1] = fRec200[0];
			fRec205[2] = fRec205[1];
			fRec205[1] = fRec205[0];
			fRec204[1] = fRec204[0];
			fRec203[1] = fRec203[0];
			fRec208[2] = fRec208[1];
			fRec208[1] = fRec208[0];
			fRec207[1] = fRec207[0];
			fRec206[1] = fRec206[0];
			fRec211[2] = fRec211[1];
			fRec211[1] = fRec211[0];
			fRec210[1] = fRec210[0];
			fRec209[1] = fRec209[0];
			fRec214[2] = fRec214[1];
			fRec214[1] = fRec214[0];
			fRec213[1] = fRec213[0];
			fRec212[1] = fRec212[0];
			fRec217[2] = fRec217[1];
			fRec217[1] = fRec217[0];
			fRec216[1] = fRec216[0];
			fRec215[1] = fRec215[0];
			fRec220[2] = fRec220[1];
			fRec220[1] = fRec220[0];
			fRec219[1] = fRec219[0];
			fRec218[1] = fRec218[0];
			fRec223[2] = fRec223[1];
			fRec223[1] = fRec223[0];
			fRec222[1] = fRec222[0];
			fRec221[1] = fRec221[0];
			fRec226[2] = fRec226[1];
			fRec226[1] = fRec226[0];
			fRec225[1] = fRec225[0];
			fRec224[1] = fRec224[0];
			fRec229[2] = fRec229[1];
			fRec229[1] = fRec229[0];
			fRec228[1] = fRec228[0];
			fRec227[1] = fRec227[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "VocoderMono.dsp"
	#define FAUST_CLASS_NAME "_VocoderMono"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _VocoderMono -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 4
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("[0]Vocoder/Attack Duration", fHslider2, 0.1f, 0.01f, 1e+02f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("[0]Vocoder/Release Duration", fHslider1, 1.0f, 0.01f, 1e+02f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("[0]Vocoder/Q", fHslider0, 15.0f, 1.0f, 3e+01f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("[1]Sawtooth/Excitation Frequency", fHslider3, 1.5e+02f, 7e+01f, 1.5e+04f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Attack_Duration, "[0]Vocoder/Attack Duration", fHslider2, 0.1f, 0.01f, 1e+02f, 0.01f) \
		p(HORIZONTALSLIDER, Release_Duration, "[0]Vocoder/Release Duration", fHslider1, 1.0f, 0.01f, 1e+02f, 0.01f) \
		p(HORIZONTALSLIDER, Q, "[0]Vocoder/Q", fHslider0, 15.0f, 1.0f, 3e+01f, 0.01f) \
		p(HORIZONTALSLIDER, Excitation_Frequency, "[1]Sawtooth/Excitation Frequency", fHslider3, 1.5e+02f, 7e+01f, 1.5e+04f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

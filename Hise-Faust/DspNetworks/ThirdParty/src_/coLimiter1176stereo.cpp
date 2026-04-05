/* ------------------------------------------------------------
name: "coLimiter1176stereo"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _coLimiter1176stereo -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___coLimiter1176stereo_H__
#define  ___coLimiter1176stereo_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _coLimiter1176stereo
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


struct _coLimiter1176stereo final : public ::faust::dsp {
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider2;
	float fRec1[2];
	FAUSTFLOAT fHslider3;
	float fRec0[2];
	
	_coLimiter1176stereo() {
	}
	
	_coLimiter1176stereo(const _coLimiter1176stereo&) = default;
	
	virtual ~_coLimiter1176stereo() = default;
	
	_coLimiter1176stereo& operator=(const _coLimiter1176stereo&) = default;
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/amp_follower_ar:author", "Jonatan Liljedahl, revised by Romain Michon");
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.3.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _coLimiter1176stereo -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("compressors.lib/compression_gain_mono:author", "Julius O. Smith III");
		m->declare("compressors.lib/compression_gain_mono:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compression_gain_mono:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/compressor_stereo:author", "Julius O. Smith III");
		m->declare("compressors.lib/compressor_stereo:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compressor_stereo:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/name", "Faust Compressor Effect Library");
		m->declare("compressors.lib/version", "1.6.0");
		m->declare("filename", "coLimiter1176stereo.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "coLimiter1176stereo");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/onePoleSwitching:author", "Jonatan Liljedahl, revised by Dario Sanfilippo");
		m->declare("signals.lib/onePoleSwitching:licence", "STK-4.3");
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
		fConst0 = 1.0f / std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(4.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider2 = static_cast<FAUSTFLOAT>(0.0008f);
		fHslider3 = static_cast<FAUSTFLOAT>(-6.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec0[l1] = 0.0f;
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
	
	_coLimiter1176stereo* clone() {
		return new _coLimiter1176stereo(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("coLimiter1176stereo");
		ui_interface->addHorizontalSlider("attack", &fHslider2, FAUSTFLOAT(0.0008f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("ratio", &fHslider0, FAUSTFLOAT(4.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("release", &fHslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("threshold", &fHslider3, FAUSTFLOAT(-6.0f), FAUSTFLOAT(-3e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = 1.0f / std::max<float>(1.1920929e-07f, std::max<float>(0.0f, std::min<float>(2e+01f, static_cast<float>(fHslider0)))) + -1.0f;
		float fSlow1 = std::max<float>(0.0f, std::min<float>(5.0f, static_cast<float>(fHslider1)));
		int iSlow2 = std::fabs(fSlow1) < 1.1920929e-07f;
		float fSlow3 = ((iSlow2) ? 0.0f : std::exp(-(fConst0 / ((iSlow2) ? 1.0f : fSlow1))));
		float fSlow4 = std::max<float>(0.0f, std::min<float>(1e+01f, static_cast<float>(fHslider2)));
		int iSlow5 = std::fabs(fSlow4) < 1.1920929e-07f;
		float fSlow6 = ((iSlow5) ? 0.0f : std::exp(-(fConst0 / ((iSlow5) ? 1.0f : fSlow4))));
		float fSlow7 = std::max<float>(-3e+01f, std::min<float>(0.0f, static_cast<float>(fHslider3)));
		float fSlow8 = 0.5f * fSlow4;
		int iSlow9 = std::fabs(fSlow8) < 1.1920929e-07f;
		float fSlow10 = ((iSlow9) ? 0.0f : std::exp(-(fConst0 / ((iSlow9) ? 1.0f : fSlow8))));
		float fSlow11 = 1.0f - fSlow10;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			float fTemp1 = static_cast<float>(input1[i0]);
			float fTemp2 = std::fabs(std::fabs(fTemp0) + std::fabs(fTemp1));
			float fTemp3 = ((fTemp2 > fRec1[1]) ? fSlow6 : fSlow3);
			fRec1[0] = fTemp2 * (1.0f - fTemp3) + fRec1[1] * fTemp3;
			fRec0[0] = fSlow0 * std::max<float>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, fRec1[0])) - fSlow7, 0.0f) * fSlow11 + fSlow10 * fRec0[1];
			float fTemp4 = std::pow(1e+01f, 0.05f * fRec0[0]);
			output0[i0] = static_cast<FAUSTFLOAT>(fTemp0 * fTemp4);
			output1[i0] = static_cast<FAUSTFLOAT>(fTemp1 * fTemp4);
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "coLimiter1176stereo.dsp"
	#define FAUST_CLASS_NAME "_coLimiter1176stereo"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _coLimiter1176stereo -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 4
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("attack", fHslider2, 0.0008f, 0.0f, 1e+01f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("ratio", fHslider0, 4.0f, 0.0f, 2e+01f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("release", fHslider1, 0.5f, 0.0f, 5.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("threshold", fHslider3, -6.0f, -3e+01f, 0.0f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, attack, "attack", fHslider2, 0.0008f, 0.0f, 1e+01f, 0.01f) \
		p(HORIZONTALSLIDER, ratio, "ratio", fHslider0, 4.0f, 0.0f, 2e+01f, 0.01f) \
		p(HORIZONTALSLIDER, release, "release", fHslider1, 0.5f, 0.0f, 5.0f, 0.01f) \
		p(HORIZONTALSLIDER, threshold, "threshold", fHslider3, -6.0f, -3e+01f, 0.0f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

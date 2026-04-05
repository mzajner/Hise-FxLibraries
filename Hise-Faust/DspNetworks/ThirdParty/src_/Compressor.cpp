/* ------------------------------------------------------------
author: "Albert Graef"
name: "compressor -- compressor/limiter unit"
version: "1.0"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _Compressor -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___Compressor_H__
#define  ___Compressor_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _Compressor
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


struct _Compressor final : public ::faust::dsp {
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fEntry1;
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider1;
	float fConst3;
	float fConst4;
	float fRec1[2];
	float fRec2[2];
	FAUSTFLOAT fHslider2;
	float fRec0[2];
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT fHbargraph0;
	
	_Compressor() {
	}
	
	_Compressor(const _Compressor&) = default;
	
	virtual ~_Compressor() = default;
	
	_Compressor& operator=(const _Compressor&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Albert Graef");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _Compressor -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "Compressor.dsp");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/version", "1.0");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "compressor -- compressor/limiter unit");
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
		fConst1 = 1e+03f / fConst0;
		fConst2 = 0.001f / fConst0;
		fConst3 = std::exp(-(1e+01f / fConst0));
		fConst4 = 1.0f - fConst3;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(0.0f);
		fEntry0 = static_cast<FAUSTFLOAT>(2.0f);
		fEntry1 = static_cast<FAUSTFLOAT>(3.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(2.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(5e+02f);
		fEntry2 = static_cast<FAUSTFLOAT>(-2e+01f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec2[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec0[l2] = 0.0f;
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
	
	_Compressor* clone() {
		return new _Compressor(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("compressor -- compressor/limiter unit");
		ui_interface->openHorizontalBox("1-compression");
		ui_interface->addNumEntry("knee", &fEntry1, FAUSTFLOAT(3.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->addNumEntry("ratio", &fEntry0, FAUSTFLOAT(2.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->addNumEntry("threshold", &fEntry2, FAUSTFLOAT(-2e+01f), FAUSTFLOAT(-96.0f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2-envelop");
		ui_interface->addHorizontalSlider("attack (ms)", &fHslider1, FAUSTFLOAT(2.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(1.0f));
		ui_interface->addHorizontalSlider("release (ms)", &fHslider2, FAUSTFLOAT(5e+02f), FAUSTFLOAT(0.0f), FAUSTFLOAT(3e+03f), FAUSTFLOAT(1e+01f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3-gain");
		ui_interface->addHorizontalBargraph("gain", &fHbargraph0, FAUSTFLOAT(-96.0f), FAUSTFLOAT(0.0f));
		ui_interface->addHorizontalSlider("makeupGain", &fHslider0, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = std::max<float>(-12.0f, std::min<float>(12.0f, static_cast<float>(fHslider0)));
		float fSlow1 = 1.0f - std::max<float>(1.0f, std::min<float>(2e+01f, static_cast<float>(fEntry0)));
		float fSlow2 = std::max<float>(0.0f, std::min<float>(2e+01f, static_cast<float>(fEntry1)));
		float fSlow3 = std::exp(-(fConst1 / std::max<float>(fConst2, std::max<float>(0.0f, std::min<float>(1e+03f, static_cast<float>(fHslider1))))));
		float fSlow4 = std::exp(-(fConst1 / std::max<float>(fConst2, std::max<float>(0.0f, std::min<float>(3e+03f, static_cast<float>(fHslider2))))));
		float fSlow5 = std::max<float>(-96.0f, std::min<float>(1e+01f, static_cast<float>(fEntry2)));
		float fSlow6 = 1.0f / (fSlow2 + 0.001f);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			fRec1[0] = fConst3 * fRec1[1] + fConst4 * std::fabs(fTemp0);
			float fTemp1 = static_cast<float>(input1[i0]);
			fRec2[0] = fConst3 * fRec2[1] + fConst4 * std::fabs(fTemp1);
			float fTemp2 = std::max<float>(fRec1[0], fRec2[0]);
			float fTemp3 = fSlow3 * static_cast<float>(fRec0[1] < fTemp2) + fSlow4 * static_cast<float>(fRec0[1] >= fTemp2);
			fRec0[0] = fRec0[1] * fTemp3 + fTemp2 * (1.0f - fTemp3);
			float fTemp4 = std::max<float>(0.0f, fSlow2 + (2e+01f * std::log10(fRec0[0]) - fSlow5));
			float fTemp5 = std::min<float>(1.0f, std::max<float>(0.0f, fSlow6 * fTemp4));
			float fTemp6 = fSlow1 * (fTemp4 * fTemp5 / (1.0f - fSlow1 * fTemp5));
			fHbargraph0 = static_cast<FAUSTFLOAT>(fTemp6);
			float fTemp7 = std::pow(1e+01f, 0.05f * (fSlow0 + fTemp6));
			output0[i0] = static_cast<FAUSTFLOAT>(fTemp0 * fTemp7);
			output1[i0] = static_cast<FAUSTFLOAT>(fTemp1 * fTemp7);
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "Compressor.dsp"
	#define FAUST_CLASS_NAME "_Compressor"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _Compressor -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 6
	#define FAUST_PASSIVES 1

	FAUST_ADDNUMENTRY("1-compression/knee", fEntry1, 3.0f, 0.0f, 2e+01f, 0.1f);
	FAUST_ADDNUMENTRY("1-compression/ratio", fEntry0, 2.0f, 1.0f, 2e+01f, 0.1f);
	FAUST_ADDNUMENTRY("1-compression/threshold", fEntry2, -2e+01f, -96.0f, 1e+01f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("2-envelop/attack (ms)", fHslider1, 2.0f, 0.0f, 1e+03f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("2-envelop/release (ms)", fHslider2, 5e+02f, 0.0f, 3e+03f, 1e+01f);
	FAUST_ADDHORIZONTALBARGRAPH("3-gain/gain", fHbargraph0, -96.0f, 0.0f);
	FAUST_ADDHORIZONTALSLIDER("3-gain/makeupGain", fHslider0, 0.0f, -12.0f, 12.0f, 0.1f);

	#define FAUST_LIST_ACTIVES(p) \
		p(NUMENTRY, knee, "1-compression/knee", fEntry1, 3.0f, 0.0f, 2e+01f, 0.1f) \
		p(NUMENTRY, ratio, "1-compression/ratio", fEntry0, 2.0f, 1.0f, 2e+01f, 0.1f) \
		p(NUMENTRY, threshold, "1-compression/threshold", fEntry2, -2e+01f, -96.0f, 1e+01f, 0.1f) \
		p(HORIZONTALSLIDER, attack_(ms), "2-envelop/attack (ms)", fHslider1, 2.0f, 0.0f, 1e+03f, 1.0f) \
		p(HORIZONTALSLIDER, release_(ms), "2-envelop/release (ms)", fHslider2, 5e+02f, 0.0f, 3e+03f, 1e+01f) \
		p(HORIZONTALSLIDER, makeupGain, "3-gain/makeupGain", fHslider0, 0.0f, -12.0f, 12.0f, 0.1f) \

	#define FAUST_LIST_PASSIVES(p) \
		p(HORIZONTALBARGRAPH, gain, "3-gain/gain", fHbargraph0, 0.0, -96.0f, 0.0f, 0.0) \

#endif

#endif

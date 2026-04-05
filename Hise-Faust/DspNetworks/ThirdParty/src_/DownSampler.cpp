/* ------------------------------------------------------------
author: "Gabriele Acquafredda"
name: "Simple Mid Side Ping Pong Flip Flop Tic Tac Zip Zap Delay"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _DownSampler -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___DownSampler_H__
#define  ___DownSampler_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _DownSampler
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

static float _DownSampler_faustpower2_f(float value) {
	return value * value;
}

struct _DownSampler final : public ::faust::dsp {
	
	int iRec2[2];
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	float fRec3[2];
	float fRec1[2];
	float fConst3;
	FAUSTFLOAT fHslider1;
	float fRec4[2];
	FAUSTFLOAT fHslider2;
	float fRec5[2];
	float fRec0[3];
	FAUSTFLOAT fHslider3;
	float fRec7[2];
	FAUSTFLOAT fHslider4;
	float fRec8[2];
	float fRec6[3];
	float fRec10[2];
	float fRec9[3];
	float fRec11[3];
	
	_DownSampler() {
	}
	
	_DownSampler(const _DownSampler&) = default;
	
	virtual ~_DownSampler() = default;
	
	_DownSampler& operator=(const _DownSampler&) = default;
	
	void metadata(Meta* m) { 
		m->declare("author", "Gabriele Acquafredda");
		m->declare("basics.lib/downSample:author", "Romain Michon");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/sAndH:author", "Romain Michon");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _DownSampler -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "DownSampler.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/resonhp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonhp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonhp:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/resonlp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonlp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonlp:license", "MIT-style STK-4.3 license");
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
		m->declare("name", "Simple Mid Side Ping Pong Flip Flop Tic Tac Zip Zap Delay");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("vendor", "G.A.");
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
		fConst3 = 3.1415927f / fConst0;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(2e+04f);
		fHslider1 = static_cast<FAUSTFLOAT>(2.2e+04f);
		fHslider2 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider3 = static_cast<FAUSTFLOAT>(2e+01f);
		fHslider4 = static_cast<FAUSTFLOAT>(1.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iRec2[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec3[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec4[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 3; l5 = l5 + 1) {
			fRec0[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec7[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec8[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 3; l8 = l8 + 1) {
			fRec6[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec10[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec9[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec11[l11] = 0.0f;
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
	
	_DownSampler* clone() {
		return new _DownSampler(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Simple Mid Side Ping Pong Flip Flop Tic Tac Zip Zap Delay");
		ui_interface->openHorizontalBox("Filters");
		ui_interface->addHorizontalSlider("HPF Freq", &fHslider3, FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2.2e+04f), FAUSTFLOAT(1.0f));
		ui_interface->addHorizontalSlider("HPF Q", &fHslider4, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.05f));
		ui_interface->addHorizontalSlider("LPF Freq", &fHslider1, FAUSTFLOAT(2.2e+04f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2.2e+04f), FAUSTFLOAT(1.0f));
		ui_interface->addHorizontalSlider("LPF Q", &fHslider2, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.05f));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Modulation");
		ui_interface->addHorizontalSlider("Downsample Frequency", &fHslider0, FAUSTFLOAT(2e+04f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2.2e+04f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst1 * std::max<float>(2e+01f, std::min<float>(2.2e+04f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst1 * std::max<float>(2e+01f, std::min<float>(2.2e+04f, static_cast<float>(fHslider1)));
		float fSlow2 = fConst1 * std::max<float>(1.0f, std::min<float>(5.0f, static_cast<float>(fHslider2)));
		float fSlow3 = fConst1 * std::max<float>(2e+01f, std::min<float>(2.2e+04f, static_cast<float>(fHslider3)));
		float fSlow4 = fConst1 * std::max<float>(1.0f, std::min<float>(5.0f, static_cast<float>(fHslider4)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iRec2[0] = iRec2[1] + 1;
			fRec3[0] = fSlow0 + fConst2 * fRec3[1];
			int iTemp0 = (iRec2[1] % static_cast<int>(fConst0 / fRec3[0])) == 0;
			fRec1[0] = ((iTemp0) ? static_cast<float>(input0[i0]) : fRec1[1]);
			fRec4[0] = fSlow1 + fConst2 * fRec4[1];
			float fTemp1 = std::tan(fConst3 * fRec4[0]);
			float fTemp2 = 1.0f / fTemp1;
			fRec5[0] = fSlow2 + fConst2 * fRec5[1];
			float fTemp3 = 1.0f / fRec5[0];
			float fTemp4 = (fTemp2 - fTemp3) / fTemp1 + 1.0f;
			float fTemp5 = 1.0f - 1.0f / _DownSampler_faustpower2_f(fTemp1);
			float fTemp6 = (fTemp3 + fTemp2) / fTemp1 + 1.0f;
			fRec0[0] = fRec1[0] - (fRec0[2] * fTemp4 + 2.0f * fRec0[1] * fTemp5) / fTemp6;
			float fTemp7 = (fRec0[2] + fRec0[0] + 2.0f * fRec0[1]) / fTemp6;
			fRec7[0] = fSlow3 + fConst2 * fRec7[1];
			float fTemp8 = std::tan(fConst3 * fRec7[0]);
			float fTemp9 = 1.0f / fTemp8;
			fRec8[0] = fSlow4 + fConst2 * fRec8[1];
			float fTemp10 = 1.0f / fRec8[0];
			float fTemp11 = (fTemp9 - fTemp10) / fTemp8 + 1.0f;
			float fTemp12 = 1.0f - 1.0f / _DownSampler_faustpower2_f(fTemp8);
			float fTemp13 = (fTemp10 + fTemp9) / fTemp8 + 1.0f;
			fRec6[0] = fTemp7 - (fRec6[2] * fTemp11 + 2.0f * fRec6[1] * fTemp12) / fTemp13;
			output0[i0] = static_cast<FAUSTFLOAT>(fTemp7 - (fRec6[2] + fRec6[0] + 2.0f * fRec6[1]) / fTemp13);
			fRec10[0] = ((iTemp0) ? static_cast<float>(input1[i0]) : fRec10[1]);
			fRec9[0] = fRec10[0] - (fTemp4 * fRec9[2] + 2.0f * fTemp5 * fRec9[1]) / fTemp6;
			float fTemp14 = (fRec9[2] + fRec9[0] + 2.0f * fRec9[1]) / fTemp6;
			fRec11[0] = fTemp14 - (fTemp11 * fRec11[2] + 2.0f * fTemp12 * fRec11[1]) / fTemp13;
			output1[i0] = static_cast<FAUSTFLOAT>(fTemp14 - (fRec11[2] + fRec11[0] + 2.0f * fRec11[1]) / fTemp13);
			iRec2[1] = iRec2[0];
			fRec3[1] = fRec3[0];
			fRec1[1] = fRec1[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec10[1] = fRec10[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "DownSampler.dsp"
	#define FAUST_CLASS_NAME "_DownSampler"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _DownSampler -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 5
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Filters/HPF Freq", fHslider3, 2e+01f, 2e+01f, 2.2e+04f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("Filters/HPF Q", fHslider4, 1.0f, 1.0f, 5.0f, 0.05f);
	FAUST_ADDHORIZONTALSLIDER("Filters/LPF Freq", fHslider1, 2.2e+04f, 2e+01f, 2.2e+04f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("Filters/LPF Q", fHslider2, 1.0f, 1.0f, 5.0f, 0.05f);
	FAUST_ADDHORIZONTALSLIDER("Modulation/Downsample Frequency", fHslider0, 2e+04f, 2e+01f, 2.2e+04f, 1.0f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, HPF_Freq, "Filters/HPF Freq", fHslider3, 2e+01f, 2e+01f, 2.2e+04f, 1.0f) \
		p(HORIZONTALSLIDER, HPF_Q, "Filters/HPF Q", fHslider4, 1.0f, 1.0f, 5.0f, 0.05f) \
		p(HORIZONTALSLIDER, LPF_Freq, "Filters/LPF Freq", fHslider1, 2.2e+04f, 2e+01f, 2.2e+04f, 1.0f) \
		p(HORIZONTALSLIDER, LPF_Q, "Filters/LPF Q", fHslider2, 1.0f, 1.0f, 5.0f, 0.05f) \
		p(HORIZONTALSLIDER, Downsample_Frequency, "Modulation/Downsample Frequency", fHslider0, 2e+04f, 2e+01f, 2.2e+04f, 1.0f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

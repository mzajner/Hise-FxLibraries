/* ------------------------------------------------------------
name: "GritAmp"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _GritAmp -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___GritAmp_H__
#define  ___GritAmp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _GritAmp
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

static float _GritAmp_faustpower2_f(float value) {
	return value * value;
}

struct _GritAmp final : public ::faust::dsp {
	
	FAUSTFLOAT fHslider0;
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fVec0[2];
	float fRec3[2];
	float fRec2[2];
	FAUSTFLOAT fHslider1;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	FAUSTFLOAT fHslider2;
	float fConst8;
	float fRec5[2];
	float fVec1[2];
	float fRec4[2];
	float fVec2[2];
	float fConst9;
	FAUSTFLOAT fHslider3;
	float fRec6[2];
	float fRec1[2];
	float fRec0[3];
	float fRec8[2];
	float fRec7[3];
	FAUSTFLOAT fHslider4;
	float fRec9[2];
	
	_GritAmp() {
	}
	
	_GritAmp(const _GritAmp&) = default;
	
	virtual ~_GritAmp() = default;
	
	_GritAmp& operator=(const _GritAmp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.3.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _GritAmp -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "GritAmp.dsp");
		m->declare("filters.lib/dcblocker:author", "Julius O. Smith III");
		m->declare("filters.lib/dcblocker:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/dcblocker:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/filterbank:author", "Julius O. Smith III");
		m->declare("filters.lib/filterbank:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/filterbank:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/highshelf:author", "Julius O. Smith III");
		m->declare("filters.lib/highshelf:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/highshelf:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
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
		m->declare("name", "GritAmp");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
	}

	static constexpr int getStaticNumInputs() {
		return 1;
	}
	static constexpr int getStaticNumOutputs() {
		return 1;
	}
	int getNumInputs() {
		return 1;
	}
	int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = 1.0f / std::tan(5403.5396f / fConst0);
		fConst2 = 1.0f / (fConst1 + 1.0f);
		fConst3 = 1.0f - fConst1;
		fConst4 = 1.0f / std::tan(376.99112f / fConst0);
		fConst5 = 1.0f / (fConst4 + 1.0f);
		fConst6 = 1.0f - fConst4;
		fConst7 = 44.1f / fConst0;
		fConst8 = 1.0f - fConst7;
		fConst9 = 3.1415927f / fConst0;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(5e+01f);
		fHslider3 = static_cast<FAUSTFLOAT>(7.2e+02f);
		fHslider4 = static_cast<FAUSTFLOAT>(-7.5f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fVec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec3[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec2[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec5[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fVec1[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec4[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fVec2[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec6[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec1[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec0[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec8[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec7[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec9[l12] = 0.0f;
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
	
	_GritAmp* clone() {
		return new _GritAmp(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("GritAmp");
		ui_interface->addHorizontalSlider("Depth", &fHslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("Gritz", &fHslider2, FAUSTFLOAT(5e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(1.0f));
		ui_interface->addHorizontalSlider("Tone", &fHslider4, FAUSTFLOAT(-7.5f), FAUSTFLOAT(-15.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.1f));
		ui_interface->addHorizontalSlider("Tone Frequency", &fHslider3, FAUSTFLOAT(7.2e+02f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(5e+03f), FAUSTFLOAT(1.0f));
		ui_interface->addHorizontalSlider("Volume", &fHslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = 0.0005f * std::pow(1e+01f, 2.5f * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider0))));
		float fSlow1 = std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider1))) + -1.0f;
		float fSlow2 = fConst7 * std::max<float>(0.0f, std::min<float>(1e+02f, static_cast<float>(fHslider2)));
		float fSlow3 = fConst7 * std::max<float>(1e+02f, std::min<float>(5e+03f, static_cast<float>(fHslider3)));
		float fSlow4 = fConst7 * std::max<float>(-15.0f, std::min<float>(0.0f, static_cast<float>(fHslider4)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			fVec0[0] = fTemp0;
			fRec3[0] = fTemp0 + 0.995f * fRec3[1] - fVec0[1];
			fRec2[0] = -(fConst2 * (fConst3 * fRec2[1] - (fRec3[0] + fRec3[1])));
			fRec5[0] = fSlow2 + fConst8 * fRec5[1];
			float fTemp1 = 0.005f * fRec5[0];
			float fTemp2 = std::min<float>(1.0f, std::max<float>(0.0f, 1e+01f * fRec2[0] * std::pow(1e+01f, fTemp1) + 0.5f));
			fVec1[0] = fTemp2;
			fRec4[0] = -(fConst5 * (fConst6 * fRec4[1] - fConst4 * (fTemp2 - fVec1[1])));
			float fTemp3 = fRec2[0] * (fSlow1 * (std::min<float>(1.0f, std::max<float>(-1.0f, (_GritAmp_faustpower2_f(fRec4[0] + 0.5f) + -0.4f) * std::pow(1e+01f, 0.01f * fRec5[0]))) + 0.15f) + 1.0f);
			fVec2[0] = fTemp3;
			fRec6[0] = fSlow3 + fConst8 * fRec6[1];
			float fTemp4 = std::tan(fConst9 * fRec6[0]);
			float fTemp5 = 1.0f / fTemp4;
			float fTemp6 = 1.0f - fTemp5;
			float fTemp7 = fTemp5 + 1.0f;
			fRec1[0] = (1e+01f * (fTemp3 + fVec2[1]) - fTemp6 * fRec1[1]) / fTemp7;
			float fTemp8 = (fTemp5 + -1.0f) / fTemp4 + 1.0f;
			float fTemp9 = _GritAmp_faustpower2_f(fTemp4);
			float fTemp10 = 1.0f - 1.0f / fTemp9;
			float fTemp11 = (fTemp5 + 1.0f) / fTemp4 + 1.0f;
			fRec0[0] = fRec1[0] - (fTemp8 * fRec0[2] + 2.0f * fTemp10 * fRec0[1]) / fTemp11;
			fRec8[0] = (1e+01f * ((fTemp3 - fVec2[1]) / fTemp4) - fRec8[1] * fTemp6) / fTemp7;
			fRec7[0] = fRec8[0] - (fRec7[2] * fTemp8 + 2.0f * fRec7[1] * fTemp10) / fTemp11;
			fRec9[0] = fSlow4 + fConst8 * fRec9[1];
			output0[i0] = static_cast<FAUSTFLOAT>(fSlow0 * ((fRec0[2] + fRec0[0] + 2.0f * fRec0[1] + (fRec7[2] + (fRec7[0] - 2.0f * fRec7[1])) * std::pow(1e+01f, 0.05f * (fRec9[0] + 7.5f)) / fTemp9) * std::pow(1e+01f, -fTemp1) / fTemp11));
			fVec0[1] = fVec0[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec5[1] = fRec5[0];
			fVec1[1] = fVec1[0];
			fRec4[1] = fRec4[0];
			fVec2[1] = fVec2[0];
			fRec6[1] = fRec6[0];
			fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec9[1] = fRec9[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "GritAmp.dsp"
	#define FAUST_CLASS_NAME "_GritAmp"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _GritAmp -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 1
	#define FAUST_OUTPUTS 1
	#define FAUST_ACTIVES 5
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Depth", fHslider1, 1.0f, 0.0f, 1.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("Gritz", fHslider2, 5e+01f, 0.0f, 1e+02f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("Tone", fHslider4, -7.5f, -15.0f, 0.0f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Tone Frequency", fHslider3, 7.2e+02f, 1e+02f, 5e+03f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("Volume", fHslider0, 1.0f, 0.0f, 1.0f, 0.001f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Depth, "Depth", fHslider1, 1.0f, 0.0f, 1.0f, 0.001f) \
		p(HORIZONTALSLIDER, Gritz, "Gritz", fHslider2, 5e+01f, 0.0f, 1e+02f, 1.0f) \
		p(HORIZONTALSLIDER, Tone, "Tone", fHslider4, -7.5f, -15.0f, 0.0f, 0.1f) \
		p(HORIZONTALSLIDER, Tone_Frequency, "Tone Frequency", fHslider3, 7.2e+02f, 1e+02f, 5e+03f, 1.0f) \
		p(HORIZONTALSLIDER, Volume, "Volume", fHslider0, 1.0f, 0.0f, 1.0f, 0.001f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

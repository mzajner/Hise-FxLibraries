/* ------------------------------------------------------------
name: "SpeakerSimulator"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _SpeakerSimulator -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___SpeakerSimulator_H__
#define  ___SpeakerSimulator_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _SpeakerSimulator
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

static float _SpeakerSimulator_faustpower2_f(float value) {
	return value * value;
}

struct _SpeakerSimulator final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	float fConst3;
	float fRec4[2];
	float fVec0[2];
	float fRec3[2];
	float fVec1[2];
	float fRec2[2];
	FAUSTFLOAT fHslider1;
	float fRec5[2];
	float fRec1[3];
	float fRec0[3];
	float fVec2[2];
	float fRec9[2];
	float fVec3[2];
	float fRec8[2];
	float fRec7[3];
	float fRec6[3];
	
	_SpeakerSimulator() {
	}
	
	_SpeakerSimulator(const _SpeakerSimulator&) = default;
	
	virtual ~_SpeakerSimulator() = default;
	
	_SpeakerSimulator& operator=(const _SpeakerSimulator&) = default;
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _SpeakerSimulator -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "SpeakerSimulator.dsp");
		m->declare("filters.lib/dcblockerat:author", "Julius O. Smith III");
		m->declare("filters.lib/dcblockerat:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/dcblockerat:license", "MIT-style STK-4.3 license");
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
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
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
		m->declare("name", "SpeakerSimulator");
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
		fConst1 = 3.1415927f / fConst0;
		fConst2 = 44.1f / fConst0;
		fConst3 = 1.0f - fConst2;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(1.3e+02f);
		fHslider1 = static_cast<FAUSTFLOAT>(5e+03f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec4[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fVec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec3[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fVec1[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec2[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec5[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 3; l6 = l6 + 1) {
			fRec1[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 3; l7 = l7 + 1) {
			fRec0[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fVec2[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec9[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fVec3[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec8[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 3; l12 = l12 + 1) {
			fRec7[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 3; l13 = l13 + 1) {
			fRec6[l13] = 0.0f;
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
	
	_SpeakerSimulator* clone() {
		return new _SpeakerSimulator(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("SpeakerSimulator");
		ui_interface->declare(&fHslider0, "01", "");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->addHorizontalSlider("F1", &fHslider0, FAUSTFLOAT(1.3e+02f), FAUSTFLOAT(5e+01f), FAUSTFLOAT(3e+03f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider1, "01", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("F2", &fHslider1, FAUSTFLOAT(5e+03f), FAUSTFLOAT(3.5e+03f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst2 * std::max<float>(5e+01f, std::min<float>(3e+03f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst2 * std::max<float>(3.5e+03f, std::min<float>(2e+04f, static_cast<float>(fHslider1)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			fRec4[0] = fSlow0 + fConst3 * fRec4[1];
			float fTemp1 = fConst1 * fRec4[0];
			float fTemp2 = 1.0f - fTemp1;
			float fTemp3 = fTemp1 + 1.0f;
			fVec0[0] = fTemp0 / fTemp3;
			fRec3[0] = (fTemp0 + fTemp2 * fRec3[1]) / fTemp3 - fVec0[1];
			fVec1[0] = fRec3[0] / fTemp3;
			fRec2[0] = (fRec3[0] + fRec2[1] * fTemp2) / fTemp3 - fVec1[1];
			fRec5[0] = fSlow1 + fConst3 * fRec5[1];
			float fTemp4 = std::tan(fConst1 * fRec5[0]);
			float fTemp5 = 1.0f / fTemp4;
			float fTemp6 = (fTemp5 + -1.847759f) / fTemp4 + 1.0f;
			float fTemp7 = 1.0f - 1.0f / _SpeakerSimulator_faustpower2_f(fTemp4);
			float fTemp8 = (fTemp5 + 1.847759f) / fTemp4 + 1.0f;
			fRec1[0] = fRec2[0] - (fRec1[2] * fTemp6 + 2.0f * fRec1[1] * fTemp7) / fTemp8;
			float fTemp9 = (fTemp5 + -0.76536685f) / fTemp4 + 1.0f;
			float fTemp10 = (fTemp5 + 0.76536685f) / fTemp4 + 1.0f;
			fRec0[0] = (fRec1[2] + fRec1[0] + 2.0f * fRec1[1]) / fTemp8 - (fRec0[2] * fTemp9 + 2.0f * fTemp7 * fRec0[1]) / fTemp10;
			output0[i0] = static_cast<FAUSTFLOAT>((fRec0[2] + fRec0[0] + 2.0f * fRec0[1]) / fTemp10);
			float fTemp11 = static_cast<float>(input1[i0]);
			fVec2[0] = fTemp11 / fTemp3;
			fRec9[0] = (fTemp11 + fTemp2 * fRec9[1]) / fTemp3 - fVec2[1];
			fVec3[0] = fRec9[0] / fTemp3;
			fRec8[0] = (fRec9[0] + fTemp2 * fRec8[1]) / fTemp3 - fVec3[1];
			fRec7[0] = fRec8[0] - (fTemp6 * fRec7[2] + 2.0f * fTemp7 * fRec7[1]) / fTemp8;
			fRec6[0] = (fRec7[2] + fRec7[0] + 2.0f * fRec7[1]) / fTemp8 - (fTemp9 * fRec6[2] + 2.0f * fTemp7 * fRec6[1]) / fTemp10;
			output1[i0] = static_cast<FAUSTFLOAT>((fRec6[2] + fRec6[0] + 2.0f * fRec6[1]) / fTemp10);
			fRec4[1] = fRec4[0];
			fVec0[1] = fVec0[0];
			fRec3[1] = fRec3[0];
			fVec1[1] = fVec1[0];
			fRec2[1] = fRec2[0];
			fRec5[1] = fRec5[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fVec2[1] = fVec2[0];
			fRec9[1] = fRec9[0];
			fVec3[1] = fVec3[0];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "SpeakerSimulator.dsp"
	#define FAUST_CLASS_NAME "_SpeakerSimulator"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _SpeakerSimulator -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("F1", fHslider0, 1.3e+02f, 5e+01f, 3e+03f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("F2", fHslider1, 5e+03f, 3.5e+03f, 2e+04f, 1.0f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, F1, "F1", fHslider0, 1.3e+02f, 5e+01f, 3e+03f, 1.0f) \
		p(HORIZONTALSLIDER, F2, "F2", fHslider1, 5e+03f, 3.5e+03f, 2e+04f, 1.0f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

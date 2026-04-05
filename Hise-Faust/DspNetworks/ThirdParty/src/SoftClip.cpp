/* ------------------------------------------------------------
name: "SoftClip"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _SoftClip -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___SoftClip_H__
#define  ___SoftClip_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _SoftClip
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

static float _SoftClip_faustpower2_f(float value) {
	return value * value;
}
static float _SoftClip_faustpower3_f(float value) {
	return value * value * value;
}

struct _SoftClip final : public ::faust::dsp {
	
	FAUSTFLOAT fEntry0;
	float fVec0[2];
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fEntry1;
	float fConst1;
	float fRec0[2];
	FAUSTFLOAT fEntry2;
	float fRec1[2];
	float fVec1[2];
	FAUSTFLOAT fEntry3;
	float fRec2[2];
	float fVec2[3];
	
	_SoftClip() {
	}
	
	_SoftClip(const _SoftClip&) = default;
	
	virtual ~_SoftClip() = default;
	
	_SoftClip& operator=(const _SoftClip&) = default;
	
	void metadata(Meta* m) { 
		m->declare("aanl.lib/ADAA1:author", "Dario Sanfilippo");
		m->declare("aanl.lib/ADAA1:copyright", "Copyright (C) 2021 Dario Sanfilippo     <sanfilippo.dario@gmail.com>");
		m->declare("aanl.lib/ADAA1:license", "MIT License");
		m->declare("aanl.lib/ADAA2:author", "Dario Sanfilippo");
		m->declare("aanl.lib/ADAA2:copyright", "Copyright (C) 2021 Dario Sanfilippo     <sanfilippo.dario@gmail.com>");
		m->declare("aanl.lib/ADAA2:license", "MIT License");
		m->declare("aanl.lib/arctan:author", "Dario Sanfilippo");
		m->declare("aanl.lib/arctan:copyright", "Copyright (C) 2021 Dario Sanfilippo     <sanfilippo.dario@gmail.com>");
		m->declare("aanl.lib/arctan:license", "MIT License");
		m->declare("aanl.lib/hardclip2:author", "Dario Sanfilippo");
		m->declare("aanl.lib/hardclip2:copyright", "Copyright (C) 2021 Dario Sanfilippo     <sanfilippo.dario@gmail.com>");
		m->declare("aanl.lib/hardclip2:license", "MIT License");
		m->declare("aanl.lib/name", "Faust Antialiased Nonlinearities");
		m->declare("aanl.lib/version", "1.4.2");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _SoftClip -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "SoftClip.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "SoftClip");
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
		fConst0 = 44.1f / std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = 1.0f - fConst0;
	}
	
	void instanceResetUserInterface() {
		fEntry0 = static_cast<FAUSTFLOAT>(0.0f);
		fEntry1 = static_cast<FAUSTFLOAT>(0.0f);
		fEntry2 = static_cast<FAUSTFLOAT>(0.0f);
		fEntry3 = static_cast<FAUSTFLOAT>(0.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fVec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fVec1[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec2[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 3; l5 = l5 + 1) {
			fVec2[l5] = 0.0f;
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
	
	_SoftClip* clone() {
		return new _SoftClip(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("SoftClip");
		ui_interface->addNumEntry("clipping", &fEntry0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addNumEntry("drive", &fEntry1, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addNumEntry("softclip", &fEntry3, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addNumEntry("squeeze", &fEntry2, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fEntry0)));
		float fSlow1 = std::min<float>(2e+01f * fSlow0, 1.0f);
		float fSlow2 = std::max<float>(1.1920929e-07f, 2e+01f * _SoftClip_faustpower2_f(0.85f * fSlow0 + 0.15f));
		float fSlow3 = fConst0 * std::pow(1e+01f, std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fEntry1))));
		float fSlow4 = fConst0 * std::pow(1e+01f, std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fEntry2))));
		float fSlow5 = fSlow2 * std::atan(fSlow2);
		float fSlow6 = std::log(_SoftClip_faustpower2_f(fSlow2) + 1.0f);
		float fSlow7 = 1.0f - fSlow1;
		float fSlow8 = fConst0 * std::pow(1e+01f, -(0.15f * std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fEntry3)))));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fVec0[0] = fSlow2;
			fRec0[0] = fSlow3 + fConst1 * fRec0[1];
			fRec1[0] = fSlow4 + fConst1 * fRec1[1];
			float fTemp0 = static_cast<float>(input0[i0]) * fRec0[0] * fRec1[0];
			float fTemp1 = fSlow2 * fTemp0;
			fVec1[0] = fTemp1;
			float fTemp2 = fTemp1 - fVec1[1];
			float fTemp3 = fSlow2 - fVec0[1];
			float fTemp4 = fSlow1 * (((std::fabs(fTemp2) <= 0.001f) ? std::atan(0.5f * (fTemp1 + fVec1[1])) : (fSlow2 * fTemp0 * std::atan(fTemp1) - (fVec1[1] * std::atan(fVec1[1]) + 0.5f * (std::log(_SoftClip_faustpower2_f(fTemp1) + 1.0f) - std::log(_SoftClip_faustpower2_f(fVec1[1]) + 1.0f)))) / fTemp2) / ((std::fabs(fTemp3) <= 0.001f) ? std::atan(0.5f * (fSlow2 + fVec0[1])) : (fSlow5 - (fVec0[1] * std::atan(fVec0[1]) + 0.5f * (fSlow6 - std::log(_SoftClip_faustpower2_f(fVec0[1]) + 1.0f)))) / fTemp3)) + fSlow7 * fTemp0;
			float fTemp5 = std::fabs(fTemp4);
			fRec2[0] = fSlow8 + fConst1 * fRec2[1];
			float fTemp6 = 1.0f - fRec2[0];
			float fTemp7 = std::min<float>(fTemp5, fRec2[0] + 0.63661975f * fTemp6 * std::atan(1.5707964f * ((fTemp5 - fRec2[0]) / fTemp6))) * static_cast<float>((fTemp4 > 0.0f) - (fTemp4 < 0.0f));
			fVec2[0] = fTemp7;
			float fTemp8 = _SoftClip_faustpower2_f(fTemp7 - fVec2[1]);
			int iTemp9 = (fTemp7 <= 1.0f) & (fTemp7 >= -1.0f);
			float fTemp10 = static_cast<float>((fTemp7 > 0.0f) - (fTemp7 < 0.0f));
			float fTemp11 = 0.5f * _SoftClip_faustpower2_f(fTemp7);
			int iTemp12 = (fVec2[1] <= 1.0f) & (fVec2[1] >= -1.0f);
			float fTemp13 = static_cast<float>((fVec2[1] > 0.0f) - (fVec2[1] < 0.0f));
			float fTemp14 = 0.5f * _SoftClip_faustpower2_f(fVec2[1]);
			float fTemp15 = ((iTemp12) ? fTemp14 : fVec2[1] * fTemp13 + -0.5f);
			float fTemp16 = ((iTemp12) ? 0.33333334f * _SoftClip_faustpower3_f(fVec2[1]) : fTemp13 * (fTemp14 + -0.16666667f));
			float fTemp17 = 2.0f * fVec2[1];
			int iTemp18 = (fVec2[2] <= 1.0f) & (fVec2[2] >= -1.0f);
			float fTemp19 = static_cast<float>((fVec2[2] > 0.0f) - (fVec2[2] < 0.0f));
			float fTemp20 = 0.5f * _SoftClip_faustpower2_f(fVec2[2]);
			output0[i0] = static_cast<FAUSTFLOAT>((((fTemp8 <= 0.001f) ? 0.5f * std::max<float>(-1.0f, std::min<float>(1.0f, 0.33333334f * (fTemp7 + fTemp17))) : (fTemp7 * (((iTemp9) ? fTemp11 : fTemp7 * fTemp10 + -0.5f) - fTemp15) + fTemp16 - ((iTemp9) ? 0.33333334f * _SoftClip_faustpower3_f(fTemp7) : fTemp10 * (fTemp11 + -0.16666667f))) / fTemp8) + ((_SoftClip_faustpower2_f(fVec2[1] - fVec2[2]) <= 0.001f) ? 0.5f * std::max<float>(-1.0f, std::min<float>(1.0f, 0.33333334f * (fTemp17 + fVec2[2]))) : (fTemp16 + fVec2[2] * (((iTemp18) ? fTemp20 : fVec2[2] * fTemp19 + -0.5f) - fTemp15) - ((iTemp18) ? 0.33333334f * _SoftClip_faustpower3_f(fVec2[2]) : fTemp19 * (fTemp20 + -0.16666667f))) / _SoftClip_faustpower2_f(fVec2[2] - fVec2[1]))) / fRec1[0]);
			fVec0[1] = fVec0[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fVec1[1] = fVec1[0];
			fRec2[1] = fRec2[0];
			fVec2[2] = fVec2[1];
			fVec2[1] = fVec2[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "SoftClip.dsp"
	#define FAUST_CLASS_NAME "_SoftClip"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _SoftClip -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 1
	#define FAUST_OUTPUTS 1
	#define FAUST_ACTIVES 4
	#define FAUST_PASSIVES 0

	FAUST_ADDNUMENTRY("clipping", fEntry0, 0.0f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDNUMENTRY("drive", fEntry1, 0.0f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDNUMENTRY("softclip", fEntry3, 0.0f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDNUMENTRY("squeeze", fEntry2, 0.0f, 0.0f, 1.0f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(NUMENTRY, clipping, "clipping", fEntry0, 0.0f, 0.0f, 1.0f, 0.01f) \
		p(NUMENTRY, drive, "drive", fEntry1, 0.0f, 0.0f, 1.0f, 0.01f) \
		p(NUMENTRY, softclip, "softclip", fEntry3, 0.0f, 0.0f, 1.0f, 0.01f) \
		p(NUMENTRY, squeeze, "squeeze", fEntry2, 0.0f, 0.0f, 1.0f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

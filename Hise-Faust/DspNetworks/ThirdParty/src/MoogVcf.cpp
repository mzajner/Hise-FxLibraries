/* ------------------------------------------------------------
name: "moogVCF"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _MoogVcf -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___MoogVcf_H__
#define  ___MoogVcf_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _MoogVcf
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

static float _MoogVcf_faustpower4_f(float value) {
	return value * value * value * value;
}
static float _MoogVcf_faustpower2_f(float value) {
	return value * value;
}

struct _MoogVcf final : public ::faust::dsp {
	
	FAUSTFLOAT fCheckbox0;
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	float fRec0[2];
	FAUSTFLOAT fCheckbox1;
	float fConst3;
	float fConst4;
	FAUSTFLOAT fHslider1;
	float fRec6[2];
	FAUSTFLOAT fHslider2;
	float fRec5[2];
	float fRec4[2];
	float fRec3[2];
	float fRec2[2];
	float fRec1[2];
	FAUSTFLOAT fCheckbox2;
	float fConst5;
	float fRec8[3];
	float fRec7[3];
	float fRec11[2];
	float fRec9[2];
	float fRec14[2];
	float fRec12[2];
	float fRec19[2];
	float fRec18[2];
	float fRec17[2];
	float fRec16[2];
	float fRec15[2];
	float fRec21[3];
	float fRec20[3];
	float fRec24[2];
	float fRec22[2];
	float fRec27[2];
	float fRec25[2];
	
	_MoogVcf() {
	}
	
	_MoogVcf(const _MoogVcf&) = default;
	
	virtual ~_MoogVcf() = default;
	
	_MoogVcf& operator=(const _MoogVcf&) = default;
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/bypass1:author", "Julius Smith");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _MoogVcf -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("demos.lib/moog_vcf_demo:author", "Julius O. Smith III");
		m->declare("demos.lib/moog_vcf_demo:licence", "MIT");
		m->declare("demos.lib/name", "Faust Demos Library");
		m->declare("demos.lib/version", "1.4.0");
		m->declare("description", "Exercise and compare three Moog VCF implementations");
		m->declare("filename", "MoogVcf.dsp");
		m->declare("filters.lib/allpassnnlt:author", "Julius O. Smith III");
		m->declare("filters.lib/allpassnnlt:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/allpassnnlt:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2np:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2np:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2np:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "moogVCF");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("vaeffects.lib/moog_vcf:author", "Julius O. Smith III");
		m->declare("vaeffects.lib/moog_vcf:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("vaeffects.lib/moog_vcf:license", "MIT-style STK-4.3 license");
		m->declare("vaeffects.lib/moog_vcf_2b:author", "Julius O. Smith III");
		m->declare("vaeffects.lib/moog_vcf_2b:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("vaeffects.lib/moog_vcf_2b:license", "MIT-style STK-4.3 license");
		m->declare("vaeffects.lib/moog_vcf_2bn:author", "Julius O. Smith III");
		m->declare("vaeffects.lib/moog_vcf_2bn:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("vaeffects.lib/moog_vcf_2bn:license", "MIT-style STK-4.3 license");
		m->declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m->declare("vaeffects.lib/version", "1.4.0");
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
		fConst4 = 19404.0f / fConst0;
		fConst5 = 3.1415927f / fConst0;
	}
	
	void instanceResetUserInterface() {
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider0 = static_cast<FAUSTFLOAT>(5.0f);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(25.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(0.9f);
		fCheckbox2 = static_cast<FAUSTFLOAT>(0.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec6[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec5[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec4[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec3[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec2[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec1[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 3; l7 = l7 + 1) {
			fRec8[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 3; l8 = l8 + 1) {
			fRec7[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec11[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec9[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec14[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec12[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec19[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec18[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec17[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec16[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec15[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 3; l18 = l18 + 1) {
			fRec21[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 3; l19 = l19 + 1) {
			fRec20[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fRec24[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			fRec22[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fRec27[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec25[l23] = 0.0f;
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
	
	_MoogVcf* clone() {
		return new _MoogVcf(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->declare(0, "tooltip", "See Faust's         vaeffects.lib for info and references");
		ui_interface->openHorizontalBox("MOOG VCF (Voltage Controlled Filter)");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the Moog VCF         has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fCheckbox1, "1", "");
		ui_interface->declare(&fCheckbox1, "tooltip", "Select moog_vcf_2b (two-biquad)         implementation, instead of the default moog_vcf (analog style) implementation");
		ui_interface->addCheckButton("Use Biquads", &fCheckbox1);
		ui_interface->declare(&fCheckbox2, "2", "");
		ui_interface->declare(&fCheckbox2, "tooltip", "If using biquads, make         them normalized ladders (moog_vcf_2bn)");
		ui_interface->addCheckButton("Normalized Ladders", &fCheckbox2);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "tooltip", "The VCF resonates         at the corner frequency (specified in PianoKey (PK) units, with A440 = 49 PK).         The VCF response is flat below the corner frequency, and rolls off -24 dB per         octave above.");
		ui_interface->declare(&fHslider1, "unit", "PK");
		ui_interface->addHorizontalSlider("Corner Frequency", &fHslider1, FAUSTFLOAT(25.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(88.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider2, "2", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->declare(&fHslider2, "tooltip", "Amount of         resonance near VCF corner frequency (specified between 0 and 1)");
		ui_interface->addHorizontalSlider("Corner Resonance", &fHslider2, FAUSTFLOAT(0.9f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "tooltip", "output level in decibels");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("VCF Output Level", &fHslider0, FAUSTFLOAT(5.0f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		int iSlow0 = static_cast<int>(static_cast<float>(fCheckbox0));
		float fSlow1 = fConst1 * std::pow(1e+01f, 0.05f * std::max<float>(-6e+01f, std::min<float>(2e+01f, static_cast<float>(fHslider0))));
		int iSlow2 = static_cast<int>(static_cast<float>(fCheckbox1));
		float fSlow3 = fConst4 * std::pow(2.0f, 0.083333336f * (std::max<float>(1.0f, std::min<float>(88.0f, static_cast<float>(fHslider1))) + -49.0f));
		float fSlow4 = std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fHslider2)));
		float fSlow5 = 4.0f * std::max<float>(0.0f, std::min<float>(_MoogVcf_faustpower4_f(fSlow4), 0.999999f));
		int iSlow6 = static_cast<int>(static_cast<float>(fCheckbox2));
		float fSlow7 = std::min<float>(1.4141995f, 1.4142135f * fSlow4);
		float fSlow8 = 1.4142135f * fSlow7;
		float fSlow9 = _MoogVcf_faustpower2_f(fSlow7);
		float fSlow10 = fSlow8 + fSlow9;
		float fSlow11 = fSlow8 + 2.0f;
		float fSlow12 = 2.0f - fSlow8;
		float fSlow13 = _MoogVcf_faustpower2_f(1.4141995f * fSlow4);
		float fSlow14 = 1.99998f * fSlow4;
		float fSlow15 = fSlow13 + fSlow14;
		float fSlow16 = fSlow14 + 2.0f;
		float fSlow17 = 2.0f - fSlow14;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[0] = fSlow1 + fConst2 * fRec0[1];
			float fTemp0 = static_cast<float>(input0[i0]);
			float fTemp1 = ((iSlow0) ? 0.0f : fTemp0);
			fRec6[0] = fSlow3 + fConst2 * fRec6[1];
			float fTemp2 = fConst3 * fRec6[0];
			float fTemp3 = 1.0f - fTemp2;
			fRec5[0] = fTemp1 + fTemp3 * fRec5[1] - fSlow5 * fRec1[1];
			fRec4[0] = fRec5[0] + fTemp3 * fRec4[1];
			fRec3[0] = fRec4[0] + fTemp3 * fRec3[1];
			fRec2[0] = fRec3[0] + fRec2[1] * fTemp3;
			float fTemp4 = _MoogVcf_faustpower4_f(fTemp2);
			fRec1[0] = fRec2[0] * fTemp4;
			float fTemp5 = std::tan(fConst5 * std::max<float>(2e+01f, std::min<float>(1e+04f, fRec6[0])));
			float fTemp6 = 1.0f / fTemp5;
			float fTemp7 = fSlow10 + (fTemp6 - fSlow11) / fTemp5 + 1.0f;
			float fTemp8 = 1.0f - 1.0f / _MoogVcf_faustpower2_f(fTemp5);
			float fTemp9 = fSlow10 + fTemp8;
			float fTemp10 = fSlow10 + (fSlow11 + fTemp6) / fTemp5 + 1.0f;
			fRec8[0] = fTemp1 - (fRec8[2] * fTemp7 + 2.0f * fRec8[1] * fTemp9) / fTemp10;
			float fTemp11 = fSlow9 + ((fTemp6 - fSlow12) / fTemp5 + 1.0f - fSlow8);
			float fTemp12 = fSlow9 + (fTemp8 - fSlow8);
			float fTemp13 = fSlow9 + ((fSlow12 + fTemp6) / fTemp5 + 1.0f - fSlow8);
			fRec7[0] = (fRec8[2] + fRec8[0] + 2.0f * fRec8[1]) / fTemp10 - (fRec7[2] * fTemp11 + 2.0f * fRec7[1] * fTemp12) / fTemp13;
			float fTemp14 = std::tan(fConst5 * std::max<float>(fRec6[0], 2e+01f));
			float fTemp15 = 1.0f / fTemp14;
			float fTemp16 = fSlow15 + (fSlow16 + fTemp15) / fTemp14 + 1.0f;
			float fTemp17 = (fSlow15 + (1.0f - (fSlow16 - fTemp15) / fTemp14)) / fTemp16;
			float fTemp18 = std::max<float>(-0.9999999f, std::min<float>(0.9999999f, fTemp17));
			float fTemp19 = 1.0f - _MoogVcf_faustpower2_f(fTemp18);
			float fTemp20 = std::sqrt(std::max<float>(0.0f, fTemp19));
			float fTemp21 = fTemp1 * fTemp20 - fTemp18 * fRec9[1];
			float fTemp22 = 1.0f - 1.0f / _MoogVcf_faustpower2_f(fTemp14);
			float fTemp23 = fSlow15 + fTemp22;
			float fTemp24 = std::max<float>(-0.9999999f, std::min<float>(0.9999999f, 2.0f * (fTemp23 / (fTemp16 * (fTemp17 + 1.0f)))));
			float fTemp25 = 1.0f - _MoogVcf_faustpower2_f(fTemp24);
			float fTemp26 = std::sqrt(std::max<float>(0.0f, fTemp25));
			fRec11[0] = fTemp21 * fTemp26 - fTemp24 * fRec11[1];
			fRec9[0] = fTemp21 * fTemp24 + fRec11[1] * fTemp26;
			float fRec10 = fRec11[0];
			float fTemp27 = 1.0f - fTemp23 / fTemp16;
			float fTemp28 = std::sqrt(fTemp19);
			float fTemp29 = 1.0f - fTemp17 - 2.0f * fTemp24 * fTemp27;
			float fTemp30 = fTemp28 * std::sqrt(fTemp25);
			float fTemp31 = fTemp1 * fTemp18 + fRec9[1] * fTemp20 + 2.0f * (fRec9[0] * fTemp27 / fTemp28) + fRec10 * fTemp29 / fTemp30;
			float fTemp32 = fSlow13 + ((fSlow17 + fTemp15) / fTemp14 + 1.0f - fSlow14);
			float fTemp33 = (fSlow13 + ((fTemp15 - fSlow17) / fTemp14 + 1.0f - fSlow14)) / fTemp32;
			float fTemp34 = std::max<float>(-0.9999999f, std::min<float>(0.9999999f, fTemp33));
			float fTemp35 = 1.0f - _MoogVcf_faustpower2_f(fTemp34);
			float fTemp36 = std::sqrt(std::max<float>(0.0f, fTemp35));
			float fTemp37 = fTemp31 * fTemp36 / fTemp16 - fTemp34 * fRec12[1];
			float fTemp38 = fSlow13 + (fTemp22 - fSlow14);
			float fTemp39 = std::max<float>(-0.9999999f, std::min<float>(0.9999999f, 2.0f * (fTemp38 / (fTemp32 * (fTemp33 + 1.0f)))));
			float fTemp40 = 1.0f - _MoogVcf_faustpower2_f(fTemp39);
			float fTemp41 = std::sqrt(std::max<float>(0.0f, fTemp40));
			fRec14[0] = fTemp37 * fTemp41 - fTemp39 * fRec14[1];
			fRec12[0] = fTemp37 * fTemp39 + fRec14[1] * fTemp41;
			float fRec13 = fRec14[0];
			float fTemp42 = 1.0f - fTemp38 / fTemp32;
			float fTemp43 = std::sqrt(fTemp35);
			float fTemp44 = 1.0f - fTemp33 - 2.0f * fTemp39 * fTemp42;
			float fTemp45 = fTemp43 * std::sqrt(fTemp40);
			output0[i0] = static_cast<FAUSTFLOAT>(((iSlow0) ? fTemp0 : fRec0[0] * ((iSlow2) ? ((iSlow6) ? (fTemp31 * fTemp34 / fTemp16 + fRec12[1] * fTemp36 + 2.0f * (fRec12[0] * fTemp42 / fTemp43) + fRec13 * fTemp44 / fTemp45) / fTemp32 : (fRec7[2] + fRec7[0] + 2.0f * fRec7[1]) / fTemp13) : fRec1[0])));
			float fTemp46 = static_cast<float>(input1[i0]);
			float fTemp47 = ((iSlow0) ? 0.0f : fTemp46);
			fRec19[0] = fTemp47 + fTemp3 * fRec19[1] - fSlow5 * fRec15[1];
			fRec18[0] = fRec19[0] + fTemp3 * fRec18[1];
			fRec17[0] = fRec18[0] + fTemp3 * fRec17[1];
			fRec16[0] = fRec17[0] + fTemp3 * fRec16[1];
			fRec15[0] = fRec16[0] * fTemp4;
			fRec21[0] = fTemp47 - (fTemp7 * fRec21[2] + 2.0f * fTemp9 * fRec21[1]) / fTemp10;
			fRec20[0] = (fRec21[2] + fRec21[0] + 2.0f * fRec21[1]) / fTemp10 - (fTemp11 * fRec20[2] + 2.0f * fTemp12 * fRec20[1]) / fTemp13;
			float fTemp48 = fTemp47 * fTemp20 - fTemp18 * fRec22[1];
			fRec24[0] = fTemp26 * fTemp48 - fTemp24 * fRec24[1];
			fRec22[0] = fTemp24 * fTemp48 + fTemp26 * fRec24[1];
			float fRec23 = fRec24[0];
			float fTemp49 = fTemp47 * fTemp18 + fTemp20 * fRec22[1] + 2.0f * (fRec22[0] * fTemp27 / fTemp28) + fRec23 * fTemp29 / fTemp30;
			float fTemp50 = fTemp36 * fTemp49 / fTemp16 - fTemp34 * fRec25[1];
			fRec27[0] = fTemp41 * fTemp50 - fTemp39 * fRec27[1];
			fRec25[0] = fTemp39 * fTemp50 + fTemp41 * fRec27[1];
			float fRec26 = fRec27[0];
			output1[i0] = static_cast<FAUSTFLOAT>(((iSlow0) ? fTemp46 : fRec0[0] * ((iSlow2) ? ((iSlow6) ? (fTemp34 * fTemp49 / fTemp16 + fTemp36 * fRec25[1] + 2.0f * (fRec25[0] * fTemp42 / fTemp43) + fRec26 * fTemp44 / fTemp45) / fTemp32 : (fRec20[2] + fRec20[0] + 2.0f * fRec20[1]) / fTemp13) : fRec15[0])));
			fRec0[1] = fRec0[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec11[1] = fRec11[0];
			fRec9[1] = fRec9[0];
			fRec14[1] = fRec14[0];
			fRec12[1] = fRec12[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec24[1] = fRec24[0];
			fRec22[1] = fRec22[0];
			fRec27[1] = fRec27[0];
			fRec25[1] = fRec25[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "MoogVcf.dsp"
	#define FAUST_CLASS_NAME "_MoogVcf"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _MoogVcf -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 6
	#define FAUST_PASSIVES 0

	FAUST_ADDCHECKBOX("MOOG VCF (Voltage Controlled Filter) [tooltip: See Faust's         vaeffects.lib for info and references]/[0]/Bypass", fCheckbox0);
	FAUST_ADDCHECKBOX("MOOG VCF (Voltage Controlled Filter) [tooltip: See Faust's         vaeffects.lib for info and references]/[0]/Use Biquads", fCheckbox1);
	FAUST_ADDCHECKBOX("MOOG VCF (Voltage Controlled Filter) [tooltip: See Faust's         vaeffects.lib for info and references]/[0]/Normalized Ladders", fCheckbox2);
	FAUST_ADDHORIZONTALSLIDER("MOOG VCF (Voltage Controlled Filter) [tooltip: See Faust's         vaeffects.lib for info and references]/Corner Frequency", fHslider1, 25.0f, 1.0f, 88.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("MOOG VCF (Voltage Controlled Filter) [tooltip: See Faust's         vaeffects.lib for info and references]/Corner Resonance", fHslider2, 0.9f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("MOOG VCF (Voltage Controlled Filter) [tooltip: See Faust's         vaeffects.lib for info and references]/VCF Output Level", fHslider0, 5.0f, -6e+01f, 2e+01f, 0.1f);

	#define FAUST_LIST_ACTIVES(p) \
		p(CHECKBOX, Bypass, "MOOG VCF (Voltage Controlled Filter) [tooltip: See Faust's         vaeffects.lib for info and references]/[0]/Bypass", fCheckbox0, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(CHECKBOX, Use_Biquads, "MOOG VCF (Voltage Controlled Filter) [tooltip: See Faust's         vaeffects.lib for info and references]/[0]/Use Biquads", fCheckbox1, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(CHECKBOX, Normalized_Ladders, "MOOG VCF (Voltage Controlled Filter) [tooltip: See Faust's         vaeffects.lib for info and references]/[0]/Normalized Ladders", fCheckbox2, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(HORIZONTALSLIDER, Corner_Frequency, "MOOG VCF (Voltage Controlled Filter) [tooltip: See Faust's         vaeffects.lib for info and references]/Corner Frequency", fHslider1, 25.0f, 1.0f, 88.0f, 0.01f) \
		p(HORIZONTALSLIDER, Corner_Resonance, "MOOG VCF (Voltage Controlled Filter) [tooltip: See Faust's         vaeffects.lib for info and references]/Corner Resonance", fHslider2, 0.9f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, VCF_Output_Level, "MOOG VCF (Voltage Controlled Filter) [tooltip: See Faust's         vaeffects.lib for info and references]/VCF Output Level", fHslider0, 5.0f, -6e+01f, 2e+01f, 0.1f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

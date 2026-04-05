/* ------------------------------------------------------------
author: "Julius Smith"
license: "MIT Style STK-4.2"
name: "compressor"
version: "0.0"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _mp3Compressor -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___mp3Compressor_H__
#define  ___mp3Compressor_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _mp3Compressor
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


struct _mp3Compressor final : public ::faust::dsp {
	
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fRec3[2];
	FAUSTFLOAT fHslider4;
	float fRec2[2];
	float fRec1[2];
	float fRec0[2];
	FAUSTFLOAT fHbargraph0;
	float fRec7[2];
	float fRec6[2];
	float fRec5[2];
	float fRec4[2];
	FAUSTFLOAT fHbargraph1;
	
	_mp3Compressor() {
	}
	
	_mp3Compressor(const _mp3Compressor&) = default;
	
	virtual ~_mp3Compressor() = default;
	
	_mp3Compressor& operator=(const _mp3Compressor&) = default;
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/amp_follower_ar:author", "Jonatan Liljedahl, revised by Romain Michon");
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.3.0");
		m->declare("author", "Julius Smith");
		m->declare("basics.lib/bypass1:author", "Julius Smith");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _mp3Compressor -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("compressors.lib/compression_gain_mono:author", "Julius O. Smith III");
		m->declare("compressors.lib/compression_gain_mono:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compression_gain_mono:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/compressor_lad_mono:author", "Julius O. Smith III");
		m->declare("compressors.lib/compressor_lad_mono:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compressor_lad_mono:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/compressor_mono:author", "Julius O. Smith III");
		m->declare("compressors.lib/compressor_mono:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compressor_mono:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/name", "Faust Compressor Effect Library");
		m->declare("compressors.lib/version", "1.6.0");
		m->declare("description", "Compressor demo application, adapted from the Faust Library's dm.compressor_demo in demos.lib");
		m->declare("documentation", "https://faustlibraries.grame.fr/libs/compressors/#cocompressor_mono");
		m->declare("filename", "mp3Compressor.dsp");
		m->declare("license", "MIT Style STK-4.2");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "compressor");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/onePoleSwitching:author", "Jonatan Liljedahl, revised by Dario Sanfilippo");
		m->declare("signals.lib/onePoleSwitching:licence", "STK-4.3");
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
		fConst0 = 1.0f / std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
	}
	
	void instanceResetUserInterface() {
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider0 = static_cast<FAUSTFLOAT>(2.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(2.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(4e+01f);
		fHslider3 = static_cast<FAUSTFLOAT>(15.0f);
		fHslider4 = static_cast<FAUSTFLOAT>(-24.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec3[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec2[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec0[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec7[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec6[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec5[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec4[l7] = 0.0f;
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
	
	_mp3Compressor* clone() {
		return new _mp3Compressor(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->declare(0, "tooltip", "References:                 https://faustlibraries.grame.fr/libs/compressors/                 http://en.wikipedia.org/wiki/Dynamic_range_compression");
		ui_interface->openVerticalBox("COMPRESSOR");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the compressor                 has no effect");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fHbargraph1, "1", "");
		ui_interface->declare(&fHbargraph1, "tooltip", "Compressor gain in dB");
		ui_interface->declare(&fHbargraph1, "unit", "dB");
		ui_interface->addHorizontalBargraph("Compressor Gain", &fHbargraph1, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fHbargraph0, "1", "");
		ui_interface->declare(&fHbargraph0, "tooltip", "Compressor gain in dB");
		ui_interface->declare(&fHbargraph0, "unit", "dB");
		ui_interface->addHorizontalBargraph("Compressor Gain", &fHbargraph0, FAUSTFLOAT(-5e+01f), FAUSTFLOAT(1e+01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("0x00");
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("Compression Control");
		ui_interface->declare(&fHslider1, "0", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "tooltip", "A compression Ratio of N means that for each N dB increase in input         signal level above Threshold, the output level goes up 1 dB");
		ui_interface->addHorizontalSlider("Ratio", &fHslider1, FAUSTFLOAT(2.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->declare(&fHslider4, "tooltip", "When the signal level exceeds the Threshold (in dB), its level         is compressed according to the Ratio");
		ui_interface->declare(&fHslider4, "unit", "dB");
		ui_interface->addHorizontalSlider("Threshold", &fHslider4, FAUSTFLOAT(-24.0f), FAUSTFLOAT(-1e+02f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openHorizontalBox("Compression Response");
		ui_interface->declare(&fHslider3, "1", "");
		ui_interface->declare(&fHslider3, "scale", "log");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->declare(&fHslider3, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain         to approach (exponentially) a new lower target level (the compression         `kicking in')");
		ui_interface->declare(&fHslider3, "unit", "ms");
		ui_interface->addHorizontalSlider("Attack", &fHslider3, FAUSTFLOAT(15.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider2, "2", "");
		ui_interface->declare(&fHslider2, "scale", "log");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->declare(&fHslider2, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain         to approach (exponentially) a new higher target level (the compression         'releasing')");
		ui_interface->declare(&fHslider2, "unit", "ms");
		ui_interface->addHorizontalSlider("Release", &fHslider2, FAUSTFLOAT(4e+01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(3e+03f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(&fHslider0, "5", "");
		ui_interface->declare(&fHslider0, "tooltip", "The compressed-signal output level is increased by this amount         (in dB) to make up for the level lost due to compression");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("MakeUpGain", &fHslider0, FAUSTFLOAT(2.0f), FAUSTFLOAT(-96.0f), FAUSTFLOAT(96.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		int iSlow0 = static_cast<int>(static_cast<float>(fCheckbox0));
		float fSlow1 = std::pow(1e+01f, 0.05f * std::max<float>(-96.0f, std::min<float>(96.0f, static_cast<float>(fHslider0))));
		float fSlow2 = 1.0f / std::max<float>(1.1920929e-07f, std::max<float>(1.0f, std::min<float>(2e+01f, static_cast<float>(fHslider1)))) + -1.0f;
		float fSlow3 = std::max<float>(fConst0, 0.001f * std::max<float>(1.0f, std::min<float>(3e+03f, static_cast<float>(fHslider2))));
		int iSlow4 = std::fabs(fSlow3) < 1.1920929e-07f;
		float fSlow5 = ((iSlow4) ? 0.0f : std::exp(-(fConst0 / ((iSlow4) ? 1.0f : fSlow3))));
		float fSlow6 = std::max<float>(fConst0, 0.001f * std::max<float>(1.0f, std::min<float>(1e+03f, static_cast<float>(fHslider3))));
		int iSlow7 = std::fabs(fSlow6) < 1.1920929e-07f;
		float fSlow8 = ((iSlow7) ? 0.0f : std::exp(-(fConst0 / ((iSlow7) ? 1.0f : fSlow6))));
		float fSlow9 = std::max<float>(-1e+02f, std::min<float>(1e+01f, static_cast<float>(fHslider4)));
		float fSlow10 = 0.5f * fSlow6;
		int iSlow11 = std::fabs(fSlow10) < 1.1920929e-07f;
		float fSlow12 = ((iSlow11) ? 0.0f : std::exp(-(fConst0 / ((iSlow11) ? 1.0f : fSlow10))));
		float fSlow13 = 1.0f - fSlow12;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			float fTemp1 = ((iSlow0) ? 0.0f : fTemp0);
			float fTemp2 = std::fabs(fTemp1);
			float fTemp3 = ((fTemp2 > fRec3[1]) ? fSlow8 : fSlow5);
			fRec3[0] = fTemp2 * (1.0f - fTemp3) + fRec3[1] * fTemp3;
			fRec2[0] = fSlow2 * std::max<float>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, fRec3[0])) - fSlow9, 0.0f) * fSlow13 + fSlow12 * fRec2[1];
			float fTemp4 = fTemp1 * std::pow(1e+01f, 0.05f * fRec2[0]);
			float fTemp5 = std::fabs(fTemp4);
			float fTemp6 = ((fTemp5 > fRec1[1]) ? fSlow8 : fSlow5);
			fRec1[0] = fTemp5 * (1.0f - fTemp6) + fRec1[1] * fTemp6;
			fRec0[0] = fSlow2 * std::max<float>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, fRec1[0])) - fSlow9, 0.0f) * fSlow13 + fSlow12 * fRec0[1];
			fHbargraph0 = static_cast<FAUSTFLOAT>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::pow(1e+01f, 0.05f * fRec0[0]))));
			output0[i0] = static_cast<FAUSTFLOAT>(((iSlow0) ? fTemp0 : fSlow1 * fTemp4));
			float fTemp7 = static_cast<float>(input1[i0]);
			float fTemp8 = ((iSlow0) ? 0.0f : fTemp7);
			float fTemp9 = std::fabs(fTemp8);
			float fTemp10 = ((fTemp9 > fRec7[1]) ? fSlow8 : fSlow5);
			fRec7[0] = fTemp9 * (1.0f - fTemp10) + fRec7[1] * fTemp10;
			fRec6[0] = fSlow2 * std::max<float>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, fRec7[0])) - fSlow9, 0.0f) * fSlow13 + fSlow12 * fRec6[1];
			float fTemp11 = fTemp8 * std::pow(1e+01f, 0.05f * fRec6[0]);
			float fTemp12 = std::fabs(fTemp11);
			float fTemp13 = ((fTemp12 > fRec5[1]) ? fSlow8 : fSlow5);
			fRec5[0] = fTemp12 * (1.0f - fTemp13) + fRec5[1] * fTemp13;
			fRec4[0] = fSlow2 * std::max<float>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, fRec5[0])) - fSlow9, 0.0f) * fSlow13 + fSlow12 * fRec4[1];
			fHbargraph1 = static_cast<FAUSTFLOAT>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, std::pow(1e+01f, 0.05f * fRec4[0]))));
			output1[i0] = static_cast<FAUSTFLOAT>(((iSlow0) ? fTemp7 : fSlow1 * fTemp11));
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "mp3Compressor.dsp"
	#define FAUST_CLASS_NAME "_mp3Compressor"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _mp3Compressor -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 6
	#define FAUST_PASSIVES 2

	FAUST_ADDCHECKBOX("COMPRESSOR [tooltip: References:                 https://faustlibraries.grame.fr/libs/compressors/                 http://en.wikipedia.org/wiki/Dynamic_range_compression]/[0]/Bypass", fCheckbox0);
	FAUST_ADDHORIZONTALBARGRAPH("COMPRESSOR [tooltip: References:                 https://faustlibraries.grame.fr/libs/compressors/                 http://en.wikipedia.org/wiki/Dynamic_range_compression]/[0]/Compressor Gain", fHbargraph1, -5e+01f, 1e+01f);
	FAUST_ADDHORIZONTALBARGRAPH("COMPRESSOR [tooltip: References:                 https://faustlibraries.grame.fr/libs/compressors/                 http://en.wikipedia.org/wiki/Dynamic_range_compression]/[0]/Compressor Gain", fHbargraph0, -5e+01f, 1e+01f);
	FAUST_ADDHORIZONTALSLIDER("COMPRESSOR [tooltip: References:                 https://faustlibraries.grame.fr/libs/compressors/                 http://en.wikipedia.org/wiki/Dynamic_range_compression]/[1]/[3] Compression Control/Ratio", fHslider1, 2.0f, 1.0f, 2e+01f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("COMPRESSOR [tooltip: References:                 https://faustlibraries.grame.fr/libs/compressors/                 http://en.wikipedia.org/wiki/Dynamic_range_compression]/[1]/[3] Compression Control/Threshold", fHslider4, -24.0f, -1e+02f, 1e+01f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("COMPRESSOR [tooltip: References:                 https://faustlibraries.grame.fr/libs/compressors/                 http://en.wikipedia.org/wiki/Dynamic_range_compression]/[1]/[4] Compression Response/Attack", fHslider3, 15.0f, 1.0f, 1e+03f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("COMPRESSOR [tooltip: References:                 https://faustlibraries.grame.fr/libs/compressors/                 http://en.wikipedia.org/wiki/Dynamic_range_compression]/[1]/[4] Compression Response/Release", fHslider2, 4e+01f, 1.0f, 3e+03f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("COMPRESSOR [tooltip: References:                 https://faustlibraries.grame.fr/libs/compressors/                 http://en.wikipedia.org/wiki/Dynamic_range_compression]/MakeUpGain", fHslider0, 2.0f, -96.0f, 96.0f, 0.1f);

	#define FAUST_LIST_ACTIVES(p) \
		p(CHECKBOX, Bypass, "COMPRESSOR [tooltip: References:                 https://faustlibraries.grame.fr/libs/compressors/                 http://en.wikipedia.org/wiki/Dynamic_range_compression]/[0]/Bypass", fCheckbox0, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(HORIZONTALSLIDER, Ratio, "COMPRESSOR [tooltip: References:                 https://faustlibraries.grame.fr/libs/compressors/                 http://en.wikipedia.org/wiki/Dynamic_range_compression]/[1]/[3] Compression Control/Ratio", fHslider1, 2.0f, 1.0f, 2e+01f, 0.1f) \
		p(HORIZONTALSLIDER, Threshold, "COMPRESSOR [tooltip: References:                 https://faustlibraries.grame.fr/libs/compressors/                 http://en.wikipedia.org/wiki/Dynamic_range_compression]/[1]/[3] Compression Control/Threshold", fHslider4, -24.0f, -1e+02f, 1e+01f, 0.1f) \
		p(HORIZONTALSLIDER, Attack, "COMPRESSOR [tooltip: References:                 https://faustlibraries.grame.fr/libs/compressors/                 http://en.wikipedia.org/wiki/Dynamic_range_compression]/[1]/[4] Compression Response/Attack", fHslider3, 15.0f, 1.0f, 1e+03f, 0.1f) \
		p(HORIZONTALSLIDER, Release, "COMPRESSOR [tooltip: References:                 https://faustlibraries.grame.fr/libs/compressors/                 http://en.wikipedia.org/wiki/Dynamic_range_compression]/[1]/[4] Compression Response/Release", fHslider2, 4e+01f, 1.0f, 3e+03f, 0.1f) \
		p(HORIZONTALSLIDER, MakeUpGain, "COMPRESSOR [tooltip: References:                 https://faustlibraries.grame.fr/libs/compressors/                 http://en.wikipedia.org/wiki/Dynamic_range_compression]/MakeUpGain", fHslider0, 2.0f, -96.0f, 96.0f, 0.1f) \

	#define FAUST_LIST_PASSIVES(p) \
		p(HORIZONTALBARGRAPH, Compressor_Gain, "COMPRESSOR [tooltip: References:                 https://faustlibraries.grame.fr/libs/compressors/                 http://en.wikipedia.org/wiki/Dynamic_range_compression]/[0]/Compressor Gain", fHbargraph1, 0.0, -5e+01f, 1e+01f, 0.0) \
		p(HORIZONTALBARGRAPH, Compressor_Gain, "COMPRESSOR [tooltip: References:                 https://faustlibraries.grame.fr/libs/compressors/                 http://en.wikipedia.org/wiki/Dynamic_range_compression]/[0]/Compressor Gain", fHbargraph0, 0.0, -5e+01f, 1e+01f, 0.0) \

#endif

#endif

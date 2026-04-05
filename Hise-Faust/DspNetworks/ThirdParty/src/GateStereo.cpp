/* ------------------------------------------------------------
name: "GateStereo"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _GateStereo -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___GateStereo_H__
#define  ___GateStereo_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _GateStereo
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


struct _GateStereo final : public ::faust::dsp {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	float fRec2[2];
	FAUSTFLOAT fHslider1;
	float fRec3[2];
	float fConst3;
	float fRec1[2];
	FAUSTFLOAT fHslider2;
	float fRec4[2];
	int iVec0[2];
	FAUSTFLOAT fHslider3;
	float fRec6[2];
	int iRec5[2];
	float fRec0[2];
	
	_GateStereo() {
	}
	
	_GateStereo(const _GateStereo&) = default;
	
	virtual ~_GateStereo() = default;
	
	_GateStereo& operator=(const _GateStereo&) = default;
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/amp_follower_ar:author", "Jonatan Liljedahl, revised by Romain Michon");
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.3.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _GateStereo -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "GateStereo.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("misceffects.lib/gate_gain_mono:author", "Julius O. Smith III");
		m->declare("misceffects.lib/gate_gain_mono:license", "STK-4.3");
		m->declare("misceffects.lib/gate_stereo:author", "Julius O. Smith III");
		m->declare("misceffects.lib/gate_stereo:license", "STK-4.3");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.5.1");
		m->declare("name", "GateStereo");
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
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 1.0f / fConst0;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(0.1f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider2 = static_cast<FAUSTFLOAT>(-6.0f);
		fHslider3 = static_cast<FAUSTFLOAT>(0.5f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec2[l0] = 0.0f;
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
			iVec0[l4] = 0;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec6[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			iRec5[l6] = 0;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec0[l7] = 0.0f;
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
	
	_GateStereo* clone() {
		return new _GateStereo(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("GateStereo");
		ui_interface->declare(&fHslider0, "01", "");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->addHorizontalSlider("Attack", &fHslider0, FAUSTFLOAT(0.1f), FAUSTFLOAT(1e-05f), FAUSTFLOAT(0.15f), FAUSTFLOAT(1e-05f));
		ui_interface->declare(&fHslider3, "01", "");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("Hold", &fHslider3, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.001f), FAUSTFLOAT(1.5f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider2, "01", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("Threshold", &fHslider2, FAUSTFLOAT(-6.0f), FAUSTFLOAT(-1.2e+02f), FAUSTFLOAT(6.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider1, "01", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("release", &fHslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.001f), FAUSTFLOAT(3.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst1 * std::max<float>(1e-05f, std::min<float>(0.15f, static_cast<float>(fHslider0)));
		float fSlow1 = fConst1 * std::max<float>(0.001f, std::min<float>(3.0f, static_cast<float>(fHslider1)));
		float fSlow2 = fConst1 * std::max<float>(-1.2e+02f, std::min<float>(6.0f, static_cast<float>(fHslider2)));
		float fSlow3 = fConst1 * std::max<float>(0.001f, std::min<float>(1.5f, static_cast<float>(fHslider3)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			float fTemp1 = static_cast<float>(input1[i0]);
			fRec2[0] = fSlow0 + fConst2 * fRec2[1];
			fRec3[0] = fSlow1 + fConst2 * fRec3[1];
			float fTemp2 = std::min<float>(fRec2[0], fRec3[0]);
			int iTemp3 = std::fabs(fTemp2) < 1.1920929e-07f;
			float fTemp4 = ((iTemp3) ? 0.0f : std::exp(-(fConst3 / ((iTemp3) ? 1.0f : fTemp2))));
			fRec1[0] = std::fabs(std::fabs(fTemp0) + std::fabs(fTemp1)) * (1.0f - fTemp4) + fRec1[1] * fTemp4;
			fRec4[0] = fSlow2 + fConst2 * fRec4[1];
			int iTemp5 = fRec1[0] > std::pow(1e+01f, 0.05f * fRec4[0]);
			iVec0[0] = iTemp5;
			fRec6[0] = fSlow3 + fConst2 * fRec6[1];
			iRec5[0] = std::max<int>((iTemp5 < iVec0[1]) * static_cast<int>(fConst0 * fRec6[0]), iRec5[1] + -1);
			float fTemp6 = std::fabs(std::max<float>(static_cast<float>(iTemp5), static_cast<float>(iRec5[0] > 0)));
			int iTemp7 = std::fabs(fRec3[0]) < 1.1920929e-07f;
			int iTemp8 = std::fabs(fRec2[0]) < 1.1920929e-07f;
			float fTemp9 = ((fTemp6 > fRec0[1]) ? ((iTemp8) ? 0.0f : std::exp(-(fConst3 / ((iTemp8) ? 1.0f : fRec2[0])))) : ((iTemp7) ? 0.0f : std::exp(-(fConst3 / ((iTemp7) ? 1.0f : fRec3[0])))));
			fRec0[0] = fTemp6 * (1.0f - fTemp9) + fRec0[1] * fTemp9;
			output0[i0] = static_cast<FAUSTFLOAT>(fTemp0 * fRec0[0]);
			output1[i0] = static_cast<FAUSTFLOAT>(fTemp1 * fRec0[0]);
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec1[1] = fRec1[0];
			fRec4[1] = fRec4[0];
			iVec0[1] = iVec0[0];
			fRec6[1] = fRec6[0];
			iRec5[1] = iRec5[0];
			fRec0[1] = fRec0[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "GateStereo.dsp"
	#define FAUST_CLASS_NAME "_GateStereo"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _GateStereo -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 4
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Attack", fHslider0, 0.1f, 1e-05f, 0.15f, 1e-05f);
	FAUST_ADDHORIZONTALSLIDER("Hold", fHslider3, 0.5f, 0.001f, 1.5f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("Threshold", fHslider2, -6.0f, -1.2e+02f, 6.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("release", fHslider1, 0.5f, 0.001f, 3.0f, 0.001f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Attack, "Attack", fHslider0, 0.1f, 1e-05f, 0.15f, 1e-05f) \
		p(HORIZONTALSLIDER, Hold, "Hold", fHslider3, 0.5f, 0.001f, 1.5f, 0.001f) \
		p(HORIZONTALSLIDER, Threshold, "Threshold", fHslider2, -6.0f, -1.2e+02f, 6.0f, 0.01f) \
		p(HORIZONTALSLIDER, release, "release", fHslider1, 0.5f, 0.001f, 3.0f, 0.001f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

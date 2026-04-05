/* ------------------------------------------------------------
name: "Bitcrush"
Code generated with Faust 2.83.1 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _Bitcrush -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___Bitcrush_H__
#define  ___Bitcrush_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _Bitcrush
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


struct _Bitcrush final : public ::faust::dsp {
	
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	int iRec1[2];
	float fRec0[2];
	float fRec2[2];
	int fSampleRate;
	
	_Bitcrush() {
	}
	
	_Bitcrush(const _Bitcrush&) = default;
	
	virtual ~_Bitcrush() = default;
	
	_Bitcrush& operator=(const _Bitcrush&) = default;
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _Bitcrush -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "Bitcrush.dsp");
		m->declare("name", "Bitcrush");
		m->declare("spats.lib/name", "Faust Spatialization Library");
		m->declare("spats.lib/version", "1.2.1");
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
	}
	
	void instanceResetUserInterface() {
		fVslider0 = static_cast<FAUSTFLOAT>(1.0f);
		fVslider1 = static_cast<FAUSTFLOAT>(16.0f);
		fVslider2 = static_cast<FAUSTFLOAT>(1.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iRec1[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec2[l2] = 0.0f;
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
	
	_Bitcrush* clone() {
		return new _Bitcrush(*this);
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Bitcrush");
		ui_interface->addVerticalSlider("Bits", &fVslider1, FAUSTFLOAT(16.0f), FAUSTFLOAT(0.1f), FAUSTFLOAT(16.0f), FAUSTFLOAT(0.01f));
		ui_interface->addVerticalSlider("Downsampling Factor", &fVslider2, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(8e+01f), FAUSTFLOAT(1.0f));
		ui_interface->addVerticalSlider("Mix", &fVslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = std::max<float>(0.0f, std::min<float>(1.0f, static_cast<float>(fVslider0)));
		float fSlow1 = std::pow(2.0f, std::max<float>(0.1f, std::min<float>(16.0f, static_cast<float>(fVslider1))));
		float fSlow2 = fSlow0 / fSlow1;
		int iSlow3 = static_cast<int>(std::max<float>(1.0f, std::min<float>(8e+01f, static_cast<float>(fVslider2))));
		int iSlow4 = iSlow3 > 1;
		int iSlow5 = iSlow3 + -1;
		float fSlow6 = 1.0f - fSlow0;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			iRec1[0] = ((iRec1[1] < iSlow5) ? iRec1[1] + 1 : 0);
			int iTemp1 = iRec1[0] == 0;
			fRec0[0] = ((iTemp1) ? fTemp0 : fRec0[1]);
			output0[i0] = static_cast<FAUSTFLOAT>(fSlow2 * std::rint(fSlow1 * ((iSlow4) ? fRec0[0] : fTemp0)) + fSlow6 * fTemp0);
			float fTemp2 = static_cast<float>(input1[i0]);
			fRec2[0] = ((iTemp1) ? fTemp2 : fRec2[1]);
			output1[i0] = static_cast<FAUSTFLOAT>(fSlow2 * std::rint(fSlow1 * ((iSlow4) ? fRec2[0] : fTemp2)) + fSlow6 * fTemp2);
			iRec1[1] = iRec1[0];
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "Bitcrush.dsp"
	#define FAUST_CLASS_NAME "_Bitcrush"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -fpga-mem-th 4 -rui -nvi -ct 1 -cn _Bitcrush -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 3
	#define FAUST_PASSIVES 0

	FAUST_ADDVERTICALSLIDER("Bits", fVslider1, 16.0f, 0.1f, 16.0f, 0.01f);
	FAUST_ADDVERTICALSLIDER("Downsampling Factor", fVslider2, 1.0f, 1.0f, 8e+01f, 1.0f);
	FAUST_ADDVERTICALSLIDER("Mix", fVslider0, 1.0f, 0.0f, 1.0f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(VERTICALSLIDER, Bits, "Bits", fVslider1, 16.0f, 0.1f, 16.0f, 0.01f) \
		p(VERTICALSLIDER, Downsampling_Factor, "Downsampling Factor", fVslider2, 1.0f, 1.0f, 8e+01f, 1.0f) \
		p(VERTICALSLIDER, Mix, "Mix", fVslider0, 1.0f, 0.0f, 1.0f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif

/* ========================================
 *  PeaksOnly - PeaksOnly.h
 *  Copyright (c) 2016 airwindows, Airwindows uses the MIT license
 * ======================================== */

#ifndef __PeaksOnly_H
#include "PeaksOnly.h"
#endif

AudioEffect* createEffectInstance(audioMasterCallback audioMaster) {return new PeaksOnly(audioMaster);}

PeaksOnly::PeaksOnly(audioMasterCallback audioMaster) :
    AudioEffectX(audioMaster, kNumPrograms, kNumParameters)
{
	A = 1.0;
	smoothStages = 16.0;

	for (int s = 0; s < kMaxAP; ++s)
	{
		apX[s] = 1;
		for (int i = 0; i < kAPBufSize; ++i)
		{
			apL[s][i] = 0.0;
			apR[s][i] = 0.0;
		}
	}

	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;

    _canDo.insert("plugAsChannelInsert");
    _canDo.insert("plugAsSend");
    _canDo.insert("x2in2out"); 
    setNumInputs(kNumInputs);
    setNumOutputs(kNumOutputs);
    setUniqueID(kUniqueId);
    canProcessReplacing();
    canDoubleReplacing();
	programsAreChunks(true);
    vst_strncpy (_programName, "Default", kVstMaxProgNameLen);
}

PeaksOnly::~PeaksOnly() {}
VstInt32 PeaksOnly::getVendorVersion () {return 1000;}
void PeaksOnly::setProgramName(char *name) {vst_strncpy (_programName, name, kVstMaxProgNameLen);}
void PeaksOnly::getProgramName(char *name) {vst_strncpy (name, _programName, kVstMaxProgNameLen);}

void PeaksOnly::setParameter(VstInt32 index, float value) {
	switch (index)
	{
		case kParamA:
			A = value;
			if (A < 0.0) A = 0.0;
			if (A > 1.0) A = 1.0;
			break;
		default:
			break;
	}
}

float PeaksOnly::getParameter(VstInt32 index) {
	switch (index)
	{
		case kParamA: return (float)A;
		default: return 0.0f;
	}
}

void PeaksOnly::getParameterName(VstInt32 index, char *text) {
	switch (index)
	{
		case kParamA: vst_strncpy(text, "Stages", kVstMaxParamStrLen); break;
		default: vst_strncpy(text, "", kVstMaxParamStrLen); break;
	}
}

void PeaksOnly::getParameterDisplay(VstInt32 index, char *text) {
	switch (index)
	{
		case kParamA:
		{
			int stages = 1 + (int)floor((A * 15.0) + 0.5);
			if (stages < 1) stages = 1;
			if (stages > 16) stages = 16;
			char temp[16];
			sprintf(temp, "%d", stages);
			vst_strncpy(text, temp, kVstMaxParamStrLen);
			break;
		}
		default:
			vst_strncpy(text, "", kVstMaxParamStrLen);
			break;
	}
}

void PeaksOnly::getParameterLabel(VstInt32 index, char *text) {
	switch (index)
	{
		case kParamA: vst_strncpy(text, "", kVstMaxParamStrLen); break;
		default: vst_strncpy(text, "", kVstMaxParamStrLen); break;
	}
}

VstInt32 PeaksOnly::canDo(char *text) 
{ return (_canDo.find(text) == _canDo.end()) ? -1: 1; }

bool PeaksOnly::getEffectName(char* name) {
    vst_strncpy(name, "PeaksOnly", kVstMaxProductStrLen); return true;
}

VstPlugCategory PeaksOnly::getPlugCategory() {return kPlugCategEffect;}

bool PeaksOnly::getProductString(char* text) {
  	vst_strncpy (text, "airwindows PeaksOnly", kVstMaxProductStrLen); return true;
}

bool PeaksOnly::getVendorString(char* text) {
  	vst_strncpy (text, "airwindows", kVstMaxVendorStrLen); return true;
}

/* ========================================
 *  PeaksOnly - PeaksOnly.h
 *  Copyright (c) 2016 airwindows, Airwindows uses the MIT license
 * ======================================== */

#ifndef __PeaksOnly_H
#include "PeaksOnly.h"
#endif

void PeaksOnly::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) 
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();

	static const int primes[kMaxAP] = {
		149, 179, 191, 223, 257, 293, 337, 383,
		431, 479, 523, 577, 631, 683, 739, 797
	};

	int apM[kMaxAP];
	for (int s = 0; s < kMaxAP; ++s)
	{
		int m = (int)((double)primes[s] * overallscale);
		if (m < 1) m = 1;
		if (m > (kAPBufSize - 1)) m = (kAPBufSize - 1);
		apM[s] = m;
	}

    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;

		if (inputSampleL > 1.0) inputSampleL = 1.0;
		if (inputSampleL < -1.0) inputSampleL = -1.0;
		if (inputSampleR > 1.0) inputSampleR = 1.0;
		if (inputSampleR < -1.0) inputSampleR = -1.0;
		inputSampleL = asin(inputSampleL);
		inputSampleR = asin(inputSampleR);

		double tapL[17];
		double tapR[17];
		tapL[0] = inputSampleL;
		tapR[0] = inputSampleR;

		for (int s = 0; s < kMaxAP; ++s)
		{
			int allpasstemp = apX[s] - 1;
			if (allpasstemp < 0 || allpasstemp > apM[s]) allpasstemp = apM[s];

			double xL = tapL[s];
			double xR = tapR[s];

			xL -= apL[s][allpasstemp] * 0.5;
			xR -= apR[s][allpasstemp] * 0.5;

			apL[s][apX[s]] = xL;
			apR[s][apX[s]] = xR;

			xL *= 0.5;
			xR *= 0.5;

			apX[s]--;
			if (apX[s] < 0 || apX[s] > apM[s]) {apX[s] = apM[s];}

			xL += apL[s][apX[s]];
			xR += apR[s][apX[s]];

			if (xL > 1.0) xL = 1.0;
			if (xL < -1.0) xL = -1.0;
			if (xR > 1.0) xR = 1.0;
			if (xR < -1.0) xR = -1.0;
			xL = asin(xL);
			xR = asin(xR);

			tapL[s+1] = xL;
			tapR[s+1] = xR;
		}

		double targetStages = 1.0 + (A * 15.0);
		if (targetStages < 1.0) targetStages = 1.0;
		if (targetStages > 16.0) targetStages = 16.0;

		smoothStages = (smoothStages * 0.995) + (targetStages * 0.005);
		if (smoothStages < 1.0) smoothStages = 1.0;
		if (smoothStages > 16.0) smoothStages = 16.0;

		int k = (int)floor(smoothStages);
		double frac = smoothStages - (double)k;

		if (k >= 16)
		{
			inputSampleL = tapL[16];
			inputSampleR = tapR[16];
		}
		else
		{
			inputSampleL = tapL[k] * (1.0 - frac) + tapL[k+1] * frac;
			inputSampleR = tapR[k] * (1.0 - frac) + tapR[k+1] * frac;
		}

		inputSampleL *= 0.63679;
		inputSampleR *= 0.63679;

		int expon; frexpf((float)inputSampleL, &expon);
		fpdL ^= fpdL << 13; fpdL ^= fpdL >> 17; fpdL ^= fpdL << 5;
		inputSampleL += ((double(fpdL)-uint32_t(0x7fffffff)) * 5.5e-36l * pow(2,expon+62));
		frexpf((float)inputSampleR, &expon);
		fpdR ^= fpdR << 13; fpdR ^= fpdR >> 17; fpdR ^= fpdR << 5;
		inputSampleR += ((double(fpdR)-uint32_t(0x7fffffff)) * 5.5e-36l * pow(2,expon+62));

		*out1 = (float)inputSampleL;
		*out2 = (float)inputSampleR;

		in1++;
		in2++;
		out1++;
		out2++;
    }
}

void PeaksOnly::processDoubleReplacing(double **inputs, double **outputs, VstInt32 sampleFrames) 
{
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];

	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();

	static const int primes[kMaxAP] = {
		149, 179, 191, 223, 257, 293, 337, 383,
		431, 479, 523, 577, 631, 683, 739, 797
	};

	int apM[kMaxAP];
	for (int s = 0; s < kMaxAP; ++s)
	{
		int m = (int)((double)primes[s] * overallscale);
		if (m < 1) m = 1;
		if (m > (kAPBufSize - 1)) m = (kAPBufSize - 1);
		apM[s] = m;
	}

    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;

		if (inputSampleL > 1.0) inputSampleL = 1.0;
		if (inputSampleL < -1.0) inputSampleL = -1.0;
		if (inputSampleR > 1.0) inputSampleR = 1.0;
		if (inputSampleR < -1.0) inputSampleR = -1.0;
		inputSampleL = asin(inputSampleL);
		inputSampleR = asin(inputSampleR);

		double tapL[17];
		double tapR[17];
		tapL[0] = inputSampleL;
		tapR[0] = inputSampleR;

		for (int s = 0; s < kMaxAP; ++s)
		{
			int allpasstemp = apX[s] - 1;
			if (allpasstemp < 0 || allpasstemp > apM[s]) allpasstemp = apM[s];

			double xL = tapL[s];
			double xR = tapR[s];

			xL -= apL[s][allpasstemp] * 0.5;
			xR -= apR[s][allpasstemp] * 0.5;

			apL[s][apX[s]] = xL;
			apR[s][apX[s]] = xR;

			xL *= 0.5;
			xR *= 0.5;

			apX[s]--;
			if (apX[s] < 0 || apX[s] > apM[s]) {apX[s] = apM[s];}

			xL += apL[s][apX[s]];
			xR += apR[s][apX[s]];

			if (xL > 1.0) xL = 1.0;
			if (xL < -1.0) xL = -1.0;
			if (xR > 1.0) xR = 1.0;
			if (xR < -1.0) xR = -1.0;
			xL = asin(xL);
			xR = asin(xR);

			tapL[s+1] = xL;
			tapR[s+1] = xR;
		}

		double targetStages = 1.0 + (A * 15.0);
		if (targetStages < 1.0) targetStages = 1.0;
		if (targetStages > 16.0) targetStages = 16.0;

		smoothStages = (smoothStages * 0.995) + (targetStages * 0.005);
		if (smoothStages < 1.0) smoothStages = 1.0;
		if (smoothStages > 16.0) smoothStages = 16.0;

		int k = (int)floor(smoothStages);
		double frac = smoothStages - (double)k;

		if (k >= 16)
		{
			inputSampleL = tapL[16];
			inputSampleR = tapR[16];
		}
		else
		{
			inputSampleL = tapL[k] * (1.0 - frac) + tapL[k+1] * frac;
			inputSampleR = tapR[k] * (1.0 - frac) + tapR[k+1] * frac;
		}

		inputSampleL *= 0.63679;
		inputSampleR *= 0.63679;

		fpdL ^= fpdL << 13; fpdL ^= fpdL >> 17; fpdL ^= fpdL << 5;
		fpdR ^= fpdR << 13; fpdR ^= fpdR >> 17; fpdR ^= fpdR << 5;

		*out1 = inputSampleL;
		*out2 = inputSampleR;

		in1++;
		in2++;
		out1++;
		out2++;
    }
}

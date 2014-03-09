#include "Tremolo.h"
#include "MyLFO.h"

CTremolo::CTremolo()
{
	this->reset();
}

void CTremolo::create(CTremolo*& pCTremolo)
{
	pCTremolo = new CTremolo();
}

void CTremolo::init(float sampleRate, int numChannels, float depth, float rate)
{
	setSampleRate(sampleRate);
	setChanNum(numChannels);
	setDepth(depth);

	LFO = new CMyLFO(sampleRate);

	setRate(rate);
}

void CTremolo::setType(CMyLFO::LFO_Type type)
{
	LFO->setLFOType(type);
}

void CTremolo::setSampleRate(int smplRate)
{
	if (smplRate >0)
		sampleRate = smplRate;
}

void CTremolo::setChanNum(int numChan)
{
	if (numChan >= 1)
		numChannels = numChan;
}

void CTremolo::setDepth(float dpth)
{
	if (dpth >= 0)
	{
		if (dpth <= 1)
		{
			depth = dpth;
		};
	};
}

void CTremolo::setRate(float rateInHz)
{
	LFO->setFrequencyinHz(rateInHz);
}

float ** CTremolo::process(float **inputBuffer, float **outputBuffer, int numFrames)
{
	// generate the LFO:
	LFO->generate(numFrames);

	// for each channel, for each sample:
	for (int i = 0; i < numFrames; i++)
	{
		for (int c = 0; c < numChannels; c++)
		{	
			//outputBuffer[c][i] = 0.5 + 0.5*getDepth()*LFO->getLFOSampleData(i)*(inputBuffer[c][i]);
			outputBuffer[c][i] = (1 + getDepth()*LFO->getLFOSampleData(i))*(inputBuffer[c][i]);
		};
	};

	return outputBuffer;
}

int CTremolo::getSampleRate()
{
	return sampleRate;
}

float CTremolo::getDepth()
{
	return depth;
}

float CTremolo::getRate()
{
	return rate;
}

void CTremolo::reset()
{
}
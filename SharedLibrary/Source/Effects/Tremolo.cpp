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
//	setDepth(depth);
	setParam(1,depth);
	LFO = new CMyLFO(sampleRate);

	setParam(2, rate);
//	setRate(rate);
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

void CTremolo::setParam(/*hFile::enumType type*/ int type, float value)
{
	switch(type)
	{
		case 0:
			depth_target	= value;
		break;
		case 1:
			rate_target		= value;
		break;
	};
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

void CTremolo::process(float **inputBuffer, int numFrames, bool bypass)
{

	// generate the LFO:
	LFO->generate(numFrames);

	// for each channel, for each sample:
	for (int i = 0; i < numFrames; i++)
	{
		for (int c = 0; c < numChannels; c++)
		{	
			inputBuffer[c][i] = (1 + getParam(0)*LFO->getLFOSampleData(i))*(inputBuffer[c][i]);
		};
	};
}

int CTremolo::getSampleRate()
{
	return sampleRate;
}

float CTremolo::getParam(/*hFile::enumType type*/ int type)
{
	switch(type)
	{
		case 0:
			return depth;
		break;
		case 1:
			return rate;
		break;
	};
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
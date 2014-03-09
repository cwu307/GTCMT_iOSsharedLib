#include "Delay.h"

CDelay::CDelay()
{
	this->reset();
};

void CDelay::create(CDelay*& pCDelay)
{
	pCDelay = new CDelay();
};

void CDelay::init(float sampleRate, int numChannels, float maxDelayInS, float delayInS, float mix, float fdBack)
{
	setSampleRate(sampleRate);
	setMaxDelay(maxDelayInS);
	setChanNum(numChannels);
	setWetDry(mix);
	setFeedback(fdBack);

	ringBuffer = new CRingBuffer<float> *[numChannels];

	for (int n = 0; n < numChannels; n++)
	{
		ringBuffer[n]	= new CRingBuffer<float>(2*(int)(maxDelayInS*sampleRate));	
		// set indices and buffer contents to zero:
		ringBuffer[n]->resetInstance();
	};

	setDelayTime(delayInS);
};

void CDelay::setSampleRate(int smplRate)
{
	if (smplRate >0)
		sampleRate = smplRate;
};

void CDelay::setChanNum(int numChan)
{
	if (numChan >= 1)
		numChannels = numChan;
};

void CDelay::setDelayTime(float delay)
{
	if (delay >= 0)
	{
		if (delay <= getMaxDelay())
		{
			delayTime = delay;
			// set the read index of each ring buffer to the correct index:
			for (int n = 0; n < numChannels; n++)
				ringBuffer[n]->setReadIdx(-(int)((delay/getMaxDelay())*getSampleRate()));
		};
	};
};

void CDelay::setWetDry(float mix)
{
	if (abs(mix) <= 1)
		wetDry = mix;
};

void CDelay::setFeedback(float fdBack)
{
	if (fdBack >= 0 && fdBack <= 1)
		feedBack = fdBack;
};

void CDelay::setMaxDelay(float delayTimeInS)
{
	if (delayTimeInS > 0)
		maxDelayTimeInS = delayTimeInS;
};

float ** CDelay::process(float **inputBuffer, float **outputBuffer, int numFrames)
{
	// for each channel, for each sample:
	for (int i = 0; i < numFrames; i++)
	{
		for (int c = 0; c < numChannels; c++)
		{	
			// ugly looking equation for fractional delay:
			outputBuffer[c][i] =	(1-getWetDry())*(inputBuffer[c][i]) 
									+ getFeedback()*getWetDry()*((ringBuffer[c]->getPostInc())*(getDelay()*getSampleRate()-(int)(getDelay()*getSampleRate()))
									+ (ringBuffer[c]->get())*(1-getDelay()*getSampleRate()+(int)(getDelay()*getSampleRate())));

			// outputBuffer[c][i] =	(1-getWetDry())*(inputBuffer[c][i])
			//						 + 0.5*getWetDry()*(ringBuffer[c]->getPostInc());

			// add the output value to the ring buffer:
			ringBuffer[c]->putPostInc(outputBuffer[c][i]);
		};
	};

	return outputBuffer;
};

int CDelay::getSampleRate()
{
	return sampleRate;
};

float CDelay::getWetDry()
{
	return wetDry;
};

float CDelay::getDelay()
{
	return delayTime;
};

float CDelay::getFeedback()
{
	return feedBack;
};

float CDelay::getMaxDelay()
{
	return maxDelayTimeInS;
};

void CDelay::reset()
{
		for (int c = 0; c < numChannels; c++)
		{	
			ringBuffer[c]->resetInstance();
		};
};
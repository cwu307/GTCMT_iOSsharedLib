#if !defined(__Delay_hdr__)
#define __Delay_hdr__

#include "RingBuffer.h"

// fractional delay line, IIR
class CDelay
{
public:
	// constructor
	CDelay(float sampleRate, int numChannels, float maxDelayInS, float delay, float mix);
	// set
	void setSampleRate(int sampleRate);
	void setChanNum(int numChan);
	void setDelayFeedback(float feedback);
	void setDelayTime(float delay);
	void setWetDry(float mix);
	void setMaxDelay(float delay);
	// get
	float getMaxDelay();
	float getWetDry();
	float getDelay();
	int getSampleRate();
	//process
	float ** process(float** inputBuffer, float **outputBuffer, int numFrames);

	virtual ~CDelay () {};

protected:

private:

	CRingBuffer<float> **ringBuffer;

	int sampleRate;
	int numChannels;

	float feedback;
	float wetDry;
	float delayTime;
	float maxDelayTimeInS;
};

#endif

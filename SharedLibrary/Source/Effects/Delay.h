#if !defined(__CDelay_hdr__)
#define __CDelay_hdr__

#include "RingBuffer.h"

/*	Fractional Delay
	----------------
	Paramaters:	
		- Delay time
		- Feedback
		- Wet/Dry Mix
*/

class CDelay
{
public:

	CDelay();

	static void create(CDelay*& pCDelay);
	void init(float sampleRate, int numChannels, float maxDelayInS, float delayInS, float mix, float fdBack);
	// set:
	void setParam(/*hFile::enumType type*/ int type, float value);

	void setSampleRate(int sampleRate);
	void setChanNum(int numChan);
	void setDelayFeedback(float feedback);
	void setDelayTime(float delay);
	void setWetDry(float mix);
	void setMaxDelay(float delay);
	void setFeedback(float fdBack);
	
	// get:
	float CDelay::getParam(/*hFile::enumType type*/ int type);

	float getMaxDelay();
	float getWetDry();
	float getDelay();
	float getFeedback();
	int   getSampleRate();
	// process:
	void process(float **inputBuffer, int numFrames, bool bypass);

	void reset();
	virtual ~CDelay () {};

private:

	CRingBuffer<float> **ringBuffer;

	int sampleRate;
	int numChannels;

	float feedBack;
	float wetDry;
	float delayTime;
	float maxDelayTimeInS;

	float feedBack_target;
	float wetDry_target;
	float delayTime_target;
};

#endif

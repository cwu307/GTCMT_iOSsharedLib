#if !defined(__Tremolo_hdr__)
#define __Tremolo_hdr__

#include "MyLFO.h"

/*	Tremolo
	----------------
	Paramaters:	
		- Depth
		- Rate
*/

class CTremolo
{
public:

	CTremolo();

	static void create(CTremolo*& pCTremolo);
	void init(float sampleRate, int numChannels, float depth, float rate);
	// set:
	void setSampleRate(int sampleRate);
	void setChanNum(int numChan);
	void setDepth(float depth);
	void setRate(float rate);
	void setType(CMyLFO::LFO_Type type);
	// get:
	float getDepth();
	float getRate();
	int   getSampleRate();
	// process:
	float ** process(float **inputBuffer, float **outputBuffer, int numFrames);

	void reset();
	virtual ~CTremolo () {};

private:

	CMyLFO *LFO;

	int sampleRate;
	int numChannels;

	float depth;
	float rate;

};

#endif

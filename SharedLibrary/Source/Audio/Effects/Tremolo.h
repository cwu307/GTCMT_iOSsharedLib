#if !defined(__Tremolo_hdr__)
#define __Tremolo_hdr__

#include "LFO.h"

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
	void setParam(/*hFile::enumType type*/ int type, float value);

	void setSampleRate(int sampleRate);
	void setChanNum(int numChan);
	void setType(CLFO::LFO_Type type);


	void setDepth(float depth);
	void setRate(float rate);
	
	// get:
	float getParam(/*hFile::enumType type*/ int type);
	int   getSampleRate();


	float getDepth();
	float getRate();

	// process:
	void process(float **inputBuffer, int numFrames, bool bypass);

	void reset();
	virtual ~CTremolo () {};

private:

	CLFO *LFO;

	int sampleRate;
	int numChannels;

	float depth;
	float rate;

	float depth_target;
	float rate_target;

};

#endif

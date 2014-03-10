#if !defined(__Wah_hdr__)
#define __Wah_hdr__

#include <Math.h>

/*	Wah
	----------------
	Paramaters:	
		- Gain
		- Theta "Pedal Value"
*/

class CWah
{
public:

	CWah(int NumChannels);
	~CWah ();

	// set:
	void setParam(/*hFile::enumType type*/ int type, float value);
	// get:
	float getParam(/*hFile::enumType type*/ int type);
	void prepareToPlay(float sampleRate);

	void initDefaults();

	// process:
	void process(float **inputBuffer, int numFrames, bool bypass);

private:

	float **buff;

	float m_fSampleRate;
	int   m_iNumChannels;

	float m_fGain;
	float m_fTheta;		// pedal value

	float m_fReso;
	float m_fQ;

	float m_fPoleAngle;

	float m_fFrn;

	float m_fCoeff2;
	float m_fCoeff3;
};

#endif

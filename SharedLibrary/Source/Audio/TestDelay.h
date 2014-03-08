//
//  TestDelay.h
//  SharedLibrary
//
//  Created by Govinda Ram Pingali on 3/8/14.
//  Copyright (c) 2014 GTCMT. All rights reserved.
//

#ifndef __SharedLibrary__TestDelay__
#define __SharedLibrary__TestDelay__

#include "RingBuffer.h"


class TestDelay
{
    
    
public:
    
    
    TestDelay (int iNumChannels, int fSampleRate);
    ~TestDelay();

    
    enum FilterType
    {
        k_FIR = 0,
        k_IIR = 1
    };
    
    
    //--- Set and Get Sampling Frequency ---//
    void setFsInHz(float current_Fs);
    float getFsInHz();
    
    
    //--- Set and Get Delay Time in ms ---//
    void setDelayTime_ms(float current_delay_time_ms);
    float getDelayTime_ms();
    
    
    
    //--- Set and Get Delay Gain ---//
    void setDelayLine_gain(float current_delay_line_gain);
    float getDelayLine_gain();
    
    
    
    //--- Set and Get Input Gain ---//
    void setInput_gain(float current_input_gain);
    float getInput_gain();
    
    
    
    //--- Set and Get Filter Type ---//
    void setFilterType(FilterType current_filter_type );
    FilterType getFilterType();
    
    
    
    //--- Get Max Allowed Time Delay in ms ---//
    float getMaxDelayTime_ms();
    
    
    //--- Main Filter Process Method ---//
    void process(float** audioBuffer, int blockSize, bool bypassState);
    
    
    
private:
    
    float       m_Fs;
    float       m_fDelay_Time_ms;
    float       m_fDelay_line_gain;
    float       m_fInput_gain;
    float       m_fMax_Delay_Time_ms;
    int         m_iMax_Delay_Time_Samples;
    long        m_iDelay_Time_Samples;
    int         m_iNumChannels;
    FilterType  m_FilterType;
    
    
    void convertDelayTimeToSamples();
    
    void initializeDefaultParameters();

    CRingBuffer<float>** m_CRingBuffer;
    
};

#endif /* defined(__SharedLibrary__TestDelay__) */

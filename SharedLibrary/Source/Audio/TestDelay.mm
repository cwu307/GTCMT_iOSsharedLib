//
//  TestDelay.cpp
//  SharedLibrary
//
//  Created by Govinda Ram Pingali on 3/8/14.
//  Copyright (c) 2014 GTCMT. All rights reserved.
//

#include "TestDelay.h"


TestDelay::TestDelay(int iNumChannels, int fSampleRate)     :   m_Fs(fSampleRate),
                                                                m_fDelay_Time_ms(0),
                                                                m_fDelay_line_gain(0),
                                                                m_fMax_Delay_Time_ms(0),
                                                                m_iMax_Delay_Time_Samples(0),
                                                                m_iDelay_Time_Samples(0),
                                                                m_iNumChannels(iNumChannels)
{
    
    //-- Assert Sampling Frequency and Number of Channels > 0 --//
    assert(m_Fs > 0);
    assert(m_iNumChannels > 0);
    
    //-- Setting Maximum Delay Time to 4 seconds --//
    m_fMax_Delay_Time_ms = 4000;
    
    //-- Converting Max Delay Time to Samples --//
    m_iMax_Delay_Time_Samples = m_fMax_Delay_Time_ms * m_Fs / 1000;
    
    //-- Setting Default Filter Type to FIR --//
    m_FilterType = k_IIR;
    
    
    //-- Initialize Array of Ring Buffers (one per channel) --//
    m_CRingBuffer = new CRingBuffer<float>*;
    for (int channel=0; channel<m_iNumChannels; channel++) {
        m_CRingBuffer[channel] = new CRingBuffer<float>(m_iMax_Delay_Time_Samples);
    }
    
    
    initializeDefaultParameters();
}


TestDelay::~TestDelay()
{
    delete [] m_CRingBuffer;
}



void TestDelay::setFsInHz(float current_Fs)
{
    m_Fs = current_Fs;
}


float TestDelay::getFsInHz()
{
    return m_Fs;
}



void TestDelay::setDelayTime_ms(float current_delay_time_ms)
{
    assert(current_delay_time_ms < m_fMax_Delay_Time_ms);       // Check if delay time is less than max delay time
    m_fDelay_Time_ms = current_delay_time_ms;
    convertDelayTimeToSamples();
    
    //- Offset Write Index by 'Delay' -//
    for (int channel=0; channel < m_iNumChannels; channel++) {
        m_CRingBuffer[channel]->setWriteIdx(m_CRingBuffer[channel]->getReadIdx() + m_iDelay_Time_Samples);
    }

}

float TestDelay::getDelayTime_ms()
{
    return m_fDelay_Time_ms;
}



void TestDelay::setDelayLine_gain(float current_delay_line_gain)
{
    assert(current_delay_line_gain <= 1 && current_delay_line_gain >= 0);       // Check if delay gain is between 0 and 1
    m_fDelay_line_gain = current_delay_line_gain;
}

float TestDelay::getDelayLine_gain()
{
    return m_fDelay_line_gain;
}



void TestDelay::setInput_gain(float current_input_gain)
{
    assert(current_input_gain <= 1 && current_input_gain >= 0);
    m_fInput_gain = current_input_gain;
}

float TestDelay::getInput_gain()
{
    return m_fInput_gain;
}



void TestDelay::setFilterType(FilterType current_filter_type )
{
    m_FilterType = current_filter_type;
}


TestDelay::FilterType TestDelay::getFilterType()
{
    return m_FilterType;
}



float TestDelay::getMaxDelayTime_ms()
{
    return m_fMax_Delay_Time_ms;
}



void TestDelay::process(const float** inputBuffer, float** outputBuffer, int blockSize)
{
    //-- Iterate Through Channels --/
    for (int channel=0; channel < m_iNumChannels; channel++)
    {
        //-- Iterate Through Samples in Each Block --//
        for (int sample=0; sample < blockSize; sample++)
        {
            //-- FIR Filter --//
            if (m_FilterType == k_FIR)
            {
                outputBuffer[channel][sample] = inputBuffer[channel][sample] + (m_fDelay_line_gain * m_CRingBuffer[channel]->getPostInc());
                m_CRingBuffer[channel]->putPostInc(inputBuffer[channel][sample]);
            }
            
            //-- IIR Filter --//
            else
            {
                outputBuffer[channel][sample] = (m_fInput_gain * inputBuffer[channel][sample]) + (m_fDelay_line_gain * m_CRingBuffer[channel]->getPostInc());
                m_CRingBuffer[channel]->putPostInc(outputBuffer[channel][sample]);
            }
        }
    }
    
}


void TestDelay::initializeDefaultParameters()
{
    m_fDelay_Time_ms        =   250;
    m_fInput_gain           =   0.5;
    m_fDelay_line_gain      =   0.5;
    m_FilterType            =   k_IIR;
    
}


void TestDelay::convertDelayTimeToSamples()
{
    m_iDelay_Time_Samples = m_Fs * m_fDelay_Time_ms / 1000;
}
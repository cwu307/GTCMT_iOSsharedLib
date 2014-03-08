//
//  AudioEffectSource.cpp
//  SharedLibrary
//
//  Created by Govinda Ram Pingali on 3/8/14.
//  Copyright (c) 2014 GTCMT. All rights reserved.
//

#include "AudioEffectSource.h"


AudioEffectSource::AudioEffectSource(int effectID, int numChannels, float sampleRate)
{
    switch (effectID)
    {
        
        // Delay
        case 0:
        {
            delayEffect     =   new TestDelay(numChannels, sampleRate);
            break;
        }
            
        default:
            break;
    }
    
    m_iEffectID  = effectID;
}


AudioEffectSource::~AudioEffectSource()
{
    delayEffect =   nullptr;
    
}


void AudioEffectSource::setParameter(int parameterID, float value)
{
    
}



void AudioEffectSource::run(const float **inputBuffer, float **outputBuffer, int blockSize)
{
    switch (m_iEffectID)
    {
        // Delay
        case 0:
        {
            delayEffect->process(inputBuffer, outputBuffer, blockSize);
            break;
        }
            
            
        default:
            break;
    }
}
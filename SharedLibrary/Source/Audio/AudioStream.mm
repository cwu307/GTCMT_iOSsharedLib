//
//  AudioStream.cpp
//  SharedLibrary
//
//  Created by Govinda Ram Pingali on 3/7/14.
//  Copyright (c) 2014 GTCMT. All rights reserved.
//

#include "AudioStream.h"


AudioStream::AudioStream()
{
    //--- Audio Device Settings ---//
    sharedAudioDeviceManager->getAudioDeviceSetup(deviceSetup);
}



AudioStream::~AudioStream()
{
    sharedAudioDeviceManager->removeAudioCallback(this);
}




void AudioStream::audioDeviceAboutToStart(AudioIODevice* device)
{
    
}



void AudioStream::audioDeviceStopped()
{
    
}




//==============================================================================
// Process Block
// !!! Running on Audio Thread
//==============================================================================

void AudioStream::audioDeviceIOCallback( const float** inputChannelData,
                                        int totalNumInputChannels,
                                        float** outputChannelData,
                                        int totalNumOutputChannels,
                                        int blockSize)
{
    
    
    if (audioEffectSource.size() > 0)
    {
        for (int effectNo = 0; effectNo < audioEffectSource.size(); effectNo++)
        {
            audioEffectSource.getUnchecked(effectNo)->run(inputChannelData, outputChannelData, blockSize);
        }
        
    }
    
    
    
    else
    {
        for (int sample = 0; sample < blockSize; sample++)
        {
            for (int channel = 0; channel < totalNumOutputChannels; channel++)
            {
                outputChannelData[channel][sample] = inputChannelData[channel][sample];
            }
        }
    }
    
        
    
}



void AudioStream::addAudioEffect(int sampleID, int effectPosition, int effectID)
{
    audioEffectSource.add(new AudioEffectSource(effectID, 2, float(deviceSetup.sampleRate)));
}


void AudioStream::removeAudioEffect(int sampleID, int effectPosition)
{
    audioEffectSource.remove(effectPosition, true);
}



void AudioStream::setParameter(int sampleID, int effectID, int parameterID, float value)
{
    
}


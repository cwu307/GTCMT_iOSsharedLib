//
//  AudioEngine.cpp
//  SharedLibrary
//
//  Created by Govinda Ram Pingali on 3/8/14.
//  Copyright (c) 2014 GTCMT. All rights reserved.
//

#include "AudioEngine.h"

ScopedPointer<AudioDeviceManager> sharedAudioDeviceManager;


AudioEngine::AudioEngine()
{
    sharedAudioDeviceManager = new AudioDeviceManager();
    sharedAudioDeviceManager->initialise(2, 2, 0, true, String::empty, 0);
    
    liveAudioStream     =   new AudioStream();
    
}



AudioEngine::~AudioEngine()
{
    liveAudioStream             =   nullptr;
    sharedAudioDeviceManager    =   nullptr;
    
}


void AudioEngine::toggleAudioButtonClicked(bool toggleState)
{
    if(toggleState)
    {
        sharedAudioDeviceManager->addAudioCallback(liveAudioStream);
    }
    
    else
    {
        sharedAudioDeviceManager->removeAudioCallback(liveAudioStream);
    }
    
}
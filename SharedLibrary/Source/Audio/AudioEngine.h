//
//  AudioEngine.h
//  SharedLibrary
//
//  Created by Govinda Ram Pingali on 3/8/14.
//  Copyright (c) 2014 GTCMT. All rights reserved.
//

#ifndef __SharedLibrary__AudioEngine__
#define __SharedLibrary__AudioEngine__

#include "SharedLibraryHeader.h"
#include "AudioStream.h"

class AudioEngine

{
public:
    
    AudioEngine();
    ~AudioEngine();
    
    void startAudioStreaming();
    void stopAudioStreaming();
    bool isAudioRunning();
    
    void addAudioEffect(int sampleID, int effectPosition, int effectID);
    void removeAudioEffect(int sampleID, int effectPosition);
    void setAudioEffectBypassState(int sampleID, int effectPosition, bool bypassState);
    
private:
    
    ScopedPointer<AudioStream>  liveAudioStream;
    
    bool m_bAudioThreadRunning;
    
};

#endif /* defined(__SharedLibrary__AudioEngine__) */

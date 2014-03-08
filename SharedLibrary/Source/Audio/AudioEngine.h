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
    
    void toggleAudioButtonClicked(bool toggleState);
    
    
private:
    
    ScopedPointer<AudioStream>  liveAudioStream;
    
};

#endif /* defined(__SharedLibrary__AudioEngine__) */

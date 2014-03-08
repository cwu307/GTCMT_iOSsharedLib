//
//  SharedLibraryViewController.h
//  SharedLibrary
//
//  Created by Govinda Ram Pingali on 3/8/14.
//  Copyright (c) 2014 GTCMT. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "AudioEngine.h"

@interface SharedLibraryViewController : UIViewController
{
    AudioEngine*    audioEngine;
    
    
    bool m_bAudioToggleStatus;
    
}



@property (retain, nonatomic) IBOutlet UIButton *toggleAudioButton;
- (IBAction)toggleAudioButtonClicked:(UIButton *)sender;

@end

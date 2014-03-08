//
//  SharedLibraryViewController.h
//  SharedLibrary
//
//  Created by Govinda Ram Pingali on 3/8/14.
//  Copyright (c) 2014 GTCMT. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>
#include "SharedLibraryInterface.h"
#include "SharedLibraryHeader.h"

typedef struct {
    int sampleID;
    int effectID;
    int parameterID;
    float value;
} AudioEffect;


@interface SharedLibraryViewController : UIViewController
{
    SharedLibraryInterface*     backEndInterface;
    
    // Motion Data Parameters
    float roll;
    float pitch;
    float yaw;
    
    // GUI Parameters
    bool m_bAudioToggleStatus;
    bool m_bTempEffectStatusToggle;
    AudioEffect effectA;
    AudioEffect effectB;
    AudioEffect effectC;
}

// Motion Data Management
@property (nonatomic, strong) CMMotionManager* motionManager;

- (void) motionDeviceUpdate:(CMDeviceMotion *)deviceMotion;



// GUI Interface
@property (retain, nonatomic) IBOutlet UIButton *toggleAudioButton;
- (IBAction)toggleAudioButtonClicked:(UIButton *)sender;

- (IBAction)addEffectButtonClicked:(UIButton *)sender;

- (IBAction)sliderAValueChanged:(UISlider *)sender;

- (IBAction)sliderBValueChanged:(UISlider *)sender;

- (IBAction)sliderCValueChanged:(UISlider *)sender;

- (IBAction)segmentedControlAChanged:(UISegmentedControl *)sender;

- (IBAction)segmentedControlBChanged:(UISegmentedControl *)sender;

- (IBAction)segmentedControlCChanged:(UISegmentedControl *)sender;



@property (retain, nonatomic) IBOutlet UILabel *rollLabelValue;


@end

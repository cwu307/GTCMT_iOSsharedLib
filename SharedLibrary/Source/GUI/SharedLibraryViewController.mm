//
//  SharedLibraryViewController.m
//  SharedLibrary
//
//  Created by Govinda Ram Pingali on 3/8/14.
//  Copyright (c) 2014 GTCMT. All rights reserved.
//

#import "SharedLibraryViewController.h"

@interface SharedLibraryViewController ()

@end

@implementation SharedLibraryViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    backEndInterface    =   new SharedLibraryInterface;
    m_bAudioToggleStatus = false;
    m_bTempEffectStatusToggle   =   false;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)toggleAudioButtonClicked:(UIButton *)sender
{
    if (!m_bAudioToggleStatus)
    {
        backEndInterface->toggleAudioButtonClicked(true);
        m_bAudioToggleStatus    =   true;
    }
    else
    {
        backEndInterface->toggleAudioButtonClicked(false);
        m_bAudioToggleStatus    =   false;
    }
    
}

- (IBAction)addEffectButtonClicked:(UIButton *)sender
{
    if (!m_bTempEffectStatusToggle)
    {
        // Add Audio Effect :   Sample ID, Audio Effect Position, Audio Effect ID
        backEndInterface->addAudioEffect(0, 0, 0);
        m_bTempEffectStatusToggle   =   true;
    }
    
    else
    {
        // Remove Audio Effect :   Sample ID, Audio Effect Position
        backEndInterface->removeAudioEffect(0, 0);
        m_bTempEffectStatusToggle   =   false;
    }
}

- (IBAction)sliderAValueChanged:(UISlider *)sender
{
    effectA.value = [sender value];
    backEndInterface->setParameter(effectA.sampleID, effectA.effectID, effectA.parameterID, effectA.value);
}

- (IBAction)sliderBValueChanged:(UISlider *)sender
{
    effectB.value = [sender value];
    backEndInterface->setParameter(effectB.sampleID, effectB.effectID, effectB.parameterID, effectB.value);
}

- (IBAction)sliderCValueChanged:(UISlider *)sender
{
    effectC.value = [sender value];
    backEndInterface->setParameter(effectC.sampleID, effectC.effectID, effectC.parameterID, effectC.value);
}

- (IBAction)segmentedControlAChanged:(UISegmentedControl *)sender
{
    effectA.effectID = sender.selectedSegmentIndex;
}

- (IBAction)segmentedControlBChanged:(UISegmentedControl *)sender
{
    effectB.effectID = sender.selectedSegmentIndex;
}

- (IBAction)segmentedControlCChanged:(UISegmentedControl *)sender
{
    effectC.effectID = sender.selectedSegmentIndex;
}



- (void)dealloc
{
    
    [_toggleAudioButton release];
    
    delete backEndInterface;
    
    
    [super dealloc];
}
@end

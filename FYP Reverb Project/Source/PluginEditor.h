/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class FYPReverbProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FYPReverbProjectAudioProcessorEditor (FYPReverbProjectAudioProcessor&);
    ~FYPReverbProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    Slider allpassCoeff1Slider;
    Slider allpassCoeff2Slider;
    Slider allpassCoeff3Slider;
    Slider combCoeff1Slider;
    Slider combCoeff2Slider;
    Slider combCoeff3Slider;
    Slider combCoeff4Slider;
    Slider allpassTime1Slider;
    Slider allpassTime2Slider;
    Slider allpassTime3Slider;
    Slider combTime1Slider;
    Slider combTime2Slider;
    Slider combTime3Slider;
    Slider combTime4Slider;
    
    Label allpassCoeff1Label;
    Label allpassCoeff2Label;
    Label allpassCoeff3Label;
    Label combCoeff1Label;
    Label combCoeff2Label;
    Label combCoeff3Label;
    Label combCoeff4Label;
    Label allpassTime1Label;
    Label allpassTime2Label;
    Label allpassTime3Label;
    Label combTime1Label;
    Label combTime2Label;
    Label combTime3Label;
    Label combTime4Label;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> allpassCoeff1SliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> allpassCoeff2SliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> allpassCoeff3SliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> combCoeff1SliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> combCoeff2SliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> combCoeff3SliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> combCoeff4SliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> allpassTime1SliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> allpassTime2SliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> allpassTime3SliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> combTime1SliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> combTime2SliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> combTime3SliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> combTime4SliderAttachment;
    
    FYPReverbProjectAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FYPReverbProjectAudioProcessorEditor)
};

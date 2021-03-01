/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FYPReverbProjectAudioProcessorEditor::FYPReverbProjectAudioProcessorEditor (FYPReverbProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (800, 1200);
    
    allpassCoeff1Slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    allpassCoeff1Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(allpassCoeff1Slider);
    allpassCoeff1Label.setText("Allpass Coeff 1", dontSendNotification);
    allpassCoeff1Label.attachToComponent(&allpassCoeff1Slider, true);
    addAndMakeVisible(allpassCoeff1Label);
    
    allpassCoeff2Slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    allpassCoeff2Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(allpassCoeff2Slider);
    allpassCoeff2Label.setText("Allpass Coeff 2", dontSendNotification);
    allpassCoeff2Label.attachToComponent(&allpassCoeff2Slider, true);
    addAndMakeVisible(allpassCoeff2Label);
    
    allpassCoeff3Slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    allpassCoeff3Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(allpassCoeff3Slider);
    allpassCoeff3Label.setText("Allpass Coeff 3", dontSendNotification);
    allpassCoeff3Label.attachToComponent(&allpassCoeff3Slider, true);
    addAndMakeVisible(allpassCoeff3Label);
    
    combCoeff1Slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    combCoeff1Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(combCoeff1Slider);
    combCoeff1Label.setText("Comb Coeff 1", dontSendNotification);
    combCoeff1Label.attachToComponent(&combCoeff1Slider, true);
    addAndMakeVisible(combCoeff1Label);
    
    combCoeff2Slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    combCoeff2Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(combCoeff2Slider);
    combCoeff2Label.setText("Comb Coeff 2", dontSendNotification);
    combCoeff2Label.attachToComponent(&combCoeff2Slider, true);
    addAndMakeVisible(combCoeff2Label);
    
    combCoeff3Slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    combCoeff3Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(combCoeff3Slider);
    combCoeff3Label.setText("Comb Coeff 3", dontSendNotification);
    combCoeff3Label.attachToComponent(&combCoeff3Slider, true);
    addAndMakeVisible(combCoeff3Label);
    
    combCoeff4Slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    combCoeff4Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(combCoeff4Slider);
    combCoeff4Label.setText("Comb Coeff 4", dontSendNotification);
    combCoeff4Label.attachToComponent(&combCoeff4Slider, true);
    addAndMakeVisible(combCoeff4Label);
    
    allpassTime1Slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    allpassTime1Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(allpassTime1Slider);
    allpassTime1Label.setText("Allpass Time 1", dontSendNotification);
    allpassTime1Label.attachToComponent(&allpassTime1Slider, true);
    addAndMakeVisible(allpassTime1Label);
    
    allpassTime2Slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    allpassTime2Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(allpassTime2Slider);
    allpassTime2Label.setText("Allpass Time 2", dontSendNotification);
    allpassTime2Label.attachToComponent(&allpassTime2Slider, true);
    addAndMakeVisible(allpassTime2Label);
    
    allpassTime3Slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    allpassTime3Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(allpassTime3Slider);
    allpassTime3Label.setText("Allpass Time 3", dontSendNotification);
    allpassTime3Label.attachToComponent(&allpassTime3Slider, true);
    addAndMakeVisible(allpassTime3Label);
    
    combTime1Slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    combTime1Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(combTime1Slider);
    combTime1Label.setText("Comb Time 1", dontSendNotification);
    combTime1Label.attachToComponent(&combTime1Slider, true);
    addAndMakeVisible(combTime1Label);
    
    combTime2Slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    combTime2Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(combTime2Slider);
    combTime2Label.setText("Comb Time 2", dontSendNotification);
    combTime2Label.attachToComponent(&combTime2Slider, true);
    addAndMakeVisible(combTime2Label);
    
    combTime3Slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    combTime3Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(combTime3Slider);
    combTime3Label.setText("Comb Time 3", dontSendNotification);
    combTime3Label.attachToComponent(&combTime3Slider, true);
    addAndMakeVisible(combTime3Label);
    
    combTime4Slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    combTime4Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(combTime4Slider);
    combTime4Label.setText("Comb Time 4", dontSendNotification);
    combTime4Label.attachToComponent(&combTime4Slider, true);
    addAndMakeVisible(combTime4Label);
    
    mixSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mixSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(mixSlider);
    mixLabel.setText("Dry / Wet", dontSendNotification);
    mixLabel.attachToComponent(&mixSlider, true);
    addAndMakeVisible(mixLabel);
    
    allpassCoeff1SliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ALLPASSCOEFF1", allpassCoeff1Slider);
    allpassCoeff2SliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ALLPASSCOEFF2", allpassCoeff2Slider);
    allpassCoeff3SliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ALLPASSCOEFF3", allpassCoeff3Slider);
    combCoeff1SliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "COMBCOEFF1", combCoeff1Slider);
    combCoeff2SliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "COMBCOEFF2", combCoeff2Slider);
    combCoeff3SliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "COMBCOEFF3", combCoeff3Slider);
    combCoeff4SliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "COMBCOEFF4", combCoeff4Slider);
    allpassTime1SliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ALLPASSTIME1", allpassTime1Slider);
    allpassTime2SliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ALLPASSTIME2", allpassTime2Slider);
    allpassTime3SliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ALLPASSTIME3", allpassTime3Slider);
    combTime1SliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "COMBTIME1", combTime1Slider);
    combTime2SliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "COMBTIME2", combTime2Slider);
    combTime3SliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "COMBTIME3", combTime3Slider);
    combTime4SliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "COMBTIME4", combTime4Slider);
    mixSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MIX", mixSlider);
}

FYPReverbProjectAudioProcessorEditor::~FYPReverbProjectAudioProcessorEditor()
{
}

//==============================================================================
void FYPReverbProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    
}

void FYPReverbProjectAudioProcessorEditor::resized()
{
    allpassCoeff1Slider.setBounds(200, 0, 200, 100);
    allpassTime1Slider.setBounds(500, 0, 200, 100);
    allpassCoeff2Slider.setBounds(200, 100, 200, 100);
    allpassTime2Slider.setBounds(500, 100, 200, 100);
    allpassCoeff3Slider.setBounds(200, 200, 200, 100);
    allpassTime3Slider.setBounds(500, 200, 200, 100);
    combCoeff1Slider.setBounds(200, 300, 200, 100);
    combTime1Slider.setBounds(500, 300, 200, 100);
    combCoeff2Slider.setBounds(200, 400, 200, 100);
    combTime2Slider.setBounds(500, 400, 200, 100);
    combCoeff3Slider.setBounds(200, 500, 200, 100);
    combTime3Slider.setBounds(500, 500, 200, 100);
    combCoeff4Slider.setBounds(200, 600, 200, 100);
    combTime4Slider.setBounds(500, 600, 200, 100);
    mixSlider.setBounds(200, 700, 200, 100);
}

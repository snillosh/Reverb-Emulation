/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <array>

#include "SchroederAllPass.h"
#include "FeedbackCombFilter.h"

//==============================================================================
/**
*/
class FYPReverbProjectAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    FYPReverbProjectAudioProcessor();
    ~FYPReverbProjectAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    //==============================================================================

    void updateParameters();
    
    AudioProcessorValueTreeState apvts;
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FYPReverbProjectAudioProcessor)
    
    std::array<SchroederAllPass, 3> allpassArray;
    std::array<FeedbackCombFilter, 4> combFilterArray;
    
    float allpassCoeff1, allpassCoeff2, allpassCoeff3, allpassTime1, allpassTime2, allpassTime3, combFilterCoeff1, combFilterCoeff2, combFilterCoeff3, combFilterCoeff4, combFilterTime1, combFilterTime2, combFilterTime3, combFilterTime4, mix;
    
    AudioProcessorValueTreeState::ParameterLayout createParameters();
};

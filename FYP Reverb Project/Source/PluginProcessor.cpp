/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FYPReverbProjectAudioProcessor::FYPReverbProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
}

FYPReverbProjectAudioProcessor::~FYPReverbProjectAudioProcessor()
{
}

//==============================================================================
const juce::String FYPReverbProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FYPReverbProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FYPReverbProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FYPReverbProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FYPReverbProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FYPReverbProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FYPReverbProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FYPReverbProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FYPReverbProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void FYPReverbProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FYPReverbProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    for (int i = 0; i < 3; i++)
        allpassArray[i].initialise();
    
    for (int i = 0; i < 4; i++)
        combFilterArray[i].initialise();
}

void FYPReverbProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FYPReverbProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FYPReverbProjectAudioProcessor::updateParameters()
{
    allpassCoeff1 = *apvts.getRawParameterValue("ALLPASSCOEFF1");
    allpassCoeff2 = *apvts.getRawParameterValue("ALLPASSCOEFF2");
    allpassCoeff3 = *apvts.getRawParameterValue("ALLPASSCOEFF3");
    allpassTime1 = *apvts.getRawParameterValue("ALLPASSTIME1");
    allpassTime2 = *apvts.getRawParameterValue("ALLPASSTIME2");
    allpassTime3 = *apvts.getRawParameterValue("ALLPASSTIME3");
    combFilterCoeff1 = *apvts.getRawParameterValue("COMBCOEFF1");
    combFilterCoeff2 = *apvts.getRawParameterValue("COMBCOEFF2");
    combFilterCoeff3 = *apvts.getRawParameterValue("COMBCOEFF3");
    combFilterCoeff4 = *apvts.getRawParameterValue("COMBCOEFF4");
    combFilterTime1 = *apvts.getRawParameterValue("COMBTIME1");
    combFilterTime2 = *apvts.getRawParameterValue("COMBTIME2");
    combFilterTime3 = *apvts.getRawParameterValue("COMBTIME3");
    combFilterTime4 = *apvts.getRawParameterValue("COMBTIME4");
    mix = *apvts.getRawParameterValue("MIX");
    
    
    allpassArray[0].setFilterCoeff(allpassCoeff1);
    allpassArray[0].setDelayTime(allpassTime1);
    
    allpassArray[1].setFilterCoeff(allpassCoeff2);
    allpassArray[1].setDelayTime(allpassTime2);
    
    allpassArray[2].setFilterCoeff(allpassCoeff3);
    allpassArray[2].setDelayTime(allpassTime3);
    
    combFilterArray[0].setFilterCoeff(combFilterCoeff1);
    combFilterArray[0].setDelayTime(combFilterTime1);
    
    combFilterArray[1].setFilterCoeff(combFilterCoeff2);
    combFilterArray[1].setDelayTime(combFilterTime2);
    
    combFilterArray[2].setFilterCoeff(combFilterCoeff3);
    combFilterArray[2].setDelayTime(combFilterTime3);
    
    combFilterArray[3].setFilterCoeff(combFilterCoeff4);
    combFilterArray[3].setDelayTime(combFilterTime4);
}

void FYPReverbProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
        
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        updateParameters();
        auto* channelData = buffer.getWritePointer(0);
        
        float combOut1 = combFilterArray[0].processSample(channelData[sample]);
        float combOut2 = combFilterArray[1].processSample(channelData[sample]);
        float combOut3 = combFilterArray[2].processSample(channelData[sample]);
        float combOut4 = combFilterArray[3].processSample(channelData[sample]);
        
        float combOut = combOut1 + combOut2 + combOut3 + combOut4;
        
        float allpass1 = allpassArray[0].processSample(combOut);
        float allpass2 = allpassArray[1].processSample(allpass1);
        float allpassOut = allpassArray[3].processSample(allpass2);
        
        channelData[sample] = (allpassOut * mix) + (channelData[sample] * (1 - mix));
         
        buffer.copyFrom(1, 0, buffer, 0, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool FYPReverbProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FYPReverbProjectAudioProcessor::createEditor()
{
    return new FYPReverbProjectAudioProcessorEditor (*this);
}

//==============================================================================
void FYPReverbProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FYPReverbProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FYPReverbProjectAudioProcessor();
}

AudioProcessorValueTreeState::ParameterLayout FYPReverbProjectAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<AudioParameterFloat>("ALLPASSCOEFF1", "Allpass coeff 1", 0.0f, 0.99f, 0.7f));
    params.push_back(std::make_unique<AudioParameterFloat>("ALLPASSTIME1", "Allpass time 1", 0.f, 3.999f, 0.125f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("ALLPASSCOEFF2", "Allpass coeff 2", 0.0f, 0.99f, 0.7f));
    params.push_back(std::make_unique<AudioParameterFloat>("ALLPASSTIME2", "Allpass time 2", 0.f, 3.999f, 0.042f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("ALLPASSCOEFF3", "Allpass coeff 3", 0.0f, 0.99f, 0.7f));
    params.push_back(std::make_unique<AudioParameterFloat>("ALLPASSTIME3", "Allpass time 3", 0.f, 3.999f, 0.012f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("COMBCOEFF1", "Comb coeff 1", 0.0f, 0.99f, 0.805f));
    params.push_back(std::make_unique<AudioParameterFloat>("COMBTIME1", "Comb Time 1", 0.f, 3.999f, 0.901f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("COMBCOEFF2", "Comb coeff 2", 0.0f, 0.99f, 0.827f));
    params.push_back(std::make_unique<AudioParameterFloat>("COMBTIME2", "Comb Time 2", 0.f, 3.999f, 0.778f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("COMBCOEFF3", "Comb coeff 3", 0.0f, 0.99f, 0.783f));
    params.push_back(std::make_unique<AudioParameterFloat>("COMBTIME3", "Comb Time 3", 0.f, 3.999f, 1.011f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("COMBCOEFF4", "Comb coeff 4", 0.0f, 0.99f, 0.764f));
    params.push_back(std::make_unique<AudioParameterFloat>("COMBTIME4", "Comb Time 4", 0.f, 3.999f, 1.123f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("MIX", "Mix", 0.f, 1.f, 0.5f));
    
    
    return {params.begin(), params.end() };
}

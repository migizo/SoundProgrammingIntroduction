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
class SoundProgrammingIntroductionAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SoundProgrammingIntroductionAudioProcessorEditor (SoundProgrammingIntroductionAudioProcessor&);
    ~SoundProgrammingIntroductionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SoundProgrammingIntroductionAudioProcessor& audioProcessor;
    juce::MidiKeyboardComponent keyboardComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundProgrammingIntroductionAudioProcessorEditor)
};

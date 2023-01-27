/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SoundProgrammingIntroductionAudioProcessorEditor::SoundProgrammingIntroductionAudioProcessorEditor (SoundProgrammingIntroductionAudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p),
keyboardComponent(p.keyboardState, juce::KeyboardComponentBase::Orientation::horizontalKeyboard)
{
    addAndMakeVisible(& keyboardComponent);
    
    setSize (400, 300);
}

SoundProgrammingIntroductionAudioProcessorEditor::~SoundProgrammingIntroductionAudioProcessorEditor()
{
}

//==============================================================================
void SoundProgrammingIntroductionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SoundProgrammingIntroductionAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    keyboardComponent.setBounds(area.removeFromBottom(48));
}

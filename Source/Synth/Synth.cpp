/*
  ==============================================================================

    Synth.cpp
    Created: 25 Dec 2022 4:29:25pm
    Author:  migizo

  ==============================================================================
*/

#include "Synth.h"
#include "AdditiveSynth.h"

//==============================================================================
void Synth::setup(juce::Synthesiser& synth)
{
    synth.clearVoices();
    synth.clearSounds();
    
//    for (int i = 0; i < 128; i++) synth.addVoice(new SineWaveSynth::Voice());
    for (int i = 0; i < 128; i++) synth.addVoice(new AdditiveSynth::Voice());
    
    synth.addSound(CommonSynth::Sound::create());
}

//==============================================================================
void Synth::setupSampler(juce::Synthesiser& synth)
{
    synth.clearVoices();
    synth.clearSounds();
    
    juce::File rsrcDir = juce::File::getSpecialLocation(juce::File::SpecialLocationType::currentApplicationFile).getChildFile("Contents/Resources");

    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    juce::AudioFormatReader* reader = formatManager.createReaderFor(rsrcDir.getChildFile("wav/missile.wav"));
    
    for (int i = 0; i < 128; i++)
    {
        auto* voice = new juce::SamplerVoice();
        synth.addVoice(voice);
    }
    
    juce::BigInteger midiNoteRange;
    midiNoteRange.setRange(0, 128, true);
    
    int baseNoteNumber = 60;
    
    auto* sound = new juce::SamplerSound("default", *reader, midiNoteRange, baseNoteNumber,
                                         0, 0.1, 10.0);
    synth.addSound(sound);
}

//==============================================================================

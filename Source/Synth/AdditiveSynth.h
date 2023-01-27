/*
  ==============================================================================

    AdditiveSynth.h
    Created: 25 Dec 2022 2:14:58pm
    Author:  migizo
    reference: https://qiita.com/COx2/items/e50e8f29bea633c6e5b0

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "BaseSynth.h"
//==============================================================================
namespace SineWaveSynth
{
struct Voice  : public CommonSynth::Voice
{
    double process(double theta) override { return std::sin (currentAngle); }
};
}

//==============================================================================
namespace AdditiveSynth
{
struct Voice  : public CommonSynth::Voice
{
    struct Overtone
    {
        double amp;
        double freq;
    } overtone[5];
    
    Voice()
    {
        overtone[0].amp = 0.5;
        overtone[1].amp = 1.0;
        overtone[2].amp = 0.7;
        overtone[3].amp = 0.5;
        overtone[4].amp = 0.3;
        for (int i = 0; i < 5; i++) overtone[i].freq = i;
    }
    double process(double theta) override
    {
        auto midiNoteNumber = getCurrentlyPlayingNote();
        auto noteFreq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        auto cyclesPerSample = noteFreq / getSampleRate();
        auto angleDelta = cyclesPerSample * juce::MathConstants<double>::twoPi;
        
        double value = 0.0;
        for (int i = 0; i < 5; i++)
        {
            value += overtone[i].amp * std::sin (angleDelta * overtone[i].freq * i );
        }
        return value;
    }
};
}

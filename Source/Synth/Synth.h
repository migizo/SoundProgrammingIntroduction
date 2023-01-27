/*
  ==============================================================================

    Synth.h
    Created: 25 Dec 2022 4:29:25pm
    Author:  migizo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct Synth
{
    static void setup(juce::Synthesiser& synth);
    static void setupSampler(juce::Synthesiser& synth);
};

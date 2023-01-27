/*
  ==============================================================================

    BaseSynth.cpp
    Created: 25 Dec 2022 9:43:33pm
    Author:  migizo

  ==============================================================================
*/

#include "BaseSynth.h"
using namespace CommonSynth;

//==============================================================================
bool Voice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<Sound*> (sound) != nullptr;
}

//==============================================================================
void Voice::startNote (int midiNoteNumber, float velocity,
                               juce::SynthesiserSound*, int /*currentPitchWheelPosition*/)
{
    this->currentSample
    this->velocity = velocity * 0.2;
    this->fade = 0.0;

    auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    auto cyclesPerSample = cyclesPerSecond / getSampleRate();
    this->angleDelta = cyclesPerSample * juce::MathConstants<double>::twoPi;
}

//==============================================================================
void Voice::stopNote (float /*velocity*/, bool allowTailOff)
{
    if (allowTailOff == false)
    {
        clearCurrentNote();
    }
}

//==============================================================================
void Voice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (isKeyDown() || isPlayingButReleased())
    {
        // check note ON or OFF
        bool isPlayingNote = (getCurrentlyPlayingNote() >= 0);

        for (int sample = 0; sample < numSamples; sample++)
        {
            // 値の計算
            double currentSample = process(currentAngle) * velocity * fade;
            currentAngle += angleDelta;

            // 出力バッファに書き込み
            for (auto i = 0; i < outputBuffer.getNumChannels(); i++)
            {
                outputBuffer.addSample (i, startSample + sample, currentSample);
            }
            
            // fade更新
            if (isPlayingButReleased()) fade *= 0.99;
            else if (fade < 1.0) fade = std::max(0.0, std::min(1.0, currentAngle / juce::MathConstants<double>::twoPi));
            
            // tailOff後のoff処理
            if (isPlayingNote == false && fade <= 0.005)
            {
                clearCurrentNote();
                angleDelta = 0.0;
                break;
            }
        }
    }
}

//==============================================================================

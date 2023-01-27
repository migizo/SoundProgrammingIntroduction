/*
  ==============================================================================

    SineWave.h
    Created: 25 Dec 2022 6:59:48pm
    Author:  migizo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//==============================================================================
/**
  juce::SynthesiserSound...波形の管理(数式による定義,ファイルから生成,etc...)
*/
struct SineWaveSound : public juce::SynthesiserSound
{
  SineWaveSound() {}
  bool appliesToNote (int midiNoteNumber) override    { return true; }
  bool appliesToChannel (int midiChannel) override    { return true; }
};

//==============================================================================
/**
  juce::SynthesiserVoice...波形の再生(バッファへ書き込み,ピッチベンド,モジュレーション,etc..)
*/
struct SineWaveVoice  : public juce::SynthesiserVoice
{
  SineWaveVoice() {}

  bool canPlaySound (juce::SynthesiserSound* sound) override;

  void startNote (int midiNoteNumber, float velocity,
                  juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override;
  void stopNote (float /*velocity*/, bool allowTailOff) override;

  void pitchWheelMoved (int newValue) override {}
  void controllerMoved (int controllerNumber, int newValue) override {}

  void renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

  using juce::SynthesiserVoice::renderNextBlock;

private:
  double currentAngle = 0.0;
  double angleDelta = 0.0;
  double level = 0.0;
  double tailOff = 0.0;
  
};



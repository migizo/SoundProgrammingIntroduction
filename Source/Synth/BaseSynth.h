/*
  ==============================================================================

    BaseSynth.h
    Created: 25 Dec 2022 9:43:33pm
    Author:  migizo
    reference: https://qiita.com/COx2/items/e50e8f29bea633c6e5b0

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace CommonSynth
{

//==============================================================================
//! juce::SynthesiserSound...どのMIDI ch&Noteで使用可能か、波形の管理(数式による定義,ファイルから生成,etc...)
struct Sound : public juce::SynthesiserSound
{
    Sound() {}
    bool appliesToNote (int midiNoteNumber) override    { return true; }
    bool appliesToChannel (int midiChannel) override    { return true; }
    static juce::SynthesiserSound* create() { return new Sound(); }
};

//==============================================================================
/**
    juce::SynthesiserVoice...波形の再生(バッファへ書き込み,ピッチベンド,モジュレーション,etc..)
*/
class Voice  : public juce::SynthesiserVoice
{
public:
    Voice() {}

    bool canPlaySound (juce::SynthesiserSound* sound) override;

    void startNote (int midiNoteNumber, float velocity,
                    juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override;
    void stopNote (float /*velocity*/, bool allowTailOff) override;

    void pitchWheelMoved (int newValue) override {}
    void controllerMoved (int controllerNumber, int newValue) override {}

    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    
protected:
    virtual double process(double theta) = 0;
    
    double currentSample = 0; // サンプリング周波数で折り返す
    double velocity = 0.0;
    double fade = 0.0;
    
};

} // namespace Base

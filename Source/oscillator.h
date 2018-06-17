/*
  ==============================================================================

    oscillator.h
    Created: 19 May 2018 11:04:43am
    Author:  Isaac Jacobs

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class osc    : public Component, public ComboBox::Listener
{
public:
    osc(StarterSynthAudioProcessor&, string, string, string, string, string, string, juce::Colour);
    ~osc();

    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged(ComboBox*) override;
private:
    juce::Colour color;
    ComboBox oscMenu;
    string name;
    Slider volumeSlider, cutoffSlider, pitchSlider, phaseSlider;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> wavePtr;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> volumePtr, cutoffPtr, pitchPtr, phasePtr;

    StarterSynthAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (osc)
};

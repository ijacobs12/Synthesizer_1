/*
  ==============================================================================

    LFO.h
    Created: 22 May 2018 6:33:18pm
    Author:  Isaac Jacobs

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class LFO    : public Component, public ComboBox::Listener
{
public:
    LFO(StarterSynthAudioProcessor&, Colour, string, string, string, string);
    ~LFO();

    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged(ComboBox*) override;
private:
    ComboBox destMenu, rateFromTempo;
    StarterSynthAudioProcessor& processor;
    float bpm;
    Slider depthSlide, rateSlide;
    string name;
    Colour color;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> destPtr;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> ratePtr, depthPtr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFO)
};

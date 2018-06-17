/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "adsr_complete.h"
#include "oscillator.h"
#include "LFO.h"

//==============================================================================
/**
*/
class StarterSynthAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener, public ComboBox::Listener, public Button::Listener
{
public:
    StarterSynthAudioProcessorEditor (StarterSynthAudioProcessor&);
    ~StarterSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* ) override;
    void comboBoxChanged(ComboBox * ) override;
    void buttonClicked(Button* ) override;
    //void sliderValueChanged(Slider* slider) override;
private:
    Slider a1,d1,s1,r1,a2,d2,s2,r2,cutoff1,phase1,vol1, cutoff2, phase2, vol2, cutoff3, phase3, vol3, pitch1,pitch2,pitch3,vibRate,vibDepth, bend, autoBendSlider, qSlider, autoBTimeSlider;
    Label c1_label, p1_label, v1_label, c2_label, p2_label, v2_label, c3_label, v3_label, p3_label,pi1_label, pi2_label, pi3_label;
    ToggleButton vibModButton;
    adsr_graphic amp_graphic, cutoff_graphic;
    ComboBox osc1type, osc2type, osc3type;
    osc osc1, osc2, osc3;
    LFO lfo1;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTree_ampA,sliderTree_ampD, sliderTree_ampS, sliderTree_ampR;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTree_cutA,sliderTree_cutD,sliderTree_cutS,sliderTree_cutR;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTree_cutoff1, sliderTree_phase1, sliderTree_vol1, sliderTree_pitch1;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTree_cutoff2, sliderTree_phase2, sliderTree_vol2, sliderTree_pitch2;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTree_cutoff3, sliderTree_phase3, sliderTree_vol3, sliderTree_pitch3;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTree_vibDepth, sliderTree_vibRate, sliderTree_bend, sliderTree_cutoffQ, sliderTree_autoBend, sliderTree_autoBTime;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> sliderTree_vibModBox;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    StarterSynthAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StarterSynthAudioProcessorEditor)
};

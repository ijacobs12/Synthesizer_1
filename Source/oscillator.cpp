/*
  ==============================================================================

    oscillator.cpp
    Created: 19 May 2018 11:04:43am
    Author:  Isaac Jacobs

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "oscillator.h"

//==============================================================================
osc::osc(StarterSynthAudioProcessor& p, string oscname, string waveTree, string vol, string cut, string pitch, string phase, juce::Colour c): processor(p)
{
    name = oscname; //for asthetics
    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Triangle", 2);
    oscMenu.addItem("Saw", 3);
    oscMenu.addItem("Square", 4);
    oscMenu.addItem("Noise", 5);
    oscMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&oscMenu);
    addAndMakeVisible(&volumeSlider);
    addAndMakeVisible(&cutoffSlider);
    addAndMakeVisible(&pitchSlider);
    addAndMakeVisible(&phaseSlider);
    cutoffSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    cutoffSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    volumeSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    volumeSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    pitchSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    pitchSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    pitchSlider.setTextValueSuffix(" Semitones");
    pitchSlider.setPopupDisplayEnabled(true, false, this);
    phaseSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaseSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    phaseSlider.setTextValueSuffix(" Hz");
    phaseSlider.setPopupDisplayEnabled(true, false, this);
    wavePtr.reset(new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, waveTree, oscMenu));
    volumePtr.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, vol, volumeSlider));
    cutoffPtr.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, cut, cutoffSlider));
    pitchPtr.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, pitch, pitchSlider));
    phasePtr.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, phase, phaseSlider));
    pitchSlider.setRange(-24, 24,1);
    
    color = c;
}


osc::~osc()
{
}

void osc::paint (Graphics& g)
{
    g.setColour(color);
    g.drawRect(0, 0, getWidth(), getHeight());
    g.drawFittedText(name, 0, getHeight()-30, 100, 30, Justification::bottomLeft, 1);
    g.drawFittedText("Vol", volumeSlider.getX(),volumeSlider.getY()-20, 30, 30, Justification::centred, 1);
    g.drawFittedText("Cutoff", cutoffSlider.getX(), cutoffSlider.getY()+15, 50, 30, Justification::centred, 1);
    g.drawFittedText("Pitch", pitchSlider.getX(), pitchSlider.getY()+10, 50, 30, Justification::centred, 1);
    g.drawFittedText("+/- Hz", phaseSlider.getX(), phaseSlider.getY()+10, 50, 30, Justification::centred, 1);
    
}

void osc::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(10);
    oscMenu.setBounds(area.removeFromTop(20));
    Rectangle<int> vol = area.removeFromRight(30);
    vol.removeFromTop(25); // make room for volume label
    volumeSlider.setBounds(vol);
    cutoffSlider.setBounds(area.removeFromTop(60));
    pitchSlider.setBounds(area.removeFromTop(50));
    phaseSlider.setBounds(area.removeFromTop(50));
    
    

}
void osc::comboBoxChanged(ComboBox* box) {
    
}

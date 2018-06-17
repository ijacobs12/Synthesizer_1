/*
  ==============================================================================

    LFO.cpp
    Created: 22 May 2018 6:33:18pm
    Author:  Isaac Jacobs

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "LFO.h"

//==============================================================================
LFO::LFO(StarterSynthAudioProcessor& p, Colour col, string label, string rate, string depth, string dest): processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    color = col;
    addAndMakeVisible(&destMenu);
    addAndMakeVisible(&depthSlide);
    addAndMakeVisible(&rateSlide);
    addAndMakeVisible(&rateFromTempo);
    rateFromTempo.addListener(this);
    destMenu.addItem("None", 1);
    destMenu.addItem("Amp", 2);
    destMenu.addItem("Cutoff", 3);
    rateFromTempo.addItem("Whole Note", 1);
    rateFromTempo.addItem("1/2 Note", 2);
    rateFromTempo.addItem("1/4 Note", 3);
    rateFromTempo.addItem("1/4 Triplet", 4);
    rateFromTempo.addItem("1/8 Note", 5);
    rateFromTempo.addItem("1/8 Triplet", 6);
    rateFromTempo.setSize(10, 10);
    rateFromTempo.setJustificationType(Justification::centred);
    destMenu.setJustificationType(Justification::centred);
    depthSlide.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateSlide.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthSlide.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    rateSlide.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 15);
    rateSlide.setTextValueSuffix(" Hz");
    name = label;
    destPtr.reset(new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, dest, destMenu));
    ratePtr.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, rate, rateSlide));
    depthPtr.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, depth, depthSlide));
    
}

LFO::~LFO()
{
}

void LFO::paint (Graphics& g)
{
 
    g.setColour(color);
    g.drawRect(0, 0, getWidth(), getHeight());
    g.setColour(color.brighter(3));//here because i'm lazy and i want the border to be dark blue
    g.drawFittedText(name, getLocalBounds().reduced(5), Justification::centredTop, 1);
    g.setColour(Colours::magenta.darker(.5));
    g.drawFittedText("Controlling", getLocalBounds(),Justification::centredBottom, 1);
    g.setColour(Colours::orange);
    g.drawFittedText("Rate", getLocalBounds().removeFromBottom(50), Justification::centredTop, 1);
    g.setColour(Colours::palegreen);
    g.drawFittedText("Depth", getLocalBounds().removeFromTop(77), Justification::centredBottom, 1);

}

void LFO::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(5);
    area.removeFromBottom(10); //make room for comboBox label
    destMenu.setBounds(area.removeFromBottom(20));
    rateSlide.setBounds(area.removeFromBottom(area.getHeight()/2).translated(0, -15));//translate to make room for label
    rateFromTempo.setBounds(getLocalBounds());
    rateFromTempo.centreWithSize(15, 15);
    depthSlide.setBounds(area.reduced(11).translated(0, -3));

}

void LFO::comboBoxChanged(ComboBox* box) {
    bpm = processor.getBPM();
    if (box == &rateFromTempo) {
        if (box->getSelectedIdAsValue() == 1) {//whole note
            rateSlide.setValue(bpm/240);
        }
        else if (box->getSelectedIdAsValue() == 2) {//half note
            rateSlide.setValue(bpm/120);
        }
        else if (box->getSelectedIdAsValue() == 3) {//quarter note
            rateSlide.setValue(bpm/60.);
        }
        else if (box->getSelectedIdAsValue() == 4) {//quarter triplet
            rateSlide.setValue(bpm/40.);
        }
        else if (box->getSelectedIdAsValue() == 5) {//eigth note
            rateSlide.setValue((bpm/30.));
        }
        else if (box->getSelectedIdAsValue() == 6) {//eigth triplet
            rateSlide.setValue(bpm/20.);
        }
        
    }

}

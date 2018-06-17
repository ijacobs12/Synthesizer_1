/*
  ==============================================================================

    adsr_complete.cpp
    Created: 2 May 2018 2:50:51pm
    Author:  Isaac Jacobs

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "adsr_complete.h"

//==============================================================================
adsr_complete::adsr_complete()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(a_slider);
    addAndMakeVisible(d_slider);
    addAndMakeVisible(s_slider);
    addAndMakeVisible(r_slider);
    addAndMakeVisible(graphic);
    
    a_default = 500;
    d_default = 500;
    s_default = 1;
    r_default = 500;
    a_slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    a_slider.setValue(a_default);
    a_slider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    a_slider.setDoubleClickReturnValue(true, a_default);
    a_slider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
    a_slider.addListener(this);
    d_slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    d_slider.setValue(d_default);
    d_slider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
    d_slider.setDoubleClickReturnValue(true, 5);
    d_slider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
    d_slider.addListener(this);
    s_slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    s_slider.setValue(s_default);
    s_slider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
    s_slider.setDoubleClickReturnValue(true, s_default);
    s_slider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
    s_slider.addListener(this);
    r_slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    r_slider.setValue(r_default);
    r_slider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
    r_slider.setDoubleClickReturnValue(true, s_default);
    r_slider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
    r_slider.addListener(this);

}
adsr_complete::~adsr_complete()
{
}
void adsr_complete::setRange(float maxAttack, float maxDecay, float maxRelease) {
    a_slider.setRange(0, maxAttack, 1);
    d_slider.setRange(0, maxDecay, 1);
    s_slider.setRange(0,1,.001); //sustain is always a scale from 0-1
    r_slider.setRange(0, maxRelease, 1);
    graphic.setMaxes(maxAttack, maxDecay, maxRelease);
    
}
void adsr_complete::setDefaults(float a, float d, float s, float r){
    a_default = a;
    d_default = d;
    s_default = s;
    r_default = r;
    a_slider.setValue(a);
    a_slider.setDoubleClickReturnValue(true, a);
    d_slider.setValue(d);
    d_slider.setDoubleClickReturnValue(true, d);
    s_slider.setValue(s);
    s_slider.setDoubleClickReturnValue(true, s);
    r_slider.setValue(r);
    r_slider.setDoubleClickReturnValue(true, r);
    repaint();
    graphic.repaint();
}
void adsr_complete::sliderValueChanged(Slider *slider) {
    graphic.update(a_slider.getValue(), d_slider.getValue(), s_slider.getValue(), r_slider.getValue());
}
void adsr_complete::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background


}

float adsr_complete::getA() {
    return a_slider.getValue();
}
float adsr_complete::getD() {
    return d_slider.getValue();
}
float adsr_complete::getS() {
    return s_slider.getValue();
}
float adsr_complete::getR() {
    return r_slider.getValue();
}
void adsr_complete::setTextColor(juce::Colour color) {
    a_slider.setColour(Slider::textBoxTextColourId, color);
    d_slider.setColour(Slider::textBoxTextColourId, color);
    s_slider.setColour(Slider::textBoxTextColourId, color);
    r_slider.setColour(Slider::textBoxTextColourId, color);
}
void adsr_complete::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    int x_size = getWidth()/4;
    int y_size = getHeight()/2;
    int y_location = getHeight()-y_size;
    a_slider.setBounds(0, y_location, x_size, y_size);
    d_slider.setBounds(x_size, y_location, x_size, y_size);
    s_slider.setBounds(2*x_size, y_location, x_size, y_size);
    r_slider.setBounds(3*x_size, y_location, x_size, y_size);
    graphic.setBounds(0,0, getWidth(), getHeight()/2);

}

void adsr_complete::changeLine(juce::Colour color, int thickness) {
    graphic.setLine(color, thickness);
}
void adsr_complete::changeLine(juce::Colour color) {
    graphic.setLine(color, 3);
}

void adsr_complete::changeBackground(juce::Colour color) {
    graphic.SetBackgroundColor(color);
}

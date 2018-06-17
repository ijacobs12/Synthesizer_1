/*
  ==============================================================================

    adsr.cpp
    Created: 1 May 2018 12:54:41pm
    Author:  Isaac Jacobs

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "adsr_graphic.h"

//==============================================================================


adsr_graphic::adsr_graphic(){
    //initialize colors:
    lineColor = Colours::bisque;
    lineThickness = 3;
    backColor = Colours::grey;
    textColor = Colours::blanchedalmond;

}
adsr_graphic::~adsr_graphic()
{
}
void adsr_graphic::setMaxes(float a, float d, float r) {
    amax = a;
    dmax = d;
    smax = 1;
    rmax = r;
}

void adsr_graphic::update(float a, float d, float s, float r) {
    attack = a;
    decay = d;
    sustain = s;
    release = r;
    repaint();
}
void adsr_graphic::setText(String s, juce::Colour c) {
    text = s;
    textColor = c;
    repaint();
}
void adsr_graphic::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.fillAll (backColor);   // clear the background

    Line<float> aline (0, getHeight(), attack*getWidth()/(4*amax), getHeight()/6);
    Path p;
    p.addLineSegment(aline, 0); //make the width of the segment 0 so the outline doesn't look wack
    p.lineTo(getWidth()*(attack/(4*amax)+decay/(4*dmax)), getHeight()-sustain*getHeight()*5/(6*smax));
    p.lineTo(getWidth()*(1-release/(3*rmax)),getHeight()-sustain*getHeight()*5/(6*smax));
    p.lineTo(getWidth(), getHeight());
    PathStrokeType stroke(lineThickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded);
    g.setColour(lineColor);
    g.strokePath(p, stroke);
    g.setColour(textColor);
    g.drawFittedText(text, 0, 0, getWidth(), getHeight(), Justification::centredBottom, 1);
    
}
void adsr_graphic::setLine(juce::Colour color, int thickness) {
    lineColor = color;
    lineThickness = thickness;
    repaint();
}
void adsr_graphic::SetBackgroundColor(juce::Colour color) {
    backColor = color;
    repaint();
}
void adsr_graphic::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}



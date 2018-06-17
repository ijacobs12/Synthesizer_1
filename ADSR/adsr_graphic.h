/*
  ==============================================================================

    adsr.h
    Created: 1 May 2018 12:54:41pm
    Author:  Isaac Jacobs

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class adsr_graphic    : public Component
{
    float attack,decay,sustain,release;
public:
    adsr_graphic();
    ~adsr_graphic();
    void paint (Graphics&) override;
    void resized() override;
    void setLine(juce::Colour, int);
    void SetBackgroundColor(juce::Colour);
    void update(float, float, float, float);
    void setMaxes(float, float, float);
    void setText(String, juce::Colour);
private:
    float amax, dmax, smax, rmax;
    String text;
    juce::Colour lineColor;
    juce::Colour backColor;
    juce::Colour textColor;
    int lineThickness;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (adsr_graphic)
};

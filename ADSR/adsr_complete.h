/*
  ==============================================================================

    adsr_complete.h
    Created: 2 May 2018 2:50:51pm
    Author:  Isaac Jacobs

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "adsr_graphic.h"

//==============================================================================
/*
*/
class adsr_complete    : public Component, public Slider::Listener
{
public:
    adsr_complete();
    ~adsr_complete();
    class JUCE_API  Listener
    {
    public:
        //==============================================================================
        /** Destructor. */
        virtual ~Listener() {}
        
        //==============================================================================
        /** Called when the slider's value is changed.
         
         This may be caused by dragging it, or by typing in its text entry box,
         or by a call to Slider::setValue().
         
         You can find out the new value using Slider::getValue().
         
         @see Slider::valueChanged
         */
        virtual void adsrValueChanged (adsr_complete* adsr) = 0;
    };
    void addListener (Listener* listener);
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;
    void setDefaults(float, float, float, float);
    void changeBackground(juce::Colour);
    void changeLine(juce::Colour, int);
    void changeLine(juce::Colour);
    float getA();
    float getD();
    float getS();
    float getR();
    void setTextColor(juce::Colour);
    void setRange(float, float, float);
    Slider a_slider, d_slider, s_slider, r_slider;
private:
    ActionBroadcaster broadcaster;
    adsr_graphic graphic;
    
    float a_default, d_default, s_default, r_default;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (adsr_complete)
};

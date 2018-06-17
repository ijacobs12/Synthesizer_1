/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"

//==============================================================================
StarterSynthAudioProcessorEditor::StarterSynthAudioProcessorEditor (StarterSynthAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p), osc1(p, "Oscillator 1", "wavetype1", "vol1","cutoff1","pitch1","phase1", Colours::turquoise), osc2(p, "Oscillator 2", "wavetype2", "vol2","cutoff2","pitch2","phase2", Colours::lime), osc3(p, "Oscillator 3", "wavetype3", "vol3","cutoff3","pitch3","phase3", Colours::orchid), lfo1(p, Colours::blue, "LFO", "LFOrate", "LFOdepth","LFOdest")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);
    addAndMakeVisible(&osc1);
    addAndMakeVisible(&osc2);
    addAndMakeVisible(&osc3);
    addAndMakeVisible(&lfo1);
    addAndMakeVisible(&a1);
    addAndMakeVisible(&d1);
    addAndMakeVisible(&s1);
    addAndMakeVisible(&r1);
    addAndMakeVisible(&amp_graphic);
    addAndMakeVisible(&cutoff_graphic);
    addAndMakeVisible(&a2);
    addAndMakeVisible(&d2);
    addAndMakeVisible(&s2);
    addAndMakeVisible(&r2);
    addAndMakeVisible(&vibRate);
    addAndMakeVisible(&vibDepth);
    addAndMakeVisible(&bend);
    addAndMakeVisible(&vibModButton);
    addAndMakeVisible(&qSlider);
    addAndMakeVisible(&autoBendSlider);
    addAndMakeVisible(&autoBTimeSlider);
    vibRate.addListener(this);
    vibRate.setSliderStyle(Slider::SliderStyle::LinearVertical);
    vibRate.setPopupDisplayEnabled(true, false, this);
    vibRate.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    vibRate.setTextValueSuffix(" Hz");
    vibDepth.addListener(this);
    vibDepth.setSliderStyle(Slider::SliderStyle::LinearVertical);
    vibDepth.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    vibDepth.setTextValueSuffix(" Semitones");
    qSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    qSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    autoBendSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    autoBendSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    autoBendSlider.setTextValueSuffix(" Semitones");
    autoBendSlider.setPopupDisplayEnabled(true, false, this);
    autoBTimeSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    autoBTimeSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    autoBTimeSlider.setPopupDisplayEnabled(true, false, this);
    bend.addListener(this);
    bend.setSliderStyle(Slider::SliderStyle::LinearVertical);
    bend.setPopupDisplayEnabled(true, false, this);
    bend.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    bend.setTextValueSuffix(" Semitones");
    a2.addListener(this);
    d2.addListener(this);
    s2.addListener(this);
    r2.addListener(this);
    vibModButton.addListener(this);
    vibModButton.setButtonText("Via Modwheel?");
    vibModButton.setToggleState(true, dontSendNotification);
    vibModButton.setColour(ToggleButton::ColourIds::textColourId, Colours::aqua);
    vibModButton.setColour(ToggleButton::ColourIds::tickColourId, Colours::aqua);
    amp_graphic.setText("Amplifier Envelope", Colours::blue);
    cutoff_graphic.setText("Cutoff Envelope", Colours::red);
    amp_graphic.setLine(Colours::hotpink, 4);
    amp_graphic.SetBackgroundColor(Colours::lightgoldenrodyellow);
    cutoff_graphic.setLine(Colours::limegreen, 4);
    cutoff_graphic.SetBackgroundColor(Colours::powderblue);
    a1.setColour(Slider::ColourIds::thumbColourId, Colours::lightgreen);
    d1.setColour(Slider::ColourIds::thumbColourId, Colours::royalblue);
    s1.setColour(Slider::ColourIds::thumbColourId, Colours::coral);
    r1.setColour(Slider::ColourIds::thumbColourId, Colours::lightseagreen);
    a2.setColour(Slider::ColourIds::thumbColourId, Colours::lightgreen);
    d2.setColour(Slider::ColourIds::thumbColourId, Colours::royalblue);
    s2.setColour(Slider::ColourIds::thumbColourId, Colours::coral);
    r2.setColour(Slider::ColourIds::thumbColourId, Colours::lightseagreen);
    a1.addListener(this);
    d1.addListener(this);
    s1.addListener(this);
    r1.addListener(this);
    a1.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    d1.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    s1.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    r1.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    a1.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    d1.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
	s1.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    r1.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    a1.setTextValueSuffix("ms");
    d1.setTextValueSuffix("ms");
    s1.setTextValueSuffix(" / 1");
    r1.setTextValueSuffix("ms");
    a2.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    d2.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    s2.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    r2.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    a2.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    d2.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    s2.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    r2.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    a2.setTextValueSuffix("ms");
    d2.setTextValueSuffix("ms");
    s2.setTextValueSuffix(" / 1");
    r2.setTextValueSuffix("ms");
    amp_graphic.setMaxes(5000, 5000, 5000);
    cutoff_graphic.setMaxes(5000, 5000, 5000);
    sliderTree_ampA.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "amp_attack", a1));
    sliderTree_ampD.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "amp_decay", d1));
    sliderTree_ampS.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "amp_sustain", s1));
    sliderTree_ampR.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "amp_release", r1));
    sliderTree_cutA.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "cut_attack", a2));
    sliderTree_cutD.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "cut_decay", d2));
    sliderTree_cutS.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "cut_sustain", s2));
    sliderTree_cutR.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "cut_release", r2));
    sliderTree_vibDepth.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "vibdepth", vibDepth));
    sliderTree_vibRate.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "vibrate", vibRate));
    sliderTree_bend.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "bend", bend));
    sliderTree_vibModBox.reset(new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "vibModBox", vibModButton));
    sliderTree_cutoffQ.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "cutQ", qSlider));
    sliderTree_autoBend.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "autoBend", autoBendSlider));
    sliderTree_autoBTime.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "autoBTime", autoBTimeSlider));
    bend.setRange(0, 12, 1);
    vibDepth.setRange(0,12,.1);
    autoBendSlider.setRange(-12,12,1);
}

StarterSynthAudioProcessorEditor::~StarterSynthAudioProcessorEditor()
{
    a1.removeListener(this);
    d1.removeListener(this);
    s1.removeListener(this);
    r1.removeListener(this);
    cutoff1.removeListener(this);
    vol1.removeListener(this);
    phase1.removeListener(this);
    cutoff2.removeListener(this);
    vol2.removeListener(this);
    phase2.removeListener(this);
}
void StarterSynthAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    amp_graphic.update(a1.getValue(), d1.getValue(), s1.getValue(), r1.getValue());
    cutoff_graphic.update(a2.getValue(),d2.getValue(), s2.getValue(), r2.getValue());
}
void StarterSynthAudioProcessorEditor::buttonClicked(Button * button) {
    
}
void StarterSynthAudioProcessorEditor::comboBoxChanged(ComboBox *combo) {
    
}
//==============================================================================
void StarterSynthAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    //g.setGradientFill(ColourGradient(Colours::transparentBlack, -400, 800,getLookAndFeel().findColour (ResizableWindow::backgroundColourId), 600, 0, true)); g.fillAll();
    g.setFont(13.0f);
    g.setColour(Colours::lightgreen);
    g.drawFittedText("A", a1.getBounds(), Justification::centredBottom, 1);
    g.drawFittedText("A", a2.getBounds(), Justification::centredBottom, 1);
    g.setColour(Colours::royalblue);
    g.drawFittedText("D", d1.getBounds(), Justification::centredBottom, 1);
    g.drawFittedText("D", d2.getBounds(), Justification::centredBottom, 1);
    g.setColour(Colours::coral);
    g.drawFittedText("S", s1.getBounds(), Justification::centredBottom, 1);
    g.drawFittedText("S", s2.getBounds(), Justification::centredBottom, 1);
    g.setColour(Colours::lightseagreen);
    g.drawFittedText("R", r1.getBounds(), Justification::centredBottom, 1);
    g.drawFittedText("R", r2.getBounds(), Justification::centredBottom, 1);
    g.setColour(Colours::hotpink);
    g.drawRect(400, 300, 200, 100);
    g.setColour(Colours::limegreen);
    g.drawRect(400, 200, 200, 100);
    g.setColour(Colours::darkorchid);
    g.drawRect(0, 0, 200, 200);
    g.setColour(Colours::mediumspringgreen);
    g.drawRect(0,200,100,200);
    g.setColour(Colours::yellow);
    g.drawFittedText("Vibrato", vibRate.getX(), vibRate.getY(), 100, 100, Justification::centred, 1);
    g.setColour(Colours::orange);
    g.drawFittedText("Rate", -25, 330, 100, 60, Justification::centred, 1);
    g.drawFittedText("Time",300,375,50,20,Justification::centred, 1);
    g.setColour(Colours::palegreen);
    g.drawFittedText("Depth", 25, 330, 100, 60, Justification::centred, 1);
    g.drawFittedText("Depth", 350, 375, 50, 20, Justification::centred, 1);
    g.setColour(Colours::crimson);
    g.drawRect(100, 200, 100, 200);
    g.setColour(Colours::greenyellow);
    g.drawFittedText("Bend Range", 100, 210, 100, 100, Justification::centredTop, 1);
    g.setColour(Colours::red.brighter(1));
    g.drawRect(300,200,100,75);
    g.drawFittedText("Cutoff Q", 300, 200, 100, 75, Justification::centredTop, 1);
    g.setColour(Colours::mediumspringgreen.darker(.2));
    g.drawRect(300, 275, 100, 125);
    g.drawFittedText("Autobend", 300, 275, 100, 125, Justification::centredTop, 1);


    
}

void StarterSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    Rectangle<int> area = getLocalBounds();
    const int componentWidth = getWidth()/3;
    const int componentHeight = getHeight()/2;
    osc1.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    osc2.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    osc3.setBounds(area.removeFromTop(componentHeight));
    area.removeFromRight(componentWidth); //adsr's go here
    a1.setBounds(400,345,50,50);
    d1.setBounds(450,345,50,50);
    s1.setBounds(500, 345, 50, 50);
    r1.setBounds(550, 345, 50, 50);
    a2.setBounds(400,245,50,50);
    d2.setBounds(450,245,50,50);
    s2.setBounds(500, 245, 50, 50);
    r2.setBounds(550, 245, 50, 50);
    Rectangle<int> vib (0,200,100,200);
    vibDepth.setBounds(vib.removeFromRight(componentWidth/4).removeFromTop(4*componentHeight/5));
    vibRate.setBounds(vib.removeFromTop(4*componentHeight/5));
    vibModButton.setBounds(0,345,100,70);
    bend.setBounds(100, 225, 100, 150);
    amp_graphic.setBounds(400,300,200,50);
    cutoff_graphic.setBounds(400,200,200,50);
    lfo1.setBounds(200, 200, 100, 200);
    qSlider.setBounds(305,210,90,70);
    autoBTimeSlider.setBounds(300,285,50,90);
    autoBendSlider.setBounds(350,285,50,90);
   

    
}

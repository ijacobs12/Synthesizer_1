/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
StarterSynthAudioProcessor::StarterSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
tree(*this, nullptr)

#endif
{
    NormalisableRange<float> attackRange (0.01,5000);
    tree.createAndAddParameter("amp_attack", "Amp Attack", "Amp Attack", attackRange, 10, nullptr, nullptr);
    tree.createAndAddParameter("cut_attack", "Cutoff Attack", "Cutoff Attack", attackRange, 10, nullptr, nullptr);
    NormalisableRange<float> decayRange (0.01,5000);
    tree.createAndAddParameter("amp_decay", "Amp Decay", "Amp Decay", decayRange, 10, nullptr, nullptr);
    tree.createAndAddParameter("cut_decay", "Cutoff Decay", "Cutoff Decay", decayRange, 10, nullptr, nullptr);
    NormalisableRange<float> susRange (0.01,1.f);
    tree.createAndAddParameter("amp_sustain", "Amp Sustain", "Amp Sustain", susRange, 1., nullptr, nullptr);
    tree.createAndAddParameter("cut_sustain", "Cutoff Sustain", "Cutoff Sustain", susRange, 1., nullptr, nullptr);
    NormalisableRange<float> relRange (0.01,5000);
    tree.createAndAddParameter("amp_release", "Amp Release", "Amp Release", relRange, 10, nullptr, nullptr);
    tree.createAndAddParameter("cut_release", "Cutoff Release", "Cutoff Release", relRange, 10, nullptr, nullptr);
    NormalisableRange<float> cutRange (0.f,5000);
    tree.createAndAddParameter("cutoff1", "Cutoff 1", "Cutoff 1", cutRange, 1000, nullptr, nullptr);
    tree.createAndAddParameter("cutoff2", "Cutoff 2", "Cutoff 2", cutRange, 1000, nullptr, nullptr);
    tree.createAndAddParameter("cutoff3", "Cutoff 3", "Cutoff 3", cutRange, 1000, nullptr, nullptr);
    NormalisableRange<float> phaseRange (-10.,10.);
    tree.createAndAddParameter("phase1", "Phase 1", "Phase 1", phaseRange, 0, nullptr, nullptr);
    tree.createAndAddParameter("phase2", "Phase 2", "Phase 2", phaseRange, 0, nullptr, nullptr);
    tree.createAndAddParameter("phase3", "Phase 3", "Phase 3", phaseRange, 0, nullptr, nullptr);
    NormalisableRange<float> volRange (0., 1.);
    tree.createAndAddParameter("vol1", "Volume 1", "Volume 1", volRange, 1, nullptr, nullptr);
    tree.createAndAddParameter("vol2", "Volume 2", "Volume 2", volRange, 0, nullptr, nullptr);
    tree.createAndAddParameter("vol3", "Volume 3", "Volume 3", volRange, 0, nullptr, nullptr);
    NormalisableRange<float> pitchParam (-24, 24);
    tree.createAndAddParameter("pitch1", "Pitch 1", "Pitch 1", pitchParam, 0, nullptr, nullptr);
    tree.createAndAddParameter("pitch2", "Pitch 2", "Pitch 2", pitchParam, 0, nullptr, nullptr);
    tree.createAndAddParameter("pitch3", "Pitch 3", "Pitch 3", pitchParam, 0, nullptr, nullptr);
    NormalisableRange<float> wavetypeparam  (0,4);
    tree.createAndAddParameter("wavetype1", "Wavetype1", "Wavetype1", wavetypeparam, 0, nullptr, nullptr);
    tree.createAndAddParameter("wavetype2", "Wavetype2", "Wavetype2", wavetypeparam, 0, nullptr, nullptr);
    tree.createAndAddParameter("wavetype3", "Wavetype3", "Wavetype3", wavetypeparam, 0, nullptr, nullptr);
    NormalisableRange<float> vibDepth (0, 15);
    tree.createAndAddParameter("vibdepth", "vibdepth", "vibdepth", vibDepth, 2, nullptr, nullptr);
    NormalisableRange<float> vibRate (0,5);
    tree.createAndAddParameter("vibrate", "vibrate", "vibrate", vibRate, 2, nullptr, nullptr);
    NormalisableRange<float> bend (0,12);
    tree.createAndAddParameter("bend", "bend", "bend", bend, 2, nullptr, nullptr);
    NormalisableRange<float> vibModRange (0,1);
    tree.createAndAddParameter("vibModBox", "vibModBox", "vibModBox", vibModRange, 1, nullptr, nullptr);
    NormalisableRange<float> lfoRateRange (0.,10.);
    tree.createAndAddParameter("LFOrate", "LFOrate", "LFOrate", lfoRateRange, 1.5, nullptr, nullptr);
    tree.createAndAddParameter("LFOdepth", "LFOdepth", "LFOdepth", volRange, .5, nullptr, nullptr); //since volRange goes from 0 to 1.
    NormalisableRange<float> lfoDest (0,2);
    tree.createAndAddParameter("LFOdest", "LFOdest", "LFOdest", lfoDest, 0, nullptr, nullptr);
    NormalisableRange<float> qRange (0,10);
    tree.createAndAddParameter("cutQ", "cutQ", "cutQ", qRange, 0, nullptr, nullptr);
    NormalisableRange<float> autoBendRange (-12,12);
    tree.createAndAddParameter("autoBend", "autoBend", "autoBend", autoBendRange, 0, nullptr, nullptr);
    NormalisableRange<float> autoBendTimeRange (0,3000);
    tree.createAndAddParameter("autoBTime", "autoBTime", "autoBTime", autoBendTimeRange, 200, nullptr, nullptr);
    tree.state = ValueTree("savedParams");
    mySynth.clearVoices();
    int voices = 9; //number of voices here!
    for (int i = 0; i < voices-1; i++){
        mySynth.addVoice(new SynthVoice());
    }
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

StarterSynthAudioProcessor::~StarterSynthAudioProcessor()
{
}

//==============================================================================
const String StarterSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool StarterSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StarterSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool StarterSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double StarterSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StarterSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int StarterSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StarterSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String StarterSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void StarterSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void StarterSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void StarterSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool StarterSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif
double StarterSynthAudioProcessor::getBPM() {
    return positionInfo.bpm;
}
void StarterSynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    for (int i = 0; i < mySynth.getNumVoices(); i ++) {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))) {
            this->getPlayHead()->getCurrentPosition(positionInfo); //populates positionInfo w/ info!
            myVoice->setBPM(&positionInfo.bpm);
            myVoice->get_ampADSR(tree.getRawParameterValue("amp_attack"),
                                 tree.getRawParameterValue("amp_decay"),
                                 tree.getRawParameterValue("amp_sustain"),
                                 tree.getRawParameterValue("amp_release"));
            myVoice->get_cutADSR(tree.getRawParameterValue("cut_attack"),
                                 tree.getRawParameterValue("cut_decay"),
                                 tree.getRawParameterValue("cut_sustain"),
                                 tree.getRawParameterValue("cut_release"));
            myVoice->getCutoffs(tree.getRawParameterValue("cutoff1"),
                                tree.getRawParameterValue("cutoff2"),
                                tree.getRawParameterValue("cutoff3"));
            myVoice->getPhases(tree.getRawParameterValue("phase1"),
                               tree.getRawParameterValue("phase2"),
                               tree.getRawParameterValue("phase3"));
            myVoice->getVols(tree.getRawParameterValue("vol1"),
                             tree.getRawParameterValue("vol2"),
                             tree.getRawParameterValue("vol3"));
            myVoice->getPitches(tree.getRawParameterValue("pitch1"),
                                tree.getRawParameterValue("pitch2"),
                                tree.getRawParameterValue("pitch3"));
            myVoice->getOscs(tree.getRawParameterValue("wavetype1"),
                             tree.getRawParameterValue("wavetype2"),
                             tree.getRawParameterValue("wavetype3"));
            myVoice->getVib(tree.getRawParameterValue("vibrate"),
                            tree.getRawParameterValue("vibdepth"),
                            tree.getRawParameterValue("vibModBox"));
            myVoice->getBend(tree.getRawParameterValue("bend"));
            myVoice->getLFO(tree.getRawParameterValue("LFOrate"),
                            tree.getRawParameterValue("LFOdepth"),
                            tree.getRawParameterValue("LFOdest"));
            myVoice->getQ(tree.getRawParameterValue("cutQ"));
            myVoice->getAutoBend(tree.getRawParameterValue("autoBTime"),
                                 tree.getRawParameterValue("autoBend"));
        }
    }
    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool StarterSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* StarterSynthAudioProcessor::createEditor()
{
    return new StarterSynthAudioProcessorEditor (*this);
}

//==============================================================================
void StarterSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    std::unique_ptr<XmlElement> xml (tree.state.createXml());
    copyXmlToBinary(*xml, destData);
    
    
}

void StarterSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> settings (getXmlFromBinary(data, sizeInBytes));
    if (settings != nullptr && settings->hasTagName(tree.state.getType())) {
        tree.state = ValueTree::fromXml(*settings);
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StarterSynthAudioProcessor();
}

/*
  ==============================================================================

    SynthSound.h
    Created: 3 May 2018 4:02:19pm
    Author:  Isaac Jacobs

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
class SynthSound : public SynthesiserSound
{
public:
    bool appliesToNote(int /*midiNoteNumber*/) {
        return true;
    }
    
    bool appliesToChannel(int /*midiChannel*/) {
        return true;
    }
    
    
};

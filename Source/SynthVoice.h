/*
  ==============================================================================

    SynthVoice.h
    Created: 3 May 2018 4:02:24pm
    Author:  Isaac Jacobs

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"
#include "math.h"
class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound(SynthesiserSound* sound) {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    void get_ampADSR(float * attack, float *decay, float*sustain, float *release){
        amp_env.setAttack(*attack);
        amp_env.setDecay(*decay);
        amp_env.setSustain(*sustain);
        amp_env.setRelease(*release);
    }
    void get_cutADSR(float * attack, float *decay, float*sustain, float *release){
        cut_env.setAttack(*attack);
        cut_env.setDecay(*decay);
        cut_env.setSustain(*sustain);
        cut_env.setRelease(*release);
    }

    void getOscs(float *selection1, float *selection2, float *selection3) {
        wavetype1 = *selection1;
        wavetype2 = *selection2;
        wavetype3 = *selection3;
    }
    
    void getCutoffs(float *c1, float *c2, float *c3) {
        cutoff1 = *c1;
        cutoff2 = *c2;
        cutoff3 = *c3;
    }
    void getPhases(float *p1, float *p2, float *p3) {
        phase1 = *p1;
        phase2 = *p2;
        phase3 = *p3;
    }
    
    void getVols(float *v1, float *v2, float *v3) {
        velocity1 = pow(10, (*v1-1)*48/20); //for linear percieved volume change
        velocity2 = pow(10, (*v2-1)*48/20);
        velocity3 = pow(10, (*v3-1)*48/20);
    }

    void getPitches(float *p1, float *p2, float *p3) {
        pitch1 = *p1;
        pitch2 = *p2;
        pitch3 = *p3;
    }
    void getVib(float * vr, float *vd, float *status){
        vibRate = *vr;
        vibDepth = *vd;
        vibMod = *status;
    }
    void getBend(float *bnd){
        bendrange = *bnd;
    }
  
    void getLFO(float *rate, float *depth, float *selection) {
        lfoDest = *selection;
        lfoFreq = (*rate/3); //so the sync with bpm thingy works. don't ask me why...
        lfoDepth = *depth;
    }
    double getOscType1(){
        double freq1 = (MidiMessage::getMidiNoteInHertz(note+pitch1)+vibrato(note+pitch1))*pow(2,bend*bendrange/12.)*pow(2,ab_env.adsr(abRange, ab_env.trigger)/12.);
        if (wavetype1 == 0) {
            return osc1.sinewave(freq1+phase1);
        }
        else if (wavetype1 == 1) {
            return osc1.triangle(freq1+phase1);
        }
        else if (wavetype1 == 2) {
            return osc1.saw(freq1+phase1);
        }
        else if (wavetype1 == 3) {
            return osc1.square(freq1+phase1);
        }
        else if (wavetype1 == 4) {
            return osc1.noise();
        }
        else{
            return osc1.sinewave(freq1+phase1);
        }
    }
    double getOscType2() {
        double freq2 = (MidiMessage::getMidiNoteInHertz(note+pitch2)+vibrato(note+pitch2))*pow(2,bend*bendrange/12.)*pow(2,ab_env.adsr(abRange, ab_env.trigger)/12.);
        if (wavetype2 == 0) {
            return osc2.sinewave(freq2+phase2);
        }
        else if (wavetype2 == 1) {
            return osc2.triangle(freq2+phase2);
        }
        else if (wavetype2 == 2) {
            return osc2.saw(freq2+phase2);
        }
        else if (wavetype2 == 3) {
            return osc2.square(freq2+phase2);
        }
        else if (wavetype2 == 4) {
            return osc2.noise();
        }
        else{
            return osc2.sinewave(freq2+phase2);
        }
    }
    double getOscType3(){
        double freq3 = (MidiMessage::getMidiNoteInHertz(note+pitch3)+vibrato(note+pitch3))*pow(2,bend*bendrange/12.)*pow(2,ab_env.adsr(abRange, ab_env.trigger)/12.);
        if (wavetype3 == 0) {
            return osc3.sinewave(freq3+phase3);
        }
        else if (wavetype3 == 1) {
            return osc3.triangle(freq3+phase3);
        }
        else if (wavetype3 == 2) {
            return osc3.saw(freq3+phase3);
        }
        else if (wavetype3 == 3) {
            return osc3.square(freq3+phase3);
        }
        else if (wavetype3 == 4) {
            return osc3.noise();
        }
        else{
            return osc3.sinewave(freq3+phase3);
        }
    }
    double vibrato(int frequency){
        if (vibMod == 0) { //no modwheel
            return frequency*pow(2,vibDepth*vibOsc.sinewave(vibRate)/12.)-frequency;
        }
        else{ //via modwheel
            return (frequency*pow(2,vibDepth*vibOsc.sinewave(vibRate)/12.)-frequency)*modwheel/127;
        }
    }
    void setBPM (double *beats) {
        bpm = *beats;
    }
    void getQ(float *q) {
        cutoffQ = *q;
    }
    void getAutoBend(float *time, float *range) {
        ab_env.setDecay(*time);
        abTime = *time;
        ab_env.setAttack(0.);
        ab_env.setSustain(0.);
        ab_env.setRelease(0.);
        abRange = *range;
    }
    //==================================================
    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) {
        amp_env.trigger = 1;
        cut_env.trigger = 1;
        ab_env.trigger = 1;
        ab_env.holdtime = 0;
        cut_env.holdtime = 0;
        amp_env.holdtime = 0;
        level = velocity;
        note = midiNoteNumber;
        bend = (currentPitchWheelPosition-8192)/8192.;
        modwheel = 0;

    }
    //==================================================
    void stopNote(float velocity, bool allowTailOff){
        amp_env.trigger = 0;
        cut_env.trigger = 0;
        ab_env.trigger = 0;
        allowTailOff = true;
        clearCurrentNote();
        /*if (velocity == 0) {
            clearCurrentNote();
        } //from the tutorial. doesn't seem to help.*/
    }
    //==================================================
    void pitchWheelMoved(int newValue) {
        bend = (newValue-8192)/8192.;
    }
    //==================================================
    
    void controllerMoved(int controllerNumber, int newControllerValue) {
        modwheel = newControllerValue; //for my midi keyboard, controllerNumber is 1 for the modwheel. merits some exploration. should probably have an if statement here to confirm that the newControllerValue belongs to the modwheel!
    }
    //==================================================
    double getSound() {
        if (lfoDest == 1) {   //lfo controlls amp. using cosine for lfo so it starts at 1 (that way when syncing LFO rate to BPM max volume happens on a beat
            double wave1 = level*getOscType1()*velocity1*(lfo.coswave(lfoFreq)*lfoDepth+1);
            double wave2 = level*getOscType2()*velocity2*(lfo.coswave(lfoFreq)*lfoDepth+1);
            double wave3 = level*getOscType3()*velocity3*(lfo.coswave(lfoFreq)*lfoDepth+1);
            double filtered1 = filter1.lores(wave1, cut_env.adsr(cutoff1, cut_env.trigger), cutoffQ);
            double filtered2 = filter2.lores(wave2, cut_env.adsr(cutoff2, cut_env.trigger), cutoffQ);
            double filtered3 = filter3.lores(wave3, cut_env.adsr(cutoff3, cut_env.trigger), cutoffQ);
            return (amp_env.adsr(filtered1, amp_env.trigger)+amp_env.adsr(filtered2,amp_env.trigger)+amp_env.adsr(filtered3, amp_env.trigger))/(velocity1+velocity2+velocity3+2); //normalization...there's got to be a better way. + 1 (which makes more sense to me) still results in +0db in logic. + 2 does pretty well.
        }
        else if (lfoDest == 2) {  //lfo controlls cutoff
            double wave1 = level*getOscType1()*velocity1;
            double wave2 = level*getOscType2()*velocity2;
            double wave3 = level*getOscType3()*velocity3;
            double filtered1 = filter1.lores(wave1, cut_env.adsr(cutoff1, cut_env.trigger)*(lfo.coswave(lfoFreq)*lfoDepth+1), cutoffQ);
            double filtered2 = filter2.lores(wave2, cut_env.adsr(cutoff2, cut_env.trigger)*(lfo.coswave(lfoFreq)*lfoDepth+1), cutoffQ);
            double filtered3 = filter3.lores(wave3, cut_env.adsr(cutoff3, cut_env.trigger)*(lfo.coswave(lfoFreq)*lfoDepth+1), cutoffQ);
            return (amp_env.adsr(filtered1, amp_env.trigger)+amp_env.adsr(filtered2,amp_env.trigger)+amp_env.adsr(filtered3, amp_env.trigger))/(velocity1+velocity2+velocity3+2);
        }
        else { //lfo not controlling anything
            double wave1 = level*getOscType1()*velocity1;
            double wave2 = level*getOscType2()*velocity2;
            double wave3 = level*getOscType3()*velocity3;
            double filtered1 = filter1.lores(wave1, cut_env.adsr(cutoff1, cut_env.trigger), cutoffQ);
            double filtered2 = filter2.lores(wave2, cut_env.adsr(cutoff2, cut_env.trigger), cutoffQ);
            double filtered3 = filter3.lores(wave3, cut_env.adsr(cutoff3, cut_env.trigger), cutoffQ);
            return (amp_env.adsr(filtered1, amp_env.trigger)+amp_env.adsr(filtered2,amp_env.trigger)+amp_env.adsr(filtered3, amp_env.trigger))/(velocity1+velocity2+velocity3+2);
        }
    }
    //==================================================
    void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
        for (int sample = 0; sample < numSamples; sample ++) {
            double sound = getSound();
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel){
                outputBuffer.addSample(channel, startSample, sound);
            }
            ++startSample;
        }
        
    }
    //================================================== playHead functions:

    
private:
    int wavetype1, wavetype2, wavetype3, lfoDest;
    maxiOsc osc1, osc2, osc3, lfo, vibOsc;
    maxiEnv amp_env, cut_env, ab_env;
    maxiEnvelope test;
    maxiFilter filter1, filter2, filter3;
    float cutoff1, phase1, velocity1, cutoff2, phase2, velocity2, cutoff3, phase3, velocity3, pitch1, pitch2, pitch3, bend, bendrange, vibDepth, vibRate, vibMod, lfoFreq, lfoDepth, cutoffQ, abRange, abTime;
    float modwheel = 0;
    int note;
    double level, bpm;
    
};

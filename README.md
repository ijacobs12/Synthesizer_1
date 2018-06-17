# Synthesizer_1
My first synthesizer! A three-oscillator additive synth with a few wavetypes, adjustable pitch/frequency offset, and cutoff control for each oscillator. Also has a bunch of other cool stuff (Amp/Cutoff ADSR/LFO, autobend, etc.) to make noise.

IF YOU JUST WANT THE PLUGIN:
there's a file called Synth.component in the main directory. Pop this into Library/Audio/Plug-Ins/Components/ (for Mac...not sure where this folder is on windows but it shouldn't be too hard to figure out) and restart your DAW. That ought to do it.

IF YOU WANT TO PLAY WITH/COMPILE THE CODE:

You'll need the Maximilian DSP library: https://github.com/micknoise/Maximilian
and JUCE: https://shop.juce.com/get-juce/download
 
To open this project in xcode, install JUCE and open the .jucer file in the main directory, then click the button next to the play button that shows the xcode icon. This should create an xcode file. Build the project, and then you should have aliases to .vst and .component files in Builds/MacOSX/build/debug/
graph.filtergraph in the main directory is for debugging in the JUCE AudioPluginHost (learn more about that here if this is confusing: https://www.youtube.com/watch?v=YwSonmLAAzI)

I've been playing around with making c++ classes that are a little more portable so my next project is a little quicker...the ADSR class, which is in its own directory, is a  ADSR gui that animates a little graph and scales nicely. I got lazy and only ended up using the adsr_graphic class in my project (the graph only) but the adsr_complete class contains both a graphic and four knobs (for A, D, S, and R). I hope you find this useful!

Enjoy!!
Best,

Isaac


# Synthesizer_1
My first synthesizer! Three-oscillator additive synth with adjustable pitch/frequency offset and cutoff for each oscillator. Also has autobend, pitch wheel bend range modification, vibrato (optionally via modwheel), master amp/master cutoff LFO and ADSR control. Built using JUCE. 

Requires the Maximilian DSP library: https://github.com/micknoise/Maximilian
and JUCE: https://shop.juce.com/get-juce/download

Some Notes:
-- if you just want to use the plugin: there's a file called Synth.component in the main directory. Pop this into User/Library/Audio/Plug-Ins/Components/ and restart your DAW. That ought to do it.
-- to open this project in xcode: install JUCE and open the .jucer file, then click the button next to the play button that shows the xcode icon. This should create an xcode file. Build the project, and then you should have aliases to .vst and .component files in Builds/MacOSX/build/debug/
-- graph.filtergraph is for the JUCE AudioPluginHost
-- I've been playing around with making c++ classes that are a little more portable...the ADSR class, which is in its own directory, is a  ADSR gui that animates a little graph and scales nicely. I got lazy and only ended up using the adsr_graphic class in my project (the graph only) but the adsr_complete class contains both a graphic and four knobs (for A, D, S, and R).




/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class C74projucerGenPluginAudioProcessorEditor  : public AudioProcessorEditor,
public juce::Slider::Listener, private juce::Timer
{
public:
    C74projucerGenPluginAudioProcessorEditor (C74GenAudioProcessor&);
    ~C74projucerGenPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    C74GenAudioProcessor& processor;
    std::unique_ptr<juce::Slider> thrustSlider;
    std::unique_ptr<juce::Slider> mixSlider;
    std::unique_ptr<juce::Label> mixLabel;
    std::unique_ptr<juce::Label> thrustLabel;
    std::unique_ptr<juce::Slider> modeSlider;
    juce::Path internalPath1;
    juce::Path internalPath2;
    juce::Path internalPath3;
    juce::Path internalPath4;
    
    //Create the booster rectangles and create a movement array, which will move the rectangles a random amount
    Rectangle<int> rectangles[100];
    std::vector<int> movement_arr;
    int particlesMaxX;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (C74projucerGenPluginAudioProcessorEditor)
};

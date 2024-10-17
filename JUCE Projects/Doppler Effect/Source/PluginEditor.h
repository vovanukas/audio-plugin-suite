/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class C74projucerGenPluginAudioProcessorEditor  : public AudioProcessorEditor,
public juce::Slider::Listener, private juce::Timer
{
public:
    C74projucerGenPluginAudioProcessorEditor (C74GenAudioProcessor&);
    ~C74projucerGenPluginAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void timerCallback() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;

    // Binary resources:
    static const char* rocketL_png;
    static const int rocketL_pngSize;
    static const char* rocketR_png;
    static const int rocketR_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    C74GenAudioProcessor& processor;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Slider> distanceSlider;
    std::unique_ptr<juce::Slider> pathSlider;
    std::unique_ptr<juce::Slider> directionSlider;
    std::unique_ptr<juce::Label> directionLabel;
    std::unique_ptr<juce::Slider> gainSlider;
    std::unique_ptr<juce::Label> gainLabel;
    juce::Path internalPath1;
    juce::Path internalPath2;
    juce::Image cachedImage_rocketL_png_3;
    juce::Image cachedImage_rocketR_png_4;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (C74projucerGenPluginAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


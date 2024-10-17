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
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class NewComponent  : public juce::Component,
                      public juce::Slider::Listener
{
public:
    //==============================================================================
    NewComponent ();
    ~NewComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;

    // Binary resources:
    static const char* outputonlinetools_png;
    static const int outputonlinetools_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Slider> feedback1;
    std::unique_ptr<juce::Slider> feedback2;
    std::unique_ptr<juce::Slider> damp;
    std::unique_ptr<juce::Slider> mix;
    std::unique_ptr<juce::Label> fb1Label;
    std::unique_ptr<juce::Label> fb2Label;
    std::unique_ptr<juce::Slider> spread;
    std::unique_ptr<juce::Label> mixLabel;
    juce::Path internalPath1;
    juce::Path internalPath2;
    juce::Image cachedImage_outputonlinetools_png_3;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


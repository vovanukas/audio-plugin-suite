/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
C74projucerGenPluginAudioProcessorEditor::C74projucerGenPluginAudioProcessorEditor (C74GenAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]
    juce::Timer::startTimerHz (60);

    thrustSlider.reset (new juce::Slider ("Thrust"));
    addAndMakeVisible (thrustSlider.get());
    thrustSlider->setRange (0, 1, 0);
    thrustSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    thrustSlider->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    thrustSlider->setColour (juce::Slider::thumbColourId, juce::Colour (0xffd93425));
    thrustSlider->addListener (this);

    thrustSlider->setBounds (150, 130, 135, 24);

    mixSlider.reset (new juce::Slider ("Mix"));
    addAndMakeVisible (mixSlider.get());
    mixSlider->setRange (0, 1, 0.1);
    mixSlider->setSliderStyle (juce::Slider::Rotary);
    mixSlider->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    mixSlider->setColour (juce::Slider::thumbColourId, juce::Colour (0xffd93425));
    mixSlider->addListener (this);

    mixSlider->setBounds (15, 70, 88, 72);

    mixLabel.reset (new juce::Label ("Mix Label",
                                     TRANS("0.0\n")));
    addAndMakeVisible (mixLabel.get());
    mixLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    mixLabel->setJustificationType (juce::Justification::centred);
    mixLabel->setEditable (false, false, false);
    mixLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    mixLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    mixLabel->setBounds (15, 130, 88, 24);

    thrustLabel.reset (new juce::Label ("Thrust Label",
                                        TRANS("0.0\n")));
    addAndMakeVisible (thrustLabel.get());
    thrustLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    thrustLabel->setJustificationType (juce::Justification::centred);
    thrustLabel->setEditable (false, false, false);
    thrustLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    thrustLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    thrustLabel->setBounds (95, 130, 88, 24);

    modeSlider.reset (new juce::Slider ("Mode"));
    addAndMakeVisible (modeSlider.get());
    modeSlider->setRange (1, 2, 1);
    modeSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    modeSlider->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    modeSlider->setColour (juce::Slider::thumbColourId, juce::Colour (0xffd93425));
    modeSlider->addListener (this);

    modeSlider->setBounds (308, 130, 47, 24);
    
    auto& mixObj = mixSlider->getValueObject();
    mixObj.referTo(processor.getMixValueObject());

    auto& mixLab = mixLabel->getTextValue();
    mixLab.referTo(processor.getMixLabelObject());
    
    auto& thrustObj = thrustSlider->getValueObject();
    thrustObj.referTo(processor.getThrustValueObject());
    
    auto& thrustLab = thrustLabel->getTextValue();
    thrustLab.referTo(processor.getThrustLabelObject());
    
    auto& modeObj = modeSlider->getValueObject();
    modeObj.referTo(processor.getModeValueObject());

    internalPath1.startNewSubPath (176.0f, 32.0f);
    internalPath1.lineTo (176.0f, 76.0f);
    internalPath1.lineTo (130.0f, 58.0f);
    internalPath1.lineTo (130.0f, 48.0f);
    internalPath1.closeSubPath();

    internalPath2.startNewSubPath (248.0f, 78.0f);
    internalPath2.lineTo (258.0f, 92.0f);
    internalPath2.lineTo (200.0f, 78.0f);
    internalPath2.closeSubPath();

    internalPath3.startNewSubPath (258.0f, 16.0f);
    internalPath3.lineTo (248.0f, 30.0f);
    internalPath3.lineTo (200.0f, 30.0f);
    internalPath3.closeSubPath();

    internalPath4.startNewSubPath (260.0f, 40.0f);
    internalPath4.lineTo (270.0f, 36.0f);
    internalPath4.lineTo (270.0f, 72.0f);
    internalPath4.lineTo (260.0f, 68.0f);
    internalPath4.closeSubPath();

    //MOVING PARTICLES
    for (int i = 0; i < std::size(rectangles); i++){
        movement_arr.push_back(rand() % 70);
        rectangles[i].setSize (4, 4);
        rectangles[i].setPosition(270, rand() % 23 + 42);
    }
    
//    thrustSlider->onValueChange = [this] () {
//        for (int i = 0; i < std::size(rectangles); i++){
//            rectangles[i].setX ((thrustSlider->getValue()) * movement_arr[i] + 270);
//        }
//
//        repaint();
//    };
    //END - MOVING PARTICLES

    
    
    //[UserPreSize]
    //[/UserPreSize]

    setSize (386, 172);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

C74projucerGenPluginAudioProcessorEditor::~C74projucerGenPluginAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    thrustSlider = nullptr;
    mixSlider = nullptr;
    mixLabel = nullptr;
    thrustLabel = nullptr;
    modeSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void C74projucerGenPluginAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    {
        float x = 0.0f, y = 0.0f, width = 386.0f, height = 172.0f;
        juce::Colour fillColour = juce::Colour (0xff9bb1bf);
        juce::Colour strokeColour = juce::Colour (0xff61788c);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 2.000f);
    }

    {
        float x = 119.0f, y = 9.0f, width = 254.0f, height = 90.0f;
        juce::Colour fillColour = juce::Colours::black;
        juce::Colour strokeColour = juce::Colour (0xff61788c);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 5.000f);
    }

    {
        float x = 126.0f, y = 46.0f, width = 30.0f, height = 14.0f;
        juce::Colour fillColour = juce::Colours::azure;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillEllipse (x, y, width, height);
    }

    {
        float x = 0, y = 0;
        juce::Colour fillColour = juce::Colour (0xffd93425);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillPath (internalPath1, juce::AffineTransform::translation(x, y));
    }

    {
        float x = 172.0f, y = 30.0f, width = 88.0f, height = 48.0f;
        juce::Colour fillColour = juce::Colour (0xff9bb1bf);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    {
        float x = 188.0f, y = 38.0f, width = 32.0f, height = 32.0f;
        juce::Colour fillColour = juce::Colour (0xff61788c);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillEllipse (x, y, width, height);
    }

    {
        float x = 192.0f, y = 42.0f, width = 24.0f, height = 24.0f;
        juce::Colour fillColour = juce::Colours::cornflowerblue;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillEllipse (x, y, width, height);
    }

    {
        float x = 0, y = 0;
        juce::Colour fillColour = juce::Colour (0xffd93425);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillPath (internalPath2, juce::AffineTransform::translation(x, y));
    }

    {
        float x = 0, y = 0;
        juce::Colour fillColour = juce::Colour (0xffd93425);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillPath (internalPath3, juce::AffineTransform::translation(x, y));
    }

    {
        float x = 0, y = 0;
        juce::Colour fillColour = juce::Colour (0xff61788c);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillPath (internalPath4, juce::AffineTransform::translation(x, y));
    }

    {
        float x = 13.0f, y = 45.0f, width = 92.0f, height = 119.0f;
        juce::Colour fillColour = juce::Colour (0xff9bb1bf);
        juce::Colour strokeColour = juce::Colour (0xff61788c);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 3.000f);
    }

    {
        int x = 14, y = 33, width = 90, height = 64;
        juce::String text (TRANS("MIX"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Figtree", 20.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 14, y = 31, width = 90, height = 63;
        juce::String text (TRANS("MIX"));
        juce::Colour fillColour = juce::Colours::aliceblue;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Figtree", 21.00f, juce::Font::plain).withTypefaceStyle ("Bold").withExtraKerningFactor (-0.020f));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        float x = 116.0f, y = 108.0f, width = 258.0f, height = 54.0f;
        juce::Colour fillColour = juce::Colour (0xff9bb1bf);
        juce::Colour strokeColour = juce::Colour (0xff61788c);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 3.000f);
    }

    {
        int x = 101, y = 111, width = 213, height = 30;
        juce::String text (TRANS("THRUST"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Figtree", 20.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 160, y = 109, width = 94, height = 30;
        juce::String text (TRANS("THRUST"));
        juce::Colour fillColour = juce::Colours::aliceblue;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Figtree", 21.00f, juce::Font::plain).withTypefaceStyle ("Bold").withExtraKerningFactor (-0.020f));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 285, y = 108, width = 3, height = 54;
        juce::Colour fillColour = juce::Colour (0xff61788c);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    {
        int x = 287, y = 110, width = 85, height = 30;
        juce::String text (TRANS("MODE"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Figtree", 21.00f, juce::Font::plain).withTypefaceStyle ("Black").withExtraKerningFactor (-0.020f));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 287, y = 108, width = 85, height = 30;
        juce::String text (TRANS("MODE"));
        juce::Colour fillColour = juce::Colours::aliceblue;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Figtree", 21.00f, juce::Font::plain).withTypefaceStyle ("Bold").withExtraKerningFactor (-0.020f));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        float x = 13.0f, y = 8.0f, width = 92.0f, height = 28.0f;
        juce::Colour fillColour = juce::Colour (0xff9bb1bf);
        juce::Colour strokeColour = juce::Colour (0xff61788c);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 3.000f);
    }

    {
        int x = 14, y = 14, width = 90, height = 16;
        juce::String text (TRANS("BITCRUSHER"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Figtree", 14.40f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 14, y = 11, width = 90, height = 19;
        juce::String text (TRANS("BITCRUSHER"));
        juce::Colour fillColour = juce::Colours::aliceblue;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Figtree", 14.80f, juce::Font::plain).withTypefaceStyle ("Bold").withExtraKerningFactor (-0.020f));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    //[UserPaint] Add your own custom painting code here..
    g.setColour (juce::Colour (0xffff9904));
    for (int i = 0; i < std::size(rectangles); i++) {
        g.fillRect(rectangles[i]);
    }
    //[/UserPaint]
}

void C74projucerGenPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void C74projucerGenPluginAudioProcessorEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == thrustSlider.get())
    {
        //[UserSliderCode_thrustSlider] -- add your slider handling code here..
        processor.setParameter(0, thrustSlider->getValue());
        
        for (int i = 0; i < std::size(rectangles); i++){
            rectangles[i].setX ((thrustSlider->getValue()) * movement_arr[i] + 270);
        }
        
        repaint();
        //[/UserSliderCode_thrustSlider]
    }
    else if (sliderThatWasMoved == mixSlider.get())
    {
        //[UserSliderCode_mixSlider] -- add your slider handling code here..
        processor.setParameter(1, mixSlider->getValue());
        
        for (int i = 0; i < std::size(rectangles); i++){
            Point<int> oldCentre = rectangles[i].getCentre();
            rectangles[i].setSize(mixSlider->getValue() * 10, mixSlider->getValue() * 10);
            rectangles[i].setCentre(oldCentre);
        }
        
        repaint();
        //[/UserSliderCode_mixSlider]
    }
    else if (sliderThatWasMoved == modeSlider.get())
    {
        //[UserSliderCode_modeSlider] -- add your slider handling code here..
        processor.setParameter(2, modeSlider->getValue());
        //[/UserSliderCode_modeSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void C74projucerGenPluginAudioProcessorEditor::timerCallback()
{
    particlesMaxX = thrustSlider->getValue() * 90 + 270;
    for (int i = 0; i < std::size(rectangles); i++){
        if(rectangles[i].getX() < particlesMaxX && processor.isCurrentlyPlaying())
        {
            rectangles[i].setX(rectangles[i].getX()+ rand() % 3 + 1);
        }
        else if (rectangles[i].getX() >= particlesMaxX)
        {
            rectangles[i].setX(270);
        }
        
    }
    repaint();
}

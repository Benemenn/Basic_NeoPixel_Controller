/**
 * @file LedSegment.h
 * @author Ben Cloos, Johannes Schramm
 * @brief A class for controlling an Adafruit NeoPixel LED strip.
 * 
 * 
 * @version 0.1
 * @date 2024-08-30
 * 
 * @copyright Copyright (c) 2024 Ben Cloos & Johannes Schramm.
 * 
 */

#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <arduino_stopwatch.h> 

using namespace ArduinoStopwatch;


enum class LEDSEGMENT_MODE {
    OFF = 0,
    STATIC,
    BLINKING,
    BREATHING
};

enum class LED_BLINK_STATE{
    OFF = 0,
    ON,
    BREATHE_IN,
    BREATHE_OUT
};

struct BrightnessRange{
    uint8_t minBrightness = 0, maxBrightness = 255;
};


/// @brief this class defines the signal wave a certain color sheme will follow
/// it saves all the necessary data like the frequency, the amplitude and the different times
/// in one place. The class also provides the necessary functions to update these parameters in an automated way
class RectangleSignal{
public:
    uint16_t currentPeriod_ms = 1000;
    uint8_t currentDutyCycle = 50;
    uint16_t tOn;
    uint16_t tOff;
    uint16_t breatheDelay;
    uint8_t breathingSteps;
    BrightnessRange brightnessRange;

    /// @brief constructs a rectangle signal
    /// @param currentPeriod_ms the period of the signal
    /// @param currentDutyCycle the duty cycle of the signal
    RectangleSignal(uint16_t currentPeriod_ms = 1000, uint8_t currentDutyCycle = 50);
    /// @brief update the parameters for the blinking action
    void updateSignalParametersForBlinking();
    /// @brief updates the parameters for the blinking action
    void updateSignalParametersForBreathing();
};



///@class ColorModifier
///@brief A utility class for modifying and transforming color values.
///The ColorModifier class provides static methods for manipulating color values, such as converting
///RGB values to a 32-bit integer representation. This class cannot be instantiated.
class ColorModifier{
    public:
        static const uint32_t RED   = 0x00FF0000;
        static const uint32_t GREEN = 0x0000FF00;
        static const uint32_t BLUE  = 0x000000FF;
        static const uint32_t WHITE = 0x00FFFFFF;

        ///@brief Deleted default constructor to prevent instantiation.
        ///The default constructor is deleted to enforce the use of static methods only.
        ColorModifier() = delete;
        ///@brief Converts 8-bit RGB color values to a 32-bit unsigned integer.
        ///@param r The red color component (0-255).
        ///@param g The green color component (0-255).
        ///@param b The blue color component (0-255).
        ///@return uint32_t The combined 32-bit color value in the format 0x00RRGGBB.
        static uint32_t rgbColorToUint32(uint8_t r, uint8_t g, uint8_t b);
};


/// @brief This class represents one segment on an ledstrip.
/// The class uses the Adafruit_Neopixel library and builds onto it.
/// The class provides the possibility for a user to control a specific element with different animations.
class LedSegment {
private:
    LEDSEGMENT_MODE currentMode = LEDSEGMENT_MODE::OFF;
    uint32_t currentColor;
    uint8_t currentBrightness = 255;
    RectangleSignal _rectangleSignal;
    uint16_t startLed;
    uint16_t length;
    Stopwatch16MS stopwatch;

    LED_BLINK_STATE currentBlinkState;
    
    Adafruit_NeoPixel* neopixelsPtr;

    bool xEntrySM = true;

    /// @brief This function recalculates rgb values, depending on the brightness that is desired. 
    /// To skip HSV calculations, the methos from this source is used: https://stackoverflow.com/questions/596216/formula-to-determine-perceived-brightness-of-rgb-color
    /// @param color an rgb color value, stashed in a uint32_t value
    /// @param brightness the desired brightness the segment should be on
    /// @return colorvalue of the type uint32_t
    uint32_t calcRGBWithBrightness(uint32_t color, uint8_t brightness);
public:
    /// @brief construcs one segment in the lightstrip
    /// @param neopixels the adafruit neopixel object
    /// @param startLed starting led of the segment on the strip
    /// @param length the lenght of a segment
    LedSegment(Adafruit_NeoPixel* neopixels, uint16_t startLed, uint16_t length);
    /// @brief returns the index of the first led
    /// @return index of first led
    uint16_t getStartLed() const;
    /// @brief returns the length of the segment
    /// @return length of segment
    uint16_t getLength() const;
    /// @brief turns the segment off
    void setOff();
    /// @brief appplies a static color to the segment
    /// @param color the color the segment should show
    /// @param brightness the brightness the segment should be on
    void setStaticColor(uint32_t color, uint8_t brightness=255);
    /// @brief sets the parameters so that the segment can blink, needs update() to be called cyclically after.
    /// @param color the color the segment should show
    /// @param period_ms the blinking period
    /// @param brightness the brightness the segment should be on
    /// @param dutyCylce the duty cycle of the signal, ranges from 0 to 100%
    void setBlinking(uint32_t color, uint16_t period_ms, uint8_t brightness=255, uint8_t dutyCylce=50);
    /// @brief sets the parameters so that the segment can perform a breathing. needs update() to be called cyclically after.
    /// @param color the color the segment should show 
    /// @param period_ms the breathing period
    /// @param minBrightness the lowest brightness in the breathing display
    /// @param maxBrightness the highest brightness in the breathing display
    void setBreathing(uint32_t color, uint16_t period_ms, uint8_t minBrightness=0, uint8_t maxBrightness=255);
    /// @brief needs to be called cyclically for the set...() functions to be applied to the segment. 
    void update();

    
};

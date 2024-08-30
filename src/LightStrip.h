/**
 * @file LightStrip.h
 * @author Ben Cloos <<b.cloos@icloud.com>>
 * @brief A class for controlling an Adafruit NeoPixel LED strip.
 * 
 * This class provides methods for controlling an Adafruit NeoPixel LED strip, including setting the color of individual LEDs,
 * blinking the entire strip, and more.
 * 
 * @version 0.2
 * @date 2024-02-29
 * 
 * @copyright Copyright (c) 2024 Ben Cloos.
 * 
 */

#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "LedSegment.h"

class LightStrip {
private:
    Adafruit_NeoPixel neopixels;
    LedSegment* segmentList;
    size_t segmentListCapacity;
    size_t segmentListSize;
public:       
    /// @brief initializes the NeoPixel strip on the specified pin with the specified number of pixels and brightness
    /// @param numPixels the number of NeoPixels in the strip
    /// @param pin the pin on which the NeoPixels are connected
    /// @param type the NeoPixel type, which determines the number of data lines and the order of the color bytes
    LightStrip(uint16_t numPixels, uint16_t pin, neoPixelType type = NEO_GRB + NEO_KHZ800);
    ~LightStrip();
    void begin();
    LedSegment& operator[](size_t index);
    LedSegment& segment(size_t index);
    bool addSegment(uint8_t length);
    void update();
    /// @brief make a little initialisation show, to check if all leds are connected and are working
    void testShow();
    void setAllOff();
    void setAllStaticColor(uint32_t color, uint8_t brightness);
    void setAllBlinking(uint32_t color, uint8_t frequency, uint8_t brightness, uint8_t dutyCylce);
    void setAllBreathing(uint32_t color, uint8_t frequency, uint8_t minBrightness, uint8_t maxBrightness);     
};
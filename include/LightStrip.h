#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "LedSegment.h"

/// @brief This class controls a segmented NeoPixel LED strip.
/// This class provides methods for controlling an Adafruit NeoPixel LED strip, including setting the color,
/// blinking and breathing of LED segments, or the entire strip, and more.
class LightStrip {
private:
    Adafruit_NeoPixel neopixels;
    LedSegment* segmentList;
    size_t segmentListCapacity;
    size_t segmentListSize;
public:       
    /// @brief constructs the strip of neopixels
    /// @param numPixels the number of NeoPixels in the strip
    /// @param pin the pin on which the NeoPixels are connected
    /// @param maxSegments the maximum number of led segments
    /// @param type the NeoPixel type, which determines the number of data lines and the order of the color bytes
    LightStrip(uint16_t numPixels, uint16_t pin, size_t maxSegments, neoPixelType type = NEO_GRB + NEO_KHZ800);
    /// @brief deconstructs the strip of neopixels
    ~LightStrip();
    /// @brief sets the pin as an output and all leds off
    void begin();
    /// @brief overloads the [] operator to access a specific led segment
    /// @param index the index of a led segment
    /// @return a reference to a led segment
    LedSegment& operator[](size_t index);
    /// @brief access a specific led segment
    /// @param index the index of a led segment
    /// @return a reference to a led segment
    LedSegment& segment(size_t index);
    /// @brief create a new led segment
    /// @param startLed the first led of the segment
    /// @param length the number of leds in the segment
    /// @return if the segment was successfully created
    bool createSegment(uint16_t startLed, uint16_t length);
    /// @brief deletes all segments
    void deleteAllSegments();
    /// @brief update the state and colors of the leds
    void update();
    /// @brief blocking function which makes a little test show, to check if all leds are connected and are working
    void testShow();
    /// @brief returns the number of leds in the strip
    /// @return number of leds
    uint16_t getLedCount() const;
    /// @brief returns the number of segments in the strip
    /// @return number of segments
    size_t getSegmentCount() const;
    /// @brief returns the maximum number of segments
    /// @return the maximum number of segments
    size_t getSegmentCapacity() const;
    /// @brief sets all segments off
    void setAllOff();
    /// @brief sets all segments a static color
    /// @param color the color of the leds
    /// @param brightness the brightness of the leds
    void setAllStaticColor(uint32_t color, uint8_t brightness=255);
    /// @brief sets all segments to blinking
    /// @param color the color of the leds
    /// @param period_ms the blinking period
    /// @param brightness the brightness of the leds
    /// @param dutyCylce the blink dutycycle (relation ON to OFF)
    void setAllBlinking(uint32_t color, uint16_t period_ms, uint8_t brightness=255, uint8_t dutyCylce=127);
    /// @brief sets all segments to breathing
    /// @param color the color of the leds
    /// @param period_ms the breathing period
    /// @param minBrightness the minimum brightness of the leds
    /// @param maxBrightness the maximum brightness of the leds
    void setAllBreathing(uint32_t color, uint16_t period_ms, uint8_t minBrightness=0, uint8_t maxBrightness=255);     
};
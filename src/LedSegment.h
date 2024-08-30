#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


enum LEDSEGMENT_MODE {
    OFF = 0,
    STATIC,
    BLINKING,
    BREATHING
};

class LedSegment {
private:
    LEDSEGMENT_MODE currentMode = LEDSEGMENT_MODE::OFF;
    uint32_t currentColor;
    uint8_t currentBrightness = 255;
    uint8_t currentFrequency = 1;
    uint8_t currentDutyCylce = 50;
    uint16_t startLed;
    uint16_t length;
    unsigned long lastUpdate = 0;
    uint8_t currentState;
    
    Adafruit_NeoPixel* neopixelsPtr;

    uint32_t calcRGBWithBrightness(uint32_t color, uint8_t brightness);
public:
    LedSegment(Adafruit_NeoPixel* neopixels, uint16_t startLed, uint16_t length);
    void setOff();
    void setStaticColor(uint32_t color, uint8_t brightness);
    void setBlinking(uint32_t color, uint8_t frequency, uint8_t brightness, uint8_t dutyCylce);
    void setBreathing(uint32_t color, uint8_t frequency, uint8_t minBrightness, uint8_t maxBrightness);
};

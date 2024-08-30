#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "LedSegment.h"

LedSegment::LedSegment(Adafruit_NeoPixel* neopixels, uint16_t startLed, uint16_t length){
    this->neopixelsPtr = neopixels;
    this->startLed = startLed;
    this->length = length;
}



uint32_t LedSegment::calcRGBWithBrightness(uint32_t color, uint8_t brightness){

    uint8_t r = (uint8_t)(color >> 16);
    uint8_t g = (uint8_t)(color >> 8);
    uint8_t b = (uint8_t)color;

    #if defined(__AVR__)

        uint8_t rPrime = (r * brightness) >> 8;
        uint8_t gPrime = (g * brightness) >> 8;
        uint8_t bPrime = (b * brightness) >> 8;

    #else
        // Source: https://stackoverflow.com/questions/596216/formula-to-determine-perceived-brightness-of-rgb-color
        //float may cause problems with small processors
        float fLuminance = 0.2126 * r + 0.7152 * g + 0.0722 * b;
        float fScaleFactor = (float)brightness / fLuminance;

        uint8_t bPrime = uint8_t((float)b * fScaleFactor);
        uint8_t gPrime = uint8_t((float)g * fScaleFactor);
        uint8_t rPrime = uint8_t((float)r * fScaleFactor);
    #endif
        
    return (bPrime << 16) | (gPrime << 8) | rPrime;
    
}

void LedSegment::setOff(){
    this->neopixelsPtr->fill(0, this->startLed, this->length);
}

void LedSegment::setStaticColor(uint32_t color, uint8_t brightness){
    neopixelsPtr->fill(this->calcRGBWithBrightness(color, brightness), this->startLed, this->length);
}

void LedSegment::setBlinking(uint32_t color, uint8_t frequency, uint8_t brightness, uint8_t dutyCylce){
    
}
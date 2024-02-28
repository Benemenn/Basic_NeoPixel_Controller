/**
 * @file LightStrip.cpp
 * @author Ben Cloos <<b.cloos@icloud.com>>
 * @brief A class for controlling an Adafruit NeoPixel LED strip.
 * 
 * This class provides methods for controlling an Adafruit NeoPixel LED strip, including setting the color of individual LEDs,
 * blinking the entire strip, and more.
 * 
 * @version 0.1
 * @date 2024-02-28
 * 
 * @copyright Copyright (c) 2024 Ben Cloos.
 * 
 */

//================================================================
//BEGIN FILE
//================================================================


#include "LightStrip.h"

LightStrip::LightStrip(uint16_t numPixels, uint16_t pin, neoPixelType type, uint8_t brightness) :
    ledStrip(numPixels, pin, type),
    stripLength(numPixels),
    stripBrightness(brightness)
    {
        this->ledStrip.begin();
    }

bool LightStrip::initialisationShow(){
    uint16_t showColorDelay = 700;
    bool done = false;

    if (millis() - this->lastChangeTime >= showColorDelay){
        this->initState++;
        this->lastChangeTime = millis();
        this->sendLEDCommands = true;
    }

    if(this->sendLEDCommands){
        switch(initState){
            case 0:
                this->setBrightness(200);
                this->setLEDs(254, 0, 0, 0, this->stripLength);
                break;
            case 1:
                this->setBrightness(200);
                this->setLEDs(0, 254, 0, 0, this->stripLength);
                break;
            case 2:
                this->setBrightness(200);
                this->setLEDs(0, 0, 254, 0, this->stripLength);
                break;

            case 3: 
                this->setBrightness(200);
                this->setLEDs(245, 245, 245, 0, this->stripLength);
                break;
            case 4:
                this->turnStripOff();
                done = true;
                break;
        }

        this->sendLEDCommands = false;
    }

    return done;
}


void LightStrip::setBrightness(uint8_t brightness) {
    this->stripBrightness = brightness;
    ledStrip.setBrightness(this->stripBrightness);
}

void LightStrip::setAndShowColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t startLed, uint8_t endLed){
    for(auto i = startLed; i < endLed; ++i){
        ledStrip.setPixelColor(i, red, green, blue);
    }
    ledStrip.show();
}

void LightStrip::setAndShowColor(uint8_t red, uint8_t green, uint8_t blue){
    setAndShowColor(red, green, blue, 0, this->stripLength);
}

void LightStrip::blinkColor(uint8_t red, uint8_t green, uint8_t blue, uint64_t delayTime, uint8_t startLed, uint8_t endLed){
    
    if (millis() - this->lastChangeTime >= delayTime)
    {
        this->onState = !this->onState;
        this->lastChangeTime = millis();
        this->sendLEDCommands = true;
    }
    
    if(this->sendLEDCommands){
        switch (onState){
            case 1:
                this->setAndShowColor(red, green, blue, startLed, endLed);
                break;
            case 0:
                this->setAndShowColor(0, 0, 0, startLed, endLed);
                break;
        }

        this->sendLEDCommands = false;
    }
}

void LightStrip::blinkColor(Color c, uint64_t delayTime, uint8_t startLed, uint8_t endLed){
    this->blinkColor(c.red, c.green, c.blue, delayTime, startLed, endLed);
}

void LightStrip::setLEDs(uint8_t red, uint8_t green, uint8_t blue, uint8_t startLed, uint8_t endLed){
    this->setAndShowColor(red, green, blue, startLed, endLed);
}

void LightStrip::setLEDs(Color c, uint8_t startLed, uint8_t endLed){
    this->setAndShowColor(c.red, c.green, c.blue, startLed, endLed);
}

void LightStrip::turnStripOff(){
    this->setAndShowColor(0, 0, 0, 0, this->stripLength);
}

void LightStrip::breatheColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t delayTime, uint8_t startLed, uint8_t endLed, uint8_t maxBrightness, uint8_t minBrightness){
    if(millis() - this->lastChangeTime >= delayTime){
        lastChangeTime = millis();
        
        switch(breatheDirection){
            case 0:
                this->setBrightness(++this->stripBrightness);
                this->setLEDs(red, green, blue, startLed, endLed);
                break;
            case 1:
                this->setBrightness(--this->stripBrightness);
                this->setLEDs(red, green, blue, startLed, endLed);
                break;
        }

        if(this->stripBrightness >= maxBrightness){
            breatheDirection  = 1;
        }
        else if(this->stripBrightness <= minBrightness){
            breatheDirection = 0;
        }
    }
}

void LightStrip::breatheColor(Color c, uint8_t delayTime, uint8_t startLed, uint8_t endLed,  uint8_t maxBrightness, uint8_t minBrightness){
    this->breatheColor(c.red, c.green, c.blue, delayTime, startLed, endLed, maxBrightness, minBrightness);
}


uint8_t LightStrip::getStripLength(){
    return this->stripLength;
} 

uint8_t LightStrip::getStripBrightness(){
    return this->stripBrightness;
}
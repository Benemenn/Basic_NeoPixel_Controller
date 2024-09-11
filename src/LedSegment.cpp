
#include "LedSegment.h"


RectangleSignal::RectangleSignal(uint16_t currentPeriod_ms, uint8_t currentDutyCycle){
    this->currentDutyCycle = constrain(currentDutyCycle, 0, 100);
    this->currentPeriod_ms = currentPeriod_ms;
    this->brightnessRange.minBrightness = 0;
    this->brightnessRange.maxBrightness = 255;
    this->updateSignalParametersForBlinking();
    this->updateSignalParametersForBreathing();
}
void RectangleSignal::updateSignalParametersForBlinking(){
    this->tOff = (uint32_t)this->currentPeriod_ms * (100 - this->currentDutyCycle) / 100;
    this->tOn  = (uint32_t)this->currentPeriod_ms * currentDutyCycle / 100;
}

void RectangleSignal::updateSignalParametersForBreathing(){
    this->breathingSteps = this->brightnessRange.maxBrightness - this->brightnessRange.minBrightness;
    this->breatheDelay = this->currentPeriod_ms / 2 / this->breathingSteps;
}

LedSegment::LedSegment(Adafruit_NeoPixel* neopixels, uint16_t startLed, uint16_t length){
    this->neopixelsPtr = neopixels;
    this->startLed = startLed;
    this->length = length;
}



uint32_t LedSegment::calcRGBWithBrightness(uint32_t color, uint8_t brightness){
    uint8_t r = (uint8_t)(color >> 16);
    uint8_t g = (uint8_t)(color >> 8);
    uint8_t b = (uint8_t)color;


    uint8_t rPrime = ((uint32_t)r * (uint32_t)brightness) / 255;
    uint8_t gPrime = ((uint32_t)g * (uint32_t)brightness) / 255;
    uint8_t bPrime = ((uint32_t)b * (uint32_t)brightness) / 255;

        
    return ((uint32_t)rPrime << 16) | ((uint32_t)gPrime << 8) | (uint32_t)bPrime;
    
}

void LedSegment::setOff(){
    this->currentMode = LEDSEGMENT_MODE::OFF;
}

void LedSegment::setStaticColor(uint32_t color, uint8_t brightness){
    this->currentMode = LEDSEGMENT_MODE::STATIC;
    this->currentBrightness = brightness;
    this->currentColor = this->calcRGBWithBrightness(color, this->currentBrightness);
}

void LedSegment::setBlinking(uint32_t color, uint16_t period_ms, uint8_t brightness, uint8_t dutyCylce){
    this->currentMode = LEDSEGMENT_MODE::BLINKING;
    this->currentBlinkState = LED_BLINK_STATE::OFF;
    this->currentBrightness = brightness;
    this->currentColor = this->calcRGBWithBrightness(color, this->currentBrightness);
    this->_rectangleSignal.currentPeriod_ms = period_ms;
    this->_rectangleSignal.currentDutyCycle = constrain(dutyCylce, 0, 100);

    this->_rectangleSignal.updateSignalParametersForBlinking();

    xEntrySM = true;
}

void LedSegment::setBreathing(uint32_t color, uint16_t period_ms, uint8_t minBrightness, uint8_t maxBrightness){
    this->currentMode = LEDSEGMENT_MODE::BREATHING;
    this->currentBlinkState = LED_BLINK_STATE::BREATHE_IN;
    this->_rectangleSignal.brightnessRange.minBrightness = minBrightness;
    this->_rectangleSignal.brightnessRange.maxBrightness = maxBrightness;
    this->currentBrightness = this->_rectangleSignal.brightnessRange.minBrightness; //start at low brightness breathing!
    this->_rectangleSignal.currentPeriod_ms = period_ms;
    this->currentColor = color;
    this->_rectangleSignal.updateSignalParametersForBreathing();

    xEntrySM = true;
}

void LedSegment::update(){
    switch (currentMode)
    {
    case LEDSEGMENT_MODE::OFF:
        this->neopixelsPtr->fill(0, this->startLed, this->length);
        break;
    
    case LEDSEGMENT_MODE::STATIC:
        this->neopixelsPtr->fill(this->currentColor, this->startLed, this->length);
        break;

    case LEDSEGMENT_MODE::BLINKING:
        switch (currentBlinkState)
        {
        case LED_BLINK_STATE::OFF:
            if(xEntrySM){
                xEntrySM = false;
                stopwatch.restart();
            }
            
            this->neopixelsPtr->fill(0, this->startLed, this->length);
            if(stopwatch.getTimeSinceStart() > _rectangleSignal.tOff){
                currentBlinkState = LED_BLINK_STATE::ON;
                xEntrySM = true;
            }
            break;

        case LED_BLINK_STATE::ON:
            if(xEntrySM){
                xEntrySM = false;
                stopwatch.restart();
            }
            this->neopixelsPtr->fill(currentColor, startLed, length);
            if(stopwatch.getTimeSinceStart() > _rectangleSignal.tOn){
                currentBlinkState = LED_BLINK_STATE::OFF;
                xEntrySM = true;
            }
            break;

        default:
            currentBlinkState = LED_BLINK_STATE::OFF;
            xEntrySM = true;
        }
        break;

    case LEDSEGMENT_MODE::BREATHING:
        switch (this->currentBlinkState){
            case LED_BLINK_STATE::BREATHE_IN:
                if(xEntrySM){
                    xEntrySM = false;
                    stopwatch.restart();
                }
                if (stopwatch.getTimeSinceStart() > _rectangleSignal.breatheDelay){
                    if(currentBrightness + 1 >= _rectangleSignal.brightnessRange.maxBrightness){
                        currentBlinkState = LED_BLINK_STATE::BREATHE_OUT;
                        
                    }
                    else{
                        ++currentBrightness;
                    }
                    
                    uint32_t tempColor = calcRGBWithBrightness(currentColor, currentBrightness);
                    
                    neopixelsPtr->fill(tempColor, this->startLed, this->length);
                    xEntrySM = true; //restart timer for breathing effect
                }
            break;

            case LED_BLINK_STATE::BREATHE_OUT:
                if(xEntrySM){
                    xEntrySM = false;
                    stopwatch.restart();
                }
                if (stopwatch.getTimeSinceStart() > _rectangleSignal.breatheDelay){
                    if(currentBrightness - 1 <= _rectangleSignal.brightnessRange.minBrightness){
                        currentBlinkState = LED_BLINK_STATE::BREATHE_IN;
                    }
                    else{
                        --currentBrightness;
                    }

                    uint32_t tempColor = calcRGBWithBrightness(currentColor, currentBrightness);
                    neopixelsPtr->fill(tempColor, startLed, length);

                    xEntrySM = true; //restart timer for breathing effect
                }
                
            break;

            default:
                currentBlinkState = LED_BLINK_STATE::BREATHE_IN;
                xEntrySM = true;
                break;
        }


    }
}

uint32_t ColorModifier::rgbColorToUint32(uint8_t r, uint8_t g, uint8_t b){
    return 0xFF000000 | ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;
};
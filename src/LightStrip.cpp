#include "LightStrip.h"

LightStrip::LightStrip(uint16_t numPixels, uint16_t pin, size_t maxSegments, neoPixelType type) :
    neopixels(numPixels, pin, type),
    segmentList(nullptr),
    segmentListCapacity(maxSegments),
    segmentListSize(0)
{
    segmentList = (LedSegment*)malloc(segmentListCapacity * sizeof(LedSegment));
    if(segmentList == nullptr) {
        segmentListCapacity = 0;
    }
}
LightStrip::~LightStrip() {
    free(segmentList);
}
void LightStrip::begin() {
    neopixels.begin();
    neopixels.show();
}
LedSegment& LightStrip::operator[](size_t index) {
    return segment(index);
}
LedSegment& LightStrip::segment(size_t index) {
    if(index >= segmentListSize) {
        return segmentList[0];
    }
    return segmentList[index];
}
bool LightStrip::createSegment(uint16_t startLed, uint16_t length) {
    if(segmentListSize >= segmentListCapacity) {
        return false;
    }
    segmentList[segmentListSize] = LedSegment(&neopixels, startLed, length);
    segmentListSize++;
    return true;
}
void LightStrip::update() {
    for(size_t i; i < segmentListSize; i++) {
        segmentList[i].update();
    }
    neopixels.show();
}
void LightStrip::testShow() {
    const uint16_t TEST_COLOR_DELAY_MS = 700;
    const uint8_t BRIGHTNESS    = 255;
    const uint32_t COLOR_RED    = 0x00FF0000;
    const uint32_t COLOR_GREEN  = 0x0000FF00;
    const uint32_t COLOR_BLUE   = 0x000000FF;
    const uint32_t COLOR_WHITE  = 0x00FFFFFF;
    
    for(size_t i; i < segmentListSize; i++) {
        segment(i).setStaticColor(COLOR_RED, BRIGHTNESS);
        this->update();
        delay(TEST_COLOR_DELAY_MS);
        segment(i).setStaticColor(COLOR_GREEN, BRIGHTNESS);
        this->update();
        delay(TEST_COLOR_DELAY_MS);
        segment(i).setStaticColor(COLOR_BLUE, BRIGHTNESS);
        this->update();
        delay(TEST_COLOR_DELAY_MS);
        segment(i).setStaticColor(COLOR_WHITE, BRIGHTNESS);
        this->update();
        delay(TEST_COLOR_DELAY_MS);
        segment(i).setOff();
        this->update();
        delay(TEST_COLOR_DELAY_MS);
    }

    this->setAllStaticColor(COLOR_RED, BRIGHTNESS);
    this->update();
    delay(TEST_COLOR_DELAY_MS);
    this->setAllStaticColor(COLOR_GREEN, BRIGHTNESS);
    this->update();
    delay(TEST_COLOR_DELAY_MS);
    this->setAllStaticColor(COLOR_BLUE, BRIGHTNESS);
    this->update();
    delay(TEST_COLOR_DELAY_MS);
    this->setAllStaticColor(COLOR_WHITE, BRIGHTNESS);
    this->update();
    delay(TEST_COLOR_DELAY_MS);
    this->setAllOff();
    this->update();
}
void LightStrip::setAllOff() {
    for(size_t i; i < segmentListSize; i++) {
        segmentList[i].setOff();
    }
}
void LightStrip::setAllStaticColor(uint32_t color, uint8_t brightness) {
    for(size_t i; i < segmentListSize; i++) {
        segmentList[i].setStaticColor(color, brightness);
    }
}
void LightStrip::setAllBlinking(uint32_t color, uint8_t frequency, uint8_t brightness, uint8_t dutyCylce) {
    for(size_t i; i < segmentListSize; i++) {
        segmentList[i].setBlinking(color, frequency, brightness, dutyCylce);
    }
}
void LightStrip::setAllBreathing(uint32_t color, uint8_t frequency, uint8_t minBrightness, uint8_t maxBrightness) {
    for(size_t i; i < segmentListSize; i++) {
        segmentList[i].setBreathing(color, frequency, minBrightness, maxBrightness);
    }
}    
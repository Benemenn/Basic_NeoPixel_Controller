#include <Arduino.h>
#include "LightStrip.h"

const uint16_t NUMBER_OF_LEDS = 30;
const uint8_t NEOPIXEL_PIN = 14;
const size_t MAX_SEGMENTS = 4;
LightStrip ledStrip(NUMBER_OF_LEDS, NEOPIXEL_PIN, MAX_SEGMENTS);

const uint32_t COLOR_RED    = 0x00FF0000;
const uint32_t COLOR_GREEN  = 0x0000FF00;
const uint32_t COLOR_BLUE   = 0x000000FF;
const uint32_t COLOR_WHITE  = 0x00FFFFFF;

void setup() {
    // Serial:
    Serial.begin(115200);
    Serial.println("NeoPixel LightStrip blink example!");

    // LedStrip:
    ledStrip.begin();

    // Segments:
    ledStrip.createSegment(0, 5);   //  0 -  4
    ledStrip.createSegment(5, 10);  //  5 - 14
    ledStrip.createSegment(15, 7);  // 15 - 21
    ledStrip.createSegment(22, 8);  // 22 - 29

    ledStrip[0].setBlinking(COLOR_RED, 2);
    ledStrip[1].setBlinking(COLOR_GREEN, 5);
    ledStrip[2].setBlinking(COLOR_BLUE, 1, 255, 20);
    ledStrip[3].setBlinking(COLOR_WHITE, 20, 50);

    // Test show:
    Serial.print("Testing leds...");
    ledStrip.testShow();
    Serial.println("done!");

    Serial.println("Setup done!");
}

void loop() {
    ledStrip.update();
}

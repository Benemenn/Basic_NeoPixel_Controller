#include <Arduino.h>
#include "LightStrip.h"

const uint16_t NUMBER_OF_LEDS = 4;
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
    ledStrip.createSegment(0, 1);   //  0 -  2
    ledStrip.createSegment(1, 1);  //  3 - 6
    ledStrip.createSegment(2, 1);  // 7 - 10
    ledStrip.createSegment(3, 1);  // 10 - 12

    // Test show:
    Serial.print("Testing leds...");
    ledStrip.testShow();
    Serial.println("done!");

    ledStrip[0].setBlinking(ColorModifier::RED, 2000, 50, 10);
    ledStrip[1].setBlinking(COLOR_GREEN, 500);
    ledStrip[2].setBreathing(ColorModifier::rgbColorToUint32(132, 0, 250), 10000, 10, 255);
    ledStrip[3].setBlinking(COLOR_WHITE, 1000, 50);


    Serial.println("Setup done!");
    delay(2000);
}

void loop() {
    ledStrip.update();
}

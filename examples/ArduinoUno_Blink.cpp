#include <Arduino.h>
#include "LightStrip.h"

const uint16_t NUMBER_OF_LEDS = 12;
const uint8_t NEOPIXEL_PIN = 9;
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
    ledStrip.createSegment(0, 3);   //  0 -  2
    ledStrip.createSegment(3, 3);  //  3 - 6
    ledStrip.createSegment(7, 3);  // 7 - 10
    ledStrip.createSegment(10, 3);  // 10 - 12

    // Test show:
    Serial.print("Testing leds...");
    ledStrip.testShow();
    Serial.println("done!");

    ledStrip[0].setBlinking(ColorModifier::rgbColorToUint32(255, 255, 0), 2000, 50, 10);
    ledStrip[1].setBlinking(COLOR_GREEN, 500);
    ledStrip[2].setBreathing(COLOR_BLUE, 1000, 10, 200);
    ledStrip[3].setBlinking(COLOR_WHITE, 1000, 50);


    Serial.println("Setup done!");
    delay(2000);
}

void loop() {
    ledStrip.update();
}

#include <Arduino.h>
#include "LightStrip.h"

const uint16_t NUMBER_OF_LEDS = 14;
const uint8_t NEOPIXEL_PIN = 9;
const size_t MAX_SEGMENTS = 4;
LightStrip ledStrip(NUMBER_OF_LEDS, NEOPIXEL_PIN, MAX_SEGMENTS);

void setup() {
    // Serial:
    Serial.begin(115200);
    Serial.println("NeoPixel LightStrip blink example!");

    // LedStrip:
    ledStrip.begin();

    // Segments:
    ledStrip.createSegment(0, 5);   //  0 - 29
    ledStrip.createSegment(5, 5); //

    // Test show:
    Serial.print("Testing leds...");
    ledStrip.testShow();
    Serial.println("done!");

    Serial.println("Setup done!");
}

long lastChange = 0;
byte state = 0;
byte numberOfStates = 5;
void loop() {
    ledStrip.update();

    switch(state) {
        case 0:
            ledStrip[0].setBlinking(0x0000B1AC, 1000, 50);
            break;
        case 1:
            ledStrip[0].setStaticColor(0x00787800);
            break;
        case 2:
            ledStrip[0].setBlinking(0x003219AC, 500, 20);
            break;
        case 3:
            ledStrip[0].setBlinking(0x000000FF, 2000);
            break;
        case 4:
            ledStrip[0].setBreathing(0x0000FF00, 1000, 10, 200);
            break;
    }

    if (millis() - lastChange > 10000) {
       state = (state + 1) % numberOfStates;
       lastChange = millis();
       Serial.println("next state: " + String(state));
    } 
}

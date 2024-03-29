#include <Arduino.h>
#include "LightStrip.h"

LightStrip ledStrip(30, 14);

Adafruit_NeoPixel neopixel(12, 14, NEO_GRB + NEO_KHZ800);



long lastChange = 0;
byte state = 0;
byte maxState = 4;

void setup() {
    Serial.begin(115200);
    while (!ledStrip.initialisationShow())
    {
        //wait until
    }
    Serial.println("ledStrip initialised");


  
}

void loop() {

    switch(state){
        case 0:
            ledStrip.setStripBrightness(50);
            ledStrip.blinkColor(0, 177, 172, 500, 0, ledStrip.getStripLength());
            break;
        case 1:
            ledStrip.setLEDs(120, 120, 0, 0, ledStrip.getStripLength());
            break;

        case 2:
            ledStrip.setStripBrightness(20);
            ledStrip.blinkColor(50, 25, 172, 200, 5, 9);
            break;
        case 3:
            ledStrip.blinkColor(0,0,255, 1000, 0, 1);
            break;

        case 4:
            ledStrip.breatheColor(0, 255, 0, 10, 0, ledStrip.getStripLength(), 200, 10);
            break;
    }

    if (millis() - lastChange > 10000) {
    
       state++;
       ledStrip.turnStripOff();
       lastChange = millis();
       Serial.println("next state: " + String(state));
    }

    if(state > maxState){
        state = 0;
        Serial.println("next state: " + String(state));
    }

    ledStrip.turnStripOff();
    

}

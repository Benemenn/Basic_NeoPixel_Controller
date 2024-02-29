
#include <Arduino.h>
#include "LightStrip.h"

LightStrip ledStrip(12, 14);

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
            simpleColor c(0, 0, 255);
            ledStrip.blinkColor(c, 1000, 0, 1);
            break;
    }

    if (millis() - lastChange > 10000) {
    
       state++;
       ledStrip.turnStripOff();
       lastChange = millis();
       Serial.println("next state: " + String(state));
    }

    if(state >= maxState){
        state = 0;
        Serial.println("next state: " + String(state));
    }
    

}

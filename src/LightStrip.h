/**
 * @file LightStrip.h
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

#include <Adafruit_NeoPixel.h>

struct Color{
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    Color(uint8_t r, uint8_t g, uint8_t b){
        red = r;
        green = g;
        blue = b;
    }

};

class LightStrip {
    private:
        Adafruit_NeoPixel ledStrip;
        uint8_t stripLength;
        uint8_t stripBrightness;

        bool onState = false; 
        uint64_t lastChangeTime = 0; // needed for the non-blocking blinking function
        bool sendLEDCommands = false;
        byte initState = false; // for initialization of the LED strip

        bool breatheDirection = false;
        /**
         * Sets the color of the LEDs on the NeoPixel strip, and updates the strip with the new color.
         * 
         * @param red The amount of red to set for each LED, between 0 and 255.
         * @param green The amount of green to set for each LED, between 0 and 255.
         * @param blue The amount of blue to set for each LED, between 0 and 255.
         * @param startLed The index of the first LED to set the color for.
         * @param endLed The index of the last LED to set the color for.
         */
        
        void setAndShowColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t startLed, uint8_t endLed);
        /**
         * Sets the color of the LEDs on the NeoPixel strip, and updates the strip with the new color.
         * 
         * @param red The amount of red to set for each LED, between 0 and 255.
         * @param green The amount of green to set for each LED, between 0 and 255.
         * @param blue The amount of blue to set for each LED, between 0 and 255.
         */
        void setAndShowColor(uint8_t red, uint8_t green, uint8_t blue);

    public:
        LightStrip() = delete;
        
        /**
         * @brief initializes the NeoPixel strip on the specified pin with the specified number of pixels and brightness
         * 
         * @param numPixels the number of NeoPixels in the strip
         * @param pin the pin on which the NeoPixels are connected
         * @param type the NeoPixel type, which determines the number of data lines and the order of the color bytes
         * @param brightness the brightness of the NeoPixels, which is a value between 0 and 255
         */
        LightStrip(uint16_t numPixels, uint16_t pin, neoPixelType type = NEO_GRB + NEO_KHZ800, uint8_t brightness = 254);

        
        /**
         * @brief make a little initialisation show, to check if all leds are connected and are working
         * 
         * @param numPixels the number of NeoPixels in the strip
         * @param pin the pin on which the NeoPixels are connected
         * @param type the NeoPixel type, which determines the number of data lines and the order of the color bytes
         * @param brightness the brightness of the NeoPixels, which is a value between 0 and 255
         */
        bool initialisationShow();
        
        /**
         * @brief Sets the brightness of the LEDs on the NeoPixel strip
         * 
         * @param brightness the brightness of the LEDs, which is a value between 0 and 255
         */
        void setBrightness(uint8_t brightness);
        
        /**
         * Blinks the NeoPixels on the strip in the specified color, with the specified delay time.
         * 
         * @param c The color to set the NeoPixels to.
         * @param delayTime The delay time in milliseconds between each LED being turned on or off.
         * @param startLed The index of the first LED to set the color for.
         * @param endLed The index of the last LED to set the color for.
         * @param maxBrightness The maximum brightness of the NeoPixels, which is a value between 0 and 255.
         * @param minBrightness The minimum brightness of the NeoPixels, which is a value between 0 and 255.
         */
        void blinkColor(uint8_t red, uint8_t green, uint8_t blue, uint64_t delayTime, uint8_t startLed, uint8_t endLed);
        
        
        /**
         * Blinks the NeoPixels on the strip in the specified color, with the specified delay time.
         * 
         * @param c The color to set the NeoPixels to.
         * @param delayTime The delay time in milliseconds between each LED being turned on or off.
         * @param startLed The index of the first LED to set the color for.
         * @param endLed The index of the last LED to set the color for.
         * @param maxBrightness The maximum brightness of the NeoPixels, which is a value between 0 and 255.
         * @param minBrightness The minimum brightness of the NeoPixels, which is a value between 0 and 255.
         */
        void blinkColor(Color c, uint64_t delayTime, uint8_t startLed, uint8_t endLed);
        
        /**
         * Sets the color of the LEDs on the NeoPixel strip, and updates the strip with the new color.
         * 
         * @param red The amount of red to set for each LED, between 0 and 255.
         * @param green The amount of green to set for each LED, between 0 and 255.
         * @param blue The amount of blue to set for each LED, between 0 and 255.
         * @param startLed The index of the first LED to set the color for.
         * @param endLed The index of the last LED to set the color for.
         */
        void setLEDs(uint8_t red, uint8_t green, uint8_t blue, uint8_t startLed, uint8_t endLed);
        
        /**
         * Sets the color of the LEDs on the NeoPixel strip, and updates the strip with the new color.
         * 
         * @param c The color to set the LEDs to.
         * @param startLed The index of the first LED to set the color for.
         * @param endLed The index of the last LED to set the color for.
         */
        void setLEDs(Color c, uint8_t startLed, uint8_t endLed);
       
       /**
         * @brief Blinks the NeoPixels on the strip in the specified color, with the specified delay time.
         * 
         * @param c The color to set the NeoPixels to.
         * @param delayTime The delay time in milliseconds between each LED being turned on or off.
         * @param startLed The index of the first LED to set the color for.
         * @param endLed The index of the last LED to set the color for.
         * @param maxBrightness The maximum brightness of the NeoPixels, which is a value between 0 and 255.
         * @param minBrightness The minimum brightness of the NeoPixels, which is a value between 0 and 255.
         */
       void breatheColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t delayTime, uint8_t startLed, uint8_t endLed,  uint8_t maxBrightness = 254, uint8_t minBrightness = 0);
        
        /**
         * @brief Blinks the NeoPixels on the strip in the specified color, with the specified delay time.
         * 
         * @param c The color to set the NeoPixels to.
         * @param delayTime The delay time in milliseconds between each LED being turned on or off.
         * @param startLed The index of the first LED to set the color for.
         * @param endLed The index of the last LED to set the color for.
         * @param maxBrightness The maximum brightness of the NeoPixels, which is a value between 0 and 255.
         * @param minBrightness The minimum brightness of the NeoPixels, which is a value between 0 and 255.
         */
        void breatheColor(Color c, uint8_t delayTime, uint8_t startLed, uint8_t endLed,  uint8_t maxBrightness = 254, uint8_t minBrightness = 0);

        /**
         * @brief sets the color to 0 and thus turns the strip off
        */
        void turnStripOff();

        
        /**
         * @return the number of pixels in the strip
        */
        uint8_t getStripLength();

        /**
         * @brief return the current brightness of the LEDs on the NeoPixel strip
         * @return uint8_t the current brightness of the LEDs on the NeoPixel strip
        */
        uint8_t getStripBrightness();
       
};


//================================================================
//END OF FILE
//================================================================
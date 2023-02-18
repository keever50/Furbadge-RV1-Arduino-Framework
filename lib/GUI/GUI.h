#ifndef _GUI_H
#define _GUI_H
#include <Adafruit_SSD1305.h>
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include <GUI_Object.h>
#include <GUI_Buttons.h>


class GUI : Adafruit_SSD1305
{
public:
    GUI(uint16_t w, uint16_t h, SPIClass *spi, int8_t dc_pin, int8_t rst_pin, int8_t cs_pin, uint32_t bitrate = 8000000UL); //display.begin(0x3C);

    void update();
    GUI_Button* create_button( int ID, int x, int y, int w, int h, const unsigned char* icon, String text );

private:
    GUI_Object* gui_objects[256];
};




#endif 


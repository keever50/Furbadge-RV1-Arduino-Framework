#ifndef _GUI_H
#define _GUI_H
#include <Adafruit_SSD1305.h>
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

class GUI_Display : Adafruit_SSD1305
{
public:
    GUI_Display(uint16_t w, uint16_t h, SPIClass *spi, int8_t dc_pin, int8_t rst_pin, int8_t cs_pin, uint32_t bitrate = 8000000UL); //display.begin(0x3C);
};

class GUI_Object 
{
public:
    void (*init_ptr)();
    void (*update_ptr)(GUI_Object* obj_ptr );
    void* properties_ptr;
    GUI_Display** display_ptr_ptr; //Pointer to the display pointer defined in the GUI_Page. So one pointer can be changed and all objects will follow.

};

class GUI_Page
{
public:
    GUI_Page(GUI_Display* gui);
    GUI_Display* display_ptr;
    void update();

    GUI_Object* create_button( String text );
};



#endif 


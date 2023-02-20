#ifndef _GUI_H
#define _GUI_H
#include <Adafruit_SSD1305.h>
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

class GUI_Display : public Adafruit_SSD1305
{
public:
    GUI_Display(uint16_t w, uint16_t h, SPIClass *spi, int8_t dc_pin, int8_t rst_pin, int8_t cs_pin, uint32_t bitrate = 8000000UL); //display.begin(0x3C);
};

class GUI_Object 
{
public:
    GUI_Object( GUI_Display **display_ptr_ptr, int x, int y, int w, int h, bool (*init_ptr)(GUI_Object *obj_ptr), void (*update_ptr)(GUI_Object *obj_ptr ), void *properties_ptr );

    void init();
    void update();

    int *get_pos();
    int *get_size();

    bool initialized = false;
    GUI_Object *self;
private:
    
    bool (*_init_ptr)(GUI_Object *obj_ptr);
    void (*_update_ptr)(GUI_Object *obj_ptr);
    void *_properties_ptr;
    GUI_Display **_display_ptr_ptr; //Pointer to the display pointer defined in the GUI_Page. So one pointer can be changed and all objects will follow.

    int _pos[2];
    int _size[2];

};

class GUI_Page
{
public:
    GUI_Page(GUI_Display* gui, int object_limit = 64 );
    GUI_Display *display_ptr;
    GUI_Object **object_ptr_array;
    int obj_limit;

    void update();
    GUI_Object *create_button( String text, int x, int y, int w, int h );

private:
    bool add_to_object_array( GUI_Object *obj );
};



#endif 


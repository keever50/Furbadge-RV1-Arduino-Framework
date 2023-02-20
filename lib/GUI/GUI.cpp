#include <GUI.h>
#include <Arduino.h>


//Constructors

GUI_Display::GUI_Display(uint16_t w, uint16_t h, SPIClass *spi, int8_t dc_pin, int8_t rst_pin, int8_t cs_pin, uint32_t bitrate) 
: Adafruit_SSD1305(w, h, spi, dc_pin, rst_pin, cs_pin, bitrate) 
{
    //12V power
    pinMode(24, OUTPUT);
    digitalWrite(24, HIGH);
};

GUI_Page::GUI_Page(GUI_Display* gui, int object_limit )
{
    obj_limit = object_limit;
    display_ptr = gui;    
    object_ptr_array = new GUI_Object* [object_limit]();
};

//GUI Functions

namespace _GUI_Button
{
    struct button_properties 
    {
        String button_text;
    };

    void button_init()
    {
        Serial.println("Button init");
    }

    void button_update(GUI_Object* obj_ptr )
    {
        button_properties* props = (button_properties*)obj_ptr->properties_ptr;

        Serial.println("Button update");
        Serial.println(props->button_text);

    }
};

//Page Functions

void GUI_Page::update()
{
    for(int i=0; i<sizeof(object_ptr_array); i++)
    {
        GUI_Object* obj_ptr = object_ptr_array[i];
        if(obj_ptr->initialized)
        {
            obj_ptr->update_ptr(obj_ptr);
        }
    }

}

bool GUI_Page::add_to_object_array( GUI_Object* obj )
{

    for(int i=0; i<sizeof(object_ptr_array);i++)
    {
           
        if(object_ptr_array[i]->initialized == false) 
        {
            object_ptr_array[i] = obj;
            return true;
        }  
    }

    return false;
}



GUI_Object* GUI_Page::create_button( String text )
{
    GUI_Object* obj = new GUI_Object();
    obj->init_ptr = &_GUI_Button::button_init;
    obj->update_ptr = &_GUI_Button::button_update;
    obj->display_ptr_ptr = &display_ptr; 

    _GUI_Button::button_properties* new_props_ptr = new _GUI_Button::button_properties; //Create ptr to new properties
    new_props_ptr->button_text = text;

    obj->properties_ptr = new_props_ptr; //Give ptr to properties to object

    obj->initialized = true;
    //Add obj to list
    bool succ = add_to_object_array( obj );
    //Serial.println(succ);
    //Serial.println("fdvdgfdfgfdg");
    
    return obj;
}


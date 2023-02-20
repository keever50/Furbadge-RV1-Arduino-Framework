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

GUI_Object::GUI_Object( GUI_Display **display_ptr_ptr, int x, int y, int w, int h, bool (*init_ptr)(GUI_Object *obj_ptr), void (*update_ptr)(GUI_Object *obj_ptr), void *properties_ptr )
{
    
        _init_ptr = init_ptr;
        _update_ptr = update_ptr;
        _display_ptr_ptr = display_ptr_ptr;
        _properties_ptr = properties_ptr; //Give ptr to properties to object

        //_pos = pos;
        //_size = size;
};

//GUI Functions

namespace _GUI_Button
{
    struct button_properties 
    {
        String button_text;
        float* pos[2];
        float* size[2];
    };

    bool button_init( GUI_Object* obj_ptr )
    {
        Serial.println("Button init");
        return true;
    }

    void button_update( GUI_Object* obj_ptr )
    {
        //button_properties* props = (button_properties*)obj_ptr->properties_ptr;

        //GUI_Display** display_ptr_ptr = obj_ptr->display_ptr_ptr;
        //GUI_Display* display_ptr = display_ptr_ptr[0];

        //display_ptr->drawLine(0,0,30,30, WHITE);
        //display_ptr->display();

        Serial.println("Button update");
        //Serial.println(props->button_text);

    }
};


//Object functions

void GUI_Object::init( )
{
    initialized = _init_ptr( self );
}

void GUI_Object::update( )
{
    _update_ptr( self );
}

//Page Functions

void GUI_Page::update()
{
    for(int i=0; i<sizeof(object_ptr_array); i++)
    {
        GUI_Object* obj_ptr = object_ptr_array[i];
        if(obj_ptr->initialized)
        {
            obj_ptr->update();
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


GUI_Object* GUI_Page::create_button( String text, int x, int  y, int w, int h )
{

    _GUI_Button::button_properties* new_props_ptr = new _GUI_Button::button_properties; //Create ptr to new properties
        new_props_ptr->button_text = text;

    GUI_Object* obj = new GUI_Object(&display_ptr, x, y, w, h, &_GUI_Button::button_init, &_GUI_Button::button_update, new_props_ptr);
    obj->self = obj;
    obj->init( );

    //Add obj to list
    bool succ = add_to_object_array( obj );

    return obj;
}


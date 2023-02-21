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
    _obj_limit = object_limit;
    display_ptr = gui;    
    object_ptr_array = new GUI_Object* [_obj_limit]();
};

GUI_Object::GUI_Object( GUI_Display **display_ptr_ptr, int x, int y, int w, int h, bool (*init_ptr)(GUI_Object *obj_ptr), void (*update_ptr)(GUI_Object &obj), void *properties_ptr )
{
    
        _init_ptr = init_ptr;
        _update_ptr = update_ptr;
        _display_ptr_ptr = display_ptr_ptr;
        _properties_ptr = properties_ptr; //Give ptr to properties to object

        _pos[0]=x;
        _pos[1]=y;
        _size[0]=w;
        _size[1]=h;
};



//Object functions

void GUI_Object::init( )
{
    initialized = _init_ptr( self );
}

void GUI_Object::update( )
{
    _update_ptr( *self );
}

int *GUI_Object::get_pos()
{
    return _pos;    
}

int *GUI_Object::get_size()
{
    return _size;    
}

GUI_Display *GUI_Object::get_display()
{
    return *_display_ptr_ptr;
}

void *GUI_Object::get_properties()
{
    return _properties_ptr;
}

//Page Functions

void GUI_Page::update()
{
    display_ptr->clearDisplay();

    for(int i=0; i<_obj_limit; i++)
    {
        GUI_Object* obj_ptr = object_ptr_array[i];
        if(obj_ptr->initialized)
        {
            obj_ptr->update();
        }
    }

    display_ptr->display();

}

bool GUI_Page::add_to_object_array( GUI_Object* obj )
{

    for(int i=0; i<_obj_limit;i++)
    {
           
        if(object_ptr_array[i]->initialized == false) 
        {
            object_ptr_array[i] = obj;
            
            return true;
        }  
    }

    return false;
}

//GUI Functions

namespace _GUI_Button
{
    struct button_properties 
    {
        String button_text;
        int size;
    };

    bool button_init( GUI_Object *obj_ptr )
    {
        Serial.println("Button init");
        return true;
    }

    void button_update( GUI_Object &obj )
    {
        button_properties& props = *((button_properties*)obj.get_properties());
        GUI_Display& disp = *obj.get_display();

        //disp.clearDisplay();

        int *pos = obj.get_pos();
        int *size = obj.get_size();

        disp.setTextSize(props.size);
        disp.setTextWrap(false);
        disp.setTextColor(BLACK);

        int16_t pos_x = (int16_t)pos[0];
        int16_t pos_y = (int16_t)pos[1];

        int16_t text_x; int16_t text_y; uint16_t text_size_x; uint16_t text_size_y;
        String text = props.button_text;
        disp.getTextBounds(text, pos_x, pos_y, &text_x, &text_y, &text_size_x, &text_size_y);

        disp.fillRect(text_x, text_y, text_size_x, text_size_y-props.size, WHITE);
        disp.setCursor(pos_x,pos_y);
        disp.print(text);

        
    }
};


GUI_Object* GUI_Page::create_button( String text, int x, int  y, int s )
{

    _GUI_Button::button_properties* new_props_ptr = new _GUI_Button::button_properties; //Create ptr to new properties
        new_props_ptr->button_text = text;
        new_props_ptr->size = s;
    GUI_Object* obj = new GUI_Object(&display_ptr, x, y, 1, 1, &_GUI_Button::button_init, &_GUI_Button::button_update, new_props_ptr);
    obj->self = obj;
    obj->init( );
    
    //Add obj to list
    bool succ = add_to_object_array( obj );

    return obj;
}


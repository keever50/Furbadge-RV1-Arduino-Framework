
#include <GUI.h>
#include <Arduino.h>

void update(void* obj)
{
    Serial.println("TEST");

    GUI_Button* bb = static_cast<GUI_Button*>(obj);

    Serial.println(bb->text);
    Serial.println("----");

}

GUI_Button::GUI_Button(int ID, int x, int y, int w, int h, const unsigned char* icon, String text )
: GUI_Object( ID, x, y, w, h )
{
    update_ptr = &update;
    
};


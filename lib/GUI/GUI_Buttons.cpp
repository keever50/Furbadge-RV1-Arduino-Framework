
#include <GUI.h>
#include <Arduino.h>

void update(void)
{
    Serial.println("TEST");
}

GUI_Button::GUI_Button(int ID, int x, int y, int w, int h, const unsigned char* icon, String text )
: GUI_Object( ID, x, y, w, h )
{
    update_ptr = &update;
};


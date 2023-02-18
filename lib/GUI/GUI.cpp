#include <GUI.h>
#include <Arduino.h>


//Constructors

GUI::GUI(uint16_t w, uint16_t h, SPIClass *spi, int8_t dc_pin, int8_t rst_pin, int8_t cs_pin, uint32_t bitrate) 
: Adafruit_SSD1305(w, h, spi, dc_pin, rst_pin, cs_pin, bitrate) 
{
    //12V power
    pinMode(24, OUTPUT);
    digitalWrite(24, HIGH);
};




/**************************************************************************/
/*!
    @brief  Updates all created objects and shows them
*/
/**************************************************************************/
void GUI::update()
{
    
}

/**************************************************************************/
/*!
    @brief  Creates a new button object
    @param  x     x coordinate
    @param  y     y coordinate
    @param  w     Width
    @param  h     Height
    @param  icon  A const unsigned char array that represents a 1 bit per pixel bitmap. Make sure it matches the width and height above.
    @param  text  Text under the button. Leave empty for no text.
    @returns      A pointer to the created object.
*/
/**************************************************************************/
GUI_Button* GUI::create_button( int ID, int x, int y, int w, int h, const unsigned char* icon, String text )
{
    GUI_Button* button = new GUI_Button( ID, x, y, w, h, icon, text);
    gui_objects[ID] = button;
    return button;
}
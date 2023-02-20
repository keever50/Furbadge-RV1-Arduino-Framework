/*********************************************************************
This is a library for our Monochrome OLEDs based on SSD1305 drivers

  Pick one up today in the adafruit shop!
  ------> https://www.adafruit.com/products/2675

These displays use SPI or I2C to communicate, 3-5 pins are required to  
interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen below must be included in any redistribution
*********************************************************************/

#include <Wire.h>
#include <SPI.h>
#include "Joystick.h"
#include "icons.h"
#include "GUI.h"

// Used for software SPI
#define OLED_CLK 10
#define OLED_MOSI 11

// Used for software or hardware SPI
#define OLED_CS 9
#define OLED_DC 7

// Used for I2C or SPI
#define OLED_RESET 6

Joystick JOY(12,13,14,15);
GUI_Display gui(128, 32, &SPI1, OLED_DC, OLED_RESET, OLED_CS, 62500000UL);

GUI_Page page = GUI_Page(&gui);
String test_msg = "BUTTON";
GUI_Object* test_button = page.create_button(test_msg);

void setup()   {    

  Serial.begin(9600);
  
}

float x;
float y;
void loop() {

  bool* J = JOY.get_inputs();
  float* pos = JOY.get_direction(J);
  x += pos[0];
  y += pos[1];

  
  //
  //page.update();
  test_button->update_ptr(test_button);
  delay(1000);

}




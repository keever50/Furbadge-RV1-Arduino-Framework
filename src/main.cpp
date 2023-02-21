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


#define OLED_CS 9
#define OLED_DC 7
#define OLED_RESET 6

GUI_Display gui(128, 32, &SPI1, OLED_DC, OLED_RESET, OLED_CS, 62500000UL);
GUI_Page page = GUI_Page(&gui);

void setup()   {  
  delay(500);  
  Serial.begin(9600);
  gui.begin(0x3C);

  gui.display();
  delay(1000);  

  page.create_button("Option A", 10, 8*0, 1 );
  page.create_button("Option B", 10, 8*1, 1 );
  page.create_button("Option C", 10, 8*2, 1 );
  page.create_button("SAVE", 60, 0, 2 );

  page.create_button("Option D", 10, 8*3, 1 );
}


void loop() {
  page.update();

  delay(1000);
}




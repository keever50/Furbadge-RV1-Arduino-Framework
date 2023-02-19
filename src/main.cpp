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
GUI gui(128, 32, &SPI1, OLED_DC, OLED_RESET, OLED_CS, 62500000UL);

GUI_Button* test;
void setup()   {    

  Serial.begin(9600);

  //12V power
  //pinMode(24, OUTPUT);
  //digitalWrite(24, HIGH);

  //GUI_Button test_button = new GUI_Button(0, 5, 5, 16, 16, icon16_bmp_test, "TEST");
  test = gui.create_button(0,5,5,16,16, icon16_bmp_test, "TEXT");
}


float x;
float y;
void loop() {

  bool* J = JOY.get_inputs();
  float* pos = JOY.get_direction(J);
  x += pos[0];
  y += pos[1];

  gui.update();

  delay(1000/60);

}




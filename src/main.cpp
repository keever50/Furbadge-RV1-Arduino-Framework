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
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1305.h>
#include "Joystick.h"

// Used for software SPI
#define OLED_CLK 10
#define OLED_MOSI 11

// Used for software or hardware SPI
#define OLED_CS 9
#define OLED_DC 7

// Used for I2C or SPI
#define OLED_RESET 6

Adafruit_SSD1305 display(128, 32, &SPI1, OLED_DC, OLED_RESET, OLED_CS, 62500000UL);
Joystick JOY(12,13,14,15);



void setup()   {    

  //12V power
  pinMode(24, OUTPUT);
  digitalWrite(24, HIGH);

  display.begin(0x3C);

}


int t = 0;
void loop() {
  if(JOY.get_inputs()[0] == true){
    t = t + 1;
  }
  
  display.clearDisplay();
  display.drawCircle(10+(t%100), 16, 5, WHITE);
  display.display();
  delay(1000/60);

}

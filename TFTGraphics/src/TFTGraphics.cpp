/*
 * Sketch       TFTGraphics.cpp
 * Author       2019-12-11  Charles Geiser 
 * Purpose      Zeigt die Auswahl verschiedener Testfunktionen über ein 
 *              auf einem TFT-Display dargestellten Menü mit Hilfe eine
 *              Tasters.
 * Board        DOIT ESP32 DEVKIT V1
 * Remarks      To select the right TFT driver edit the User_Setup.h 
 *              in the lib directory TFT_eSPI_ID1559 or set the corresponding
 *              build-flags like those in the platformio.ini of this project
 * 
 *              build_flags =
 *                 -DUSER_SETUP_LOADED=1
 *                 -DST7735_DRIVER=1
 *                 -DST7735_GREENTAB2=1
 *                 -DTFT_WIDTH=128
 *                 -DTFT_HEIGHT=160
 *                 -DTFT_MISO=19
 *                 -DTFT_MOSI=23
 *                 -DTFT_SCLK=18
 *                 -DTFT_CS=5
 *                 -DTFT_DC=2
 *                 -DTFT_RST=4
 *                 -DLOAD_GLCD=1
 *                 -DLOAD_FONT2=1
 *                 -DLOAD_FONT4=1
 *                 -DLOAD_FONT6=1
 *                 -DLOAD_FONT7=1
 *                 -DLOAD_FONT8=1
 *                 -DLOAD_GFXFF=1
 *                 -DSMOOTH_FONT=1
 *                 -DSPI_FREQUENCY=27000000
 *
 * Reference    Based on: "Arduino the Object Oriented way"
 *              https://paulmurraycbr.github.io/ArduinoTheOOWay.html
 *
 * The test functions are offered in a menu. The selected menu item is highlighted. 
 * The menu is navigated with a push button. A short click (50ms .. 250ms) switches 
 * to the next menu item, a long click (> 250ms) calls the selected test function. 
 * Clicks shorter than 50ms are interpreted as switch bounces and are ignored. 
 * The menu may contain more lines than can be displayed on the LCD. The menu 
 * item are then displayd page by page
 *   
 * The texts of the menu items and the corresponding test functions are stored 
 * in an array MenuItem menuItems[]. A MenuItem consists of a text and a 
 * reference to the action to be done, defined as follows: 
 * struct MenuItem {const char * txt; void (& action) (void);} 
 * 
 * The sketch shows how the time can be displayed on a 160x128 pixel TFT display 
 * in analog or digital form. The date and time are extracted from the compile 
 * time __TIME__, __DATE__ and thus set the RTC of the ESP32.
 *
 * To illustrate the capabilities of the TFT_eSPI library there are also test 
 * routines for points, lines, rectangles, rounded rectangles, circles, triangles, 
 * some fractals (Mandelbrot, Barnsley-Fern, Sierpinsky-Triangle), 
 * text, fonts etc. implemented.
 * 
 *                      
 *                      --+
 * Connections            |-- GND   --> GND         Connections
 * TFT 160 x 128 Pixel    |-- Vcc   --> 3.3V        DOIT ESP32 DEVKIT V1
 * 1.8" Color LCD  with   |-- SCL   --> 18          SPI SCK
 * SPI ST7735 Controller  |-- SDA   --> 23          SPI MOSI
 * NOMEN_TEC V2.0         |-- RES   --> 4            
 *                        |-- DC    --> 2                        
 *                        |-- CS    --> 5           SPI SS  
 *                        |-- BL    --> 3V3 / or open
 *                      --+                      
 *                        
 *                            _I_
 * Pushbutton           GND --o o-- 13 INPUT_PULLUP                    
 */
#include <Arduino.h>
#include <sys/time.h>
#include "TFTGraphics.h"                      

#define MS_REFRESH  1000

DigitalClock      myDigitalClock = DigitalClock(MS_REFRESH);
AnalogClock       myAnalogClock = AnalogClock(MS_REFRESH);
TFT_eSPI          myTFT = TFT_eSPI(128, 160);
Menu              myMenu(myTFT, menuItems, nbrMenuItems, NBR_DISPLAYED_MENUITEMS);
MenuControlButton myControlButton(PIN_BUTTON, myMenu);

/**
 * Sets the RTC of the ESP32 to the compile time and date. The delay  
 * due to the upload time can be compensated by specifying a value 
 * for sec_uploadCompensation (approx. 15 sec).
 * 
 * Example of compile time and date strings:
 * __TIME__   19:32:39
 * __DATE__   Apr 17 2020
 * 
 */
void setCompileTime(int sec_uploadCompensation = 0)
{
  struct tm time;
  char str_month[5];
  int y, mday;
  timeval sec_musec;
  static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
  sscanf(__DATE__, "%s%d%d", str_month, &mday, &y);
  sscanf(__TIME__, "%2d%*c%2d%*c%2d", &time.tm_hour, &time.tm_min, &time.tm_sec);
  //Serial.println(__DATE__);
  //Serial.println(__TIME__);
  time.tm_mon = (strstr(month_names, str_month) - month_names) / 3;  // Calculate the month number
  time.tm_year = y - 1900;
  time.tm_mday = mday;

  sec_musec.tv_sec = mktime(&time) + sec_uploadCompensation;
  sec_musec.tv_usec= 0;
  settimeofday(&sec_musec, NULL); // Set the internal RTC of the ESP32
}

void setup() 
{
  Serial.begin(COMPORT_SPEED);

    // Show default pins for SPI and I2C
  Serial.printf("SPI MOSI = %d\r\n", MOSI);
  Serial.printf("SPI MISO = %d\r\n", MISO);
  Serial.printf("SPI SCK  = %d\r\n", SCK);
  Serial.printf("SPI SS   = %d\r\n", SS);
  Serial.printf("I2C SCL  = %d\r\n", SCL);
  Serial.printf("I2C SDA  = %d\r\n", SDA);
  

  setCompileTime(15);     // Initialize the RTC of the ESP32 
  myTFT.init();
  myTFT.setRotation(1);
  myTFT.setTextFont(1);   // Set smallest font. Allowed: 1,2,4,6,7,8
  myTFT.setTextSize(1);   // Set smallest text size multiplier. Allowed: 1..7
  
  myControlButton.setup();
  myMenu.setup();
}

void loop() 
{
  myControlButton.loop();
}

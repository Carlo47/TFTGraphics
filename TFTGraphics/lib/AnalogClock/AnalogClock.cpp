/**
 * Class        AnalogClock.cpp
 * Author       2020-04-13 Charles Geiser
 * 
 * Purpose      Implements a class AnalogClock which displays an analog clock face
 *              on a TFT display. The method loop() periodically hands back the 
 *              control to the main program and displays the dial only every
 *              msRefresh seconds. 
 *              The time is fetched from the ESP32 module's internal RTC by calling 
 *              the getlocaltime function.  
 *             
 * Board        ESP32 / TFT 128 x 160 with SPI ST7735 driver 
 * Remarks      The refresh rate in ms is passed to the class contructor
 * References     
 */
#include "AnalogClock.h"

bool AnalogClock::isRunning()
{
  return _isRunning;
}

void AnalogClock::stop()
{
  //Serial.println("clock stop");
  _isRunning = false;
}

void AnalogClock::setup()
{
  myTFT.fillScreen(TFT_BLACK);
  myTFT.setTextColor(TFT_GREEN, TFT_BLACK);
  myTFT.setTextSize(2);
  drawDial(myTFT.width()/2,55,50);
  _isRunning = true;
}

void AnalogClock::loop()
{
  if (millis() > _msPrevious + _msRefresh )
  {
    _msPrevious = millis();
    updateDial();
  }
}

/**
 * Refreshs the dial
 * Called every msRefresh seconds from loop
 */
void AnalogClock::updateDial()
{
  char theDate[12];
  getLocalTime(&_rtcTime);
  _hh = _rtcTime.tm_hour;
  _mm = _rtcTime.tm_min;
  _ss = _rtcTime.tm_sec;
  myTFT.fillCircle(_mx, _my, _rTh, TFT_BLACK);        // Erase old hands 
  drawHands(_hh, _mm, _ss, _mx, _my, _rH, _rM, _rS);  // Draw new hands
  strftime(theDate, 20, "%F", &_rtcTime);             // Date as yyyy-mo-dd
  myTFT.drawString(theDate, (myTFT.width()-myTFT.textWidth(theDate))/2, 110); 
}


void AnalogClock::drawTickMarks(int mx, int my, int r1, int r2, int nbr, int color)
{
  int x1, y1, x2, y2;
  float phi, sinPhi, cosPhi; 
  float phi0 = 2 * PI / nbr;
  
  for (int i = 0; i < nbr; i++)
  {
    phi = phi0 * i;
    sinPhi = sin(phi);
    cosPhi = cos(phi);
    x1 = mx + r1 * cosPhi;
    y1 = my + r1 * sinPhi;
    x2 = mx + r2 * cosPhi;
    y2 = my + r2 * sinPhi;
    myTFT.drawLine(x1, y1, x2, y2, color);
  }
}

void AnalogClock::drawHands(byte hh, byte mm, byte ss, int mx, int my, int rH, int rM, int rS)
{
  float wSec, wMin, wHour;
  int xH, yH, xM, yM, xS, yS;

  wSec = PI/30 * ss;                                       
  wMin = PI/30 * (mm + ss / 60);
  wHour =PI/6 * (hh + mm / 60 + ss / 3600);

  wSec -= PI/2;	// subtract PI/2 to rotate to the 1st quadrant
  wMin -= PI/2;
  wHour -= PI/2;

  xH = rH * cos(wHour) + mx;
  yH = rH * sin(wHour) + my;
  xM = rM * cos(wMin) + mx;
  yM = rM * sin(wMin) + my;
  xS = rS * cos(wSec) + mx;
  yS = rS * sin(wSec) + my;

  myTFT.drawLine(mx, my, xH, yH, TFT_WHITE);
  myTFT.drawLine(mx, my, xM, yM, TFT_WHITE);
  myTFT.drawLine(mx, my, xS, yS, TFT_RED);
  myTFT.fillCircle(mx, my, 3, TFT_RED);        
}

void AnalogClock::drawDial(int mx, int my, int radius)
{
  _mx = mx;       // dial center x
  _my = my;       // dial center y
  _r = radius;    // outer radius of dial
  _rH = _r-28;    // radius of hour hand
  _rM = _r-18;    // radius of minute hand
  _rS = _r-15;    // radius of second hand
  _rTh = _r-13;   // radius of hour tickmarks
  _rTm = _r-7;    // radius of minute tickmarks

  myTFT.drawRect(0,0,myTFT.width(),myTFT.height(), TFT_GREEN); // Border
  myTFT.fillCircle(_mx, _my, _r, TFT_BLUE);          // Draw a blue disc
  myTFT.fillCircle(_mx, _my, _r - 3, TFT_BLACK);     // Draw a black disc so that only a blue ring remains 
  myTFT.fillCircle(_mx, _my, 3, TFT_RED);            // Draw a red disc 
    
  drawTickMarks(_mx, _my, _r, _rTm,  60, TFT_BLUE);  // Draw short minute tick marks
  drawTickMarks(_mx, _my, _r, _rTh,  12, TFT_BLUE);  // Draw longer hour tickmarks
}

/**
 * Class        AnalogClock.cpp
 * Author       2020-04-13 Charles Geiser
 * 
 * Purpose      Implements a class DigitalClock which displays time and date on a TFT display.
 *              The method loop() periodically hands back the control to the main
 *              program and updates the display only every msRefresh seconds. 
 *              The time is fetched from the ESP32 module's internal RTC by calling 
 *              the getlocaltime function.  
 *             
 * Board        ESP32 / TFT 128 x 160 with SPI ST7735 driver 
 * Remarks      The refresh rate in ms is passed to the class contructor
 * References     
 */
#include "DigitalClock.h"

bool DigitalClock::isRunning()
{
    return _isRunning;
}

void DigitalClock::stop()
{
    _isRunning = false;
}

void DigitalClock::setup()
{
    _isRunning = true;
}

void DigitalClock::loop()
{
    if (millis() > _msPrevious + _msRefresh)  // Get new time every sec
    {
        _msPrevious = millis();
        getLocalTime(&_rtcTime);
        myTFT.fillScreen(TFT_ORANGE);
        myTFT.setRotation(1);
        myTFT.setTextSize(1);
        myTFT.setTextFont(4);
        myTFT.setTextColor(TFT_WHITE, TFT_ORANGE);
        strftime(_s, 20, "%T", &_rtcTime); // Time as hh:mm:ss
        myTFT.drawString(_s,(myTFT.width() - myTFT.textWidth(_s))/2, myTFT.height()/2 - myTFT.fontHeight());
        strftime(_s, 20, "%F", &_rtcTime); // Date as yyyy-mo-dd
        myTFT.drawString(_s,(myTFT.width() - myTFT.textWidth(_s))/2, myTFT.height()/2);
    }
}

/**
 * DigitalClock.h
 * 
 * Declaration of the class DigitalClock.The object myTFT is  
 * declared as external because it resides in the main program.
 */ 
#ifndef _DIGITALCLOCK_H_
#define _DIGITALCLOCK_H_

#include <Arduino.h>
#include <sys/time.h>
#include <TFT_eSPI.h>

extern TFT_eSPI myTFT;

class DigitalClock
{
  public:
    DigitalClock(uint32_t msRefresh) : _msRefresh(msRefresh) {}

    void setup();
    void loop();
    bool isRunning();
    void stop();

  private:
    bool _isRunning = false;
    uint32_t _msPrevious = millis();
    uint32_t _msRefresh;
    struct tm _rtcTime;
    char _s[20];
};
#endif
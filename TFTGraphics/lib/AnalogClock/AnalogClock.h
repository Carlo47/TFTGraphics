/**
 * AnalogClock.h
 * 
 * Declaration of the class AnalogClock.The object myTFT is  
 * declared as external because it resides in the main program.
 */ 
#ifndef _ANALOGCLOCK_H_
#define _ANALOGCLOCK_H_

#include <Arduino.h>
#include <sys/time.h>
#include <TFT_eSPI.h>

extern TFT_eSPI myTFT;

class AnalogClock 
{
  public:
    AnalogClock(uint32_t msRefresh) : _msRefresh(msRefresh) {}

    void setup();
    void loop();
    bool isRunning();
    void stop();
    void updateDial();

  private:
    bool _isRunning = false;
    int _hh, _mm, _ss, _mx, _my, _rH, _rM, _rS, _rTh, _r, _rTm;
    uint32_t _msPrevious = millis();
    uint32_t _msRefresh;
    struct tm _rtcTime;
    void drawDial(int mx, int my, int radius);
    void drawTickMarks(int mx, int my, int r1, int r2, int nbr, int color);
    void drawHands(uint8_t hh, uint8_t mm, uint8_t ss, int mx, int my, int rH, int rM, int rS);
};
#endif

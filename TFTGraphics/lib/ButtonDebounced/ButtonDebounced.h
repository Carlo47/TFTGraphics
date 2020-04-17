/**
 * ButtonDebounced.h
 * 
 * Declaration of the class ButtonDebounced. The methods onClick (), onLongClick () 
 * and onDoubleKlick () are virtual and are implemented later in the derived class
 * (see class MenuControlButton).
 */
#ifndef _BUTTONDEBOUNCED_H_
#define _BUTTONDEBOUNCED_H_
#include <Arduino.h>

class ButtonDebounced
{
  public:
    ButtonDebounced(uint8_t pin) : _pin(pin) {}

    void setup();
    void loop();

  protected:
    // Virtual methods to be implemented in the derived class
    virtual void onClick();
    virtual void onLongClick();
    virtual void onDoubleClick();

  private:
    const uint8_t _pin;
    uint8_t _clickCount;
    int _btnState;
    int _msDebounce = 50;        // After 50ms the button should have reached a steady state
    int _msLongClick = 300;      // A Button that is held longer than 300ms is considered as longClick
    int _msDoubleClickGap = 250; // Two button clicks within 250ms count as a doubleClick
    unsigned long _msButtonDown;
    unsigned long _msFirstClick;  
};
#endif
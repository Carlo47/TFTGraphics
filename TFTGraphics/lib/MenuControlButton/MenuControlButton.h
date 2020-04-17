/**
 * MenuControlButton.h
 * 
 * Declares the class MenuControlButton. It inherits the the class 
 * ButtonDebounced. The virtual methods onClick(), onLongClick() and
 * onDoubleClick() of the base class are implemented in MenuControlButton.cpp
 */ 
#ifndef _MENUCONTROLBUTTON_H_
#define _MENUCONTROLBUTTON_H_

#include "ButtonDebounced.h"
#include "Menu.h"
#include "DigitalClock.h"
#include "AnalogClock.h"

class MenuControlButton: public ButtonDebounced
{
  public:
    MenuControlButton(byte pin, Menu &menu) : ButtonDebounced(pin), _menu(menu) {}

  protected:
    // Virtual methods of the base class
    void onClick();
    void onLongClick();
    void onDoubleClick();

  private:
    Menu &_menu;
    bool _actionDone = false;
};
#endif
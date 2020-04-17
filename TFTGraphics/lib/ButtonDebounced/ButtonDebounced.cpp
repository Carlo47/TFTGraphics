/**
 * Class        ButtonDebounced.cpp
 * Author       2020-04-13 Charles Geiser
 * 
 * Purpose      Implements a button class which debounces a mechanical
 *              pushbutton and provides the virtual methods click(),
 *              doubleClick() and longClick.
 * 
 * Board        Any Arduino / ESP8266 / ESP32 board  
 * Remarks      The user of this class has to implement in his derived class
 *              the three virtual methods.
 * References   http://www.technoblogy.com/show?1YHJ   
 */

#include "ButtonDebounced.h"

void ButtonDebounced::setup() 
{
  pinMode(_pin, INPUT_PULLUP);
  _btnState = HIGH;
  _clickCount = 0;
  _msFirstClick = 0;
}

void ButtonDebounced::loop() 
{
  int prevState = _btnState;
  _btnState = digitalRead(_pin);                   // Knopf abfragen, gedrückt LOW
  
  if (prevState == HIGH && _btnState == LOW)       // Knopf gedrückt
  {
    _msButtonDown = millis();                      // Zeit merken
  }
  else if (prevState == LOW && _btnState == HIGH)  // Knopf losgelassen ...
  {
    if (millis() - _msButtonDown < _msDebounce)    // ... Schalter prellt
    {
      // Prellen ignorieren
    }
    else if (millis() - _msButtonDown > _msLongClick)    // Zeit grösser als 300 ms
    {
      onLongClick();
    }
    else
    {
      _clickCount++;                            // Zeit des 1. Clicks nur merken
      if (_clickCount == 1) 
        _msFirstClick = millis();
    }
  }
  else                                          // Dieser Zweig wird durchlaufen, wenn im
  {                                             // loop nichts zu tun ist
    if (_clickCount == 1 && millis() - _msFirstClick > _msDoubleClickGap) // Zeit nach 1. Click abgelaufen
      {
        _msFirstClick = 0;
        _clickCount = 0;
        onClick();
      }
    else if (_clickCount > 1)                   // Mehr als 1 Click getätigt 
    {
      _msFirstClick = 0;
      _clickCount = 0;
      onDoubleClick(); 
    }     
  }
}


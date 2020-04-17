/**
 * Class        MenuControlButton.cpp
 * Author       2020-04-13 Charles Geiser
 * 
 * Purpose      Implements a class MenuControlButton  which is derived from the
 *              base class ButtonDebounced. It implements the virtual methods 
 *              onClick(), onLongClick() and onDoubleClick of the base class.
 *              
 * Board        ESP32 / TFT 128 x 160 with SPI ST7735 driver 
 * Remarks      The methods of this class handle all the functionality
 *              of the menu system
 * References     
 */

/**
 * Implements the virtual methods of the base class ButtonDebounced
 * The used objects DigitalClock and AnalgClock are declared as external
 */ 
#include "MenuControlButton.h"

extern DigitalClock myDigitalClock;
extern AnalogClock myAnalogClock;

void MenuControlButton::onClick()
{
  Serial.println("onClick called");
  if (myDigitalClock.isRunning())
  {
    myDigitalClock.stop();  // Stopps the clock and completes the onDoubleClick-action.
    return;                 // Subsequently _actionDone is set to true. The next onClick()
  }                         // shows the menu again.
  

  if (myAnalogClock.isRunning())
  {
    myAnalogClock.stop();   // Stopps the clock and completes the onDoubleClick-action.
    return;                 // Subsequently _actionDone is set to true. The next onClick()
  }                         // shows the menu again.

  if (_actionDone)
  {
    _menu.show();           // Shows menu again
    _actionDone = false;
  }
  else
    _menu.nextMenuItem();  
}

void MenuControlButton::onLongClick()
{
  Serial.println("onLongClick called");
  _menu.doAction();         // Do the menu action
  _actionDone = true;
}

void MenuControlButton::onDoubleClick()
{
  Serial.println("onDoubleClick called");
  // Could be prevMenuItem() but is not implemented
}


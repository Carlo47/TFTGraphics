/**
 * Class        Menu.cpp
 * Author       2020-04-13 Charles Geiser
 * 
 * Purpose      Implements a class Menu which shows up to 16 menu lines on a TFT display
 *              with 160 x 128 pixels. The number of menu lines is not limited. If there 
 *              are more lines than the display can show, the other menu items are  
 *              offered page by page. How many menu items a menu page displays can be specified 
 *              with the optional argument "nbrDisplayedMenuItems". If this argument is 
 *              missing in the constructor, it takes the value 0 and the only menu page 
 *              shows all defined menu items. The user must then ensure that nbrDisplayedMenuItems 
 *              is not larger than the number of possible lines on the display. 
 *              
 * Board        ESP32 / TFT 128 x 160 with SPI ST7735 driver 
 * Remarks      
 * References     
 */
#include "Menu.h"

void Menu::setup()
{
  if (_nbrDisplayedMenuItems == 0)
    _nbrDisplayedMenuItems = _nbrMenuItems;

  _menuPage = _selectedMenuItem / _nbrDisplayedMenuItems;
  _startMenuItem = _menuPage * _nbrDisplayedMenuItems;
  _stopMenuItem = _startMenuItem + _nbrDisplayedMenuItems;
  
  Menu::show();
}

void Menu::loop() // Not used
{
}

// Show the menu
void Menu::show(bool clearScreen)
{
  if (clearScreen) _tft.fillScreen(TFT_BLACK);
  _tft.setTextColor(TFT_GREEN, TFT_BLACK);
  _tft.setTextFont(1);
  _tft.setTextSize(1);
  _tft.setCursor(0,0);

  for(int i = _startMenuItem; i < _stopMenuItem; i++)
  {
    if (i == _selectedMenuItem)
      _tft.setTextColor(TFT_RED, TFT_GREEN);
    else
      _tft.setTextColor(TFT_GREEN, TFT_BLACK);
      
    _tft.println(_menuItems[i].txt);
  }      
}

// Move selection to the next menuitem
void Menu::nextMenuItem()
{
  _previousMenuPage = _menuPage;
  _selectedMenuItem++;
  _selectedMenuItem %= _nbrMenuItems;
  _menuPage = _selectedMenuItem / _nbrDisplayedMenuItems;
  _startMenuItem = _menuPage * _nbrDisplayedMenuItems;
  _stopMenuItem = _startMenuItem + _nbrDisplayedMenuItems;
  if (_stopMenuItem > _nbrMenuItems) { _stopMenuItem = _nbrMenuItems; }

  // If new page, clear the menu and start a new page otherwise just
  // overwrite old entries to prevent flickering.
  show(_previousMenuPage != _menuPage); 
}

void Menu::doAction()
{
  (_menuItems[_selectedMenuItem]).action();
}
    

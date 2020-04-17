/**
 * Menu.h
 * 
 * Declaration of the class Menu. The constructor needs a reference to 
 * the TFT object, the array of menu entries and their number, as well 
 * as the number of menu lines to be displayed on a menu page. 
 * If the default value 0 is used, an attempt is made to show all menu 
 * lines, which can, however, result in an overflow on the display.
 */ 
#ifndef _MENU_H_
#define _MENU_H_
#include <TFT_eSPI.h>

struct MenuItem {const char *txt; void (&action)();};
extern MenuItem menuItems[];
extern int nbrMenuItems;

class Menu
{
  public:
    Menu(TFT_eSPI &tft, MenuItem menuItems[], int nbrMenuItems, int nbrDisplayedMenuItems = 0) : 
      _tft(tft), 
      _menuItems(menuItems), 
      _nbrMenuItems(nbrMenuItems),
      _nbrDisplayedMenuItems(nbrDisplayedMenuItems)
    { 
    }

    void setup();
    void loop();            // Not used
    void nextMenuItem();    // Selects the next menu item
    void show(bool clearScreen = true);
    void doAction();        // Calls the action associated wis the selected menu item

  private:
    TFT_eSPI &_tft;
    MenuItem *_menuItems;   // Pointer to the array of menuitems
    uint8_t  _nbrMenuItems;
    int      _selectedMenuItem = 0;
    int      _startMenuItem = 0;
    int      _stopMenuItem;
    int      _menuPage = 0;
    int      _previousMenuPage = 0;
    int      _nbrDisplayedMenuItems;
};
#endif
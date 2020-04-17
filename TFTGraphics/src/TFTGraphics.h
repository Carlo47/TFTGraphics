/**
 * TFTGraphics.h
 * 
 * Includes und definitions for the main program
 */
#include "MenuControlButton.h"
#include "MenuItems.h"
#include "Testfunctions.h"

#ifndef _TFTGraphics_H_
#define _TFTGraphics_H_

#define COMPORT_SPEED   115200
#define NBR_DISPLAYED_MENUITEMS 10  // Anzahl Zeilen auf einer Menüseite
#define PIN_BUTTON  13

uint16_t Color[] = {  TFT_BLACK,
                      TFT_NAVY,
                      TFT_DARKGREEN,
                      TFT_DARKCYAN,
                      TFT_MAROON,
                      TFT_PURPLE,
                      TFT_OLIVE,
                      TFT_LIGHTGREY,
                      TFT_DARKGREY,
                      TFT_BLUE,
                      TFT_GREEN,
                      TFT_CYAN,
                      TFT_RED,
                      TFT_MAGENTA,
                      TFT_YELLOW,
                      TFT_WHITE,
                      TFT_ORANGE,
                      TFT_GREENYELLOW,
                      TFT_PINK,
                    };

int nbrOfColors = sizeof(Color) / sizeof(Color[0]);
#endif
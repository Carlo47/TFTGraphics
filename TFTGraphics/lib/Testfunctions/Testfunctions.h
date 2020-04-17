/**
 * Testfuncions.h
 * 
 * Includes and extern-declarations needed for the test functions
 */ 
#ifndef _TESTFUNCTIONS_H_
#define _TESTFUNCTIONS_H_
#include <Arduino.h>
#include "MenuControlButton.h"
#include "Menu.h"
#include "DigitalClock.h"
#include "AnalogClock.h"
extern uint16_t Color[];
extern int nbrOfColors;
extern MenuControlButton myControlButton;
extern DigitalClock myDigitalClock;
extern AnalogClock  myAnalogClock;
#endif
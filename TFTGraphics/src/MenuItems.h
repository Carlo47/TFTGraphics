/**
 * MenuItems.h
 * 
 * Here the menu is defined as an array of pairs {MenuText, MenuFunction}. 
 * The menu functions are declared external because they are implemented in 
 * the module Testfunctions.cpp
 */ 

#ifndef _MENUITEMS_H_
#define _MENUITEMS_H_

// Function Prototypes
extern void testLines();
extern void testRectangles();
extern void testRoundRectangles();
extern void testCircles();
extern void testTriangles();
extern void testSierpinskyDreieck();
extern void testMandelbrot();
extern void testBarnsleyFarn();
extern void testZufallswanderung();
extern void testZufallspunkte();
extern void testFarbVieleck();
extern void testRGBColorSpace();
extern void testHSVColorSpace();
extern void testRotateText();
extern void testTextSizes();
extern void testFonts();
extern void testDigitalUhr();
extern void testAnalogUhr();
extern void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v );

MenuItem menuItems[] =
{
  {"Digitaluhr",            testDigitalUhr},
  {"Analoguhr ",            testAnalogUhr},
  {"Linien",                testLines},
  {"Rechtecke",             testRectangles},
  {"Abgerundete Rechtecke", testRoundRectangles},
  {"Kreise",                testCircles},
  {"Dreiecke",              testTriangles},
  {"Sierpinsky Dreieck",    testSierpinskyDreieck},
  {"Mandelbrot",            testMandelbrot},
  {"Fraktales Farn",        testBarnsleyFarn},
  {"Zufallswanderung",      testZufallswanderung},
  {"Zufallspunkte",         testZufallspunkte},
  {"HSV-Farbkreis",         testFarbVieleck},
  {"RGB-Farbraum",          testRGBColorSpace},
  {"HSV-Farbraum",          testHSVColorSpace},
  {"Text rotieren",         testRotateText},
  {"Text-Groessen",         testTextSizes},
  {"Fonts",                 testFonts},
};

int nbrMenuItems = sizeof(menuItems) / sizeof(menuItems[0]);
#endif
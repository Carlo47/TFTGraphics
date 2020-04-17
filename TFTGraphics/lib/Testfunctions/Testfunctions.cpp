/**
 * Sketch       Testfunctions.cpp
 * Author       2020-04-13 Charles Geiser
 * 
 * Purpose      A collection of functions to demonstrate the capabilities
 *              of the ESP32 and a a connected color TFT display. 
 *             
 * Board        ESP32 / TFT 128 x 160 with SPI ST7735 driver 
 * Remarks      The refresh rate in ms is passed to the class contructor
 * References     
 */

/*
 * Definition der Testfunktionen
 */ 
#include "Testfunctions.h"

// Umwandlung des HSV- in den RGB-Farbraum
void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v )
{
  int i;
  float f, p, q, t;

  if( s == 0 ) {
    // achromatic (grey)
    *r = *g = *b = v;
    return;
  }

  h /= 60;      // sector 0 to 5
  i = floor( h );
  f = h - i;      // factorial part of h
  p = v * ( 1 - s );
  q = v * ( 1 - s * f );
  t = v * ( 1 - s * ( 1 - f ) );

  switch( i ) {
    case 0:
      *r = v;
      *g = t;
      *b = p;
      break;
    case 1:
      *r = q;
      *g = v;
      *b = p;
      break;
    case 2:
      *r = p;
      *g = v;
      *b = t;
      break;
    case 3:
      *r = p;
      *g = q;
      *b = v;
      break;
    case 4:
      *r = t;
      *g = p;
      *b = v;
      break;
    default:    // case 5:
      *r = v;
      *g = p;
      *b = q;
      break;
  }
}

// Zeichnet Linien ausgehend von allen 4 Ecken
void testLines()
{
  int w = myTFT.width();
  int h = myTFT.height();
  
  myTFT.fillScreen(TFT_BLACK);
  for(int i = 0; i < w; i +=7 )
  {
    myTFT.drawLine(0, 0, w, i, TFT_GREEN);
    myTFT.drawLine(w, 0, w-i, h, TFT_BLUE);
    myTFT.drawLine(w, h, 0, h-i, TFT_RED);
    myTFT.drawLine(0, h, i, 0, TFT_YELLOW);
  }
}

// Zeichnet kleiner werdende Rechtecke
void testRectangles()
{
  int w = myTFT.width();
  int h = myTFT.height();
  
  myTFT.fillScreen(TFT_BLACK);
  for (int i = 0; i < h/2; i += 5)
  {
    myTFT.drawRect(i, i, w-2*i, h-2*i, Color[random(0,nbrOfColors)]);
    delay(100);  
  }
}

// Zeichnet abgerundete Rechtecke mit unterschiedlichen Radien
void testRoundRectangles() 
{
  myTFT.fillScreen(TFT_BLACK);
  int w = myTFT.width();
  int h = myTFT.height();
  int rectH =40;
  int rectR = 15;

  for(int i = 0 ; i < h/2; i+=7) 
  {
    rectR = i+1;
    rectH = 2 * rectR;
    myTFT.drawRoundRect(0, (h-rectH)/2, w, rectH, rectR, TFT_RED);
    myTFT.drawRoundRect((w-rectH)/2, 0, rectH, h, rectR, TFT_MAGENTA);
    delay(200);
  }
}

// Zeichnet gefüllte Farbkreise
void testCircles()
{
  int w = myTFT.width();
  int h = myTFT.height();

  myTFT.fillScreen(TFT_BLACK);
  for(int i = 0; i < h/2; i += 3)
  {
    myTFT.fillCircle(w/2, h/2, h/2 - 2*i, Color[random(0,nbrOfColors)]); 
  }
}

// Zeichnet blaue und rote Dreiecke
void testTriangles()
{
  int w = myTFT.width()-1;
  int h = myTFT.height();
  myTFT.fillScreen(TFT_BLACK);
  for(int i = 0; i < w; i += 5)
  {
    myTFT.drawTriangle(w/2, 0, 0, h/2, i, i, TFT_RED);  
    myTFT.drawTriangle(0, h/2, w/2, h, i, w-i, TFT_BLUE); 
    myTFT.drawTriangle(w/2, 0, w, h/2, w-i, i, TFT_BLUE);  
    myTFT.drawTriangle(w, w/2, w/2, h, w-i, w-i, TFT_RED); 
  }
}

// Fraktales Sierpinsky-Dreieck darstellen.
// 1) Wähle einen beliebigen Anfangspunkt, hier P(20,20)
// 2) Wähle zufällig eine Ecke, markiere die Mitte der Strecke P-Ecke
// 3) Die Mitte wird zum neuen Punkt P
// 4) Wiederhole ab 3)
void testSierpinskyDreieck()
{
  int ecke[3][2] = {{0,0}, {159,0}, {79,127}};
  unsigned int farbe[] = {TFT_RED, TFT_BLUE, TFT_GREEN};
  int p[] = {20,20};
  int k, x, y, mx, my;
  
  myTFT.fillScreen(TFT_BLACK);
  for(int i = 0; i < 15000; i++)
  {
    k = random(0,3);
    x = ecke[k][0];
    y = ecke[k][1];
    mx = (x-p[0])/2 + p[0]; 
    my = (y-p[1])/2 + p[1];
    myTFT.drawPixel(mx, my, farbe[k]);
    p[0] = mx;
    p[1] = my;
  }
  myTFT.drawRect(0, 0, myTFT.width(), myTFT.height(), TFT_YELLOW);
}

// Mandelbrot-Apfelmännchen darstellen
void testMandelbrot()
{
  myTFT.setRotation(1);
  int maxIteration = 1000;
  int w = myTFT.width();
  int h = myTFT.height();
  unsigned int farbe;
  myTFT.fillScreen(TFT_WHITE);

  for(int zeile = 0; zeile < h; zeile++)
  {
    for(int spalte = 0; spalte < w; spalte++)
    {
      float c_re = (spalte - w/2.0) * 4.0 / w;
      float c_im = (zeile- h/2.0) * 4.0 / h;
      float x = 0;
      float y = 0;
      int iteration = 0;
      while (x*x + y*y <=4 && iteration < maxIteration)
      {
        float x_neu = x*x - y*y + c_re;
        y = 2*x*y + c_im;
        x = x_neu;
        iteration++;
      }
      if (iteration < maxIteration)
      {
        if (iteration < nbrOfColors) farbe = Color[iteration];
        else farbe = TFT_WHITE;
        myTFT.drawPixel(spalte, zeile, farbe);
      }
      else
          myTFT.drawPixel(spalte, zeile, TFT_BLACK);
    }
  }
  myTFT.drawRect(0, 0, myTFT.width(), myTFT.height(), TFT_BLUE);
}

// Zufällig Punkte in einer zufällig gewählten Farbe 
// auf dem ganzen Display setzen
void testZufallspunkte()
{
  int x, y;
  myTFT.fillScreen(TFT_BLACK);
  
  for(unsigned int i = 0; i < 32000; i++)
  {
    x = random(0, myTFT.width());
    y = random(0, myTFT.height());
    myTFT.drawPixel(x, y, Color[random(1,8)]);  
  }
  myTFT.drawRect(0, 0, myTFT.width(), myTFT.height(), TFT_GREEN);
}

// Fraktales Farn mit iterierten Funktionen darstellen 
void testBarnsleyFarn() 
{
  float x = 0;
  float y = 0;

  myTFT.fillScreen(TFT_BLACK);

  for (unsigned int i = 0; i < 32000; i++) 
  {
    float xt = 0;
    float yt = 0;
 
    int r = random(0, 100);
 
    if (r <= 1) 
    {
      xt = 0;
      yt = 0.16*y;
    } else if (r <= 8) 
    {
      xt = 0.20*x - 0.26*y;
      yt = 0.23*x + 0.22*y + 1.60;
    } else if (r <= 15) 
    {
      xt = -0.15*x + 0.28*y;
      yt =  0.26*x + 0.24*y + 0.44;
    } else 
    {
      xt =  0.85*x + 0.04*y;
      yt = -0.04*x + 0.85*y + 1.60;
    }
 
    x = xt;
    y = yt;
 
    int m = round(myTFT.width()/2 + 20*x);
    int n = myTFT.height()-round(12*y);
 
    myTFT.drawPixel(m, n, TFT_GREEN);
  }
  myTFT.drawRect(0, 0, myTFT.width(), myTFT.height(), TFT_GREEN);
}

// Zufallswanderung ausgehend von der Display-Mitte in eines
// der 8 benachbarten Felder oder ruhen an Ort.
void testZufallswanderung()
{
  int x = myTFT.width()/2;
  int y = myTFT.height()/2;

  myTFT.fillScreen(TFT_BLACK);
  
  for(unsigned int i = 0; i < 32000; i++)
  {
    x += random(0, 3) - 1;  // 0, 1, 2 ==> -1, 0, 1
    y += random(0, 3) - 1;
    if (x >= 0 && x < myTFT.width() && y >= 0 && y < myTFT.height())
      myTFT.drawPixel(x, y, Color[random(1,8)]);
  }
  myTFT.drawRect(0, 0, myTFT.width(), myTFT.height(), TFT_GREEN);
}

// HSV-Farbkreis als Vieleck mit 120 Seiten darstellen
// Der Farbwert (H = Hue) ändert von 0 .. 360° in Schritten von 3°.
// Sättigung (S = Saturation) und Helligkeit (V = Value) sind auf 1.0, 
// das Maximum gesetzt
void testFarbVieleck()
{
  float DEGTORAD = PI/180;
  int xm = myTFT.width() / 2;
  int ym = myTFT.height() /2;
  int xA, yA, xB, yB;
  int alpha = 3;
  int radius = 60;
  float r, g, b;
  unsigned int R, G, B, farbe;
  
  myTFT.fillScreen(TFT_BLACK);
  for( int phi = 0; phi < 360; phi += alpha)
  {
    xA = xm + radius * sin(DEGTORAD * phi);
    yA = ym + radius * cos(DEGTORAD * phi);
    xB = xm + radius * sin(DEGTORAD * (phi+alpha));
    yB = ym + radius * cos(DEGTORAD * (phi+alpha)); 

    HSVtoRGB(&r, &g, &b, phi, 1.0, 0.99);
    R = r * 32; R = R << 11;
    G = g * 64; G = G << 5;
    B = b * 32;
    farbe = R | G | B;

    myTFT.fillTriangle(xm, ym, xA, yA, xB, yB, farbe); 
  }
  myTFT.drawRect(0, 0, myTFT.width(), myTFT.height(), TFT_BLUE);
}

// Das Display mit (fast) allen farben des RGB-Farbraums füllen
void testRGBColorSpace()
{
  int w = myTFT.width();
  int h = myTFT.height();
  unsigned int farbe = 0;
  myTFT.fillScreen(TFT_BLACK);
  
  for(int zeile = 0; zeile < h; zeile++)
  {
    for(int spalte = 0; spalte < w; spalte++)
    {
      myTFT.drawPixel(spalte, zeile, farbe);
      farbe += 4;
    }
  }
}

// Das Display mit allen Farben des Farbkreises füllen
void testHSVColorSpace()
{
  float r, g, b;
  unsigned int R, G, B, farbe;

  myTFT.fillScreen(TFT_BLACK);
  for(int hue = 0; hue < 360; hue++)
  {
    HSVtoRGB(&r, &g, &b, hue, 0.9, 0.9);
    R = r * 32; R = R << 11;
    G = g * 64; G = G << 5;
    B = b * 32;
    farbe = R | G | B;
    //sprintf(s, "%3u: %05u %05u %05u %05u", hue,R,G,B,farbe);
    //Serial.println(s);
    myTFT.fillScreen(farbe);
  }
}

// Zeigt die 4 möglichen Textrotationen 0..3
void testRotateText()
{
  for (int i = 0; i < 6; i++)
  {
    myTFT.fillScreen(TFT_BLACK);
    myTFT.setRotation(i % 4);  // 0, 1, 2, 3, 0, 1
    myTFT.setTextColor(TFT_GREEN, TFT_BLACK);
    myTFT.setTextSize(1);
    int pos_x = (myTFT.width() - myTFT.textWidth("Good By! Good By!")) / 2;  // Den ersten Text zentrieren
    myTFT.setCursor(pos_x,0);
    myTFT.println("Good By! Good By!");   // println() setzt den Curser auf 
                                          // den Anfang der nächsten Zeile
    
    myTFT.setTextColor(TFT_RED, TFT_BLACK);
    myTFT.setTextSize(2);
    myTFT.println("Good By!");
  
    myTFT.setTextColor(TFT_YELLOW, TFT_BLACK);
    myTFT.setTextSize(3);
    myTFT.println("Good By");
    delay(2000); 
  }
}

// Zeigt Text in den Schriftgrössen 1..5
void testTextSizes()
{
  myTFT.setRotation(1);
  myTFT.fillScreen(TFT_BLACK);
  myTFT.setTextColor(TFT_GREEN, TFT_BLACK);
  myTFT.setCursor(0,0);

  myTFT.setTextSize(1);
  myTFT.println("Size 1");

  myTFT.setTextSize(2);
  myTFT.println("Size 2");

  myTFT.setTextSize(3);
  myTFT.println("Size 3");
  
  myTFT.setTextSize(4);
  myTFT.println("Size 4");
    
  myTFT.setTextSize(5);
  myTFT.println("Size5");    
}

// Zeigt einige Fonts an. Erlaubt sind die Fontnummern 1,2,4,6,7,8
void testFonts()
{
  myTFT.setRotation(1);
  myTFT.fillScreen(TFT_BLACK);
  myTFT.setTextColor(TFT_GREEN, TFT_BLACK);
  myTFT.setTextFont(1);
  myTFT.drawString("MWIJLOYgmwijloyg", 2, 0);
  myTFT.setTextFont(2);
  myTFT.drawString("MWIJLOYgmwijloyg", 2, 12);
  myTFT.setTextFont(4);
  myTFT.drawString("IJLYgmwijloy", 2, 32);
  myTFT.setTextFont(7);
  myTFT.drawString("1234", 2, 64);
  myTFT.setTextFont(1);
}

// Zeigt die Zeit digital an
void testDigitalUhr()
{
  myDigitalClock.setup();
  while (myDigitalClock.isRunning())
  {
    myDigitalClock.loop();
    myControlButton.loop();
  }
}

// Zeigt die Zeit analog an
void testAnalogUhr()
{
  myAnalogClock.setup();
  while (myAnalogClock.isRunning())
  {
    myAnalogClock.loop();
    myControlButton.loop();
  }
}
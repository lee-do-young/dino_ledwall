
/**************************************************************************/
/*!
    Description
 */
/**************************************************************************/

#include <Adafruit_NeoPixel.h>
#include <stdio.h>
#include <stdlib.h>

class Dino_LedWall {
    int p = 6;
    int h = 48;     //Num pixels in height
    int w = 27;     //Num pixels in width
    
    int fontSize = 1;
    
    
public:
    
    Adafruit_NeoPixel pixels;
    uint32_t color;     //color to draw
    
    
    Dino_LedWall(int pin);

    Dino_LedWall(int pin, int width, int height);
    
    void background(int r, int g, int b);
    
    void clear();
    
    bool canShow();
    
    void setColor(int r, int g, int b);
    
    void setOrientation();
    
    // draw dot at (x,y) {left upper point start from (0,0) } with color c -> it should be form of { pixels.Color(0,0,0) }
    void drawDot(int x, int y);
    
    //draw rectangle, (x1,y1) and (x2,y2) become upper left and lower right corners.
    void drawRect(int x1, int y1, int x2, int y2);
    
    //draw circle at (x1,y1) with r as radius
    void drawEllipse(int x, int y, int r);
    
    //draw a line connecting both lines
    void drawLine(int x0, int y0, int x1, int y1);
    
    //1 is default; (8by8 pixels)
    //n is 8*n by 8*n pixels ...
    void setFontSize(int size);
    
    void drawText(String text, int x, int y);
    
    void show();
    
    int getWidth();
    
    int getHeight();
    
private:
    
    
};



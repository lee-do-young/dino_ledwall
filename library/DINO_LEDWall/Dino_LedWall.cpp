// Dino Led Wall Example
// Description
// Author: Lee, DoYoung ( http://leedoyoung.com )
// License: MIT License ( https://opensource.org/licenses/MIT )



#include <Dino_LedWall.h>
#include <font.c>

/**************************************************************************/
/*!
    Description
*/
/**************************************************************************/

Dino_LedWall::Dino_LedWall(int pin) {
    pixels = Adafruit_NeoPixel(w*h, p, NEO_GRB + NEO_KHZ800);
    pixels.begin();
    pixels.clear();
    p = pin;

}


Dino_LedWall::Dino_LedWall(int pin, int width, int height) {
    w = width;
    h = height;
    p = pin;
    pixels = Adafruit_NeoPixel(w*h, p, NEO_GRB + NEO_KHZ800);
    pixels.begin();
    pixels.clear();
}

void Dino_LedWall::background(int r, int g, int b) {
    for (int i = 0; i < w*h; i++) {
        pixels.setPixelColor(i, pixels.Color(r,g,b));
    }
}

void Dino_LedWall::clear(){
    pixels.clear();
}

bool Dino_LedWall::canShow(){
    return pixels.canShow();
}

void Dino_LedWall::setColor(int r, int g, int b){
    color = pixels.Color(r, g, b);
}


// draw dot at (x,y) {left upper point start from (0,0) } with color c -> it should be form of { pixels.Color(0,0,0) }
void Dino_LedWall::drawDot(int x, int y) {
    if( !(x<w && y<h && x>=0 && y>=0)){
        return;
    }
    if ( (x + w * y) % (2 * w) < w )
        pixels.setPixelColor(w * y + (w-1) - x, color);
    else
        pixels.setPixelColor(x + w * y, color);
}

//draw rectangle, (x1,y1) and (x2,y2) become upper left and lower right corners.
void Dino_LedWall::drawRect(int x1, int y1, int x2, int y2) {
    int sx = 0; //small x
    int lx = 0; //large x
    
    int sy = 0;
    int ly = 0;
    
    sx = min(x1,x2);
    sy = min(y1,y2);
    
    lx = max(x1,x2);
    ly = max(y1,y2);
    
    sx = sx<0?0:(sx>w?w:sx);
    sy = sy<0?0:(sy>h?h:sy);
    
    lx = lx>w?w:(lx<0?0:lx);
    ly = ly>h?h:(ly<0?0:ly);
    
    for (int x = sx; x <= lx; x++) {
        for (int y = sy; y <= ly; y++) {
            drawDot(x, y);
        }
    }
}

//draw circle at (x1,y1) with r as radius
void Dino_LedWall::drawEllipse(int x, int y, int r) {
    int sx = x-r; //small x
    int lx = x+r; //large x
    
    int sy = y-r;
    int ly = y+r;

    sx = sx<0?0:(sx>w?w:sx);
    sy = sy<0?0:(sy>h?h:sy);
    
    lx = lx>w?w:(lx<0?0:lx);
    ly = ly>h?h:(ly<0?0:ly);
      
    for (int i = sx; i <= lx; i++) {
        for (int j = sy; j <= ly; j++) {
            if ( pow(i - x, 2) + pow(j - y, 2) <= pow(r, 2) ) {
                drawDot(i, j);
            }
        }
    }
}

void Dino_LedWall::drawLine(int x0, int y0, int x1, int y1) {
    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;
    
    for(;;){
        drawDot(x0,y0);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

void Dino_LedWall::setFontSize(int size){
    if(size>0 && size<7){
        fontSize = size;
    }
}

void Dino_LedWall::drawText(String text, int x, int y){
    int posX = x;
    
    for(int i=0; i<text.length(); i++){
        int asciiIdx = text.charAt(i);
        uint64_t ch = font[asciiIdx];
        
        for(int j=0; j<8*8; j++){
            if(((ch>>j) & 1) != 0){
                drawDot((posX+(j%8)), (0+floor(8-j/8))+y);
            }
        }
        posX -= fontSize*8;
    }
}

void Dino_LedWall::show(){
    pixels.show();
}

int Dino_LedWall::getWidth(){
    return w;
}

int Dino_LedWall::getHeight(){
    return h;
}





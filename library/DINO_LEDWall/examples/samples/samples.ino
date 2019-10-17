// Dino Led Wall Example
// Description
// Author: Lee, DoYoung (leedoyoung.com)
// License: MIT License (https://opensource.org/licenses/MIT)


#include <Dino_LedWall.h>

Dino_LedWall wall = Dino_LedWall(6);


void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

}


void loop() {
  //draw dots
  wall.setColor(10, 0, 0);
  wall.drawDot(13, 3);
  wall.drawDot(13, 4);
  wall.drawDot(14, 3);
  wall.show();
  delay(1500);
  wall.clear();

  //draw rectangle
  wall.setColor(0, 10, 0);
  wall.drawRect(10, 0, 14, 4);
  wall.show();
  delay(1500);
  wall.clear();

  //draw ellipses
  wall.setColor(0, 0, 10);
  wall.drawEllipse(16, 16, 9);
  wall.show();
  delay(1500);
  wall.clear();
  
  //draw lines
  wall.setColor(10, 10, 0);
  wall.drawLine(10, 0, 14, 8);
  wall.drawLine(2, 7, 6, 3);
  wall.show();
  delay(1500);
  wall.clear();

}

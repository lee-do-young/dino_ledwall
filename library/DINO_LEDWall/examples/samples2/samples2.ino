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
  bombing();

  moveRect(wall.getWidth() / 2 , wall.getHeight() / 5, 5);

  ellipseSizeChange(10, 10);

  rotateLines(10, 10, 5);
}

void bombing() {
  wall.setColor(10, 0, 0);
  for (int i = 0; i < 10; i++) {
    bomb(floor(getRandom(wall.getWidth())), floor(getRandom(wall.getHeight())));
  }
}

void bomb(int x, int y) {
  for (int i = 0; i < 2; i++) {
    wall.drawDot(x + i, y + i);
    wall.drawDot(x + i, y - i);
    wall.drawDot(x - i, y + i);
    wall.drawDot(x - i, y - i);
    wall.show();
    delay(30);
    wall.clear();
  }
}

void moveRect(int x, int y, int r) {
  int rectX = x;
  int rectY = y;
  int rectR = r;

  for (int i = 0; i < 10; i++) {
    rectX += getRandom(3)-1; //floor(random(-1, 2));
    rectY += getRandom(3)-1; //floor(random(-1, 2));
    rectR += getRandom(3)-1; //floor(random(-1, 2));

    rectR = constrain(rectR, 1, 10);
    rectX = constrain(rectX, 0, wall.getWidth() - rectR);
    rectY = constrain(rectY, 0, wall.getHeight() - rectR);

    wall.setColor(i, 10 - i, 0);
    wall.drawRect(rectX, rectY, 14, 4);
    wall.show();
    delay(30);
    wall.clear();
  }
}

void ellipseSizeChange(int x, int y) {
  wall.setColor(10, 10, 0);
  for (int i = 0; i < 10; i++) {
    wall.drawEllipse(x, y, i);
    wall.show();
    delay(30);
    wall.clear();
  }
}

void rotateLines(int x, int y, int r) {
  wall.setColor(0, 10, 10);

  for (int i = 0; i < 30; i++) {
    wall.drawLine(x + r * cos((2 * PI / 30)*i), y + r * sin((2 * PI / 30)*i), x + r * cos((2 * PI / 30)*i + PI), y + r * sin((2 * PI / 30)*i + PI) );
    wall.show();
    delay(30);
    wall.clear();
  }

}

//Temporary implementation of ramdom function...
//Recommended endVal is less than 100?
int getRandom(int endVal) {
  if (endVal <= 0) {
    return 0;
  }
  if (endVal > 100) {
    return analogRead(A0) % 100;
  }
  return analogRead(A0) % endVal;
}

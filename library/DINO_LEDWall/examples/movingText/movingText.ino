// Dino Led Wall Example
// Description
// Author: Lee, DoYoung (leedoyoung.com)
// License: MIT License (https://opensource.org/licenses/MIT)


#include <Dino_LedWall.h>

Dino_LedWall wall = Dino_LedWall(6);

int i = 0;
int idxMax = 0;
String txt = "hello world!";

void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  idxMax = txt.length() * 8;

}


void loop() {
  wall.setColor(10, 0, 10);
  wall.drawText("hello", idxMax - i, 8);
  wall.show();
  delay(500);
  wall.clear();

  if (i > idxMax) {
    i %= idxMax;
  }
}

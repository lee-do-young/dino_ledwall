#include "udp.h"
#include <Dino_LedWall.h>

Dino_LedWall wall(6);

int encoder0Cnt = 0;
int encoder1Cnt = 0;
//
boolean encoder0Clicked = false;
boolean encoder1Clicked = false;

int r, g, b;

int i = 0;
int lastMili = 0;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  //  while (!Serial) {
  //    ; // wait for serial port to connect. Needed for native USB port only
  //  }

  udpInit();

  wall.clear();
  wall.setColor(50, 0, 0);

  int packetSize = Udp.parsePacket();
  while (packetSize != 0) {
    ;
  }
}

void loop() {
  wall.clear();

  encoder0Clicked = false;
  encoder1Clicked = false;


  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int len = Udp.read(packetBuffer, 4);
    Serial.print(len);
    Serial.print(" ");
    //encoders
    if (len == 2) {
      if (byte(packetBuffer[0]) == 2)
        encoder0Cnt++;
      else if (byte(packetBuffer[0]) == 3)
        encoder0Cnt--;
      else if (byte(packetBuffer[0]) == 4)
        encoder0Clicked = true;

      if (byte(packetBuffer[1]) == 2)
        encoder1Cnt++;
      else if (byte(packetBuffer[1]) == 3)
        encoder1Cnt--;
      else if (byte(packetBuffer[1]) == 4)
        encoder1Clicked = true;
    }
    //rgbs
    else if (len == 3 || len == 4) {
      r = byte( (packetBuffer[0] - 1) );
      g = byte( (packetBuffer[1] - 1) );
      b = byte( (packetBuffer[2] - 1) );
      wall.setColor(r, g, b);
    }

    Serial.print("getVal ");

    for (int i = 0; i < len; i++) {
      Serial.print(byte(packetBuffer[i]));
      Serial.print(" ");
    }
    Serial.print("  cntVal ");
    Serial.println(encoder0Cnt);
  }

  wall.drawDot(10 + encoder0Cnt, 5 + encoder1Cnt);
  wall.show();

  //  if(lastMili + 100 < millis()){
  //    i++;
  //    i = i%(27*48);
  //    wall.pixels.setPixelColor(i,wall.color);
  //    wall.show();
  //    lastMili = millis();
  //  }


}

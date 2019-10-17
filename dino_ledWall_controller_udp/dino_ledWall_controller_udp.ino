#include "udp.h"
#include "encoders.h"

String str = "";

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  //  while (!Serial) {
  //    ; // wait for serial port to connect. Needed for native USB port only
  //  }

  udpInit();
}

void loop() {
  //  int i = rotary0.rotate();
  //  int j = rotary1.rotate();
  int r0rot = rotary0.rotate();
  int r1rot = rotary1.rotate();
  //
  int r0push = rotary0.push();
  int r1push = rotary1.push();

  int i=r0push==0?r0rot:3;
  int j=r1push==0?r1rot:3;
  
  if ( !(i == 0 && j == 0) ) {
    char  ReplyBuffer[2];
    ReplyBuffer[0] = byte(1 + i);
    ReplyBuffer[1] = byte(1 + j);

    Udp.beginPacket(remoteIP, remotePort);
    Udp.write(ReplyBuffer);
    Udp.endPacket();

    Serial.print(byte(ReplyBuffer[0]));
    Serial.print(byte(ReplyBuffer[1]));
    Serial.print("  |  ");
    Serial.print(ReplyBuffer);
    Serial.println();
  }
}

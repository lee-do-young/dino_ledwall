#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
#include <cmath>

#include <WiFiNINA.h>
#include <WiFiUdp.h>

#include "wifi_secret.h"
#include "udp.h"

#include "imu.h"

String str = "";


int R;
int G;
int B;

int preR;
int preG;
int preB;

int RArr[] = {0, 0, 0, 0, 0};
int GArr[] = {0, 0, 0, 0, 0};
int BArr[] = {0, 0, 0, 0, 0};

int ptr = 0;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  //  while (!Serial) {
  //    ; // wait for serial port to connect. Needed for native USB port only
  //  }

  udpInit();
  imuInit();
}

void loop() {
  //  imuUpdate();

  if ( imu.accelAvailable() )  {
    //    delay(10);
    imu.readAccel();

    HSV_To_RGB();
    
    R /= 8;
    G /= 8;
    B /= 8;

    
    R = constrain(R, 1, 32);
    G = constrain(G, 1, 32);
    B = constrain(B, 1, 32);

    RArr[ptr] = R;
    GArr[ptr] = G;
    BArr[ptr] = B;

    ptr++;
    ptr = ptr % 5;

    R = 0; G = 0; B = 0;
    for (int i = 0; i < 5; i++) {
      R += RArr[i];
      G += GArr[i];
      B += BArr[i];
    }
    
    R = R / 5;
    G = G / 5;
    B = B / 5;

    if ( !(preR == R && preG == G && preB == B)) {
      char  ReplyBuffer[4];
      ReplyBuffer[0] = byte(R);
      ReplyBuffer[1] = byte(G);
      ReplyBuffer[2] = byte(B);
      ReplyBuffer[3] = 0;

      Udp.beginPacket(remoteIP, remotePort);
      Udp.write(ReplyBuffer);
      Udp.endPacket();

      Serial.print(byte(ReplyBuffer[0]));
      Serial.print(", ");
      Serial.print(byte(ReplyBuffer[1]));
      Serial.print(", ");
      Serial.print(byte(ReplyBuffer[2]));

      Serial.println();
      preR = R;
      preG = G;
      preB = B;
    }
  }

}



void HSV_To_RGB()
{
  double s = 1.0;
  double f, q, p, t;
  int i;
  angle =  atan2(imu.calcAccel(imu.ax), imu.calcAccel(imu.ay));
  angle = (angle * 180.0) / PI + 180;
  // Serial.print("angle: ");
  //  Serial.println(angle);
  double h = angle;
  double v = imu.calcAccel(imu.az);
  v = (v + 1.0) / 2.0;
  //  Serial.print("v: ");
  //  Serial.println(v);
  if (h == 360)
    h = 0.0;
  h /= 60.0;
  i = (int)h;
  f = h - i;
  p = v * (1.0 - s);
  q = v * (1.0 - (s * f));
  t = v * (1.0 - (s * (1.0 - f)));
  double r , g , b ;
  switch (i) {
    case 0:
      r = v;
      g = t;
      b = p;
      break;
    case 1:
      r = q;
      g = v;
      b = p;
      break;
    case 2:
      r = p;
      g = v;
      b = t;
      break;
    case 3:
      r = p;
      g = q;
      b = v;
      break;
    case 4:
      r = t;
      g = p;
      b = v;
      break;
    case 5:
      r = v;
      g = p;
      b = q;
      break;
  }


  R = int(r * 255);
  G = int(g * 255);
  B = int(b * 255);

  if (v > 0.85) {
    R += (255 - R) * (0.2 + v - 1.0) * 5;
    G += (255 - G) * (0.2 + v - 1.0) * 5;
    B += (255 - B) * (0.2 + v - 1.0) * 5;
  }

  R = constrain(R, 0, 255);
  G = constrain(G, 0, 255);
  B = constrain(B, 0, 255);
  // delay(100);
  //Serial.print(h);
  // Serial.print(", ");
  // Serial.print(s);
  //Serial.print(", ");
  // Serial.println(v);
  //  Serial.print("RGB : ");
  //  Serial.print(R);
  //  Serial.print(", ");
  //  Serial.print(G);
  //  Serial.print(", ");
  //  Serial.println(B);
  //delay(500);
}

#include <SimpleRotary.h>

SimpleRotary rotary0(2, 3, 0); //rotary0(1, 2, 0); 
SimpleRotary rotary1(4, 5, 1); //rotary1(4, 5, 3);

int encoder0Cnt = 0;
int encoder1Cnt = 0;

int encoder0CntLast = 0;
int encoder1CntLast = 0;

boolean encoderChanged = false;

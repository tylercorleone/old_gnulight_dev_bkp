# 1 "/tmp/tmpzjEHDw"
#include <Arduino.h>
# 1 "/home/paolo/Documents/arduino/gnulight/src/gnulight.ino"
#include "Gnulight.h"

Gnulight* pGnulight;
void setup();
void loop();
void setUnusedPinStatus(int mode, int level);
#line 5 "/home/paolo/Documents/arduino/gnulight/src/gnulight.ino"
void setup() {
#ifdef INFO
 Serial.begin(9600);
#endif
 debug("setup()");


 pGnulight = new Gnulight;
 pGnulight->Setup();
}

void loop() {
 pGnulight->Loop(WDTO_X);
}

void setUnusedPinStatus(int mode, int level) {







 pinMode(0, mode);
 pinMode(3, mode);
 pinMode(4, mode);
 pinMode(6, mode);
 pinMode(7, mode);
 pinMode(8, mode);
 pinMode(12, mode);

 digitalWrite(0, level);
 digitalWrite(3, level);
 digitalWrite(4, level);
 digitalWrite(6, level);
 digitalWrite(7, level);
 digitalWrite(8, level);
 digitalWrite(12, level);

 pinMode(A0, mode);
 pinMode(A1, mode);
 pinMode(A5, mode);
 pinMode(A6, mode);
 pinMode(A7, mode);

 digitalWrite(A0, level);
 digitalWrite(A1, level);
 digitalWrite(A5, level);
 digitalWrite(A6, level);
 digitalWrite(A7, level);
}
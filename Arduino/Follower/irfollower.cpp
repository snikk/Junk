#include "irfollower.h"
#include <Arduino.h>

const int irfollower::cornerWeight = 90;
const int irfollower::innerWeight = 50;
const int irfollower::forwardWeight = 10;

irfollower::irfollower(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6) : 
    d1_(d1), d2_(d2), d3_(d3), d4_(d4), d5_(d5), d6_(d6)
{
  pinMode(d1_, INPUT);
  pinMode(d2_, INPUT);
  pinMode(d3_, INPUT);
  pinMode(d4_, INPUT);
  pinMode(d5_, INPUT);
  pinMode(d6_, INPUT);
}

double irfollower::readDegrees() {
  bool f1, f2, f3, f4, f5, f6;

  f1 = !digitalRead(d1_);
  f2 = !digitalRead(d2_);
  f3 = !digitalRead(d3_);
  f4 = !digitalRead(d4_);
  f5 = !digitalRead(d5_);
  f6 = !digitalRead(d6_);

  double sum = 0.0;
  int divisor = 0;

  if (f1) {
    sum += cornerWeight;
    divisor++;
  }
  if (f2) {
    sum += innerWeight;
    divisor++;
  }
  if (f3) {
    sum += forwardWeight;
    divisor++;
  }

  if (f4) {
    sum -= forwardWeight;
    divisor++;
  }
  if (f5) {
    sum -= innerWeight;
    divisor++;
  }
  if (f6) {
    sum -= cornerWeight;
    divisor++;
  }

  if (!f1 && !f2 && !f3 && !f4 && !f5 && !f6) {
    return INTEGER_MIN;
  }

  return sum / divisor;
}


#ifndef __IRFOLLOWER_H__
#define __IRFOLLOEWR_H__

#include <stdint.h>

#define INTEGER_MIN -32768

class irfollower {
public:
  irfollower(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6);

  double readDegrees();

private:
  uint8_t d1_;
  uint8_t d2_;
  uint8_t d3_;
  uint8_t d4_;
  uint8_t d5_;
  uint8_t d6_;

  static const int cornerWeight;
  static const int innerWeight;
  static const int forwardWeight;
};

#endif

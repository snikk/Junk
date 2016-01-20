#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <stdint.h>

class Motor {
public:
  Motor(uint8_t pinIN1, uint8_t pinIN2, uint8_t pinEN);

  void forward(uint8_t speed);
  void backward(uint8_t speed);
  void brake();
  void freeRun();

private:
  uint8_t pinIN1_;
  uint8_t pinIN2_;
  uint8_t pinEN_;
};

#endif

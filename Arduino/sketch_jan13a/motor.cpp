#include "motor.h"
#include <Arduino.h>

Motor::Motor(uint8_t pinIN1, uint8_t pinIN2, uint8_t pinEN)
    : pinIN1_(pinIN1), pinIN2_(pinIN2), pinEN_(pinEN)
{
  pinMode(pinIN1_, OUTPUT);
  pinMode(pinIN2_, OUTPUT);
  pinMode(pinEN_, OUTPUT);

  digitalWrite(pinEN_, LOW);
}

void Motor::forward(uint8_t speed) {
  digitalWrite(pinIN1_, HIGH);
  digitalWrite(pinIN2_, LOW);

  analogWrite(pinEN_, speed);
}

void Motor::backward(uint8_t speed) {
  digitalWrite(pinIN1_, LOW);
  digitalWrite(pinIN2_, HIGH);

  analogWrite(pinEN_, speed);
}

void Motor::brake() {
  digitalWrite(pinIN1_, LOW);
  digitalWrite(pinIN2_, LOW);

  analogWrite(pinEN_, HIGH);
}

void Motor::freeRun() {
  digitalWrite(pinEN_, LOW);
}


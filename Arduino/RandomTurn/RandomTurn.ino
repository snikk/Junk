#include "motor.h"

const int motorRENPin = 10;
const int motorRIN1Pin = 8;
const int motorRIN2Pin = 9;

const int motorLENPin = 5;
const int motorLIN1Pin = 6;
const int motorLIN2Pin = 7;

const int driveSpeed = 200;
const int turnSpeed = 200;

Motor rightMotor(motorRIN1Pin, motorRIN2Pin, motorRENPin);
Motor leftMotor(motorLIN1Pin, motorLIN2Pin, motorLENPin);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int randomDrive = random(200, 3000);
  int randomTurn = random(200, 3000);

  rightMotor.forward(driveSpeed);
  leftMotor.forward(driveSpeed);

  delay(randomDrive);
  
  if (random(2)) {
    Serial.println("Turn Right");
    rightMotor.backward(turnSpeed);
    leftMotor.forward(turnSpeed);
  } else {
    Serial.println("Turn Left");
    rightMotor.forward(turnSpeed);
    leftMotor.backward(turnSpeed);
  }
  

  delay(randomTurn);
}

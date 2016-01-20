#include "irfollower.h"
#include "motor.h"

enum State {
  WAITING, 
  CHASING, 
  AVOID, 
  AVOID_LEFT, 
  AVOID_RIGHT
};

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

const int followD1 = A5;
const int followD2 = A4;
const int followD3 = A3;
const int followD4 = A2;
const int followD5 = A1;
const int followD6 = A0;

irfollower follow(followD1, followD2, followD3, followD4, followD5, followD6);

const int collisionLeftPin = 2;
const int collisionRightPin = 3;

State state = WAITING;
bool collisionLeft = false;
bool collisionRight = false;

long missingDirection = 0;
double lastDirection;
const long waitDuration = 300;
long lastMillis = 0;

const int maxSpeed = 255;
const int steeringMax = 90;
const double steeringSlope = ((double) maxSpeed * -1) / steeringMax;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  long curr = millis();
  long duration = curr - lastMillis;
  lastMillis = curr;
  
  switch (state) {
    case WAITING: {
      double deg = follow.readDegrees();
      if (deg != INTEGER_MIN) {
        state = CHASING;
        lastDirection = deg;
        missingDirection = waitDuration;
      }
      break;
    }
    case CHASING: {
      double deg = follow.readDegrees();
      if (deg == INTEGER_MIN) {
        missingDirection -= duration;
        if (missingDirection <= 0) {
          state = WAITING;
          leftMotor.freeRun();
          rightMotor.freeRun();
        }
      } else {
        missingDirection = waitDuration;
        lastDirection = follow.readDegrees();
        steerDeg(lastDirection);
      }

      checkCollision();
      break;
    }
    case AVOID: {
      leftMotor.backward(200);
      rightMotor.forward(200);

      checkCollision();
      break;
    }
    case AVOID_LEFT: {
      leftMotor.freeRun();
      rightMotor.backward(200);

      checkCollision();
      break;
    }
    case AVOID_RIGHT: {
      leftMotor.backward(200);
      rightMotor.freeRun();

      checkCollision();
      break;
    }
  }
}

void steerDeg(double deg) {
  if (deg > -1 && deg < 1) {
    leftMotor.forward(maxSpeed);
    rightMotor.forward(maxSpeed);
    
    return;
  }

  double turnMotorSpeed = (steeringSlope * abs(deg)) + maxSpeed;

  if (deg < -1) {
    leftMotor.forward(turnMotorSpeed);
    rightMotor.forward(maxSpeed);
  } else if (deg > 1) {
    leftMotor.forward(maxSpeed);
    rightMotor.forward(turnMotorSpeed);
  }
}

void checkCollision() {
  collisionLeft = digitalRead(collisionLeftPin) == LOW;
  collisionRight = digitalRead(collisionRightPin) == LOW;

  if (collisionLeft && collisionRight) {
    state = AVOID;
  } else if (collisionLeft) {
    state = AVOID_LEFT;
  } else if (collisionRight) {
    state = AVOID_RIGHT;
  } else {
    state = CHASING;
  }
}


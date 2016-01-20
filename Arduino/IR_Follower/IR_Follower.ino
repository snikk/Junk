#include <Servo.h>

#include "irfollower.h"

const int followD1 = A5;
const int followD2 = A4;
const int followD3 = A3;
const int followD4 = A2;
const int followD5 = A1;
const int followD6 = A0;

irfollower follow(followD1, followD2, followD3, followD4, followD5, followD6);

Servo myservo;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  myservo.attach(11);
}

void loop() {
  // put your main code here, to run repeatedly:

  double deg = follow.readDegrees();

  if (deg == INTEGER_MIN) {
    Serial.println("No direction");
    myservo.write(90);
  } else {
    Serial.print("Deg: ");
    Serial.println(deg);
    myservo.write(map(deg * 10, -900, 900, 0, 180));
  }
  
  delay(300);
}

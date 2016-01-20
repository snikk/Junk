#include "prescalar.h"

const int pinDetector1a = 2;
const int pinDetector1b = 4;
const int feedback = 13;

long lastMicro = 0;
volatile long currentMicro = 0;
long trueMicros;
long oldMicros;
volatile long currentTimerTicks = 0;
volatile boolean checkSpeed = false;
volatile boolean first = false;
volatile long duration = 0;

long count = 0;
long start = 0;

void setup() {
  // put your setup code here, to run once:
  

  Serial.begin(9600);
  
  Serial.print("TCCR1A = ");
  Serial.print(TCCR1A);
  Serial.print(" | TCCR1B = ");
  Serial.print(TCCR1B);
  Serial.print(" | TCCR1C = ");
  Serial.println(TCCR1C);
  
  TCCR1A = 4;
  TCCR1B = 1;

  pinMode(pinDetector1a, INPUT);
  pinMode(pinDetector1b, INPUT);
  digitalWrite(pinDetector1a, HIGH);
  digitalWrite(pinDetector1b, HIGH);
  attachInterrupt(digitalPinToInterrupt(pinDetector1a), broken, CHANGE);

  pinMode(feedback, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(feedback, digitalRead(pinDetector1a));
  if (checkSpeed) {
    Serial.println("Checking speed");
    boolean second;
    boolean isSecondBroken = (PIND & (1 << pinDetector1b)) != 0;
    while (1) {
      second = (PIND & (1 << 4)) != 0;
//      bool first = (PIND & (1 << pinDetector1a)) != 0;
//      Serial.print(second);
//      Serial.print(" ");
//      Serial.print(isSecondBroken);
//      Serial.print(" ");
//      Serial.print(first);
//      Serial.print(" ");
//      Serial.println(PIND);
      if (!second && isSecondBroken) {
        duration = micros() - duration;
        break;
      }
      isSecondBroken = second;
//      delay(100);
    }
    checkSpeed = false;
    Serial.print("Detect speed! | dur = ");
    Serial.println(duration);
  }
  if (currentMicro != lastMicro) {
    
    long ticks = 0;
    boolean tripped = false;
    currentTimerTicks = 0;
    Serial.print("micros before = ");
    Serial.println(micros());
    long dur = micros();
    TCNT1 = 0;
    while (ticks < 1000000) {
        ticks++;
      if (!tripped && (PIND & (1 << 4))) {
        tripped = true;
      }
    }
    long num = TCNT1;
    dur = micros() - dur;
    Serial.print("micros after = ");
    Serial.println(micros());
    
    Serial.print("Hmmm = ");
    Serial.print(PIND);
    Serial.print(" | ahhhhh = ");
    Serial.print(currentMicro - lastMicro);
    Serial.print(" | ticks = ");
    Serial.print(ticks);
    Serial.print(" | currentTimerTicks = ");
    Serial.print(num);
    Serial.print(" | dur= ");
    Serial.println(dur);
    lastMicro = currentMicro;
  }
//  Serial.print("Prescalar = ");
//  Serial.print(getClockPrescaler());
//  Serial.print(" | Division factor = ");
//  Serial.println(getClockDivisionFactor());
//  
//  delay(1000);
}

void broken() {
  boolean isBroken = (PIND & (1 << pinDetector1a)) != 0;
  if (!isBroken && first) {
    checkSpeed = true;
    duration = micros();
  }
  first = isBroken;
}


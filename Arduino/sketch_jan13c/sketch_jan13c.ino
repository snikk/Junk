#include <IRremote.h>
#include <IRremoteInt.h>

const int rec = 0;
bool broke = false;
long start;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  long mic = micros();
  bool didBreak = analogRead(rec) > 1000;
  mic = micros() - mic;

  if (broke != didBreak) {
    broke = didBreak;
    if (broke) {
      start = micros();
    } else {
      Serial.print("Time = ");
      Serial.print(micros() - start);
      Serial.print(" | read time = ");
      Serial.println(mic);
      
    }
  }
}

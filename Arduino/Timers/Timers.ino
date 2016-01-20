// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int input = 2;
const int timers = 5;
long timer[timers];

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);

  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  pinMode(4, INPUT);
  digitalWrite(4, HIGH);
  
  Serial.print("TCCR1A = ");
  Serial.print(TCCR2A);
  Serial.print(" | TCCR1B = ");
  Serial.println(TCCR2B);
  // initialize the digital pin as an output.
  pinMode(input, INPUT);
  TCCR2A = 0;
  TCCR2B &= ~((1 << 3) - 1);
  TCCR2B |= 1;
  Serial.print("TCCR1A = ");
  Serial.print(TCCR2A);
  Serial.print(" | TCCR1B = ");
  Serial.println(TCCR2B);
  // initialize the digital pin as an output.
  pinMode(input, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  long ticks = 0;
  long val = 0;
  boolean tripped = false;
  long dur = micros();
  TCNT2 = 0;
  while (ticks < 1000000) {
    ticks++;
    if (!tripped && (PIND & (1 << 4))) {
      tripped = true;
    }
  }
  val = TCNT2;
  dur = micros() - dur;
  
  if (digitalRead(input)) {
    Serial.print("Pushed ");
    Serial.println(millis());
  }
  Serial.print("TCNT1 = ");
  Serial.print(val);
  Serial.print(" | tripped = ");
  Serial.print(tripped);
  Serial.print(" | micros = ");
  Serial.println(dur);
  timer[0] = TCNT2;
  timer[1] = TCNT2;
  timer[2] = TCNT2;
  timer[3] = TCNT2;
  timer[4] = TCNT2;
  Serial.print("Internal timers = ");
  for (int i = 0; i < timers; i++) {
    Serial.print(timer[i]);
    Serial.print(", ");
  }
  Serial.println();
  Serial.print("diffs = ");
  for (int i = 1; i < timers; i++) {
    Serial.print(timer[i] - timer[i - 1]);
    Serial.print(", ");
  }
  Serial.println();
  timer[0] = micros();
  timer[1] = micros();
  timer[2] = micros();
  timer[3] = micros();
  timer[4] = micros();
  Serial.print("micros() timers = ");
  for (int i = 0; i < timers; i++) {
    Serial.print(timer[i]);
    Serial.print(", ");
  }
  Serial.println();
  Serial.print("diffs = ");
  for (int i = 1; i < timers; i++) {
    Serial.print(timer[i] - timer[i - 1]);
    Serial.print(", ");
  }
  Serial.println();
  delay(100);               // wait for a second
}

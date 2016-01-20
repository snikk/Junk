enum State {
  WAITING, 
  RUNNING
};

int numSensors = 3;
//int tempIndicators[] = {2};
int tempIndicators[] = {2, 3, 4};
//int tempSensors[] = {0};
int tempSensors[] = {0, 1, 2};
int onButton = 5;
int outputPin = 6;
int targetTemp = 500;

boolean pressed = false;
State state = WAITING;
boolean atTemp[] = {false, false, false};

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  for (int i = 0; i < numSensors; i++) {
    pinMode(tempIndicators[i], OUTPUT);
  }
  pinMode(outputPin, OUTPUT);
  pinMode(onButton, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  boolean isPressed = digitalRead(onButton);
  boolean anyTemp = false;
  boolean allTemp = true;
  
  for (int i = 0; i < numSensors; i++) {
    atTemp[i] = analogRead(tempSensors[i]) < targetTemp;
  digitalWrite(tempIndicators[i], atTemp[i]);
    anyTemp |= !atTemp[i];
    allTemp &= atTemp[i];
  }
  
  if (pressed != isPressed) {
    pressed = isPressed;
    if (pressed && anyTemp) {
      state = RUNNING;
      digitalWrite(outputPin, HIGH);
    }
  }
  
  if (state == RUNNING && allTemp) {
    state = WAITING;
    digitalWrite(outputPin, LOW);
  }
  
  delay(100);
}

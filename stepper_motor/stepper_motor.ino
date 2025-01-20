#include <Stepper.h>
int stepsPerRevolution = 2048;
int motSpeed = 10;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
int buttonPin = 2;
int dt = 500;
int currentButtonState = 1;
int previousButtonState = 1;
int stepsPerLoop=10;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myStepper.setSpeed(motSpeed);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  myStepper.step(stepsPerLoop);
  currentButtonState = digitalRead(buttonPin);
  Serial.println(currentButtonState);
  if (currentButtonState == 1 && previousButtonState == 0) {
    stepsPerLoop *= -1;
  }
  previousButtonState = currentButtonState;
    Serial.println(currentButtonState);

}

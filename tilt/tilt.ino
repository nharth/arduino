int tiltPin = 2;
int tiltVal;
int greenPin = 9;
int redPin = 8;
int dt = 500;
void setup() {
  // put your setup code here, to run once:
  pinMode(tiltPin, INPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  digitalWrite(tiltPin, HIGH);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  tiltVal = digitalRead(tiltPin);
  Serial.println(tiltVal);
  if (tiltVal == 0) {
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, LOW);
  } else {
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);
  }
  delay(dt);
}

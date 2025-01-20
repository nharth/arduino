int lightPin = A3;
int lightVal;
int greenPin = 8;
int redPin = 9;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(lightVal, INPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  lightVal = analogRead(lightPin);
  Serial.println(lightVal);
  if (lightVal >= 200) {
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, LOW);
  } else {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }

}

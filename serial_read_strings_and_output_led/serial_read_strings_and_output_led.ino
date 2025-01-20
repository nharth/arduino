
int photoPin = A3;
int greenPin = 8;
int redPin = 9;
int photoVal;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(photoPin, INPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  photoVal = analogRead(photoPin);
  if (photoVal <= 200) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  } else {
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, LOW);
  }
  Serial.println(photoVal);

}

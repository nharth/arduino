int speedPin = 5;
int dir1 = 4;
int dir2 = 3;
int mSpeed = 0;
int forwardPin = 8;
int forwardState;
int reversePin = 9;
int reverseState;
void setup() {
  // put your setup code here, to run once:
  pinMode(speedPin, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(forwardPin, INPUT);
  digitalWrite(forwardPin, HIGH);
  pinMode(reversePin, INPUT);
  digitalWrite(reversePin, HIGH);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  forwardState = digitalRead(forwardPin);
  Serial.print("Forward: ");
  Serial.println(forwardState);

  reverseState = digitalRead(reversePin);
  Serial.print("Reverse: ");
  Serial.println(reverseState);
  if (forwardState == 0 && mSpeed < 255) {
    if (mSpeed < 0 && mSpeed > -150) {
      mSpeed = 0;
      delay(200);
    } else if (mSpeed > 0 && mSpeed < 150) {
      mSpeed = 150;
      delay(100);

    } else {
       mSpeed+=5;
    }
  }
  if (reverseState == 0 && mSpeed > -255) {
    if (mSpeed > 0 && mSpeed < 150) {
      mSpeed = 0;
      delay(200);

    } else if (mSpeed < 0 && mSpeed > -150) {
      mSpeed = -150;
      delay(100);

    } else {
      mSpeed-=5;
    }
  }
  if (mSpeed < 0) {
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, HIGH);
    analogWrite(speedPin, -mSpeed);

  } else {
    digitalWrite(dir1, HIGH);
    digitalWrite(dir2, LOW);
    analogWrite(speedPin, mSpeed);
  }

  Serial.print("Motor speed: ");
  Serial.println(mSpeed);
  
}

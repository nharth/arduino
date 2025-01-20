int numBlinks;
String msg = "How many blinks do you want? ";
int redLED = 12;
int delayTime = 200;
int i;
void setup() {
  Serial.begin(9600);
  pinMode(redLED, OUTPUT);
}

void loop() {
  // ask
  Serial.println(msg);
  
  // wait for input
  while (Serial.available() == 0) {

  }
 // read
  numBlinks = Serial.parseInt();
  for (i = 0; i < numBlinks; i++) {
    digitalWrite(redLED, HIGH);
    delay(delayTime);
    digitalWrite(redLED, LOW);
    delay(delayTime);
  }


}

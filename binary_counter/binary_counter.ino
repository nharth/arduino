int redLED = 8;
int greenLED = 9;
int blueLED = 10;
int yellowLED = 11;
void setup() {
  // put your setup code here, to run once:
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int b;
  int leds[] = {yellowLED, blueLED, greenLED, redLED}; 
  for (int i = 0; i < 16; i++) {
    clear();

    int num = i;
    for (int i = 0; i < 4; i++) {
      int remainder = num % 2;
      if (remainder == 1) {
        digitalWrite(leds[i], HIGH);
      }
      num /= 2;
    }
    delay(500);

  }
  delay(1000);
  
}

void clear() {
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(yellowLED, LOW);
}



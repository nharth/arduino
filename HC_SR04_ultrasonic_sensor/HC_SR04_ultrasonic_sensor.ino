#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_I2C_ADDRESS 0x3C
#define OLED_RESET_PIN -1

Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);
int buttonPin = 8;
int buttonState;
int trigPin = 12;
int echoPin = 11;
int pingTravelTime;
float pingTravelDistance;
float distanceToTarget;
float avg;
float sum = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  screen.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDRESS);
  screen.clearDisplay();
  screen.setTextSize(1);
  screen.setTextColor(WHITE);
  screen.setCursor(1, 1);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  screen.clearDisplay();
  if (buttonState == 0) {
    screen.setCursor(1,1);
    screen.print("Calculating distance...");
    screen.display();
    for (int i = 0; i < 50; i++) {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(10);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10); 
      digitalWrite(trigPin, LOW);
      pingTravelTime = pulseIn(echoPin, HIGH);
      delay(25);
      pingTravelDistance = pingTravelTime * 0.0135039;
      distanceToTarget = pingTravelDistance / 2;
      Serial.println(distanceToTarget); 
      sum += distanceToTarget;
    }
    screen.clearDisplay();
    Serial.println(sum);
    avg = sum / 50;
    screen.setTextSize(1);
    screen.setTextColor(WHITE);
    screen.setCursor(1, 1);
    screen.print(avg);
    screen.print(" inches");
    screen.setCursor(1, 8);
    screen.print(" away from the target");
    screen.display();
    delay(5000);
    sum = 0;
  }
    screen.clearDisplay();
    screen.setCursor(1, 1);
    screen.print("Place the target");
    screen.setCursor(1, 10);
    screen.print("Press to measure");
    screen.display();
}

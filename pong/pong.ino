#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_I2C_ADDRESS 0x3C
#define OLED_RESET_PIN -1

Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);
const int yPin = 27;
int yVal;
const int paddleLength = 8;
const int pixels = 2;
const int startXPos = 58;
const int yPos = 58;
int paddleDir;
int paddle[paddleLength][2];

int ballX = 20;
int ballY = 20;
int ballXDir = 1;
int ballYDir = 1;
int delayTime = 40;
int speed = 0;
int score = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);


  screen.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDRESS);
  screen.clearDisplay();
  screen.setTextSize(1);
  screen.setTextColor(WHITE);
  setupPaddle();
}

void loop() {
  // put your main code here, to run repeatedly:
  screen.clearDisplay();
  yVal = analogRead(yPin);
  screen.setCursor(0, 10);
  screen.print("Score:");
  screen.print(score);
  drawPaddle();
  drawBall();
  movePaddle();
  moveBall();
  screen.display();
  delay(delayTime - speed);
}

void setupPaddle() {
  paddleDir = 0;
  int x = startXPos;
  int y = yPos;
  for (int i = 0; i < paddleLength; i++) {
    paddle[i][0] = x;
    paddle[i][1] = y;
    x += 2;
  }
}

void drawPaddle() {
  for (int i = 0; i < paddleLength; i++) {
    int x = paddle[i][0];
    int y = paddle[i][1];
    screen.drawRect(x, y, pixels, pixels, WHITE);
    screen.fillRect(x, y, pixels, pixels, WHITE);
  }
}

void movePaddle() {
  
  if (yVal < 1900 && paddle[paddleLength - 1][0] < 126) {
    for (int i = 0; i < paddleLength; i++) {
      paddle[i][0] += pixels;
    }
  } else if (yVal > 2500 && paddle[0][0] > 0) {
    for (int i = 0; i < paddleLength; i++) {
      paddle[i][0] -= pixels;
    }
  }
}

void drawBall() {
  screen.drawCircle(ballX, ballY, pixels, WHITE);
  screen.fillCircle(ballX, ballY, pixels, WHITE);
}

void moveBall() {
  if (checkBallPaddleCollision()) {
    ballYDir = -1;
  }
  if (ballY <= 0) {
    ballYDir = 1;
  }
  if (ballX <= 0) {
    ballXDir = 1;
  }
  if (ballX >= 126) {
    ballXDir = -1;
  }
  if (ballY >= 62) {
    ballXDir = 1;
    ballYDir = 1;
    score = 0;
    ballX = 0;
    ballY = 0;
    speed = 0;
  }
  ballX += pixels * ballXDir;
  ballY += pixels * ballYDir;
}

bool checkBallPaddleCollision() {
  for (int i = 0; i < paddleLength; i++) {
    if (paddle[i][0] == ballX && paddle[i][1] == ballY) {
      Serial.print("Ball X: ");
      Serial.print(ballX);
      Serial.print(", Ball Y: ");
      Serial.println(ballY);
      Serial.print("Paddle X: ");
      Serial.print(paddle[i][0]);
      Serial.print(", Paddle Y: ");
      Serial.println(paddle[i][1]);
      score += 10;
      if (delayTime - speed > 1) {
        speed++;
      }
      return true;
    }
  }
  return false;
}

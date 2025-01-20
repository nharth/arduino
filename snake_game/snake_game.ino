#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LinkedList.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_I2C_ADDRESS 0x3C
#define OLED_RESET_PIN -1

Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

struct SnakePart {
    uint8_t xPos;
    uint8_t yPos;
};

LinkedList<SnakePart> snake = LinkedList<SnakePart>();

int snakeLength = 4;
uint8_t pixelSize = 4;
uint8_t initialXCoord = 28;
const uint8_t initialSnake[][2]  = {{initialXCoord, 32}, {initialXCoord - pixelSize, 32},{initialXCoord - pixelSize * 2, 32}, {initialXCoord - pixelSize * 4, 32}};
int xDir = 1;
int yDir = 0;

//mega
// const uint8_t leftButtonPin = 3;
// const uint8_t rightButtonPin = 4;
// const uint8_t downButtonPin = 5;
// const uint8_t upButtonPin = 2;

//esp32
const uint8_t leftButtonPin = 25;
const uint8_t rightButtonPin = 32;
const uint8_t downButtonPin = 13;
const uint8_t upButtonPin = 33;

uint8_t leftButtonState;
uint8_t rightButtonState;
uint8_t downButtonState;
uint8_t upButtonState;
uint8_t foodX;
uint8_t foodY;
uint8_t delayTime = 70;
int score = 0;
int speed = 0;
void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(0));
  Serial.begin(9600);
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);
  pinMode(upButtonPin, INPUT_PULLUP);

  screen.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDRESS);
  screen.clearDisplay();
  screen.setTextSize(1);
  screen.setTextColor(WHITE);
  screen.setCursor(0, 0);
  displayBoundaries();
}

void loop() {
  // put your main code here, to run repeatedly:
  displayGameTitle();
  while (1) {
    playGame();
  }
}
void displayGameTitle() {
    screen.clearDisplay();
    screen.setCursor(8, 10);
    screen.setTextSize(2);
    screen.print("Snake Game");
    screen.setCursor(13, 30);
    screen.setTextSize(1);
    screen.print("Press up to start");
    screen.display();
    do {
      readInput();
    } while (upButtonState == 1);
    delay(500);
    Serial.println(upButtonState);
}

void playGame() {
  setupSnake();
  randomizeFoodPosition();
  score = 0;
  while (1) {
    screen.clearDisplay();
    displayBoundaries();
    drawFood();
    drawSnake();
    moveSnakeAndFood();
    readInputAndChangeDirection();
    if (checkGameOver()) {
      break;
    }
    delay(delayTime - speed);
  }
  displayGameOver();
  while (downButtonState == 1) {
    readInput();
  }
  delay(1000);
}



void displayGameOver() {
    screen.clearDisplay();
    displayBoundaries();
    screen.setCursor(12, 10);
    screen.setTextSize(2);
    screen.print("GAME OVER");
    screen.setCursor(10, 30);
    screen.setTextSize(1);
    screen.print("Your Score: ");
    screen.print(score);
    screen.setCursor(10, 40);
    screen.print("restart: press down");
    screen.display();
}


void setupSnake() {
  speed = 0;
  xDir = 1;
  yDir = 0;
  snake.clear();
  snakeLength = 4;
  for (int i = 0; i < snakeLength; i++) {
    SnakePart part;
    part.xPos = initialSnake[i][0];
    part.yPos = initialSnake[i][1];
    snake.add(part);
  }
}

void displayBoundaries() {
  for (int row = 0; row < 64; row++) {
    for (int col = 0; col < 128; col++) {
      if (row == 0 || row == 63 || col == 0 || col == 127) {
        screen.drawPixel(col, row, WHITE);
      }
    }
  } 
  screen.display();
}

void drawSnake() {
  SnakePart part;
  for (int snakePartIndex = 0; snakePartIndex < snakeLength; snakePartIndex++) {
    part = snake.get(snakePartIndex);
    screen.drawRect(part.xPos, part.yPos, pixelSize, pixelSize, WHITE);
    screen.fillRect(part.xPos, part.yPos, pixelSize, pixelSize, WHITE);
  }
  screen.display();
}

void moveSnakeAndFood() {
  SnakePart currHead = snake.get(0);
  SnakePart newHead;
  int newXPos = currHead.xPos + xDir * pixelSize;
  int newYPos = currHead.yPos + yDir * pixelSize;
  newHead.xPos = newXPos;
  newHead.yPos = newYPos;

  // add to front of snake
  snake.add(0, newHead);

  // remove tail if the snake hasn't eaten the food (when the snake head coordinates are not  equal to the food coordinates).
  // not removing the tail is equivalent to adding one part to the length of the snake.
  if (foodX == currHead.xPos && foodY == currHead.yPos) {
    if (speed < delayTime - 1) {
      speed += 1;
    }
    score += 10;
    randomizeFoodPosition();
    snakeLength++;
  } else {
    snake.pop();
  }
  
}

void readInput() {
  leftButtonState = digitalRead(leftButtonPin);
  rightButtonState = digitalRead(rightButtonPin);
  downButtonState = digitalRead(downButtonPin);
  upButtonState = digitalRead(upButtonPin);
}

void readInputAndChangeDirection() {
  readInput();
  if (leftButtonState == 0 && xDir != 1) {
    yDir = 0;
    xDir = -1;
  } else if (rightButtonState == 0 && xDir != -1) {
    yDir = 0;
    xDir = 1;
  } else if (downButtonState == 0 && yDir != -1) {
    yDir = 1;
    xDir = 0;
  } else if (upButtonState == 0 && yDir != 1) {
    yDir = -1;
    xDir = 0;
  }
}

void drawFood() {
  screen.drawRect(foodX, foodY, pixelSize, pixelSize,WHITE);
  screen.fillRect(foodX, foodY, pixelSize, pixelSize, WHITE);


}

void randomizeFoodPosition() {
  do {
    foodX = random(4, 124);
  } while (foodX % pixelSize != 0);
  do {
    foodY = random(4, 60);
  } while (foodY % pixelSize != 0);
}

bool checkGameOver() {

  return checkOutOfBounds() || checkSnakeCollision();
}

bool checkOutOfBounds() {
  SnakePart head = snake.get(0);
  uint8_t headX = head.xPos;
  uint8_t headY = head.yPos;
  return headX < 0 || headX > 128 - pixelSize || headY < 0 || headY > 64 - pixelSize;
}

bool checkSnakeCollision() {
  SnakePart head = snake.get(0);
  for (int i = 1; i < snakeLength; i++) {
    SnakePart currPart = snake.get(i);
    if (currPart.xPos == head.xPos && currPart.yPos == head.yPos) {
      return true;
    }
  }
  return false;

}

// void display_freeram() {
//   Serial.print(F("- SRAM left: "));
//   Serial.println(freeRam());
// }

// int freeRam() {
//   extern int __heap_start,*__brkval;
//   int v;
//   return (int)&v - (__brkval == 0  
//     ? (int)&__heap_start : (int) __brkval);  
// }

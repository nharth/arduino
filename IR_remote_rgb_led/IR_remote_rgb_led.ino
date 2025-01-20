#include <IRremote.h>
int IRpin = A7;
IRrecv IR(IRpin);
decode_results cmd;
String myCommand;
int redPin = 2;
int greenPin = 3;
int bluePin = 4;
int redVal = 255;
int greenVal = 255;
int blueVal = 255;
int numDecrements = 0;
int stepVal = 15;
int ledState = 1;
bool redState = true;
bool greenState = true;
bool blueState = true;
void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
  IR.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (redState) {
    redVal = 255 - numDecrements * stepVal;
  } else {
    redVal = 0;
  }
  if (greenState) {
    greenVal = 255 - numDecrements * stepVal;
  } else {
    greenVal = 0;
  }
  if (blueState) {
    blueVal = 255 - numDecrements * stepVal;
  } else {
    blueVal = 0;
  }
  analogWrite(redPin, redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin, blueVal);

  // 0 white
  // 1 red
  // 2 green
  // 3 blue
  // 4 cyan (0, 255, 255)
  // 5 magenta (255, 0, 255)
  // 6 yellow (255, 255, 0)
  while (IR.decode(&cmd) == 0) {
  }
  delay(750);
  IR.resume();
  if (cmd.value == 0xFF6897) {
    myCommand = "zero";
    setColorStates(1, 1, 1);
  }
  if (cmd.value == 0xFF30CF) {
    myCommand = "one";
    setColorStates(1, 0, 0);
    Serial.println(redState);

  }
  if (cmd.value == 0xFF18E7) {
    myCommand = "two";
    setColorStates(0, 1, 0);
  }
  if (cmd.value == 0xFF7A85) {
    myCommand = "three";
    setColorStates(0, 0, 1);
  }
  if (cmd.value == 0xFF10EF) {
    myCommand = "four";
    setColorStates(0, 1, 1);
  }
  if (cmd.value == 0xFF38C7) {
    myCommand = "five";
    setColorStates(1, 0, 1);

  }
  if (cmd.value == 0xFF5AA5) {
    myCommand = "six";
    setColorStates(1, 1, 0);

  }
  if (cmd.value == 0xFF42BD) {
    myCommand = "seven";
  }
  if (cmd.value == 0xFF4AB5) {
    myCommand = "eight";
  }
  if (cmd.value == 0xFF52AD) {
    myCommand = "nine";
  }
  if (cmd.value == 0xFFA25D) {
    myCommand = "pwr";
    if (ledState == 1) {
      redVal = 0;
      greenVal = 0;
      blueVal = 0;
      ledState = 0;
      numDecrements = 17;
    } else {
      redVal = 255;
      greenVal = 255;
      blueVal = 255;
      ledState = 1;
      numDecrements = 0;
      setColorStates(1, 1, 1);
    }
  }
  if (cmd.value == 0xFF629D) {
    myCommand = "vol_plus";
  }
  if (cmd.value == 0xFFA857) {
    myCommand = "vol_min";
  }
  if (cmd.value == 0xFFE21D) {
    myCommand = "stop";
  }
  if (cmd.value == 0xFF22DD) {
    myCommand = "rewind";
  }
  if (cmd.value == 0xFF02FD) {
    myCommand = "pause_play";
  }
  if (cmd.value == 0xFFC23D) {
    myCommand = "fast_forward";
  }
  if (cmd.value == 0xFFE01F) {
    myCommand = "down";
    if (ledState && numDecrements < 17) {
      numDecrements++;
    }
  }
  if (cmd.value == 0xFFA857) {
    myCommand = "vol_min";
  }
  if (cmd.value == 0xFF906F) {
    myCommand = "up";
    if (ledState && numDecrements > 0) {
      numDecrements--;
    }
  }
  if (cmd.value == 0xFF9867) {
    myCommand = "eq";
  }
  if (cmd.value == 0xFFB04F) {
    myCommand = "st_rept";
  }
  Serial.println(cmd.value, HEX);
  Serial.println(myCommand);
}

void setColorStates(bool rState, bool gState, bool bState) {
  redState = rState;
  greenState = gState;
  blueState = bState;
}

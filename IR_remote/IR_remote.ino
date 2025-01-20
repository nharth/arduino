#include <IRremote.h>
int IRpin = A7;
IRrecv IR(IRpin);
decode_results cmd;
String myCommand;

int speedPin = 5;
int dir1 = 4;
int dir2 = 3;
int mSpeed = 110;
int motorState = 1;
void setup() {
  // put your setup code here, to run once:
  pinMode(speedPin, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, HIGH);
  Serial.begin(9600);
  IR.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(speedPin, mSpeed);
  while (IR.decode(&cmd) == 0) {
  }
  delay(750);
  IR.resume();
  if (motorState == 1) {
    if (cmd.value == 0xFF6897) {
      myCommand = "zero";
      mSpeed = 0;
    }
    if (cmd.value == 0xFF30CF) {
      myCommand = "one";
      mSpeed = 130;
    }
    if (cmd.value == 0xFF18E7) {
      myCommand = "two";
      mSpeed = 145;
    }
    if (cmd.value == 0xFF7A85) {
      myCommand = "three";
      mSpeed = 150;
    }
    if (cmd.value == 0xFF10EF) {
      myCommand = "four";
      mSpeed = 165;
    }
    if (cmd.value == 0xFF38C7) {
      myCommand = "five";
      mSpeed = 180;
    }
    if (cmd.value == 0xFF5AA5) {
      myCommand = "six";
      mSpeed = 195;
    }
    if (cmd.value == 0xFF42BD) {
      myCommand = "seven";
      mSpeed = 210;
    }
    if (cmd.value == 0xFF4AB5) {
      myCommand = "eight";
      mSpeed = 225;
    }
    if (cmd.value == 0xFF52AD) {
      myCommand = "nine";
      mSpeed = 255;
    }
  }
  if (cmd.value == 0xFFA25D) {
    myCommand = "pwr";
    if (motorState == 0) {
      mSpeed = 255;
      motorState = 1;
    } else {
      mSpeed = 0;
      motorState = 0;
    }
  }
  if (cmd.value == 0xFF629D) {
    myCommand = "vol_plus";
    if (motorState == 1) {
      mSpeed += 5;
      if (mSpeed > 255) {
        mSpeed = 255;
      } else if (mSpeed < 130) {
        mSpeed = 130;
      }
    }
  }
  if (cmd.value == 0xFFA857) {
    myCommand = "vol_min";
    if (motorState == 1) {
      mSpeed -= 5;
      if (mSpeed <= 130) {
        mSpeed = 0;
      }
    }
  }
  if (cmd.value == 0xFFE21D) {
    myCommand = "stop";
  }
  if (cmd.value == 0xFF22DD) {
    myCommand = "rewind";
    if (motorState == 1) {
      digitalWrite(dir1, HIGH);
      digitalWrite(dir2, LOW);
    }
  }
  if (cmd.value == 0xFF02FD) {
    myCommand = "pause_play";
  }
  if (cmd.value == 0xFFC23D) {
    myCommand = "fast_forward";
    if (motorState == 1) {
      digitalWrite(dir1, LOW);
      digitalWrite(dir2, HIGH);
    }
  }
  if (cmd.value == 0xFFE01F) {
    myCommand = "down";
  }
  if (cmd.value == 0xFFA857) {
    myCommand = "vol_min";
  }
  if (cmd.value == 0xFF906F) {
    myCommand = "up";
  }
  if (cmd.value == 0xFF9867) {
    myCommand = "eq";
  }
  if (cmd.value == 0xFFB04F) {
    myCommand = "st_rept";
  }
  Serial.println(myCommand);
}

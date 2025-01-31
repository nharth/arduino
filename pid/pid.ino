#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <math.h>
#include <Servo.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 myIMU = Adafruit_BNO055();

Servo pitchServo;
Servo rollServo;

float q0;
float q1;
float q2;
float q3;

float k1 = 0.5; // proportion constant
float k2 = 70; //constant for derivative
float k3 = = 0.001; //constant for integral 

int millisOld;
int millisNew;
int dt; // change in time between a loop



float rollTarget = 0;
float rollActual;
float rollError = 0;
float rollServoAngle = 90;


float pitchTarget = 0;
float pitchActual;
float pitchError;
float pitchServoAngle = 90;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  myIMU.begin();
  delay(1000);
  int8_t temp = myIMU.getTemp();
  myIMU.setExtCrystalUse(true);
  rollServo.attach(2);
  pitchServo.attach(3);


  rollServo.write(rollServoAngle);
  delay(20);
  pitchServo.write(pitchServoAngle);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t system, gyro, accel, mg = 0;
  myIMU.getCalibration(&system, &gyro, &accel, &mg);
  imu::Quaternion quat = myIMU.getQuat();
  q0 = quat.w();
  q1 = quat.x();
  q2 = quat.y();
  q3 = quat.z();

  rollActual = atan2(2 * (q0 * q1 + q2 * q3), 1 - 2 * (q1 * q1 + q2 * q2)) * 180 / 3.141592654;
  pitchActual = asin(2 * (q0 * q2 - q3 * q1)) * 180 / 3.141592654;

  rollError = rollTarget - rollActual;
  pitchError = pitchTarget - pitchActual;
  if (pitchError < -1.5 || pitchError > 1.5) {
    pitchServoAngle += pitchError * 0.8;
    if (pitchServoAngle > 150) {
      pitchServoAngle = 150;
    } else if (pitchServoAngle < 40) {
      pitchServoAngle = 0;
    }
    pitchServo.write(pitchServoAngle);
    delay(20);
  }

  if (rollError < -1.5 || rollError > 1.5) {
    rollServoAngle += rollError * 0.8;
    if (rollServoAngle > 150) {
      rollServoAngle = 150;
    } else if (rollServoAngle < 0) {
      rollServoAngle = 0;
    }
    rollServo.write(rollServoAngle);
    delay(20);
  }


  Serial.print(rollTarget);
  Serial.print(",");
  Serial.print(rollActual);
  Serial.print(",");
  Serial.print(pitchTarget);
  Serial.print(",");
  Serial.print(pitchActual);
  Serial.print(",");
  Serial.print(quat.w());
  Serial.print(",");
  Serial.print(quat.x());
  Serial.print(",");
  Serial.print(quat.y());
  Serial.print(",");
  Serial.print(quat.z());
  Serial.print(",");
  Serial.print(accel);
  Serial.print(",");
  Serial.print(gyro);
  Serial.print(",");
  Serial.print(mg);
  Serial.print(",");
  Serial.println(system);


  delay(BNO055_SAMPLERATE_DELAY_MS);
}

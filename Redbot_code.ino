#include <RedBot.h>

#define LIR_PIN A3
#define CIR_PIN A6
#define RIR_PIN A7

#define LB_PIN 3
#define RB_PIN 11

int bSpeed = 60;
int tadj = 50;
int Lthrs = 1000;

RedBotMotors motors;
RedBotSensor LIR(LIR_PIN);
RedBotSensor CIR(CIR_PIN);
RedBotSensor RIR(RIR_PIN);
RedBotBumper LB(LB_PIN);
RedBotBumper RB(RB_PIN);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int LIRValue = LIR.read();
  int CIRValue = CIR.read();
  int RIRValue = RIR.read();

  if (LB.read() == LOW) {
    moveForward(-bSpeed, -bSpeed);
    delay(1300);
    stopMotor();
    turnRight();
    delay(1600);
    stopMotor();
    return;
  }

  if (RB.read() == LOW) {
    moveForward(-bSpeed, -bSpeed);
    delay(1300);
    stopMotor();
    turnLeft();
    delay(1600);
    stopMotor();
    return;
  }

  if (CIRValue > Lthrs) {
    moveForward(bSpeed, bSpeed);
  } else if (LIRValue > Lthrs) {
    moveForward(bSpeed - tadj, bSpeed + tadj);
  } else if (RIRValue > Lthrs) {
    moveForward(bSpeed + tadj, bSpeed - tadj);
  } else {
    moveForward(bSpeed, bSpeed);
  }

  delay(50);
}

void moveForward(int leftSpeed, int rightSpeed) {
  motors.leftDrive(leftSpeed);
  motors.rightDrive(rightSpeed);
}

void turnLeft() {
  motors.leftDrive(-bSpeed);
  motors.rightDrive(bSpeed);
}

void turnRight() {
  motors.leftDrive(bSpeed);
  motors.rightDrive(-bSpeed);
}

void stopMotor() {
  motors.leftDrive(0);
  motors.rightDrive(0);
}
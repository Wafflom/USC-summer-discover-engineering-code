#include <Wire.h>
#include <Adafruit_SHTC3.h>

Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();

#define LB 5
#define LF 6
#define RB 9
#define RF 10

#define TRIG 12
#define ECHO 13

#define DISTANCE_THRESHOLD 5
#define TEMPERATURE_THRESHOLD 40.0

int mSpeed = 180;
int tSpeed = 180;
int bTime = 1000;
int tTime = 1000;

void setup() {
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  randomSeed(2);
  Serial.begin(9600);
  Wire.begin();
  
  if (!shtc3.begin()) {
    Serial.println("Couldn't find SHTC3");
    while (1);
  } 
  }

void loop() {
  unsigned int distance = getDistance();
  sensors_event_t temp_event, humidity_event;
  shtc3.getEvent(&humidity_event, &temp_event);
  
  float temperature = temp_event.temperature;

  if (temperature > TEMPERATURE_THRESHOLD) {
    stopMotors();
    Serial.print("Temperature exceeded threshold: ");
    Serial.print(temperature);
    Serial.println(" C");
    while (true);
  } 

  if (distance > 0 && distance < DISTANCE_THRESHOLD) {
    stopMotors();
    delay(500);

    moveBackward();
    delay(bTime);

    stopMotors();
    delay(500);

    int turnDirection = random(2);
    Serial.println(turnDirection);
    if (turnDirection == 0) {
      turnLeft();
    } else if (turnDirection == 1){
      turnRight();
    }
    delay(tTime);

    stopMotors();S
    delay(500);
  } else {   
    moveForward();
  }
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  delay(50);
}

unsigned int getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  unsigned long duration = pulseIn(ECHO, HIGH);
  return duration / 29 / 2;
}

void moveForward() {
  analogWrite(LF, mSpeed);
  analogWrite(LB, 0);
  analogWrite(RF, mSpeed);
  analogWrite(RB, 0);
}

void moveBackward() {
  analogWrite(LF, 0);
  analogWrite(LB, mSpeed);
  analogWrite(RF, 0);
  analogWrite(RB, mSpeed);
}

void turnLeft() {
  analogWrite(LF, 0);
  analogWrite(LB, tSpeed);
  analogWrite(RF, tSpeed);
  analogWrite(RB, 0);
}

void turnRight() {
  analogWrite(LF, tSpeed);
  analogWrite(LB, 0);
  analogWrite(RF, 0);
  analogWrite(RB, tSpeed);
}

void stopMotors() {
  analogWrite(LF, 0);
  analogWrite(LB, 0);
  analogWrite(RF, 0);
  analogWrite(RB, 0);
}
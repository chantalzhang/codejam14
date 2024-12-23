#include "motors.h"
#include <Arduino.h>

extern const int motor1pin1 = 2; // Motor 1 direction control
extern const int motor1pin2 = 3; 
extern const int motor2pin1 = 4; // Motor 2 direction control
extern const int motor2pin2 = 5;
extern const int motor3pin1 = 6; // Motor 3 direction control
extern const int motor3pin2 = 7; 
extern const int motor4pin1 = 8; // Motor 4 direction control
extern const int motor4pin2 = 9; 


void initializeMotors() {
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor3pin1, OUTPUT);
  pinMode(motor3pin2, OUTPUT);
  pinMode(motor4pin1, OUTPUT);
  pinMode(motor4pin2, OUTPUT);
}

void backward() {
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);

      digitalWrite(motor3pin1, HIGH);
      digitalWrite(motor3pin2, LOW);

      digitalWrite(motor4pin1, LOW);
      digitalWrite(motor4pin2, HIGH);
}

void forward() {
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);

      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);

      digitalWrite(motor3pin1, LOW);
      digitalWrite(motor3pin2, HIGH);

      digitalWrite(motor4pin1, HIGH);
      digitalWrite(motor4pin2, LOW);
}

void turn_left() {
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);

      digitalWrite(motor3pin1, LOW);
      digitalWrite(motor3pin2, HIGH);

      digitalWrite(motor4pin1, LOW);
      digitalWrite(motor4pin2, HIGH);
}
void turn_right() {
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);

      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);

      digitalWrite(motor3pin1, HIGH);
      digitalWrite(motor3pin2, LOW);

      digitalWrite(motor4pin1, HIGH);
      digitalWrite(motor4pin2, LOW);
}

void stop() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  digitalWrite(motor3pin1, LOW);
  digitalWrite(motor3pin2, LOW);
  digitalWrite(motor4pin1, LOW);
  digitalWrite(motor4pin2, LOW);
}